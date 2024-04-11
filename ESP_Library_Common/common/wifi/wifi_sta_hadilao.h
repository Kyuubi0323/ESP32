#ifndef _WIFI_STA_HADILAO_H_
#define _WIFI_STA_HADILAO_H_
/**
 * @file wifi_hadilao.h
 * @Kyuubi {Kyuubi} ({khoi.nv0323.work@gmail.com})
 * @brief 
 * @version 0.1
 * @date 2024-04-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */
#include "esp_err.h"
#include "hal/gpio_types.h"

#include <math.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

void wifi_init(void);
void wifi_sta(wifi_config_t wifi_cfg, wifi_mode_t wifi_mode);

#endif
 