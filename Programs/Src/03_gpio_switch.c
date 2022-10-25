/**
 ******************************************************************************
 * @file 03_gpio_switch.c
 * @author Dennis Stumm
 * @date 2022
 * @version 1.0
 * @brief
 ******************************************************************************
 */
#if defined PROGRAM_03

#include <03_gpio_switch.h>
#include <rcc.h>
#include <gpio.h>

void configure() {
  RCC_ConfigureClocks();
  RCC_ConfigureSysTick();
  GPIO_ConfigureLeds();
  GPIO_ConfigureSwitches();

  GPIO_WriteGreenLed(REGISTER_STATE_RESET);
  GPIO_WriteRedLed(REGISTER_STATE_RESET);
}

void run() {
  GPIO_WriteGreenLed(GPIO_ReadSwitch1State());
  GPIO_WriteRedLed(GPIO_ReadSwitch2State());
  RCC_Delay(DELAY_MS);
}

#endif /* PROGRAM_02 */
