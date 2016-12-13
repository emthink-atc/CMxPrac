/*----------------------------------------------------------------------------*
 *      www.emthink.com
 *      (C)2015 Cortex-Mx Practical Course
 *
 * FILE: thread-virtual_led.c for 6-HID
 *----------------------------------------------------------------------------*/


#include "INCLUDE.h"


/*----------------------------------------------------------------------------*
 *  Thread 'virtual_led': HID input responses on the virtual LEDs on the LCD
 *----------------------------------------------------------------------------*/
void virtual_led (void const *argument) {
  T_MEAS *rptr;
  osEvent evt;
  int32_t i;
  uint8_t ox, led;
  
  for (;;) {
    evt = osMailGet(mail_LED, osWaitForever);         /* wait for mail */
    if(evt.status == osEventMail) {
      rptr = evt.value.p;
      led = rptr->led;
      osMailFree(mail_LED, rptr);                     /* free memory allocated for mail */
      osMutexWait(mut_GLCD, osWaitForever);
      GLCD_SetBackgroundColor(GLCD_COLOR_BLUE);       /* Set the Back Color */
      GLCD_SetForegroundColor(GLCD_COLOR_GREEN);      /* Set the Text Color */
      for(i=7; i>=0; i--){
        if(led & 1<<i) {
          GLCD_SetForegroundColor(GLCD_COLOR_GREEN);  /* Set the Text Color */
          ox = CIRCLE_FULL;      
        }					
        else {
          GLCD_SetForegroundColor(GLCD_COLOR_DARK_GREY); /* Set the Text Color */
          ox = CIRCLE_EMPTY_SMALL;
        }
        GLCD_DrawChar((GLCD_Font_16x24.width*10)+(GLCD_Font_16x24.width*(7-i)), 8*GLCD_Font_16x24.height, ox);    
      }
      osMutexRelease(mut_GLCD);
    }
  }
}

