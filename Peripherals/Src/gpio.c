/**
 ******************************************************************************
 * @file gpio.c
 * @author Dennis Stumm
 * @date 2022
 * @version 1.0
 * @brief Functions for the GPIO devices.
 ******************************************************************************
 */

#include <register.h>
#include <stm32f103xb.h>

/* Leds */
void GPIO_ConfigureLeds(void) {
  /* Enable Port B clock. */
  REGISTER_Set(&RCC->APB2ENR, RCC_APB2ENR_IOPBEN);

  /* Configure PB13 and PB14 to output mode 2 MHz. */
  REGISTER_Reset(&GPIOB->CRH, (GPIO_CRH_MODE13_Msk | GPIO_CRH_MODE14_Msk));
  REGISTER_Set(&GPIOB->CRH, (GPIO_CRH_MODE13_1 | GPIO_CRH_MODE14_1));

  /* Configure PB13 and PB14 to push pull. */
  REGISTER_Reset(&GPIOB->CRH, (GPIO_CRH_CNF13_Msk | GPIO_CRH_CNF14_Msk));
}

void GPIO_WriteGreenLed(state_t state) {
  REGISTER_WriteState(&GPIOB->ODR, GPIO_ODR_ODR13, state);
}

void GPIO_WriteRedLed(state_t state) {
  REGISTER_WriteState(&GPIOB->ODR, GPIO_ODR_ODR14, state);
}

void GPIO_ToggleGreenLed(void) {
  REGISTER_ToggleState(&GPIOB->ODR, GPIO_ODR_ODR13);
}

void GPIO_ToggleRedLed(void) {
  REGISTER_ToggleState(&GPIOB->ODR, GPIO_ODR_ODR14);
}

/* Push buttons */

void GPIO_ConfigurePushButton(void) {
  /* Enable Port A clock. */
  REGISTER_Set(&RCC->APB2ENR, RCC_APB2ENR_IOPAEN);

  /* Configure PA0 to input mode. */
  REGISTER_Reset(&GPIOA->CRL, GPIO_CRL_MODE0_Msk);

  /* Configure PA0 to floating input. */
  REGISTER_Reset(&GPIOA->CRL, GPIO_CRL_CNF0_Msk);
  REGISTER_Set(&GPIOA->CRL, GPIO_CRL_CNF0_0);
}

state_t GPIO_ReadPushButtonState(void) {
  return (state_t) REGISTER_IsSet(&GPIOA->IDR, GPIO_IDR_IDR0);
}

/* Switches */

void GPIO_ConfigureSwitches(void) {
  /* Enable Port A clock. */
  REGISTER_Set(&RCC->APB2ENR, RCC_APB2ENR_IOPAEN);

  /* Configure PA8 and PA15 to input mode. */
  REGISTER_Reset(&GPIOA->CRH, (GPIO_CRH_MODE8_Msk | GPIO_CRH_MODE15_Msk));

  /* Configure PA8 and PA15 to floating input. */
  REGISTER_Reset(&GPIOA->CRH, (GPIO_CRH_CNF8_Msk | GPIO_CRH_CNF15_Msk));
  REGISTER_Set(&GPIOA->CRH, (GPIO_CRH_CNF8_0 | GPIO_CRH_CNF15_0));

  /* Remap PA15. */
  REGISTER_Set(&RCC->APB2ENR, RCC_APB2ENR_AFIOEN);
  REGISTER_Set(&RCC->APB1ENR, RCC_APB1ENR_PWREN);
  REGISTER_Reset(&AFIO->MAPR, AFIO_MAPR_SWJ_CFG_Msk);
  REGISTER_Set(&AFIO->MAPR, AFIO_MAPR_SWJ_CFG_JTAGDISABLE);
}

state_t GPIO_ReadSwitch1State(void) {
  return (state_t) REGISTER_IsSet(&GPIOA->IDR, GPIO_IDR_IDR8);
}

state_t GPIO_ReadSwitch2State(void) {
  return (state_t) REGISTER_IsSet(&GPIOA->IDR, GPIO_IDR_IDR15);
}
