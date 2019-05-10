#ifndef _EMPTYFOLDER_HPP
#define _EMPTYFOLDER_HPP
class EmptyFolder : public std::exception{
  private:
    std::string message;
  public:
    EmptyFolder() :message("Folder is Empty") {}
    const char* what() const throw(){
      return message.c_str();
    }
};
#endif /* _EMPTYFOLDER_HPP */
