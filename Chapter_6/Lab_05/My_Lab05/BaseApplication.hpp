#ifndef _BASEAPPLICATION_HPP
#define _BASEAPPLICATION_HPP

#include <iostream>
#include <string>
#include <sstream>
#include "ItemType.hpp"
#include "FolderType.hpp"
#include "Structures/LinkedHistoryStack.hpp"
#include "Structures/LinkedQueue.hpp"
#include "Error/InvalidOperation.hpp"
#include "Error/ItemNotFound.hpp"
#include "Error/NameError.hpp"
#include "Error/NoHistory.hpp"
#include "Error/NoParent.hpp"

/**
*	@brief	BaseApplication class.
*	@details	This class processes management about Item and entire system and function
*/
class BaseApplication {
private:
  std::string m_Command; ///< command
  FolderType Root;		///< root folder.
  FolderType *m_fdCurPointer; ///<<Point Current Item
  LinkedHistoryStack<FolderType*> m_History; //store history to open information
  //LinkedQueue<std::string> m_CommandHistory // store command History
  LinkedQueue<ItemType*> m_RecentFolder; // store Recent Access item
  ItemType* Heap; //store cut and copy
public:
  /**
  *	default constructor.
  */
  BaseApplication ():Root("Root"),Heap(nullptr){
    this->Root.SetPath("Root");
    this->Root.SetParentPtr(nullptr); //set Root parent is no have
    this->m_fdCurPointer=&this->Root;
  }

  /**
  *	destructor.
  */
  ~BaseApplication (){}

  //run management

  /**
  *	@brief	Program driver.
  *	@pre	program is started.
  *	@post	program is finished.
  */
  void Run();

  /**
  *	@brief	get a command from keyboard.
  *	@pre	none.
  *	@post	none.
  * @param Command from KB
  *	@return	if function works well, return 1 otherwise 0.
  */
  int GetCommand(std::string &Command);

  /**
  *	@brief	get operation code.
  *	@pre	operation is set.
  *	@post	op code to int.
  * @param operation
  * @return op-code
  */
  int GetOpCode(std::string Operation);

  // fuction to help

  /**
  *	@brief	Check ItemType and Value is right.
  *	@pre	Value is existed.
  *	@post	value decide item type.
  * @param value
  * @return if value has '.' return 0(file), no has return 1(folder), last value has name error throw name error.
  */
  int CheckValueItemType(std::string Value);

  /**
  *	@brief	Split the path in PathQueue
  * @detail split by '/' and last word check value and return 0 or 1
  *	@pre PathQueue is Empty
  *	@post	make PathQueue split the path
  * @param path to split and container to contain path splited
  *	@return	return 1 if the last word is folder, file 0.
  */
  int PathProcessor(std::string Path, LinkedQueue<std::string> &PathQueue);

  /**
  *	@brief	using Path processor find TargetFolder
  * @detail trace the folder path
  *	@pre Target path is existed
  *	@post	make Target_FolderPtr and Temp_curFolderPtr(Target_FolderPtr's parent)
  * @param Target folder path , its Pointer and Temp_curFolderPtr(Target_FolderPtr's parent)
  *	@return	return 1 if the last word is folder, file 0.
  */
  int GetTargetFolderPtrInPath(std::string Target, FolderType*& Target_FolderPtr, FolderType* Temp_curFolderPtr=nullptr);

  /**
  *	@brief	using Path processor find TargetFile
  * @detail trace the file path
  *	@pre Target path is existed
  *	@post	make Target_FilerPtr and Temp_curFolderPtr(Target_FilePtr's parent)
  * @param Target file path , its Pointer and Temp_curFolderPtr(Target_FolderPtr's parent)
  *	@return	return 1 if the last word is folder, file 0.
  */
  int GetTargetFilePtrInPath(std::string Target, FileType*& Target_FilePtr, FolderType* Temp_curFolderPtr=nullptr);

  // system management

  /**
	* @brief	Create New Item in Current Folder.
  * @detail operation mkdir [Value] (folder) or touch [Value] (file)
            mkdir -o [Value] make folder and open
            touch -r [Value] make file and run
            it can be only controlled in current folder
	* @pre	none.
	*	@post	New Item is created in Current Folder.
  * @param Item Name to create
	*	@return	return 1 if this function works well, otherwise 0.
	*/
  int NewItem(std::string Value);

  /**
	*	@brief	Delete Item you search in Current Folder.
  * @detail operation rm [Value]
            rm * make current folder empty
            it can be only controlled in current folder
	*	@pre	SubItem is existed in Current Folder.
	*	@post	Item you search is deleted in Current Folder.
  * @param Item Name to delete
	*	@return	return 1 if this function works well, otherwise 0.
	*/
  int DeleteItem(std::string Value);

  /**
  *	@brief	Update Item Name you search in Current Folder.
  * @detail operation update [target] [value]
            it can be only controlled in current folder
  *	@pre	SubItem is existed in Current Folder.
  *	@post	Item you search is Updated Name in Current Folder.
  * @param Item Name to update, New name to update
  *	@return	return 1 if this function works well, otherwise 0.
  */
  int UpdateItemName(std::string Target, std::string Value);

  /**
  *	@brief	Run File.
  * @detail operation run [Target]
  *	@pre	Target must be file.
  *	@post	When Run is finished, come back to current folder
  * @param File Name to run
  *	@return	return 1 if this function works well, otherwise 0.
  */
  int RunFile(std::string Target);

  /**
  *	@brief	Copy Item.
  * @detail operation copy [target] [value]
                      copy [target] store on Heap
                      copy [target] [value] copy target and paste in value
                      it can be controlled in all child's path
  *	@pre	target can be folder or file but value must be folder path.
  *	@post	When copy is finished, heap store the info
  * @param path or name to copy
  *	@return	return 1 if this function works well, otherwise 0.
  */
  int CopyItem(std::string Target);

  /**
  *	@brief	cut/move Item.
  * @detail operation cut [target] [value]
                      cut [target] store on Heap and delete it
                      cut [target] [value] cut target and paste in value
                      move [target] [value] cut target and paste in value
                      it can be controlled in all child's path
  *	@pre	target can be folder or file but value must be folder path.
  *	@post	When cut is finished, heap store the info and delete item
  * @param path or name to cut
  *	@return	return 1 if this function works well, otherwise 0.
  */
  int CutItem(std::string Target);

  /**
  *	@brief	paste Item.
  * @detail operation paste [value]
                      paste [target] paste heap data to Value
                      default value is current folder
                      it can be controlled in all child's path
  *	@pre	target can be folder or file but value must be folder path.
  *	@post	When paste is finished, add heap item to value
  * @param path(Where) to paste
  *	@return	return 1 if this function works well, otherwise 0.
  */
  int Paste(std::string Value="");

  /**
  *	@brief	Retrieve and Display all Items that contain the keword in all child path.
  *	@pre	Items are existed in all child path.
  *	@post	Display all Items searched in all child path.
  * @param Keyword to search
  *	@return	none.
  */
  void SearchItemsByName(std::string Value);

  /**
  *	@brief	sort items in curret folder by value criteria.
  *	@pre	Item is existed in current folder.
  *	@post	sort items by criteria.
  * @param criteria (stirng) (default : name or "" / created, modified, access)
  *	@return	none.
  */
  void SortAllItems(std::string Value="name");

  /**
  *	@brief	sort items in curret folder by value criteria.
  *	@pre	Item is existed in current folder.
  *	@post	sort items by criteria.
  * @param criteria (int)  (default : name or ""(0) / created(1), modified(2), access(3))
  *	@return	none.
  */
  void SortAllItems(int inKey=0);

  /**
  *	@brief	Display the Current Folder's SubItem List on Screen.
  * @detail operation ls
  *	@pre	Current Folder Pointer must be pointed existed Folder.
  *	@post	Display the Current Folder SubItem Information on Screen.
  */
  void DisplayAllItems();

  /**
  *	@brief	Display the Current Folder's SubItem List of info on Screen.
  * @detail operation ls a
  *	@pre	Current Folder Pointer must be pointed existed Folder.
  *	@post	Display the Current Folder item list Information on Screen.
  */
  void DisplayAllItemsDetail();

  /**
  *	@brief	Display the Current Item Information which is in currentfolder on Screen.
  * @detail operation info [Value]
            it can be controlled only on current folder
  *	@pre	Current Folder Pointer must be pointed existed Folder and current item must be in current folder.
  *	@post	Display the Current Item Information on Screen.
  */
  void DisplayItemInfo(std::string Value);

  /**
  *	@brief	Display the Current Folder Information on Screen.
  *	@pre	Current Folder Pointer must be pointed existed Folder.
  *	@post	Display the Current Folder Information on Screen.
  */
  void DisplayCurFolderInfo();

  /**
  *	@brief	Add Item record in Recently Folder.
  * @detail If Item path is overlap, delete the existing Item record.
  *	@pre	none.
  *	@post	Add Item record in Recently Folder.
  *	@param	the Item to add.
  *	@return	return 1 if this function works well, otherwise 0.
  */
  int AddRecentItem(ItemType *Temp_Item);

  /**
  *	@brief	Display the Recent Item on Screen.
  *	@pre	none.
  *	@post	Display the Recently Item name on Screen.
  */
  void DisplayRecentFolder();
};

#endif /* _BASEAPPLICATION_HPP */
