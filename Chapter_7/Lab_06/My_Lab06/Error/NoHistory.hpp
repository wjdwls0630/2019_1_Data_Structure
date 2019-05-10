#ifndef _NOHISTORY_HPP
#define _NOHISTORY_HPP

class NoHistory : public std::exception{
  private :
    std::string message;
  public:
    NoHistory() :message("No History!") {}
    const char* what() const throw(){
      return message.c_str();
    }
};
#endif /* _NOHISTORY_HPP */
