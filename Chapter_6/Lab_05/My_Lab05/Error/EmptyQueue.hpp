#ifndef _EMPTYQUEUE_HPP
#define _EMPTYQUEUE_HPP
class EmptyQueue : public std::exception {
private:
  std::string message;
public:
  EmptyQueue ():message("Queue is Empty!"){}
  virtual const char * what() const throw(){return message.c_str();}
};

#endif /* _EMPTYQUEUE_HPP */
