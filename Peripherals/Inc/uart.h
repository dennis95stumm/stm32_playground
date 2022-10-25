/**
 ******************************************************************************
 * @file uart.h
 * @author Dennis Stumm
 * @date 2022
 * @version 1.0
 * @brief Function and type definitions for UART peripherals.
 ******************************************************************************
 */
#ifndef INC_UART_H_
#define INC_UART_H_

#include <stdint.h>

#define UART_SR_ERROR_MSK (USART_SR_PE | USART_SR_FE | USART_SR_NE | USART_SR_ORE)

/* DIV = 72M/(16*115200)=39.0625 = Mantissa 0x27, Fraction 16*0,0625=1 */
#define UART_MANTISSA 0x0027
#define UART_FRACTION 0x1

/**
 * @brief Status of UART peripheral device interaction.
 */
typedef enum __status_t {
  UART_STATUS_OK = 0, /**< STATUS_OK */
  UART_STATUS_ERROR = 1, /**< STATUS_ERROR */
  UART_STATUS_TIMEOUT = 2/**< STATUS_TIMEOUT */
} status_t;

/**
 * @brief Sets up UART1 ports and mode.
 */
void UART_Configure(void);

/**
 * Sends data over the UART1.
 *
 * @param data Pointer to the data which should be send.
 * @param len Length of data that should be send.
 * @param timeout Timeout in milliseconds after which the send will be aborted.
 * @return {@link status_t} Status whether the data was send successful or not.
 */
status_t UART_Transmit(uint8_t *data, uint32_t len, uint32_t timeout);

#endif /* INC_UART_H_ */
