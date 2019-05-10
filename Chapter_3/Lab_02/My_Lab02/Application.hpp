#ifndef _APPLICATION_HPP
#define _APPLICATION_HPP

#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include "FolderType.hpp"
#include "Error/InvalidOperation.hpp"
#include "Error/EmptyFolder.hpp"
#include "Error/NoHistory.hpp"


#define FILENAMESIZE 1024

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
	*	@brief	Retrieve and Display one Folder that the name is exactly same youin Current Folder.
	*	@pre	SubFolder is existed in Current Folder.
	*	@post	Display all Folder searched in Current Folder.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int RetrieveFolderByName();

	/**
	*	@brief	Delete Folder you search in Current Folder.
	*	@pre	SubFolder is existed in Current Folder.
	*	@post	Folder you search is deleted in Current Folder.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int DeleteFolder();

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
	*	@brief	read all Info of the Current Folder on the file, and set Folder by the data.
	*	@pre	Current Folder Pointer must be pointed existed Folder.
	*	@post	all Info of the Current Folder is set from the file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ReadDataFromFile();

	/**
	*	@brief	write all Info of the Current Folder into the file.
	*	@pre	Current Folder Pointer must be pointed existed Folder.
	*	@post	all Info of the Current Folder is stored in the output file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int WriteDataToFile();


private:
	int m_Command;			///< current command number.
	std::ifstream m_InFile;		///< input file descriptor.
	std::ofstream m_OutFile;		///< output file descriptor.
	FolderType Root;		///< root folder.
	FolderType *m_fdCurPointer; ///<<Point Current Folder
	FolderType *m_fdBackPointer; ///<<Point last Folder
	FolderType *m_fdForwardPointer; ///<<Point Front Folder
};

#endif	/* _APPLICATION_HPP */
