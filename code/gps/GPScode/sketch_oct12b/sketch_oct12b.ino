#include<SoftwareSerial.h>
SoftwareSerial mySerial(3, 4); // 設定Arduino板子上RX,TX
void setup()  
{ 
  Serial.begin(9600); //COMPORT鮑率
  mySerial.begin(9600);//GPS
}
 
void loop() // run over and over
{
  if (mySerial.available())
    Serial.write(mySerial.read()); 
                                  
  if (Serial.available())         
    mySerial.write(Serial.read()); 
}
