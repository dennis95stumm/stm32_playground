/**
 ******************************************************************************
 * @file rcc.h
 * @author Dennis Stumm
 * @date 2022
 * @version 1.0
 * @brief Header file for the RCC peripheral containing function declarations
 *   for configuring the peripheral clocks and basic timing functions.
 ******************************************************************************
 */
#ifndef PERIPHERALS_INC_RCC_H_
#define PERIPHERALS_INC_RCC_H_

#include <stdint.h>

/**
 * @brief Configures the system clocks to by using an external oscillator. With
 * the following settings:
 *
 * HSE: 8MHz
 * PLL Source: HSE
 * PLL: 8MHz
 * PLL Multiplier: 9
 * USB Prescaler: 1
 * USB: 72 MHz
 * System Clock Source: PLL
 * System Clock: 72 MHz
 * AHB Prescaler: 1
 * HCLK: 72 MHz
 * DMA: 72 MHz
 * Cortex Timer: 72 MHz
 * FCLK: 72 MHz
 * APB1 Prescaler: 2 (36 MHz PCLK1, 72 MHz Timer)
 * ABP2 Prescaler: 1 (72 MHz PCLK2, 72 MHz Timer, ADC Prescaler 6 => 12 MHz)
 * ACR Latency: 2, Prefetchbuffer enabled
 */
void RCC_ConfigureClocks(void);

/**
 * @brief Configures the system tick timer to one millisecond.
 */
void RCC_ConfigureSysTick(void);

/**
 * @brief Returns the milliseconds since system start.
 * @return The current milliseconds since system start.
 */
uint32_t RCC_GetSysTick(void);

/**
 * @brief Pauses the program for the passed amount of milliseconds.
 */
void RCC_Delay(uint32_t milliseconds);

#endif /* PERIPHERALS_INC_RCC_H_ */
