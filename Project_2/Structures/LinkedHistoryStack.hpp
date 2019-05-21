#ifndef _LINKEDHISTORYSTACK_HPP
#define _LINKEDHISTORYSTACK_HPP

#include "DoublyNodeType.hpp"
#include "../Error/EmptyStack.hpp"
#include "../Error/NoHistory.hpp"



/**
*	@brief	Linked History Stack class.
*	@details	This class processes as Last In, First Out (LIFO). Linked History Stack
            This only can be used by proper purpose
*/
template <typename T>
class LinkedHistoryStack{

private:
  DNodeType<T> lhs_Head_Node; /// Head node for programming list more easy. It has not data, only has real head pointer
  DNodeType<T> lhs_Tail_Node; /// Tail node for programming list more easy. It has not data, only has real tail pointer
  // head node next link is top
  DNodeType<T>* lhs_Top; // Top pointer( using like iterator) (always point top)
  DNodeType<T>* lhs_Cur; // Cur pointer( using like iterator) (always point current data)
  int lhs_Length;	///< Number of node in the list.

public:

  /**
	*	default constructor.
	*/
  LinkedHistoryStack():lhs_Top(nullptr),lhs_Cur(nullptr),lhs_Length(0){
    this->lhs_Head_Node.SetnLink(&this->lhs_Tail_Node); //reset head node
    this->lhs_Tail_Node.SetnLink(&this->lhs_Head_Node); //reset tail node
  }
  /**
  *	copy constructor. (deep copy)
  */
  LinkedHistoryStack(const LinkedHistoryStack<T> &lhs){
    this->lhs_Head_Node.SetnLink(&this->lhs_Tail_Node); //reset head node
    this->lhs_Tail_Node.SetnLink(&this->lhs_Head_Node); //reset tail node
    T Copy_Data;
    if (lhs.lhs_Length!=0) {
      for (int i = 0; i < lhs.GetLength(); i++) {
        this->Push(lhs.Top()); // use push
        lhs.lhs_Top=lhs.lhs_Top->GetnLink(); //move pointer to next
      }
      lhs.lhs_Top=lhs.lhs_Head_Node.GetnLink(); // reset ls top ptr
      //if using push it will be same as ls.ls_Length
    }
  }

  /**
	*	destructor.
	*/
	~LinkedHistoryStack() {
    if (!this->IsEmpty()) {
      this->MakeEmpty();
    }
  }

  /**
  *	@brief	Make Linked History Stack empty.
  *	@pre	none.
  *	@post	clear Linked History Stack.
  */
  void MakeEmpty(){
    while (!this->IsEmpty()) {
      this->Pop(); // remove top
    }
    this->lhs_Top=nullptr;
    this->lhs_Length=0;
  }

  /**
  *	@brief	Get a number of Items in current Linked History Stack.
  *	@pre	none.
  *	@post	none.
  *	@return	number of Items in current Linked History Stack.
  */
  int GetLength() const { return this->lhs_Length; }

  /**
  *	@brief	Set a number of Items in current Linked History Stack.
  *	@pre	none.
  *	@post	none.
  *	@return	number of Items in current Linked History Stack.
  */
  void SetLength(int inLength) const { return this->lhs_Length=inLength; }

  /**
	*	@brief	Check capacity of Linked History Stack is empty.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if Linked History Stack capacity reached to the lower bound, otherwise return false.
	*/
  bool IsEmpty() const { return this->lhs_Length==0; }

  //data management

  /**
	*	@brief	add a new data to the top of Linked History Stack.
  * @detail if top != cur using pop to make top ==cur
	*	@pre	Linked History Stack should be initialized.
	*	@post	added the new data to the top of Linked History Stack.
	*	@param	data	new data.
	*/
  void Push(T data);

  /**
  *	@brief  Remove the top data from the Linked History Stack, if Linked Stack is empty throw EmptyLinked Stack Exception
  *	@pre	Linked Stack should be initialized.
  *	@post	Remove the top data from the Linked Stack
  */
  void Pop();

  //iterator management

  /**
  *	@brief  Move cur pointer one node to top direction(head)
  *	@pre	Linked History Stack should be initialized.
  *	@post	cur pointer is moved on one node to top direction
  */
  void Prev();

  /**
  *	@brief  Move cur pointer one node to top opposite direction(tail)
  *	@pre	Linked History Stack should be initialized.
  *	@post	cur pointer is moved on one node to top opposite direction
  */
  void Next();

	/**
	*	@brief	Returns a copy of top item on the Linked History Stack. if Linked History Stack is empty throw EmptyLinked Stack Exception
	*	@pre	Linked History Stack should be initialized.
	*	@post	If (Linked Stack is empty), throw EmptyLinked Stackr ; otherwise, returns top item
  * @return the top item
	*/
  T Top();

  /**
  *	@brief	Returns a reference of top item on the Linked History Stack. if Linked History Stack is empty throw EmptyLinked Stack Exception
  *	@pre	Linked History Stack is not empty.
  *	@post	If (Linked Stack is empty), throw EmptyLinked Stack ; otherwise, returns top item
  * @return reference of the top item
  */
  T* TopPtr();

  /**
  *	@brief	Returns a copy of cur pointer on the Linked History Stack. if Linked Stack is empty throw EmptyLinked Stack Exception
  *	@pre	Linked Stack should be initialized.
  *	@post	If (Linked Stack is empty), throw EmptyLinked Stackr ; otherwise, returns top item
  * @return the cur item
  */
  T Cur();

  /**
  *	@brief	Returns a reference of cur pointer on the Linked History Stack. if Linked History Stack is empty throw EmptyLinked Stack Exception
  *	@pre	Linked History Stack is not empty.
  *	@post	If (Linked Stack is empty), throw EmptyLinked Stack ; otherwise, returns top item
  * @return reference of the cur item
  */
  T* CurPtr();

  /**
  *	@brief	Doing Deep copy by copy assignment operator.
  *	@pre	Linked History Stack already set info.
  *	@post	object copy data by deep.
  *	@param	Linked History Stack that you want to be copied.
  *	@return	return self-reference if self and Linked History Stack is not same object, otherwise self that unchanged.
  */
  LinkedHistoryStack<T>& operator= (const LinkedHistoryStack<T> &LHStack);
};




// add a new data to the top of Linked History Stack.
template <typename T>
void LinkedHistoryStack<T>::Push(T data){

  while ((this->lhs_Cur!=nullptr)&&(this->lhs_Cur!=this->lhs_Top)) {
    this->Pop();
  }

  DNodeType<T>* NewNode;
  NewNode= new DNodeType<T>; // make new node
  NewNode->SetData(data);// set node data
  if (this->IsEmpty()) { // if stack is empty
    this->lhs_Head_Node.SetnLink(NewNode); // if no stack make new node to head
    this->lhs_Tail_Node.SetpLink(NewNode); // if no stack make new node to head
    NewNode->SetpLink(&this->lhs_Head_Node); //set back link to head node
    NewNode->SetnLink(&this->lhs_Tail_Node); //set next link to head node
    this->lhs_Top=NewNode;
  } else{
    NewNode->SetnLink(this->lhs_Head_Node.GetnLink()); //now new node be on the top
    NewNode->SetpLink(&this->lhs_Head_Node); //set back link to head node
    this->lhs_Head_Node.SetnLink(NewNode); // make head ptr to new node
    this->lhs_Top->SetpLink(NewNode); //set back link to new node
    this->lhs_Top=NewNode;
  }

  this->lhs_Length++;
  this->lhs_Cur=this->lhs_Top;



}

// Remove the top data from the Linked History Stack, if Linked Stack is empty throw EmptyLinked Stack Exception
template <typename T>
void LinkedHistoryStack<T>::Pop(){
  if (this->IsEmpty()) { //if it is empty
    throw EmptyStack();
  }
  DNodeType<T>* Temp_Ptr = this->lhs_Top;
  this->lhs_Head_Node.SetnLink(this->lhs_Top->GetnLink()); // make head ptr to next the top
  this->lhs_Top=this->lhs_Top->GetnLink(); //move top ptr to next
  this->lhs_Top->SetpLink(&this->lhs_Head_Node); //set prev link to head node
  delete Temp_Ptr; //delete
  this->lhs_Top=this->lhs_Head_Node.GetnLink(); //set top ptr
  this->lhs_Length--; // make length -1

}

// Move cur pointer one node to top direction(head)
template <typename T>
void LinkedHistoryStack<T>::Prev(){
  if (this->IsEmpty()) { //if it is empty
    throw EmptyStack();
  }

  //if lhs_Cur is null
  if (this->lhs_Cur==nullptr) {
    this->lhs_Cur=this->lhs_Top;
  }

  if (this->lhs_Cur==this->lhs_Top) { // if cur arrive first
    throw NoHistory();
  }
  this->lhs_Cur=this->lhs_Cur->GetpLink();

}

// Move cur pointer one node to top opposite direction(tail)
template <typename T>
void LinkedHistoryStack<T>::Next(){
  if (this->IsEmpty()) { //if it is empty
    throw EmptyStack();
  }

  //if lhs_Cur is null
  if (this->lhs_Cur==nullptr) {
    this->lhs_Cur=this->lhs_Top;
  }

  if (this->lhs_Cur->GetnLink()==nullptr) { //if arrive last
    throw NoHistory();
  }
  this->lhs_Cur=this->lhs_Cur->GetnLink();

}


// Returns a copy of top item on the Linked History Stack. if Linked History Stack is empty throw EmptyLinked Stack Exception
// Linked Stack is not empty
template <typename T>
T LinkedHistoryStack<T>::Top(){
  if (this->IsEmpty()) {
    throw EmptyStack();
  }
	return this->lhs_Top->GetData();
}

// Returns a reference of top item on the Linked History Stack. if Linked History Stack is empty throw EmptyLinked Stack Exception
// Linked Stack is not empty
template <typename T>
T* LinkedHistoryStack<T>::TopPtr(){
  if (this->IsEmpty()) {
    throw EmptyStack();
  }
	return &this->lhs_Top->GetData();
}

// Returns a copy of cur pointer on the Linked History Stack. if Linked Stack is empty throw EmptyLinked Stack Exception
template <typename T>
T LinkedHistoryStack<T>::Cur(){
  if (this->IsEmpty()) {
    throw EmptyStack();
  } 
	return this->lhs_Cur->GetData();
}

// Returns a reference of cur pointer on the Linked History Stack. if Linked History Stack is empty throw EmptyLinked Stack Exception
// Linked Stack is not empty
template <typename T>
T* LinkedHistoryStack<T>::CurPtr(){
  if (this->IsEmpty()) {
    throw EmptyStack();
  }
	return &this->lhs_Cur->GetData();
}

// Doing Deep copy like explicit copy constructor.
template <typename T>
LinkedHistoryStack<T>& LinkedHistoryStack<T>::operator= (const LinkedHistoryStack<T> &LHStack){
	if (this!=&LHStack) {
    this->MakeEmpty();
    if (LHStack.GetLength()!=0) {
      for (int i = 0; i < LHStack.GetLength(); i++) {
        this->Push(LHStack.Top()); // use push
        LHStack.lhs_Top=LHStack.lhs_Top->GetnLink(); //move pointer to next
      }
    }
    LHStack.lhs_Top=LHStack.lhs_Head_Node.GetnLink(); // reset LStack top pointer
		//if using push it will be same as lstack.ls_Length
	}
	return *this;
}


#endif /* _LINKEDHISTORYSTACK_HPP */
