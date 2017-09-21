/*----------------------------------------------------------------------------*
 *      www.emthink.com
 *      (C)2016 Cortex-Mx Practical Course
 *
 * FILE: INCLUDE.h for 5-RTX
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

/* Font */
extern GLCD_FONT     GLCD_Font_16x24;

/* LCD Chars */
#define CIRCLE_FULL           0x81
#define CIRCLE_EMPTY_SMALL    0x82

/*----------------------------------------------------------------------------*
 *    My_Thread Macro
 *----------------------------------------------------------------------------*/
#ifdef __MASTER_FILE
#define My_Thread(name) \
  extern void name (void const *argument); \
  osThreadId tid_##name; \
  osThreadDef(name, osPriorityNormal, 1, 0)
#else
#define My_Thread(name) \
  extern osThreadId tid_##name
#endif /* __MASTER_FILE */

/*----------------------------------------------------------------------------*
 *    My_Thread Definitions
 *----------------------------------------------------------------------------*/
My_Thread(blinky);

#endif /* __INCLUDE_H */

