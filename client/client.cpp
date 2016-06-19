#include <WinSock2.h>
#include <iostream>
#include "process.h"

#pragma comment(lib,"ws2_32.lib")

using namespace std;

#define PORT 2046
#define BACKLOG 10


int uchoose;
void menu(const int &iClientSock);

void main()
{
	int id,key;
	int iClientSock;
	struct sockaddr_in ServerAddr;
	int numbytes;

	WSADATA WSAData;
	if( WSAStartup( MAKEWORD( 1, 1 ), &WSAData ) ){
		printf( "initializationing error!\n" );
		WSACleanup( );
		exit( 0 );
	}
	if( ( iClientSock = socket( AF_INET, SOCK_STREAM, 0 ) ) == INVALID_SOCKET ){
		printf( "创建套接字失败!\n" );
		WSACleanup( );
		exit( 0 );
	}
    ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons( PORT );
	ServerAddr.sin_addr.s_addr = inet_addr( "127.0.0.1" );
	memset( &( ServerAddr.sin_zero ), 0, sizeof( ServerAddr.sin_zero ) );
    if( connect( iClientSock, ( struct sockaddr * ) & ServerAddr, sizeof( struct sockaddr ) ) == -1 ){
		printf( "connect失败!" );
		WSACleanup( );
		exit( 0 );
	}

	while(1){
		menu(iClientSock);
	}

}

void menu(const int &iClientSock){
	cout<<"请选择："<<endl<<"1.账号登陆"<<endl<<"2.发送用户消息"<<endl<<"3.查看好友"<<endl<<"4.查看资料"<<endl<<"5.修改密码"<<endl<<"6.添加好友"<<endl<<"7.加入聊天室"<<endl<<"8.发送聊天室消息"<<endl<<"9.接收消息"<<endl<<"0.退出"<<endl;
	cin>>uchoose;
	switch(uchoose){
	case 1:
		l_pro(iClientSock);
		break;
	case 2: 
		p_pro(iClientSock);
		break;
	case 3:
		f_pro(iClientSock);
		break;
	case 4:
		s_pro(iClientSock);
		break;
	case 5:
		c_pro(iClientSock);
		break;
	case 6: 
		a_pro(iClientSock);
		break;
	case 7: 
		r_pro(iClientSock);
		break;
	case 8: 
		b_pro(iClientSock);
		break;
	case 9:
		e_pro(iClientSock);
		break;
	case 0:
		closesocket( iClientSock );
	    WSACleanup( );
		exit(0);
	default:
		break;
	}
}