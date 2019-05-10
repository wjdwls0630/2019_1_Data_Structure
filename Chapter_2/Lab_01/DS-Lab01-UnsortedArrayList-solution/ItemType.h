
#ifndef _ITEMTYPE_H
#define _ITEMTYPE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


/**
*	Relation between two items.
*/
enum RelationType {LESS, GREATER, EQUAL};


/**
*	item information class.
*/
class ItemType
{
public:
	/**
	*	default constructor.
	*/
	ItemType()
	{
		m_Id = -1;
		m_sName = "";
		m_sAddress = "";
	}

	/**
	*	destructor.
	*/
	~ItemType()	{}

	/**
	*	@brief	Get student id.
	*	@pre	student id is set.
	*	@post	none.
	*	@return	student id.
	*/
	int GetId()
	{
		return m_Id;
	}

	/**
	*	@brief	Get student name.
	*	@pre	student name is set.
	*	@post	none.
	*	@return	student name.
	*/
	string GetName()
	{
		return m_sName;
	}

	/**
	*	@brief	Get student address
	*	@pre	student address is set.
	*	@post	none.
	*	@return	student address.
	*/
	string GetAddress()
	{
		return m_sAddress;
	}

	/**
	*	@brief	Set student id.
	*	@pre	none.
	*	@post	student id is set.
	*	@param	inId	student id.
	*/
	void SetId(int inId)
	{
		m_Id = inId;
	}
	
	/**
	*	@brief	Set student name.
	*	@pre	none.
	*	@post	student name is set.
	*	@param	inName	student name.
	*/
	void SetName(string inName)
	{
		m_sName = inName;
	}
	
	/**
	*	@brief	Set student address.
	*	@pre	none.
	*	@post	student address is set.
	*	@param	inAddress	student address.
	*/
	void SetAddress(string inAddress)
	{
		m_sAddress = inAddress;
	}
	
	/**
	*	@brief	Set student record.
	*	@pre	none.
	*	@post	student record is set.
	*	@param	inId	student id.
	*	@param	inName	student name.
	*	@param	inAddress	student address.
	*/
	void SetRecord(int inId, string inName, string inAddress)
	{
		SetId(inId);
		SetName(inName);
		SetAddress(inAddress);
	}

	/**
	*	@brief	Display student id on screen.
	*	@pre	student id is set.
	*	@post	student id is on screen.
	*/
	void DisplayIdOnScreen() 
	{
		cout << "\tID   : " << m_Id << endl; 
	};

	/**
	*	@brief	Display student name on screen.
	*	@pre	student name is set.
	*	@post	student name is on screen.
	*/
	void DisplayNameOnScreen() 
	{
		cout << "\tName : " << m_sName << endl; 
	};

	/**
	*	@brief	Display student address on screen.
	*	@pre	student address is set.
	*	@post	student address is on screen.
	*/
	void DisplayAddressOnScreen() 
	{
		cout << "\tAddress : " << m_sAddress << endl; 
	};

	/**
	*	@brief	Display an student record on screen.
	*	@pre	student record is set.
	*	@post	student record is on screen.
	*/
	void DisplayRecordOnScreen()
	{
		DisplayIdOnScreen();
		DisplayNameOnScreen();
		DisplayAddressOnScreen();
	};

	/**
	*	@brief	Set student id from keyboard.
	*	@pre	none.
	*	@post	student id is set.
	*/
	void SetIdFromKB();

	/**
	*	@brief	Set student name from keyboard.
	*	@pre	none.
	*	@post	student name is set.
	*/
	void SetNameFromKB();

	/**
	*	@brief	Set student address from keyboard.
	*	@pre	none.
	*	@post	student address is set.
	*/
	void SetAddressFromKB();
	
	/**
	*	@brief	Set student record from keyboard.
	*	@pre	none.
	*	@post	student record is set.
	*/
	void SetRecordFromKB();

	/**
	*	@brief	Read a record from file.
	*	@pre	the target file is opened.
	*	@post	student record is set.
	*	@param	fin	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ReadDataFromFile(ifstream& fin);

	/**
	*	@brief	Write a record into file.
	*	@pre	the target file is opened. And the list should be initialized.
	*	@post	the target file is included the new student record.
	*	@param	fout	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int WriteDataToFile(ofstream& fout);
	
	/**
	*	Compare two itemtypes.
	*	@brief	Compare two item types by item id.
	*	@pre	two item types should be initialized.
	*	@post	the target file is included the new item record.
	*	@param	data	target item for comparing.
	*	@return	return LESS if this.id < data.id, 
	*			return GREATER if this.id > data.id then,
	*			otherwise return EQUAL.
	*/
	RelationType CompareByID(const ItemType &data);

protected:
	int m_Id;			///< student ID.
	string m_sName;		///< student name.
	string m_sAddress;	///< student address.
};

#endif	// _ITEMTYPE_H
