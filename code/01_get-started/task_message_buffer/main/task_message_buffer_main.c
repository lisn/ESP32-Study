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

#if 0
MessageBufferHandle_t xMessageBuffer;

void sendTask(void *pvParameters)
{
	char tx_buf[50] = {0};
	int strlen, sendlen;
	for (int i = 0; i < 3; i++)
	{
		strlen = sprintf(tx_buf, "I am sunny,now I am in shenzhou.");
		sendlen = xMessageBufferSend(xMessageBuffer, 
										tx_buf, 
										strlen, 
										portMAX_DELAY);
		printf("i = %d, str len: %d, send len: %d, send data: %s\n", i, strlen, sendlen, tx_buf);	
	}
	vTaskDelete(NULL);
}

void rcvTask(void *pvParameters)
{
	char rx_buf[100] = {0};
	int recvlen; 
	for (;;)
	{
		memset(rx_buf, 0, sizeof(rx_buf));
		recvlen = xMessageBufferReceive(xMessageBuffer, rx_buf, sizeof(rx_buf), portMAX_DELAY);
		printf("**************************************************\n");
		printf("recv len: %d, recv data: %s\n", recvlen, rx_buf);
	}
}

void app_main(void)
{
	xMessageBuffer = xMessageBufferCreate(1000);
	if (xMessageBuffer == NULL)
	{
		/* There was not enough heap memory space available to create the
		stream buffer. */
		printf("Failed to create stream buffer\n");
	}
	else
	{
		/* The stream buffer was created successfully and can now be used. */

		xTaskCreate(sendTask, "sendTask", 2048, NULL, 1, NULL);
		xTaskCreate(rcvTask, "rcvTask", 2048, NULL, 1, NULL);
	}
}
#elif 1

StreamBufferHandle_t xStreamBuffer;

void sendTask(void *pvParameters)
{
	char tx_buf[50] = {0};
	int strlen, sendlen;
	for (int i = 0; i < 3; i++)
	{
		strlen = sprintf(tx_buf, "I am sunny,now I am in shenzhou.");
		sendlen = xStreamBufferSend(xStreamBuffer,
									 tx_buf,
									 strlen,
									 portMAX_DELAY);
		printf("i = %d, str len: %d, send len: %d, send data: %s\n", i, strlen, sendlen, tx_buf);
	}
	vTaskDelete(NULL);
}

void rcvTask(void *pvParameters)
{
	char rx_buf[10] = {0};
	int recvlen;
	for (;;)
	{
		memset(rx_buf, 0, sizeof(rx_buf));
		recvlen = xStreamBufferReceive(xStreamBuffer, rx_buf, sizeof(rx_buf), portMAX_DELAY);
		printf("**************************************************\n");
		printf("recv len: %d, recv data: %s\n", recvlen, rx_buf);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void app_main(void)
{
	xStreamBuffer = xStreamBufferCreate(1000,10);
	if (xStreamBuffer == NULL)
	{
		/* There was not enough heap memory space available to create the
		stream buffer. */
		printf("Failed to create stream buffer\n");
	}
	else
	{
		/* The stream buffer was created successfully and can now be used. */

		xTaskCreate(sendTask, "sendTask", 2048, NULL, 1, NULL);
		xTaskCreate(rcvTask, "rcvTask", 2048, NULL, 1, NULL);
	}
}

#else


MessageBufferHandle_t xMessageBuffer;

void sendTask(void *pvParameters)
{
	char tx_buf[50] = {0};
	int strlen, sendlen;
	for (int i = 0; i < 3; i++)
	{
		strlen = sprintf(tx_buf, "I am sunny,now I am in shenzhou.");
		sendlen = xMessageBufferSend(xMessageBuffer,
									 tx_buf,
									 strlen,
									 portMAX_DELAY);
		printf("i = %d, str len: %d, send len: %d, send data: %s\n", i, strlen, sendlen, tx_buf);
	}
	vTaskDelete(NULL);
}

void rcvTask(void *pvParameters)
{
	char rx_buf[10] = {0};
	int recvlen;
	for (;;)
	{
		memset(rx_buf, 0, sizeof(rx_buf));
		recvlen = xMessageBufferReceive(xMessageBuffer, rx_buf, sizeof(rx_buf), portMAX_DELAY);
		printf("**************************************************\n");
		printf("recv len: %d, recv data: %s\n", recvlen, rx_buf);
		vTaskDelay(1000 / portTICK_PERIOD_MS);
	}
}

void app_main(void)
{
	xMessageBuffer = xMessageBufferCreate(1000);
	if (xMessageBuffer == NULL)
	{
		/* There was not enough heap memory space available to create the
		stream buffer. */
		printf("Failed to create stream buffer\n");
	}
	else
	{
		/* The stream buffer was created successfully and can now be used. */

		xTaskCreate(sendTask, "sendTask", 2048, NULL, 1, NULL);
		xTaskCreate(rcvTask, "rcvTask", 2048, NULL, 1, NULL);
	}
}
#endif