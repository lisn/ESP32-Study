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

#if 0

#else

void sndTask1(void *pvParam)
{
	QueueHandle_t xQueue = (QueueHandle_t)pvParam;

	int i = 111;
	while (1)
	{
		if (xQueueSend(xQueue, &i, 0) != pdTRUE)
		{
			printf("sndTask send data failed\n");
		}
		else
		{
			printf("sndTask send data: %d\n", i);
		}

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

void sndTask2(void *pvParam)
{
	QueueHandle_t xQueue = (QueueHandle_t)pvParam;

	int i = 222;
	while (1)
	{
		if (xQueueSend(xQueue, &i, 0) != pdTRUE)
		{
			printf("sndTask send data failed\n");
		}
		else
		{
			printf("sndTask send data: %d\n", i);
		}

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

void sndTask3(void *pvParam)
{
	QueueHandle_t xQueue = (QueueHandle_t)pvParam;

	int i = 333;
	while (1)
	{
		if (xQueueSend(xQueue, &i, 0) != pdTRUE)
		{
			printf("sndTask send data failed\n");
		}
		else
		{
			printf("sndTask send data: %d\n", i);
		}

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}


void recTask(void *pvParam)
{

	QueueHandle_t xQueue = (QueueHandle_t)pvParam;
	int i;
	while (1)
	{
			// if no data in queue, wait until data is sent to queue
			if (xQueueReceive(xQueue, &i, portMAX_DELAY) == pdTRUE)
			{
				printf("recTask rcvd data: %d\n", i);
				
			}
			else
			{
				printf("recTask receive data failed\n");
			}
		
	}

	vTaskDelete(NULL);
}
void app_main(void)
{
	QueueHandle_t xQueue;
	xQueue = xQueueCreate(10, sizeof(int));

	xTaskCreate(sndTask1, "sndTask1", 2048, (void *)xQueue, 1, NULL);
	xTaskCreate(sndTask2, "sndTask2", 2048, (void *)xQueue, 1, NULL);
	xTaskCreate(sndTask3, "sndTask3", 2048, (void *)xQueue, 1, NULL);

	xTaskCreate(recTask, "recTask", 2048, (void *)xQueue, 2, NULL);
}
#endif