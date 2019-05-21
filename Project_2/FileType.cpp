#include "FileType.hpp"

// Doing Deep copy by copy assignment operator.
FileType& FileType::operator= (const FileType& fi){
  if (this!=&fi) {
    ItemType::operator=(fi);
    this->fiExtensions=fi.fiExtensions;
  }
  return *this;
}
