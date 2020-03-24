#ifndef _APPLICATION_H
#define _APPLICATION_H


#include <iostream>
using namespace std;

#include "ItemType.h"
#include "LinkedList.h"
#include "DoublyIterator.h"


/**
*	application class for item management simply.
*/
class Application
{
	
public:
	/**
	*	default constructor.
	*/
	Application()
	{
		m_nCurCommand = 0;
	}

	/**
	*	destructor.
	*/
	~Application()
	{
	}
	
	/**
	*	@brief	Program driver.
	*	@pre	program is started.
	*	@post	program is finished.
	*/
	void Run();

	/**
	*	@brief	Display command on screen and get a input from keyboard.
	*	@pre	none.
	*	@post	none.
	*	@return	user's command.
	*/
	int GetCommand();

	/**
	*	@brief	Add new record into list.
	*	@pre	list should be initialized.
	*	@post	new record is added into the list.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int InsertItem();

	/**
	*	@brief	Delete record into list.
	*	@pre	list should be not empty.
	*	@post	record is deleted into the list.
	*	@return	1 if this function works well, otherwise 0.
	*/
	int DeleteItem();

	/**
	*	@brief	Display all records in the list on screen.
	*	@pre	none.
	*	@post	none.
	*/
	void DisplayAll();

	/**
	*	@brief	Make empty list.
	*	@pre	none.
	*	@post	Make empty list in this member.
	*/
	int MakeEmpty();

	/**
	*	@brief	Retrieve item in the list.
	*	@pre	none.
	*	@post	none.
	*	@return	1 if the target item is exist in the list, otherwise 0.
	*/
	int RetrieveItem();


	/**
	*	@brief	Primary key(�й�)�� �޾� �˻��Ͽ� �ش� ������ ����.
	*	@pre	����Ʈ�� �ʱ�ȭ�Ǿ��־�� ��.
	*	@post	������� �ִ� ��� ������ ������ �Է¹޾� �����ϰ�, ���� ���� ���ٰ� ���.
	*/
	int ReplaceItem();

private:
	DoublySortedLinkedList<ItemType> m_List;	///< Linked-list for ItemType.
	int m_nCurCommand;	///< current command number
};

#endif