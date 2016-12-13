/*----------------------------------------------------------------------------*
 *      www.emthink.com
 *      (C)2016 Cortex-Mx Practical Course
 *
 * FILE: Practical.c for 2-SysTick
 *----------------------------------------------------------------------------*/

#define __MASTER_FILE
#include "INCLUDE.h"

/*----------------------------------------------------------------------------*
 *      Main function
 *----------------------------------------------------------------------------*/

int main (void) {
  SystemClock_Config();
  SysTick_Config(SystemCoreClock/100);      /* Generate interrupt each 10 ms  */

  while(1);
}


/*----------------------------------------------------------------------------*
 *      SysTick IRQ Handler
 *----------------------------------------------------------------------------*/

void SysTick_Handler (void) {
  static uint32_t ticks;
  
  switch (ticks++) {
    default:
      if (ticks > 10) {
        ticks = 0;
      }
  }
}
