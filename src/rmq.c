/**
 *
 *  Copyright (c) 2021 NuWave Technologies, Inc. All rights reserved.
 *
 *  MIT License
 *  https://github.com/nuwavetech/sample-lwc-rabbitmq/blob/main/LICENSE
 *
 */

#pragma nolist
#include <cextdecs>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <tal.h>
#pragma list

#include "rmq.h"

static const char* get_env_value(const char* name, int required);
static void get_message(int argc, char** argv, const char* pathmon_name,
                        const char* server_class);
static void print_send_error(void);
static void print_usage(void);
static void publish_message(int argc, char** argv, const char* pathmon_name,
                            const char* server_class);

int main(int argc, char** argv, char** env) {
  const char* pathmon_name;
  const char* server_class;

  printf("\nLightWave Client(tm) - RabbitMQ sample client.\n");

  /* Get variables from the environment. These are set by the SETENV macro. */
  if ((pathmon_name = get_env_value("PATHMON-NAME", 1)) == NULL) {
    return 0;
  }

  if ((server_class = get_env_value("SERVER-CLASS", 1)) == NULL) {
    return 0;
  }

  /* Check argument count. */
  if (argc < 2) {
    printf("\n");
    print_usage();
    return 0;
  }

  if (strcasecmp(argv[1], "get") == 0) {
    get_message(argc, argv, pathmon_name, server_class);
  } else if (strcasecmp(argv[1], "pub") == 0) {
    publish_message(argc, argv, pathmon_name, server_class);
  } else {
    printf("\n<operation> must be get or pub.\n\n");
    print_usage();
  }

  return 0;
}

static const char* get_env_value(const char* name, int required) {
  const char* v = getenv(name);
  if (v == NULL && required != 0) {
    printf("PARAM \"%s\" not set. Did you run SETENV?\n", name);
  }
  return v;
}

static void get_message(int argc, char** argv, const char* pathmon_name,
                        const char* server_class) {
  long long start_time;
  long long end_time;
  int reply_len;
  short rc;
  error_rp_def* error_rp;
  message_type_def* msg;
  get_messages_rq_def get_messages_rq;

  union {
    lightwave_rp_header_def header;
    get_messages_200_rp_def rp_200;
    get_messages_other_rp_def rp_other;
  } get_messages_rp;

  /* Check arguments. */
  if (argc < 4) {
    printf("\nMissing <queue> argument.\n\n");
    print_usage();
    return;
  }

  if (argc < 3) {
    printf("\nMissing <vhost> argument.\n\n");
    print_usage();
    return;
  }

  /* Get messages. */
  memset(&get_messages_rq, 0, sizeof(get_messages_rq));
  get_messages_rq.lightwave_rq_header.rq_code = rq_get_messages;
  strcpy(get_messages_rq.vhost, argv[2]);
  strcpy(get_messages_rq.name, argv[3]);
  get_messages_rq.get_rq.count_rw = 1;
  strcpy(get_messages_rq.get_rq.ackmode, "ack_requeue_false");
  strcpy(get_messages_rq.get_rq.encoding, "base64");

  start_time = JULIANTIMESTAMP();

  rc = SERVERCLASS_SENDL_((char*)pathmon_name, (short)strlen(pathmon_name),
                          (char*)server_class, (short)strlen(server_class),
                          (char*)&get_messages_rq, (char*)&get_messages_rp,
                          sizeof(get_messages_rq), sizeof(get_messages_rp),
                          &reply_len);

  end_time = JULIANTIMESTAMP();

  /* Pathway error? */
  if (rc != 0) {
    print_send_error();
    return;
  }

  /* Output the results. */
  if (get_messages_rp.header.http_status != 200) {
    error_rp = &get_messages_rp.rp_other.error_rp;
    printf("\nUnexpected HTTP error %d on get message request:\n\n",
           get_messages_rp.header.http_status);
    printf("  error:  %s\n", error_rp->error_rw);
    printf("  reason: %s\n\n", error_rp->reason);
  } else {
    if (get_messages_rp.rp_200.get_rp.msg_count == 0) {
      printf("\nQueue \'%s\' in vhost \'%s\' empty.\n\n", get_messages_rq.name,
             get_messages_rq.vhost);
    } else {

      /* Ensure NULL termination and print the message payload. */
      msg = &get_messages_rp.rp_200.get_rp.item[0];
      msg->payload[msg->payload_bytes] = 0;

      printf("\n%d byte message retrieved: %-40.40s\n\n",
             msg->payload_bytes, msg->payload);
    }
  }

  printf("Request completed in %g seconds.\n\n",
         (double)(end_time - start_time) / 1000000.0);

  return;
}

static void print_send_error(void) {
  short prc;
  short frc;

  SERVERCLASS_SEND_INFO_(&prc, &frc);

  printf("\n\nSERVERCLASS_SEND_ error %hd:%hd occurred.\n\n", prc, frc);
  switch (frc) {
  case 14:
    printf("Did you start the pathway by running STARTPW?\n\n");
    break;
  default:
    break;
  }

  return;
}

static void print_usage(void) {
  printf("Usage:\n");
  printf("        rmq get <vhost> <queue>\n");
  printf("  or\n");
  printf("        rmq pub <vhost> <queue> <routing-key> <quoted-message>\n");
  printf("\nwhere:\n");
  printf("        <vhost> the virtual host name (may not be \"/\")\n");
  printf("        <queue> the name of the queue\n");
  printf("        <routing-key> the message routing key\n");
  printf("        <quoted-message> the message to publish, enclosed in "
         "quotes.\n\n");
}

static void publish_message(int argc, char** argv, const char* pathmon_name,
                            const char* server_class) {

  long long start_time;
  long long end_time;
  int reply_len;
  int rc;
  error_rp_def* error_rp;
  pub_base_64_rq_def* msg;
  pub_base_64_msg_rq_def pub_base_64_msg_rq;

  union {
    lightwave_rp_header_def header;
    pub_base_64_msg_200_rp_def rp_200;
    pub_base_64_msg_other_rp_def rp_other;
  } pub_base64_msg_rp;

  /* Check arguments. */
  if (argc < 6) {
    printf("\nMissing <quoted-message> argument.\n\n");
    print_usage();
    return;
  }

  if (argc < 5) {
    printf("\nMissing <routing-key> argument.\n\n");
    print_usage();
    return;
  }

  if (argc < 4) {
    printf("\nMissing <queue> argument.\n\n");
    print_usage();
    return;
  }

  if (argc < 3) {
    printf("\nMissing <vhost> argument.\n\n");
    print_usage();
    return;
  }

  /* Build publish message requst and send it. */
  memset(&pub_base_64_msg_rq, 0, sizeof(pub_base_64_msg_rq));
  pub_base_64_msg_rq.lightwave_rq_header.rq_code = rq_pub_base_64_msg;
  strcpy(pub_base_64_msg_rq.vhost, argv[2]);
  strcpy(pub_base_64_msg_rq.name, argv[3]);

  msg = &pub_base_64_msg_rq.pub_base_64_rq;
  strcpy(msg->routing_key, argv[4]);
  msg->properties.delivery_mode = 2;
  strcpy(msg->payload_encoding, "base64");
  strcpy(msg->payload, argv[5]);
  msg->payload_size = (unsigned int)strlen(msg->payload);

  start_time = JULIANTIMESTAMP();

  rc = SERVERCLASS_SENDL_((char*)pathmon_name, (short)strlen(pathmon_name),
                          (char*)server_class, (short)strlen(server_class),
                          (char*)&pub_base_64_msg_rq, (char*)&pub_base64_msg_rp,
                          sizeof(pub_base_64_msg_rq), sizeof(pub_base64_msg_rp),
                          &reply_len);

  end_time = JULIANTIMESTAMP();

  /* Pathway error? */
  if (rc != 0) {
    print_send_error();
    return;
  }

  /* Output the results. */
  if (pub_base64_msg_rp.header.http_status != 200) {
    error_rp = &pub_base64_msg_rp.rp_other.error_rp;
    printf("\nUnexpected HTTP error %d on publish message request:\n\n",
           pub_base64_msg_rp.header.http_status);
    printf("  error:  %s\n", error_rp->error_rw);
    printf("  reason: %s\n\n", error_rp->reason);
  } else {
    if (pub_base64_msg_rp.rp_200.pub_rp.routed != 0) {
      printf("\n%d byte message published: %-40.40s\n\n",
             msg->payload_size, msg->payload);
    } else {
      printf("\nThe message was not routed to any queue.\n\n");
    }
  }

  printf("Request completed in %g seconds.\n\n",
         (double)(end_time - start_time) / 1000000.0);

  return;
}

/* End of file. */