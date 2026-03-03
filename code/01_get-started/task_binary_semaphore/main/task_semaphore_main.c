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

SemaphoreHandle_t xSemaphore;
unsigned int iCount = 0;

void myTask1(void *pvParameters)
{
	while (1)
	{
		if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
		{
			for (int i = 0; i < 3; i++)
			{

				iCount++;
				printf("mytask1: iCount = %u\n", iCount);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
			}
		}
		xSemaphoreGive(xSemaphore);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}

void myTask2(void *pvParameters)
{
	while (1)
	{
		if (xSemaphoreTake(xSemaphore, portMAX_DELAY) == pdTRUE)
		{
			for (int i = 0; i < 3; i++)
			{
				iCount++;
				printf("mytask2: iCount = %u\n", iCount);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
			}
		}
		xSemaphoreGive(xSemaphore);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}

void app_main(void)
{
	xSemaphore = xSemaphoreCreateBinary();
	xSemaphoreGive(xSemaphore);

	xTaskCreate(myTask1, "myTask1", 2048, NULL, 5, NULL);
	xTaskCreate(myTask2, "myTask2", 2048, NULL,	5, NULL);
}