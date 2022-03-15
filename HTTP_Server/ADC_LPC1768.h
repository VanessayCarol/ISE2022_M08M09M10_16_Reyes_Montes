#include "LPC17xx.h"
#include "GPIO_LPC17xx.h"

int32_t ADC_Initialize (void);
int32_t ADC_Uninitialize (void);
int32_t ADC_StartConversion (void);
int32_t ADC_ConversionDone (void) ;
int32_t ADC_GetValue (void) ;
uint32_t ADC_GetResolution (void) ;
void ADC_IRQHandler(void) ;
