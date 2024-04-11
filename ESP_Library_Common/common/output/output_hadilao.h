#ifndef _OUTPUT_HADILAO_H_
#define _OUTPUT_HADILAO_H_

#include "esp_err.h"
#include "hal/gpio_types.h"

void output_io_create(gpio_num_t);
void output_io_set_level(gpio_num_t, int);
void output_io_toggle(gpio_num_t);

#endif 
