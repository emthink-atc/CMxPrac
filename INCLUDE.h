/*----------------------------------------------------------------------------*
 *      www.emthink.com
 *      (C)2016 Cortex-Mx Practical Course
 *
 * FILE: INCLUDE.h for 4-GLCD
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

/* Font */
extern GLCD_FONT     GLCD_Font_16x24;
#endif /* __INCLUDE_H */

