/**
 ******************************************************************************
 * @file gpio.h
 * @author Dennis Stumm
 * @date 2022
 * @version 1.0
 * @brief Functions for the gpio devices.
 ******************************************************************************
 */
#ifndef INC_GPIO_H_
#define INC_GPIO_H_

#include <register.h>

/**
 * @brief Configures the pins for the leds as outputs.
 */
void GPIO_ConfigureLeds(void);

/**
 * @brief Sets the green led to the passed state.
 *
 * @param state State to set the green led to.
 */
void GPIO_WriteGreenLed(state_t state);

/**
 * @brief Sets the red led to the passed state.
 *
 * @param state State to set the red led to.
 */
void GPIO_WriteRedLed(state_t state);

/**
 * @brief Toggles the state of the green led.
 */
void GPIO_ToggleGreenLed(void);

/**
 * @brief Toggles the state of the red led.
 */
void GPIO_ToggleRedLed(void);

/**
 * @brief Configures the user push button as input.
 */
void GPIO_ConfigurePushButton(void);

/**
 * @brief Reads the state of the user push button.
 *
 * @return State of the push button.
 */
state_t GPIO_ReadPushButtonState(void);

/**
 * @brief Configures the switches as inputs.
 */
void GPIO_ConfigureSwitches(void);

/**
 * @brief Reads the state of the switch one.
 *
 * @return State of the switch one.
 */
state_t GPIO_ReadSwitch1State(void);

/**
 * @brief Reads the state of the switch two.
 *
 * @return State of the switch two.
 */
state_t GPIO_ReadSwitch2State(void);

#endif /* INC_GPIO_H_ */
