#ifndef _WEB_HADILAO_H_
#define _WEB_HADILAO_H_

#include <math.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "esp_http_server.h"

httpd_handle_t start_webserver(void);
void stop_webserver(httpd_handle_t server);

#endif
