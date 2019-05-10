#ifndef _FILETYPE_HPP
#define _FILETYPE_HPP

#include <string>
#include "ItemType.hpp"
#include "TextApplication.hpp"
#include "JPGApplication.hpp"

enum Extensions { TXT, JPG, MP3  };


/**
*	@brief	FileType class.
*	@details	This class processes management file
*/
class FileType : public ItemType{
private:
  std::string fiExtensions; // kind of extensions
public:
  /**
  *	default constructor.
  */
  FileType (std::string inName="untitled")
  :ItemType(inName),fiExtensions(inName.substr(inName.find('.')+1)){}

  /**
  *	copy constructor.(by deep copy)
  */
  FileType(const FileType& fi)
  : ItemType(fi),fiExtensions(fi.fiExtensions){}

  /**
  *	destructor.
  */
  ~FileType (){}

  /**
  *	@brief	Get ItemType kind.
  *	@pre	kind is set.
  *	@post	none.
  *	@return	"File".
  */
  std::string WhatIs() const override{ return "File"; }

  /**
  *	@brief	Get Extensions.
  *	@pre	Extensions is set.
  *	@post	none.
  *	@return	Extensions.
  */
  std::string GetExtensions() const { return this->fiExtensions; }

  /**
  *	@brief	Get Extensions code.
  *	@pre	Extensions is set.
  *	@post	none.
  *	@return	Extensions code(txt :0 jpg: 1 mp3 :2).
  */
  int GetExtensionsCode() {
    int code = -1;
    if (this->fiExtensions=="txt") {
      code=Extensions::TXT;
    } else if (this->fiExtensions=="jpg") {
      code=Extensions::JPG;
    } else if (this->fiExtensions=="mp3") {
      code=Extensions::MP3;
    }
    return code;
  }

  /**
  *	@brief	Set Extensions.
  * @detail Do not use this except reading data!
  *	@pre	none.
  *	@post	Extensions is set.
  *	@param	inExtensions Extensions.
  */
  void SetExtensions(std::string inExtensions) { this->fiExtensions=inExtensions; };

  /**
  *	@brief	Set File Name.
  * @detail also Set Extensions
  *	@pre	none.
  *	@post	File Name is set.
  *	@param	inName	File Name.
  */
  void SetName(std::string inName) override {
    ItemType::SetName(inName);
    this->SetExtensions(inName.substr(inName.find('.')+1));
  };

  /**
  *	@brief	Display File Extensions on screen.
  *	@pre	Extensions is set.
  *	@post	Extensions is on screen.
  */
  void DisplayExtensionsOnScreen(){
    std::cout <<"Extensions : " << this->fiExtensions<<'\n' ;
  };

  /**
  *	@brief	Display file Info on screen.
  *	@pre	file Info is set.
  *	@post	file Info is on screen.
  */
  void DisplayInfoOnScreen() override{
    std::cout << "============ File Info ============" << '\n';
    this->DisplayNameOnScreen();
    this->DisplayKindOnScreen();
    this->DisplayPathOnScreen();
    this->DisplayCreatedTimeOnScreen();
    this->DisplayModifiedTimeOnScreen();
    this->DisplayAccessTimeOnScreen();
    std::cout << "===================================" << '\n';
  };

  //operator overloading

  /**
  *	@brief	Comparing File Path is same. (for object real same )
  *	@pre	none.
  *	@post	none.
  *	@param	another File type File that you want to Compare.
  *	@return	return true if Path is same, otherwise false.
  */
  bool operator == (const FileType &fi) const { return this->GetPath()==fi.GetPath(); }


  /**
  *	@brief	Comparing File Path is different.
  *	@pre	none.
  *	@post	none.
  *	@param	another File type File that you want to Compare.
  *	@return	return true if Path is different, otherwise false.
  */
  bool operator!=(const FileType &fi) const { return this->GetPath()!=fi.GetPath(); }


  /**
  *	@brief	Comparing File name is smaller. (by key)
  *	@pre	none.
  *	@post	none.
  *	@param	another File type File that you want to Compare.
  *	@return	return true if pre is smaller than post, otherwise false.
  */
  bool operator<(const FileType &fi) const {
    bool result;
    switch (this->GetKey()) {
      case NAME:
      result = this->GetName()<fi.GetName();
      break;
      case CREATEDTIME:
      result = this->GetCreatedTime()<fi.GetCreatedTime();
      break;
      case MODIFIEDTIME:
      result = this->GetModifiedTime()<fi.GetModifiedTime();
      break;
      case ACCESSTIME:
      result = this->GetAccessTime()<fi.GetAccessTime();
      break;
    }
    return result;
  }

  /**
  *	@brief	Comparing File name is bigger. (by key)
  *	@pre	none.
  *	@post	none.
  *	@param	another File type File that you want to Compare.
  *	@return	return true if pre is bigger than post, otherwise false.
  */
  bool operator>(const FileType &fi) const {
    bool result;
    switch (this->GetKey()) {
      case NAME:
      result = this->GetName()>fi.GetName();
      break;
      case CREATEDTIME:
      result = this->GetCreatedTime()>fi.GetCreatedTime();
      break;
      case MODIFIEDTIME:
      result = this->GetModifiedTime()>fi.GetModifiedTime();
      break;
      case ACCESSTIME:
      result = this->GetAccessTime()>fi.GetAccessTime();
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
  FileType& operator= (const FileType& fi);

  /**
  *	@brief	display file name by cout.
  *	@pre	set file name.
  *	@post	display file name on screen.
  *	@param	ostream os.
  *	@param	file to display on console.
  *	@return	return ostream filename
  */
  friend std::ostream & operator<<(std::ostream & os, const FileType & fi) { return os<<fi.GetName() ;}

  //File management

  /**
  *	@brief	Run the file by proper file application.
  *	@pre	none.
  *	@post	Run the file by proper file application.
  *	@param	none.
  *	@return	return 1 if this function works well, otherwise 0.
  */
  void Run();
};

#endif /* _FILETYPE_HPP */
