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

    //�}�l Winsock-DLL
    int r;
    WSAData wsaData;
    WORD DLLVersion;
    DLLVersion = MAKEWORD(2,2);
    r = WSAStartup(DLLVersion, &wsaData);

    //�ŧi�� socket �ϥΪ� sockadder_in ���c
    SOCKADDR_IN addr;

    int addlen = sizeof(addr), lensb;

    //�]�w socket
    SOCKET sConnect;

    //AF_INET: internet-family
    //SOCKET_STREAM: connection-oriented socket
    sConnect = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);

    //cout<<"IP �M port: "<<endl;
   	//cin>>add_ip>>add_port;
    add_ip="192.168.4.1";
    add_port=31304;
             //�w�]

    //�]�w addr ���
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

            cout << "~~~~~~�w��~~~~~~"<<endl<<endl;
            cout <<"0  ��氱��F"<<endl
                     <<"re  ���s���o�s�u(���m���_�u)"<<endl
                     <<"-1  �o���C��"<<endl<<endl;
             system("pause");
             system("cls");
             system("color 70");
             cout << "~~~~��t����~~~~"<<endl<<endl
                      << "�X����t�� :  029" <<endl
                      << "�̧C��t�� :  027" <<endl
                      << "�̰���t�� :  180" <<endl<<endl
                      << "��t�ȥ��ɻ�3���!!!!"<<endl
                      << "��J �T��� : �������F��t�Τ@ ex: 120"<<endl
                      << "��J �|��� : �����w���F��t ex : 3120 �ĤT�����F��t=12)"<<endl
                      << "��J �Q�G��� : �̧ǳ]�w�Ҧ����F��t ex : 110110150150"<<endl;
 			     while(true){
                        if(cin>>sendbuf){
                            lensb=sendbuf.length();
                            if(sendbuf=="0"){
                                //��
                                sendbuf="000000000000";
                                sendServer(sendbuf, sConnect);
                            }
                            else if(sendbuf=="-1"){
                                //�C��
                                sendbuf="111222333444";
                                sendServer(sendbuf, sConnect);
                            }
                            else if(sendbuf=="re"){
                                //���s��
                                connect(sConnect, (SOCKADDR*)&addr, sizeof(addr));
                                break;
                            }
                            else if(sendbuf=="?"){
                                //�d��
                                system("cls");
                                cout<<"::::�ثe���F::::"<<endl;
                                for(int i=0;i<4;i++){
                                    cout<<":::��"<<(i+1)<<"��: "<<sendsave[i*3]<<sendsave[i*3+1]<<sendsave[i*3+2]<<":::"<<endl;
                                }
                                cout<<"::::::::::::::::"<<endl;
                            }
                            else{
                                switch(lensb){
                                    case 3:                //�o��
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
                                        cout<<endl<<"!!���~�榡!!"<<endl;
                                }
 				            }
 				       }
 			     }
 			     //���� server �ݪ��T��
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
