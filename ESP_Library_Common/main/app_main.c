#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

#include "esp_log.h"

#include "sdkconfig.h"
#include "output_hadilao.h"
//#include "input_hadilao.h"
#define LED 2
static const char *TAG = "MAIN";
void app_main()
{
    output_io_create(LED);

    while(1)
    {
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        output_io_toggle(LED);
        ESP_LOGI(TAG, "TOGGLE");
    }
    
}