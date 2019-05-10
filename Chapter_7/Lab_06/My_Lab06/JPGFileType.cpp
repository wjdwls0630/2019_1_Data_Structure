#include "JPGFileType.hpp"

void JPGFileType::Run(){
  JPGApplication JPGApp;
  JPGApp.SetFileName(this->GetName());
  JPGApp.Run();
}
