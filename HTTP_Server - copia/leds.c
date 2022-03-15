#include "leds.h"

    
    void inicia_leds(void){
    GPIO_SetDir (PORT_LED, PIN_LED1, GPIO_DIR_OUTPUT); 
    GPIO_SetDir (PORT_LED, PIN_LED2, GPIO_DIR_OUTPUT); 
    GPIO_SetDir (PORT_LED, PIN_LED3, GPIO_DIR_OUTPUT); 
    GPIO_SetDir (PORT_LED, PIN_LED4, GPIO_DIR_OUTPUT); 
 }

 //función para encender leds
  void encender_leds(int led){
  
    if(led & 1){
      GPIO_PinWrite (PORT_LED, PIN_LED1, 1);
    }
    if(led & 2){
      GPIO_PinWrite (PORT_LED, PIN_LED2, 1);
    }
    if(led & 4){
      GPIO_PinWrite (PORT_LED, PIN_LED3, 1);
    }
    if(led & 8){
      GPIO_PinWrite (PORT_LED, PIN_LED4, 1);
    }
  }
  
  
  void apagar_leds(int led){
  
      GPIO_PinWrite (PORT_LED, PIN_LED1, 0);
      GPIO_PinWrite (PORT_LED, PIN_LED2, 0);
      GPIO_PinWrite (PORT_LED, PIN_LED3, 0);
      GPIO_PinWrite (PORT_LED, PIN_LED4, 0);
  }
  
  