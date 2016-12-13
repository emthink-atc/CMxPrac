/*----------------------------------------------------------------------------*
 *      www.emthink.com
 *      (C)2016 Cortex-Mx Practical Course
 *
 * FILE: Practical.c for 6-HID
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
  GLCD_DrawString(0, 5*GLCD_Font_16x24.height, "        HID         ");
  GLCD_DrawString(0, 6*GLCD_Font_16x24.height, "  www.emthink.com   ");
  
  GLCD_DrawString(0, 8*GLCD_Font_16x24.height, "HID LEDs:           ");
  GLCD_SetBackgroundColor(GLCD_COLOR_BLUE);           /* Set the Back Color */
  GLCD_SetForegroundColor(GLCD_COLOR_GREEN);          /* Set the Text Color */
  GLCD_DrawString(10*GLCD_Font_16x24.width, 8*GLCD_Font_16x24.height, "NO_LINK");
  
  USBD_Initialize(0);
  USBD_Connect(0);
  
  Buttons_Initialize();
  
  mut_GLCD    = osMutexCreate(osMutex(mut_GLCD));
  mail_LED    = osMailCreate(osMailQ(mail_LED),  NULL);


  tid_blinky      = osThreadCreate(osThread(blinky),      NULL);
  tid_virtual_led = osThreadCreate(osThread(virtual_led), NULL);
  tid_hid         = osThreadCreate(osThread(hid),         NULL);
  
  osThreadTerminate(osThreadGetId()); 
}

