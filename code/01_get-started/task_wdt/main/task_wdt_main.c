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
#else

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
#endif