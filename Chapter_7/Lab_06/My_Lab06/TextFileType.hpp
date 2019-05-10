#ifndef _TEXTFILETYPE_HPP
#define _TEXTFILETYPE_HPP

#include <string>
#include "FileType.hpp"
#include "TextApplication.hpp"

/**
*	@brief	TextFileType class.
*	@details	This class processes management file
*/
class TextFileType : public FileType{
private:
  //std::string fiExtensions; // kind of extensions
public:
  /**
  *	default constructor.
  */
  TextFileType (std::string inName="untitled")
  :FileType(inName){ this->SetExtensions(".txt"); }

  /**
  *	copy constructor.(by deep copy)
  */
  TextFileType(const TextFileType& tfi)
  : FileType(tfi){ this->SetExtensions(".txt"); }

  /**
  *	destructor.
  */
  ~TextFileType (){}

  /**
  *	@brief	Get ItemType kind.
  *	@pre	kind is set.
  *	@post	none.
  *	@return	"File".
  */
  std::string WhatIs() const override{ return "TextFile"; }

  /**
  *	@brief	Get Extensions.
  *	@pre	Extensions is set.
  *	@post	none.
  *	@return	Extensions.
  */
  std::string GetExtensions() const override{ return ".txt"; }

  /**
  *	@brief	Get Extensions code.
  *	@pre	Extensions is set.
  *	@post	none.
  *	@return	Extensions code(txt :0 jpg: 1 mp3 :2).
  */
  int GetExtensionsCode() const override{ return Extensions::TXT; }


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

#endif /* _TEXTFILETYPE_HPP */
