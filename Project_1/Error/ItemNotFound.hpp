#ifndef _ITEMNOTFOUND_HPP
#define _ITEMNOTFOUND_HPP

class ItemNotFound : public std::exception{
  private :
    std::string message;
  public:
    ItemNotFound(const std::string &itname) :message("No Such File or Directory : "+itname) {}
    const char* what() const throw(){
      return message.c_str();
    }
};
#endif /* _ITEMNOTFOUND_HPP */
