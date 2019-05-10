#ifndef _SORTEDLINKEDLIST_HPP
#define _SORTEDLINKEDLIST_HPP

/**
*	@brief	NodeType Structure.
*	@details	This Structure has data and next pointer.
*/
template <typename T>
class NodeType {
public:
  T data;	///< A data for each node.
  NodeType* next;	///< A node pointer to point succeed node.
};

/**
*	@brief	SortedLinkedList class.
*	@details	This class processes as connected by NodeType next pointer, only can access by sequential
*/
template <typename T>
class SLinkedList {
private:
  NodeType<T>* m_pList;	///< Pointer for pointing a first node.
  NodeType<T>* m_pCurPointer;	///< Node pointer for pointing current node to use iteration.
  NodeType<T>* m_pPrePointer;	///< Node pointer for pointing pre node to use iteration.
  int m_nLength;	///< Number of node in the list.

public:
  /**
  *	default constructor.
  */
  SLinkedList () :m_pList(nullptr), m_pCurPointer(nullptr),m_pPrePointer(nullptr), m_nLength(0){}

  /**
  *	copy constructor. (deep copy)
  */
  SLinkedList(const SLinkedList& sl){
    this->m_pList=nullptr;
    T Copy_Data;
    if (sl.m_nLength!=0) {
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
    this->MakeEmpty();
  }

  /**
  *	@brief	Initialize list to empty state.
  *	@pre	None
  *	@post	List is empty.
  */
  void MakeEmpty(){
    NodeType<T>* Temp_Ptr;
    while (this->m_pList!=nullptr) {
      Temp_Ptr=this->m_pList;
      this->m_pList=this->m_pList->next;
      delete Temp_Ptr;
    }
    this->m_nLength=0;
  }

  /**
	*	@brief	Get a number of Node in current list.
	*	@pre	none.
	*	@post	none.
	*	@return	number of Node in current list.
	*/
  int GetLength() const { return this->m_nLength; }

  /**
  *	@brief	Initialize current pointer for an iteration through the list. (make nullptr)
  *	@pre	None.
  *	@post	current pointer is prior to list. current pointer has been initialized.
  */
  void ResetList() { this->m_pCurPointer=nullptr; this->m_pPrePointer=nullptr; }

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
  *	@brief	Doing Deep copy by copy assignment operator.
  *	@pre	List set info.
  *	@post	object copy data by deep.
  *	@param	List that you want to be copied.
  *	@return	return self-reference if self and List is not same object, otherwise self that unchanged.
  */
  SLinkedList<T>& operator= (SLinkedList<T>& SList);
};

template <typename T>
int SLinkedList<T>::GetNextItem(T &data){
  if (this->m_pList==nullptr) { // if list is empty
    return 0;
  }
  //if list is not empty
  if (this->m_pCurPointer==nullptr) {
    this->m_pCurPointer=this->m_pList; // if curpointer is null, point list head.
  } else{
    if (this->m_pCurPointer->next==nullptr) { // if curpointer is last, return 0;
      return 0;
    }
    this->m_pPrePointer=this->m_pCurPointer;
    this->m_pCurPointer=this->m_pCurPointer->next;
  }
  data=this->m_pCurPointer->data;
  return 1;
}

template <typename T>
T* SLinkedList<T>::GetNextItemPtr(){
  if (this->m_pList==nullptr) { // if list is empty
    return nullptr;
  }
  if (this->m_pCurPointer==nullptr) {
    this->m_pCurPointer=this->m_pList; // if curpointer is null, point list head.
  } else{
    if (this->m_pCurPointer->next==nullptr) { // if curpointer is last, return 0;
      return nullptr;
    }
    this->m_pPrePointer=this->m_pCurPointer;
    this->m_pCurPointer=this->m_pCurPointer->next;
  }
  return &this->m_pCurPointer->data;
}


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


template <typename T>
int SLinkedList<T>::Add(T data){
  T Temp_Data;
  NodeType<T>* NewNode;
  NewNode=new NodeType<T>;
  NewNode->data=data; //initialize new node
  NewNode->next=nullptr;
  if (this->m_nLength==0) { // if no node in list
    this->m_pList=NewNode;
    this->m_nLength++;
    return 1;
  }

  this->ResetList();
  while (this->GetNextItem(Temp_Data)) {
    //compare data and Node data
    if (data<Temp_Data) {
      if (this->m_pPrePointer==nullptr) { // if pre node don't exist, change head to NewNode
        this->m_pList=NewNode;
      } else{
        this->m_pPrePointer->next=NewNode;
      }
      NewNode->next=this->m_pCurPointer;
      this->m_nLength++;
      return 1;
    }
  }
  //if data is biggest in the list
  this->m_pCurPointer->next=NewNode;
  this->m_nLength++;
  return 1;
}

template <typename T>
int SLinkedList<T>::Delete(T data){
  if (this->m_nLength==0) { //if list is empty no search
    return 0;
  }
  if (!this->Get(data)) { // if not found
    return 0;
  }
  // if found
  if (this->m_pPrePointer==nullptr) { // if pre node don't exist, change head to next node
    this->m_pList=this->m_pCurPointer->next;
  } else{
    this->m_pPrePointer->next=this->m_pCurPointer->next; //pre point cur next
  }
  delete this->m_pCurPointer; //delete cur node
  this->m_nLength--;
  return 1;
}

// Doing Deep copy by copy assignment operator.
template <typename T>
SLinkedList<T>& SLinkedList<T>::operator= (SLinkedList<T>& SList){
	if (this!=&SList) {
		this->MakeEmpty();
		this->m_pList=nullptr;
    T Copy_Data;
		if (SList.m_nLength!=0) {
      SList.ResetList();
      while (SList.GetNextItem(Copy_Data)) {
        this->Add(Copy_Data);
      }
		}
    //if using add it will be same as slist.sl_Length
	}
	return *this;
}
#endif /* _SORTEDLINKEDLIST_HPP */
