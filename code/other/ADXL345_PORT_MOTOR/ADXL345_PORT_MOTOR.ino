/*
1.
MUX:0 單鏈 / 1 雙鏈 (int)

2.
UDP/TCP(String) ， "IP位址"(String)， 端口(int)
*/
#include<Servo.h>
#include<Wire.h>
#include<ADXL345.h>
unsigned long time_setup;
////////////MOTOR///////////////
int motor_pin[4] = {2,3,4,5};
Servo motor[4];
int throttle_in=0;
///////////ADXL345///////////////
const float alpha = 0.5;

double fXg = 0;
double fYg = 0;
double fZg = 0;

ADXL345 acc;

void setup(){
  pinMode(13,OUTPUT);
  acc.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
  while(!Serial1);
  Serial1.println("AT+JoinAP?");
  String data;
  while(1){
    if(Serial1.available()>0){
      char a = Serial1.read();
      data+=a;
    }
    if(data.indexOf("done")!=-1 || data.indexOf("ERROR")!=-1)break;
  }
  //Data processing
  char head[4] = {0x0D,0x0A};
  char tail[7] = {0x0D,0x0A,0x0D,0x0A};
  data.replace("AT+JoinAP?","");
  data.replace("+JoinAP:","wifi : ");
  data.replace("done","");
  data.replace(head,"");
  data.replace(tail,"");
  Serial.println(data);
  Serial.println("set MUX : 0 / 1 ");
  while(Serial1.available()>0){
    Serial1.read();
    delay(1);
  }
  while(1){
    if(Serial.available()>0){
      char a = Serial.read();
      Serial1.println("AT+MUX="+(String)a);
      Serial.println("sent : AT+MUX="+(String)a);
    }
    if(Serial1.available()>0){
      char a = Serial1.read();
      if (a == 'e')break;      //done
    }
  }
  Serial.print("U/T : ");
  String data_U_T;
  while(1){
    if(Serial.available()>0){
      char a = Serial.read();
      switch(a){
      case 'U':
        data_U_T="UDP";
        break;
      case 'T':
        data_U_T="TCP";
        break;
      default:
        Serial.println("UorT");
      }
      break;
    }
  }
  Serial.println(data_U_T);
  Serial.print("IP : ");
  String data_IP;
  while(1){
    if(Serial.available()>0){
      char a = Serial.read();
      data_IP+=(String)a;
      delay(1);
      if(Serial.available()==0)break;
    }
  }
  Serial.println(data_IP);
  Serial.print("port : ");
  String data_port;
  while(1){
    if(Serial.available()>0){
      char a = Serial.read();
      data_port+=a;
      delay(1);
      if(Serial.available()==0)break;
    }
  }
  Serial.println(data_port);
  Serial.println("SENT :AT+NewSTA=\"" + data_U_T + "\",\"" + data_IP + 
                 "\"," + data_port );
  Serial1.println("AT+NewSTA=\"" + data_U_T + "\",\"" + data_IP + 
                 "\"," + data_port );
  while(1){
    delay(1);
    //Serial.print(".");          //
    if(Serial1.available()>0){
      char a = Serial1.read();
      Serial.print(a);              //
      delay(1);
      if(Serial1.available()==0){
        Serial1.println("AT+UpDate=10");
        while(1){
          if(Serial1.available()>0){
            Serial1.println("0123456789");
            while(1){
              if(Serial1.available()>0){
                //Serial.print(",");
                char b = Serial1.read();
                Serial.print(b);
                if(b=='K')break;            //SEND OK
              }
            }
            break;
          }
        }
        Serial.println("Done and sent 'test' to the port. ");
        break;
      }
    }
  }
  while(Serial.available()>0){
    Serial.read();
    delay(1000);
  }
  while(Serial1.available()>0){
    Serial1.read();
    delay(1000);
  }
  Serial.println("WIFI OK.");
  ////////////////////////
  for(int i = 0 ; i < 4 ; i++ )
    motor[i].attach(motor_pin[i]);
  Serial.println("START");
  time_setup=millis();
  
}
//////////////////
//////////////////
//////////////////
//////////////////
//////////////////
void loop(){
  /*冒號前 往後讀*/
  if(Serial1.available()>0){
    if((char)Serial1.read()=='+'){    //確認接收
      String get;
      while(1){
        int a=Serial1.read();
        if(a==101)break;
        if(a>=33 && a<=127)
        get+=(char)a;
      }
      //提出
      //Serial.println("\n\n");
      //Serial.println(get);
      int len=get[4]-48;  //before ':'，ascii char to int
      throttle_in=0;
      for(int i = 6 ; i<(6+len) ; i++){
        throttle_in*=10;
        //Serial.print(throttle_in);
        throttle_in+=int(get[i]-48);
        //Serial.println(throttle_in);
      }
      Serial.println(throttle_in);
      /*~get~*/
    }
    for(int i = 0 ; i<4 ; i++ )
    motor[i].write(throttle_in);
  }
  ////////////ADXL345return//////////////
  unsigned long time_here=millis()-time_setup;
  if(time_here%500==0){
    double pitch , roll , Xg , Yg , Zg;
    acc.read(&Xg,&Yg,&Zg);
    fXg = Xg * alpha + (fXg * (1.0 - alpha));
    fYg = Yg * alpha + (fYg * (1.0 - alpha));
    fZg = Zg * alpha + (fZg * (1.0 - alpha));
    roll  = (atan2(-fYg, fZg)*180.0)/M_PI;
    pitch = (atan2(fXg, sqrt(fYg*fYg + fZg*fZg))*180.0)/M_PI;
    int Ipitch=int(pitch+0.5);
    int Iroll=int(roll+0.5);
    String p= Ipitch +(String)" " + Iroll +(String)" "+ (String)Zg;
    Serial1.print("AT+UpDate=");
    Serial1.println(p.length());
    while(1){
          if(Serial1.available()>0){
            Serial1.println(p);
            while(1){
              if(Serial1.available()>0){
                //Serial.print(",");
                char b = Serial1.read();
                if(b=='K'){
                  Serial1.read();
                  Serial1.read();
                  break;            //SEND OK
                }
              }
            }
            break;
          }
        }
    }
}
