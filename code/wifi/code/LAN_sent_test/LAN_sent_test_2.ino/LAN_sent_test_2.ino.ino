#include <uarlWIFI.h>
#include <WIFI.h>
WIFI wifi;
void setup(){
  Serial.begin(9600);
  wifi.confMux(0);
  wifi.Reset();
  delay(6000);
  wifi.newMux(UDP,"192.168.0.106",8081);
  Serial.println(wifi.showIP());
}
void loop(){
  if (Serial.available()!=0){
    Serial.println("got");
    wifi.Send("got");
    Serial.println("g000t");
    delay(1000);
  }
}
