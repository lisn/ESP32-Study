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

#if 1

void myTask1(void *pvParam)
{

	while (1)
	{
		printf("Task 1 is running\n");
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

void myTask2(void *pvParam)
{

	while (1)
	{
		printf("Task 2 is running\n");
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

void app_main(void)
{
	TaskHandle_t pxTask1 = NULL;
	
	xTaskCreate(myTask1, "myTask01", 2048, NULL, 1, &pxTask1);
	xTaskCreate(myTask2, "myTask02", 2048, NULL, 2, NULL);
	// Suspend task 1 for 5 seconds, then resume it , if pxTask1 is NULL, the function will suspend current task.
	vTaskSuspend(pxTask1);

	vTaskDelay(5000 / portTICK_PERIOD_MS);

	vTaskResume(pxTask1);

}
#else

#endif