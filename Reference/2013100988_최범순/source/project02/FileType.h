#ifndef _FILETYPE_H
#define _FILETYPE_H

#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <sstream>
#include <fstream>

#include "BaseType.h"

using namespace std;

/**
*	@brief	a class that manage files
*/
class FileType :public BaseType {
protected:
	string name;									///<file name
	string location;								///<file location
	int size;										///<file size
	string date;									///<date when the file was created
	string extension;								///<extension of the file

public:

	/**
	*	@brief	default constructor
	*/
	FileType() {
		name = "C:\\";
		location = "C:\\";
		size = 0;
		setDate();
		extension = "";
	}

	/**
	*	@brief	get file name
	*	@pre	file name is set
	*	@post	none
	*	@return file name
	*/
	virtual string getName();

	/**
	*	@brief	get file location
	*	@pre	file location is set
	*	@post	none
	*	@return	file location
	*/
	virtual string getLocation();

	virtual string getLocationName();

	/**
	*	@brief	get file size
	*	@pre	file size is set
	*	@post	none
	*	@return	file size
	*/
	virtual int getSize();

	/**
	*	@brief	get date of when file was created
	*	@pre	date is set
	*	@post	none
	*	@return	date of when file was created
	*/
	string getDate();

	/**
	*	@brief	get extension of the file
	*	@pre	extension is set
	*	@post	none
	*	@return extension of the file
	*/
	string getExtension();

	/**
	*	@brief	set file name
	*	@pre	none
	*	@post	file name is set
	*	@param	inName	file name.
	*/
	void setName(string inName);

	/**
	*	@brief	set location of file
	*	@pre	none
	*	@post	file location is set
	*	@param	inLocation	location of current folder
	*/
	void setLocation(string inLocation);

	/**
	*	@brief	set size of file
	*	@pre	none
	*	@post	file is set
	*/
	void setSize();

	/**
	*	@brief	set created date of file
	*	@pre	none
	*	@post	file created date is set
	*/
	void setDate();

	/**
	*	@brief	set extension of the file
	*	@pre	none
	*	@post	file extension is set
	*/
	void setExtension(string extension);

	/**
	*	@brief	set name of file obtained from user
	*	@pre	none
	*	@post	file name is set
	*/
	void setNameFromKB();

	/**
	*	@brief	set property of file obtained from user
	*	@pre	none
	*	@post	file property is set
	*/
	void setPropertyFromKB();

	/**
	*	@brief	display current file name
	*	@pre	file name is set
	*	@post	file name is displayed
	*/
	void displayName();

	/**
	*	@brief	display current file location
	*	@pre	location of the file is set
	*	@post	location of the file is displayed
	*/
	void displayLocation();

	/**
	*	@brief	display file size
	*	@pre	file size is set
	*	@post	file size is displayed
	*/
	void displaySize();

	/**
	*	@brief	display created date of file
	*	@pre	created date is set
	*	@post	created date of file is displayed
	*/
	void displayDate();

	/**
	*	@brief	display extension of file
	*	@pre	file extension is set
	*	@post	extension of file is displayed
	*/
	void displayExtension();

	/**
	*	@brief	display property of file
	*	@pre	property is all set
	*	@post	property of file is displayed
	*/
	void displayProperty();

	/**
	*	@brief	check two files' name and location are same
	*	@param	dataBeingCompared	data which will be compared to former one
	*	@return	return true if two folders' name and location are same, otherwise false
	*/
	bool operator==(const FileType& dataBeingCompared) const;

	/**
	*	@brief	check two files' name compare by name
	*	@param	dataBeingCompared	data which will be compared to former one
	*	@return	return true if former folder name's ASCII code is bigger , otherwise false
	*/
	bool operator>(const FileType& dataBeingCompared) const;

	/**
	*	@brief	check two files' name compare by name
	*	@param	dataBeingCompared	data which will be compared to former one
	*	@return	return true if former folder name's ASCII code is smaller , otherwise false
	*/
	bool operator<(const FileType& dataBeingCompared) const;

};


#endif _FILETYPE_H