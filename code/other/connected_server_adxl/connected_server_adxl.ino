#include<Servo.h>
#include<Wire.h>
#include<ADXL345.h>

int motor_pin[4] = {2,3,4,5};
Servo motor[4];
int Speed[4] = {0,0,0,0};

double standardAcceData[3] = {0,0,0.89};  //sensors data ADXL
double currentAcceData[3] ;
ADXL345 adxl345;

double errorX , errorY , tFix[4] = {0,0,0,0} ;  //PID
double Kp = 20 , Ki = 1.5 , Kd = 10 ; 

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
  adxl345.powerOn();
///////////////////////////
  Serial.println("u can fly...");
}
void loop(){
  get_inSpeed();
  while(Speed[0] == 0 && Speed[1] == 0 && Speed[2] == 0 && Speed[3] == 0){
    for(int j=0;j<4;j++){
      motor[j].write(25);
      //Serial.println("here");
    }
    get_inSpeed();
  }
  get_AcceData();
  calculatePID();
  send_motor();
}


void get_inSpeed(){
  if(Serial1.available()>0){
    if((char)Serial1.read()=='+'){
      String get;
      while(1){
        int a=Serial1.read();
        if(a>=33 && a<=127)get+=(char)a;
        if(a==101)break;
      }
      for(int i = 0 ; i < 4; i++ ){
        Speed[i] = 0;
        Speed[i] += int( get[9 + 3*i ] - 48 );
        Speed[i] *= 10;
        Speed[i] += int( get[10 + 3*i ] - 48 );
        Speed[i] *=10;
        Speed[i] += int( get[11 + 3*i ] - 48 );
      }
    }
  }
}

void get_AcceData(){
  adxl345.get_Gxyz(currentAcceData);
}

void calculatePID(){
  for(int i=0;i<4;i++){
    tFix[i]=0;
  }
  // caculata error
  errorX = currentAcceData[0] - standardAcceData[0];
  errorY = currentAcceData[1] - standardAcceData[1];
  
  //P (X axis)
  tFix[0] -= Kp * errorX;
  tFix[2] += Kp * errorX;
  //P (Y axis)
  tFix[1] -= Kp * errorY;
  tFix[3] += Kp * errorY;
}

void send_motor(){
  for(int i=0;i<4;i++){
    int fix = (int)tFix[i];
    int f = Speed[i] + fix ;
    motor[i].write(f);
    //Serial.print(f);
  }
}
