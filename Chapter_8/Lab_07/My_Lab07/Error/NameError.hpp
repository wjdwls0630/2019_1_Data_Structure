#ifndef _NAMEERROR_HPP
#define _NAMEERROR_HPP

class NameError : public std::exception{
  private :
    std::string message;
  public:
    NameError(const std::string &itname) :message("This Name Can not be used : "+itname) {}
    const char* what() const throw(){
      return message.c_str();
    }
};
#endif /* _NAMEERROR_HPP */
