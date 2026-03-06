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
	uint32_t ulNotifiedValue = 0;
	for (;;)
	{
		printf("Task 1 is running\n");
		/* Block indefinitely (without a timeout, so no need to check the function's
		return value) to wait for a notification.
		Bits in this RTOS task's notification value are set by the notifying
		tasks and interrupts to indicate which events have occurred. */
		xTaskNotifyWait(0x00,			  /* Don't clear any notification bits on entry. */
						ULONG_MAX,		  /* Reset the notification value to 0 on exit. */
						&ulNotifiedValue, /* Notified value pass out in ulNotifiedValue. */
						portMAX_DELAY);	  /* Block indefinitely. */
		/* Process any events that have been latched in the notified value. */
		if ((ulNotifiedValue & 0x01) != 0)
		{
			/* Bit 0 was set - process whichever event is represented by bit 0. */
			printf("Bit0 was set in the notification value.\n");
		}
		if ((ulNotifiedValue & 0x02) != 0)
		{
			/* Bit 1 was set - process whichever event is represented by bit 1. */
			printf("Bit1 was set in the notification value.\n");
		}
		if ((ulNotifiedValue & 0x04) != 0)
		{
			/* Bit 2 was set - process whichever event is represented by bit 2. */
			printf("Bit2 was set in the notification value.\n");
		}
	}
}

void task2(void *pvParameters)
{
	printf("Task 2 is running\n");
	vTaskDelay(pdMS_TO_TICKS(2000)); /* Delay for 2 seconds. */
	for (;;)
	{
		/* Set the notification value of the task referenced by task1 to 0x01,
			even if the task had not read its previous notification value. */
		printf("Bit0 is set in the notification value in task2.\n");
		xTaskNotify(xTaskGetHandle("task1"), 0x01, eSetValueWithOverwrite);
		vTaskDelay(pdMS_TO_TICKS(3000)); /* Delay for 2 seconds. */

		printf("Bit1 is set in the notification value in task2.\n");
		xTaskNotify(xTaskGetHandle("task1"), 0x02, eSetValueWithOverwrite);
		vTaskDelay(pdMS_TO_TICKS(3000)); /* Delay for 2 seconds. */

		printf("Bit2 is set in the notification value in task2.\n");
		xTaskNotify(xTaskGetHandle("task1"), 0x04, eSetValueWithOverwrite);
		vTaskDelay(pdMS_TO_TICKS(3000)); /* Delay for 2 seconds. */
	}
}
void app_main(void)
{

	vTaskSuspendAll();

	xTaskCreate(task1, "task1", 2048, NULL, 1, NULL);
	xTaskCreate(task2, "task2", 2048, NULL, 1, NULL);

	xTaskResumeAll();
}