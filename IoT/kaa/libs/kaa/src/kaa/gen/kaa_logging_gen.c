/*
 * Copyright 2014-2016 CyberVision, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

# include <inttypes.h>
# include <string.h>
# include "platform/stdio.h"
# include "kaa_logging_gen.h"
# include "avro_src/avro/io.h"
# include "avro_src/encoding.h"
# include "utilities/kaa_mem.h"

/*
 * AUTO-GENERATED CODE
 */



static void kaa_logging_data_collection_float_destroy(void *data)
{
    if (data) {
        kaa_logging_data_collection_float_t *record = (kaa_logging_data_collection_float_t *)data;

        kaa_string_destroy(record->time);
        kaa_data_destroy(record);
    }
}

static void kaa_logging_data_collection_float_serialize(avro_writer_t writer, void *data)
{
    if (data) {
        kaa_logging_data_collection_float_t *record = (kaa_logging_data_collection_float_t *)data;

        kaa_float_serialize(writer, &record->res);
        kaa_string_serialize(writer, record->time);
    }
}

static size_t kaa_logging_data_collection_float_get_size(void *data)
{
    if (data) {
        size_t record_size = 0;
        kaa_logging_data_collection_float_t *record = (kaa_logging_data_collection_float_t *)data;

        record_size += AVRO_FLOAT_SIZE;
        record_size += kaa_string_get_size(record->time);

        return record_size;
    }

    return 0;
}

kaa_logging_data_collection_float_t *kaa_logging_data_collection_float_create(void)
{
    kaa_logging_data_collection_float_t *record = 
            (kaa_logging_data_collection_float_t *)KAA_CALLOC(1, sizeof(kaa_logging_data_collection_float_t));

    if (record) {
        record->serialize = kaa_logging_data_collection_float_serialize;
        record->get_size = kaa_logging_data_collection_float_get_size;
        record->destroy = kaa_logging_data_collection_float_destroy;
    }

    return record;
}

kaa_logging_data_collection_float_t *kaa_logging_data_collection_float_deserialize(avro_reader_t reader)
{
    kaa_logging_data_collection_float_t *record = 
            (kaa_logging_data_collection_float_t *)KAA_MALLOC(sizeof(kaa_logging_data_collection_float_t));

    if (record) {
        record->serialize = kaa_logging_data_collection_float_serialize;
        record->get_size = kaa_logging_data_collection_float_get_size;
        record->destroy = kaa_logging_data_collection_float_destroy;

        avro_binary_encoding.read_float(reader, &record->res);
        record->time = kaa_string_deserialize(reader);
    }

    return record;
}

