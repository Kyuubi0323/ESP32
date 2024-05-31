#ifndef _MQ135_HADILAO_H_
#define _MQ135_HADILAO_H_
/**
 * @file output_hadilao.h
 * @Kyuubi {Kyuubi} ({khoi.nv0323.work@gmail.com})
 * @brief 
 * @version 0.1
 * @date 2024-04-11
 * 
 * @copyright Copyright (c) 2024
 * 
 */

/* Sensor's characteristics
Rl: Load resistance(can adjust)
Rh: Heater resistance(33Ohm +- 5%)
Ph: Heating consumption(Less than 800mW)
Rs: Sensing resistance(30kO-200kO)
*/

/* Sensitivy characteristics
*/
#include "esp_err.h"
#include "hal/gpio_types.h"

void mq_init(void);


#endif 
