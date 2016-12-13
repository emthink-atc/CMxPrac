/*----------------------------------------------------------------------------*
 *    www.emthink.com
 *    (C)2016 Cortex-Mx Practical Course
 *
 * FILE: thread-blinky.c for 5-RTX
 *----------------------------------------------------------------------------*/


#include "INCLUDE.h"


/*----------------------------------------------------------------------------*
 *      Thread 'blinky': Swing the LEDs
 *----------------------------------------------------------------------------*/
void blinky (void const *argument) {


  int32_t ticks   = 0;
  int32_t max_num = 8;
  int32_t num     = 0;
  int32_t dir     = 1;
  int32_t LEDOn, LEDOff;


  for (;;) {
    switch(ticks++) {
      case 0: LEDOn  = 1; break;
      case 5: LEDOff = 1; break;
      case 9: ticks  = 0; break;
    }
    if(LEDOn == 1) {
      LEDOn = 0;
      LED_On(num);
    }
    if(LEDOff == 1) {
      LEDOff = 0;
      LED_Off(num);
      num += dir;
      if(dir == 1 && num == (max_num-1)){
        dir = -1;
      }
      else if(num == 0){
        dir = 1;
      }
    }
    osDelay(5);
  }
}


