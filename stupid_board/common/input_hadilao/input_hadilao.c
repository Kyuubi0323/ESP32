#include <stdio.h>
#include <stdbool.h>
#include <esp_log.h>
#include "driver/gpio.h"
#include "input_hadilao.h"
#include "output_hadilao.h"
#include "esp_attr.h"
input_callback_t input_callback = NULL;



static void IRAM_ATTR gpio_input_handler(void *arg)
{
    int gpio_num = (uint32_t) arg;
    input_callback(gpio_num);
}

void input_set_callback(void *cb)
{
    input_callback = cb;
}

void input_io_create(gpio_num_t gpio_num, interrupt_type_edle_t type)
{
    gpio_reset_pin(gpio_num);
    gpio_set_direction(gpio_num, GPIO_MODE_INPUT);
    gpio_set_pull_mode(gpio_num, GPIO_PULLUP_ONLY);
    gpio_set_intr_type(gpio_num, type);
    gpio_install_isr_service(0);
    gpio_isr_handler_add(gpio_num, gpio_input_handler, (void *)gpio_num);
}

uint8_t input_io_get_level(gpio_num_t gpio_num)
{
    return gpio_get_level(gpio_num);
}
/* example with input button and output LED_GPIO*/
/* app_main.c 
    void input_event_callback(int pin)
    {
        if(pin == GPIO_NUM_X)
        {
            output_io_toggle(BLINK_GPIO);
        }
    }
    void app_main()
    {
        output_io_create(BLINK_GPIO);
        input_io_create(GPIO_NUM_X, HI_TO_LO);
        input_set_callback(input_event_callback);
        while(1)
        {
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    }
*/


