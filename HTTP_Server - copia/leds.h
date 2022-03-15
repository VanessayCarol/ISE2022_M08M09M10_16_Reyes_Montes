#ifndef  _LEDS_H_
#define  _LEDS_H_
#include "LPC17xx.h" /** Incluye la librería del microprocesador*/
#include "GPIO_LPC17xx.h" /** Incluye la librería de los pines GPIO (pines que se pueden usar como entradas o salidas para distintos usos) del microcontrolador. */
#include "PIN_LPC17xx.h" /** Librería para el pin driver para NXP LPC17xx*/

#define PORT_LED    1 
#define PIN_LED1     18 
#define PIN_LED2     20 
#define PIN_LED3     21 
#define PIN_LED4     23 

void inicia_leds(void);
void encender_leds(int led);
void apagar_leds(int led);


#endif


