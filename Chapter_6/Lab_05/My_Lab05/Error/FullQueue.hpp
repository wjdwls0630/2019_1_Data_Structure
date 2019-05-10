#ifndef _FULLQUEUE_HPP
#define _FULLQUEUE_HPP
class FullQueue : public std::exception {
private:
  std::string message;
public:
  FullQueue ():message("Queue is Full!"){}
  virtual const char * what() const throw(){return message.c_str();}
};

#endif /* _FULLQUEUE_HPP */
