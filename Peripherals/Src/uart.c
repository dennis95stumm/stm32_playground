/**
 ******************************************************************************
 * @file uart.c
 * @author Dennis Stumm
 * @date 2022
 * @version 1.0
 * @brief Functions for UART peripherals.
 ******************************************************************************
 */

#include <stm32f103xb.h>

#include <uart.h>
#include <register.h>
#include <rcc.h>

void UART_Configure(void) {
  /* Enable clock */
  REGISTER_Set(
    &RCC->APB2ENR,
    (RCC_APB2ENR_AFIOEN | RCC_APB2ENR_IOPAEN | RCC_APB2ENR_USART1EN));

  /* Configure GPIO Pins (PA9 - TX, PA10 - RX) with modes */
  REGISTER_Reset(&AFIO->MAPR, AFIO_MAPR_USART1_REMAP_Msk);
  REGISTER_Reset(&GPIOA->CRH, (GPIO_CRH_CNF9_Msk | GPIO_CRH_MODE9_Msk));
  REGISTER_Set(
    &GPIOA->CRH,
    (GPIO_CRH_CNF9_1 | GPIO_CRH_MODE9_1 | GPIO_CRH_MODE9_0));
  REGISTER_Reset(&GPIOA->CRH, (GPIO_CRH_CNF10_Msk | GPIO_CRH_MODE10_Msk));
  REGISTER_Set(&GPIOA->CRH, GPIO_CRH_CNF10_1);

  /* Configure USART1 MODE */
  /* Set word length 8 Bit */
  REGISTER_Set(&USART1->CR1, USART_CR1_M);

  /* Enable parity control (even parity) */
  REGISTER_Set(&USART1->CR1, USART_CR1_PS);
  REGISTER_Set(&USART1->CR1, USART_CR1_PCE);

  /* Disable interrupts */
  REGISTER_Reset(
    &USART1->CR1,
    (USART_CR1_PEIE | USART_CR1_TXEIE | USART_CR1_TCIE | USART_CR1_RXNEIE
      | USART_CR1_IDLEIE));
  REGISTER_Reset(&USART1->CR2, USART_CR2_LBDIE);
  REGISTER_Reset(&USART1->CR3, (USART_CR3_CTSIE | USART_CR3_EIE));

  /* Disable receiver */
  REGISTER_Reset(&USART1->CR1, USART_CR1_RE);

  /* Send no break character */
  REGISTER_Reset(&USART1->CR1, USART_CR1_SBK);

  /* Disable not necessary modes (lin, hardware flow control, dma, smartcard,
   * halfduplex, irda) */
  REGISTER_Reset(&USART1->CR2, USART_CR2_LINEN);
  REGISTER_Reset(
    &USART1->CR3,
    (USART_CR3_CTSE | USART_CR3_RTSE | USART_CR3_DMAT
      | USART_CR3_DMAR | USART_CR3_SCEN | USART_CR3_NACK | USART_CR3_HDSEL
      | USART_CR3_IREN));

  /* Set stop bits to 1 */
  REGISTER_Reset(&USART1->CR2, USART_CR2_STOP_Msk);

  /* Set clock polarity, phase, last bit clock pulse and enable clock */
  REGISTER_Set(
    &USART1->CR2,
    (USART_CR2_CPOL | USART_CR2_CPHA | USART_CR2_CLKEN));

  /* Enable transmitter */
  REGISTER_Set(&USART1->CR1, USART_CR1_TE);

  /* Enable UART */
  REGISTER_Set(&USART1->CR1, USART_CR1_UE);

  /* Configure USART1 Baud Rate
   * DIV = 72M/(16*115200)=39.0625 = Mantissa 0x27, Fraction 16*0,0625=1 */
  REGISTER_Reset(
    &USART1->BRR,
    (USART_BRR_DIV_Fraction_Msk | USART_BRR_DIV_Mantissa_Msk));
  REGISTER_Set(
    &USART1->BRR,
    (UART_MANTISSA << USART_BRR_DIV_Mantissa_Pos));
  REGISTER_Set(
    &USART1->BRR,
    (UART_FRACTION << USART_BRR_DIV_Fraction_Pos));
}

status_t UART_Transmit(uint8_t *data, uint32_t len, uint32_t timeout) {
  uint32_t index = 0;
  uint32_t start = RCC_GetSysTick();

  while (index < len) {
    if (REGISTER_IsSet(&USART1->SR, UART_SR_ERROR_MSK)) {
      return UART_STATUS_ERROR;
    } else if (REGISTER_IsSet(&USART1->SR, USART_SR_TXE)) {
      USART1->DR = data[index++];
    } else if ((RCC_GetSysTick() - start) >= timeout) {
      return UART_STATUS_TIMEOUT;
    }
  }

  while (1) {
    if (REGISTER_IsSet(&USART1->SR, UART_SR_ERROR_MSK)) {
      return UART_STATUS_ERROR;
    } else if (REGISTER_IsSet(&USART1->SR, USART_SR_TC)) {
      return UART_STATUS_OK;
    } else if ((RCC_GetSysTick() - start) >= timeout) {
      return UART_STATUS_TIMEOUT;
    }
  }
}
