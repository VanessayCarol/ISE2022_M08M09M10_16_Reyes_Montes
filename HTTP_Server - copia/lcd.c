#include "lcd.h"
#include "Arial12x12.h"

extern ARM_DRIVER_SPI Driver_SPI1;
ARM_DRIVER_SPI* SPIdrv=&Driver_SPI1;

uint8_t buffer[512];
int posicion1=0;
int posicion2=0;
uint8_t ancho1=0;
uint8_t ancho2=0;

/*Inicializacion del SPI*/
void init(void){

	SPIdrv->Initialize(NULL); 
	SPIdrv->PowerControl(ARM_POWER_FULL);
	SPIdrv->Control(ARM_SPI_MODE_MASTER | ARM_SPI_CPOL1_CPHA1 | ARM_SPI_MSB_LSB | ARM_SPI_DATA_BITS(8), 20000000);

	//Configuracion
	GPIO_SetDir (PORT_RST, PIN_RST, GPIO_DIR_OUTPUT);
	GPIO_SetDir (PORT_A0, PIN_A0, GPIO_DIR_OUTPUT);
	GPIO_SetDir (PORT_CS, PIN_CS, GPIO_DIR_OUTPUT);
		
	PIN_Configure (PORT_RST,PIN_RST,PIN_FUNC_0,PIN_PINMODE_PULLUP,PIN_PINMODE_NORMAL);
	GPIO_PinWrite (PORT_RST, PIN_RST,1);
	GPIO_PinWrite (PORT_A0, PIN_A0,1);
	GPIO_PinWrite (PORT_CS, PIN_CS,1);
		
	//Forma de la señal
	retardo (1000);
	GPIO_PinWrite(PORT_RST, PIN_RST, 0);
	retardo (1000);
	GPIO_PinWrite (PORT_RST, PIN_RST, 1);
}


void retardo (uint32_t microsegundos){
	
  LPC_SC->PCONP |= ((uint32_t) (1<<2));
  LPC_SC->PCLKSEL0 |= ((uint32_t)(3<<4));   
  LPC_TIM1->MR0 = (microsegundos*12.5); 
  LPC_TIM1->MCR|=((uint32_t)(1<<0));
  LPC_TIM1->TCR|=1; 
  while(!(LPC_TIM1->IR & 0x01)); 
  LPC_TIM1->IR|=1; 
  LPC_TIM0->TCR=0; 
  LPC_TIM1->TC=0; 
}

void wr_data (unsigned char data){
	
	GPIO_PinWrite (PORT_CS, PIN_CS, 0);
	GPIO_PinWrite (PORT_A0, PIN_A0,1);
	SPIdrv->Send(&data, 1);
	GPIO_PinWrite (PORT_CS, PIN_CS, 1);
	
}
void wr_cmd (unsigned char cmd){

	GPIO_PinWrite (PORT_CS, PIN_CS, 0);
	GPIO_PinWrite (PORT_A0, PIN_A0,0);
	SPIdrv->Send(&cmd, 1);	
	GPIO_PinWrite (PORT_CS, PIN_CS, 1);

}

void LCD_reset(void){
	
	wr_cmd(0xAE);
	wr_cmd(0xA2);
	wr_cmd(0xA0);
	wr_cmd(0xC8);
	wr_cmd(0x22);
	wr_cmd(0x2F);
	wr_cmd(0x40);
	wr_cmd(0xAF);
	wr_cmd(0x81);
	wr_cmd(0x17);
	wr_cmd(0xA6);
  memset(buffer,0,512);
  copy_to_lcd();

}
void copy_to_lcd(void){
	int i=0;
	
	wr_cmd(0x00);
	wr_cmd(0x10);
	wr_cmd(0xB0);		//Pagina 0

	for(i=0;i<128;i++){
		wr_data(buffer[i]);
	}
	
	wr_cmd(0x00);
	wr_cmd(0x10);
	wr_cmd(0xB1);		//Pagina 1
	
	for(i=128;i<256;i++){
		wr_data(buffer[i]);
	}

	wr_cmd(0x00);
	wr_cmd(0x10);
	wr_cmd(0xB2);		//Pagina 2
	
	for(i=256;i<384;i++){
		wr_data(buffer[i]);
	}
	
	wr_cmd(0x00);
	wr_cmd(0x10);
	wr_cmd(0xB3);		//Pagina 3
	
	for(i=384;i<512;i++){
		wr_data(buffer[i]);
	}
}
int EscribeLetra_L1(uint8_t letra){
  uint8_t i, valor1, valor2;
  uint16_t comienzo = 0;
  
  comienzo = 25* (letra - ' '); 
	posicion1 = posicion1 + ancho1;
	ancho1 = Arial12x12[comienzo];
	
	if(posicion1+ancho1 < 124){
		for (i = 0; i < 12; i++){
			valor1 = Arial12x12[comienzo+i*2+1];
			valor2 = Arial12x12[comienzo+i*2+2];
		 
			buffer[i+posicion1] = valor1;
			buffer[i+128+posicion1] = valor2;
		}
	}
  copy_to_lcd();
  return 0;
}


int EscribeLetra_L2(uint8_t letra){
  uint8_t i, valor1, valor2;
  uint16_t comienzo = 0;
  
  comienzo = 25* (letra - ' '); 
  posicion2 = posicion2 + ancho2;
	ancho2 = Arial12x12[comienzo];
	
	if(posicion2+ancho2 < 124){
		for (i = 0; i < 12; i++){
			valor1 = Arial12x12[comienzo+i*2+1];
			valor2 = Arial12x12[comienzo+i*2+2];
		 
			buffer[i+256+posicion2] = valor1;
			buffer[i+384+posicion2] = valor2;
		}
	}
  copy_to_lcd();
  return 0;
}

void EscribeLinea_1 (char *lineas){
  uint8_t p;
 
  for (p=0; p<strlen(lineas); p++) {
   EscribeLetra_L1(lineas[p]); 
  }
}

void EscribeLinea_2 (char *lineas){
  uint8_t p;

  for (p=0; p<strlen(lineas); p++) {
   EscribeLetra_L2(lineas[p]);  
  }
}

