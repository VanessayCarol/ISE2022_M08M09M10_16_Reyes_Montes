/*------------------------------------------------------------------------------
 * MDK Middleware - Component ::Network
 * Copyright (c) 2004-2014 ARM Germany GmbH. All rights reserved.
 *------------------------------------------------------------------------------
 * Name:    HTTP_Server.c
 * Purpose: HTTP Server example
 *----------------------------------------------------------------------------*/

#include <stdio.h>
#include "cmsis_os.h"                   /* CMSIS RTOS definitions             */
#include "rl_net.h"                     /* Network definitions                */

#include "Board_GLCD.h"
#include "GLCD_Config.h"
#include "Board_LED.h"
#include "Board_Buttons.h"
#include "Board_ADC.h"

#include "leds.h"
#include "lcd.h"
#include "ADC_LPC1768.h"

extern GLCD_FONT GLCD_Font_6x8;
extern GLCD_FONT GLCD_Font_16x24;

bool LEDrun;
bool LCDupdate;
char lcd_text[2][20+1];

static void BlinkLed (void const *arg);
static void Display (void const *arg);

osThreadDef(BlinkLed, osPriorityNormal, 1, 0);
osThreadDef(Display, osPriorityNormal, 1, 0);

/// Read analog inputs
uint16_t AD_in (uint32_t ch) {
  int32_t val = 0;

  if (ch == 0) {
    ADC_StartConversion();
    while (ADC_ConversionDone () < 0);
    val = ADC_GetValue();
  }
  return ((uint16_t)val);
}

/// Read digital inputs
uint8_t get_button (void) {
  return (Buttons_GetState ());
}

/// IP address change notification
void dhcp_client_notify (uint32_t if_num,
                         dhcpClientOption opt, const uint8_t *val, uint32_t len) {
  if (opt == dhcpClientIPaddress) {
    // IP address has changed
    sprintf (lcd_text[0],"IP address:");
    sprintf (lcd_text[1],"%s", ip4_ntoa (val));
    LCDupdate = true;
  }
}

/*----------------------------------------------------------------------------
  Thread 'Display': LCD display handler
 *---------------------------------------------------------------------------*/
static void Display (void const *arg) {
  init();
  retardo(1000); //us
  LCD_reset();
  retardo(1000);

  sprintf (lcd_text[0], "");
  sprintf (lcd_text[1], "Waiting for DHCP");
  LCDupdate = true;

  while(1) {
    if (LCDupdate == true) {
      LCD_reset();
      EscribeLinea_1(lcd_text[0]);
      EscribeLinea_2(lcd_text[1]);
      posicion1 = 0;
      posicion2 = 0;
      ancho1 = 0;
      ancho2 = 0;
      LCDupdate = false;
    }
    osDelay (250);
  }
}

/*----------------------------------------------------------------------------
  Thread 'BlinkLed': Blink the LEDs on an eval board
 *---------------------------------------------------------------------------*/
static void BlinkLed (void const *arg) {
  const uint8_t led_val[4] = { 0x01,0x02,0x04,0x08 };
  int cnt = 0;

  LEDrun = true;
  while(1) {
    // Every 100 ms
    if (LEDrun == true) {
      LED_SetOut (led_val[cnt]);
      apagar_leds(led_val[cnt]);
      encender_leds(led_val[cnt]);
      if (++cnt >= sizeof(led_val)) {
        cnt = 0;
      }
    }
    osDelay (100);
  }
}

/*----------------------------------------------------------------------------
  Main Thread 'main': Run Network
 *---------------------------------------------------------------------------*/
int main (void) {
  //LED_Initialize     ();
  //Buttons_Initialize ();
  
  ADC_Initialize     ();
  inicia_leds();
  net_initialize     ();

  osThreadCreate (osThread(BlinkLed), NULL);
  osThreadCreate (osThread(Display), NULL);

  while(1) {
    net_main ();
    osThreadYield ();
  }
}
