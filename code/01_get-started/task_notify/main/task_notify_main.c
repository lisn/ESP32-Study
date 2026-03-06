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

void task1(void *pvParameters)
{
	uint32_t iCount = 0;
	for (;;)
	{
		printf("Task 1 is running\n");
		vTaskDelay(pdMS_TO_TICKS(1000)); /* Delay for 1 second. */
		iCount = ulTaskNotifyTake(pdTRUE,		 /* Clear the notification value on exit. */
						 portMAX_DELAY); /* Block indefinitely. */
		printf("Task 1 received notification: %" PRIu32 "\n", iCount);
	}
}

void task2(void *pvParameters)
{
	vTaskDelay(pdMS_TO_TICKS(2000)); /* Delay for 2 seconds. */
	for (;;)
	{
		printf("Task 2 is running\n");
		vTaskDelay(pdMS_TO_TICKS(2000)); /* Delay for 2 seconds. */
		xTaskNotifyGive(xTaskGetHandle("task1")); /* Send notification to task1. */
		printf("Task 2 sent notification to Task 1\n");
	}
}
void app_main(void)
{

	vTaskSuspendAll();

	xTaskCreate(task1, "task1", 2048, NULL, 1, NULL);
	xTaskCreate(task2, "task2", 2048, NULL, 1, NULL);

	xTaskResumeAll();
}