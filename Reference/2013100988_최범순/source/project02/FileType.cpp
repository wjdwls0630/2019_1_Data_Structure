#include "FileType.h"
#pragma warning(disable:4996)//control error of localtime()

//get file name
string FileType::getName() {
	return name;
}

//get file location
string FileType::getLocation() {
	return location;
}

string FileType::getLocationName()
{
	string ln = location + name;
	if (location.substr(0, 1) == "\\") {
		ln = location.substr(1);
	}
	if (location.length() > 3) {
		if (location.substr(3, 1) == "\\") {
			ln = location.substr(0, 3) + location.substr(4);
		}
	}
	return ln;
}

//get file size
int FileType::getSize() {
	return size;
}

//get date of when file was created
string FileType::getDate() {
	return date;
}

//get extension of the file
string FileType::getExtension() {
	return extension;
}

//set file name
void FileType::setName(string inName) {
	name = inName;
}

//set location of file
void FileType::setLocation(string inLocation) {
	location = inLocation;
}

//set size of file
void FileType::setSize() {

}

//set created date of file
void FileType::setDate()
{
	time_t tt;

	time(&tt);

	struct tm* ti;

	ti = localtime(&tt);

	stringstream ss;
	ss << setw(4) << ti->tm_year + 1900 << "/ " << setfill('0') << setw(2)
		<< ti->tm_mon + 1 << "/ " << setfill('0') << setw(2) << ti->tm_mday << ", " << setfill('0') << setw(2) << ti->tm_hour << ":" << setfill('0') << setw(2)
		<< ti->tm_min << ":" << setfill('0') << setw(2) << ti->tm_sec << "\0";

	//copy the stream buffer to name 
	date = ss.str();
}

//set extension of file
void FileType::setExtension(string inExtension) {
	extension = inExtension;
}

//set name of file obtained from user 
void FileType::setNameFromKB() {
	string inName;
	cout << "\tEnter file name with extension : ";
	cin >> inName;
	setName(inName);
}

//set property of file obtained from user
void FileType::setPropertyFromKB() {
	setNameFromKB();
}

//display current file name
void FileType::displayName() {
	cout << "\tFile name : " << name << endl;
}

//display current file location
void FileType::displayLocation() {
	cout << "\tLocation : " << location << endl;
}

//display file size
void FileType::displaySize() {
	cout << "\tSize : " << size << endl;
}

//display created date of current file
void FileType::displayDate() {
	cout << "\tCreated date : " << date << endl;
}

//display extension of file
void FileType::displayExtension() {
	cout << "\tExtension : " << extension << endl;
}

//display property of current file
void FileType::displayProperty() {
	cout << "\t-----------------------------------------------" << endl;
	displayName();
	displayExtension();
	displayLocation();
	displaySize();
	displayDate();
	cout << "\t-----------------------------------------------" << endl;

}

//check two files' name and location are same
bool FileType::operator==(const FileType& dataBeingCompared) const {
	bool isTrue = false;
	if ((this->name == dataBeingCompared.name) && (this->location == dataBeingCompared.location)) {
		isTrue = true;
	}
	return isTrue;
}

//check two files' name compare by name
bool FileType::operator>(const FileType& dataBeingCompared) const {
	if (this->name > dataBeingCompared.name) {
		return true;
	}
	return false;
}

//check two files' name compare by name
bool FileType::operator<(const FileType& dataBeingCompared) const {
	if (this->name < dataBeingCompared.name) {
		return true;
	}
	return false;
}
