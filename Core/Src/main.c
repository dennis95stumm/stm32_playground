/**
 ******************************************************************************
 * @file main.c
 * @author Dennis Stumm
 * @date 2022
 * @version 1.0
 * @brief Main file of the STM32 playground project.
 ******************************************************************************
 */

#include <main.h>
#include <program.h>

int main(void) {
  configure();

  while (1) {
    run();
  }
}
