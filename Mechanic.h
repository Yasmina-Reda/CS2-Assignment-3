#pragma once
#include "Person.h"

class Mechanic : public Person {
private:
	int counter = 0;
	appointment appts[1440]; //number of minutes in a day: maximum number of appts possible
	bool** reserved; //For availability: a 2d of 24*60 [mins] initially set to false meaning mechanic is free. After each appointment the time slot is reserved
public:
	Mechanic();
	~Mechanic();
	bool isAvailable(int, int, int, int); //tests if the mechanic is available from the start time till the endtime
	bool setAppt(int,int, int, int, int); //sets an appointment from the start time to end time
	//void setCount(int);
	void printinfo();
	appointment getAppt(int); //returns a specific appointment of index i
	int getCount();
};


//notes to self: additions to make later
//add mechanic in breaktime
//Wanted to use this to give the mechanic time off by setting break time to false but question specified to make them available all 24 hours
