#include "Person.h"
#include "Person.cpp"
#include "Customer.h"
#include "Customer.cpp"
#include "Mechanic.h"
#include "Mechanic.cpp"
#include <iostream>
#include <fstream>
#include <string>
#include "Queue.h"

void validatetime(int&, int&, int&, int&,string&,string&, int, string); //to validate that the entered time is correct and modify if not
void readtime(string&, int&, int&); //reads a string of time in hh:mm format and sets back the hours and mins
void settime(string&, int, int); //rads hours and mins and sets a string in hh:mm
int readMechData(Mechanic[], int); //reads and sets the data of mechanics from a file
int readCustData(Customer*&, Mechanic[], int); //reads in and sets the data of a customer, creates an array of customers and returns its size
string getAssignedMech(string, Mechanic[], int); //returns the assigned mechanic name according to mechanic id
int AssignAppt(Customer*, int, Mechanic[], int, Customer*&); //Assigns customers to mechanics, creates a new array without cancelled appointments and returns its size
template <class T>
void swap(T*, int, int); //swaps any two elements in an array of index i and j
void sortArray(Customer*, int); //sorts customers ascendingly
void QueueCust(Queue<Customer>& QC, Customer*, int); //Queues sorted Customers 
void printQueue(Queue<Customer>& QC, int apptCount, Mechanic[], int); //prints queue with assigned mechanic and time info
void writeMech(Mechanic[], int); //writes mech data to new file


int main()
{
	cout << "\nWelcome to TKRVGS Motorbike Workshop!\n\n";
	int mCount = 3, cCount, apptCount;
	Mechanic arr[3];
	readMechData(arr,mCount);
	Customer* Cptr, *newCptr;
	cCount=readCustData(Cptr, arr, mCount);
	apptCount=AssignAppt(Cptr,cCount,arr,mCount,newCptr);
	Queue<Customer> QC(apptCount);
	QueueCust(QC, newCptr, apptCount);
	printQueue(QC, apptCount, arr, mCount);
	writeMech(arr,mCount);
	cout << endl;

	delete[]Cptr, newCptr;
	
	return 0;
}

void validatetime(int& starthours, int& startmins, int& endhours, int& endmins,string&starttime,string&endtime, int num, string name)
{
	string temp;
	while (starthours < 0 || starthours >= 24)
	{
		cout << name << " slot " << num+1<< " Invalid starting hour. Please re-enter time: "; cin >> temp;
		readtime(temp, starthours, startmins);
		settime(starttime, starthours, startmins);
	}

	while (startmins < 0 || startmins >= 60)
	{
		cout << name << " slot " << num+1 << " Invalid starting minutes. Please re-enter time: "; cin >> temp;
		readtime(temp, starthours, startmins);
		settime(starttime, starthours, startmins);
	}

	while (endhours < 0 || endhours >= 24 || endhours < starthours)
	{
		cout << name << " slot " << num+1 << " Invalid ending hour. Please re-enter time: "; cin >> temp;
		readtime(temp, endhours, endmins);
		settime(endtime, endhours, endmins);
	}

	while (endmins < 0 || endmins >= 60 || starthours == endhours && startmins == endmins || starthours == endhours && endmins < startmins)
	{
		cout << name << " slot " << num+1 << " Invalid ending minutes for slot. Please re - enter time: "; cin >> temp;
		readtime(temp, endhours, endmins);
		settime(endtime, endhours, endmins);
	}
}

void readtime(string& time, int& hr, int& min)

{
	while (!(time.length() == 4 && time.at(1)==':') && time.length() != 5) 	// to make sure string entered is in h:mm or hh:mm format
	{
		cout << "\nInvalid time format. Please re-enter: "; cin >> time;
	}
		string shr = "", smin = "";
		bool colon = false;
		for (int i = 0;i < time.length();i++) {
			if (time.at(i) != ':' && colon == false) shr += time.at(i);
			else if (time.at(i) == ':') colon = true;
			else smin += time.at(i);
		}
		hr = stoi(shr);
		min = stoi(smin);	
}

void settime(string& time, int hr, int min)
{
	time = "" + to_string(hr)+':';
	if (min < 10) time = time + '0';
	time += to_string(min);
}

int readMechData(Mechanic arr[], int size) {
	string temp, starttime, endtime; int Mcount = 0, Apptcount = 0;
	int starthours, startmins, endhours, endmins;
	ifstream readM("Mech.txt"); bool available;

	if(!readM.fail())
	{
		while (readM >> temp) {
			if (Mcount < size) {

				arr[Mcount].setName(temp);
				readM >> temp;
				arr[Mcount].setAge(stoi(temp));
				readM >> temp;
				arr[Mcount].setId(temp);
				readM >> temp;
				Apptcount = stoi(temp);
				for (int i = 0;i < Apptcount;i++)
				{
					readM >> starttime >> endtime;
					readtime(starttime, starthours, startmins);
					readtime(endtime, endhours, endmins);
					validatetime(starthours, startmins, endhours, endmins,starttime,endtime, i, arr[Mcount].getName());
					available = arr[Mcount].setAppt(starthours, startmins, endhours, endmins, i);
					if (available == false) cout << "\n\n\nSlot not available for " << arr[Mcount].getName() << " from " << starttime << " to " << endtime;
				}
				Mcount++;

			}
			else cout << "\nNot Enough Slots for Mechanic.";
		}
		return 0;
	}
	else { cout << "\n\nfailed to open Mech.txt\n\n"; return -1; }
}

int readCustData(Customer*& Cptr, Mechanic arr[], int Msize) //I do not think there is need to set age and id for customer
{
	ifstream readC("Cust.txt"); string temp,starttime,endtime;int num, shr, smin, ehr, emin,i=0;

	if (!readC.fail())
	{
		readC >> temp; 
		num = stoi(temp);
		Cptr = new Customer[num];
		while (i<num)
		{
			readC >> temp;
			(Cptr + i)->setName(temp);
			readC >> starttime;
			readtime(starttime, shr, smin);
			readC >> endtime;
			readtime(endtime, ehr, emin);
			validatetime(shr, smin, ehr, emin, starttime, endtime, 0, (Cptr + i)->getName());
			(Cptr + i)->setAppt(shr, smin, ehr, emin);
			i++;
		}
		return num;
	}
 else { cout << "\n\nfailed to open Cust.txt\n\n"; return 0; }
}


string getAssignedMech(string Mechid, Mechanic arr[], int mCount) {

	for (int i = 0;i < mCount;i++)
	{
		if (Mechid == arr[i].getId()) return arr[i].getName();
	}

}

int AssignAppt(Customer* Cptr, int cCount, Mechanic arr[], int mCount, Customer*& newCptr)
{
	int j = 0, shr, smin, ehr, emin, apptCount = 0; Person::appointment temp; bool reserved=true;

	for (int i = 0;i < cCount;i++)
	{
		temp = (Cptr + i)->getAppt();
		shr = temp.starthours;
		smin = temp.startmins;
		ehr = temp.endhours;
		emin = temp.endmins;

		j = i % mCount;
		reserved = false;
		for (int z = 0;z < mCount && reserved == false;z++)
		{
			reserved = arr[j].setAppt(shr, smin, ehr, emin, arr[j].getCount());
			j = ++j % mCount;
		}

		if (reserved == true)
		{
			if (j == 0) j = mCount; //in order to go back to end of array
			(Cptr + i)->setMechId(arr[j-1].getId()); //j-1 to decrement last ++j in previous loop
			apptCount++;
			cout << '\n' << (Cptr + i)->getName() << " is assigned to " << getAssignedMech((Cptr + i)->getMechId(), arr, mCount) << '\n';

		}
		else
		{
			cout << "\n\nCould Not Reserve Spot for "<< (Cptr + i)->getName() <<": No Mechanics Available.Cancelling Appointment...\n";
			(Cptr + i)->setName("");
			temp.starthours = NULL;
			temp.startmins = NULL;
			temp.endhours = NULL;
			temp.endmins = NULL;
		}
	}

	//new array to remove all cancelled appointments;
	newCptr = new Customer[apptCount]; j = 0;
	for (int i = 0;i < cCount;i++)
	{
		if ((Cptr + i)->getName() == "") continue; //to skip cancelled appointments;
		else
		{
			*(newCptr + j) = *(Cptr + i);
			j++;
		}
	}


	return apptCount;
}


template <class T>
void swap(T* ptr, int i, int j)
{
	T temp;
	temp = *(ptr + i);
	*(ptr + i) = *(ptr + j);
	*(ptr + j) = temp;
}

void sortArray(Customer* Cptr, int apptCount) {
	for (int i = 0;i < apptCount-1;i++)
	{
		for (int j = i+1; j < apptCount;j++)
		{
			if (*(Cptr + i) > *(Cptr + j)) swap(Cptr, i, j); 
		}
	}
}

void QueueCust(Queue<Customer>& QC, Customer* Cptr, int apptCount) {
	sortArray(Cptr, apptCount);
	for (int i = 0;i < apptCount;i++)
	{
		QC.push(*(Cptr + i));
	}
}

void printQueue(Queue<Customer>& QC, int apptCount, Mechanic arr[], int mCount)
{
	Customer temp;
	for (int i = 0; i < apptCount;i++)
	{
		QC.pop(temp);
		cout << '\n' << temp.getName() << " has an appointment with " << getAssignedMech(temp.getMechId(), arr, mCount); temp.printtime();
	}

}

void writeMech(Mechanic arr[], int mCount) {
	ofstream writeM("newMech.txt");
	if (!writeM.fail())
	{
		for (int i = 0;i < mCount;i++)
		{
			writeM << arr[i].getName() << '\n'<<arr[i].getAge() << '\n'<<arr[i].getId() << '\n' << arr[i].getCount() << '\n';
			for (int j = 0; j < arr[i].getCount();j++)
			{
				writeM << arr[i].getAppt(j).starthours << ":";
				if (arr[i].getAppt(j).startmins < 10) writeM << '0' << arr[i].getAppt(j).startmins;
				else writeM << arr[i].getAppt(j).startmins;
				writeM << '\n';
				writeM << arr[i].getAppt(j).endhours << ":";
				if (arr[i].getAppt(j).endmins < 10) writeM << '0' << arr[i].getAppt(j).endmins;
				else writeM << arr[i].getAppt(j).endmins;
				writeM << '\n';
			}

		}
	}
	else cout << "failed to open newMech.txt to write";

}