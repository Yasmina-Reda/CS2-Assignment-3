#include "Person.h"
#include <iostream>
#include <string>
using namespace std;


void Person::setName(string name) {
	this->name = name;
}

void Person::setId(string id) {
	this->id = id;
}

void Person::setAge(int age) {
	this->age = age;
}

string Person::getName() {
	return name;
}

string Person::getId() {
	return id;
}

int Person::getAge() {
	return age;
}
