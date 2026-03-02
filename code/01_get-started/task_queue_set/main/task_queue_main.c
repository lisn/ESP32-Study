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

void recTask(void *pvParam)
{

	QueueSetHandle_t xQueueSet = (QueueSetHandle_t)pvParam;
	int i;

	while (1)
	{
		QueueSetMemberHandle_t xQueueMember = xQueueSelectFromSet(xQueueSet, portMAX_DELAY);

		if (xQueueReceive(xQueueMember, &i, portMAX_DELAY) == pdTRUE)
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
	QueueHandle_t xQueue1;
	xQueue1 = xQueueCreate(10, sizeof(int));

	QueueHandle_t xQueue2;
	xQueue2 = xQueueCreate(10, sizeof(int));

	QueueSetHandle_t xQueueSet1;

	xQueueSet1 = xQueueCreateSet(20);
	xQueueAddToSet(xQueue1, xQueueSet1);
	xQueueAddToSet(xQueue2, xQueueSet1);

	xTaskCreate(sndTask1, "sndTask1", 2048, (void *)xQueue1, 1, NULL);
	xTaskCreate(sndTask2, "sndTask2", 2048, (void *)xQueue2, 1, NULL);

	xTaskCreate(recTask, "recTask", 2048, (void *)xQueueSet1, 2, NULL);
}
#endif