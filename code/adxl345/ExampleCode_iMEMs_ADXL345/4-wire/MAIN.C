/********************************************************************************

 Author        : Neil.Zhao  

 Date          : Sep 25th 2009

 File          : main.c

 Hardware      : ADXL345 EVALUATION BOARD (Based on M Board)`ADUC7026+ADXL345
		
********************************************************************************/

#include<ADuC7026.h>
#include<Common.h>
#include"ADXL345.H"	

unsigned char buf[4] = {0,0,0,0};

void putchar(unsigned char ch)/* Write character to Serial Port  */  
{          
	COMTX = ch;				 //COMTX is an 8-bit transmit register.
    while(!(0x020==(COMSTA0 & 0x020)))
    {;}
}


void ADuC7026_Initiate(void)
{
//  PLL SETTING  //
	POWKEY1 = 0x01;				//Start PLL setting
	POWCON = 0x00;				//Set PLL active mode with CD = 0
	POWKEY2 = 0xF4;				//Finish PLL setting

//  GPIO SETTING  //

	GP1CON = 0x00000011;		//CONFIG P1.6 P1.5 P1.4  as GPIO  P1.1 P1.O  as com
	GP2CON = 0x00000000;		//CONFIG P1.7 as GPIO

	GP2DAT = 0xE0E00000;		//P2.7 (CS4)  P2.6(CS2) P2.5(CS1) HIGH
	GP1DAT = 0xD0D00000;		//P1.6 SDO,P1.5 SDI,P1.4 SCLK  LOW	 P1.7(CS3) HIGH

//UART Initial£¬Baud Rate = 9600
	COMCON0 = 0x80;  
	COMDIV0 = 0x88;    		
	COMDIV1 = 0x00;
	COMCON0 = 0x07;  	
//*/
//  ADC / DAC SETTING  //
	DAC0CON = 0x13;				// DAC configuration
	DAC1CON = 0x13;				// DAC configuration
	DAC2CON = 0x13;				// DAC configuration
	
	DAC0DAT = 0x5500000;		//Set VS1 = 3.3 V
	DAC1DAT = 0x5500000;		//Set VS2 = 3.3 V

}

int main(void) {

	ADuC7026_Initiate();
/*
	buf[0]=0X03;
	WriteToADXL345ViaSpi(XL345_OFSX,1,buf);
	buf[0]=0XFF;
	ReadFromADXL345ViaSpi(XL345_OFSX,1,buf);
	putchar(buf[0]);
*/
	ReadFromADXL345ViaSpi(XL345_DEVID,1,buf);
	putchar(buf[0]);

	while(1)
    {;}
}
