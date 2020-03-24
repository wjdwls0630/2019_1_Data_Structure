#ifndef _FOLDERTYPE_H
#define _FOLDERTYPE_H

#include <iostream>
#include <string>
#include <iomanip>
#include <time.h>
#include <sstream>

using namespace std;

#include "SortedLinkedList.h"
#include "FileType.h"
#include "AVLtree.h"
#include "BaseType.h"

/**
*	@brief	a class that manage folders, and contents of folders
*/
class FolderType : public BaseType {
protected:
	string name;									///<folder name
	string location;								///<folder location
	int size;										///<forder size
	string date;									///<date when the folder was created
	int theNumOfFolder;								///<the number of folder inside current folder
	int theNumOfFile;								///<the number of file inside current folder
	FolderType* upperFolder;						///<pointer of pointing upper folder
	AVLtree<FolderType>* subFolderList;	///<pointer of sub folder list in linked list
	AVLtree<FileType>* subFileList;		///<pointer of sub file list in linked list
public:

	/**
	*	@brief	default constructor
	*/
	FolderType() {
		name = "C:\\";
		location = "";
		theNumOfFolder = 0;
		theNumOfFile = 0;
		size = 0;
		setDate();
		subFolderList = NULL;
		subFileList = NULL;
	}

	/**
	*	@brief	destructor
	*/
	~FolderType() {
		if (theNumOfFolder != 0) {
			subFolderList->makeEmpty();
		}
		if (theNumOfFile != 0) {
			subFileList->makeEmpty();
		}
	}

	/**
	*	@brief	get folder name
	*	@pre	folder name is set
	*	@post	none
	*	@return folder name
	*/
	virtual string getName();

	/**
	*	@brief	get folder location
	*	@pre	folder location is set
	*	@post	none
	*	@return	folder location
	*/
	virtual string getLocation();

	virtual string getLocationName();

	/**
	*	@brief	get folder size
	*	@pre	folder size is set
	*	@post	none
	*	@return	folder size
	*/
	virtual int getSize();

	/**
	*	@brief	get date of when folder was created
	*	@pre	date is set
	*	@post	none
	*	@return	date of when folder was created
	*/
	string getDate();

	/**
	*	@brief	get the number of folder inside current folder
	*	@pre	the number of folder is set
	*	@post	none
	*	@return	the number of folder inside current folder
	*/
	int getTheNumOfFolder();

	/**
	*	@brief	get the number of file inside current folder
	*	@pre	the number of file is set
	*	@post	none
	*	@return	the number of file inside current folder
	*/
	int getTheNumOfFile();

	/**
	*	@brief	get subFolderList's address(means pointer)
	*	@pre	object should be initialized
	*	@pre	folders exist in subfolder
	*	@return	return subFolderList's address(means pointer)
	*/
	AVLtree<FolderType>* getSubFolderList();

	/**
	*	@brief	get subFileList's address(means pointer)
	*	@pre	object should be initialized
	*	@pre	files exist in folder
	*	@return	return subFileList's address(means pointer)
	*/
	AVLtree<FileType>* getSubFileList();

	/**
	*	@brief	set folder name
	*	@pre	none
	*	@post	folder name is set
	*	@param	inName	folder name.
	*/
	void setName(string inName);

	/**
	*	@brief	set location of current folder
	*	@pre	none
	*	@post	folder location is set
	*	@param	inLocation	location of current folder
	*/
	void setLocation(string inLocation);

	/**
	*	@brief	set size of current folder
	*	@pre	none
	*	@post	folder size is set
	*	@param	inSize	size of folder
	*/
	void setSize(int inSize);

	/**
	*	@brief	set created date of current folder
	*	@pre	none
	*	@post	folder created date is set
	*/
	void setDate();

	/**
	*	@brief	set data memeber upperFolder's address to input data's address
	*	@post	upperFolder's address is changed to input data's address
	*	@param	upperFolder	to give address to this->upperFolder
	*/
	void setUpperFolder(FolderType* upperFolder);

	/**
	*	@brief	set name of folder obtained from user
	*	@pre	none
	*	@post	folder name is set
	*/
	void setNameFromKB();

	/**
	*	@brief	set property of folder obtained from user
	*	@pre	none
	*	@post	folder property is set
	*/
	void setPropertyFromKB();

	/**
	*	@breif	set subFolderList's address(means pointer)
	*	@pre	object should be initialized
	*	@post	subFolderList's address is set
	*	@param	ArrayList<FolderType>* inItem	new address of subfolder list
	*/
	void setSubFolderList(AVLtree<FolderType>* inItem);

	/**
	*	@breif	set subFileList's address(means pointer)
	*	@pre	object should be initialized
	*	@post	subFileList's address is set
	*	@param	ArrayList<FileType>* inItem	new address of subfile list
	*/
	void setSubFileList(AVLtree<FileType>* inItem);

	/**
	*	@brief	display current folder name
	*	@pre	folder name is set
	*	@post	folder name is displayed
	*/
	void displayName();

	/**
	*	@brief	display current folder location
	*	@pre	location of the folder is set
	*	@post	location of the folder is displayed
	*/
	void displayLocation();
	/**
	*	@brief	display folder size
	*	@pre	folder size is set
	*	@post	folder size is displayed
	*/
	void displaySize();

	/**
	*	@brief	display created date of current folder
	*	@pre	created date is set
	*	@post	created date of current folder is displayed
	*/
	void displayDate();

	/**
	*	@brief	display property of current folder
	*	@pre	property is all set
	*	@post	property of current folder is displayed
	*/
	void displayProperty();

	/**
	*	@brief	get folder name from user and add folder to subfolder list
	*	@pre	none
	*	@post	new folder is added to subfolder list
	*	@param	inItem	folder that will be added
	*	@return	return 1 if this function works well, otherwise 0
	*/
	int addFolderToSFL(FolderType& inItem);

	/**
	*	@brief	get folder name from user and delete folder from subfolder list
	*	@pre	none
	*	@post	certain folder is deleted from subfolder list
	*	@param	inItem	folder that will be deleted
	*	@return return 1 if this function works well, otherwise 0
	*/
	int deleteFolderFromSFL(FolderType& inItem);

	/**
	*	@brief	get folder name from user and delete folder temporarily from subfolder list
	*	@pre	none
	*	@post	certain folder is deleted from subfolder list
	*	@return return 1 if this function works well, otherwise 0
	*/
	int deleteFolderFromSFLtemporarily(FolderType& inItem);

	/**
	*	@brief	rename a folder in current path
	*	@pre	object should be initialized
	*	@post	a folder in current path is renamed	
	*	@param	inItem	folder that will be renamed
	*	@param	newName	new name for the folder
	*	@return	return 1 if this function works well, otherwise 0
	*/
	int renameFolder(FolderType*& inItem, const string& newName);

	/**
	*	@brief	display names of folders inside current subfolder list
	*	@pre	folder exists in subfolder list
	*	@post	names of folders inside current subfolder list are displayed
	*/
	void displaySubFolders();

	/**
	*	@brief	display the number of folder inside current folder
	*	@pre	the number of folder inside current folder is set
	*	@post	the number of folder inside current folder is displayed
	*/
	void displayTheNumOfFolder();

	/**
	*	@brief	search all folders which include the input string in current folder
	*	@pre	the object should be initialized
	*	@post	the number of found folders are set
	*	@param	FolderType& input	the input foldertype which name is the search keyword
	*	@param	int& theNumOfFound	the number of folders found
	*	@param	SortedLinkedList<FolderType*>&	the list of found folders in the form of sorted linked list
	*/
	void searchFolderName(FolderType& input, int& theNumOfFound, SortedLinkedList<FolderType*>& foundlist);

	/**
	*	@brief	search the folder which is exactly same with input
	*	@pre	the object should be initialized
	*	@param	FolderType& input	the input filetype which name is the search keyword
	*	@return	the pointer of found folder of subfolder list
	*/
	FolderType* searchExactFolderName(FolderType& input);

	/**
	*	@brief	display current folder's sublist and set input folder's address to certain folder
	*	@pre	FolderType has been initialized
	*	@post	input data's address is set to one of subfolder's address
	*	@return	return 1 if opened, otherwise 0
	*/
	int openFolderAtSFL(FolderType*& m_curFolder, const string& name);

	/**
	*	@brief	set input data's address to upperFolder's address
	*	@post	input data's address is set to upperFolder's address
	*	@return	return 1 if this function works well, otherwise 0
	*/
	int openUpperFolder(FolderType*& m_curFolder);

	/**
	*	@brief	get file name from user and add file to subfile list
	*	@pre	none
	*	@post	new file is added to subfile list
	*	@param	FileType& inItem the file that will be added to subfile list
	*	@return	return 1 if this function works well, otherwise 0
	*/
	int addFileToSFL(FileType& inItem);

	/**
	*	@brief	get file name from user and delete folder from subfile list
	*	@pre	none
	*	@post	certain folder is deleted from subfolder list
	*	@param	FileType& inItem the file that will be deleted to subfile list
	*	@return return 1 if this function works well, otherwise 0
	*/
	int deleteFileFromSFL(FileType& inItem);

	/**
	*	@brief	get file name from user and delete folder temporarily from subfile list
	*	@pre	none
	*	@post	certain folder is deleted from subfolder list
	*	@param	FileType& inItem the file that will be deleted to subfile list
	*	@return return 1 if this function works well, otherwise 0
	*/
	int deleteFileFromSFLtemporarily(FileType& inItem);

	/**
	*	@brief	rename a file in current path
	*	@pre	object should be initialized
	*	@post	a file in current path is renamed
	*	@param	m_curFolder	the pointer of current folder
	*	@return return 1 if file renamed, otherwise 0
	*/
	int renameFile(FileType*& inItem, string& newName);

	/**
	*	@brief	display names of files inside current subfile list
	*	@pre	file exists in subfile list
	*	@post	names of files inside current subfile list are displayed
	*/
	void displaySubFiles();

	/**
	*	@brief	display the number of file inside current folder
	*	@pre	the number of file inside current folder is set
	*	@post	the number of file inside current folder is displayed
	*/
	void displayTheNumOfFile();

	/**
	*	@brief	search all files which include the input string in current folder
	*	@pre	the object should be initialized
	*	@post	the number of found files are set
	*	@param	Filetype& input	the input filetype which name is the search keyword
	*	@param	int& theNumOfFound	the number of files found
	*	@return the list of found files in the form of sorted linked list
	*/
	void searchFileName(FileType& input, int& theNumOfFound, SortedLinkedList<FileType*>& foundlist);

	/**
	*	@brief	search the file which is exactly same with input
	*	@pre	the object should be initialized
	*	@param	Filetype& input	the input filetype which name is the search keyword
	*	@return	the pointer of found file of subfile list
	*/
	FileType* searchExactFileName(FileType& input);

	/**
	*	@brief	check two folders' name and location are same
	*	@param	dataBeingCompared	data which will be compared to former one
	*	@return	return true if two folders' name and location are same, otherwise false
	*/
	bool operator==(const FolderType& dataBeingCompared) const;

	/**
	*	@brief	check two folders' name compare by name
	*	@param	dataBeingCompared	data which will be compared to former one
	*	@return	return true if former folder name's ASCII code is bigger , otherwise false
	*/
	bool operator>(const FolderType& dataBeingCompared) const;

	/**
	*	@brief	check two folders' name compare by name
	*	@param	dataBeingCompared	data which will be compared to former one
	*	@return	return true if former folder name's ASCII code is smaller , otherwise false
	*/
	bool operator<(const FolderType& dataBeingCompared) const;

};

#endif _FOLDERTYPE_H

