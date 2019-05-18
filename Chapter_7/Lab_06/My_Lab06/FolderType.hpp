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
  FolderType* fdParentPtr; // point this folder's parent
  DSLinkedList<ItemType*>* fdSubItemList; // subfolderlist

public:
  /**
  *	default constructor.
  */
  FolderType (std::string inName="untitled")
  :ItemType(inName),fdSubItemNum(0){}

  /**
  *	copy constructor.(by deep copy)
  */
  FolderType(const FolderType& fd)
  : ItemType(fd){
    if (fd.fdSubItemNum!=0) {
      this->fdSubItemList=new DSLinkedList<ItemType*>;
      DoublyIterator<ItemType*>iter(*fd.fdSubItemList);
      ItemType* Copy_Folder = new FolderType; //for copy folder
      iter.Next(); // move iterator next
      while (!iter.IsTail()) {
        if (iter.Cur()->WhatIs()=="File") { // file type
          iter.Cur()->SetPath(fd.GetPath()+"/"+iter.Cur()->GetName());
          this->fdSubItemList->Add(iter.Cur());
        } else if (iter.Cur()->WhatIs()=="Folder"){ // folder type
          if (iter.Cur()->GetSubItemNum()!=0) { //if folder has sub items
            *dynamic_cast<FolderType*>(Copy_Folder) = *dynamic_cast<FolderType*>(iter.Cur()); // call recursive operator =
            Copy_Folder->SetPath(fd.GetPath()+"/"+Copy_Folder->GetName());
            this->fdSubItemList->Add(Copy_Folder);
          } else {
            iter.Cur()->SetPath(fd.GetPath()+"/"+iter.Cur()->GetName());
            this->fdSubItemList->Add(iter.Cur());
          }
          iter.Next(); //move iterator
        }
      }
    }
    this->fdSubItemNum=fd.fdSubItemNum;
    this->fdParentPtr=fd.fdParentPtr;
  }

  /**
  *	destructor.
  */
  ~FolderType (){
    if (!this->IsEmpty()) {
      this->MakeEmptyFolder();
    }
  }

  void MakeEmptyFolder(){
    if(this->fdSubItemNum!=0){
      DoublyIterator<ItemType*>iter(*this->fdSubItemList);
      while (!iter.NextIsTail()) {
        if (iter.Next()->GetSubItemNum()!=0) {
          delete iter.Cur();
        }
      }
    }
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
  int GetSubItemNum() const override{ return this->fdSubItemNum; }

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
    if(this->fdSubItemNum!=0){
      this->fdSubItemList->SetDirection(inDirection);
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
  int NewItem(ItemType* Temp_Item);

  /**
	*	@brief	Delete Folder in Current Folder.
	*	@pre	SubFolder is existed, and set path.
	*	@post	Delete Folder what you want in current Folder.
	* @param	the Folder to delete.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
  int DeleteItem(ItemType* Temp_Item); // 삭제할 폴더 정보를 읽어서 해당 폴더를 찾아서 삭제

  /**
	*	@brief	Retrieve one Folder you search in Current Folder.
	*	@pre	SubFolder is existed, and set path.
	*	@post	get one Folder searched exactly in current Folder.
	* @param Target Folder that you want
	*	@return	return 1 if this function works well, otherwise 0.
	*/
  int RetrieveItemByName(ItemType*& Target_Item);

  ItemType** RetrieveItemPtrByName(ItemType*& Target_Item);



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
