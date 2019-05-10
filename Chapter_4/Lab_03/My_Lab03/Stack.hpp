#ifndef _STACK_HPP
#define _STACK_HPP

#include "Error/FullStack.hpp"
#include "Error/EmptyStack.hpp"

#define MAXSTACKSIZE 10

/**
*	@brief	Stack class.
*	@details	This class processes as Last In, First Out (LIFO).
*/
template <typename T>
class Stack{
public:

  /**
	*	default constructor.
	*/
  Stack(int size=MAXSTACKSIZE):m_Top(-1),maxSize(size){
    this->m_Stack=new T [this->maxSize];
  }
  /**
  *	copy constructor. (deep copy)
  */
  Stack(const Stack& st):m_Top(st.m_Top),maxSize(st.maxSize){
    this->m_Stack=new T [st.maxSize];
    if (st.GetLength()!=0) {
      for (int i = 0; i < st.GetLength(); i++) {
        *(this->m_Stack+i)=*(st.m_Stack+i);
      }
    }
  }

  /**
	*	destructor.
	*/
	~Stack() { if(this->GetLength()!=0) delete [] this->m_Stack; }

  /**
  *	@brief	Make stack empty.
  *	@pre	none.
  *	@post	clear stack.
  */
  void MakeEmpty();

  /**
  *	@brief	Get a number of Items in current stack.
  *	@pre	none.
  *	@post	none.
  *	@return	number of Items in current stack.
  */
  int GetLength() const;

  /**
	*	@brief	Check capacity of stack is full.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if stack capacity reached to the upper bound, otherwise return false.
	*/
	bool IsFull() const;

  /**
	*	@brief	Check capacity of stack is empty.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if stack capacity reached to the lower bound, otherwise return false.
	*/
  bool IsEmpty() const;

  /**
  *	@brief	Rellocate dynamic stack, Increase Capactiy by 10.
  *	@pre	none.
  *	@post	length is increase by 10, stack Size is also increased.
  */
  void ReAlloc();

  /**
	*	@brief	add a new data to the top of Stack. if stack is full throw FullStack Exception
	*	@pre	Stack should be initialized.
	*	@post	added the new data to the top of Stack.
	*	@param	data	new data.
	*/
  void Push(T data);

  /**
  *	@brief  Remove the top data from the stack, if stack is empty throw EmptyStack Exception
  *	@pre	Stack should be initialized.
  *	@post	Remove the top data from the stack
  */
  void Pop();

	/**
	*	@brief	Returns a copy of top item on the stack. if stack is empty throw EmptyStack Exception
	*	@pre	Stack should be initialized.
	*	@post	If (stack is empty), throw EmptyStackr ; otherwise, returns top item
  * @return the top item
	*/
  T Top();

  /**
  *	@brief	Returns a reference of top item on the stack. if stack is empty throw EmptyStack Exception
  *	@pre	Stack is not empty.
  *	@post	If (stack is empty), throw EmptyStack ; otherwise, returns top item
  * @return reference of the top item
  */
  T* TopPtr();

  /**
  *	@brief	Doing Deep copy by copy assignment operator.
  *	@pre	Stack already set info.
  *	@post	object copy data by deep.
  *	@param	Stack that you want to be copied.
  *	@return	return self-reference if self and Stack is not same object, otherwise self that unchanged.
  */
  Stack<T>& operator= (const Stack& SStack);

private:
  T *m_Stack;	///< Stack.
  int m_Top;	///< top of stack.
  int maxSize;		///< max Capacity of Stack.
};

// Make list empty.
template <typename T>
void Stack<T>::MakeEmpty(){
  this->m_Top = -1;
}

// Get a number of Items in current stack.
template <typename T>
int Stack<T>::GetLength() const{
  return this->m_Top+1;
}

// Check capacity of list is full.
template <typename T>
bool Stack<T>::IsFull() const{
  if (this->m_Top>this->maxSize-1) {
    return true;
  } else {
    return false;
  }
}

// Check capacity of stack is empty.
template <typename T>
bool Stack<T>::IsEmpty() const{
	if(this->m_Top == -1){
    return true;
  } else{
    return false;
  }
}

// Rellocate dynamic stack, Increase Capactiy by 10.
template <typename T>
void Stack<T>::ReAlloc(){
	//declare new dynamic stack to copy
	T* n_Stack= new T[this->maxSize+10];

	for (int i = 0; i < this->maxSize; i++) {
		*(n_Stack+i)=*(this->m_Stack+i);
	}
	//delete old stack
	delete [] this->m_Stack;

	//set new stack, size up
	this->m_Stack=n_Stack;
	this->maxSize+=10;

}

// add a new data to the top of Stack. if stack is full throw FullStack Exception
template <typename T>
void Stack<T>::Push(T data){
  if (this->IsFull()) {
    throw FullStack();
  }
  this->m_Stack[++this->m_Top]=data; //add to the top
}


// Remove the top data from the stack, if stack is empty throw EmptyStack Exception
template <typename T>
void Stack<T>::Pop(){
  if (this->IsEmpty()) {
    throw EmptyStack();
  }
  this->m_Top--;
}


// Returns a copy of top item on the stack.  if stack is empty throw EmptyStack Exception
// stack is not empty
template <typename T>
T Stack<T>::Top(){
  if (this->IsEmpty()) {
    throw EmptyStack();
  }
	return this->m_Stack[this->m_Top];
}

// Returns a reference of top item on the stack.  if stack is empty throw EmptyStack Exception
// stack is not empty
template <typename T>
T* Stack<T>::TopPtr(){
  if (this->IsEmpty()) {
    throw EmptyStack();
  }
	return &this->m_Stack[this->m_Top];
}

// Doing Deep copy like explicit copy constructor.
template <typename T>
Stack<T>& Stack<T>::operator= (const Stack& SStack){
	if (this!=&SStack) {
    delete [] this->m_Stack;
    this->m_Stack=new T[SStack.maxSize];
    if (SStack.GetLength()!=0) {
      for (int i = 0; i < SStack.GetLength(); i++) {
        *(this->m_Stack+i)=*(SStack.m_Stack+i);
      }
    }
    this->m_Top=SStack.m_Top;
		this->maxSize=SStack.maxSize;
	}
	return *this;
}


#endif /* _STACK_HPP */
