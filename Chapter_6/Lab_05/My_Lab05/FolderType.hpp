#ifndef _FOLDERTYPE_HPP
#define _FOLDERTYPE_HPP

#include "ItemType.hpp"
#include "FileType.hpp"
#include "Structures/DoublySortedLinkedList.hpp"
#include "Structures/DoublyIterator.hpp"
#include "Error/ItemNotFound.hpp"
#include "Error/EmptyFolder.hpp"
#include "Error/ItemNotFound.hpp"


/**
*	@brief	FolderType class.
*	@details	This class processes management Folder
*/
class FolderType : public ItemType{
private:
  int fdSubItemNum; // number of subitem in current folder
  int fdSubFolderNum; // number of subitem in current folder
  int fdSubFileNum; // number of subitem in current folder
  FolderType* fdParentPtr; // point this folder's parent
  DSLinkedList<FolderType>* fdSubFolderList; // subfolderlist
  DSLinkedList<FileType>* fdSubFileList; // subfolderlist

public:
  /**
  *	default constructor.
  */
  FolderType (std::string inName="untitled")
  :ItemType(inName),fdSubItemNum(0),fdSubFolderNum(0),fdSubFileNum(0){}

  /**
  *	copy constructor.(by deep copy)
  */
  FolderType(const FolderType& fd)
  : ItemType(fd){

    //File part
    if (fd.fdSubFileNum!=0) {
      this->fdSubFileList=new DSLinkedList<FileType>;
      DoublyIterator<FileType>fi_iter(*fd.fdSubFileList);
      while (!fi_iter.NextIsTail()) {
        fi_iter.Next().SetPath(fd.GetPath()+"/"+fi_iter.Cur().GetName());
        this->fdSubFileList->Add(fi_iter.Cur());
      }
    }

    //folder part
    FolderType Copy_Folder;
    if (fd.fdSubFolderNum!=0) {
      this->fdSubFolderList=new DSLinkedList<FolderType>;
      DoublyIterator<FolderType>fd_iter(*fd.fdSubFolderList);
      while (!fd_iter.NextIsTail()) {
        if (fd_iter.Next().GetSubItemNum()!=0) {
          Copy_Folder=fd_iter.Cur();
          Copy_Folder.SetPath(fd.GetPath()+"/"+Copy_Folder.GetName());
          this->fdSubFolderList->Add(Copy_Folder);
        } else{
          fd_iter.Cur().SetPath(fd.GetPath()+"/"+fd_iter.Cur().GetName());
          this->fdSubFolderList->Add(fd_iter.Cur());
        }
      }
    }
    this->fdSubFolderNum=fd.fdSubFolderNum; // set 0
    this->fdSubItemNum=fd.fdSubItemNum;
    this->fdSubFileNum=fd.fdSubFileNum; //set 0
    this->fdParentPtr=fd.fdParentPtr;
  }

  /**
  *	destructor.
  */
  ~FolderType (){

    if(this->fdSubFolderNum!=0){
      this->MakeEmptyFolder();

      //delete this->fdSubFolderList;
    } // 소멸자 recursive로 다 파괴하기

    if (this->fdSubFileNum!=0) {
      delete this->fdSubFileList;
    }
  }

  void MakeEmptyFolder(){
    FolderType* Temp_FolderPtr;
    if(this->fdSubFolderNum!=0){
      DoublyIterator<FolderType>fd_iter(*this->fdSubFolderList);
      while (!fd_iter.NextIsTail()) {
        if (fd_iter.Next().GetSubItemNum()!=0) {
          delete fd_iter.CurPtr();
        }
      }
      //delete this->fdSubFolderList;
    }

    if (this->fdSubFileNum!=0) {
      delete this->fdSubFileList;
    }
    this->fdSubFileNum=0;
    this->fdSubFolderNum=0;
    this->fdSubItemNum=0;
  }

  //Set Get Display Method

  /**
  *	@brief	Get This Folder is empty.
  *	@pre	none.
  *	@post	none.
  *	@return	if folder is not empty return true otherwise false.
  */
  bool IsEmpty(){ return this->fdSubItemNum==0; }

  /**
  *	@brief	Get ItemType kind.
  *	@pre	kind is set.
  *	@post	none.
  *	@return	"Folder".
  */
  std::string WhatIs() const override{ return "Folder"; }
  /**
  *	@brief	Get SubFolder Number.
  *	@pre	SubFolder Number is set.
  *	@post	none.
  *	@return	SubFolder Number.
  */
  int GetSubItemNum() const { return this->fdSubItemNum; }

  /**
  *	@brief	Get ParentFolder.
  *	@pre	ParentFolder is set.
  *	@post	none.
  *	@return	ParentFolder.
  */
  FolderType* GetParentPtr() const { return this->fdParentPtr; }

  /**
  *	@brief	Set SubFolderNum.
  * @detail Do not use this except reading data!
  *	@pre	none.
  *	@post	SubFolderNum is set.
  *	@param	inSubFolderNum SubFolderNum.
  */
  void SetSubItemNum(int inSubItemNum) { this->fdSubItemNum=inSubItemNum; };

  /**
  *	@brief	Set ParentFolder.
  *	@pre	none.
  *	@post	ParentFolder is set.
  *	@param	inParentPtr ParentFolder.
  */
  void SetParentPtr(FolderType* inParentPtr) { this->fdParentPtr = inParentPtr; }

  /**
  *	@brief	Set Direction (sort).
  *	@pre	none.
  *	@post	Direction is set.
  *	@param	inDirection Direction. ASCENDING(1) DESCENDING(0)
  */
  void SetDirection(int inDirection =1) {
    if(this->fdSubFolderNum!=0){
      this->fdSubFolderList->SetDirection(inDirection);
    }

    if (this->fdSubFileNum!=0) {
      this->fdSubFileList->SetDirection(inDirection);
    }
  }

  /**
  *	@brief	Display SubItemNum on screen.
  *	@pre	SubItemNum is set.
  *	@post	SubItemNum is on screen.
  */
  void DisplaySubItemNumberOnScreen(){
    std::cout <<"SubItemNum : " << this->fdSubItemNum<<'\n' ;
  };

  /**
  *	@brief	Display Folder Info on screen.
  *	@pre	Folder Info is set.
  *	@post	Folder Info is on screen.
  */
  void DisplayInfoOnScreen() override{
    std::cout << "============ Folder Info ============" << '\n';
    this->DisplayNameOnScreen();
    this->DisplayKindOnScreen();
    this->DisplaySubItemNumberOnScreen();
    this->DisplayPathOnScreen();
    this->DisplayCreatedTimeOnScreen();
    this->DisplayModifiedTimeOnScreen();
    this->DisplayAccessTimeOnScreen();
    std::cout << "=====================================" << '\n';
  };

  //operator overloading

  /**
	*	@brief	Comparing Folder path is same. (for object real same )
	*	@pre	none.
	*	@post	none.
	*	@param	another Folder type folder that you want to Compare.
	*	@return	return true if name is same, otherwise false.
	*/
  bool operator == (const FolderType &fd) const { return this->GetPath()==fd.GetPath(); }

  /**
  *	@brief	Comparing Folder path is different. (for object real different )
  *	@pre	none.
  *	@post	none.
  *	@param	another Folder type folder that you want to Compare.
  *	@return	return true if name is different, otherwise false.
  */
  bool operator!=(const FolderType &fd) const { return this->GetPath()!=fd.GetPath(); }



  /**
  *	@brief	Comparing Folder name is smaller. (by key)
  *	@pre	none.
  *	@post	none.
  *	@param	another Folder type folder that you want to Compare.
  *	@return	return true if pre is smaller than post, otherwise false.
  */
  bool operator<(const FolderType &fd) const {

    bool result;
    switch (this->GetKey()) {
      case KeyValue::NAME:
      result = this->GetName()<fd.GetName();
      break;
      case KeyValue::CREATEDTIME:
      result = this->GetCreatedTime()<fd.GetCreatedTime();
      break;
      case KeyValue::MODIFIEDTIME:
      result = this->GetModifiedTime()<fd.GetModifiedTime();
      break;
      case KeyValue::ACCESSTIME:
      result = this->GetAccessTime()<fd.GetAccessTime();
      break;
    }
    return result;
  }

  /**
  *	@brief	Comparing Folder and File name is smaller. (by key)
  *	@pre	none.
  *	@post	none.
  *	@param	another File type File that you want to Compare.
  *	@return	return true if pre is smaller than post, otherwise false.
  */
  bool operator<(const FileType &fi) const {
    bool result;
    switch (this->GetKey()) {
      case KeyValue::NAME:
      result = this->GetName()<fi.GetName();
      break;
      case KeyValue::CREATEDTIME:
      result = this->GetCreatedTime()<fi.GetCreatedTime();
      break;
      case KeyValue::MODIFIEDTIME:
      result = this->GetModifiedTime()<fi.GetModifiedTime();
      break;
      case KeyValue::ACCESSTIME:
      result = this->GetAccessTime()<fi.GetAccessTime();
      break;
    }
    return result;
  }

  /**
  *	@brief	Comparing Folder name is bigger. (by key)
  *	@pre	none.
  *	@post	none.
  *	@param	another Folder type folder that you want to Compare.
  *	@return	return true if pre is bigger than post, otherwise false.
  */
  bool operator>(const FolderType &fd) const {
    bool result;
    switch (this->GetKey()) {
      case KeyValue::NAME:
      result = this->GetName()>fd.GetName();
      break;
      case KeyValue::CREATEDTIME:
      result = this->GetCreatedTime()>fd.GetCreatedTime();
      break;
      case KeyValue::MODIFIEDTIME:
      result = this->GetModifiedTime()>fd.GetModifiedTime();
      break;
      case KeyValue::ACCESSTIME:
      result = this->GetAccessTime()>fd.GetAccessTime();
      break;
    }
    return result;
  }

  /**
  *	@brief	Doing Deep copy by copy assignment operator.
  *	@pre	data already set info.
  *	@post	object copy data by deep.
  *	@param	data that you want to be copied.
  *	@return	return self-reference if self and data is not same object, otherwise self unchanged.
  */
  FolderType& operator= (const FolderType& fd);

  /**
  *	@brief	Doing combine two different folder.
  *	@pre	folders is not same.
  *	@post	add sub items.
  *	@param	data that you want to be added.
  *	@return	return self-reference if self and data is not same object, otherwise self unchanged.
  */
  FolderType & operator+=(const FolderType &fd);

  /**
  *	@brief	display folder name by cout.
  *	@pre	set folder name.
  *	@post	display folder name on screen.
  *	@param	ostream os.
  *	@param	folder to display on console.
  *	@return	return ostream filename
  */
  friend std::ostream & operator<<(std::ostream & os, const FolderType & fd) { return os<<fd.GetName() ;}

  //SubItem management

  /**
	*	@brief	Create New Folder in Current Folder.
	* @detail If Folder name is overlap, add the number that how much is overlaped at last
	*	@pre	none.
	*	@post	Add new Folder in current Folder.
	*	@param	the Folder to add.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
  int NewFolder(FolderType Temp_Folder);

  /**
	*	@brief	Create New File in Current Folder.
	* @detail If File name is overlap, add the number that how much is overlaped at last
	*	@pre	none.
	*	@post	Add new File in current Folder.
	*	@param	the File to add.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
  int NewFile(FileType Temp_File);

  /**
	*	@brief	Delete Folder in Current Folder.
	*	@pre	SubFolder is existed, and set path.
	*	@post	Delete Folder what you want in current Folder.
	* @param	the Folder to delete.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
  int DeleteFolder(FolderType Temp_Folder); // 삭제할 폴더 정보를 읽어서 해당 폴더를 찾아서 삭제

  /**
  *	@brief	Delete File in Current Folder.
  *	@pre	SubFile is existed, and set path.
  *	@post	Delete File what you want in current Folder.
  * @param	the Folder to delete.
  *	@return	return 1 if this function works well, otherwise 0.
  */
  int DeleteFile(FileType Temp_File); // 삭제할 폴더 정보를 읽어서 해당 폴더를 찾아서 삭제

  /**
	*	@brief	Retrieve one Folder you search in Current Folder.
	*	@pre	SubFolder is existed, and set path.
	*	@post	get one Folder searched exactly in current Folder.
	* @param Target Folder that you want
	*	@return	return 1 if this function works well, otherwise 0.
	*/
  int RetrieveFolderByName(FolderType& Target_Folder);

  /**
  *	@brief	Retrieve one File you search in Current Folder.
  *	@pre	SubFile is existed, and set path
  *	@post	get one File searched exactly in current Folder.
  * @param Target File that you want
  *	@return	return 1 if this function works well, otherwise 0.
  */
  int RetrieveFileByName(FileType& Target_File);

  /**
	*	@brief	Retrieve the pointer of the one Folder you search in Current Folder.
	*	@pre	SubFolder is existed, and set path.
	*	@post	get the pointer of the one Folder searched exactly in current Folder.
	* @param Target Folder that you want
	*	@return	return the pointer of the Folder if this function works well, otherwise NULL.
	*/
	FolderType* RetrieveFolderPtrByName(FolderType& Target_Folder);

  /**
  *	@brief	Retrieve the pointer of the one File you search in Current Folder.
  *	@pre	SubFile is existed, and set path.
  *	@post	get the pointer of the one File searched exactly in current Folder.
  * @param Target File that you want
  *	@return	return the pointer of the File if this function works well, otherwise NULL.
  */
  FileType* RetrieveFilePtrByName(FileType& Target_File);

  /**
	*	@brief	Retrieve all SubItems that contain the name you search in All child folder.
	*	@pre	SubItems is existed.
	*	@post	create search folder and return.
  * @param keyword to search
	*	@return	return FolderType object which has search list for subfolderlist.
	*/
  FolderType RetrieveItemsByName(std::string KeyWord);

  /**
  *	@brief	Sort SubItem list
  *	@pre	 SubItem list is existed.
  *	@post	 SubItem list be sorted.
  * @param key(string)
  *	@return	none.
  */
  void SortSubItems(std::string Value="name");

  /**
  *	@brief	Sort SubItem list
  *	@pre	 SubItem list is existed.
  *	@post	 SubItem list be sorted.
  * @param key(int)
  *	@return	none.
  */
  void SortSubItems(int inKey=0);

  /**
  *	@brief	Display the Current Folder's SubFolder List on Screen.
  * @detail if there is no sub folders return;
  *	@pre	Current Folder Pointer must be pointed existed Folder.
  *	@post	Display the Current Folder Information on Screen.
  */
  void DisplayAllSubItems();

  /**
  *	@brief	Display the Current Folder's SubFolder List on Screen.
  * @detail if there is no sub folders return;
  *	@pre	Current Folder Pointer must be pointed existed Folder.
  *	@post	Display the Current Folder Information on Screen.
  */
  void DisplayAllSubItemsDetail();

  /**
  *	@brief	Reset all items key
  *	@pre	 items key is set.
  *	@post	 SubItem key be default.
  *	@return	none.
  */
  void ResetFolderKey();

};



#endif /* _FOLDERTYPE_HPP */
