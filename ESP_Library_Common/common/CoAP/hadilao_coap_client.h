#ifndef _HADILAO_COAP_CLIENT_H_
#define _HADILAO_COAP_CLIENT_H_

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "freertos/ringbuf.h"
#include "freertos/semphr.h"

#include "nvs_flash.h"

#include "esp_log.h"
#include "esp_wifi.h"
#include "esp_smartconfig.h"
#include "esp_spiffs.h"
#include "esp_http_client.h"
#include "esp_attr.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_http_server.h"
#include "esp_mac.h"
#include "esp_chip_info.h"

//#include "coap3/coap.h"

#include "driver/gpio.h"
#include "driver/uart.h"
#include "driver/spi_master.h"

#include <math.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netdb.h>
#include <sys/param.h>

// coap_response_t
// message_handler(coap_session_t *session,
//                 const coap_pdu_t *sent,
//                 const coap_pdu_t *received,
//                 const coap_mid_t mid);


#endif
