#ifndef _JPGFILETYPE_HPP
#define _JPGFILETYPE_HPP

#include <string>
#include "FileType.hpp"
#include "TextApplication.hpp"

/**
*	@brief	JPGFileType class.
*	@details	This class processes management file
*/
class JPGFileType : public FileType{
private:
  //std::string fiExtensions; // kind of extensions
public:
  /**
  *	default constructor.
  */
  JPGFileType (std::string inName="untitled")
  :FileType(inName){ this->SetExtensions(".jpg"); }

  /**
  *	copy constructor.(by deep copy)
  */
  JPGFileType(const JPGFileType& jfi)
  : FileType(jfi){ this->SetExtensions(".jpg"); }

  /**
  *	destructor.
  */
  ~JPGFileType (){}

  /**
  *	@brief	Get ItemType kind.
  *	@pre	kind is set.
  *	@post	none.
  *	@return	"File".
  */
  std::string WhatIs() const override{ return "JPGFile"; }

  /**
  *	@brief	Get Extensions.
  *	@pre	Extensions is set.
  *	@post	none.
  *	@return	Extensions.
  */
  std::string GetExtensions() const override{ return ".jpg"; }

  /**
  *	@brief	Get Extensions code.
  *	@pre	Extensions is set.
  *	@post	none.
  *	@return	Extensions code(txt :0 jpg: 1 mp3 :2).
  */
  int GetExtensionsCode() const override{ return Extensions::JPG; }


  //File management

  /**
  *	@brief	Run the file by proper file application.
  *	@pre	none.
  *	@post	Run the file by proper file application.
  *	@param	none.
  *	@return	return 1 if this function works well, otherwise 0.
  */
  void Run() override;
};

#endif /* _JPGFILETYPE_HPP */
