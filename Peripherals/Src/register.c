/**
 ******************************************************************************
 * @file register.c
 * @author dstumm
 * @date 2022
 * @version 1.0
 * @brief Basic functions used for accessing all registers.
 ******************************************************************************
 */

#include <stm32f103xb.h>
#include <register.h>

bool REGISTER_IsSet(volatile uint32_t *dataRegister, uint32_t pinMask) {
  return (*dataRegister & pinMask) == pinMask;
}

void REGISTER_Set(volatile uint32_t *dataRegister, uint32_t pinMask) {
  *dataRegister |= pinMask;
}

void REGISTER_Reset(volatile uint32_t *dataRegister, uint32_t pinMask) {
  *dataRegister &= ~(pinMask);
}

void REGISTER_WriteState(
  volatile uint32_t *dataRegister,
  uint32_t pinMask,
  state_t state) {

  if (state == REGISTER_STATE_SET) {
    REGISTER_Set(dataRegister, pinMask);
  } else {
    REGISTER_Reset(dataRegister, pinMask);
  }
}

void REGISTER_ToggleState(volatile uint32_t *dataRegister, uint32_t pinMask) {
  *dataRegister ^= pinMask;
}

void REGISTER_WaitUntilSet(volatile uint32_t *dataRegister, uint32_t pinMask) {
  while (!REGISTER_IsSet(dataRegister, pinMask)) {
    __NOP();
  }
}
