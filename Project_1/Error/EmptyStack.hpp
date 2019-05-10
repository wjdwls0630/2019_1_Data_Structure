#ifndef _EMPTYSTACK_HPP
#define _EMPTYSTACK_HPP
class EmptyStack : public std::exception {
private:
  std::string message;
public:
  EmptyStack ():message("Stack is Empty!"){}
  virtual const char * what() const throw(){return message.c_str();}
};

#endif /* _EMPTYSTACK_HPP */
