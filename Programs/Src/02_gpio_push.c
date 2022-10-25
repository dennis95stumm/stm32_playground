/**
 ******************************************************************************
 * @file 02_gpio_push.c
 * @author Dennis Stumm
 * @date 2022
 * @version 1.0
 * @brief
 ******************************************************************************
 */
#if defined PROGRAM_02

#include <rcc.h>
#include <gpio.h>

void configure() {
  RCC_ConfigureClocks();
  RCC_ConfigureSysTick();
  GPIO_ConfigureLeds();
  GPIO_ConfigurePushButton();

  GPIO_WriteGreenLed(REGISTER_STATE_RESET);
  GPIO_WriteRedLed(REGISTER_STATE_RESET);
}

void run() {
  GPIO_WriteGreenLed(GPIO_ReadPushButtonState());
  GPIO_WriteRedLed(GPIO_ReadPushButtonState());
}

#endif /* PROGRAM_02 */
