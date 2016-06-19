#include "mesg.h"
#include "server.h"
#include "person.h"
#include <WinSock2.h>
#include <iostream>
#include <map>
#include <vector>

#pragma comment( lib, "ws2_32.lib" )

using namespace std;

Svr svr;
DWORD WINAPI WorkerThread(LPVOID lpParameter); 
map<int,SOCKET>  idmap;
map<SOCKET,int>  sockmap;
map<int,SOCKET>::iterator it;
map<SOCKET,int>::iterator sit;
Person persons[10]; //�����û�
int allperson=2;  //�û�������


int main(){
	DWORD  dwThreadId;
	persons[0].set(10000,12345,"С��",'m',20,"����");
	persons[1].set(10001,12345,"С��",'f',20,"�Ϻ�");
	persons[0].friends.push_back(&persons[1]);
	svr.Svr_bind();
	svr.Svr_listen();
	CreateThread(NULL, 0, WorkerThread, NULL, 0, &dwThreadId);   
	while(1){
		svr.Svr_accept();
	}
}
DWORD WINAPI WorkerThread(LPVOID lpParam) {   
	int             i;   
	fd_set         fdread;   
	int             ret;   
	struct timeval tv = {1, 0};   
	char           uchoose;     
	while (1){     
		FD_ZERO(&fdread);     
		for (i = 0; i < svr.total; i++){ 
			FD_SET(svr.socks[i], &fdread); 
		}                      
		ret = select(0, &fdread, NULL, NULL, &tv); 
		if (ret == 0) {        
			continue; 
		} 
		for (i = 0; i < svr.total; i++){ 
			if (FD_ISSET(svr.socks[i], &fdread)) {         // A read event happened on g_CliSocketArr 
				ret = recv(svr.socks[i], &uchoose, 1, 0); 
				if (ret == 0 || (ret == SOCKET_ERROR && WSAGetLastError() == WSAECONNRESET)){ 
					// Client socket closed           
					cout<<"�׽��� "<<svr.socks[i]<<"�ر�"<<endl;
					cout<<"��ǰ����������  "<<svr.total-1<<endl;
					sit=sockmap.find(svr.socks[i]);
					if(sit!=sockmap.end()){
						int sid=sit->second;
						sockmap.erase(sit);
						it=idmap.find(sid);
						if(it!=idmap.end()){
							idmap.erase(it);
						}
					}
					closesocket(svr.socks[i]); 
					if (i < svr.total - 1){ 
						svr.socks[i--] = svr.socks[--svr.total]; 
					} 
					else{
						svr.total--;
					}
				} 
				else{ 
					switch(uchoose){
					case 'p' : //������Ϣ
						svr.mesgs[0]->setsock(svr.socks[i]);
						svr.mesgs[0]->process();
						break;
					case 'l': //�˺ŵ�½
						svr.mesgs[1]->setsock(svr.socks[i]);
						svr.mesgs[1]->process();
						break;
					case 'f': //�鿴����
						svr.mesgs[2]->setsock(svr.socks[i]);
						svr.mesgs[2]->process();
						break;
					case 's': //�鿴����
						svr.mesgs[3]->setsock(svr.socks[i]);
						svr.mesgs[3]->process();
						break;
					case 'r': //����������
						svr.mesgs[4]->setsock(svr.socks[i]);
						svr.mesgs[4]->process();
						break;
					case 'b': //������������Ϣ
						svr.mesgs[5]->setsock(svr.socks[i]);
						svr.mesgs[5]->process();
						break;
					case 'a': //��Ӻ���
						svr.mesgs[6]->setsock(svr.socks[i]);
						svr.mesgs[6]->process();
						break;
					case 'c': //�޸�����
						svr.mesgs[7]->setsock(svr.socks[i]);
						svr.mesgs[7]->process();
					default:
						break;
					}
				} 
			}  
		} 
	}     
	return 0; 
} 