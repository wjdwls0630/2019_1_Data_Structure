#ifndef _MP3FILETYPE_HPP
#define _MP3FILETYPE_HPP

#include <string>
#include "FileType.hpp"
//#include "MP3Application.hpp"

/**
*	@brief	MP3FileType class.
*	@details	This class processes management file
*/
class MP3FileType : public FileType{
private:
  //std::string fiExtensions; // kind of extensions
public:
  /**
  *	default constructor.
  */
  MP3FileType (std::string inName="untitled")
  :FileType(inName){ this->SetExtensions(".mp3"); }

  /**
  *	copy constructor.(by deep copy)
  */
  MP3FileType(const MP3FileType& mfi)
  : FileType(mfi){ this->SetExtensions(".mp3"); }

  /**
  *	destructor.
  */
  ~MP3FileType (){}

  /**
  *	@brief	Get ItemType kind.
  *	@pre	kind is set.
  *	@post	none.
  *	@return	"File".
  */
  std::string WhatIs() const override{ return "MP3File"; }

  /**
  *	@brief	Get Extensions.
  *	@pre	Extensions is set.
  *	@post	none.
  *	@return	Extensions.
  */
  std::string GetExtensions() const override{ return ".mp3"; }

  /**
  *	@brief	Get Extensions code.
  *	@pre	Extensions is set.
  *	@post	none.
  *	@return	Extensions code(txt :0 jpg: 1 mp3 :2).
  */
  int GetExtensionsCode() const override{ return Extensions::MP3; }


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

#endif /* _MP3FILETYPE_HPP */
