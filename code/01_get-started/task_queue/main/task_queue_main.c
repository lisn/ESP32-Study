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

void sndTask(void *pvParam)
{
	QueueHandle_t xQueue = (QueueHandle_t)pvParam;
	int data = 0;
	while (1)
	{
		if (xQueueSend(xQueue, &data, 0) != pdTRUE)
		{
			printf("sndTask send data failed\n");
		}
		else
		{
			printf("sndTask send data: %d\n", data);
		}

		data++;
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

void recTask(void *pvParam)
{

	QueueHandle_t xQueue = (QueueHandle_t)pvParam;

		int data;
	while (1)
	{
		if (xQueueReceive(xQueue, &data, 0) == pdTRUE)
		{
			printf("recTask rcvd data: %d\n", data);
		}
		else
		{
			printf("recTask receive data failed\n");
		}

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}
void app_main(void)
{
	QueueHandle_t xQueue;
	xQueue = xQueueCreate(10, sizeof(int));

	xTaskCreate(sndTask, "sndTask", 2048, (void *)xQueue, 1, NULL);
	xTaskCreate(recTask, "recTask", 2048, (void *)xQueue, 1, NULL);
}
#endif