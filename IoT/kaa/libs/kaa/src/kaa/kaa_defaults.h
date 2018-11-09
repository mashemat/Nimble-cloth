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

# ifndef KAA_DEFAULTS_H_
# define KAA_DEFAULTS_H_

/**
 *
 * DO NOT EDIT THIS FILE. IT IS AUTO-GENERATED.
 *
 */

# include "kaa_common.h"

# ifdef __cplusplus
extern "C" {
# endif

# define KAA_BUILD_VERSION             "0.10.0"
# define KAA_BUILD_COMMIT_HASH         ""

# define KAA_SDK_TOKEN                 "CNYdvTtVdHxRLRmIjShIWr4NRzk"

# define KAA_PROFILE_SCHEMA_VERSION    0


# define KAA_SYNC_TIMEOUT               60000L


/**
 * @brief Uses to represent transport-specific connection data to establish
 * connection to Bootstrap servers.
 *
 * @see kaa_transport_protocol_id_t
 * @see kaa_access_point_t
 */
typedef struct {
    kaa_transport_protocol_id_t    protocol_id;
    kaa_access_point_t             access_point;
} kaa_bootstrap_server_connection_data_t;

# define KAA_BOOTSTRAP_ACCESS_POINT_COUNT    2

static const kaa_bootstrap_server_connection_data_t KAA_BOOTSTRAP_ACCESS_POINTS[KAA_BOOTSTRAP_ACCESS_POINT_COUNT] =
{
    {
        { 0xfb9a3cf0, 1 },
        {
            0x929a2016,
            319,
            (char []) {
            0 , 0 , 1 , 38 , 48 , -126 , 1 , 34 , 48 , 13 , 6 , 9 , 42 , -122 , 72 , -122 , -9 , 13 , 1 , 1 , 1 , 5 , 0 , 3 , -126 , 1 , 15 , 0 , 48 , -126 , 1 , 10 , 2 , -126 , 1 , 1 , 0 , -117 , 9 , 123 , 54 , 117 , 94 , -49 , -76 , 62 , -116 , 82 , -54 , 93 , -28 , 35 , -47 , 114 , 45 , 39 , -45 , 112 , -119 , -30 , 41 , -114 , 88 , 117 , -22 , 31 , -67 , -43 , -75 , 69 , -115 , -81 , 55 , 55 , 67 , -39 , 81 , 36 , -37 , -47 , -64 , -99 , 81 , 8 , 86 , -123 , 105 , 15 , -95 , 112 , -64 , 0 , 21 , 48 , 68 , 127 , 7 , -98 , -76 , -111 , 26 , 41 , 123 , 68 , -23 , -11 , -120 , -118 , -110 , 61 , 104 , 81 , -53 , -70 , 8 , 94 , 6 , -11 , -73 , 93 , 125 , -48 , 38 , -91 , -31 , -58 , 14 , -12 , -66 , -120 , -63 , -66 , -68 , -30 , -20 , -79 , 6 , -74 , 49 , 98 , 37 , 59 , 45 , -3 , -71 , -126 , 112 , 2 , 113 , 119 , 9 , 39 , -111 , 20 , -105 , -103 , 9 , 20 , 47 , -32 , -80 , -49 , -83 , -68 , -79 , -110 , 110 , -8 , -122 , -37 , 24 , -62 , 120 , -84 , -20 , 86 , -40 , -104 , -43 , -112 , 101 , -74 , 67 , -61 , 9 , -126 , -29 , 48 , -94 , -96 , -6 , -40 , -121 , 53 , -24 , 7 , 24 , -45 , 109 , 14 , 125 , 24 , 20 , -105 , 86 , -31 , -49 , 21 , 51 , -113 , -121 , -87 , -47 , -28 , -126 , -75 , -9 , -49 , 103 , -108 , -54 , 111 , -97 , -81 , -98 , -106 , 25 , 0 , -79 , -7 , -24 , 65 , 43 , -32 , -37 , -109 , -32 , 93 , 124 , 15 , -128 , 118 , 87 , 51 , 98 , -3 , 80 , 24 , 102 , -69 , -99 , 118 , -85 , -87 , -91 , -74 , -105 , 95 , 89 , 7 , 71 , -88 , -37 , -87 , -86 , 5 , 62 , 16 , 73 , -54 , -83 , -123 , 115 , -126 , -49 , -43 , 71 , 12 , 21 , 31 , -28 , -59 , -109 , -84 , -60 , 44 , 126 , 11 , 106 , 16 , -6 , -108 , -59 , 2 , 3 , 1 , 0 , 1 , 0 , 0 , 0 , 13 , 49 , 57 , 50 , 46 , 49 , 54 , 56 , 46 , 49 , 46 , 49 , 52 , 53 , 0 , 0 , 38 , -95             }
        }
    },
    {
        { 0x56c8ff92, 1 },
        {
            0x929a2016,
            319,
            (char []) {
            0 , 0 , 1 , 38 , 48 , -126 , 1 , 34 , 48 , 13 , 6 , 9 , 42 , -122 , 72 , -122 , -9 , 13 , 1 , 1 , 1 , 5 , 0 , 3 , -126 , 1 , 15 , 0 , 48 , -126 , 1 , 10 , 2 , -126 , 1 , 1 , 0 , -117 , 9 , 123 , 54 , 117 , 94 , -49 , -76 , 62 , -116 , 82 , -54 , 93 , -28 , 35 , -47 , 114 , 45 , 39 , -45 , 112 , -119 , -30 , 41 , -114 , 88 , 117 , -22 , 31 , -67 , -43 , -75 , 69 , -115 , -81 , 55 , 55 , 67 , -39 , 81 , 36 , -37 , -47 , -64 , -99 , 81 , 8 , 86 , -123 , 105 , 15 , -95 , 112 , -64 , 0 , 21 , 48 , 68 , 127 , 7 , -98 , -76 , -111 , 26 , 41 , 123 , 68 , -23 , -11 , -120 , -118 , -110 , 61 , 104 , 81 , -53 , -70 , 8 , 94 , 6 , -11 , -73 , 93 , 125 , -48 , 38 , -91 , -31 , -58 , 14 , -12 , -66 , -120 , -63 , -66 , -68 , -30 , -20 , -79 , 6 , -74 , 49 , 98 , 37 , 59 , 45 , -3 , -71 , -126 , 112 , 2 , 113 , 119 , 9 , 39 , -111 , 20 , -105 , -103 , 9 , 20 , 47 , -32 , -80 , -49 , -83 , -68 , -79 , -110 , 110 , -8 , -122 , -37 , 24 , -62 , 120 , -84 , -20 , 86 , -40 , -104 , -43 , -112 , 101 , -74 , 67 , -61 , 9 , -126 , -29 , 48 , -94 , -96 , -6 , -40 , -121 , 53 , -24 , 7 , 24 , -45 , 109 , 14 , 125 , 24 , 20 , -105 , 86 , -31 , -49 , 21 , 51 , -113 , -121 , -87 , -47 , -28 , -126 , -75 , -9 , -49 , 103 , -108 , -54 , 111 , -97 , -81 , -98 , -106 , 25 , 0 , -79 , -7 , -24 , 65 , 43 , -32 , -37 , -109 , -32 , 93 , 124 , 15 , -128 , 118 , 87 , 51 , 98 , -3 , 80 , 24 , 102 , -69 , -99 , 118 , -85 , -87 , -91 , -74 , -105 , 95 , 89 , 7 , 71 , -88 , -37 , -87 , -86 , 5 , 62 , 16 , 73 , -54 , -83 , -123 , 115 , -126 , -49 , -43 , 71 , 12 , 21 , 31 , -28 , -59 , -109 , -84 , -60 , 44 , 126 , 11 , 106 , 16 , -6 , -108 , -59 , 2 , 3 , 1 , 0 , 1 , 0 , 0 , 0 , 13 , 49 , 57 , 50 , 46 , 49 , 54 , 56 , 46 , 49 , 46 , 49 , 52 , 53 , 0 , 0 , 38 , -96             }
        }
    }};



# define KAA_CONFIGURATION_DATA_LENGTH    1

static const char KAA_CONFIGURATION_DATA[KAA_CONFIGURATION_DATA_LENGTH] =
{
2 };

# ifdef __cplusplus
} // extern "C"
# endif

# endif /* KAA_DEFAULTS_H_ */

