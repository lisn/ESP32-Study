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

/* Bits used by the three tasks. */
#define TASK_0_BIT (1 << 0)
#define TASK_1_BIT (1 << 1)
#define TASK_2_BIT (1 << 2)
#define ALL_SYNC_BITS (TASK_0_BIT | TASK_1_BIT | TASK_2_BIT)
/* Use an event group to synchronize three tasks. It is assumed this event
group has already been created elsewhere. */
EventGroupHandle_t xEventBits;

void task1(void *pvParameters)
{
	EventBits_t uxReturn;
	for (;;)
	{
		/* Perform task functionality here. */
			printf("task1 is running\n");
			 vTaskDelay(1000 / portTICK_PERIOD_MS);
			/* Set bit 0 in the event group to note this task has reached the
			sync point. The other two tasks will set the other two bits defined
			by ALL_SYNC_BITS. All three tasks have reached the synchronization
			point when all the ALL_SYNC_BITS bits are set. Wait a maximum of 100ms
			for this to happen. */
			printf("task1 set bit0\n");
			uxReturn = xEventGroupSync(xEventBits,
									   TASK_0_BIT,	  /* The bit to set. */
									   ALL_SYNC_BITS, /* The bits to wait for. */
									   portMAX_DELAY); /* Timeout value. */
		if ((uxReturn & ALL_SYNC_BITS) == ALL_SYNC_BITS)
		{
			/* All three tasks reached the synchronization point before the call
			to xEventGroupSync() timed out. */
			printf("task1 is running after sync\n");
			 vTaskDelay(10000 / portTICK_PERIOD_MS);
		}
	}
}

void task2(void *pvParameters)
{
	EventBits_t uxReturn;
	for (;;)
	{
		/* Perform task functionality here. */
			printf("task2 is running\n");
			 vTaskDelay(3000 / portTICK_PERIOD_MS);
			/* Set bit 0 in the event group to note this task has reached the
			sync point. The other two tasks will set the other two bits defined
			by ALL_SYNC_BITS. All three tasks have reached the synchronization
			point when all the ALL_SYNC_BITS bits are set. Wait a maximum of 100ms
			for this to happen. */
			printf("task2 set bit1\n");
			uxReturn = xEventGroupSync(xEventBits,
									   TASK_1_BIT,	  /* The bit to set. */
									   ALL_SYNC_BITS, /* The bits to wait for. */
									   portMAX_DELAY); /* Timeout value. */
		if ((uxReturn & ALL_SYNC_BITS) == ALL_SYNC_BITS)
		{
			/* All three tasks reached the synchronization point before the call
			to xEventGroupSync() timed out. */
			printf("task2 is running after sync\n");
			 vTaskDelay(10000 / portTICK_PERIOD_MS);
		}
	}
}


void task3(void *pvParameters)
{
	EventBits_t uxReturn;
	for (;;)
	{
		/* Perform task functionality here. */
			printf("task3 is running\n");
			 vTaskDelay(5000 / portTICK_PERIOD_MS);
			/* Set bit 0 in the event group to note this task has reached the
			sync point. The other two tasks will set the other two bits defined
			by ALL_SYNC_BITS. All three tasks have reached the synchronization
			point when all the ALL_SYNC_BITS bits are set. Wait a maximum of 100ms
			for this to happen. */
			printf("task3 set bit2\n");
			uxReturn = xEventGroupSync(xEventBits,
									   TASK_2_BIT,	  /* The bit to set. */
									   ALL_SYNC_BITS, /* The bits to wait for. */
									   portMAX_DELAY); /* Timeout value. */
		if ((uxReturn & ALL_SYNC_BITS) == ALL_SYNC_BITS)
		{
			/* All three tasks reached the synchronization point before the call
			to xEventGroupSync() timed out. */
			printf("task3 is running after sync\n");
			 vTaskDelay(10000 / portTICK_PERIOD_MS);
		}
	}
}

void app_main(void)
{
	xEventBits = xEventGroupCreate();

	vTaskSuspendAll();

	xTaskCreate(task1, "task1", 2048, NULL, 1, NULL);
	xTaskCreate(task2, "task2", 2048, NULL, 1, NULL);
	xTaskCreate(task3, "task3", 2048, NULL, 1, NULL);

	xTaskResumeAll();
}