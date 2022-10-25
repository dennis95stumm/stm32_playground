/**
 ******************************************************************************
 * @file 01_printf.c
 * @author dstumm
 * @date 2022
 * @version 1.0
 * @brief
 ******************************************************************************
 */

#if defined PROGRAM_01

#include <01_printf.h>
#include <rcc.h>
#include <uart.h>
#include <stdio.h>
#include <stdint.h>

int _write(int file, char *ptr, int len) {
  UART_Transmit((uint8_t*) &ptr[0], len, TIMEOUT);

  return len;
}

void configure() {
  RCC_ConfigureClocks();
  RCC_ConfigureSysTick();
  UART_Configure();

  printf("Test\n");
}

void run() {
  printf("Test %lu \n", RCC_GetSysTick());
  RCC_Delay(DELAY_MS);
}

#endif /* PROGRAM_01 */
