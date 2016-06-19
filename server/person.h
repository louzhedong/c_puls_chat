#ifndef PERSON_H
#define PERSON_H
#include <string>
#include <iostream>
#include <vector>

using std::string;
using std::vector;
using std::endl;

class Person{
public:
	int id;
	int key;
	string name;
	char gender; //'f'--female;'m'--male
	int age;
	string city;
	vector<Person *> friends;
	Person(){};
	Person(int pid,int pkey,const string &pname,char pgender,int page,const string &pcity){
		id=pid;
		key=pkey;
		name=pname;
		gender=pgender;
		age=page;
		city=pcity;
	}
	void set(int pid,int pkey,const string &pname,char pgender,int page,const string &pcity){
		id=pid;
		key=pkey;
		name=pname;
		gender=pgender;
		age=page;
		city=pcity;
	}
	friend 	std::ostream &operator<<( std::ostream &output, Person &p );

};

/*std::ostream &operator<<( std::ostream &output, Person &p ){
	output<<"ID:"<<p.id<<"  NAME:"<<p.name<<"  AGE:"<<p.age<<"  GENDER:"<<p.gender<<"  CITY:"<<p.city<<endl;
	return output;
}*/
#endif