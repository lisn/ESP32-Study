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

static const char *sTask = "I am a task.";

void myTask(void *pvParam)
{
	char *ptask = (char *)pvParam;

	if (ptask == NULL)
	{
		printf("Invalid parameter");
		vTaskDelete(NULL);
		return;
	}

	while (1)
	{
		printf("Got message : %s\n", ptask);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

void app_main(void)
{
	TaskHandle_t pxTask = NULL;
	//components\freertos\config\include\freertos\FreeRTOSConfig.h 
	xTaskCreate(myTask, "myTask01", 2048, (void *)sTask, 24, &pxTask);
	UBaseType_t iPriority = uxTaskPriorityGet(pxTask);

	printf("Priority of myTask01 is %d\n", iPriority);
}
#else

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
	// priority 0 is the lowest, and priority configMAX_PRIORITIES - 1 is the highest. The default configMAX_PRIORITIES is 25, so the valid priority range is 0
	xTaskCreate(myTask1, "myTask01", 2048, NULL, 1, NULL);
	xTaskCreate(myTask2, "myTask02", 2048, NULL, 1, NULL);
}
#endif