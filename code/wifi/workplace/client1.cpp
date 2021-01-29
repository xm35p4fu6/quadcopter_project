#include <iostream>
#include <WInSock2.h>
#include <string>
using namespace std;
/* run this program using the console pauser or add your own getch, system("pause") or input loop */

string sendsave;
void sendServer(string sendbuf, SOCKET sConnect);

int main(int argc, char** argv) {
	string confirm="", add_ip="",test="pig";
	int add_port;
    char message[200];
 	string sendbuf="";

    //開始 Winsock-DLL
    int r;
    WSAData wsaData;
    WORD DLLVersion;
    DLLVersion = MAKEWORD(2,2);
    r = WSAStartup(DLLVersion, &wsaData);

    //宣告給 socket 使用的 sockadder_in 結構
    SOCKADDR_IN addr;

    int addlen = sizeof(addr), lensb;

    //設定 socket
    SOCKET sConnect;

    //AF_INET: internet-family
    //SOCKET_STREAM: connection-oriented socket
    sConnect = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);

    //cout<<"IP 和 port: "<<endl;
   	//cin>>add_ip>>add_port;
    add_ip="192.168.4.1";
    add_port=31304;
             //預設

    //設定 addr 資料
    addr.sin_addr.s_addr = inet_addr(add_ip.c_str());
    addr.sin_family = AF_INET;
    addr.sin_port = htons(add_port);

    cout << "connect to server?[Y] or [N]" << endl;
    cin >> confirm;

    if(confirm == "N")exit(1);
    else{
        if(confirm == "Y")
        {
            connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));

           system("cls");

            cout << "~~~~~~歡迎~~~~~~"<<endl<<endl;
            cout <<"0  緊急停止馬達"<<endl
                     <<"re  重新取得連線(閒置時斷線)"<<endl
                     <<"-1  油門低位"<<endl<<endl;
             system("pause");
             system("cls");
             system("color 70");
             cout << "~~~~轉速控制~~~~"<<endl<<endl
                      << "驅動轉速為 :  029" <<endl
                      << "最低轉速為 :  027" <<endl
                      << "最高轉速為 :  180" <<endl<<endl
                      << "轉速務必補齊3位數!!!!"<<endl
                      << "輸入 三位數 : 全部馬達轉速統一 ex: 120"<<endl
                      << "輸入 四位數 : 更改指定馬達轉速 ex : 3120 第三顆馬達轉速=12)"<<endl
                      << "輸入 十二位數 : 依序設定所有馬達轉速 ex : 110110150150"<<endl;
 			     while(true){
                        if(cin>>sendbuf){
                            lensb=sendbuf.length();
                            if(sendbuf=="0"){
                                //停
                                sendbuf="000000000000";
                                sendServer(sendbuf, sConnect);
                            }
                            else if(sendbuf=="-1"){
                                //低位
                                sendbuf="111222333444";
                                sendServer(sendbuf, sConnect);
                            }
                            else if(sendbuf=="re"){
                                //重連結
                                connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
                                break;
                            }
                            else if(sendbuf=="?"){
                                //查詢
                                system("cls");
                                cout<<"::::目前馬達::::"<<endl;
                                for(int i=0;i<4;i++){
                                    cout<<":::第"<<(i+1)<<"顆: "<<sendsave[i*3]<<sendsave[i*3+1]<<sendsave[i*3+2]<<":::"<<endl;
                                }
                                cout<<"::::::::::::::::"<<endl;
                            }
                            else{
                                switch(lensb){
                                    case 3:                //油門
                                        sendbuf+=sendbuf;
                                        sendbuf+=sendbuf;
                                        sendServer(sendbuf, sConnect);
                                        break;

                                    case 4:{
                                        int t = int(sendbuf[0]-48);
                                        int startchange = (t-1)*3;
                                        sendsave[startchange+0]=sendbuf[1];
                                        sendsave[startchange+1]=sendbuf[2];
                                        sendsave[startchange+2]=sendbuf[3];
                                        sendbuf=sendsave;
                                        sendServer(sendbuf, sConnect);
                                        break;
                                    }

                                    case 12:
                                        sendServer(sendbuf, sConnect);
                                        break;

                                    fault:
                                        cout<<endl<<"!!錯誤格式!!"<<endl;
                                }
 				            }
 				       }
 			     }
 			     //接收 server 端的訊息
        }
    }
	return 0;
}

void sendServer(string sendbuf, SOCKET sConnect){
    const char *Sendbuf=sendbuf.c_str();
    send(sConnect,Sendbuf,(int)strlen(Sendbuf), 0);
    sendsave = sendbuf;
    sendbuf="";
}
