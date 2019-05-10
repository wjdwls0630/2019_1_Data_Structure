#ifndef _FILENOTFOUND_HPP
#define _FILENOTFOUND_HPP
class FileNotFound : public std::exception {
private:
  std::string message;
public:
  FileNotFound (const std::string &fname):message("\t File \""+fname+"\" not found!"){}
  virtual const char * what() const throw(){return message.c_str();}
};

#endif /* _FILENOTFOUND_HPP */
