
/*
新添加 整合接口
Initialize
ipConfig

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

#ifndef __UARLWIFI_H__
#define __UARLWIFI_H__
#include <Arduino.h>
//#include "NilRTOS.h"


#define    OPEN          0
#define    WEP           1
#define    WAP_PSK       2
#define    WAP2_PSK      3
#define    WAP_WAP2_PSK  4

#define    TCP     1
#define    tcp     1
#define    UDP     0
#define    udp     0

#define    OPEN    1
#define    CLOSE   0

#define    STA     1
#define    AP      2
#define    AT_STA  3

#define SERIAL_TX_BUFFER_SIZE 128
#define SERIAL_RX_BUFFER_SIZE 128

class WIFI
{
  public:

    WIFI(void);
	
	//整合接口
	bool Initialize(byte a, String ssid, String pwd, byte chl = 1, byte ecn = 2);
	void ipConfig(byte type, String addr, int port, boolean a = 0, byte id = 0);
	
	void Send(String str);  //单路模式发送数据
	void Send(byte id, String str);  //多路模式发送数据
		
	int ReceiveMessage(char *buf, int MsgLen = 0);
	
    //String begin(void);
    /*=================WIFI功能指令=================*/
    void Reset(void);    //重启模块
	bool confMode(byte a);   //设置模块的模式
	void confJAP(String ssid , String pwd);    //配置登陆wifi接入点
	void confSAP(String ssid , String pwd , byte chl , byte ecn);       //配置ap模式下的网络参数 ssid 密码 通道号 以及加密方式	
	
    String showMode(void);   //查询模块目前模式
    String showAP(void);   //返回wifi列表
    String showJAP(void);  //返回目前连接的wifi接入点信息
    void quitAP(void);    //退出当前wifi连接
    String showSAP(void);     //显示ap模式下的模块的ssid 密码 通道号 以及加密方式

    /*================TCP/IP指令================*/
    String showStatus(void);    //查询链接状态
    String showMux(void);       //查询目前的链接模式（单链接or多链接）
    void confMux(boolean a);    //设置链接模式（单链接【0】or多链接【1】）
    void newMux(byte type, String addr, int port);   //创建 tcp或者udp链接（单路模式)
    void newMux(byte id, byte type, String addr, int port);   //创建 tcp或者udp链接（多路模式)（id:0-4） 0号可以连接客户端和服务器，其他只能连接服务器
    void closeMux(void);   //关闭tcp或udp （单路模式）
    void closeMux(byte id); //关闭tcp货udp （多路模式）
    String showIP(void);    //显示本机目前获取的ip地址
    void confServer(byte mode, int port);  //配置服务器
	
	String m_rev;

};

#endif
