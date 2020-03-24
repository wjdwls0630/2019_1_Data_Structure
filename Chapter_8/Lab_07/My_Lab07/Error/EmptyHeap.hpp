//
// Created by ParkJungJin on 2019-05-27.
//

#ifndef _EMPTYHEAP_HPP
#define _EMPTYHEAP_HPP

class EmptyHeap : public std::exception {
private:
    std::string message;
public:
    EmptyHeap ():message("Heap is Empty!"){}
    virtual const char * what() const throw(){return message.c_str();}
};

#endif //_EMPTYHEAP_HPP
