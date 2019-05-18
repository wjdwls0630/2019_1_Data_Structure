#ifndef _LINKEDQUEUE_HPP
#define _LINKEDQUEUE_HPP
#include <iostream>

#include "NodeType.hpp"
#include "../Error/EmptyQueue.hpp"

/**
*	@brief	LinkedQueue class.
*	@details	This class processes as First In, First Out (FIFO), 템플릿을 적용해 다양한 변수 타입을 저장할 수 있다.
*/
template <typename T>
class LinkedQueue{
private:
  NodeType<T> lq_Head_Node;	/// Head node for programming list more easy. It has not data, only has real head pointer
  NodeType<T>* lq_Front;	//index of one infront of the first element.
  NodeType<T>* lq_Rear;	//index of the last element.
  int lq_Length;	//max Capacity of the Queue.
public:
  /**
	*	default constructor.
	*/
	LinkedQueue():lq_Front(nullptr),lq_Rear(nullptr),lq_Length(0){}

	/**
	*	copy constructor.(deep copy)
	*/
	LinkedQueue(LinkedQueue& lq){
    this->lq_Head_Node.SetnLink(nullptr); //reset head node
    if (lq.GetLength()!=0) {
      for (int i = 0; i < lq.GetLength(); i++) {
        this->EnQueue(lq.Front()); // use EnQueue
        lq.lq_Front=lq.lq_Front->GetnLink(); //move pointer to next
      }
    }
    lq.lq_Front=lq.lq_Head_Node.GetnLink(); // reset SQueue top pointer
    //if using EnQueue it will be same as lq.lq_Length
	}

  /**
  *	destructor.
  */
	~LinkedQueue() {
    if(!this->IsEmpty()){
      this->MakeEmpty();
    }
  }

  /**
  *	@brief	Make Queue empty.
  *	@pre	none.
  *	@post	clear Queue.
  */
  void MakeEmpty() {
    while (!this->IsEmpty()) {
      this->DeQueue(); // remove front
    }
    this->lq_Front=nullptr;
    this->lq_Rear=nullptr;
    this->lq_Length=0;
  }

  /**
  *	@brief	Get a number of Items in current Queue.
  *	@pre	none.
  *	@post	none.
  *	@return	number of Items in current Queue.
  */
  int GetLength() const { return this->lq_Length; }

  /**
	*	@brief	Check capacity of Queue is empty.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if Queue capacity reached to the lower bound, otherwise return false.
	*/
  bool IsEmpty() const { return this->lq_Length==0; }

  /**
  *	@brief	add a new data to the last of Queue. 
  *	@pre	Queue should be initialized.
  *	@post	added the new data to the last of Queue.
  *	@param	data	new data.
  */
	void EnQueue(T data);

  /**
  *	@brief  Remove the First data from the Queue, if Queue is empty throw EmptyQueue Exception
  *	@pre	Queue should be initialized.
  *	@post	Remove the First data from the Queue.
	* @return if function works well, return 1.
  */
	int DeQueue();

  /**
  *	@brief  Returns the First data from the Queue, if Queue is empty throw EmptyQueue Exception
  *	@pre	Queue should be initialized.
  *	@post	Returns the First data from the Queue.
  * @return the First data.
  */
  T Front();

  /**
  *	@brief  Returns a reference of the First data from the Queue, if Queue is empty throw EmptyQueue Exception
  *	@pre	Queue should be initialized.
  *	@post	Returns reference of the First data from the Queue.
  * @return reference of the First data.
  */
  T* FrontPtr();

  /**
  *	@brief	Doing Deep copy by copy assignment operator.
  *	@pre	Queue already set info.
  *	@post	object copy data by deep.
  *	@param	Queue that you want to be copied.
  *	@return	return self-reference if self and Queue is not same object, otherwise self that unchanged.
  */
  LinkedQueue<T>& operator= (LinkedQueue<T>& LQueue);
};

// add a new data to the last of Queue. if Queue is full throw FullQueue Exception
template <typename T>
void LinkedQueue<T>::EnQueue(T data){
  NodeType<T>* NewNode;
  NewNode= new NodeType<T>; // make new node
  NewNode->SetData(data);// set node data
  if (this->IsEmpty()) { // if queue is empty
    this->lq_Head_Node.SetnLink(NewNode);
    this->lq_Front=NewNode;
    this->lq_Rear=NewNode; // first node
  } else{
    this->lq_Rear->SetnLink(NewNode); //only rear move
    this->lq_Rear=NewNode;
  }
  this->lq_Length++;
}

// Remove the First data from the Queue, if Queue is empty throw EmptyQueue Exception
template <typename T>
int LinkedQueue<T>::DeQueue(){
	if(this->IsEmpty()){
    throw EmptyQueue();
  }
	this->lq_Head_Node.SetnLink(this->lq_Front->GetnLink()); // make head ptr to next the top
  delete this->lq_Front;
  this->lq_Front=this->lq_Head_Node.GetnLink();
  if (this->lq_Front==nullptr) { // if there is no element in queue
    this->lq_Rear=nullptr;
  }
  this->lq_Length--;
	return 1;
}

// Get the First data from the Queue, if Queue is empty throw EmptyQueue Exception
template <typename T>
T LinkedQueue<T>::Front(){
	if(this->IsEmpty()){
    throw EmptyQueue();
  }
  return this->lq_Front->GetData();
}

// Remove the First data from the Queue, and get value of removed data. if Queue is empty throw EmptyQueue Exception
template <typename T>
T* LinkedQueue<T>::FrontPtr(){
	if(this->IsEmpty()){
    throw EmptyQueue();
  }
  return &this->lq_Front->GetData();
}

// Doing Deep copy by copy assignment operator.
template <typename T>
LinkedQueue<T>& LinkedQueue<T>::operator= (LinkedQueue<T>& SQueue){
	if (this!=&SQueue) {
    this->MakeEmpty();
    if (SQueue.GetLength()!=0) {
      for (int i = 0; i < SQueue.GetLength(); i++) {
        this->EnQueue(SQueue.Front()); // use EnQueue
        SQueue.lq_Front=SQueue.lq_Front->GetnLink(); //move pointer to next
      }
    }
    SQueue.lq_Front=SQueue.lq_Head_Node.GetnLink(); // reset SQueue top pointer
    //if using add it will be same as lstack.,s_Length
  }
  return *this;
}


#endif /* _LINKEDQUEUE_HPP */
