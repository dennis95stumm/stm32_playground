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

volatile uint32_t systemTick = 0;

void RCC_ConfigureClocks(void) {
  RCC->CFGR &= ~RCC_CFGR_PLLMULL_Msk;
  RCC->CFGR |= RCC_CFGR_PLLMULL9;

  RCC->CR |= RCC_CR_HSEON;
  while ((RCC->CR & RCC_CR_HSERDY) == 0) {
    __NOP();
  }

  RCC->CFGR |= RCC_CFGR_PLLSRC;

  RCC->CR |= RCC_CR_PLLON;
  while ((RCC->CR & RCC_CR_PLLRDY) == 0) {
    __NOP();
  }

  FLASH->ACR &= ~FLASH_ACR_LATENCY_Msk;
  FLASH->ACR |= FLASH_ACR_LATENCY_2 | FLASH_ACR_PRFTBE;

  RCC->CFGR &= ~RCC_CFGR_SW_Msk;
  RCC->CFGR |= RCC_CFGR_SW_PLL;

  while ((RCC->CFGR & RCC_CFGR_SWS_Msk) != RCC_CFGR_SWS_PLL) {
    __NOP();
  }

  RCC->CFGR &= ~RCC_CFGR_HPRE_Msk;

  RCC->CFGR &= ~RCC_CFGR_PPRE1_Msk;
  RCC->CFGR |= RCC_CFGR_PPRE1_DIV2;

  RCC->CFGR &= ~RCC_CFGR_PPRE2_Msk;
  RCC->CFGR |= RCC_CFGR_PPRE2_DIV1;

  RCC->CFGR &= ~RCC_CFGR_ADCPRE;
  RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
}

void RCC_ConfigureSysTick(void) {
  SysTick->CTRL = 0;
  SysTick->VAL = 0;
  SysTick->LOAD = 72000 - 1;
  NVIC_SetPriority(SysTick_IRQn, 0);
  SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk
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
