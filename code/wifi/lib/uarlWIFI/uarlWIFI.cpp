#include <uarlWIFI.h>



WIFI::WIFI(void)
{

  Serial1.begin(9600);
  while (!Serial1)
  {
     //等待串口连接。只有 Leonardo 需要。
   }
   

}


//////////////////////////////////////////////////////////////////////////
//整合接口
bool WIFI::Initialize(byte a, String ssid, String pwd, byte chl, byte ecn)
{
	if (a == 1)
	{	
		bool b = confMode(a);
		if (!b)
		{
			return false;
		}
		Reset();
		confJAP(ssid, pwd);
	}
	else if (a == 2)
	{
		bool b = confMode(a);
		if (!b)
		{
			return false;
		}
		Reset();
		confSAP(ssid, pwd, chl, ecn);
	}
	else if (a == 3)
	{
		bool b = confMode(a);
		if (!b)
		{
			return false;
		}
		Reset();
		confJAP(ssid, pwd);
		confSAP(ssid, pwd, chl, ecn);
	}
	
	return true;
}

void WIFI::ipConfig(byte type, String addr, int port, boolean a, byte id)
{
	if (a == 0 )
	{
		confMux(a);
		long timeStart = millis();
		while (1)
		{
			long time0 = millis();
			if (time0 - timeStart > 5000)
			{
				break;
			}
		}
		newMux(type, addr, port);
	}
	else if (a == 1)
	{
		confMux(a);
		long timeStart = millis();
		while (1)
		{
			long time0 = millis();
			if (time0 - timeStart > 5000)
			{
				break;
			}
		}
		newMux(id, type, addr, port);
	}
}


int WIFI::ReceiveMessage(char *buf, int MsgLen)
{
	//+IPD:11,wifi read11
	//done
	String data = "";
	if (Serial1.available()>0)
	{
		//Serial.println(Serial1.available());
		char c0 = Serial1.read();
		if (c0 == '+')
		{
			while (1)
			{
				if (Serial1.available()>0)
				{
					char c = Serial1.read();
					data += c;
				}
				if (data.indexOf("done")!=-1)
				{
					break;
				}
			}
			//Serial.println(data);
			int sLen = strlen(data.c_str());
			int i;
			for (i = 0; i <= sLen; i++)
			{
				if (data[i] == ':')
				{
					break;
				}
				
			}
			String _size = data.substring(4, i);
			int iSize = _size.toInt();
			//Serial.println(_size);
			String str = data.substring(i+1, i+1+iSize);
			strcpy(buf, str.c_str());
			//Serial.println(str);
			return iSize;
		}
	}
	
	return 0;
}

//////////////////////////////////////////////////////////////////////////


/*===================================*/
/*
 * 重启wifi芯片
 *
 * */
/*===================================*/
void WIFI::Reset(void)
{
    Serial1.println("AT+Reset");
    while (1) {                            //当串口有完成数据返回时，结束语句
        if(Serial1.find("OCROBOT WIFI ready")==true)
        {
           break;
        }
    }
}

/*********************************************
 *********************************************
 *********************************************
                   WIFI功能指令
 *********************************************
 *********************************************
 *********************************************
 */

/*==============================*/
/*
 *
 * 查询目前wifi模块的工作模式
 * */
/*===============================*/
String WIFI::showMode()
{
    String data;
    Serial1.println("AT+MODE?");  //发送AT指令
    while (1) {
     if(Serial1.available()>0)
     {
     char a =Serial1.read();
     data=data+a;
     }
     if (data.indexOf("done")!=-1)
     {
         break;
     }
  }
    if(data.indexOf("1")!=-1)
    {
        return "Station";
    }else if(data.indexOf("2")!=-1)
    {
            return "AP";
    }else if(data.indexOf("3")!=-1)
    {
         return "AP+Station";
    }
}



/*================================*/
/*
 *
 * 配置WIFI模块的工作模式(需要重启后方可生效)(done)
 *
 * */
/*================================*/

bool WIFI::confMode(byte a)
{
    String data;
     Serial1.print("AT+MODE=");  //发送AT指令
     Serial1.println(String(a));
     while (1) {
      if(Serial1.available()>0)
      {
      char a =Serial1.read();
      data=data+a;
      }
      if (data.indexOf("done")!=-1 || data.indexOf("no change")!=-1)
      {
          return true;
      }
	  if (data.indexOf("error")!=-1 || data.indexOf("busy")!=-1)
	  {
		  return false;
	  }
	  
   }
}




/*===================================*/
/*
 * 返回（字符串）当前wifi搜索到的接入点信息(只能在)
 * 加密类型、SSID、信号强度
 * */
/*===================================*/
String WIFI::showAP(void)
{
    String data;
    Serial1.println("AT+ShowAP");  //发送AT指令
    while (1) {
   if(Serial1.available()>0)
   {
     char a =Serial1.read();
     data=data+a;
   }
     if (data.indexOf("done")!=-1 || data.indexOf("ERROR")!=-1 )
     {
         break;
     }
  }
    if(data.indexOf("ERROR")!=-1)
    {
        return "ERROR";
    }
    else{
       char head[4] = {0x0D,0x0A};   //头部多余字符串
       char tail[7] = {0x0D,0x0A,0x0D,0x0A};        //尾部多余字符串
       data.replace("AT+ShowAP","");
       data.replace("done","");
       data.replace("+ShowAP","WIFI");
       data.replace(head,"");
       data.replace(tail,"");
        return data;
        }
 }


/*===================================*/
/*
 * 查询返回目前连接的wifi接入点信息  （done）
 *
 **/
/*===================================*/
String WIFI::showJAP(void)
{
    Serial1.println("AT+JoinAP?");  //发送AT指令
      String data;
      while (1) {
       if(Serial1.available()>0)
       {
       char a =Serial1.read();
       data=data+a;
       }
       if (data.indexOf("done")!=-1 || data.indexOf("ERROR")!=-1 )
       {
           break;
       }
    }
      char head[4] = {0x0D,0x0A};   //头部多余字符串
      char tail[7] = {0x0D,0x0A,0x0D,0x0A};        //尾部多余字符串
      data.replace("AT+JoinAP?","");
      data.replace("+JoinAP","AP");
      data.replace("done","");
      data.replace(head,"");
      data.replace(tail,"");
          return data;
}
/*=======================================*/
/*
 * 配置登陆网络需要的ssid名称以及密码(未验证，未测试)
 *
 * */
/*=======================================*/
void WIFI::confJAP(String ssid , String pwd)
{
    Serial1.print("AT+JoinAP=");
    Serial1.print("\"");     //"ssid"
    Serial1.print(ssid);
    Serial1.print("\"");

    Serial1.print(",");

    Serial1.print("\"");      //"pwd"
    Serial1.print(pwd);
    Serial1.println("\"");


    while (1) {                            //当串口有完成数据返回时，结束语句
        if(Serial1.find("done")==true)
        {
           break;
        }
    }
}
/*=============================================*/
/*
 * 退出目前登录的wifi节点
 *
 * /
 /*============================================*/

void WIFI::quitAP(void)
{
    Serial1.println("AT+ExtAP");
    while (1) {                            //当串口有完成数据返回时，结束语句
        if(Serial1.find("done")==true)
        {
           break;
        }
    }

}

/*===============================================*/
/*
 *
 * AP模式下的网络配置
 *
 * */
/*==============================================*/
String WIFI::showSAP()
{
    Serial1.println("AT+SAP?");  //发送AT指令
      String data;
      while (1) {
       if(Serial1.available()>0)
       {
       char a =Serial1.read();
       data=data+a;
       }
       if (data.indexOf("done")!=-1 || data.indexOf("ERROR")!=-1 )
       {
           break;
       }
    }
      char head[4] = {0x0D,0x0A};   //头部多余字符串
      char tail[7] = {0x0D,0x0A,0x0D,0x0A};        //尾部多余字符串
      data.replace("AT+SAP?","");
      data.replace("+SAP","mySAP");
      data.replace("done","");
      data.replace(head,"");
      data.replace(tail,"");
          return data;
}

/*==============================================*/
/*
 *
 * 设置AP模式下的SSID 密码 信道 加密方式等信息  (只能用于ap模式或者ap+Station模式下，重启芯片后生效)
 *
 * /
 /*============================================*/

void WIFI::confSAP(String ssid , String pwd , byte chl , byte ecn)
{
    Serial1.print("AT+SAP=");  //发送AT指令
    Serial1.print("\"");     //"ssid"
    Serial1.print(ssid);
    Serial1.print("\"");

    Serial1.print(",");

    Serial1.print("\"");      //"pwd"
    Serial1.print(pwd);
    Serial1.print("\"");

    Serial1.print(",");
    Serial1.print(String(chl));

    Serial1.print(",");
    Serial1.println(String(ecn));
    while (1) {                            //当串口有完成数据返回时，结束语句
        if(Serial1.find("done")==true ||Serial1.find("ERROR")==true)
        {
           break;
        }
     }

}


/*********************************************
 *********************************************
 *********************************************
                   TPC/IP功能指令
 *********************************************
 *********************************************
 *********************************************
 */


/*==============================================*/
/*
 *
 * 获取目前的链接状态
 * <ID>  0-4
 * <type>  tcp or udp
 * <addr>  ip
 * <port>  port number
 * /
 /*============================================*/
String WIFI::showStatus(void)
{
    Serial1.println("AT+ShowSTA");  //发送AT指令
      String data;
      while (1) {
       if(Serial1.available()>0)
       {
       char a =Serial1.read();
       data=data+a;
       }
       if (data.indexOf("done")!=-1)
       {
           break;
       }
    }

          char head[4] = {0x0D,0x0A};   //头部多余字符串
          char tail[7] = {0x0D,0x0A,0x0D,0x0A};        //尾部多余字符串
          data.replace("AT+ShowSTA","");
          data.replace("done","");
          data.replace(head,"");
          data.replace(tail,"");
          return data;
}

/*============================================*/
/*
 * 查询目前的链接模式（单链接or多链接）
 * */
/*============================================*/
String WIFI::showMux(void)
{
    String data;
    Serial1.println("AT+MUX?");  //发送AT指令

      while (1) {
       if(Serial1.available()>0)
       {
       char a =Serial1.read();
       data=data+a;
       }
       if (data.indexOf("done")!=-1)
       {
           break;
       }
    }
          char head[3]={0x0D,0x0A};   //将回显数据处理成需要的格式
          data.replace("AT+MUX?","");
          data.replace("+MUX","showMux");
          data.replace("done","");
          data.replace(head,"");
          return data;
}

/*============================================*/
/*
 * 设置链接模式（单链接or多链接）
 * */
/*============================================*/
void WIFI::confMux(boolean a)
{
 Serial1.print("AT+MUX=");
 Serial1.println(a);           //发送AT指令
 while (1) {                            //当串口有完成数据返回时，结束语句
     if(Serial1.find("done")==true || Serial1.find("Link is builded")==true)
     {
        break;
     }
  }
}


/*============================================*/
/*
 * 建立tcp链接或者注册UDP端口号（单路模式）
 *
 * */
/*===========================================*/
void WIFI::newMux(byte type, String addr, int port)

{
    String data;
    Serial1.print("AT+NewSTA=");
    if(type>0)
    {
        Serial1.print("\"TCP\"");
    }else
    {
        Serial1.print("\"UDP\"");
    }
    Serial1.print(",");
    Serial1.print("\"");
    Serial1.print(addr);
    Serial1.print("\"");
    Serial1.print(",");
//    Serial1.print("\"");
    Serial1.println(String(port));
//    Serial1.println("\"");
    while (1) {
     if(Serial1.available()>0)
     {
     char a =Serial1.read();
     data=data+a;
     }
     if (data.indexOf("done")!=-1 || data.indexOf("ALREAY CONNECT")!=-1 || data.indexOf("ERROR")!=-1)
     {
         break;
     }
  }
}
/*============================================*/
/*
 * 建立tcp链接或者注册UDP端口号（多路模式）（0-4共计5路）
 *
 * */
/*===========================================*/
void WIFI::newMux( byte id, byte type, String addr, int port)

{

    Serial1.print("AT+NewSTA=");
    Serial1.print("\"");
    Serial1.print(String(id));
    Serial1.print("\"");
    if(type>0)
    {
        Serial1.print("\"tcp\"");
    }else
    {
        Serial1.print("\"UDP\"");
    }
    Serial1.print(",");
    Serial1.print("\"");
    Serial1.print(addr);
    Serial1.print("\"");
    Serial1.print(",");
//    Serial1.print("\"");
    Serial1.println(String(port));
//    Serial1.println("\"");
    String data;
    while (1) {

     if(Serial1.available()>0)
     {
     char a =Serial1.read();
     data=data+a;
     }
     if (data.indexOf("done")!=-1 || data.indexOf("ALREAY CONNECT")!=-1 || data.indexOf("ERROR")!=-1)
     {
         break;
     }
  }

}
/*==============================================*/
/*
 * 发送数据(单路模式)
 *
 * */
/*==============================================*/
void WIFI::Send(String str)
{
    Serial1.print("AT+UpDate=");
//    Serial1.print("\"");
    Serial1.println(str.length());
//    Serial1.println("\"");
    while (1) {                            //当串口有完成数据返回时，结束语句
        if(Serial1.find(">")==true )
        {
           break;
        }
     }
    Serial1.println(str);


    String data;
    while (1) {
     if(Serial1.available()>0)
     {
     char a =Serial1.read();
     data=data+a;
     }
     if (data.indexOf("SEND OK")!=-1)
     {
         break;
     }
  }
}

/*==============================================*/
/*
 * 发送数据(多路路模式)
 *
 * */
/*==============================================*/
void WIFI::Send(byte id, String str)
{
    Serial1.print("AT+UpDate=");

    Serial1.print(String(id));
    Serial1.println(",");
    Serial1.println(str.length());
    while (1) {                            //当串口有完成数据返回时，结束语句
        if(Serial1.find(">")==true )
        {
           break;
        }
     }
    Serial1.println(str);


    String data;
    while (1) {
     if(Serial1.available()>0)
     {
     char a =Serial1.read();
     data=data+a;
     }
     if (data.indexOf("SEND OK")!=-1)
     {
         break;
     }
  }
}

/*========================================*/
/*
 *
 * 关闭TCP或UDP链接（单路模式）
 *
 * *-*/
/*=======================================*/
void WIFI::closeMux(void)
{
    Serial1.println("AT+CLOSE");

    String data;
    while (1) {
     if(Serial1.available()>0)
     {
     char a =Serial1.read();
     data=data+a;
     }
     if (data.indexOf("Linked")!=-1 || data.indexOf("ERROR")!=-1 || data.indexOf("we must restart")!=-1)
     {
         break;
     }
  }
}


/*========================================*/
/*
 *
 * 关闭TCP或UDP链接（多路模式）
 *
 * *-*/
/*=======================================*/
void WIFI::closeMux(byte id)
{
    Serial1.print("AT+CLOSE=");
    Serial1.println(String(id));
    String data;
    while (1) {
     if(Serial1.available()>0)
     {
     char a =Serial1.read();
     data=data+a;
     }
     if (data.indexOf("done")!=-1 || data.indexOf("Link is not")!=-1 || data.indexOf("Cant close")!=-1)
     {
         break;
     }
  }

}

/*=========================================*/
/*
 * 获取目前的本机IP地址
 * */
/*=========================================*/
String WIFI::showIP(void)
{
    Serial1.println("AT+ShowIP");  //发送AT指令
    String data;
    while (1) {
     if(Serial1.available()>0)
     {
     char a =Serial1.read();
     data=data+a;
     }
     if (data.indexOf("done")!=-1)
     {
         break;
     }
  }
    return data;
}

/*=======================================*/
/*
 *
 * 配置为服务器
 *
*/
/*=======================================*/

void WIFI::confServer(byte mode, int port)
{
    Serial1.print("AT+Server=");  //发送AT指令
    Serial1.print(String(mode));
    Serial1.print(",");
    Serial1.println(String(port));

    String data;
    while (1) {
     if(Serial1.available()>0)
     {
     char a =Serial1.read();
     data=data+a;
     }
     if (data.indexOf("done")!=-1 || data.indexOf("Link is builded")!=-1)
     {
         break;
     }
  }
}
