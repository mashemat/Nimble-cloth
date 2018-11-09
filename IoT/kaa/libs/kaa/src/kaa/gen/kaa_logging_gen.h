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

# ifndef KAA_LOGGING_GEN_H_
# define KAA_LOGGING_GEN_H_

# include "kaa_common_schema.h"
# include "collections/kaa_list.h"

# ifdef __cplusplus
extern "C" {
# endif



typedef struct {
    float res;
    kaa_string_t * time;

    serialize_fn serialize;
    get_size_fn  get_size;
    destroy_fn   destroy;
} kaa_logging_data_collection_float_t;

kaa_logging_data_collection_float_t *kaa_logging_data_collection_float_create(void);
kaa_logging_data_collection_float_t *kaa_logging_data_collection_float_deserialize(avro_reader_t reader);

#ifdef __cplusplus
}      /* extern "C" */
#endif
#endif