/*----------------------------------------------------------------------------*
 *      www.emthink.com
 *      (C)2016 Cortex-Mx Practical Course
 *
 * FILE: INCLUDE.h for 6-HID
 *----------------------------------------------------------------------------*/

#ifndef __INCLUDE_H
#define __INCLUDE_H

#include "stm32f4xx_hal.h"                  /* STM32F4xx Definitions          */

#ifdef __MASTER_FILE
extern void SystemClock_Config(void);
#endif /* __MASTER_FILE */

#include "Board_LED.h"
#include "Board_GLCD.h"
#include "GLCD_Config.h"

#include "cmsis_os.h"


#include "Board_Buttons.h"


#include "rl_usbd.h"
#include "usb_hid.h"


/* Font */
extern GLCD_FONT     GLCD_Font_16x24;

/* LCD Chars */
#define CIRCLE_FULL           0x81
#define CIRCLE_EMPTY_SMALL    0x82

/*----------------------------------------------------------------------------*
 *    My_Thread Macro
 *----------------------------------------------------------------------------*/
#ifdef __MASTER_FILE
#define My_Thread(name, stacksz) extern void name (void const *argument);osThreadId tid_##name;osThreadDef(name, osPriorityNormal, 1, stacksz)
#else
#define My_Thread(name, stacksz) extern osThreadId tid_##name
#endif /* __MASTER_FILE */

/*----------------------------------------------------------------------------*
 *    My_Mutex Macro
 *----------------------------------------------------------------------------*/
#ifdef __MASTER_FILE
#define My_Mutex(name) osMutexId name;osMutexDef(name)
#else
#define My_Mutex(name) extern osMutexId name
#endif


/*----------------------------------------------------------------------------*
 *    My_Mail Macro
 *----------------------------------------------------------------------------*/
typedef struct {
	uint8_t led;
} T_MEAS;


#ifdef __MASTER_FILE
#define My_Mail(name) osMailQId name;osMailQDef(name, 16, T_MEAS)
#else
#define My_Mail(name) extern osMailQId name
#endif


/*----------------------------------------------------------------------------*
 *    My_Threads Definitions
 *----------------------------------------------------------------------------*/
My_Thread(blinky,      0);
My_Thread(virtual_led, 0);
My_Thread(hid,       500);


/*----------------------------------------------------------------------------*
 *    My_Mutexs Definitions
 *----------------------------------------------------------------------------*/
My_Mutex(mut_GLCD);


/*----------------------------------------------------------------------------*
 *    My_Mails Definitions
 *----------------------------------------------------------------------------*/
My_Mail(mail_LED);


#endif /* __INCLUDE_H */

