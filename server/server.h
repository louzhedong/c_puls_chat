#ifndef SERVER_H
#define SERVER_H
#include <string>
#include <WinSock2.h>
#include "mesg.h"

using std::string;



class Svr{
	int iServerSock;  //监听函数socket
	int iClientSock;  //保存accept（）函数产生的socket
	struct sockaddr_in ServerAddr; //本机地址
	struct sockaddr_in ClientAddr; //用户地址
	int sin_size; //保存sockaddr_in 的大小
	WSADATA WSAData;	
public:
	Mesg* mesgs[10]; //用于完成用户请求的类数组
	int    total; //当前连接总数
    SOCKET socks[FD_SETSIZE]; //当前连接集合
	Svr();
	~Svr();
	int Svr_send();
	int Svr_recv();
	int Svr_bind();
	int Svr_listen();
	int Svr_accept();
};

#endif