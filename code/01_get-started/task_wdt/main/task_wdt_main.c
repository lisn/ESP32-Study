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
#include "esp_task_wdt.h"
#include "esp_log.h" 

#if 0

void myTask1(void *pvParam)
{

	while (1)
	{
		// printf("Task 1 is running\n");
		// vTaskDelay(1000 / portTICK_PERIOD_MS);
		;
	}

	vTaskDelete(NULL);
}

void app_main(void)
{
	TaskHandle_t pxTask1 = NULL;
	xTaskCreate(myTask1, "myTask01", 512, NULL, 1, &pxTask1);
	
	UBaseType_t iStack = uxTaskGetStackHighWaterMark(pxTask1);
	while (1)
	{
		printf("Stack High Water Mark for Task 1: %d\n", iStack);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	
}
#elif 0

void myTask1(void *pvParam)
{

	while (1)
	{
		// printf("Task 1 is running\n");
		//vTaskDelay(1000 / portTICK_PERIOD_MS);
		;
	}

	vTaskDelete(NULL);
}

void app_main(void)
{
	TaskHandle_t pxTask1 = NULL;
	xTaskCreate(myTask1, "myTask01", 512, NULL, 0, &pxTask1);
	
	UBaseType_t iStack = uxTaskGetStackHighWaterMark(pxTask1);
	while (1)
	{
		printf("Stack High Water Mark for Task 1: %d\n", iStack);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	
}
#else

static const char *TAG = "WDT_TEST";
void myTask1(void *pvParam)
{
	esp_err_t ret = esp_task_wdt_add(NULL);
    if (ret == ESP_OK) {
         ESP_LOGI(TAG, "任务已添加到 WDT 监控");  // 现在可以正常使用了
    } else {
        ESP_LOGE(TAG, "添加到 WDT 失败，错误码: %d", ret);
        vTaskDelete(NULL);
        return;
    }

	while (1)
	{
		printf("Task 1 is running\n");
		vTaskDelay(1000 / portTICK_PERIOD_MS);
		esp_task_wdt_reset();
	}

	vTaskDelete(NULL);
}

void app_main(void)
{
	xTaskCreate(myTask1, "myTask01", 2048, NULL, 1, NULL);
	
}
#endif