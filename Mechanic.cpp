#include "Mechanic.h"

Mechanic::Mechanic() {
	reserved = new bool* [24]; //default in new bool is false
	for (int i = 0;i < 24;i++)
	{
		*(reserved + i) = new bool[60];
	}
}

Mechanic::~Mechanic() {
	for (int i = 0;i < 24;i++)
	{
		delete[] * (reserved + i);
	}
	delete[]reserved;
}

bool Mechanic::isAvailable(int starthours, int startmins, int endhours, int endmins) {
	bool available = true; //use this to exit loop if mechanic is not available

	if (starthours==endhours) //if the appointment is within the same hours check the minutes from startmin to end min
	{
		for (int j=startmins;j<=endmins&& available==true;j++)
		{
			if (*(*(reserved + starthours) + j) == true) available = false;
		}
	}
	else //if the appointment starts and ends in different hours
		for (int i = starthours; i <= endhours && available == true; i++) 
	{
		if (i == starthours) //check from startmin till end of starthour
			for (int j = startmins;j < 60 && available == true;j++) 
				if (*(*(reserved + i) + j) == true) available = false;
		else if (i == endhours) //check from beggining of endhour till endmin
			for (int j = 0; j <= endmins && available == true; j++)
				if (*(*(reserved + i) + j) == true) available = false;
		else for (int j = 0;j < 60 && available == true;j++) //check all minutes in hours in between starthour and startmin
					if (*(*(reserved + i) + j) == true) available = false;
	}
	return available;
}
int Mechanic::getCount() { return counter; }

bool Mechanic::setAppt(int starthours, int startmins, int endhours, int endmins, int num) { 
	if (isAvailable(starthours, startmins, endhours, endmins))
	{
		appts[num].starthours = starthours;
		appts[num].startmins = startmins;
		appts[num].endhours = endhours;
		appts[num].endmins = endmins;

		//to reserve
		if (starthours == endhours) //if the appointment is within the same hours reserve the minutes from startmin to end min
		{
			for (int j = startmins;j < endmins == true;j++)
			{
				*(*(reserved + starthours) + j) = true;
			}
		}
		else //if the appointment starts and ends in different hours
			for (int i = starthours; i <= endhours; i++)
		{
			if (i == starthours)  //reserve from startmin till end of starthour
				for (int j = startmins;j < 60;j++)
					*(*(reserved + i) + j) = true;
			else if (i == endhours) //reserve from beggining of endhour till endmin
				for (int j = 0; j <= endmins; j++)
					*(*(reserved + i) + j) = true;
			else for (int j = 0;j < 60;j++) //reserve all minutes in hours in between starthour and startmin
				*(*(reserved + i) + j) = true;

		}
		counter++; //increase number of appts for mechanic
		return true;
	}
	else {
		return false;
	}
	
}

//void Mechanic::setCount(int count)
//{
//	counter = count;
//}

Person::appointment Mechanic::getAppt(int count)
{
	return appts[count];
}

void Mprintzero(int time) //not included in class Mechanic, just to print minutes with a zero first when needed
{
	if (time < 10) cout << "0" << time;
	else cout << time;
}

void Mechanic::printinfo()
{
	cout << "\n\nName: " << getName();
	cout << "\nAge: " << getAge();
	cout << "\nID: " << getId();
	cout << "\nNumber of Appointments: " << counter;
	cout << "\n\nAppointments info: ";
	for (int i = 0; i < counter;i++) //print individual appointment details //would have rather sorted them ascendingly but would be a lot of extra work right now
	{
		cout << "\n\nAppointment " << i + 1;
		cout << "\nStart Time " << getAppt(i).starthours << ":"; Mprintzero(getAppt(i).startmins);
		cout << "\nEnd Time " << getAppt(i).endhours << ":"; Mprintzero(getAppt(i).endmins);
	}
}

