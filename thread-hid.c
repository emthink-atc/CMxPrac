/*----------------------------------------------------------------------------*
 *  	www.emthink.com
 *  	(C)2016 Cortex-Mx Practical Course
 *
 * FILE: thread-hid.c for 6-HID
 *----------------------------------------------------------------------------*/

#include "INCLUDE.h"

/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::USB:Device
 * Copyright (c) 2004-2014 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:	USBD_User_HID_0.c
 * Purpose: USB Device Human Interface Device class (HID) User module
 * Rev.:	V6.00
 *----------------------------------------------------------------------------*/


// Called during USBD_Initialize to initialize the USB Device class.
void USBD_HID0_Initialize (void) {
  // ToDo: add code for initialization
}


// Called during USBD_Uninitialize to de-initialize the USB Device class.
void USBD_HID0_Uninitialize (void) {
  // ToDo: add code for de-initialization
}


int32_t USBD_HID0_GetReport (uint8_t rtype, uint8_t req, uint8_t rid, uint8_t *buf) {


  switch (rtype) {
    case HID_REPORT_INPUT:
      switch (rid) {
        case 0:
          switch (req) {
            case USBD_HID_REQ_EP_CTRL:        // Explicit USB Host request via Control OUT Endpoint
            case USBD_HID_REQ_PERIOD_UPDATE:  // Periodic USB Host request via Interrupt OUT Endpoint
              // ToDo: update buffer for report data, example:
              // buf[0] = 0;       // Data Value = 0
              // buf[1] = 5;       // Data Value = 5
              // return (2);       // Data Size  = 2 bytes
              break;
            case USBD_HID_REQ_EP_INT:         // Called after USBD_HID_GetReportTrigger to signal
                                              // data obtained.
              break;
          }
          break;
      }
      break;


    case HID_REPORT_FEATURE:
      break;
  }
  return (0);
}


bool USBD_HID0_SetReport (uint8_t rtype, uint8_t req, uint8_t rid, const uint8_t *buf, int32_t len) {


  T_MEAS *mptr;


  switch (rtype) {
    case HID_REPORT_OUTPUT:
      mptr = osMailAlloc(mail_LED, osWaitForever);  // Allocate memory
      mptr->led = *buf;                             // Set mail contents
      osMailPut(mail_LED, mptr);                    // Send mail
      break;
    case HID_REPORT_FEATURE:
      break;
  }
  return true;
}


/*----------------------------------------------------------------------------*
 *      Thread 'hid': Human Interface Device
 *----------------------------------------------------------------------------*/
void hid (void const *argument) {
  uint8_t but;
  uint8_t buf[2];
  for (;;) {
    but = (uint8_t)(Buttons_GetState ());
    if (but ^ buf[0]) {
      buf[0] = but;
      USBD_HID_GetReportTrigger(0, 0, &buf[0], 1);
    }
    osDelay(100);                       /* 100 ms delay for sampling buttons  */
  }
}

