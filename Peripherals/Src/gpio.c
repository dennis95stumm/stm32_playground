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
  REGISTER_WriteState(RCC->APB2ENR, RCC_APB2ENR_IOPBEN, REGISTER_STATE_SET);

  /* Configure PB13 and PB14 to output mode 2 MHz. */
  REGISTER_WriteState(GPIOB->CRH,
    (GPIO_CRH_MODE13_Msk | GPIO_CRH_MODE14_Msk),
    REGISTER_STATE_RESET);
  REGISTER_WriteState(GPIOB->CRH,
    (GPIO_CRH_MODE13_1 | GPIO_CRH_MODE14_1),
    REGISTER_STATE_SET);

  /* Configure PB13 and PB14 to push pull. */
  REGISTER_WriteState(GPIOB->CRH,
    (GPIO_CRH_CNF13_Msk | GPIO_CRH_CNF14_Msk),
    REGISTER_STATE_RESET);
}

void GPIO_WriteGreenLed(state_t state) {
  REGISTER_WriteState(GPIOB->ODR, GPIO_ODR_ODR13, state);
}

void GPIO_WriteRedLed(state_t state) {
  REGISTER_WriteState(GPIOB->ODR, GPIO_ODR_ODR14, state);
}

void GPIO_ToggleGreenLed(void) {
  REGISTER_ToggleState(GPIOB->ODR, GPIO_ODR_ODR13);
}

void GPIO_ToggleRedLed(void) {
  REGISTER_ToggleState(GPIOB->ODR, GPIO_ODR_ODR14);
}

/* Push buttons */

void GPIO_ConfigurePushButton(void) {
  /* Enable Port A clock. */
  REGISTER_WriteState(RCC->APB2ENR, RCC_APB2ENR_IOPAEN, REGISTER_STATE_SET);

  /* Configure PA0 to input mode. */
  REGISTER_WriteState(GPIOA->CRL, GPIO_CRL_MODE0_Msk, REGISTER_STATE_RESET);

  /* Configure PA0 to floating input. */
  REGISTER_WriteState(GPIOA->CRL, GPIO_CRL_CNF0_Msk, REGISTER_STATE_RESET);
  REGISTER_WriteState(GPIOA->CRL, GPIO_CRL_CNF0_0, REGISTER_STATE_SET);
}

state_t GPIO_ReadPushButtonState(void) {
  return REGISTER_ReadState(GPIOA->IDR, GPIO_IDR_IDR0);
}

/* Switches */

void GPIO_ConfigureSwitches(void) {
  /* Enable Port A clock. */
  REGISTER_WriteState(RCC->APB2ENR, RCC_APB2ENR_IOPAEN, REGISTER_STATE_SET);

  /* Configure PA8 and PA15 to input mode. */
  REGISTER_WriteState(GPIOA->CRH,
    (GPIO_CRH_MODE8_Msk | GPIO_CRH_MODE15_Msk),
    REGISTER_STATE_RESET);

  /* Configure PA8 and PA15 to floating input. */
  REGISTER_WriteState(GPIOA->CRH,
    (GPIO_CRH_CNF8_Msk | GPIO_CRH_CNF15_Msk),
    REGISTER_STATE_RESET);
  REGISTER_WriteState(GPIOA->CRH,
    (GPIO_CRH_CNF8_0 | GPIO_CRH_CNF15_0),
    REGISTER_STATE_SET);

  /* Remap PA15. */
  REGISTER_WriteState(RCC->APB2ENR, RCC_APB2ENR_AFIOEN, REGISTER_STATE_SET);
  REGISTER_WriteState(RCC->APB1ENR, RCC_APB1ENR_PWREN, REGISTER_STATE_SET);
  REGISTER_WriteState(AFIO->MAPR, AFIO_MAPR_SWJ_CFG_Msk, REGISTER_STATE_RESET);
  REGISTER_WriteState(AFIO->MAPR,
    AFIO_MAPR_SWJ_CFG_JTAGDISABLE,
    REGISTER_STATE_SET);
}

state_t GPIO_ReadSwitch1State(void) {
  return REGISTER_ReadState(GPIOA->IDR, GPIO_IDR_IDR8);
}

state_t GPIO_ReadSwitch2State(void) {
  return REGISTER_ReadState(GPIOA->IDR, GPIO_IDR_IDR15);
}
