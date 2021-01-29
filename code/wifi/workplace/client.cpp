#include <iostream>
#include <WInSock2.h>
#include <string>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	string confirm,add_ip,test="pig";
	int add_port;
    char message[200];
 	string sendbuf;

    //開始 Winsock-DLL
    int r;
    WSAData wsaData;
    WORD DLLVersion;
    DLLVersion = MAKEWORD(2,2);
    r = WSAStartup(DLLVersion, &wsaData);

    //宣告給 socket 使用的 sockadder_in 結構
    SOCKADDR_IN addr;

    int addlen = sizeof(addr);

    //設定 socket
    SOCKET sConnect;

    //AF_INET: internet-family
    //SOCKET_STREAM: connection-oriented socket
    sConnect = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);

 	cout<<"IP 和 port: "<<endl;
 	cin>>add_ip>>add_port;

    //設定 addr 資料
    addr.sin_addr.s_addr = inet_addr(add_ip.c_str());
    addr.sin_family = AF_INET;
    addr.sin_port = htons(add_port);

    cout << "connect to server?[Y] or [N]" << endl;
    cin >> confirm;

    if(confirm == "N")
    {
        exit(1);
    }else{
        if(confirm == "Y")
        {
            connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));

 			while(true){
 				if(cin>>sendbuf){
                    if(sendbuf=="0"){
                        sendbuf="000000000000";
                        const char *Sendbuf=sendbuf.c_str();
                        send(sConnect,Sendbuf,(int)strlen(Sendbuf), 0);
                        sendbuf="";
                    }
 					else{
                        const char *Sendbuf=sendbuf.c_str();
                        send(sConnect,Sendbuf,(int)strlen(Sendbuf), 0);
                        sendbuf="";
 					}
 				}
			 }

            //接收 server 端的訊息

        }
    }

	return 0;
}
