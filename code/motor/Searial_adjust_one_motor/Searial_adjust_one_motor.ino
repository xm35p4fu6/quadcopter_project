#include <Servo.h>
 
// 支援 PWM 的 pin 腳
int motor_pin = 2;

// 四個馬達
Servo motor;
 
// 四個油門（出力）
int throttle_in=0;
// Arduino 初始化
void setup()
{
  Serial.begin(9600);
  motor.attach(motor_pin);
}
void loop(){
  Serial.println("speed:  \n");
  while(Serial.available()==0);
  throttle_in = Serial.parseInt();
  motor.write(throttle_in);
}
