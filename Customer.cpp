#include "Customer.h" //note to self: no need to #include parent here

void Customer::setMechId(string mechID)
{
	MechanicID = mechID;
}
void Customer::setAppt(int starthours, int startmins, int endhours, int endmins) 
{
	appt.starthours = starthours;
	appt.startmins = startmins;
	appt.endhours = endhours;
	appt.endmins = endmins;
}
string Customer::getMechId() {
	return MechanicID;
}
Person::appointment Customer::getAppt() //note to self: cannot access struct without Person::
{
	return appt;
}
bool Customer::operator>  (Customer x) {
	if (appt.starthours > x.appt.starthours) return true;
	else if (appt.starthours == x.appt.starthours && appt.startmins > x.appt.startmins) return true;
	else return false;
}
bool Customer::operator< (Customer x)
{
	if (appt.starthours < x.appt.starthours) return true;
	else if (appt.starthours == x.appt.starthours && appt.startmins < x.appt.startmins) return true;
	else return false;
}
bool Customer::operator== (Customer x)
{
	if (appt.starthours == x.appt.starthours && x.appt.startmins == x.appt.startmins) return true;
	else return false;
}

void Cprintzero(int time) //not included in class Customer, just to print minutes with a zero first when needed
{
	if (time < 10) cout << "0" << time;
	else cout << time;
}

void Customer::printinfo()
{
		cout << "\nName: " << getName();
		cout << "\nMechanicID: " << getMechId();
		cout << "\nAppointment Info:\n";
		cout << "\nStart Time " << getAppt().starthours << ":"; Cprintzero(getAppt().startmins);
		cout << "\nEnd Time " << getAppt().endhours << ":"; Cprintzero(getAppt().endmins);
}