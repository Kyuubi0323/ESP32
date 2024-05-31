#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"
#include "freertos/queue.h"
#include "freertos/ringbuf.h"
#include "freertos/semphr.h"

#include <stdio.h>
#include <string.h>
#include <inttypes.h>
#include <stdarg.h>
#include <stdlib.h>
#include <errno.h>

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

#include "driver/gpio.h"
#include "driver/uart.h"
#include "driver/spi_master.h"
#include "driver/ledc.h"
#include "driver/adc.h"
#include "esp_system.h"
#include "esp_task.h"
#include "esp_log.h"
#include "esp_event_loop.h"
#include "esp_wifi.h"
#include "nvs_flash.h"

#include "blynk_hadilao.h"

#include "output_hadilao.h"
#include "input_hadilao.h"
#include "wifi_sta_hadilao.h"
#include "wifi_ap_hadilao.h"
#include "uart_hadilao.h"

#define MQ135_GPIO_PIN      33
#define sample_rate         4096
#define LED                 14

#define BLYNK_TEMPLATE_ID "TMPL6NBtHqwZp"
#define BLYNK_TEMPLATE_NAME "LED on off"
#define BLYNK_AUTH_TOKEN "tEFML33gimTMpXsN3ux5zRa4Hl80TUY3"
#define BLYNK_TOKEN CONFIG_BLYNK_TOKEN
#define BLYNK_SERVER CONFIG_BLYNK_SERVER

#define ADC_BITS 10
#define ADC_WIDTH(x) ((x) - 9)
#define ADC_CHANNEL 4 /* IO32 */
#define ADC_ATTEN ADC_ATTEN_0db

#define PWM_PIN 2
#define PWM_BITS 10
#define PWM_FREQ 1000
#define PWM_TIMER LEDC_TIMER_0
#define PWM_MODE LEDC_HIGH_SPEED_MODE
#define PWM_CHANNEL LEDC_CHANNEL_0

enum {
	VP_PWM = 0,
	VP_ADC,
	VP_UPTIME,
};

static const char *TAG = "blynk-example";

/* Blynk client state handler */
static void state_handler(blynk_client_t *c, const blynk_state_evt_t *ev, void *data) {
	ESP_LOGI(TAG, "state: %d\n", ev->state);
}

/* Virtual write handler */
static void vw_handler(blynk_client_t *c, uint16_t id, const char *cmd, int argc, char **argv, void *data) {
	if (argc > 1 && atoi(argv[0]) == VP_PWM) {
		uint32_t value = atoi(argv[1]);

		/* Update PWM channel */
		ledc_set_duty(PWM_MODE, PWM_CHANNEL, value);
		ledc_update_duty(PWM_MODE, PWM_CHANNEL);
	}
}

/* Virtual read handler */
static void vr_handler(blynk_client_t *c, uint16_t id, const char *cmd, int argc, char **argv, void *data) {
	if (!argc) {
		return;
	}

	int pin = atoi(argv[0]);

	switch (pin) {
		case VP_ADC:
		{
			/* Get ADC value */
			int value = adc1_get_voltage(ADC_CHANNEL);

			/* Respond with `virtual write' command */
			blynk_send(c, BLYNK_CMD_HARDWARE, 0, "sii", "vw", VP_ADC, value);
			break;
		}

		case VP_UPTIME:
		{
			unsigned long value = (unsigned long long)xTaskGetTickCount() * portTICK_RATE_MS / 1000;

			/* Respond with `virtual write' command */
			blynk_send(c, BLYNK_CMD_HARDWARE, 0, "siL", "vw", VP_UPTIME, value);
			break;
		}
	}
}

static void init_adc() {
	adc1_config_width(ADC_WIDTH(ADC_BITS));
	adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN);
}

static void init_pwm() {
	ledc_timer_config_t timer = {
		.bit_num = PWM_BITS,
		.freq_hz = PWM_FREQ,
		.speed_mode = PWM_MODE,
		.timer_num = PWM_TIMER,
	};
	ledc_timer_config(&timer);

	ledc_channel_config_t channel = {
		.channel = PWM_CHANNEL,
		.duty = 0,
		.gpio_num = PWM_PIN,
		.speed_mode = PWM_MODE,
		.timer_sel = PWM_TIMER,
	};

	ledc_channel_config(&channel);
}

void app_main() {
	init_adc();
	init_pwm();

    wifi_config_t wifi_cfg;
    char ssid[50] = "IMET_DSP";
    char pwd[50] = "phongcnpm413";
    bzero(&wifi_cfg, sizeof(wifi_config_t));
    memcpy(wifi_cfg.sta.ssid, ssid, strlen(ssid));
    memcpy(wifi_cfg.sta.password, pwd, strlen(pwd));
    
    esp_err_t err;
    
    ESP_LOGI(TAG, "Initializing...");

    err = nvs_flash_init();
    if (err == ESP_ERR_NVS_NO_FREE_PAGES)
    {
        ESP_ERROR_CHECK(nvs_flash_erase());
        err = nvs_flash_init();
    }
    ESP_ERROR_CHECK(err);
    wifi_init();
    wifi_sta_start(wifi_cfg, WIFI_MODE_STA);

	blynk_client_t *client = malloc(sizeof(blynk_client_t));
	blynk_init(client);

	blynk_options_t opt = {
		.token = BLYNK_TOKEN,
		.server = BLYNK_SERVER,
		/* Use default timeouts */
	};

	blynk_set_options(client, &opt);

	/* Subscribe to state changes and errors */
	blynk_set_state_handler(client, state_handler, NULL);

	/* blynk_set_handler sets hardware (BLYNK_CMD_HARDWARE) command handler */
	blynk_set_handler(client, "vw", vw_handler, NULL);
	blynk_set_handler(client, "vr", vr_handler, NULL);

	/* Start Blynk client task */
	blynk_start(client);
}