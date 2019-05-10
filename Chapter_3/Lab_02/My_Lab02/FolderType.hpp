#ifndef _FOLDERTYPE_HPP
#define _FOLDERTYPE_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "SortedList.hpp"
#include "Error/EmptyFolder.hpp"
#include "Error/FolderOverLap.hpp"
#include "Error/FolderNotFound.hpp"
#include "Error/DataFileNotFound.hpp"

#define FILENAMESIZE 1024

/**
*	Folder information class.
*/
class FolderType{
public:
	/**
	*	default constructor.
	*/
	FolderType(std::string inName="untitled")
	: fdSubFolderNum(0),fdName(inName){
		this->GenerateTime(this->fdCreatedTime);
		this->fdModifiedTime=this->fdCreatedTime;
	}

	/**
	*	destructor.
	*/
	~FolderType()	{ if(this->fdSubFolderNum!=0) delete this->fdFolderList; }


	/**
	*	@brief	Get SubFolder Number.
	*	@pre	SubFolder Number is set.
	*	@post	none.
	*	@return	SubFolder Number.
	*/
	int GetSubFolderNum() const { return this->fdSubFolderNum; }

	/**
	*	@brief	Get Folder path.
	*	@pre	Folder path is set.
	*	@post	none.
	*	@return	Folder path.
	*/
	std::string GetPath() const { return this->fdPath; }

	/**
	*	@brief	Get Folder name.
	*	@pre	Folder name is set.
	*	@post	none.
	*	@return	Folder name.
	*/
	std::string GetName() const { return this->fdName; }

	/**
	*	@brief	Get Created Time.
	*	@pre	Created Time is set.
	*	@post	none.
	*	@return	Created Time.
	*/
	std::string GetCreatedTime() const { return this->fdCreatedTime; }

	/**
	*	@brief	Get Modified Time.
	*	@pre	Modified Time is set.
	*	@post	none.
	*	@return	Modified Time.
	*/
	std::string GetModifiedTime() const { return this->fdModifiedTime; }

	/**
	*	@brief	Set Folder path.
	*	@pre	none.
	*	@post	Folder path, file Name(store and out) is set.
	*	@param	inPath	Folder path.
	*/
	void SetPath(std::string inPath) { this->fdPath=inPath; };

	/**
	*	@brief	Set Folder Name.
	*	@pre	none.
	*	@post	Folder Name is set.
	*	@param	inName	Folder Name.
	*/
	void SetName(std::string inName) { this->fdName=inName; };

	/**
	*	@brief	Set Created Time.
	* @detail Do not use this except reading data!
	*	@pre	none.
	*	@post	Created Time is set.
	*	@param	inCreatedTime	Created Time.
	*/
	void SetCreatedTime(std::string inCreatedTime) { this->fdCreatedTime=inCreatedTime; };

	/**
	*	@brief	Set Modified Time.
	* @detail Do not use this except reading data!
	*	@pre	none.
	*	@post	Modified Time is set.
	*	@param	inModifiedTime	Modified Time.
	*/
	void SetModifiedTime(std::string inModifiedTime) { this->fdModifiedTime=inModifiedTime; };

	/**
	*	@brief	Set SubFolderNum.
	* @detail Do not use this except reading data!
	*	@pre	none.
	*	@post	SubFolderNum is set.
	*	@param	inSubFolderNum	SubFolderNum.
	*/
	void SetSubFolderNumber(int inSubFolderNum) { this->fdSubFolderNum=inSubFolderNum; };

	/**
	*	@brief	Set Folder All Info. (For Redefinition)
	* @detail Do not use this except reading data!
	*	@pre	none.
	*	@post	Folder All Info is set.
	*	@param	inName	Folder Name.
	*	@param	inPath	Folder Path.
	*	@param	inCreatedTime	Folder inCreatedTime.
	*	@param	inModifiedTime	Folder inModifiedTime.
	*	@param	inSubFolderNum	Folder inSubFolderNum.
	*/
	void SetAllInfo(std::string inName, std::string inPath,std::string inCreatedTime, std::string inModifiedTime){
		this->SetName(inName);
		this->SetPath(inPath);
		this->SetCreatedTime(inCreatedTime);
		this->SetModifiedTime(inModifiedTime);
	};

	/**
	*	@brief	Display Folder Name on screen.
	*	@pre	Folder Name is set.
	*	@post	Folder Name is on screen.
	*/
	void DisplayNameOnScreen(){
		std::cout.width(7);
		std::cout <<" Name : " << this->fdName;
	};

	/**
	*	@brief	Display SubFolder Number on screen.
	*	@pre	SubFolder Number is set.
	*	@post	SubFolder Number is on screen.
	*/
	void DisplaySubFolderNumOnScreen(){
		std::cout.width(7);
		std::cout <<" SubFolder : " << this->fdSubFolderNum;
	};

	/**
	*	@brief	Display Folder Path on screen.
	*	@pre	Folder Path is set.
	*	@post	Folder Path is on screen.
	*/
	void DisplayPathOnScreen(){
		std::cout.width(7);
		std::cout <<" Where : " << this->fdPath ;
	};

	/**
	*	@brief	Display Folder Created Time on screen.
	*	@pre	Folder Created Time is set.
	*	@post	Folder Created Time is on screen.
	*/
	void DisplayCreatedTimeOnScreen(){
		std::cout.width(7);
		std::cout <<" Created : " << this->fdCreatedTime ;
	};

	/**
	*	@brief	Display Folder Modified Time on screen.
	*	@pre	Folder Modified Time is set.
	*	@post	Folder Modified Time is on screen.
	*/
	void DisplayModifiedTimeOnScreen(){
		std::cout.width(7);
		std::cout <<" Modified : " << this->fdModifiedTime;
	}

	/**
	*	@brief	Display Folder Info on screen.
	*	@pre	Folder Info is set.
	*	@post	Folder Info is on screen.
	*/
	void DisplayInfoOnScreen(){
		std::cout << '\n' << '\n';
		std::cout << "\t Folder Info" << '\n';
    std::cout <<"\t |";
		this->DisplayNameOnScreen();
		std::cout << " | " << '\n';
		std::cout <<"\t |";
		std::cout.width(7);
		std::cout <<" Kind : "<< "Folder";
		std::cout << " | " << '\n';

		std::cout <<"\t |";
		this->DisplaySubFolderNumOnScreen();
		std::cout << " | " << '\n';
		std::cout <<"\t |";
		this->DisplayPathOnScreen();
		std::cout << " | " << '\n';
		std::cout<<"\t |";
		this->DisplayCreatedTimeOnScreen();
		std::cout << " | " << '\n';
		std::cout <<"\t |";
		this->DisplayModifiedTimeOnScreen();
		std::cout << " | " << '\n';


	};

	/**
	*	@brief	Set Folder Name from keyboard.
	*	@pre	none.
	*	@post	Folder Name is set.
	*/
	void SetNameFromKB();

	/**
	*	@brief	Set Folder Path from keyboard.
	*	@pre	none.
	*	@post	Folder Path is set.
	*/
	void SetPathFromKB();

	/**
	*	@brief	generate string type time using the current time.
	*	@pre	none.
	*	@post	none.
	*	@param	string type data that you want to set curret time.
	*	@return	return 1
	*/
	int GenerateTime(std::string &data);

	//Operator overloading

	/**
	*	@brief	Comparing Folder name is same.
	*	@pre	none.
	*	@post	none.
	*	@param	another Folder type folder that you want to Compare.
	*	@return	return true if name is same, otherwise false.
	*/
	bool operator == (const FolderType &fd) const { return this->fdName==fd.fdName; }

	/**
	*	@brief	Comparing Folder name is different.
	*	@pre	none.
	*	@post	none.
	*	@param	another Folder type folder that you want to Compare.
	*	@return	return true if name is different, otherwise false.
	*/
	bool operator!=(const FolderType &fd) const { return this->fdName!=fd.fdName; }

	/**
	*	@brief	Comparing Folder name is smaller.
	*	@pre	none.
	*	@post	none.
	*	@param	another Folder type folder that you want to Compare.
	*	@return	return true if pre is smaller than post, otherwise false.
	*/
	bool operator<(const FolderType &fd) const { return this->fdName<fd.fdName; }

	/**
	*	@brief	Comparing Folder name is bigger.
	*	@pre	none.
	*	@post	none.
	*	@param	another Folder type folder that you want to Compare.
	*	@return	return true if pre is bigger than post, otherwise false.
	*/
	bool operator>(const FolderType &fd) const { return this->fdName>fd.fdName; }


	/**
	*	@brief	Doing Deep copy like explicit copy constructor.
	*	@pre	data already set info.
	*	@post	object copy data by deep.
	*	@param	data that you want to be copied.
	*	@return	return self-reference if self and data is not same object, otherwise self unchanged.
	*/
	FolderType& operator= (const FolderType& data);

	//Folder management

	/**
	*	@brief	Create New Folder in Current Folder.
	*	@pre	none.
	*	@post	Add new Folder in current Folder.
	*	@param	the Folder to add.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int AddFolder(FolderType Temp_Data);  // 새폴더 정보를 키보드로부터 읽어서 폴더리스트에 추가,
  //처음 폴더이며 sorteList를 동적으로 할당하여 초기화 하고 추가

	/**
	*	@brief	Delete Folder in Current Folder.
	*	@pre	SubFolder is existed.
	*	@post	Delete Folder what you want in current Folder.
	* @param *	@param	the Folder to delete.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
  int DeleteFolder(FolderType Temp_Data); // 삭제할 폴더 정보를 읽어서 해당 폴더를 찾아서 삭제


	/**
	*	@brief	Retrieve one Folder you search in Current Folder.
	*	@pre	SubFolder is existed.
	*	@post	get one Folder searched exactly in current Folder.
	* @param Folder that you want
	*	@return	return 1 if this function works well, otherwise 0.
	*/
  int RetrieveFolderByName(FolderType& Target_Folder);

	/**
	*	@brief	Retrieve the pointer of the one Folder you search in Current Folder.
	*	@pre	SubFolder is existed.
	*	@post	get the pointer of the one Folder searched exactly in current Folder.
	* @param Temp Folder that you compare
	*	@return	return the pointer of the Folder if this function works well, otherwise NULL.
	*/
	FolderType* RetrieveFolderPtrByName(FolderType& Temp_Folder);

	/**
	*	@brief	Retrieve all Folder that contain the name you search in Current Folder.
	*	@pre	SubFolder is existed.
	*	@post	Display all Folder searched in current Folder.
	*	@return	return .
	*/
  FolderType* RetrieveFoldersByName();// 검색할 폴더정보를 화면에서 읽어 검색하여 결과 출력

	/**
	*	@brief	Display SubFolders name and its info on screen.
	*	@pre	SubFolder is existed.
	*	@post	SubFolders name and its info are on screen.
	*/
	void DisplayAllFolders();// 폴더정보 화면출력


	//Data Read and Write

	/**
	*	@brief	Open a file by file descriptor as an input file.
	*	@pre	a file for reading is exist.
	*	@post	open the file for reading.
	*	@param	infilestream to open for reading.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenInFile(std::ifstream &ifs);

	/**
	*	@brief	Open a file by file descriptor as an output file.
	*	@pre	list should be initialized.
	*	@post	open the file for writing.
	*	@param	outfilestream to open for writing.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int OpenOutFile(std::ofstream &ofs);

  // Need to Modify (filename, read and write)
	/**
	*	@brief	Open a file as a read mode, read all Folder Info on the file, and set SubFolderlist by the data.
	* @detail It can be only used in root file, to modifying adapt the all file. Do not use in otherfile.
	*	@pre	The file is not opened.
	*	@post	SubFolderlist holds all records from the file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ReadDataFromFile(std::ifstream &ifs);

	/**
	*	@brief	Open a file as a write mode, and write all Folder Info into the file.
	* @detail It can be only used in root file, to modifying adapt the all file. Do not use in otherfile.
	*	@pre	The file is not opened.
	*	@post	the Folder Info is stored in the output file.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int WriteDataToFile(std::ofstream &ofs);

private:
	int fdSubFolderNum; // number of subfolder in current folder
	std::string fdPath; // path from root
	std::string fdName; // folder name
	std::string fdCreatedTime; // time that folder created(const)
	std::string fdModifiedTime; // time that folder is modified
	SortedList<FolderType>* fdFolderList; // subfolderlist
	//기타 필요한 폴더 정보 정의 ;
};

#endif	/* _FOLDERTYPE_HPP */
