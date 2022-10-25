/**
 ******************************************************************************
 * @file rcc.c
 * @author Dennis Stumm
 * @date 2022
 * @version 1.0
 * @brief Functions fpr RCC peripheral containing functions for configuring the
 *   peripheral clocks and basic timing functions.
 ******************************************************************************
 */

#include <stm32f103xb.h>
#include <register.h>

volatile uint32_t systemTick = 0;

void RCC_ConfigureClocks(void) {
  REGISTER_Reset(&RCC->CFGR, RCC_CFGR_PLLMULL_Msk);
  REGISTER_Set(&RCC->CFGR, RCC_CFGR_PLLMULL9);

  REGISTER_Set(&RCC->CR, RCC_CR_HSEON);
  REGISTER_WaitUntilSet(&RCC->CR, RCC_CR_HSERDY);

  REGISTER_Set(&RCC->CFGR, RCC_CFGR_PLLSRC);
  REGISTER_Set(&RCC->CR, RCC_CR_PLLON);
  REGISTER_WaitUntilSet(&RCC->CR, RCC_CR_PLLRDY);

  REGISTER_Reset(&FLASH->ACR, FLASH_ACR_LATENCY_Msk);
  REGISTER_Set(&FLASH->ACR, (FLASH_ACR_LATENCY_2 | FLASH_ACR_PRFTBE));

  REGISTER_Reset(&RCC->CFGR, RCC_CFGR_SW_Msk);
  REGISTER_Set(&RCC->CFGR, RCC_CFGR_SW_PLL);

  while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_PLL) {
    __NOP();
  }

  REGISTER_Reset(&RCC->CFGR, RCC_CFGR_HPRE_Msk);

  REGISTER_Reset(&RCC->CFGR, RCC_CFGR_PPRE1_Msk);
  REGISTER_Set(&RCC->CFGR, RCC_CFGR_PPRE1_DIV2);

  REGISTER_Reset(&RCC->CFGR, RCC_CFGR_PPRE2_Msk);
  REGISTER_Set(&RCC->CFGR, RCC_CFGR_PPRE2_DIV1);

  REGISTER_Reset(&RCC->CFGR, RCC_CFGR_ADCPRE);
  REGISTER_Set(&RCC->CFGR, RCC_CFGR_ADCPRE_DIV6);
}

void RCC_ConfigureSysTick(void) {
  SysTick->CTRL = 0;
  SysTick->VAL = 0;
  SysTick->LOAD = 72000 - 1;
  NVIC_SetPriority(SysTick_IRQn, 0);

  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk
    | SysTick_CTRL_TICKINT_Msk
    | SysTick_CTRL_ENABLE_Msk;
}

uint32_t RCC_GetSysTick(void) {
  return systemTick;
}

void RCC_Delay(uint32_t milliseconds) {
  uint32_t start = RCC_GetSysTick();
  while ((RCC_GetSysTick() - start) < milliseconds) {
    __NOP();
  }
}

void SysTick_Handler(void) {
  systemTick++;
}
