#include "process.h"
#include <WinSock2.h>
#include <iostream>
#include <fstream>

using namespace std;

const int bufsize=80;

void l_pro(const int &iClientSock){
	int id,key;
	int bytes;
	char choose='l';
	char buf[bufsize];
	send( iClientSock, &choose, 1, 0);
	cout<<"�������˺ţ�"<<endl;
	cin>>id;
	itoa(id,buf,10);
	send( iClientSock, buf, strlen( buf ),0 );
	cout<<"���������룺"<<endl;
	cin>>key;
	itoa(key,buf,10);	  
	send( iClientSock, buf, strlen( buf), 0 );
	bytes= recv( iClientSock, buf, bufsize, 0 );
    buf[ bytes ] = '\0';
	cout<<buf<<endl;
	return;
}

void p_pro(const int &iClientSock){
	int id;
	int bytes;
	char choose='p';
	char buf[bufsize];
	send( iClientSock, &choose, 1, 0);
	cout<<"�������û�id��"<<endl;
	cin>>id;
	itoa(id,buf,10);
	send( iClientSock, buf, strlen( buf ),0 );
	cout<<"��������Ϣ���ݣ�"<<endl;
	cin>>buf;
	send( iClientSock, buf, strlen( buf), 0 );
	bytes= recv( iClientSock, buf, bufsize, 0 );
    buf[ bytes ] = '\0';
	cout<<buf<<endl;
	return;
}

void f_pro(const int &iClientSock){
	int bytes;
	char choose='f';
	send( iClientSock, &choose, 1, 0);
	char buf[bufsize];
	int fris;
	bytes= recv( iClientSock, buf, bufsize, 0 );
    buf[ bytes ] = '\0';
	fris=atoi(buf);
	for(int i=0;i<fris;i++){
		bytes= recv( iClientSock, buf, bufsize, 0 );
		buf[bytes]='\0';
		cout<<"ID:"<<buf<<"    ������";
		bytes= recv( iClientSock, buf, bufsize, 0 );
		buf[bytes]='\0';
		cout<<buf<<endl;
	}
	return;

}

void s_pro(const int &iClientSock){
	int bytes;
	char choose='s';
	send( iClientSock, &choose, 1, 0);
	char buf[200];
	cout<<"������id�� "<<endl;
	cin>>buf;
	send( iClientSock, buf, strlen( buf ),0 );
	bytes= recv( iClientSock, buf, bufsize, 0 );
    buf[ bytes ] = '\0';
	cout<<buf<<endl;
	return;
}

void r_pro(const int &iClientSock){
	int bytes;
	char choose='r';
	send( iClientSock, &choose, 1, 0);
	char buf[bufsize];
	bytes= recv( iClientSock, buf, bufsize, 0 );
    buf[ bytes ] = '\0';
	cout<<buf<<endl;
	return;
}

void b_pro(const int &iClientSock){
	int bytes;
	char choose='b';
	send( iClientSock, &choose, 1, 0);
	char buf[bufsize];
    cout<<"��������Ϣ���ݣ� "<<endl;
	cin>>buf;
	send( iClientSock, buf, strlen( buf ),0 );
	bytes= recv( iClientSock, buf, bufsize, 0 );
    buf[ bytes ] = '\0';
	cout<<buf<<endl;
	return;
}

void a_pro(const int &iClientSock){
	int bytes;
	char choose='a';
	send( iClientSock, &choose, 1, 0);
	char buf[bufsize];
	cout<<"������id�� "<<endl;
	cin>>buf;
	send( iClientSock, buf, strlen( buf ),0 );
	bytes= recv( iClientSock, buf, bufsize, 0 );
    buf[ bytes ] = '\0';
	cout<<buf<<endl;
	return;
}

void c_pro(const int &iClientSock){
	int bytes;
	char choose='c';
	send( iClientSock, &choose, 1, 0);
	char buf[bufsize];
	cout<<"������ԭ���룺"<<endl;
	cin>>buf;
	send( iClientSock, buf, strlen( buf ),0 );
	cout<<"�����������룺"<<endl;
	cin>>buf;
	send( iClientSock, buf, strlen( buf ),0 );
	bytes= recv( iClientSock, buf, bufsize, 0 );
    buf[ bytes ] = '\0';
	cout<<buf<<endl;
	return;

}

void e_pro(const int &iClientSock){
	int bytes;
	char buf[bufsize];
	ofstream out("�����¼.txt",ios::app);
	bytes= recv( iClientSock, buf, bufsize, 0 );
    buf[ bytes ] = '\0';
	cout<<buf<<endl;
	out<<buf<<endl;
	out.close();
	return;
}