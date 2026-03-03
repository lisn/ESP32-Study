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

void carInTask(void *pvParameters)
{
	UBaseType_t count;
	BaseType_t iResult;
	while (1)
	{
		count = uxSemaphoreGetCount(xSemaphore);
		printf("Semaphore count: %u\n", count);

		iResult = xSemaphoreTake(xSemaphore, 0);
		if (iResult == pdPASS)
		{
			printf("on car in.\n");
		}
		else
		{
			printf("No Space.\n");
		}

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}

void carOutTask(void *pvParameters)
{
	while (1)
	{
		vTaskDelay(6000 / portTICK_PERIOD_MS);
		xSemaphoreGive(xSemaphore);
	}
	vTaskDelete(NULL);
}

void app_main(void)
{
	xSemaphore = xSemaphoreCreateCounting(5, 5);

	xTaskCreate(carInTask, "carInTask", 2048, NULL, 5, NULL);
	xTaskCreate(carOutTask, "carOutTask", 2048, NULL, 5, NULL);
}