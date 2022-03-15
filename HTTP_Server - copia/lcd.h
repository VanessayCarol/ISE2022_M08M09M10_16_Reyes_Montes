#include "GPIO_LPC17xx.h"
#include "LPC17xx.h"
#include "PIN_LPC17xx.h"
#include "Driver_SPI.h"
#include "stdio.h" 
#include "string.h"

#ifndef LCD_H
#define LCD_H

//Puerto y pin del RESET
#define PORT_RST 0
#define PIN_RST 8

//Puerto y pin del AO
#define PORT_A0 0
#define PIN_A0 6

//Puerto y pin del CS
#define PORT_CS 0
#define PIN_CS 18

void init(void);
void retardo (uint32_t microsegundos);
void wr_data (unsigned char data);
void wr_cmd (unsigned char cmd);
void LCD_reset(void);
void copy_to_lcd(void);
int EscribeLetra_L1(uint8_t letra);
int EscribeLetra_L2(uint8_t letra);
void EscribeLinea_1(char* lineas);
void EscribeLinea_2(char* lineas);

extern int posicion1;
extern int posicion2;
extern uint8_t ancho1;
extern uint8_t ancho2;


#endif
