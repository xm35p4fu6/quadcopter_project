//用mega版 有2個serial
//模擬"板子"送AT指令給 esp8266
void setup(){
  Serial.begin(9600);
  Serial1.begin(9600);
  Serial.println("tset");
}
void loop(){
    String str,ROOT;
    delay(500);
    while (Serial.available()>0){ 
        str=(String)Serial.read();
        while(str=="ROOT"){           //要板子送指令前 先輸入root
          if (Serial.available()>0){  //輸入完root 輸入你要板子給他的AT command
              ROOT=(String)Serial.read();
              if(ROOT="TOOR"){        //輸入TOOR 離開(輸入ROOT再次進入)
                Serial.println("exit");
                break;
              }
              Serial1.println(ROOT);  //若不是TOOR，則把你輸入的東西丟給exp8266
              if(Serial1.available()>0){
                Serial.print(Serial1.read()); //esp8266噴出的東西全部回傳
              }
            }
        }
    }
}
