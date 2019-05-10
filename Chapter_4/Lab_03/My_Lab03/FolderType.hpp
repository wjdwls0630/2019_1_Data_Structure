#ifndef _FOLDERTYPE_HPP
#define _FOLDERTYPE_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "SortedList.hpp"
#include "Error/FolderOverLap.hpp"
#include "Error/EmptyFolder.hpp"
#include "Error/FolderNotFound.hpp"

/**
*	Folder information class.
*/
class FolderType{
public:
	/**
	*	default constructor.
	*/
	FolderType(std::string inName="untitled")
	: fdName(inName), fdSubFolderNum(0){
		this->GenerateTime(this->fdCreatedTime);
	}
	/**
	*	copy constructor.(by deep copy)
	*/
	FolderType(const FolderType& fd)
	: fdName(fd.fdName),fdPath(fd.fdPath),fdCreatedTime(fd.fdCreatedTime),fdSubFolderNum(fd.fdSubFolderNum){
		if (fd.fdSubFolderNum!=0) {
			this->fdFolderList=new SortedList<FolderType>;
			*this->fdFolderList=*fd.fdFolderList;
		}
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
	*	@brief	Set SubFolderNum.
	* @detail Do not use this except reading data!
	*	@pre	none.
	*	@post	SubFolderNum is set.
	*	@param	inSubFolderNum	SubFolderNum.
	*/
	void SetSubFolderNumber(int inSubFolderNum) { this->fdSubFolderNum=inSubFolderNum; };

	/**
	*	@brief	Display Folder Name on screen.
	*	@pre	Folder Name is set.
	*	@post	Folder Name is on screen.
	*/
	void DisplayNameOnScreen(){
		std::cout <<"\t Name : " << this->fdName<<'\n';
	};

	/**
	*	@brief	Display SubFolder Number on screen.
	*	@pre	SubFolder Number is set.
	*	@post	SubFolder Number is on screen.
	*/
	void DisplaySubFolderNumOnScreen(){
		std::cout <<"\t SubFolder : " << this->fdSubFolderNum<<'\n';
	};

	/**
	*	@brief	Display Folder Path on screen.
	*	@pre	Folder Path is set.
	*	@post	Folder Path is on screen.
	*/
	void DisplayPathOnScreen(){
		std::cout <<"\t Where : " << this->fdPath<<'\n' ;
	};

	/**
	*	@brief	Display Folder Created Time on screen.
	* @detail string is constructed yyyymmddhhmmss, so divide it for good looking
	*	@pre	Folder Created Time is set.
	*	@post	Folder Created Time is on screen.
	*/
	void DisplayCreatedTimeOnScreen(){
		std::cout <<"\t Created : " << this->fdCreatedTime.substr(0,4)<<"."<<this->fdCreatedTime.substr(4,2)
		<<"."<<this->fdCreatedTime.substr(6,2)<<" / "<<this->fdCreatedTime.substr(8,2)<<":"<<this->fdCreatedTime.substr(10,2)<<'\n' ;
	};


	/**
	*	@brief	Display Folder Info on screen.
	*	@pre	Folder Info is set.
	*	@post	Folder Info is on screen.
	*/
	void DisplayInfoOnScreen(){
		std::cout << '\n' << '\n';
		std::cout << "\t ========= Folder Info =========" << '\n';
		this->DisplayNameOnScreen();
		std::cout <<"\t Kind : "<< "Folder"<<'\n';
		this->DisplaySubFolderNumOnScreen();
		this->DisplayPathOnScreen();
		this->DisplayCreatedTimeOnScreen();
		std::cout << "\t ===============================" << '\n';
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
	*	@brief	Doing Deep copy by copy assignment operator.
	*	@pre	data already set info.
	*	@post	object copy data by deep.
	*	@param	data that you want to be copied.
	*	@return	return self-reference if self and data is not same object, otherwise self unchanged.
	*/
	FolderType& operator= (const FolderType& data);

	/**
	*	@brief	display folder name by cout.
	*	@pre	set folder name.
	*	@post	display folder name on screen.
	*	@param	ostream os.
	*	@param	folder to display on console.
	*	@return	return ostream filename
	*/
	friend std::ostream & operator<<(std::ostream & os, const FolderType & fd);

	//Folder management

	/**
	*	@brief	Create New Folder in Current Folder.
	* @detail If Folder name is overlap, add the number that how much is overlaped at last
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
	*	@post	create search folder and retrun.
	*	@return	return FolderType object which has search list for subfolderlist.
	*/
  FolderType RetrieveFoldersByName(std::string KeyWord);

	/**
	*	@brief	Display SubFolders name on screen.
	*	@pre	SubFolder is existed.
	*	@post	SubFolders name and its info are on screen.
	*/
	void DisplayAllSubFolders();

private:
	std::string fdName; // folder name
	std::string fdPath; // path from root
	std::string fdCreatedTime; // time that folder created(const)
	int fdSubFolderNum; // number of subfolder in current folder
	SortedList<FolderType>* fdFolderList; // subfolderlist
	//기타 필요한 폴더 정보 정의 ;
};

#endif	/* _FOLDERTYPE_HPP */
