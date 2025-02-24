// #include "cmsis_os.h"
#include "stm32f7xx_hal.h"

#include <string.h>

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "FreeRTOS.h"
#include "semphr.h"

/* USER CODE BEGIN 0 */

// this is thread safe impllementation of printf and scanf ussing UART3.
// this is works only if using with freeRTOS and UART3. 
// you need to call print_init() before using printf and scanf.

// replace your uart handle with your uart handle.
extern UART_HandleTypeDef huart3;

// this is the mutex for print_init and print_deinit.
static SemaphoreHandle_t xPrintMutex = NULL;

void print_init(void) {
    xPrintMutex = xSemaphoreCreateMutex();
}

void print_deinit(void) {
    if (xPrintMutex != NULL) {
        vSemaphoreDelete(xPrintMutex);
        xPrintMutex = NULL;
    }
}

void print_error(const char * msg)
{
    printf("%s\n", msg);
    for(;;);
}

int __io_putchar(int ch)
{
    if (xPrintMutex != NULL) {
        xSemaphoreTake(xPrintMutex, portMAX_DELAY);
        HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, 0xFFFF);
        xSemaphoreGive(xPrintMutex);
    }
    return ch;
}

int _write(int file, char *ptr, int len)
{
    if (xPrintMutex != NULL) {
        xSemaphoreTake(xPrintMutex, portMAX_DELAY);
        HAL_UART_Transmit(&huart3, (uint8_t *)ptr, len, 0xFFFF);
        xSemaphoreGive(xPrintMutex);
    }
    return len;
}
// for scanf
int _read(int file, char *ptr, int len)
{
    int ch = 0;

    if (xPrintMutex != NULL)
    {
        xSemaphoreTake(xPrintMutex, portMAX_DELAY);

        HAL_UART_Receive(&huart3, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
        HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, HAL_MAX_DELAY);

        if (ch == 13)
        {
            ch = 10;
            HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
        }
        else if (ch == 8)
        {
            ch = 0x30;
            HAL_UART_Transmit(&huart3, (uint8_t *)&ch, 1, HAL_MAX_DELAY);
        }

        xSemaphoreGive(xPrintMutex);
    }

    *ptr = ch;
    return 1;
}
