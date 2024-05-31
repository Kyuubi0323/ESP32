#include <stdio.h>
#include <esp_log.h>
#include "driver/gpio.h"
#include "mq135_hadilao.h"

#define MQ135_PULLDOWNRES 10000         
#define default_ppm_CO2 408
#define default_ppm_NH4 5

#include <math.h>

