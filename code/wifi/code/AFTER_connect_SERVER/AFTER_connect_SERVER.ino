#include<Servo.h>
#include<Wire.h>
int motor_pin[4] = {2,3,4,5};
Servo motor[4];
int Speed[4] = {0,0,0,0};
void setup(){
  Serial1.begin(9600);
  Serial.begin(9600);
  Serial1.println("AT+ShowSTA");
  String showSTA;
  while(1){
    if(Serial1.available()>0){
      char a = Serial1.read();
      showSTA+=a;
    }
    if(showSTA.indexOf("done")!=-1 || showSTA.indexOf("ERROR")!=-1){
      Serial1.read();
      Serial1.read();
      Serial.print(showSTA);
      break;
    }
  }
  delay(500);
///////////////////////////
  for(int i = 0 ; i < 4 ; i++ )
    motor[i].attach(motor_pin[i]);
///////////////////////////
  Serial.println("u can fly...");
}
void loop(){
  if(Serial1.available()>0){
    if((char)Serial1.read()=='+'){
      String get;
      while(1){
        int a=Serial1.read();
        if(a>=33 && a<=127)get+=(char)a;
        if(a==101)break;
      }
      for(int i = 0 ; i < 4; i++ ){
        Speed[i] += int( get[9 + 3*i ] - 48 );
        Speed[i] *= 10;
        Speed[i] += int( get[10 + 3*i ] - 48 );
        Speed[i] *=10;
        Speed[i] += int( get[11 + 3*i ] - 48 );
      }
      for(int i = 0 ; i < 4 ; i++ ){
        Serial.println(Speed[i]);
        motor[i].write(Speed[i]);
        Speed[i]=0;
      }
    }
  }
}
