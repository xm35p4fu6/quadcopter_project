#include <uarlWIFI.h>
WIFI wifi;
void setup() {
 wifi.confMux(0);       //切换模块到单链接通讯模式
 wifi.Reset();           //切换模式必须重启后生效
 delay(5000);          //重启后一定要给足够的时间让模块获取IP
 wifi.newMux(UDP,"192.168.0.102",8080);    //建立一个连接 UPD 到我的电脑的8080端口 
 wifi.Send("hello Intelnet~!");                       //发送字符
 delay(1000);                                                   //等一会
 wifi.Send("My name is miniqiang");                //接着发字符
 
}
void loop() {
 
}
