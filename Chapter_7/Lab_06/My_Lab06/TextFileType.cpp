#include "TextFileType.hpp"

// Run the file by proper file application.
void TextFileType::Run(){
  TextApplication TextApp;
  TextApp.SetFileName(this->GetName());
  TextApp.Run();
  return ;
}
