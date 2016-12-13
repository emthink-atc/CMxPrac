/*----------------------------------------------------------------------------*
 *      www.emthink.com
 *      (C)2016 Cortex-Mx Practical Course
 *
 * FILE: Practical.c for 4-GLCD
 *----------------------------------------------------------------------------*/

#define __MASTER_FILE
#include "INCLUDE.h"

uint32_t LEDOn, LEDOff;

uint32_t os_time;
uint32_t HAL_GetTick (void) {
  return os_time;
}

/*----------------------------------------------------------------------------*
 *    Main function
 *----------------------------------------------------------------------------*/

int main (void) {

  int32_t max_num = LED_GetCount() - 1;
  int32_t num = 0;
  int32_t dir = 1;

  SystemClock_Config();
  SysTick_Config(SystemCoreClock/100);    /* Generate interrupt each 10 ms  */
  
  LED_Initialize();                       /* LED Initialization           */

  GLCD_Initialize();                      /* GLCD Initialization          */
  GLCD_SetBackgroundColor(GLCD_COLOR_BLUE);
  GLCD_SetForegroundColor(GLCD_COLOR_WHITE);
  GLCD_ClearScreen();                     /* Clear the GLCD               */
  GLCD_SetFont(&GLCD_Font_16x24);
  GLCD_DrawString(0, 4*GLCD_Font_16x24.height, "CM Practical Course ");
  GLCD_DrawString(0, 5*GLCD_Font_16x24.height, "        GLCD        ");
  GLCD_DrawString(0, 6*GLCD_Font_16x24.height, "  www.emthink.com   ");

  while(1) {
    if(LEDOn) {
      LEDOn = 0;
      LED_On(num);                       /* Turn specified LED on        */
    }

    if(LEDOff) {
      LEDOff = 0;
      LED_Off(num);                      /* Turn specified LED off       */
      num += dir;                        /* Change LED number            */
      if(dir == 1 && num == max_num) {
        dir = -1;                        /* Change direction to down     */
      }
      else if(num == 0) {
        dir =  1;                        /* Change direction to up       */
      }
    }
  }
}


/*----------------------------------------------------------------------------*
 *    SysTick IRQ Handler
 *----------------------------------------------------------------------------*/
void SysTick_Handler (void) {
  static uint32_t ticks;
  switch(ticks++) {
    case  0: LEDOn  = 1; break;
    case  5: LEDOff = 1; break;
    case  9: ticks  = 0; break;
    default:
      if(ticks > 10) {
        ticks = 0;
      }
  }
  os_time = os_time + 10;
}

