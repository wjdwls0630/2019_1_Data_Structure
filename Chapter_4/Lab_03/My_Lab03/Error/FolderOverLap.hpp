#ifndef _FOLDEROVERLAP_HPP
#define _FOLDEROVERLAP_HPP

class FolderOverLap : public std::exception{
  private :
    std::string message;
  public:
    FolderOverLap() :message("\t Folder overlap in the Current Folder!") {}
    const char* what() const throw(){
      return message.c_str();
    }
};
#endif /* _FOLDEROVERLAP_HPP */
