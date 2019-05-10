#ifndef _APPLICATION_HPP
#define _APPLICATION_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "FolderType.hpp"
#include "FileType.hpp"
#include "Structures/Stack.hpp"
#include "Structures/CircularQueue.hpp"
#include "Error/InvalidOperation.hpp"
#include "Error/NoHistory.hpp"
#include "Error/NameError.hpp"
#include "Error/EmptyFolder.hpp"


/**
*	@brief	Application class.
*	@details	application class for item management simply.
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
  *	@brief	Check ItemType and Value is right.
  *	@pre	Value is existed.
  *	@post	value decide item type.
  * @param value
  * @return if value has '.' return 0(file), no has return 1(folder)
  */
	int CheckValueItemType(std::string Value);

	/**
	* @brief	Create New Item in Current Folder.
	* @pre	none.
	*	@post	New Item is created in Current Folder.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int NewItem();

	/**
	*	@brief	Delete Item you search in Current Folder.
	*	@pre	SubItem is existed in Current Folder.
	*	@post	Item you search is deleted in Current Folder.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int DeleteItem();

	/**
	*	@brief	Update Item Name you search in Current Folder.
	*	@pre	SubItem is existed in Current Folder.
	*	@post	Item you search is Updated Name in Current Folder.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int UpdateItemName();

	/**
	*	@brief	Change current dircectory you want.
	* @detail if you enter 2 It is move to parent dir, and 3 is move to root dir.
	*         if you enter 1, you only can go to child dir
	*	@pre	Current Folder Pointer must be pointed existed Folder.
	*	@post	Change current dircectory(current pointer)
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ChangeDirectory();

	/**
	*	@brief	Run File.
	* @detail Now we only can run TextFile by TextApplication
	*	@pre	File extension must be .txt and File is existed.
	*	@post	When Run is finishe, come back to current folder
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int RunFile();

	/**
	*	@brief	Retrieve and Display all Items that contain the name in all Child Folder.
	*	@pre	SubItem is existed in Current Folder.
	*	@post	Display all SubItems searched in current andChild Folder.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int RetrieveItemsByName();

	/**
	*	@brief	Display the Current Folder Information on Screen.
	*	@pre	Current Folder Pointer must be pointed existed Folder.
	*	@post	Display the Current Folder Information on Screen.
	*/
	void DisplayInfo();

	/**
	*	@brief	Display the Current Folder's SubItem List on Screen.
	* @detail if there is no SubItem throw EmptyFolder error;
	*	@pre	none.
	*	@post	Display the SubItem list in Current Folder on Screen.
	*/
	void DisplayAllItems();

	/**
	*	@brief	Add Folder record in Recently Folder.
	* @detail If Folder name is overlap, delete the existing Folder record.
	*	@pre	none.
	*	@post	Add Folder record in Recently Folder.
	*	@param	the Folder to add.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddRecentlyFolder(FolderType* Temp_FolderPtr);

	/**
	*	@brief	Add File record in Recently Folder.
	* @detail If Folder name is overlap, delete the existing Folder record.
	*	@pre	none.
	*	@post	Add Folder record in Recently Folder.
	*	@param	the Folder to add.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddRecentlyFile(FileType *Temp_FilePtr);

	/**
	*	@brief	Display the Recently Folder on Screen.
	*	@pre	none.
	*	@post	Display the Recently Folder Information on Screen.
	*/
	void DisplayRecentlyItems();

private:
	int m_Command;			///< current command number.
	FolderType Root;		///< root folder.
	FolderType *m_fdCurPointer; ///<<Point Current Folder
	Stack<FolderType*> m_ParentFolder; ///< store ParentFolder
	CircularQueue<FolderType*> m_RecentlyFolder; ///< store Recent FolderType
	CircularQueue<FileType*> m_RecentlyFile; ///< store Recent FolderType
};

#endif	/* _APPLICATION_HPP */
