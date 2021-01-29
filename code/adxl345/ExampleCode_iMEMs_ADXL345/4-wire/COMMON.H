#define SET_CS()		GP2DAT = (GP2DAT | 0x00800000)	//P2.7->/CS
#define CLR_CS()		GP2DAT = (GP2DAT & 0xFF7FFFFF)

#define	SET_SCL()		GP1DAT = (GP1DAT | 0x00100000)	//P1.4->SCLK
#define	CLR_SCL()		GP1DAT = (GP1DAT & 0xffEFffff)

#define SET_SDO()		GP1DAT = (GP1DAT | 0x00400000)	//P1.6->SDO
#define CLR_SDO()		GP1DAT = (GP1DAT & 0xffBFffff)




void delay (int length);


void WriteToADXL345ViaSpi(unsigned char RegisterAddress, unsigned char NumberofRegisters, unsigned char *RegisterData);
void ReadFromADXL345ViaSpi(unsigned char RegisterAddress, unsigned char NumberofRegisters, unsigned char *RegisterData);
void putchar(unsigned char ch);

