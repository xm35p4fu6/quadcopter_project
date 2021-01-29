#include <iostream>
#include <WinSock2.h>
using namespace std;

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	int r;
    WSAData wsaData;
    WORD DLLVSERION;
    DLLVSERION = MAKEWORD(2,1);//Winsocket-DLL ����
 
    //�� WSAStartup �}�l Winsocket-DLL
    r = WSAStartup(DLLVSERION, &wsaData);
 
    //�ŧi socket ��}��T(���P���q�T,�����P����}��T,�ҥH�|�����P����Ƶ��c�s��o�Ǧ�}��T)
    SOCKADDR_IN addr;
    int addrlen = sizeof(addr);
 
    //�إ� socket
    SOCKET sListen; //listening for an incoming connection
    SOCKET sConnect; //operating if a connection was found
 
    //AF_INET�G��ܫإߪ� socket �ݩ� internet family
    //SOCK_STREAM�G��ܫإߪ� socket �O connection-oriented socket 
    sConnect = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
 
    //�]�w��}��T�����
    addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    addr.sin_family = AF_INET;
    addr.sin_port = htons(1234);
 
    //�]�w Listen
    sListen = socket(AF_INET, SOCK_STREAM,IPPROTO_TCP);
    bind(sListen, (SOCKADDR*)&addr, sizeof(addr));
    listen(sListen, SOMAXCONN);//SOMAXCONN: listening without any limit
 
    //���ݳs�u
    SOCKADDR_IN clinetAddr;
    while(true)
    {
        cout << "waiting..." << endl;
 
        if(sConnect = accept(sListen, (SOCKADDR*)&clinetAddr, &addrlen))
        {
            cout << "a connection was found" << endl;
            printf("server: got connection from %s\n", inet_ntoa(addr.sin_addr));
 
            //�ǰe�T���� client ��
            const char *sendbuf = "sending data test";
            send(sConnect, sendbuf, (int)strlen(sendbuf), 0);
             
        }
    }
 
    //getchar();
	return 0;
}
