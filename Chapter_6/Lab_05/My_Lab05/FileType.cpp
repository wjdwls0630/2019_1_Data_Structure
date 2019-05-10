#include "FileType.hpp"

// Doing Deep copy by copy assignment operator.
FileType& FileType::operator= (const FileType& fi){
  if (this!=&fi) {
    ItemType::operator=(fi);
    this->fiExtensions=fi.fiExtensions;
  }
  return *this;
}

// Run the file by proper file application.
void FileType::Run(){
  TextApplication TextApp;
  JPGApplication JPGApp;
  switch (this->GetExtensionsCode()) {
    case Extensions::TXT:
    TextApp.SetFileName(this->GetName());
    TextApp.Run();
    break;
    case Extensions::JPG:
    JPGApp.SetFileName(this->GetName());
    JPGApp.Run();
    break;
    case Extensions::MP3:
    break;

  }

}
