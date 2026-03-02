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

void writeTask(void *pvParam)
{
	QueueHandle_t xMailBox = (QueueHandle_t)pvParam;

	int i = 0;
	while (1)
	{
		if (xQueueOverwrite(xMailBox, &i) != pdTRUE)
		{
			printf("writeTask send data failed\n");
		}
		else
		{
			printf("writeTask send data: %d\n", i);
		}

		i++;

		vTaskDelay(3000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

void readTask1(void *pvParam)
{

	QueueHandle_t xMailbox = (QueueHandle_t)pvParam;
	int i;

	while (1)
	{

		if (xQueuePeek(xMailbox, &i, portMAX_DELAY) == pdTRUE)
		{
			printf("readTask1 rcvd data: %d\n", i);
		}
		else
		{
			printf("readTask1 receive data failed\n");
		}
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

void readTask2(void *pvParam)
{

	QueueHandle_t xMailbox = (QueueHandle_t)pvParam;
	int i;

	while (1)
	{

		if (xQueuePeek(xMailbox, &i, portMAX_DELAY) == pdTRUE)
		{
			printf("readTask2 rcvd data: %d\n", i);
		}
		else
		{
			printf("readTask2 receive data failed\n");
		}
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

void readTask3(void *pvParam)
{

	QueueHandle_t xMailbox = (QueueHandle_t)pvParam;
	int i;

	while (1)
	{

		if (xQueuePeek(xMailbox, &i, portMAX_DELAY) == pdTRUE)
		{
			printf("readTask3 rcvd data: %d\n", i);
		}
		else
		{
			printf("readTask3 receive data failed\n");
		}
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}

	vTaskDelete(NULL);
}

void app_main(void)
{
	QueueHandle_t xMailbox;
	xMailbox = xQueueCreate(1, sizeof(int));

	xTaskCreate(writeTask, "writeTask", 2048, (void *)xMailbox, 1, NULL);

	xTaskCreate(readTask1, "readTask1", 2048, (void *)xMailbox, 2, NULL);
	xTaskCreate(readTask2, "readTask2", 2048, (void *)xMailbox, 2, NULL);
	xTaskCreate(readTask3, "readTask3", 2048, (void *)xMailbox, 2, NULL);
}