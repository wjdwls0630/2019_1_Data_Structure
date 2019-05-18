#ifndef _TEXTAPPLICATION_HPP
#define _TEXTAPPLICATION_HPP

#include <iostream>
#include <string>
#include <fstream>


/**
*	@brief	TextApplication class.
*	@details	This class processes management File
*/
class TextApplication {
private:
  std::ifstream TAifs; //for filestream reading
  std::ofstream TAofs; //for filestream writing
  std::string FileName; //filename to open
public:
  /**
  *	default constructor.
  */
  TextApplication (const std::string &inFileName=""): FileName(inFileName){}

  /**
  *	destructor.
  */
  ~TextApplication (){}

  void SetFileName(std::string inFileName){ this->FileName=inFileName; }

  //TextApplication management

  /**
  *	@brief	TextApplication driver.
  * @detail it process filestream.
  *	@pre	FileName is set.
  *	@post	process filestream.
  */
  void Run();
};



#endif /* _TEXTAPPLICATION_HPP */
