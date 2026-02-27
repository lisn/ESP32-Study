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

#else
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
#endif