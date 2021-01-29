/*
当自身设为局域网server端时接入时候的加密方式
#define    OPEN          0
#define    WEP           1
#define    WAP_PSK       2
#define    WAP2_PSK      3
#define    WAP_WAP2_PSK  4

WIFI初始化的类型 
STA接入局域网 AP自身为局域网server端 
#define    STA     1
#define    AP      2
#define    AT_STA  3

通信方式 
#define    TCP     1
#define    tcp     1
#define    UDP     0
#define    udp     0

参数：网络方式  SSID PASSWORD   
如果网络方式选择AP模式  最后两个参数可选择填写  默认通道1 加密方式2
bool Initialize(byte a, String ssid, String pwd, byte chl = 1, byte ecn = 2);

参数：通信方式  对方ip 对方端口
默认单对单通信boolean为0  如果改为1  可以分配ID 0~4
0号可以连接客户端和服务器，其他只能连接服务器
void ipConfig(byte type, String addr, int port, boolean a = 0, byte id = 0);

参数：接收buf 未开发参数（保留）
返回接收到的buf的长度
int ReceiveMessage(char *buf, int MsgLen = 0);

例程编写 && 库函数整合
by .oο麽麽茶㊣ (你们好屌)
2014/9/18

*/

#include <uarlWIFI.h>
WIFI wifi;
void setup()
{
  Serial.begin(9600);
  bool b = wifi.Initialize(STA, "SSID", "PASSWORD");
  if(!b)
  {
    Serial.println("Init error");
  }
  wifi.ipConfig(UDP, "192.168.0.103", 60000);
  Serial.println("setup done..");
  wifi.Send("setup done..");
}
void loop()
{
  //定一个接收消息用的buffer
  char buf[1024];
  int iLen = wifi.ReceiveMessage(buf);
  if(iLen > 0)
  {
    //判断buf是否为规定字符串
    if (strcmp(buf, "HIGH") == 0)
    {
      digitalWrite(13, HIGH);
    }
    else if (strcmp(buf, "LOW") == 0)
    {
      digitalWrite(13, LOW);
    }
  }
}
