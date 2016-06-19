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
Person persons[10]; //所有用户
int allperson=2;  //用户总人数


int main(){
	DWORD  dwThreadId;
	persons[0].set(10000,12345,"小明",'m',20,"杭州");
	persons[1].set(10001,12345,"小红",'f',20,"上海");
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
					cout<<"套接字 "<<svr.socks[i]<<"关闭"<<endl;
					cout<<"当前连接总数：  "<<svr.total-1<<endl;
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
					case 'p' : //发送消息
						svr.mesgs[0]->setsock(svr.socks[i]);
						svr.mesgs[0]->process();
						break;
					case 'l': //账号登陆
						svr.mesgs[1]->setsock(svr.socks[i]);
						svr.mesgs[1]->process();
						break;
					case 'f': //查看好友
						svr.mesgs[2]->setsock(svr.socks[i]);
						svr.mesgs[2]->process();
						break;
					case 's': //查看资料
						svr.mesgs[3]->setsock(svr.socks[i]);
						svr.mesgs[3]->process();
						break;
					case 'r': //加入聊天室
						svr.mesgs[4]->setsock(svr.socks[i]);
						svr.mesgs[4]->process();
						break;
					case 'b': //发送聊天室消息
						svr.mesgs[5]->setsock(svr.socks[i]);
						svr.mesgs[5]->process();
						break;
					case 'a': //添加好友
						svr.mesgs[6]->setsock(svr.socks[i]);
						svr.mesgs[6]->process();
						break;
					case 'c': //修改密码
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