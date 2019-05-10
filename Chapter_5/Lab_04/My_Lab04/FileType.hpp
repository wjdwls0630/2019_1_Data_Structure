#ifndef _FILETYPE_HPP
#define _FILETYPE_HPP

#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <ctime>
#include "TextApplication.hpp"


/**
*	@brief	FileType class.
*	@details	This class processes management File
*/
class FileType{
private:
  std::string fiName; // fileName
  std::string fiPath; // path from root
  std::string fiExtensions; //file extensions
  std::string fiCreatedTime; // time that File created(const)
public:
  /**
  *	default constructor.
  */
  FileType (std::string inName="untitled.txt") //default untitled
  :fiName(inName),fiExtensions(inName.substr(inName.find('.')+1)){
    this->GenerateTime(this->fiCreatedTime);
  }


  /**
  *	destructor.
  */
  ~FileType (){}

  // Set Get Display Method

  /**
  *	@brief	Get File path.
  *	@pre	File path is set.
  *	@post	none.
  *	@return	File path.
  */
  std::string GetPath() const { return this->fiPath; }

  /**
  *	@brief	Get File name.
  *	@pre	File name is set.
  *	@post	none.
  *	@return	File name.
  */
  std::string GetName() const { return this->fiName; }

  /**
  *	@brief	Get Created Time.
  *	@pre	Created Time is set.
  *	@post	none.
  *	@return	Created Time.
  */
  std::string GetCreatedTime() const { return this->fiCreatedTime; }

  /**
  *	@brief	Get Extensions.
  *	@pre	Extensions is set.
  *	@post	none.
  *	@return	Extensions.
  */
  std::string GetExtensions() const { return this->fiExtensions; }

  /**
  *	@brief	Set File path.
  *	@pre	none.
  *	@post	File path, file Name(store and out) is set.
  *	@param	inPath	File path.
  */
  void SetPath(std::string inPath) { this->fiPath=inPath; };

  /**
  *	@brief	Set File Name.
  *	@pre	none.
  *	@post	File Name is set.
  *	@param	inName	File Name.
  */
  void SetName(std::string inName) { this->fiName=inName; };

  /**
  *	@brief	Set Created Time.
  * @detail Do not use this except reading data!
  *	@pre	none.
  *	@post	Created Time is set.
  *	@param	inCreatedTime	Created Time.
  */
  void SetCreatedTime(std::string inCreatedTime) { this->fiCreatedTime=inCreatedTime; };

  /**
  *	@brief	Set Extensions.
  * @detail Do not use this except reading data!
  *	@pre	none.
  *	@post	Extensions is set.
  *	@param	inExtensions Extensions.
  */
  void SetExtensions(std::string inExtensions) { this->fiExtensions=inExtensions; };

  /**
  *	@brief	Display File Name on screen.
  *	@pre	File Name is set.
  *	@post	File Name is on screen.
  */
  void DisplayNameOnScreen(){
    std::cout <<"\t Name : " << this->fiName<<'\n';
  };

  void DisplayExtensionsOnScreen(){
    std::cout <<"Extensions : " << this->fiExtensions<<'\n' ;
  };

  /**
  *	@brief	Display File Path on screen.
  *	@pre	File Path is set.
  *	@post	File Path is on screen.
  */
  void DisplayPathOnScreen(){
    std::cout <<"\t Where : " << this->fiPath<<'\n' ;
  };

  /**
  *	@brief	Display File Created Time on screen.
  * @detail string is constructed yyyymmddhhmmss, so divide it for good looking
  *	@pre	File Created Time is set.
  *	@post	File Created Time is on screen.
  */
  void DisplayCreatedTimeOnScreen(){
    std::cout <<"\t Created : " << this->fiCreatedTime.substr(0,4)<<"."<<this->fiCreatedTime.substr(4,2)
    <<"."<<this->fiCreatedTime.substr(6,2)<<" / "<<this->fiCreatedTime.substr(8,2)<<":"<<this->fiCreatedTime.substr(10,2)<<'\n' ;
  };

  /**
  *	@brief	Display file Info on screen.
  *	@pre	file Info is set.
  *	@post	file Info is on screen.
  */
  void DisplayInfoOnScreen(){
    std::cout << '\n' << '\n';
    std::cout << "========= File Info =========" << '\n';
    this->DisplayNameOnScreen();
    this->DisplayExtensionsOnScreen();
    this->DisplayPathOnScreen();
    this->DisplayCreatedTimeOnScreen();
    std::cout << "===============================" << '\n';
  };

  /**
  *	@brief	Set File Name from keyboard.
  *	@pre	none.
  *	@post	File Name is set.
  */
  void SetNameFromKB();

  /**
  *	@brief	Set File Path from keyboard.
  *	@pre	none.
  *	@post	File Path is set.
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
  *	@brief	Comparing File name is same.
  *	@pre	none.
  *	@post	none.
  *	@param	another File type File that you want to Compare.
  *	@return	return true if name is same, otherwise false.
  */
  bool operator == (const FileType &fi) const { return this->fiPath==fi.fiPath; }

  /**
  *	@brief	Comparing File name is different.
  *	@pre	none.
  *	@post	none.
  *	@param	another File type File that you want to Compare.
  *	@return	return true if name is different, otherwise false.
  */
  bool operator!=(const FileType &fi) const { return this->fiPath!=fi.fiPath; }

  /**
  *	@brief	Comparing File name is smaller.
  *	@pre	none.
  *	@post	none.
  *	@param	another File type File that you want to Compare.
  *	@return	return true if pre is smaller than post, otherwise false.
  */
  bool operator<(const FileType &fi) const { return this->fiName<fi.fiName; }

  /**
  *	@brief	Comparing File name is bigger.
  *	@pre	none.
  *	@post	none.
  *	@param	another File type File that you want to Compare.
  *	@return	return true if pre is bigger than post, otherwise false.
  */
  bool operator>(const FileType &fi) const { return this->fiName>fi.fiName; }

  /**
  *	@brief	display File name by cout.
  *	@pre	set File name.
  *	@post	display File name on screen.
  *	@param	ostream os.
  *	@param	File to display on console.
  *	@return	return ostream filename
  */
  friend std::ostream & operator<<(std::ostream & os, const FileType & fi){ return os<<fi.fiName; }


  //File management

  /**
  *	@brief	Run the file by proper file application.
  *	@pre	none.
  *	@post	Run the file by proper file application.
  *	@param	none.
  */
  void Run();
};

#endif /* _FILETYPE_HPP */
