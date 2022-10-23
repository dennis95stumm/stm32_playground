/**
 ******************************************************************************
 * @file registers.h
 * @author Dennis Stumm
 * @date 2022
 * @version 1.0
 * @brief Basic functions and type definitions used for accessing all registers.
 ******************************************************************************
 */
#ifndef REGISTERS_H_
#define REGISTERS_H_

/**
 * @brief Status of a peripheral device interaction.
 */
/* TODO: Really Registers or peripherals??? */
typedef enum __status_t {
  REGISTER_STATUS_OK = 0, /**< STATUS_OK */
  REGISTER_STATUS_ERROR = 1, /**< STATUS_ERROR */
  REGISTER_STATUS_TIMEOUT = 2/**< STATUS_TIMEOUT */
} status_t;

/**
 * @brief State of a register.
 */
typedef enum __state_t {
  REGISTER_STATE_RESET = 0,/**< STATE_RESET */
  REGISTER_STATE_SET = 1 /**< STATE_SET */
} state_t;

/**
 * @brief Readds the state of the passed register pin mask.
 *
 * @param dataRegister Register to read the state from.
 * @param pinMask Pin mask in the register to read the state from.
 * @return The state of the pin mask in the passed register.
 */
state_t REGISTER_ReadState(uint32_t dataRegister, uint32_t pinMask);

/**
 * @brief Writes the passed state to the passed register pin mask.
 *
 * @param dataRegister Register to write the state to.
 * @param pinMask PinMask in the register to write the state to.
 * @param state The state to write to the pin mask in the register.
 */
void REGISTER_WriteState(uint32_t dataRegister, uint32_t pinMask, state_t state);

/**
 * @brief Toggles a pin mask state in a register.
 *
 * @param dataRegister Register to toggle the state for.
 * @param pinMask Mask of the pins whoose state should be toggled.
 */
void REGISTER_ToggleState(uint32_t dataRegister, uint32_t pinMask);

/**
 * @brief Waits until a pin mask is not set in a register.
 *
 * @param dataRegister Register to check the state for.
 * @param pinMask Mask of the pins whoose state should be checked.
 */
void REGISTER_WaitUntilSet(uint32_t dataRegister, uint32_t pinMask);

#endif /* REGISTERS_H_ */
