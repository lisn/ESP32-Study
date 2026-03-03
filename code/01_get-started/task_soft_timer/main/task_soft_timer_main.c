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
		ESP_LOGI("TIMER", "Timer callback called, count: %" PRIu32, ++count);
}

void app_main(void)
{
	TimerHandle_t xTimer = xTimerCreate("Timer1",1000 / portTICK_PERIOD_MS, pdTRUE, (void *)0, timer_callback);

	xTimerStart(xTimer,0);

}