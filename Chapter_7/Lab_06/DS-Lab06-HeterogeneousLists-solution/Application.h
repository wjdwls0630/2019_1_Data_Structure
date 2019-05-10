
/*=================================  Application Class  =======================================
- Application : The class representing an application for Lab09
=============================================================================================*/

#ifndef _APPLICATION_H
#define _APPLICATION_H


#include <iostream>
using namespace std;

#include "ItemType.h"
#include "DoublyLinkedList.h"


class Application
{
public:
	/*====================================================================================
	// Function	: default constructor, Initialize member variables.
	// Pre		: None
	// Post		: Initialize member variables.
	=====================================================================================*/
	Application();

	/*====================================================================================
	// Function	: default destructor,
	// Pre		: None
	// Post		: release all member
	=====================================================================================*/
	~Application();
	
	/*====================================================================================
	// Function: Program driver
	// Pre: none
	// Post : none
    =====================================================================================*/
	void Run();

	/*====================================================================================
	// Function: Display command on screen and get a input from keyboard
	// Pre: 
	// Post : get command number.
    =====================================================================================*/
	int GetCommand();

	void DisplayAll();

private:
	DoublyLinkedList<Polygon*> m_List;	// Base class
};

#endif