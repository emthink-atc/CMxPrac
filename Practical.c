/*----------------------------------------------------------------------------*
 *      www.emthink.com
 *      (C)2016 Cortex-Mx Practical Course
 *
 * FILE: Practical.c for 5-RTX
 *----------------------------------------------------------------------------*/

#define __MASTER_FILE
#include "INCLUDE.h"


#ifdef RTE_CMSIS_RTOS_RTX
extern uint32_t os_time;
uint32_t HAL_GetTick(void) {
  return os_time;
}
#endif

/*----------------------------------------------------------------------------*
 *    Main function
 *----------------------------------------------------------------------------*/
int main (void) {
  SystemClock_Config();
  
  LED_Initialize();                       /* LED Initialization           */

  GLCD_Initialize();                      /* GLCD Initialization          */
  GLCD_SetBackgroundColor(GLCD_COLOR_BLUE);
  GLCD_SetForegroundColor(GLCD_COLOR_WHITE);
  GLCD_ClearScreen();                     /* Clear the GLCD               */
  GLCD_SetFont(&GLCD_Font_16x24);
  GLCD_DrawString(0, 4*GLCD_Font_16x24.height, "CM Practical Course ");
  GLCD_DrawString(0, 5*GLCD_Font_16x24.height, "        RTX         ");
  GLCD_DrawString(0, 6*GLCD_Font_16x24.height, "  www.emthink.com   ");

  tid_blinky  = osThreadCreate(osThread(blinky), NULL);
  
  osThreadTerminate(osThreadGetId()); 
}


