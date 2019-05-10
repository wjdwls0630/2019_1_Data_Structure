#ifndef _FOLDERNOTFOUND_HPP
#define _FOLDERNOTFOUND_HPP

class FolderNotFound : public std::exception{
  private :
    std::string message;
  public:
    FolderNotFound() :message("\t Folder is not found in the Current Folder!") {}
    const char* what() const throw(){
      return message.c_str();
    }
};
#endif /* _FOLDERNOTFOUND_HPP */
