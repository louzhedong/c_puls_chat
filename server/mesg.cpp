#include "mesg.h"
#include <WinSock2.h>
#include <iostream>
#include <map>
#include <time.h>
#include "person.h"
#include <vector>

using namespace std;
extern map<int,SOCKET>  idmap;
extern map<int,SOCKET>::iterator it;
extern map<SOCKET,int>  sockmap;
extern map<SOCKET,int>::iterator sit;
extern Person persons[10];
extern int allperson;

vector<SOCKET> chatroom;

int p_Mesg::process(){
	time_t nowtime;
	nowtime=time(NULL);
	char timebuf[30];
	strcpy(timebuf,ctime(&nowtime));
	int pid;
	int bytes;
	char sendid[100];
	int num;
	SOCKET recvsock;
	char *noid="ID错误";
	int nosize=strlen(noid);
	char *noid1="ID未登录";
	int nosize1=strlen(noid1);
	char *yesid="发送成功";
	int yessize=strlen(yesid);
	if((bytes=recv( iClientSock,id, idsize, 0 ))==-1){
		printf( "recv调用失败!\n" );
		return 1;
	}
	id[bytes]='\0';
	if((bytes=recv( iClientSock,msgbuf, buffersize, 0 ))==-1){
		printf( "recv调用失败!\n" );
		return 1;
	}
	msgbuf[bytes]='\0';
	sit=sockmap.find(iClientSock);
	if(sit!=sockmap.end()){
		itoa(sit->second,sendid,10);
	}
	else{
		send( iClientSock,noid1, nosize1, 0);
		return 1;
	}
	pid=atoi(id);
	it=idmap.find(pid);
	if(it==idmap.end()){
		send( iClientSock, noid, nosize, 0);
	}
	else{
		recvsock=it->second;
		send( iClientSock, yesid, yessize, 0);
		send( recvsock, timebuf, strlen(timebuf), 0);
		num=strlen(sendid);
		sendid[num]=':';
		sendid[num+1]='\0';
		strcat(sendid,msgbuf);
		send( recvsock, sendid, strlen(sendid), 0);
	}
	cout<<msgbuf<<endl;
	return 0;
}

int l_Mesg::process(){
	int flag=0;
	int pid;
	int pkey;
	int bytes;
	char *yesid="登陆成功";
	int yessize=strlen(yesid);
	char *noid="账号密码错误";
	int nosize=strlen(noid);
	if((bytes=recv( iClientSock,id, idsize, 0 ))==-1){
		printf( "recv调用失败!\n" );
		return 1;
	}
	id[bytes]='\0';
	if((bytes=recv( iClientSock,key, idsize, 0 ))==-1){
		printf( "recv调用失败!\n" );
		return 1;
	}
	key[bytes]='\0';
	pid=atoi(id);
	pkey=atoi(key);
	for(int i=0;i<allperson;i++){
		if((pid==persons[i].id)&&(pkey==persons[i].key)){
			flag=1;
			break;
		}
	}
	if(flag==0){
		send( iClientSock, noid, nosize, 0);
	}
	else{
		send( iClientSock, yesid, yessize, 0);
		idmap[pid]=iClientSock;
		sockmap[iClientSock]=pid;
	}
	return 0;
}

int f_Mesg::process(){
	int pid;
	int fris;
	char *noid="账号未登录";
	int nosize=strlen(noid);
	sit=sockmap.find(iClientSock);
	if(sit==sockmap.end()){
		send( iClientSock, noid, nosize, 0);
		return 1;
	}
	else{
		pid=sit->second;
		int i;
		for(i=0;i<allperson;i++){
			if(persons[i].id==pid){
				break;
			}
		}
		fris=persons[i].friends.size();
		itoa(fris,buf,10);
		send(iClientSock,buf,strlen(buf),0);
		for(int j=0;j<fris;j++){
			itoa((persons[i].friends[j])->id,buf,10);
			send(iClientSock,buf,strlen(buf),0);
			strcpy(buf,(persons[i].friends[j])->name.c_str());
			send(iClientSock,buf,strlen(buf),0);
		}
	}
	return 0;
}

int s_Mesg::process(){
	int flag=0;
	int pid;
	int bytes;
	char buff[200];
	char *noid="id错误";
	int nosize=strlen(noid);
	if((bytes=recv( iClientSock,sid, idsize, 0 ))==-1){
		printf( "recv调用失败!\n" );
		return 1;
	}
	sid[bytes]='\0';
	pid=atoi(sid);
	int i;
	for(i=0;i<allperson;i++){
		if(pid==persons[i].id){
			flag=1;
			break;
		}
	}
	if(flag==0){
		send( iClientSock, noid, nosize, 0);
	}
	else{
		strcpy(buff,"id:");
		itoa(pid,sid,10);
		strcat(buff,sid);
		strcat(buff,"  年龄:");
		itoa(persons[i].age,sid,10);
		strcat(buff,sid);
		strcat(buff,"  姓名:");
		strcat(buff,persons[i].name.c_str());
		strcat(buff,"  城市:");
		strcat(buff,persons[i].city.c_str());
		strcat(buff,"  性别:");
		if(persons[i].gender=='f')
		{
			strcat(buff,"女");
		}
		else{
			strcat(buff,"男");
		}
		send( iClientSock, buff, strlen(buff), 0);;
	}
	return 0;
}

int c_Mesg::process(){
	int pid;
	int bytes;
	char *noid="账号未登录";
	int nosize=strlen(noid);
	char *succ="修改成功";
	char *fail="修改失败";
	sit=sockmap.find(iClientSock);
	if(sit==sockmap.end()){
		send( iClientSock, noid, nosize, 0);
		return 1;
	}
	else{
		pid=sit->second;
		int i;
		for(i=0;i<allperson;i++){
			if(persons[i].id==pid){
				break;
			}
		}
		if((bytes=recv( iClientSock,buf,buffersize, 0 ))==-1){
			printf( "recv调用失败!\n" );
			return 1;
		}
		buf[bytes]='\0';
		okey=atoi(buf);
		if((bytes=recv( iClientSock,buf,buffersize, 0 ))==-1){
			printf( "recv调用失败!\n" );
			return 1;
		}
		buf[bytes]='\0';
		nkey=atoi(buf);
		if(persons[i].key==okey){
			persons[i].key=nkey;
			send( iClientSock, succ, strlen(succ), 0);
		}
		else{
			send( iClientSock, fail, strlen(fail), 0);
		}
	}
	return 0;
}

int a_Mesg::process(){
	int flag=0;
	int aid;
	int pid;
	int bytes;
	char *noid="账号未登录";
	int nosize=strlen(noid);
	char *succ="添加成功";
	char *fail="id错误";
	char *fail2="id已在好友列表";
	sit=sockmap.find(iClientSock);
	if(sit==sockmap.end()){
		send( iClientSock, noid, nosize, 0);
		return 1;
	}
	else{
		pid=sit->second;
		int i;
		for(i=0;i<allperson;i++){
			if(persons[i].id==pid){
				break;
			}
		}
		if((bytes=recv( iClientSock,buf,buffersize, 0 ))==-1){
			printf( "recv调用失败!\n" );
			return 1;
		}
		buf[bytes]='\0';
		aid=atoi(buf);
		int j;
		for(j=0;j<allperson;j++){
			if(persons[j].id==aid){
				flag=1;
				break;
			}
		}
		if(flag==1){
			for(int k=0;k<persons[i].friends.size();k++){
				if(persons[i].friends[k]==&persons[j]){
					send( iClientSock, fail2, strlen(fail2), 0);
					return 0;
				}
			}
			send( iClientSock, succ, strlen(succ), 0);
			persons[i].friends.push_back(&persons[j]);
		}
		else{
			send( iClientSock, fail, strlen(fail), 0);
		}
	}
	return 0;
}

int b_Mesg::process(){
	time_t nowtime;
	nowtime=time(NULL);
	char timebuf[30];
	strcpy(timebuf,ctime(&nowtime));
	int bytes;
	SOCKET recvsock;
	char buff[100];
	char *noid1="ID未登录";
	int nosize1=strlen(noid1);
	char *yesid="发送成功";
	int yessize=strlen(yesid);
	if((bytes=recv( iClientSock,buf, buffersize, 0 ))==-1){
		printf( "recv调用失败!\n" );
		return 1;
	}
	buf[bytes]='\0';
	sit=sockmap.find(iClientSock);
	if(sit!=sockmap.end()){
		itoa(sit->second,sendid,10);
	}
	else{
		send( iClientSock,noid1, nosize1, 0);
		return 1;
	}
	send( iClientSock, yesid, yessize, 0);
    for(int i=0;i<chatroom.size();i++){
		recvsock=chatroom[i];
		send( recvsock, timebuf, strlen(timebuf), 0);
		strcpy(buff,"来自聊天室的");
		strcat(buff,sendid);
		int num=strlen(buff);
		buff[num]=':';
		buff[num+1]='\0';
		strcat(buff,buf);
		send( recvsock, buff, strlen(buff), 0);
	}
	return 0;
}

int r_Mesg::process(){
	char *succ="加入成功";
	char *fail="已加入聊天室";
	int flag=0;
	for(int i=0;i<chatroom.size();i++){
		if(chatroom[i]==iClientSock){
			flag=1;
			break;
		}
	}
	if(flag==0){
		send( iClientSock,succ,strlen(succ), 0);
		chatroom.push_back(iClientSock);
	}
	else{
		send( iClientSock,fail,strlen(fail), 0);
	}
	return 0;
}