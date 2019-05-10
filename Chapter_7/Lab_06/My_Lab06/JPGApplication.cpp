#include "JPGApplication.hpp"

// JPGApplication driver.
void JPGApplication::Run(){

  // display
  std::cout << "============ JPGApp is run ============" << '\n';
  std::cout << "File Name : "<<this->FileName << '\n';
  std::cout << "========================================" << '\n';

  //read image
  this->Image=imread("JPG/"+this->FileName,IMREAD_COLOR);
  if (this->Image.empty()) {
    std::cout << "Could not open or find the image" << '\n';
    std::cin.get(); //wait for any key press
    return; //do nothing
  }

  //make window
  std::string windowName = this->FileName;
  namedWindow(windowName, WINDOW_AUTOSIZE);
	imshow(windowName, this->Image);

  //std::stirng command ="";
  //std::getline(std::cin,command);

  //문제 esc 눌러도 사진이 안 꺼진다.
  int inkey= waitKey();
  if (inkey==0x10001B) {// if press esc
    // destory all window
    destroyAllWindows();
    return ;
  }









}
