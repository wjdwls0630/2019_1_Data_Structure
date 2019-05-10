#ifndef _CIRCULARQUEUE_HPP
#define _CIRCULARQUEUE_HPP
#include <iostream>
#include "Error/FullQueue.hpp"
#include "Error/EmptyQueue.hpp"

#define MAXQUEUESIZE 10


/**
*	@brief	CircularQueue class.
*	@details	This class processes as First In, First Out (FIFO), 템플릿을 적용해 다양한 변수 타입을 저장할 수 있다.
*/
template <typename T>
class CircularQueue{
public:
  /**
	*	default constructor.
	*/
	CircularQueue(int size=MAXQUEUESIZE):m_iFront(size-1),m_iRear(size-1),maxSize(size){
		this->m_Queue=new T [this->maxSize];
	}

	/**
	*	copy constructor.(deep copy)
	*/
	CircularQueue(const CircularQueue& cq):m_iFront(cq.m_iFront),m_iRear(cq.m_iRear),maxSize(cq.maxSize){
		this->m_Queue=new T[cq.maxSize];
		if (cq.GetLength()!=0) {
			if (cq.m_iFront>cq.m_iRear) {//if cq.m_iFront>cq.m_iRear
				//m_iFront initiallize value is maxSize-1,
				for (int i = (cq.m_iFront+1)%cq.maxSize; i < cq.maxSize; i++) {
					*(this->m_Queue+i)=*(cq.m_Queue+i);
				}
				for (int i = 0; i < cq.m_iRear+1; i++) {
					*(this->m_Queue+i)=*(cq.m_Queue+i);
				}
			} else{
				for (int i = cq.m_iFront+1; i < cq.m_iRear+1; i++) {
					*(this->m_Queue+i)=*(cq.m_Queue+i);
				}
			}
		}
	}

  /**
  *	destructor.
  */
	~CircularQueue() { if(this->GetLength()!=0) delete [] this->m_Queue; }

  /**
  *	@brief	Make Queue empty.
  *	@pre	none.
  *	@post	clear Queue.
  */
  void MakeEmpty();

  /**
  *	@brief	Get a number of Items in current Queue.
  *	@pre	none.
  *	@post	none.
  *	@return	number of Items in current Queue.
  */
  int GetLength() const;


  /**
	*	@brief	Check capacity of Queue is full.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if Queue capacity reached to the upper bound, otherwise return false.
	*/
	bool IsFull() const;

  /**
	*	@brief	Check capacity of Queue is empty.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if Queue capacity reached to the lower bound, otherwise return false.
	*/
  bool IsEmpty() const;

  /**
  *	@brief	Rellocate dynamic Queue, Increase Capactiy by 10.
  *	@pre	none.
  *	@post	length is increase by 10, Queue Size is also increased.
  */
  void ReAlloc();

  /**
  *	@brief	add a new data to the last of Queue. if Queue is full throw FullQueue Exception
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
  CircularQueue<T>& operator= (const CircularQueue& SQueue);
private:
  T* m_Queue;	///< Circular Queue.
	int m_iFront;	//index of one infront of the first element.
	int m_iRear;	//index of the last element.
  int maxSize;	//max Capacity of the Queue.
};

// Make Queue empty.
template <typename T>
void CircularQueue<T>::MakeEmpty(){
	this->m_iFront=this->maxSize-1;
	this->m_iRear=this->maxSize-1;	// make m_iFront, m_iRear to same value of constructor와생성자와 같은 값으로 m_iFront와 m_iRear를 변경해준다.
}


// Get a number of Items in current Queue.
template <typename T>
int CircularQueue<T>::GetLength() const{
	//max length is maxSize-1
	if (this->m_iFront>this->m_iRear) { //this->m_iFront>this->m_iRear
		return this->maxSize-this->m_iFront+this->m_iRear;
	}
	return this->m_iRear-this->m_iFront;
}

// Check capacity of Queue is full.
template <typename T>
bool CircularQueue<T>::IsFull() const{
	if((this->m_iRear+1)%this->maxSize==this->m_iFront){
    return true;	//m_iFront가 m_iRear보다 1 앞일때는 꽉 찬것이므로 1을 리턴한다.
  } else{
    return false;
  }
}

//Determines whether the queue is empty.
template <typename T>
bool CircularQueue<T>::IsEmpty() const{
	if(this->m_iFront==this->m_iRear){
    return true; //m_iFront와 m_iRear가 같은 경우는 queue가 비어있는 상태이므로 1을 리턴한다.
  } else{
    return false;
  }
}

// Rellocate dynamic Queue, Increase Capactiy by 10.
template <typename T>
void CircularQueue<T>::ReAlloc(){
  //declare new dynamic Queue to copy
  T* n_Queue= new T[this->maxSize+10];

  for (int i = 0; i < this->maxSize; i++) {
    *(n_Queue+i)=*(this->m_Queue+i);
  }
  //delete old stack
  delete [] this->m_Queue;

  //set new stack, size up
  this->m_Queue=n_Queue;
  this->maxSize+=10;

}

// add a new data to the last of Queue. if Queue is full throw FullQueue Exception
template <typename T>
void CircularQueue<T>::EnQueue(T data){
	if(this->IsFull()){
    throw FullQueue();
  }

	this->m_iRear=(this->m_iRear+1)%this->maxSize; //for circular
	this->m_Queue[this->m_iRear]=data;	//m_iRear를 1증가시켜주고 item값을 넣어준다.
}

// Remove the First data from the Queue, if Queue is empty throw EmptyQueue Exception
template <typename T>
int CircularQueue<T>::DeQueue(){
	if(this->IsEmpty()){
    throw EmptyQueue();
  }
	this->m_iFront=(this->m_iFront+1)%this->maxSize; //for circular
	return 1;
}

// Get the First data from the Queue, if Queue is empty throw EmptyQueue Exception
template <typename T>
T CircularQueue<T>::Front(){
	if(this->IsEmpty()){
    throw EmptyQueue();
  }
  return this->m_Queue[(this->m_iFront+1)%this->maxSize];
}

// Remove the First data from the Queue, and get value of removed data. if Queue is empty throw EmptyQueue Exception
template <typename T>
T* CircularQueue<T>::FrontPtr(){
	if(this->IsEmpty()){
    throw EmptyQueue();
  }
  return &this->m_Queue[(this->m_iFront+1)&this->maxSize];
}

// Doing Deep copy by copy assignment operator.
template <typename T>
CircularQueue<T>& CircularQueue<T>::operator= (const CircularQueue& SQueue){
	if (this!=&SQueue) {
		delete [] this->m_Queue;
		this->m_Queue= new T [SQueue.maxSize];
		if (SQueue.GetLength()!=0) {
			if (SQueue.m_iFront>SQueue.m_iRear) {//if cq.m_iFront>cq.m_iRear
				//m_iFront initiallize value is maxSize-1,
				for (int i = (SQueue.m_iFront+1)%SQueue.maxSize; i < SQueue.maxSize; i++) {
					*(this->m_Queue+i)=*(SQueue.m_Queue+i);
				}
				for (int i = 0; i < SQueue.m_iRear+1; i++) {
					*(this->m_Queue+i)=*(SQueue.m_Queue+i);
				}
			} else{
				for (int i = SQueue.m_iFront+1; i < SQueue.m_iRear+1; i++) {
					*(this->m_Queue+i)=*(SQueue.m_Queue+i);
				}
			}
		}
    this->m_iFront=SQueue.m_iFront;
    this->m_iRear=SQueue.m_iRear;
		this->maxSize=SQueue.maxSize;
	}
	return *this;
}


#endif /* _CIRCULARQUEUE_HPP */
