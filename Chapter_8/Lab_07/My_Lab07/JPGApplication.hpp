#ifndef _JPGAPPLICATION_HPP
#define _JPGAPPLICATION_HPP

#include <iostream>
#include <string>
#include <fstream>
#include <opencv2/opencv.hpp>
using namespace cv;



/**
*	@brief	JPGApplication class.
*	@details	This class processes management File
*/
class JPGApplication {
private:
  Mat Image;
  std::string FileName; //filename to open
public:
  /**
  *	default constructor.
  */
  JPGApplication (const std::string &inFileName=""): FileName(inFileName){}

  /**
  *	destructor.
  */
  ~JPGApplication (){}

  void SetFileName(std::string inFileName){ this->FileName=inFileName; }

  //JPGApplication management

  /**
  *	@brief	JPGApplication driver.
  * @detail it process filestream.
  *	@pre	FileName is set.
  *	@post	process filestream.
  */
  void Run();
};



#endif /* _JPGAPPLICATION_HPP */
