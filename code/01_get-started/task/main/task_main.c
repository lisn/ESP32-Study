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

void myTask(void *pvParam)
{
	while (1)
	{
		printf("This is my first task! I am happy.\n");
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}
void app_main(void)
{
	TaskHandle_t myTaskHandle = NULL;
	xTaskCreate(myTask, "myTask01", 1024, NULL, 1, &myTaskHandle);

	vTaskDelay(8000 / portTICK_PERIOD_MS);

	if (myTaskHandle != NULL)
	{
		printf("Successfully created myTask.\n");

		vTaskDelete(myTaskHandle);
	}
	else
	{
		printf("Failed to create myTask.\n");
	}
}
