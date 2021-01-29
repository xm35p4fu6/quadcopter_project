#include <Servo.h>
 
// 支援 PWM 的 pin 腳
int motor_pin[4] = {2,3,4,5};

// 四個馬達
Servo motor[4];
 
// 四個油門（出力）
int throttle_in=0;
// Arduino 初始化
void setup()
{
  Serial.begin(9600);
  for(int i = 0; i<4; i++)
  motor[i].attach(motor_pin[i]);
}
void loop(){
  Serial.println("speed:  \n");
  while(Serial.available()==0);
  throttle_in = Serial.parseInt();
  for(int i = 0 ; i<4 ; i++ )
  motor[i].write(throttle_in);
}
