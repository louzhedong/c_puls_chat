#include <string>
#include <WinSock2.h>
#include <iostream>
#include <vector>
#include "server.h"
#include "mesg.h"

#define PORT 2046
#define BACKLOG 20

using namespace std;

Svr::Svr(){
	if( WSAStartup( MAKEWORD( 1, 1 ), &WSAData ) ){
		cout<<"initializationing error!\n";
		WSACleanup( );
		exit( 0 );
	}
	if( ( iServerSock = socket( AF_INET, SOCK_STREAM, 0 ) ) == INVALID_SOCKET ){
		cout<<"�����׽���ʧ��!\n";
		WSACleanup( );
		exit( 0 );
	}
	total=0;
	sin_size = sizeof( struct sockaddr_in );
	ServerAddr.sin_family = AF_INET;
	ServerAddr.sin_port = htons( PORT );//���ӵĶ˿ں�
	ServerAddr.sin_addr.s_addr = INADDR_ANY;//����IP
	memset( & ( ServerAddr.sin_zero ), 0, sizeof( ServerAddr.sin_zero ) );//����
	mesgs[0]=new p_Mesg;
	mesgs[1]=new l_Mesg;
	mesgs[2]=new f_Mesg;
	mesgs[3]=new s_Mesg;
	mesgs[4]=new r_Mesg;
	mesgs[5]=new b_Mesg;
	mesgs[6]=new a_Mesg;
	mesgs[7]=new c_Mesg;
}

Svr::~Svr(){
	for(int i=0;i<10;i++){
		delete mesgs[i]; 
	}
}

int Svr::Svr_bind(){
	if( bind( iServerSock, ( struct sockaddr * )&ServerAddr, sizeof( struct sockaddr ) ) == -1 )	{
		cout<< "bind����ʧ��!\n" ;
		WSACleanup( );
		exit( 0 );
	}
	return 0;
}

int Svr::Svr_listen(){
	if( listen( iServerSock, BACKLOG ) == -1 ){
		cout<< "listen����ʧ��!\n" ;
		WSACleanup( );
		exit( 0 );
	}
	return 0;
}

int Svr::Svr_accept(){
	int flag=0;
	iClientSock = accept( iServerSock, ( struct sockaddr * )&ClientAddr, &sin_size );
	if( iClientSock == -1 ){
		printf( "accept����ʧ��!\n" );
		WSACleanup( );
		exit( 0 );
	}
	socks[total++]=iClientSock;
	cout<< "���������ӵ�:  "<<inet_ntoa( ClientAddr.sin_addr ) <<endl;
	cout<<"��ǰ����������  "<<total<<endl;
	return 0;
}


