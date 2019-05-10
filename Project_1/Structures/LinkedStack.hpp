#ifndef _LINKEDSTACK_HPP
#define _LINKEDSTACK_HPP

#include "NodeType.hpp"
#include "../Error/EmptyStack.hpp"



/**
*	@brief	Linked Stack class.
*	@details	This class processes as Last In, First Out (LIFO). Linked Stack
*/
template <typename T>
class LinkedStack{

private:
  NodeType<T> ls_Head_Node; /// Head node for programming list more easy. It has not data, only has real head pointer
  // head node next link is top
  NodeType<T>* ls_Top; // Top pointer( using like iterator)
  int ls_Length;	///< Number of node in the list.

public:

  /**
	*	default constructor.
	*/
  LinkedStack():ls_Top(nullptr),ls_Length(0){}
  /**
  *	copy constructor. (deep copy)
  */
  LinkedStack(const LinkedStack<T> &ls){
    this->sl_Head_Node.SetnLink(nullptr); //reset head node
    T Copy_Data;
    if (ls.ls_Length!=0) {
      for (int i = 0; i < ls.GetLength(); i++) {
        this->Push(ls.Top()); // use push
        ls.ls_Top=ls.ls_Top->GetnLink(); //move pointer to next
      }
      ls.ls_Top=ls.ls_Head_Node.GetnLink(); // reset ls top ptr
      //if using push it will be same as ls.ls_Length
    }
  }

  /**
	*	destructor.
	*/
	virtual ~LinkedStack() {
    if (!this->IsEmpty()) {
      this->MakeEmpty();
    }
  }

  /**
  *	@brief	Make Linked Stack empty.
  *	@pre	none.
  *	@post	clear Linked Stack.
  */
  void MakeEmpty(){
    while (!this->IsEmpty()) {
      this->Pop(); // remove top
    }
    this->ls_Top=nullptr;
    this->ls_Length=0;
  }

  /**
  *	@brief	Get a number of Items in current Linked Stack.
  *	@pre	none.
  *	@post	none.
  *	@return	number of Items in current Linked Stack.
  */
  int GetLength() const { return this->ls_Length; }

  /**
  *	@brief	Set a number of Items in current Linked Stack.
  *	@pre	none.
  *	@post	none.
  *	@return	number of Items in current Linked Stack.
  */
  void SetLength(int inLength) const { return this->ls_Length=inLength; }

  /**
	*	@brief	Check capacity of Linked Stack is empty.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if Linked Stack capacity reached to the lower bound, otherwise return false.
	*/
  bool IsEmpty() const { return this->ls_Length==0; }

  /**
	*	@brief	add a new data to the top of Linked Stack. if Linked Stack is full throw FullLinked Stack Exception
	*	@pre	Linked Stack should be initialized.
	*	@post	added the new data to the top of Linked Stack.
	*	@param	data	new data.
	*/
  void Push(T data);

  /**
  *	@brief  Remove the top data from the Linked Stack, if Linked Stack is empty throw EmptyLinked Stack Exception
  *	@pre	Linked Stack should be initialized.
  *	@post	Remove the top data from the Linked Stack
  */
  void Pop();

	/**
	*	@brief	Returns a copy of top item on the Linked Stack. if Linked Stack is empty throw EmptyLinked Stack Exception
	*	@pre	Linked Stack should be initialized.
	*	@post	If (Linked Stack is empty), throw EmptyLinked Stackr ; otherwise, returns top item
  * @return the top item
	*/
  T Top();

  /**
  *	@brief	Returns a reference of top item on the Linked Stack. if Linked Stack is empty throw EmptyLinked Stack Exception
  *	@pre	Linked Stack is not empty.
  *	@post	If (Linked Stack is empty), throw EmptyLinked Stack ; otherwise, returns top item
  * @return reference of the top item
  */
  T* TopPtr();

  /**
  *	@brief	Doing Deep copy by copy assignment operator.
  *	@pre	Linked Stack already set info.
  *	@post	object copy data by deep.
  *	@param	Linked Stack that you want to be copied.
  *	@return	return self-reference if self and Linked Stack is not same object, otherwise self that unchanged.
  */
  LinkedStack<T>& operator= (const LinkedStack<T> &LStack);
};




// add a new data to the top of Linked Stack. if Linked Stack is full throw FullLinked Stack Exception
template <typename T>
void LinkedStack<T>::Push(T data){
  NodeType<T>* NewNode;
  NewNode= new NodeType<T>; // make new node
  NewNode->SetData(data);// set node data
  if (this->IsEmpty()) { // if stack is empty
    this->ls_Head_Node.SetnLink(NewNode); // if no stack make new node to head
  } else{
    NewNode->SetnLink(this->ls_Head_Node.GetnLink()); //now new node be on the top
    this->ls_Head_Node.SetnLink(NewNode); // make head ptr to new node
  }
  this->ls_Top=NewNode;
  this->ls_Length++;
}


// Remove the top data from the Linked Stack, if Linked Stack is empty throw EmptyLinked Stack Exception
template <typename T>
void LinkedStack<T>::Pop(){
  if (this->IsEmpty()) { //if it is empty
    throw EmptyStack();
  }
  this->ls_Head_Node.SetnLink(this->ls_Top->GetnLink()); // make head ptr to next the top
  delete this->ls_Top;
  this->ls_Top=this->ls_Head_Node.GetnLink();
  this->ls_Length--;
}


// Returns a copy of top item on the Linked Stack.  if Linked Stack is empty throw EmptyLinked Stack Exception
// Linked Stack is not empty
template <typename T>
T LinkedStack<T>::Top(){
  if (this->IsEmpty()) {
    throw EmptyStack();
  }
	return this->ls_Top->GetData();
}

// Returns a reference of top item on the Linked Stack.  if Linked Stack is empty throw EmptyLinked Stack Exception
// Linked Stack is not empty
template <typename T>
T* LinkedStack<T>::TopPtr(){
  if (this->IsEmpty()) {
    throw EmptyStack();
  }
	return &this->ls_Top->GetData();
}

// Doing Deep copy like explicit copy constructor.
template <typename T>
LinkedStack<T>& LinkedStack<T>::operator= (const LinkedStack<T> &LStack){
	if (this!=&LStack) {
    this->MakeEmpty();
    if (LStack.GetLength()!=0) {
      for (int i = 0; i < LStack.GetLength(); i++) {
        this->Push(LStack.Top()); // use push
        LStack.ls_Top=LStack.ls_Top->GetnLink(); //move pointer to next
      }
    }
    LStack.ls_Top=LStack.ls_Head_Node.GetnLink(); // reset LStack top pointer
		//if using push it will be same as lstack.ls_Length
	}
	return *this;
}


#endif /* _LINKEDSTACK_HPP */
