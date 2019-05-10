#include "TextApplication.hpp"

// TextApplication driver.
void TextApplication::Run(){

  // display
  std::cout << "============ TextApp is run ============" << '\n';
  std::cout << "File Name : "<<this->FileName << '\n';
  std::cout << "========================================" << '\n';

  this->TAifs.open("Text/"+this->FileName);
  std::string line;
  if (this->TAifs) {// if file found
    while (std::getline(this->TAifs,line)) {
      std::cout << line << '\n';
    }
    this->TAifs.close();
    this->TAofs.open("Text/"+this->FileName,std::ios::app); // for no losing old data.
    this->TAofs<<'\n';
  } else{
    this->TAifs.close();
    this->TAofs.open("Text/"+this->FileName,std::ios::app);
  }

  std::string write_line="";
  while (1) {
    std::getline(std::cin,line);
    if (line=="//exit") { //if //exit enter
      break;
    }
    if (write_line=="") {// if first line remove blank,
      write_line.pop_back();
      write_line+=line;
      continue;
    }
    write_line+='\n';
    write_line+=line;
  }

  // save the data
  this->TAofs<<write_line;
  this->TAofs.close();
}
