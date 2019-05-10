#ifndef _INVALIDOPERATION_HPP
#define _INVALIDOPERATION_HPP

class InvalidOperation : public std::exception {
private:
  std::string message;
public:
  InvalidOperation ():message("Invalid Operation"){}
  virtual const char * what() const throw(){ return message.c_str(); }
};

#endif /* _INVALIDOPERATION_HPP */
