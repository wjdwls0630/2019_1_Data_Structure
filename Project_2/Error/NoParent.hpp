#ifndef _NOPARENT_HPP
#define _NOPARENT_HPP

class NoParent : public std::exception{
  private :
    std::string message;
  public:
    NoParent() :message("No ParentFolder") {}
    const char* what() const throw(){
      return message.c_str();
    }
};
#endif /* _NOPARENT_HPP */
