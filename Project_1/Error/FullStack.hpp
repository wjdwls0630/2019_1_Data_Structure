#ifndef _FULLSTACK_HPP
#define _FULLSTACK_HPP
class FullStack : public std::exception {
private:
  std::string message;
public:
  FullStack ():message("Stack is Full!"){}
  virtual const char * what() const throw(){return message.c_str();}
};

#endif /* _FULLSTACK_HPP */
