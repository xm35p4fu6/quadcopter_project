/*Join wifi AP*/
#include <uarlWIFI.h>
WIFI wifi;
void setup() {
  Serial.begin(9600);
  delay(2000);
  wifi.confMode(STA);  // STA or  AP or  AP+STA   选择STA模式，也就是客户端模式，简单的说就是作为网卡来用  AP就是自己作为热点
  wifi.Reset();     //reboot wifi Modules
 wifi.confJAP("godbestyou","23919087");   //这里填写你要加入的网络热点名与密码，如果是没有密码的也乱写一个写满8位，注意千万别写错了，不会提示的，你会很难排查。
 delay(5000);                       //等待5秒钟时间，让路由器给你分配IP
   Serial.println(wifi.showIP());  // 串口显示获取到的IP，如果正常显示，说明登录网络成功了，如果不显示，需要检查SSID和密码是否写错了
}
void loop() {
 
}
