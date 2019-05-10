#ifndef _UNSORTEDLIST_H
#define _UNSORTEDLIST_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "ItemType.h"

#define MAXSIZE 5

/**
*	array based simple unsorted list.
*/
class ArrayList
{
public:
	/**
	*	default constructor.
	*/
	ArrayList()
	{
		m_Length = 0;
		ResetList();
	}

	/**
	*	destructor.
	*/
	~ArrayList()	{}

	/**
	*	@brief	Make list empty.
	*	@pre	none.
	*	@post	clear list.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get a number of records in current list.
	*	@pre	none.
	*	@post	none.
	*	@return	number of records in current list.
	*/
	int GetLength();

	/**
	*	@brief	Check capacity of list is full.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if list capacity reached to the upper bound, otherwise return false.
	*/
	bool IsFull();

	/**
	*	@brief	Check capacity of list is empty.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if list capacity reached to the lower bound, otherwise return false.
	*/
	bool IsEmpty();

	/**
	*	@brief	add a new data into list.
	*	@pre	list should be initialized.
	*	@post	added the new record into the list.
	*	@param	data	new data.
	*	@return	return 1 if this function works well, otherwise 0.
	*/

	int Add(ItemType data);

	/**
	*	@brief	Initialize list iterator.
	*	@pre	list should be initialized.
	*	@post	iterator is reset.
	*/
	void ResetList();

	/**
	*	@brief	move list iterator to the next item in list and get that item.
	*	@pre	list and list iterator should not be initialized.
	*	@post	iterator is moved to next item.
	*	@param	data	get current iterator's item. it does not need to be initialized.
	*	@return	index of current iterator's item if is not end of list, oterwise return -1.
	*/
	int GetNextItem(ItemType& data);

	/**
	*	@brief	using member function GetNextItem and get the data which has same id in the list.
	*	@pre	list should be initialized.
	*	@param	data that you want(search) to get.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int Get(ItemType& data);

	/**
	*	@brief	using member function Get and delete the data which you want to delete in the list.
	*	@pre	list should be initialized.
	*	@post	deleted the record in the list
	*	@param	data that you want(search) to delete.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int Delete(ItemType data);

	/**
	*	@brief	using member function Get and update the data which you want to update in the list.
	*	@pre	list should be initialized.
	*	@post	updated the record for new in the list.
	*	@param	data that you want(search) to update.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int Replace(ItemType data);

private:
	ItemType m_Array[MAXSIZE];  ///< list array.
	int m_Length;				///< number of elements in list.
	int m_CurPointer;			///< iterator pointer.
};

#endif	// _UNSORTEDLIST_H
