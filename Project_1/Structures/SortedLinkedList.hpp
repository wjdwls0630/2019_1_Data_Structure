#ifndef _SORTEDLINKEDLIST_HPP
#define _SORTEDLINKEDLIST_HPP

#include "NodeType.hpp"
#include "Comparer.hpp"
#define ASCENDING 1
#define DESCENDING 0

/**
*	@brief	SortedLinkedList class.
*	@details	This class processes as connected by NodeType next pointer, only can access by sequential
*/
template <typename T>
class SLinkedList {
private:

  NodeType<T> sl_Head_Node; /// Head node for programming list more easy. It has not data, only has real head pointer
  NodeType<T>* sl_CurPointer;	///< Node pointer for pointing current node to use iteration.
  NodeType<T>* sl_PrePointer;	///< Node pointer for pointing pre node to use iteration.
  int sl_Length;	///< Number of node in the list.
  int sl_Direction; /// ASCENDING(1), DESCENDING(0)
  Comparer<T> sl_Comparer; /// set Compare (for direction)

  //For Sort No fix and do not use alone

  // Sorts the linked list by changing next pointers (not data)

  /**
  *	@brief	sorted by merge sort
  * @detail split the list until length is one, and compare and last merge
  *	@pre	list should be initialized.
  *	@param	reference of head node.
  *	@return	none.
  */
  void MergeSort(NodeType<T>** refHead){
    NodeType<T>* Head = *refHead;
    NodeType<T>* Left;
    NodeType<T>* Right;

    if (Head==nullptr||Head->GetnLink()==nullptr) {
      return;
    }

    //split the list by two (left, right)
    SplitList(Head, &Left, &Right);

    //recursively sort left and right
    MergeSort(&Left);
    MergeSort(&Right);

    //merge list set sorted list
    *refHead=MergeList(Left, Right);

    return ;
  }

   // Split the list

  /**
  *	@brief	split the list
  * @detail using slow(one node move), fast(two node move), fast will be last and slow will be middle
  *	@pre	Head and left Right will be initialized.
  *	@param	reference of head node Left and Rigth to get the list splited.
  *	@return	none.
  */
  void SplitList(NodeType<T>* Head, NodeType<T>** Left, NodeType<T>** Right){
    NodeType<T>* slow = Head; // for one node move
    NodeType<T>* fast  = Head->GetnLink(); // for two node move
    while (fast!=nullptr) {
      fast=fast->GetnLink(); //fast move once
      if (fast!=nullptr) {
        slow=slow->GetnLink(); //slow move once
        fast=fast->GetnLink(); // faste one node move more
      }
    }

    // left is first to middle
    *Left=Head;
    *Right=slow->GetnLink(); //Right will be middle node to last node

    //initialize
    slow->SetnLink(nullptr);
  }


  /**
  *	@brief	merge the list
  * @detail compare left and right , using comparer set direction
  *	@pre	left Right will be initialized.
  *	@param	Left and Rigth to get the list merged.
  *	@return	newNode that be merged.
  */
  NodeType<T>* MergeList(NodeType<T>* Left,NodeType<T>* Right){
    //merging two sorted List
    NodeType<T>* newHead=nullptr;

    //Base case of Merge List Recursive
    if (Left==nullptr) { //if left node is null
      return Right; //return right
    }
    if (Right==nullptr) { //if right node is null
      return Left; //return left
    }

    //recursively merge
    if (this->sl_Comparer.Compare(Left->GetData(),Right->GetData())) {
      //ASCENDING left(first node)->GetData()< Rigth(first node) ->GetData()
      //DESCENDING left(first node)->GetData()> Rigth(first node) ->GetData()
      newHead=Left;
      newHead->SetnLink(MergeList(Left->GetnLink(), Right)); //call recursively compare and merge
    } else{
      newHead=Right;
      newHead->SetnLink(MergeList(Left, Right->GetnLink()));
    }
    return newHead;
  }
public:
  /**
  *	default constructor.
  */
  SLinkedList () :sl_CurPointer(nullptr),sl_PrePointer(nullptr), sl_Length(0),sl_Direction(ASCENDING),sl_Comparer(ASCENDING){}

  /**
  *	sl_Direction constructor.
  */
  SLinkedList(const int &Direction)
  :sl_CurPointer(nullptr),sl_PrePointer(nullptr), sl_Length(0),sl_Direction(Direction),sl_Comparer(Direction){}
  // ASCENDING(1): ascending order,  DESCENDING(0): descending order

  /**
  *	copy constructor. (deep copy)
  */
  SLinkedList(const SLinkedList& sl){
    this->sl_Head_Node.nlink=nullptr; //reset head node
    T Copy_Data;
    if (sl.sl_Length!=0) {
      sl.ResetList();
      while (sl.GetNextItem(Copy_Data)) {
        this->Add(Copy_Data);
      }
    }
    //if using add it will be same as sl.sl_Length
  }

  /**
  *	destructor.
  */
  ~SLinkedList (){
    if (!this->IsEmpty()) {
      this->MakeEmpty();
    }
  }

  /**
  *	@brief	Initialize list to empty state.
  *	@pre	None
  *	@post	List is empty.
  */
  void MakeEmpty(){
    NodeType<T>* Temp_Ptr;
    while (!this->IsEmpty()) {
      Temp_Ptr=this->GetHead(); //temp ptr point head pointer
      this->SetHead(this->GetHead()->GetnLink()); //set head pointer to next node
      delete Temp_Ptr;
    }
    this->sl_Length=0;
  }

  // Get Set , other property management

  /**
  *	@brief	Get Direction.
  *	@pre	none.
  *	@post	none.
  *	@return	Get Direction of list.
  */
  int GetDirection() const { return this->sl_Direction; }

  /**
  *	@brief	Set Direction.
  *	@pre	none.
  *	@post	Set Direction.
  *	@param Direction to set.
  */
  void SetDirection(int inDirection=ASCENDING) { this->sl_Direction=inDirection; this->sl_Comparer.SetDirection(inDirection); }

  /**
  *	@brief	Get Head pointer Head node has.
  *	@pre	none.
  *	@post	none.
  *	@return	Get Head pointer same as head node nLink.
  */
  NodeType<T>* GetHead() const { return this->sl_Head_Node.GetnLink(); }

  /**
  *	@brief	Set Head pointer Head node has.
  *	@pre	none.
  *	@post	Set Head pointer same as head node nLink.
  *	@param Head pointer to set.
  */
  void SetHead(NodeType<T>* inHead_Ptr) { this->sl_Head_Node.SetnLink(inHead_Ptr); }

  /**
	*	@brief	Get a number of Node in current list.
	*	@pre	none.
	*	@post	none.
	*	@return	number of Node in current list.
	*/
  int GetLength() const { return this->sl_Length; }

  /**
  *	@brief	Check list is empty.
  *	@pre	none.
  *	@post	none.
  *	@return	return true if list is empty, otherwise return false.
  */
  bool IsEmpty() const { return this->GetHead()==nullptr; }

  // iterator management

  /**
  *	@brief	Initialize current pointer for an iteration through the list. (make nullptr)
  *	@pre	None.
  *	@post	current pointer is prior to list. current pointer has been initialized.
  */
  void ResetList() { this->sl_CurPointer=nullptr; this->sl_PrePointer=nullptr; }

  /**
  *	@brief	move list iterator to the next item in list and get that item.
  *	@pre	list and list iterator should not be initialized.
  *	@post	iterator is moved to next item.
  *	@param	data	get current iterator's item. it does not need to be initialized.
  *	@return	return 1 if this function works well, otherwise 0.
  */
  int GetNextItem(T &data);

  /**
  *	@brief	move list iterator to the next
  *	@pre	iterator pointer should be intialized
  *	@post	iterator is moved to next item.
  * @return If new current pointer is out of bound, return NULL.
  *			Otherwise, return the pointer of the current item
  */
  T* GetNextItemPtr();

  // data management

  /**
  *	@brief	get the data which has same in the list.(Sequential Search)
  *	@pre	list should be initialized.
  *	@param	data that you want(search) to get.
  *	@return	return 1 if this function works well, otherwise 0.
  */
  int Get(T &data);

  /**
  *	@brief	get the data which has same id in the list.(Sequential Search)
  *	@pre	list should be initialized.
  *	@param	data that you want(search) to get.
  *	@return	return if this function works well, the pointer of data in the list  otherwise null.
  */
  T* GetPtr(T &data);

  /**
  *	@brief	Add item into appropriate spot of this list.
  *	@pre	List is not full. item is not in list.
  *	@post	Item is inserted in this list.
  *	@return	1 if this function works well, otherwise 0.
  */
  int Add(T data);

  /**
  *	@brief	Delete item from this list.
  *	@pre	List is not empty. the item exists in list.
  *	@post	Item is deleted from this list.
  *	@return	1 if this function works well, otherwise 0.
  */
  int Delete(T data);

  /**
  *	@brief	Sort item from this list.
  *	@pre	List is not empty. the item exists in list.
  *	@post	List is sorted.
  * @param Compare criteria.
  *	@return	1 if this function works well, otherwise 0.
  */
  void Sort();

  //operator overloading

  /**
  *	@brief	Doing Deep copy by copy assignment operator.
  *	@pre	List set info.
  *	@post	object copy data by deep.
  *	@param	List that you want to be copied.
  *	@return	return self-reference if self and List is not same object, otherwise self that unchanged.
  */
  SLinkedList<T>& operator= (SLinkedList<T>& SList);
};


// move list iterator to the next item in list and get that item.
template <typename T>
int SLinkedList<T>::GetNextItem(T &data){
  if (this->IsEmpty()) { // if list is empty
    return 0;
  }
  //if list is not empty
  if (this->sl_CurPointer==nullptr) { //if curpointer is initial value
    this->sl_CurPointer=this->GetHead(); // if curpointer is null, make curpointer head pointer.
    this->sl_PrePointer=&this->sl_Head_Node; // prepointer be Head node(meaningless)
  } else{
    if (this->sl_CurPointer->GetnLink()==nullptr) { // if curpointer is last, return 0;
      return 0;
    }
    this->sl_PrePointer=this->sl_CurPointer; // pre go to cur
    this->sl_CurPointer=this->sl_CurPointer->GetnLink(); //cur go to next pointer
  }
  data=this->sl_CurPointer->GetData();
  return 1;
}

// move list iterator to the next
template <typename T>
T* SLinkedList<T>::GetNextItemPtr(){
  if (this->IsEmpty()) { // if list is empty
    return nullptr;
  }
  //if list is not empty
  if (this->sl_CurPointer==nullptr) {//if curpointer is initial value
    this->sl_CurPointer=this->GetHead(); // if curpointer is null, make curpointer head pointer.
    this->sl_PrePointer=&this->sl_Head_Node; // prepointer be Head node(meaningless)
  } else{
    if (this->sl_CurPointer->GetnLink()==nullptr) { // if curpointer is last, return 0;
      return nullptr;
    }
    this->sl_PrePointer=this->sl_CurPointer; // pre go to cur
    this->sl_CurPointer=this->sl_CurPointer->GetnLink(); //cur go to next pointer
  }
  return this->sl_CurPointer->GetDataPtr();
}

// get the data which has same in the list.(Sequential Search)
template <typename T>
int SLinkedList<T>::Get(T &data){
  T Temp_Data;
  this->ResetList();
  while (this->GetNextItem(Temp_Data)) {
    if (data==Temp_Data) {
      data=Temp_Data; //if found copy data
      return 1;
    }
  }
  return 0; // if not found
}


// get the data which has same id in the list.(Sequential Search)
template <typename T>
T* SLinkedList<T>::GetPtr(T &data){
  T* Temp_DataPtr;
  this->ResetList();
  while ((Temp_DataPtr=this->GetNextItemPtr())) {
    if (data==*Temp_DataPtr) {
      //if found copy data
      return Temp_DataPtr;
    }
  }
  return nullptr; // if not found
}

// Add item into appropriate spot of this list.
template <typename T>
int SLinkedList<T>::Add(T data){
  T Temp_Data;
  NodeType<T>* NewNode;
  NewNode=new NodeType<T>;
  NewNode->SetData(data); //initialize new node
  if (this->sl_Length==0) { // if no node in list
    this->SetHead(NewNode);
    this->sl_Length++;
    return 1;
  }

  this->ResetList();
  while (this->GetNextItem(Temp_Data)) {
    //compare data and Node data
    if (this->sl_Comparer.Compare(data,Temp_Data)) { //compare list data and data to input
      if (this->sl_PrePointer==&this->sl_Head_Node) { // if pre node is head node, change head to NewNode
        this->SetHead(NewNode);
      } else{
        this->sl_PrePointer->SetnLink(NewNode); //pre node set n link to new node
      }
      NewNode->SetnLink(this->sl_CurPointer); // and new node point to cur node
      this->sl_Length++;
      return 1;
    }
  }
  //if data is biggest in the list
  this->sl_CurPointer->SetnLink(NewNode);
  this->sl_Length++;
  return 1;
}

// Delete item from this list.
template <typename T>
int SLinkedList<T>::Delete(T data){
  if (this->sl_Length==0) { //if list is empty no search
    return 0;
  }
  if (!this->Get(data)) { // if not found
    return 0;
  }
  // if found
  if (this->sl_PrePointer==&this->sl_Head_Node) { // if pre node is head node, change head to NewNode
    this->SetHead(this->sl_CurPointer->GetnLink());
  } else{
    this->sl_PrePointer->SetnLink(this->sl_CurPointer->GetnLink()); //pre point cur next
  }
  delete this->sl_CurPointer; //delete cur node
  this->sl_Length--;
  return 1;
}

// Sort item from this list.
template <typename T>
void SLinkedList<T>::Sort(){ //using merge sort
  NodeType<T>* Temp_HeadPointer; // for data protected
  Temp_HeadPointer=this->GetHead();
  this->MergeSort(&Temp_HeadPointer);
  this->SetHead(Temp_HeadPointer);
}


// Doing Deep copy by copy assignment operator.
template <typename T>
SLinkedList<T>& SLinkedList<T>::operator= (SLinkedList<T>& SList){
	if (this!=&SList) {
		this->MakeEmpty();
		this->SetHead(nullptr); //reset head node
    T Copy_Data;
		if (SList.sl_Length!=0) {
      SList.ResetList();
      while (SList.GetNextItem(Copy_Data)) {
        this->Add(Copy_Data);
      }
		}
		//if using add it will be same as sl.sl_Length
	}
	return *this;
}
#endif /* _SORTEDLINKEDLIST_HPP */
