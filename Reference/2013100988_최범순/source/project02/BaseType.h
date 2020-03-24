#ifndef _BASETYPE_H
#define _BASETYPE_H

#include <iostream>
#include <string>

using namespace std;

/**
*	@brief	parent of FolderType and FileType
*/
class BaseType {
private:
	string name;
	string location;
	int size;
public:
	/**
	*	@brief	set name obtained from user
	*	@pre	none
	*	@post	name is set
	*/
	void setNameFromKB();

	/**
	*	@brief	set name
	*	@pre	none
	*	@post	name is set
	*	@param	inName	name.
	*/
	void setName(string inName);

	/**
	*	@brief	set location
	*	@pre	none
	*	@post	location is set
	*	@param	inLocation	location
	*/
	void setLocation(string inLocation);

	/**
	*	@brief	get name
	*	@pre	name is set
	*	@post	none
	*	@return name
	*/
	virtual string getName();

	/**
	*	@brief	get location
	*	@pre	location is set
	*	@post	none
	*	@return	location
	*/
	virtual string getLocation();

	/**
	*	@brief	get size
	*	@pre	size is set
	*	@post	none
	*	@return	size
	*/
	virtual int getSize();

	/**
	*	@brief	check two items' name and location are same
	*	@param	dataBeingCompared	data which will be compared to former one
	*	@return	return true if two folders' name and location are same, otherwise false
	*/
	bool operator==(const BaseType& dataBeingCompared) const;

	/**
	*	@brief	check two items' name compare by name
	*	@param	dataBeingCompared	data which will be compared to former one
	*	@return	return true if former folder name's ASCII code is bigger , otherwise false
	*/
	bool operator>(const BaseType& dataBeingCompared) const;

	/**
	*	@brief	check two items' name compare by name
	*	@param	dataBeingCompared	data which will be compared to former one
	*	@return	return true if former folder name's ASCII code is smaller , otherwise false
	*/
	bool operator<(const BaseType& dataBeingCompared) const;
};

#endif _BASETYPE_H
