#pragma once
#include <string>
#include <iostream>
using namespace std;

class Person {
private:
	string name;
	string id;
	int age;
public: //no constructor since question asked for an abstract class
	void setName(string);
	void setId(string);
	void setAge(int);
	string getName();
	string getId();
	int getAge();
	virtual void printinfo()=0; //made it pure virtual to make class abstract

	struct appointment //added extra ending time variables in order to be able to reserve spots
	{
		int starthours;
		int startmins;
		int endhours;
		int endmins;
	};
};
