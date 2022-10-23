/**
 ******************************************************************************
 * @file register.c
 * @author dstumm
 * @date 2022
 * @version 1.0
 * @brief Basic functions used for accessing all registers.
 ******************************************************************************
 */

#include <register.h>

state_t REGISTER_ReadState(uint32_t dataRegister, uint32_t pinMask) {
  return (state_t) ((dataRegister & pinMask) == pinMask);
}

void REGISTER_WriteState(uint32_t dataRegister, uint32_t pinMask, state_t state) {
  if (state == REGISTER_STATE_SET) {
    dataRegister |= pinMask;
  } else {
    dataRegister &= ~(pinMask);
  }
}

void REGISTER_ToggleState(uint32_t dataRegister, uint32_t pinMask) {
  dataRegister ^= pinMask;
}

void REGISTER_WaitUntilSet(uint32_t dataRegister, uint32_t pinMask) {
  while (((state_t) (dataRegister & pinMask)) == REGISTER_STATE_RESET) {
    __NOP();
  }
}
