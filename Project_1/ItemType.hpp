#ifndef _ITEMTYPE_HPP
#define _ITEMTYPE_HPP

#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <ctime>
#include "Structures/Comparer.hpp"

#define FILENAMESIZE 1024 //for store information

enum KeyValue { NAME, CREATEDTIME, MODIFIEDTIME, ACCESSTIME};
/**
*	@brief	Item class.
*	@details	This class processes common property management. Item information class.
*/
class ItemType{
private:
  std::string itName; // item name
  std::string itPath; // path from root
  std::string itCreatedTime; // time that item created(const)
  std::string itModifiedTime; // time that item is modified
  std::string itAccessTime; // time that item is accessed (folder enter, file run)
  int itKey; // Sort by key value (default : name)
  //(Name : 0 , CreatedTime : 1 , ModifiedTime : 2, AccessTime : 3)
  //기타 필요한 아이템 정보 정의 ;
public:
	/**
	*	default constructor.
	*/
	ItemType(std::string inName="untitled")
	: itName(inName),itKey(NAME){
		this->GenerateTime(this->itCreatedTime);
		this->itModifiedTime=this->itCreatedTime;
    this->itAccessTime=this->itCreatedTime;
	}
  /**
  *	copy constructor.(by deep copy)
  */
  ItemType(const ItemType& it)
  : itName(it.itName),itPath(it.itPath),itCreatedTime(it.itCreatedTime),itModifiedTime(it.itModifiedTime),itAccessTime(it.itAccessTime),itKey(it.itKey){}


	/**
	*	destructor.
	*/
	virtual ~ItemType()	{}

  //Get Set Display method

	/**
	*	@brief	Get Item path.
	*	@pre	Item path is set.
	*	@post	none.
	*	@return	Item path.
	*/
	std::string GetPath() const { return this->itPath; }

	/**
	*	@brief	Get Item name.
	*	@pre	Item name is set.
	*	@post	none.
	*	@return	Item name.
	*/
	std::string GetName() const{ return this->itName; }

	/**
	*	@brief	Get Created Time.
	*	@pre	Created Time is set.
	*	@post	none.
	*	@return	Created Time.
	*/
	std::string GetCreatedTime() const { return this->itCreatedTime; }

	/**
	*	@brief	Get Modified Time.
	*	@pre	Modified Time is set.
	*	@post	none.
	*	@return	Modified Time.
	*/
	std::string GetModifiedTime() const { return this->itModifiedTime; }

  /**
	*	@brief	Get Access Time.
	*	@pre	Access Time is set.
	*	@post	none.
	*	@return	Access Time.
	*/
  std::string GetAccessTime() const { return this->itAccessTime; }

  int GetKey() const { return this->itKey; }

  /**
  *	@brief	Get ItemType kind.
  *	@pre	kind is set.
  *	@post	none.
  *	@return	ItemType Kind.
  */
  virtual std::string WhatIs() const = 0 ;

	/**
	*	@brief	Set Item path.
	*	@pre	none.
	*	@post	Item path, file Name(store and out) is set.
	*	@param	inPath	Item path.
	*/
	void SetPath(std::string inPath) { this->itPath=inPath; };

	/**
	*	@brief	Set Item Name.
	*	@pre	none.
	*	@post	Item Name is set.
	*	@param	inName	Item Name.
	*/
	virtual void SetName(std::string inName) { this->itName=inName; };

	/**
	*	@brief	Set Created Time.
	* @detail Do not use this except reading data!
	*	@pre	none.
	*	@post	Created Time is set.
	*	@param	inCreatedTime	Created Time.
	*/
	void SetCreatedTime(std::string inCreatedTime) { this->itCreatedTime=inCreatedTime; };

	/**
	*	@brief	Set Modified Time.
	* @detail Do not use this except reading data!
	*	@pre	none.
	*	@post	Modified Time is set.
	*	@param	inModifiedTime	Modified Time.
	*/
	void SetModifiedTime(std::string inModifiedTime) { this->itModifiedTime=inModifiedTime; };

  /**
  *	@brief	Set Access Time.
  * @detail Do not use this except reading data!
  *	@pre	none.
  *	@post	Access Time is set.
  *	@param	inAccessTime	Access Time.
  */
  void SetAccessTime(std::string inAccessTime) { this->itAccessTime=inAccessTime; };

  /**
  *	@brief	Set KeyValue.
  *	@pre	none.
  *	@post	KeyValue is set.
  *	@param	inKey	itKey.
  */
  void SetKeyValue(std::string inKey="") { //default is name
    if (inKey=="name"||inKey=="") {
      this->itKey = KeyValue::NAME;
    } else if (inKey=="created"){
      this->itKey = KeyValue::CREATEDTIME;
    } else if (inKey=="modified"){
      this->itKey = KeyValue::MODIFIEDTIME;
    } else if (inKey=="access"){
      this->itKey = KeyValue::ACCESSTIME;
    }
  }

  /**
  *	@brief	Set KeyValue.
  *	@pre	none.
  *	@post	KeyValue is set.
  *	@param	inKey	itKey.
  */
  void SetKeyValue(int inKey=0) { //default is name
    if (inKey==0) {
      this->itKey = KeyValue::NAME;
    } else if (inKey==1){
      this->itKey = KeyValue::CREATEDTIME;
    } else if (inKey==2){
      this->itKey = KeyValue::MODIFIEDTIME;
    } else if (inKey==3){
      this->itKey = KeyValue::ACCESSTIME;
    }
  }

	/**
	*	@brief	Set Item All Info. (For Redefinition)
	* @detail Do not use this except reading data!
	*	@pre	none.
	*	@post	Item All Info is set.
	*	@param	inName	Item Name.
	*	@param	inPath	Item Path.
	*	@param	inCreatedTime	 CreatedTime.
	*	@param	inModifiedTime	Item ModifiedTime.
	*	@param	inAccessTime	Item AccessTime.
	*/
	void SetAllInfo(std::string inName, std::string inPath,std::string inCreatedTime, std::string inModifiedTime, std::string inAccessTime){
		this->SetName(inName);
		this->SetPath(inPath);
		this->SetCreatedTime(inCreatedTime);
		this->SetModifiedTime(inModifiedTime);
    this->SetAccessTime(inAccessTime);
	};

  /**
  *	@brief	Display Item Name on screen.
  *	@pre	Item Name is set.
  *	@post	Item Name is on screen.
  */
  void DisplayNameOnScreen(){
  	std::cout <<"Name : " << this->itName<<'\n';
  };

  /**
  *	@brief	Display Item Kind on screen.
  *	@pre	Item Kind is set.
  *	@post	Item Kind is on screen.
  */
  void DisplayKindOnScreen(){
    std::cout <<"Kind : " << this->WhatIs()<<'\n';
  };

  /**
  *	@brief	Display Item Path on screen.
  *	@pre	Item Path is set.
  *	@post	Item Path is on screen.
  */
  void DisplayPathOnScreen(){
  	std::cout <<"Where : " << this->itPath<<'\n' ;
  };

  /**
  *	@brief	Display Item Created Time on screen.
  *	@pre	Item Created Time is set.
  *	@post	Item Created Time is on screen.
  */
  void DisplayCreatedTimeOnScreen(){
  	std::cout <<"Created : " << this->itCreatedTime.substr(0,4)<<" "<<this->MakeMonthToWord(this->itCreatedTime.substr(4,2))<<" "<<this->itCreatedTime.substr(6,2)
    <<" "<<this->MakeHourMinuteToWord(this->itCreatedTime.substr(8,4))<<'\n';
  };

  /**
  *	@brief	Display Item Modified Time on screen.
  *	@pre	Item Modified Time is set.
  *	@post	Item Modified Time is on screen.
  */
  void DisplayModifiedTimeOnScreen(){
    std::cout <<"Modified : " << this->itModifiedTime.substr(0,4)<<" "<<this->MakeMonthToWord(this->itModifiedTime.substr(4,2))<<" "<<this->itModifiedTime.substr(6,2)
    <<" "<<this->MakeHourMinuteToWord(this->itModifiedTime.substr(8, 4))<<'\n';
  };

  /**
  *	@brief	Display Item Access Time on screen.
  *	@pre	Item Access Time is set.
  *	@post	Item Access Time is on screen.
  */
  void DisplayAccessTimeOnScreen(){
    std::cout <<"Last Opened : " << this->itAccessTime.substr(0,4)<<" "<<this->MakeMonthToWord(this->itAccessTime.substr(4,2))<<" "<<this->itAccessTime.substr(6,2)
    <<" "<<this->MakeHourMinuteToWord(this->itAccessTime.substr(8, 4))<<'\n';
  };


  /**
  *	@brief	Display Item Info on screen.
  *	@pre	Item Info is set.
  *	@post	Item Info is on screen.
  */
  virtual void DisplayInfoOnScreen() =0;

	/**
	*	@brief	Set Item Name from keyboard.
	*	@pre	none.
	*	@post	Item Name is set.
	*/
	void SetNameFromKB();

	/**
	*	@brief	Set Item Path from keyboard.
	*	@pre	none.
	*	@post	Item Path is set.
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

  /**
  *	@brief	generate Month "mm" to word
  *	@pre	none.
  *	@post	none.
  *	@param	string type month "mm" that you want to set word month.
  *	@return	return 1
  */
  std::string MakeMonthToWord(std::string month);

  /**
  *	@brief	generate hour,minute "hhmm" to Am,Pm(return)
  *	@pre	none.
  *	@post	hour is changed for am/pm.
  *	@param	string type hour_minute "hhmm" for am_pm.
  *	@return	if 00<=hour<=11 return "hh:mm am" otherwise "hh:mm pm"
  */
  // Make Hour (param) to Am,Pm(return)
  std::string MakeHourMinuteToWord(std::string time);


	//Operator overloading

	/**
	*	@brief	Comparing Item name is same.
	*	@pre	none.
	*	@post	none.
	*	@param	another Item type Item that you want to Compare.
	*	@return	return true if name is same, otherwise false.
	*/
	bool operator == (const ItemType &it) const { return this->itPath==it.itPath; }

	/**
	*	@brief	Comparing Item name is different.
	*	@pre	none.
	*	@post	none.
	*	@param	another Item type Item that you want to Compare.
	*	@return	return true if name is different, otherwise false.
	*/
	bool operator!=(const ItemType &it) const { return this->itPath!=it.itPath; }

	/**
	*	@brief	Comparing Item KeyValue is smaller.(by key)
	*	@pre	none.
	*	@post	none.
	*	@param	another Item type Item that you want to Compare.
	*	@return	return true if pre is smaller than post, otherwise false.
	*/
	bool operator<(const ItemType &it) const {
    bool result;
    switch (this->itKey) {
      case KeyValue::NAME:
      result = this->itName<it.itName;
      break;
      case KeyValue::CREATEDTIME:
      result = this->itCreatedTime<it.itCreatedTime;
      break;
      case KeyValue::MODIFIEDTIME:
      result = this->itModifiedTime<it.itModifiedTime;
      break;
      case KeyValue::ACCESSTIME:
      result = this->itAccessTime<it.itAccessTime;
      break;
    }
    return result;
  }

	/**
	*	@brief	Comparing Item name is bigger. (by key)
	*	@pre	none.
	*	@post	none.
	*	@param	another Item type Item that you want to Compare.
	*	@return	return true if pre is bigger than post, otherwise false.
	*/
	bool operator>(const ItemType &it) const {
    bool result;
    switch (this->itKey) {
      case KeyValue::NAME:
      result = this->itName>it.itName;
      break;
      case KeyValue::CREATEDTIME:
      result = this->itCreatedTime>it.itCreatedTime;
      break;
      case KeyValue::MODIFIEDTIME:
      result = this->itModifiedTime>it.itModifiedTime;
      break;
      case KeyValue::ACCESSTIME:
      result = this->itAccessTime>it.itAccessTime;
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
	ItemType& operator= (const ItemType& item);


  /**
  *	@brief	display folder name by cout.
  *	@pre	set folder name.
  *	@post	display folder name on screen.
  *	@param	ostream os.
  *	@param	folder to display on console.
  *	@return	return ostream filename
  */
  friend std::ostream & operator<<(std::ostream & os, const ItemType & it) { return os<<it.itName ;}

};

#endif	/* _ITEMTYPE_HPP */
