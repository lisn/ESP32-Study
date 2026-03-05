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

#define BIT_0 ( 1 << 0 )
#define BIT_4 ( 1 << 4 )

EventGroupHandle_t xEventGroup;

void task1(void *pvParameters)
{
	while (1)
	{
		printf("task1 start\n");
		EventBits_t uxBits;
		// const TickType_t xTicksToWait = pdMS_TO_TICKS(100);
		/* Wait a maximum of 100ms for either bit 0 or bit 4 to be set within
		the event group. Clear the bits before exiting. */
		uxBits = xEventGroupWaitBits(
			xEventGroup,   /* The event group being tested. */
			BIT_0 | BIT_4, /* The bits within the event group to wait for. */
			pdTRUE,		   /* BIT_0 and BIT_4 should be cleared before returning. */
			pdFALSE,	   /* Don't wait for both bits, either bit will do. */
			// xTicksToWait); /* Wait a maximum of 100ms for either bit to be set. */
			portMAX_DELAY); /* Wait indefinitely for either bit to be set. */
		if ((uxBits & (BIT_0 | BIT_4)) == (BIT_0 | BIT_4))
		{
			/* xEventGroupWaitBits() returned because both bits were set. */
			printf("task1 Bit0 and Bit4 are set\n");
		}
		else if ((uxBits & BIT_0) != 0)
		{
			/* xEventGroupWaitBits() returned because just BIT_0 was set. */
			printf("task1 Bit0 is set\n");
		}
		else if ((uxBits & BIT_4) != 0)
		{
			/* xEventGroupWaitBits() returned because just BIT_4 was set. */
			printf("task1 Bit4 is set\n");
		}
		else
		{
			/* xEventGroupWaitBits() returned because xTicksToWait ticks passed
			without either BIT_0 or BIT_4 becoming set. */
			printf("task1 No bits are set\n");
		}

		vTaskDelay(pdMS_TO_TICKS(1000));
	}
}

void task2(void *pvParameters)
{
	while (1)
	{
		printf("task2 start\n");
		xEventGroupSetBits(xEventGroup, BIT_0);
		printf("task2 set Bit0\n");
		vTaskDelay(3000 / portTICK_PERIOD_MS);
		xEventGroupSetBits(xEventGroup, BIT_4);
		printf("task2 set Bit4\n");
		vTaskDelay(3000 / portTICK_PERIOD_MS);
	}
}

void app_main(void)
{
	xEventGroup = xEventGroupCreate();

	vTaskSuspendAll();

	xTaskCreate(task1, "task1", 2048, NULL, 1, NULL);
	xTaskCreate(task2, "task2", 2048, NULL, 1, NULL);

	xTaskResumeAll();
}