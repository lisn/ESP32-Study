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

SemaphoreHandle_t xMutexHandle;
#if 0
void task1(void *pvParameters)
{
	printf("task1 start\n");

	BaseType_t iRet;
	while (1) {
		iRet = xSemaphoreTake(xMutexHandle, portMAX_DELAY);
		if (iRet == pdPASS) {
			printf("task1 get the mutex\n");
			for(int i = 0; i < 20; i++) {
				printf("task1 is running, count = %d\n", i);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
			}
			xSemaphoreGive(xMutexHandle);
		}
		else {
			printf("task1 take the mutex failed\n");
		}

		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void task2(void *pvParameters)
{
	printf("task2 start\n");
	vTaskDelay(1000 / portTICK_PERIOD_MS);
	while (1) {
		;
	}
}

void task3(void *pvParameters)
{
	printf("task3 start\n");
	vTaskDelay(1000 / portTICK_PERIOD_MS);
	BaseType_t iRet;
	while (1) {

		iRet = xSemaphoreTake(xMutexHandle, portMAX_DELAY);
		if (iRet == pdPASS) {
			printf("task3 get the mutex\n");
			for(int i = 0; i < 10; i++) {
				printf("task3 is running, count = %d\n", i);
				vTaskDelay(1000 / portTICK_PERIOD_MS);
			}
			xSemaphoreGive(xMutexHandle);
		}
		else {
			printf("task3 take the mutex failed\n");
		}
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void app_main(void)
{
	// xMutexHandle = xSemaphoreCreateBinary();
	xMutexHandle = xSemaphoreCreateMutex();

	vTaskSuspendAll();

	xTaskCreate(task1, "task1", 2048, NULL, 1, NULL);
	xTaskCreate(task2, "task2", 2048, NULL, 2, NULL);
	xTaskCreate(task3, "task3", 2048, NULL, 3, NULL);

	xTaskResumeAll();
}
#else

void task1(void *pvParameters)
{
	while (1)
	{
		printf("task1 start\n");

		xSemaphoreTakeRecursive(xMutexHandle, portMAX_DELAY);
		printf("task1 get the mutex A\n");
		for (int i = 0; i < 10; i++)
		{
			printf("task1 A is running, count = %d\n", i);
			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}
		
		xSemaphoreTakeRecursive(xMutexHandle, portMAX_DELAY);
		printf("task1 get the mutex B\n");
		for (int i = 0; i < 10; i++)
		{
			printf("task1 B is running, count = %d\n", i);
			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}

		printf("task1 give the mutex B\n");
		xSemaphoreGiveRecursive(xMutexHandle);
		vTaskDelay(3000 / portTICK_PERIOD_MS);

		printf("task1 give the mutex A\n");
		xSemaphoreGiveRecursive(xMutexHandle);
		vTaskDelay(3000 / portTICK_PERIOD_MS);
	}
}

void task2(void *pvParameters)
{
	while (1)
	{
		printf("task2 start\n");
		vTaskDelay(1000 / portTICK_PERIOD_MS);

		xSemaphoreTakeRecursive(xMutexHandle, portMAX_DELAY);
		printf("task2 get the mutex\n");
		for (int i = 0; i < 10; i++)
		{
			printf("task2 is running, count = %d\n", i);
			vTaskDelay(1000 / portTICK_PERIOD_MS);
		}

		printf("task2 give the mutex\n");
		xSemaphoreGiveRecursive(xMutexHandle);
		vTaskDelay(3000 / portTICK_PERIOD_MS);
	}
}

void app_main(void)
{
	xMutexHandle = xSemaphoreCreateRecursiveMutex();

	vTaskSuspendAll();

	xTaskCreate(task1, "task1", 2048, NULL, 1, NULL);
	xTaskCreate(task2, "task2", 2048, NULL, 1, NULL);

	xTaskResumeAll();
}
#endif