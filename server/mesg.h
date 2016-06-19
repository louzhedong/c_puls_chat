#ifndef Mesg_H
#define Mesg_H
#include <WinSock2.h>


const int buffersize=80;
const int idsize=10;
const int namesize=20;
class Mesg{
protected:
	int iClientSock;
public:
	void setsock(int sock){
		iClientSock=sock;
	}
	char buf[buffersize];
	virtual int process() =0;
	friend class Svr;
};

class p_Mesg:public Mesg{
	char msgbuf[buffersize];
	char id[idsize];
public:
	virtual int process();
};

class l_Mesg:public Mesg{
	char id[idsize];
	char key[idsize];
public:
	virtual int process();
};

class f_Mesg:public Mesg{
	char frid[idsize];
	char frname[namesize];
public:
	virtual int process();
};

class s_Mesg:public Mesg{
	char sid[idsize];
public:
	virtual int process();
};

class c_Mesg:public Mesg{
	int okey;
	int nkey;
public:
	virtual int process();
};

class a_Mesg:public Mesg{
public:
	virtual int process();
};

class r_Mesg:public Mesg{
public:
	virtual int process();
};

class b_Mesg:public Mesg{
	char sendid[idsize];
public:
	virtual int process();
};
#endif