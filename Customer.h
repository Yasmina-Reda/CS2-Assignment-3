#pragma once
#include "Person.h"
#include <string>
using namespace std;

class Customer : public Person {
private:
	string MechanicID;
	appointment appt;
public:
	Customer(){};
	~Customer() {};
	void setMechId(string);
	void setAppt(int, int, int, int); //sets an appointment with the starting and ending time
	string getMechId();
	appointment getAppt(); 
	bool operator > (Customer);
	bool operator < (Customer);
	bool operator == (Customer);
	void printinfo(); //Did not print age or id because I do not think the are relevant to customer, so I will not set them
	void printtime();

};
