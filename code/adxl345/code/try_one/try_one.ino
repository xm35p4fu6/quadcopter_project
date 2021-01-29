#include<Wire.h>
#include<ADXL345.h>

double standardAcceData[3]={0,0,9.8};

double currentAcceData[3];
ADXL345 adxl345;
void setup(){
 adxl345.powerOn();
 Serial.begin(9600);
}
void loop(){
  adxl345.get_Gxyz(currentAcceData);
  Serial.print(currentAcceData[0]);
  Serial.print(currentAcceData[1]);
  Serial.print(currentAcceData[2]);
  Serial.println("");
  delay(60);
}


