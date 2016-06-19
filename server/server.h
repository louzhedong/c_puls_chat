#ifndef SERVER_H
#define SERVER_H
#include <string>
#include <WinSock2.h>
#include "mesg.h"

using std::string;



class Svr{
	int iServerSock;  //��������socket
	int iClientSock;  //����accept��������������socket
	struct sockaddr_in ServerAddr; //������ַ
	struct sockaddr_in ClientAddr; //�û���ַ
	int sin_size; //����sockaddr_in �Ĵ�С
	WSADATA WSAData;	
public:
	Mesg* mesgs[10]; //��������û������������
	int    total; //��ǰ��������
    SOCKET socks[FD_SETSIZE]; //��ǰ���Ӽ���
	Svr();
	~Svr();
	int Svr_send();
	int Svr_recv();
	int Svr_bind();
	int Svr_listen();
	int Svr_accept();
};

#endif