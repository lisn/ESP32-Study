/*
 * SPDX-FileCopyrightText: 2010-2022 Espressif Systems (Shanghai) CO LTD
 *
 * SPDX-License-Identifier: CC0-1.0
 */

#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"
#include "esp_log.h"

void timer_callback(TimerHandle_t xTimer){
		static uint32_t count = 0;
		const char *timer_name = pcTimerGetName(xTimer);
		uint32_t timer_id = (uint32_t)pvTimerGetTimerID(xTimer);
		ESP_LOGI("TIMER", "Timer callback called, count: %" PRIu32 ", name: %s, id: %" PRIu32, ++count, timer_name, timer_id);
}

void app_main(void)
{
	// 1000 / PortTICK_PERIOD_MS means the timer will trigger every 1000 milliseconds (1 second)
	// 1000 / PortTICK_PERIOD_MS = pdMS_TO_TICKS(1000) = 1000 / (1000 / configTICK_RATE_HZ) = configTICK_RATE_HZ
	TimerHandle_t xTimer1 = xTimerCreate("Timer1",1000 / portTICK_PERIOD_MS, pdTRUE, (void *)255, timer_callback);
	TimerHandle_t xTimer2 = xTimerCreate("Timer2",pdMS_TO_TICKS(1000), pdTRUE, (void *)266, timer_callback);

	xTimerStart(xTimer1,0);
	xTimerStart(xTimer2,0);

}