#include "BaseType.h"

//set name obtained from user
void BaseType::setNameFromKB()
{
	string inName;
	cout << "\tEnter name : ";
	cin >> inName;
	setName(inName);
}

//set folder name
void BaseType::setName(string inName)
{
	name = inName;
}

//set location
void BaseType::setLocation(string inLocation)
{
	location = inLocation;
}

//get name
string BaseType::getName()
{
	return name;
}

//get location
string BaseType::getLocation()
{
	return location;
}

//get size
int BaseType::getSize()
{
	return size;
}

//check two items' name and location are same
bool BaseType::operator==(const BaseType & dataBeingCompared) const
{
	bool isTrue = false;
	if ((this->name == dataBeingCompared.name) && (this->location == dataBeingCompared.location)) {
		isTrue = true;
	}
	return isTrue;
}

//check two items' name compare by name
bool BaseType::operator>(const BaseType & dataBeingCompared) const
{
	if (this->name > dataBeingCompared.name) {
		return true;
	}
	return false;
}

//check two items' name compare by name
bool BaseType::operator<(const BaseType & dataBeingCompared) const
{
	if (this->name < dataBeingCompared.name) {
		return true;
	}
	return false;
}
