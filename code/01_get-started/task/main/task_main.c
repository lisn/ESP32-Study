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

#if 0
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
#elif 0
void myTask(void *pvParam)
{

	printf("This is my first task! I am happy.\n");
	vTaskDelay(1000 / portTICK_PERIOD_MS);
	vTaskDelete(NULL);
}
void app_main(void)
{

	xTaskCreate(myTask, "myTask01", 1024, NULL, 1, NULL);
}

#elif 0
void myTask(void *pvParam)
{
	int *pInt = (int *)pvParam;

	if (pInt == NULL)
	{
		printf("Invalid parameter");
		vTaskDelete(NULL);
		return;
	}

	while (1)
	{
		printf("Got a num = %d\n", *pInt);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	vTaskDelete(NULL);
}
int testNum = 9;
void app_main(void)
{

	xTaskCreate(myTask, "myTask01", 2048, (void *)&testNum, 1, NULL);
}
#elif 0
void myTask(void *pvParam)
{
	int *pInt = (int *)pvParam;

	if (pInt == NULL)
	{
		printf("Invalid parameter");
		vTaskDelete(NULL);
		return;
	}

	while (1)
	{
		// 	printf("Got first num = %d\n",*pInt);
		// 	printf("Got second num = %d\n",*(pInt + 1));
		// 	printf("Got third num = %d\n",*(pInt + 2));
		pInt = (int *)pvParam;
		printf("Got first num = %d\n", *pInt++);
		printf("Got second num = %d\n", *pInt++);
		printf("Got third num = %d\n", *pInt);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	
	vTaskDelete(NULL);
}
int testArray[] = {7, 8, 9};
void app_main(void)
{

	xTaskCreate(myTask, "myTask01", 2048, (void *)testArray, 1, NULL);
}
#elif 0
typedef struct A_STUDENT
{
	int age;
	int score;
} xStudent;

void myTask(void *pvParam)
{
	xStudent *pStudent = (xStudent *)pvParam;

	if (pStudent == NULL)
	{
		printf("Invalid parameter");
		vTaskDelete(NULL);
		return;
	}

	while (1)
	{
		printf("age = %d, score = %d\n",pStudent->age, pStudent->score);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	
	vTaskDelete(NULL);
}
xStudent xStudent_A = {36, 100};
void app_main(void)
{

	xTaskCreate(myTask, "myTask01", 2048, (void *)&xStudent_A, 1, NULL);
}
#else
static const char *sTask = "I am a task.";

void myTask(void *pvParam)
{
	char *ptask = (char *)pvParam;

	if (ptask == NULL)
	{
		printf("Invalid parameter");
		vTaskDelete(NULL);
		return;
	}

	while (1)
	{
		printf("Got message : %s\n",ptask);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
	
	vTaskDelete(NULL);
}

void app_main(void)
{

	xTaskCreate(myTask, "myTask01", 2048, (void *)sTask, 1, NULL);
}
#endif