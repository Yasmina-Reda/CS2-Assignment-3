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

void validatetime(int&, int&, int&, int&, int, string); //to validate that the entered time is correct
void readtime(string&, int&, int&); //reads a string of time in hh:mm format and sends back the hours and mins
int readMechData(Mechanic[], int); //inputs and sets the data of a mechanic from a file
int readCustData(Customer*&, Mechanic[], int); //takes in and sets the data of a customer, creates customer array and returns its size
int AssignAppt(Customer*, int, Mechanic[], int, Customer*&); //Assigns customers to mechanics, creates a new array without cancelled appointments and returns size
template <class T>
void swap(T*, int, int); //swaps two elements in an array of index i and j
void sortArray(Customer*, int); //sorts customers ascendingly
void QueueCust(Queue<Customer>& QC, Customer*, int); //Queues sorted Customers
void printQueue(Queue<Customer> QC, int apptCount); //prints queue


int main()
{
	cout << "Welcome to TKRVGS Car Workshop!";
	int mCount = 2, cCount, apptCount;
	Mechanic arr[2];
	readMechData(arr,mCount);
	Customer* Cptr, *newCptr;
	cCount=readCustData(Cptr, arr, 2);
	apptCount=AssignAppt(Cptr,cCount,arr,2,newCptr);
	Queue<Customer> QC(apptCount);
	QueueCust(QC, newCptr, apptCount);
	printQueue(QC, apptCount);

	cout << "\n\nOUR TEAM:\n";
	for (int i = 0;i < mCount;i++)
	{
		arr[i].printinfo(); cout << '\n';
	}
	cout << endl;

	delete[]Cptr, newCptr;
	
	return 0;



	//don't fprget tp delete all new pointers
}

void validatetime(int& starthours, int& startmins, int& endhours, int& endmins, int count, string name)
{
	while (starthours < 0 || starthours >= 24)
	{
		cout << "Invalid starting hour. Please re-enter: "; cin >> starthours;
	}

	while (endhours < 0 || endhours >= 24 || endhours < starthours)
	{
		cout << "Invalid ending hour. Please re-enter: "; cin >> endhours;
	}

	while (startmins < 0 || startmins >= 60)
	{
		cout << "Invalid starting minutes. Please re-enter: "; cin >> startmins;
	}

	while (endmins < 0 || endmins >= 60 || starthours == endhours && startmins == endmins || starthours == endhours && endmins < startmins)
	{
		cout << "Invalid ending minutes for slot " << count + 1 << " for " << name << " Please re - enter: "; cin >> endmins;
	}
}

void readtime(string& time, int& hr, int& min)
{
	if (time.length() != 4 && time.length() != 5)
	{
		cout << "Invalid time. Please re-enter: "; cin >> time;
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
					validatetime(starthours, startmins, endhours, endmins, i, arr[Mcount].getName());
					available = arr[Mcount].setAppt(starthours, startmins, endhours, endmins, i);
					if (available == false) cout << "\n\n\nSlot not available for " << arr[Mcount].getName() << " from " << starttime << " to " << endtime;
				}
				Mcount++;

			}
			else cout << "\nNot Enough Slots for Mechanic.";
		}
		return 0;
	}
	else { cout << "\n\nfailed to open file\n\n"; return -1; }
}

int readCustData(Customer*& Cptr, Mechanic arr[], int Msize) //I do not think there is need to get age and id for customer
{
	int num;
	cout << "\n\nPlease Enter Number of Customers: "; cin >> num;
	Cptr = new Customer[num]; string stemp; int shr, smin, ehr, emin;
	for (int i = 0; i < num;i++)
	{
		cout << "\nPlease enter the relevant data for customer no. " << i + 1 << ": ";
		cout << "\nName: "; cin >> stemp;
		(Cptr + i)->setName(stemp);
		cout << "\nStarting Time: "; cin >> stemp; //to be entered with colon
		readtime(stemp, shr, smin);
		cout << "\nEnding Time: "; cin >> stemp; //to be entered with colon
		readtime(stemp, ehr, emin);
		validatetime(shr, smin, ehr, emin, i + 1, (Cptr + i)->getName()); 
		(Cptr + i)->setAppt(shr, smin, ehr, emin);
	}
	return num;
}

int AssignAppt(Customer* Cptr, int cCount, Mechanic arr[], int mCount, Customer*& newCptr)
{
	int j = 0, shr, smin, ehr, emin, apptCount = 0; Person::appointment temp; bool reserved = true;

	for (int i = 0;i < cCount;i++)
	{
		temp = (Cptr + i)->getAppt();
		shr = temp.starthours;
		smin = temp.startmins;
		ehr = temp.endhours;
		emin = temp.endmins;

		j = i % mCount; 
		if (reserved == false) --j; //in order not to skip a mechanic if an appoinment is cancelled
		reserved = false;
		for (int z = 0;z < mCount && reserved == false;z++)
		{
			reserved = arr[j].setAppt(shr, smin, ehr, emin, arr[j].getCount());
			j = ++j % mCount;
		}

		if (reserved == true)
		{
			(Cptr + i)->setMechId(arr[j].getId());
			apptCount++;
		}
		else
		{
			cout << "\nCould Not Reserve Spot:No Mechanics Available. Cancelling Appointment...";
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
	for (int i = 0;i < apptCount;i++)
	{
		for (int j = 0; j < apptCount - 1;j++)
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

void printQueue(Queue<Customer> QC, int apptCount)
{
	Customer temp;
	for (int i = 0; i < apptCount;i++)
	{
		QC.pop(temp);
		temp.printinfo();
	}

}