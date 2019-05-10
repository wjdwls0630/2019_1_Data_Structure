#ifndef _DATAFILENOTFOUND_HPP
#define _DATAFILENOTFOUND_HPP

class DataFileNotFound : public std::exception{
  private :
    std::string message;
  public:
    DataFileNotFound(const std::string &fname) :message("\t Data File \""+fname+"\" not found!") {}
    const char* what() const throw(){
      return message.c_str();
    }
};
#endif /* _DATAFILENOTFOUND_HPP */
