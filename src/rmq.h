/* SCHEMA PRODUCED DATE - TIME : 1/21/2021 - 15:51:28 */
#pragma section lightwave_rp_code_enum
/* Definition LIGHTWAVE-RP-CODE-ENUM created on 01/21/2021 at 15:51 */
enum
{
   lw_rp_success = 0,
   lw_rp_info = 1,
   lw_rp_error = 2
};
typedef short                           lightwave_rp_code_enum_def;
#pragma section lightwave_info_code_enum
/* Definition LIGHTWAVE-INFO-CODE-ENUM created on 01/21/2021 at 15:51 */
enum
{
   lw_info_field_truncated = 100,
   lw_info_array_truncated = 101
};
typedef short                           lightwave_info_code_enum_def;
#pragma section lightwave_error_src_enum
/* Definition LIGHTWAVE-ERROR-SRC-ENUM created on 01/21/2021 at 15:51 */
enum
{
   lw_error_src_lightwave = 1,
   lw_error_src_http = 2,
   lw_error_src_tcpip = 3,
   lw_error_src_ssl = 4
};
typedef short                           lightwave_error_src_enum_def;
#pragma section lightwave_error_enum
/* Definition LIGHTWAVE-ERROR-ENUM created on 01/21/2021 at 15:51 */
enum
{
   lw_error_invalid_license = 1,
   lw_error_invalid_header = 2,
   lw_error_invalid_rq_code = 3,
   lw_error_invalid_type = 4,
   lw_error_serialization_error = 5,
   lw_error_deserialization_error = 6,
   lw_error_request_timeout = 7,
   lw_error_response_not_defined = 12,
   lw_error_invalid_uri_scheme = 100,
   lw_error_invalid_api_def = 101,
   lw_error_invalid_base_uri = 102,
   lw_error_invalid_hdr_version = 103,
   lw_error_signature_error = 104,
   lw_error_internal_error = 500
};
typedef short                           lightwave_error_enum_def;
#pragma section lightwave_rq_header
/* Definition LIGHTWAVE-RQ-HEADER created on 01/21/2021 at 15:51 */
#include <tnsint.h>
#pragma fieldalign shared2 __lightwave_rq_header
typedef struct __lightwave_rq_header
{
   short                           rq_code;
   unsigned short                  rq_version;
   __uint32_t                      rq_timeout;
   char                            reserved[24];
} lightwave_rq_header_def;
#define lightwave_rq_header_def_Size 32
#pragma section lightwave_rp_header
/* Definition LIGHTWAVE-RP-HEADER created on 01/21/2021 at 15:51 */
#pragma fieldalign shared2 __lightwave_rp_header
typedef struct __lightwave_rp_header
{
   short                           rp_code;
   short                           http_status;
   short                           info_code;
   short                           info_detail;
   char                            reserved[24];
} lightwave_rp_header_def;
#define lightwave_rp_header_def_Size 32
#pragma section lightwave_error_rp
/* Definition LIGHTWAVE-ERROR-RP created on 01/21/2021 at 15:51 */
#include <tnsint.h>
#pragma fieldalign shared2 __lightwave_error_rp
typedef struct __lightwave_error_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   __int32_t                       error_source;
   __int32_t                       error_code;
   __int32_t                       error_subcode;
   char                            error_message[4096];
} lightwave_error_rp_def;
#define lightwave_error_rp_def_Size 4140
#pragma section sample_lwc_rabbitmq_val
/* Definition SAMPLE-LWC-RABBITMQ-VAL created on 01/21/2021 at 15:51 */
#pragma fieldalign shared2 __sample_lwc_rabbitmq_val
typedef struct __sample_lwc_rabbitmq_val
{
   short                           rq_pub_string_msg;
   /*value is 1*/
   short                           rq_pub_base_64_msg;
   /*value is 2*/
   short                           rq_get_messages;
   /*value is 3*/
} sample_lwc_rabbitmq_val_def;
#define sample_lwc_rabbitmq_val_def_Size 6
#pragma section sample_lwc_rabbitmq_enm
/* Definition SAMPLE-LWC-RABBITMQ-ENM created on 01/21/2021 at 15:51 */
enum
{
   rq_pub_string_msg = 1,
   rq_pub_base_64_msg = 2,
   rq_get_messages = 3
};
typedef short                           sample_lwc_rabbitmq_enm_def;
#pragma section basic_properties
/* Definition BASIC-PROPERTIES created on 01/21/2021 at 15:51 */
#include <tnsint.h>
#pragma fieldalign shared2 __basic_properties
typedef struct __basic_properties
{
   char                            cluster_id[32];
   char                            app_id[32];
   char                            user_id[32];
   char                            type_rw[32];
   __uint32_t                      timestamp;
   char                            message_id[32];
   char                            expiration[32];
   char                            reply_to[32];
   char                            correlation_id[32];
   __int32_t                       priority;
   __int32_t                       delivery_mode;
   short                           headers_count;
   struct
   {
      char                            map_key[32];
      char                            map_value[32];
   } headers[10];
   char                            content_encoding[32];
   char                            content_type[32];
} basic_properties_def;
#define basic_properties_def_Size 974
#pragma section message_type
/* Definition MESSAGE-TYPE created on 01/21/2021 at 15:51 */
#pragma fieldalign shared2 __message_type
typedef struct __message_type
{
   __int32_t                       payload_bytes;
   __int32_t                       redelivered;
   char                            exchange[64];
   char                            routing_key[64];
   __uint32_t                      message_count;
   basic_properties_def            properties;
   char                            payload_encoding[64];
   __uint32_t                      payload_size;
   char                            payload[50000];
} message_type_def;
#define message_type_def_Size 51182
#pragma section get_rq
/* Definition GET-RQ created on 01/21/2021 at 15:51 */
#include <tnsint.h>
#pragma fieldalign shared2 __get_rq
typedef struct __get_rq
{
   __uint32_t                      count_rw;
   char                            ackmode[64];
   char                            encoding[64];
   __uint32_t                      truncate;
} get_rq_def;
#define get_rq_def_Size 136
#pragma section get_rp
/* Definition GET-RP created on 01/21/2021 at 15:51 */
#pragma fieldalign shared2 __get_rp
typedef struct __get_rp
{
   short                           msg_count;
   message_type_def                item[10];
} get_rp_def;
#define get_rp_def_Size 511822
#pragma section pub_string_rq
/* Definition PUB-STRING-RQ created on 01/21/2021 at 15:51 */
#pragma fieldalign shared2 __pub_string_rq
typedef struct __pub_string_rq
{
   basic_properties_def            properties;
   char                            routing_key[64];
   char                            payload_encoding[64];
   char                            payload[50000];
} pub_string_rq_def;
#define pub_string_rq_def_Size 51102
#pragma section pub_base_64_rq
/* Definition PUB-BASE-64-RQ created on 01/21/2021 at 15:51 */
#pragma fieldalign shared2 __pub_base_64_rq
typedef struct __pub_base_64_rq
{
   basic_properties_def            properties;
   char                            routing_key[64];
   char                            payload_encoding[64];
   __uint32_t                      payload_size;
   char                            payload[50000];
} pub_base_64_rq_def;
#define pub_base_64_rq_def_Size 51106
#pragma section pub_rp
/* Definition PUB-RP created on 01/21/2021 at 15:51 */
#include <tnsint.h>
#pragma fieldalign shared2 __pub_rp
typedef struct __pub_rp
{
   __int32_t                       routed;
} pub_rp_def;
#define pub_rp_def_Size 4
#pragma section error_rp
/* Definition ERROR-RP created on 01/21/2021 at 15:51 */
#pragma fieldalign shared2 __error_rp
typedef struct __error_rp
{
   char                            error_rw[128];
   char                            reason[1024];
} error_rp_def;
#define error_rp_def_Size 1152
#pragma section pub_string_msg_rq
/* Definition PUB-STRING-MSG-RQ created on 01/21/2021 at 15:51 */
#pragma fieldalign shared2 __pub_string_msg_rq
typedef struct __pub_string_msg_rq
{
   lightwave_rq_header_def         lightwave_rq_header;
   char                            vhost[64];
   char                            name[64];
   pub_string_rq_def               pub_string_rq;
} pub_string_msg_rq_def;
#define pub_string_msg_rq_def_Size 51262
#pragma section pub_string_msg_200_rp
/* Definition PUB-STRING-MSG-200-RP created on 01/21/2021 at 15:51 */
#pragma fieldalign shared2 __pub_string_msg_200_rp
typedef struct __pub_string_msg_200_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   pub_rp_def                      pub_rp;
} pub_string_msg_200_rp_def;
#define pub_string_msg_200_rp_def_Size 36
#pragma section pub_string_msg_other_rp
/* Definition PUB-STRING-MSG-OTHER-RP created on 01/21/2021 at 15:51 */
#pragma fieldalign shared2 __pub_string_msg_other_rp
typedef struct __pub_string_msg_other_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   error_rp_def                    error_rp;
} pub_string_msg_other_rp_def;
#define pub_string_msg_other_rp_def_Size 1184
#pragma section pub_base_64_msg_rq
/* Definition PUB-BASE-64-MSG-RQ created on 01/21/2021 at 15:51 */
#pragma fieldalign shared2 __pub_base_64_msg_rq
typedef struct __pub_base_64_msg_rq
{
   lightwave_rq_header_def         lightwave_rq_header;
   char                            vhost[64];
   char                            name[64];
   pub_base_64_rq_def              pub_base_64_rq;
} pub_base_64_msg_rq_def;
#define pub_base_64_msg_rq_def_Size 51266
#pragma section pub_base_64_msg_200_rp
/* Definition PUB-BASE-64-MSG-200-RP created on 01/21/2021 at 15:51 */
#pragma fieldalign shared2 __pub_base_64_msg_200_rp
typedef struct __pub_base_64_msg_200_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   pub_rp_def                      pub_rp;
} pub_base_64_msg_200_rp_def;
#define pub_base_64_msg_200_rp_def_Size 36
#pragma section pub_base_64_msg_other_rp
/* Definition PUB-BASE-64-MSG-OTHER-RP created on 01/21/2021 at 15:51 */
#pragma fieldalign shared2 __pub_base_64_msg_other_rp
typedef struct __pub_base_64_msg_other_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   error_rp_def                    error_rp;
} pub_base_64_msg_other_rp_def;
#define pub_base_64_msg_other_rp_def_Size 1184
#pragma section get_messages_rq
/* Definition GET-MESSAGES-RQ created on 01/21/2021 at 15:51 */
#pragma fieldalign shared2 __get_messages_rq
typedef struct __get_messages_rq
{
   lightwave_rq_header_def         lightwave_rq_header;
   char                            vhost[64];
   char                            name[64];
   get_rq_def                      get_rq;
} get_messages_rq_def;
#define get_messages_rq_def_Size 296
#pragma section get_messages_200_rp
/* Definition GET-MESSAGES-200-RP created on 01/21/2021 at 15:51 */
#pragma fieldalign shared2 __get_messages_200_rp
typedef struct __get_messages_200_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   get_rp_def                      get_rp;
} get_messages_200_rp_def;
#define get_messages_200_rp_def_Size 511854
#pragma section get_messages_other_rp
/* Definition GET-MESSAGES-OTHER-RP created on 01/21/2021 at 15:51 */
#pragma fieldalign shared2 __get_messages_other_rp
typedef struct __get_messages_other_rp
{
   lightwave_rp_header_def         lightwave_rp_header;
   error_rp_def                    error_rp;
} get_messages_other_rp_def;
#define get_messages_other_rp_def_Size 1184
