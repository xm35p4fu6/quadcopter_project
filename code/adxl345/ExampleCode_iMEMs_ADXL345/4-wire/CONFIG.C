// config.c
#include <ADuC7026.h>
//#include "common.h"

void InitCPU(void){

//  PLL SETTING  //
	POWKEY1 = 0x01;				//Start PLL setting
	POWCON = 0x00;				//Set PLL active mode with CD = 0
	POWKEY2 = 0xF4;				//Finish PLL setting

//  GPIO SETTING  //
	
	GP0CON = 0x00000220;		//Look for GPIO configuration file for detail setting
	GP1CON = 0x02222211;		//P1.7 as GPIO
	GP2CON = 0x00022220;		//Configure External RAM
	GP3CON = 0x22222222;
	GP4CON = 0x22222222;

	GP0DAT = 0xCE000000;		//P0.0 P0.4 P0.5 input
	GP1DAT = 0x80800000;		//P1.7(CS3) as output and set output  
	GP2DAT = 0xE1E10000;		//Always set P2.0, P2.5/6/7(CS1/2/4) output
	GP3DAT = 0x00000000;
	GP4DAT = 0x00000000;

//  UART BAURD RATE SETTING  //
   	COMCON0 = 0x80;				// start setting up UART at 115200bps,  Setting DLAB
	COMDIV0 = 0x0B;				// 115200
	COMDIV1 = 0x00;
   	COMCON0 = 0x0F;				// clearing DLAB, Odd Parity, 8 bits, 2 stop bits
	COMDIV2 = 0x883E;			// 115200	

//  ADC / DAC SETTING  //
	DAC0CON = 0x13;				// DAC configuration
	DAC1CON = 0x13;				// DAC configuration
	DAC2CON = 0x13;				// DAC configuration
	DAC0DAT = 0x00000000;		// DAC output
	DAC1DAT = 0x00000000;		// DAC output
	DAC2DAT = 0x00000000;		// DAC output

// External Memory Config
	XMCFG = 0x1;
	XM0CON = 0x3;
	XM0PAR = 0x70FF;


}

void InitSPI(void){				// SPI-Master setup	

//	SPIDIV = 0x28;				//SPI speed in MHz = 0.5
//	SPIDIV = 0x13;				//SPI speed in MHz = 1		
	SPIDIV = 0x05;				//SPI speed in MHz = 3.4	
//	SPIDIV = 0x03;				//SPI speed in MHz = 5	
//	SPIDIV = 0x01;				//SPI speed in MHz = 10							
	SPICON = 0x104F;			// enable SPI master in continuous transfer mode 

	GP2SET = 0xE00000;			//CS1 = High CS2 = High CS4 = High
	GP1SET = 0x800000;			//CS3 = High
}