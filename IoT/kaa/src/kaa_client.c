#include <target.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <time.h>
#include <math.h>

#include <kaa/kaa_error.h>
#include <kaa/kaa_context.h>
#include <kaa/platform/kaa_client.h>
#include <kaa_configuration_manager.h>
#include <kaa_logging.h>
#include <platform-impl/common/ext_log_upload_strategies.h>

#define DEMO_LOG_UPLOAD_THRESHOLD 1

/* Shared variables */
static int newdata = 0;
static float resultant;
static kaa_string_t  *date;
/*                 */


pthread_mutex_t lock;
static long current_time = 0;

void *serverThread(void){

   int sockfd, newsockfd, portno, clilen;
   char buffer[256];
   struct sockaddr_in serv_addr, cli_addr;
   int  n;
	
   printf("Waiting for connection to database...\n");
   sleep(5);
	
   time_t t = time(NULL);
   struct tm tm = *localtime(&t);
   
   /* First call to socket() function */
   sockfd = socket(AF_INET, SOCK_STREAM, 0);
   
   if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   else
       printf("socket created\n");
   
   /* Initialize socket structure */
   bzero((char *) &serv_addr, sizeof(serv_addr));
   portno = 8081;
   
   serv_addr.sin_family = AF_INET;
   serv_addr.sin_addr.s_addr = INADDR_ANY;
   serv_addr.sin_port = htons(portno);
   
   /* Now bind the host address using bind() call.*/
   if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR on binding");
      exit(1);
   }
      
   /* Now start listening for the clients, here process will
      * go in sleep mode and will wait for the incoming connection
   */
   
   while(1){
   
		printf("listening for a connection..\n");   
		listen(sockfd,5);
		clilen = sizeof(cli_addr);
		
		/* Accept actual connection from the client */
		newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
		printf("connection accepted\n");
	
		if (newsockfd < 0) {
		   perror("ERROR on accept");
		   exit(1);
		}
		
		/* If connection is established then start communicating */
		bzero(buffer,256);
		n = read( newsockfd,buffer,255 );
		
		if (n < 0) {
		   perror("ERROR reading from socket");
		   exit(1);
		}
		
		printf("Here is the message: %s\n",buffer);
		/*        take time         */
		time_t t = time(NULL);
   		struct tm tm = *localtime(&t);
		/*			    */
	        pthread_mutex_lock(&lock);
                sscanf(buffer, "%f", &resultant);
                newdata = 1;
		sprintf(&date, "%d/%d/%d-%d:%d:%d", tm.tm_year + 1900, tm.tm_mon + 1, tm.tm_mday, tm.tm_hour, tm.tm_min, tm.tm_sec);
		printf("DATE: %s\n", &date); 
                pthread_mutex_unlock(&lock);
                
		/* Write a response to the client */
		n = write(newsockfd,"k",1);
		
		if (n < 0) {
		   perror("ERROR writing to socket");
		   exit(1);
		}
		close(newsockfd);
   }
   
   pthread_exit(NULL);
}

typedef struct {
    kaa_client_t *kaa_client;
    int32_t sample_period;
    time_t last_upload_time;
} accelerometer_sensor_context;

static void error_cleanup(kaa_client_t *client)
{
    if (client != NULL) {
        kaa_client_stop(client);
        kaa_client_destroy(client);
    }

    exit(EXIT_FAILURE);
}

static kaa_error_t configuration_update(void *context,
        const kaa_configuration_my_configuration_t *configuration)
{
    if (!context || !configuration) {
        return KAA_ERR_BADPARAM;
    }

    printf("Received new sample period: %d\n", configuration->sample_period);
    accelerometer_sensor_context *sensor_context = context;
    sensor_context->sample_period = configuration->sample_period;
    return KAA_ERR_NONE;
}

static void send_data(void *context)
{		 
		float res;
		int local_flag;
		pthread_mutex_lock(&lock);
		local_flag = newdata;
		pthread_mutex_unlock(&lock);

		if(local_flag){

		 kaa_user_log_record_t *log_record = kaa_logging_data_collection_float_create();

		pthread_mutex_lock(&lock);
		 //res = sqrt(pow(d_0, 2) + pow(d_1,2) + pow(d_2,2));
		 //log_record->data_0 = d_0;
		 //log_record->data_1 = d_1;
		 //log_record->data_2 = d_2;
		 log_record->res = resultant;
		 log_record->time = kaa_string_copy_create(&date);
		 newdata = 0;

 		pthread_mutex_unlock(&lock);

		 printf("Sampled data: %f %s\n", log_record->res, log_record->time);

			 kaa_error_t error = kaa_logging_add_record(
		         kaa_client_get_context(context)->log_collector,
		         log_record, NULL);

		 if (error) {
		     demo_printf("Failed to add log record, error code %d\r\n");
		    // error_cleanup(kaa_client);
		 }

		 log_record->destroy(log_record);
    		}
}

static void data_update(void *context)
{
    if (context == NULL) {
        return;
    }

    accelerometer_sensor_context *sensor_context = context;
    time_t current = time(NULL);

    if (current - sensor_context->last_upload_time >=
            sensor_context->sample_period) {
        send_data(sensor_context->kaa_client);
        sensor_context->last_upload_time = time(NULL);
    }
}



int main(void){

	demo_printf("4Data demo started\r\n");
	
	pthread_t thread_id;
	
	int ret_code = pthread_create(&thread_id, NULL, serverThread, NULL);
	
	if (ret_code){
		demo_printf("UNABLE TO CREATE SERVERTHREAD\n");
		exit(EXIT_FAILURE);
	}
	
	/**
     * Initialize Kaa client.
     */
    kaa_client_t *kaa_client = NULL;
    kaa_error_t error = kaa_client_create(&kaa_client, NULL);

    if (error) {
        demo_printf("Failed to create Kaa client\r\n", error);
        return EXIT_FAILURE;
    }
    
    accelerometer_sensor_context sensor_context;
    sensor_context.kaa_client = kaa_client;
    kaa_configuration_root_receiver_t receiver = {
        &sensor_context,
        configuration_update,
    };

    error = kaa_configuration_manager_set_root_receiver(
            kaa_client_get_context(kaa_client)->configuration_manager,
            &receiver);

    if (error) {
        demo_printf("Failed to set configuiration receiver\r\n", error);
        return EXIT_FAILURE;
    }
    
    const kaa_configuration_my_configuration_t *default_configuration =
            kaa_configuration_manager_get_configuration(kaa_client_get_context(kaa_client)->configuration_manager);

    sensor_context.sample_period = default_configuration->sample_period;
    sensor_context.last_upload_time = time(NULL);

	 void *log_upload_strategy_context = NULL;
    error = ext_log_upload_strategy_create(kaa_client_get_context(kaa_client),
            &log_upload_strategy_context, KAA_LOG_UPLOAD_VOLUME_STRATEGY);

    if (error) {
        demo_printf("Failed to create log upload strategy, error code %d\r\n", error);
        return EXIT_FAILURE;
    }

    error = ext_log_upload_strategy_set_threshold_count(log_upload_strategy_context,
            DEMO_LOG_UPLOAD_THRESHOLD);

    if (error) {
        demo_printf("Failed to set threshold log record count, error code %d\r\n", error);
        return EXIT_FAILURE;
    }

    error = kaa_logging_set_strategy(kaa_client_get_context(kaa_client)->log_collector,
            log_upload_strategy_context);

    if (error) {
        demo_printf("Failed to set log upload strategy, error code %d\r\n", error);
        return EXIT_FAILURE;
    }

    /**
     * Start Kaa client main loop.
     */
    error = kaa_client_start(kaa_client, data_update,
            &sensor_context, sensor_context.sample_period);

    if (error) {
        demo_printf("Failed to start Kaa client, error code %d\r\n", error);
        return EXIT_FAILURE;
    }

    /**
     * Destroy Kaa client.
     */
    kaa_client_destroy(kaa_client);

    exit(EXIT_SUCCESS);
	
}

