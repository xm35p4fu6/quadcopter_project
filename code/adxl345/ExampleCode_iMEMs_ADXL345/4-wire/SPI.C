/***************************************************************************

 Author        : Neil Zhao - CAST

 Date          : Sep 25th, 2009

 File          : SPI.c

 Hardware      : ADuC7026 and ADXL345

 Description   : Use the GPIO to simulate the 4-Wire SPI Interface of ADXL345

		
***************************************************************************/

#include<ADuC7026.h>	
#include<Common.h>	

void delay (signed int length)
{
	while (length >0)
    	length--;
}

//---------------------------------
//WriteToADXL345ViaSpi();
//---------------------------------
//Function that writes to the ADXL345 via the SPI port. It sends first the control
//word that includes the start address and then the data to write.
//--------------------------------------------------------------------------------
void WriteToADXL345ViaSpi(unsigned char RegisterAddress, unsigned char NumberofRegisters, unsigned char *RegisterData)
{
	unsigned	char	ControlValue = 0;
	unsigned	char	ValueToWrite = 0;
	signed		char	RegisterIndex = 0;
	unsigned	char	i = 0;

	//Create the 8-bit header
	ControlValue = RegisterAddress;

//	SET_SCL();
//	delay(1);	
	SET_CS();
	SET_SCL();
	delay(3);
	CLR_CS();	 //bring CS low
	delay(3);

	CLR_SCL();
	CLR_SDO();	 //set WRITE bit
	delay(3);
	SET_SCL();
	delay(3);
	ControlValue <<= 1;

	CLR_SCL();
	SET_SDO();	//set MB bit
	delay(3);
	SET_SCL();
	delay(3);
	ControlValue <<= 1;

	//Write out the control word
	for(i=0; i<6; i++)
	{
		CLR_SCL();
		if(0x80 == (ControlValue & 0x80))
		{
			SET_SDO();	  //Send one to SDO pin
		}
		else
		{
			CLR_SDO();	  //Send zero to SDO pin
		}
		delay(3);
		SET_SCL();
		delay(3);
		ControlValue <<= 1;	//Rotate data
	}

	//And then the data
	for (RegisterIndex=NumberofRegisters; RegisterIndex>0; RegisterIndex--)
	{
		ValueToWrite = *(RegisterData + RegisterIndex - 1);
		for (i=0; i<8; i++)
		{
			CLR_SCL();
			if(0x80 == (ValueToWrite & 0x80))
			{
				SET_SDO();	  //Send one to SDO pin
			}
			else
			{
				CLR_SDO();	  //Send zero to SDO pin
			}
			delay(3);
			SET_SCL();
			delay(3);
			ValueToWrite <<= 1;	//Rotate data
		}
	}
	SET_CS();	//bring CS high again
}

//---------------------------------
//ReadFromADXL345ViaSpi();
//---------------------------------
//Function that reads from the ADXL345 via the SPI port. It first send the control word
//that includes the start address and then 8 clocks for each register to read.
//--------------------------------------------------------------------------------
void ReadFromADXL345ViaSpi(unsigned char RegisterAddress, unsigned char NumberofRegisters, unsigned char *RegisterData)
{
	unsigned	char	ControlValue = 0;
	signed		char	RegisterIndex = 0;
	unsigned	char	ReceiveData = 0;
	unsigned	char	i = 0;
	unsigned	int		iTemp = 0;

	//Create the 8-bit header
	ControlValue = RegisterAddress;

//	SET_SCL();
//	delay(1);	
	SET_CS();
	SET_SCL();
	delay(3);
	CLR_CS();	 //bring CS low
	delay(3);

	CLR_SCL();
	SET_SDO();	 //set READ bit
	delay(3);
	SET_SCL();
	delay(3);
	ControlValue <<= 1;

	CLR_SCL();
	SET_SDO();	//set MB bit
	delay(3);
	SET_SCL();
	delay(3);
	ControlValue <<= 1;

	//Write out the control word
	for(i=0; i<6; i++)
	{
		CLR_SCL();
		if(0x80 == (ControlValue & 0x80))
		{
			SET_SDO();	  //Send one to SDO pin
		}
		else
		{
			CLR_SDO();	  //Send zero to SDO pin
		}
		delay(3);
		SET_SCL();
		delay(3);
		ControlValue <<= 1;	//Rotate data
	}

	//Read data in
	for (RegisterIndex=NumberofRegisters; RegisterIndex>0; RegisterIndex--)
	{
		for(i=0; i<8; i++)
		{
			CLR_SCL();
			ReceiveData <<= 1;		//Rotate data
			delay(3);
			SET_SCL();
			iTemp = GP1DAT;			//Read SDI of ADXL345
			if(0x00000020 == (iTemp & 0x00000020))			   //SDI  P1.5
			{
				ReceiveData |= 1;	
			}
			delay(2);
		}
		*(RegisterData + RegisterIndex - 1) = ReceiveData;
	}
	SET_CS();	//bring CS high again
} 

