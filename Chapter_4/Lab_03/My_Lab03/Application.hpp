#ifndef _APPLICATION_HPP
#define _APPLICATION_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "FolderType.hpp"
#include "Stack.hpp"
#include "CircularQueue.hpp"
#include "Error/InvalidOperation.hpp"
#include "Error/NoHistory.hpp"


/**
*	application class for item management simply.
*/
class Application{
public:
	/**
	*	default constructor.
	*/
	Application():Root("Root") {
		this->Root.SetPath("Root");
		this->m_fdCurPointer=&this->Root;
	}

	/**
	*	destructor.
	*/
	~Application()	{}

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
	* @brief	Create New Folder in Current Folder.
	* @pre	none.
	*	@post	New Folder is created in Current Folder.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int NewFolder();

	/**
	*	@brief	Delete Folder you search in Current Folder.
	*	@pre	SubFolder is existed in Current Folder.
	*	@post	Folder you search is deleted in Current Folder.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int DeleteFolder();

	/**
	*	@brief	Change current dircectory you want.
	* @detail if you enter 2 It is move to parent dir, and 3 is move to root dir.
	*         if you enter 1, you only can go to child dir
	*         you also can move back and forward history(maybe using stack) (modifying...)
	*	@pre	Current Folder Pointer must be pointed existed Folder.
	*	@post	Change current dircectory(current pointer)
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ChangeDirectory();

	/**
	*	@brief	Retrieve and Display one Folder that the name is exactly same youin Current Folder.
	*	@pre	SubFolder is existed in Current Folder.
	*	@post	Display all Folder searched in Current Folder.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int RetrieveFolderByName();

	/**
	*	@brief	Retrieve and Display one Folder that the name is exactly same youin Current Folder.
	*	@pre	SubFolder is existed in Current Folder.
	*	@post	Display all Folder searched in Current Folder.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int RetrieveFoldersByName();

	/**
	*	@brief	Display the Current Folder Information on Screen.
	*	@pre	Current Folder Pointer must be pointed existed Folder.
	*	@post	Display the Current Folder Information on Screen.
	*/
	void DisplayInfo();

	/**
	*	@brief	Display the Current Folder's SubFolder List on Screen.
	* @detail if there is no sub folders return;
	*	@pre	Current Folder Pointer must be pointed existed Folder.
	*	@post	Display the Current Folder Information on Screen.
	*/
	void DisplayAllFolders();

	/**
	*	@brief	Add Folder record in Recently Folder.
	* @detail If Folder name is overlap, delete the existing Folder record.
	*	@pre	none.
	*	@post	Add Folder record in Recently Folder.
	*	@param	the Folder to add.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddRecentlyFolder(FolderType &Temp_Data);

	/**
	*	@brief	Display the Recently Folder on Screen.
	*	@pre	none.
	*	@post	Display the Recently Folder Information on Screen.
	*/
	void DisplayRecentlyFolder();

private:
	int m_Command;			///< current command number.
	FolderType Root;		///< root folder.
	FolderType *m_fdCurPointer; ///<<Point Current Folder
	Stack<FolderType> m_ParentFolder; ///< store ParentFolder
	CircularQueue<FolderType> m_RecentlyFolder; ///< store history
};

#endif	/* _APPLICATION_HPP */
