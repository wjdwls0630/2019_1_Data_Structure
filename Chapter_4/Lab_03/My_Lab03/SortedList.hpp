#ifndef _SORTEDLIST_HPP
#define _SORTEDLIST_HPP

#include <iostream>
#include <fstream>
#include <string>

#define MAXLISTSIZE 5


/**
*	@brief	SortedList class.
*	@details	This class processes as sorted by criteria
*/
template <typename T>
class SortedList{
public:
	/**
	*	default constructor.
	*/
	SortedList(int size=MAXLISTSIZE):m_Length(0), m_CurPointer(-1), maxSize(size){
		this->m_Array=new T [this->maxSize];
	}

	/**
	*	copy constructor. (deep copy)
	*/
	SortedList(const SortedList& sl)
	:m_Length(sl.m_Length), m_CurPointer(sl.m_CurPointer), maxSize(sl.maxSize){
		this->m_Array=new T [sl.maxSize];
		if (sl.m_Length!=0) {
			for (int i = 0; i < sl.m_Length; i++) {
				*(this->m_Array+i)=*(sl.m_Array+i);
			}
		}
	}


	/**
	*	destructor.
	*/
	~SortedList()	{ if(this->m_Length!=0) delete [] this->m_Array; }

	/**
	*	@brief	Make list empty.
	*	@pre	none.
	*	@post	clear list.
	*/
	void MakeEmpty();

	/**
	*	@brief	Get a number of records in current list.
	*	@pre	none.
	*	@post	none.
	*	@return	number of records in current list.
	*/
	int GetLength() const;

	/**
	*	@brief	Check capacity of list is full.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if list capacity reached to the upper bound, otherwise return false.
	*/
	bool IsFull() const;

	/**
	*	@brief	Check capacity of list is empty.
	*	@pre	none.
	*	@post	none.
	*	@return	return true if list capacity reached to the lower bound, otherwise return false.
	*/
	bool IsEmpty() const;

	/**
	*	@brief	Initialize list iterator.
	*	@pre	list should be initialized.
	*	@post	iterator is reset.
	*/
	void ResetList();

	/**
	*	@brief	move list iterator to the next item in list and get that item.
	*	@pre	list and list iterator should not be initialized.
	*	@post	iterator is moved to next item.
	*	@param	data	get current iterator's item. it does not need to be initialized.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int GetNextItem(T &data);
	/**
	*	@brief	move current pointer to the next
	*	@pre	iterator pointer should be intialized
	*	@post	iterator is moved to next item.
	*  @return If new current pointer is out of bound, return NULL.
	*			Otherwise, return the pointer of the current item
	*/
	T* GetNextItemPtr();

	/**
	*	@brief	get the data which has same id in the list.(Sequential Search)
	*	@pre	list should be initialized.
	*	@param	data that you want(search) to get.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int Get(T &data);

	/**
	*	@brief	get the data which has same id in the list.(Binary Search)
	*	@pre	the primary key of data is defined
	*	@param	data that you want(search) to get.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int GetBinarySearch(T &data);

	/**
	*	@brief	get the the pointer of the data which has same id in the list.(Sequential Search)
	*	@pre	list should be initialized.
	*	@param	temp data that you compare
	*	@return	if this function works well return the the pointer of the data, otherwise NULL.
	*/
	T* GetPtr(T &data);

	/**
	*	@brief	get the the pointer of the data which has same id in the list.(Binary Search)
	*	@pre	the primary key of data is defined
	*	@param	temp data that you compare
	*	@return	if this function works well return the the pointer of the data, otherwise NULL.
	*/
	T* GetPtrBinarySearch(T &data);

	/**
	*	@brief	Rellocate dynamic Array, Increase Capactiy by 10.
	*	@pre	none.
	*	@post	length is increase by 10, List Size is also increased.
	*/
	void ReAlloc();

	/**
	*	@brief	add a new data into Sortedlist.
	*	@pre	none.
	*	@post	added the new data(not overlap) into the Sortedlist.
	*	@param	data	new data.
	*	@return return 1 if this function works well, otherwise 0.
	*/
	int Add(T data);

	/**
	*	@brief  delete the data which you want to delete in the list.
	*	@pre	list should be initialized.
	*	@post	deleted the record in the list
	*	@param	data that you want(search) to delete.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int Delete(T data);

	/**
	*	@brief	update the data which you want to update in the list.
	*	@pre	list should be initialized. data is already set to update
	*	@post	updated the record for new in the list.
	*	@param	data that you want(search) to update.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int Replace(T &data);

	/**
	*	@brief	Doing Deep copy by copy assignment operator.
	*	@pre	List already set info.
	*	@post	object copy data by deep.
	*	@param	List that you want to be copied.
	*	@return	return self-reference if self and List is not same object, otherwise self that unchanged.
	*/
	SortedList<T>& operator= (const SortedList& SList);

private:
	T *m_Array;  ///< list array.
	int m_Length;				///< number of elements in list.
	int m_CurPointer; ///< iterator pointer.
	int maxSize;		///< maxCapacity of array.
};

// Make list empty.
template <typename T>
void SortedList<T>::MakeEmpty(){
	this->m_Length = 0;
}


// Get a number of records in current list.
template <typename T>
int SortedList<T>::GetLength() const{
	return this->m_Length;
}


// Check capacity of list is full.
template <typename T>
bool SortedList<T>::IsFull() const{
	if(this->m_Length > this->maxSize - 1)
		return true;
	else
		return false;
}

//Check capacity of list is empty.
template <typename T>
bool SortedList<T>::IsEmpty() const{
	if (this->m_Length==0) {
		return true;
	} else {
		return false;
	}
}


// Initialize list iterator.
template <typename T>
void SortedList<T>::ResetList(){
	this->m_CurPointer = -1;
}


// move list iterator to the next item in list and get that item.
template <typename T>
int SortedList<T>::GetNextItem(T& data){
	this->m_CurPointer++;	// list pointer 증가
	if(this->m_CurPointer == this->maxSize)	// end of list이면 -1을 리턴
		return 0;
	data = this->m_Array[this->m_CurPointer];	// 현재 list pointer의 레코드를 복사
	return 1;
}

// move current pointer to the next.
template <typename T>
T* SortedList<T>::GetNextItemPtr() {
  this->m_CurPointer++;	// list pointer
  if (this->m_CurPointer == this->m_Length)	// return NULL when reach the end of list
    return NULL;
  return &m_Array[m_CurPointer];	// return pointer of the current record
}

// get the data which has same id in the list.(Sequential Search)
template <typename T>
int SortedList<T>::Get(T& data){
	T Temp_Data;
	this->ResetList(); // Initialize the list pointer
	for (int i = 0; i < this->m_Length; i++) {
		this->GetNextItem(Temp_Data);
		if (data==Temp_Data) { // if data and iter has same id,
			data=Temp_Data; // deep copy data from iter
			return 1; // return 1;
		}
	}
	return 0;
}

// get the data which has same id in the list.(Binary Search)
template <typename T>
int SortedList<T>::GetBinarySearch(T &data){
	int left=0;
	int right=this->m_Length-1;
	int mid;
	while (left<=right) {
		mid=left+(right-left)/2;
		if (this->m_Array[mid]==data) {
			data=this->m_Array[mid];
			return 1;
		}else if(this->m_Array[mid]<data){
			left=mid+1;
		} else if(this->m_Array[mid]>data){
			right =mid-1;
		}
	}
	return 0;
}


// get the the pointer of the data which has same id in the list.(Sequential Search)
template <typename T>
T* SortedList<T>::GetPtr(T& data){
	T* Temp_Data;
	this->ResetList(); // Initialize the list pointer
	for (int i = 0; i < this->m_Length; i++) {
		Temp_Data=this->GetNextItemPtr();
		if (data==*Temp_Data) { // if data and iter has same id,
			return Temp_Data; // return the the pointer of the data
		}
	}
	return NULL;
}

// get the the pointer of the data which has same id in the list.(Binary Search)
template <typename T>
T* SortedList<T>::GetPtrBinarySearch(T &data){
	int left=0;
	int right=this->m_Length-1;
	int mid;
	while (left<=right) {
		mid=left+(right-left)/2;
		if (this->m_Array[mid]==data) {
			return &this->m_Array[mid];
		}else if(this->m_Array[mid]<data){
			left=mid+1;
		} else if(this->m_Array[mid]>data){
			right =mid-1;
		}
	}
	return NULL;
}

//Rellocate dynamic Array, Increase Capactiy by 10.
template <typename T>
void SortedList<T>::ReAlloc(){
	//declare new dynamic array to copy
	T* n_Array= new T[this->maxSize+10];

	for (int i = 0; i < this->maxSize; i++) {
		*(n_Array+i)=*(this->m_Array+i);
	}
	//delete old Array
	delete [] this->m_Array;

	//set new Array, size up
	this->m_Array=n_Array;
	this->maxSize+=10;

}


// add a new data into list.
template <typename T>
int SortedList<T>::Add(T data){
	if (this->IsFull()) {
		return 0;
	}
	this->ResetList();

	T Temp_Data;
	for (int i = 0; i < this->m_Length; i++) {
		this->GetNextItem(Temp_Data);
		//Compare data and m_Array item
		if (data<Temp_Data) {
			//move items by one index to backward
			for (int j = this->m_Length-1; j >= i; j--) {
				this->m_Array[j+1]=this->m_Array[j];
			}
			*(this->m_Array+i)=data;
			this->m_Length++;
			return 1;
		}
	}
	//if data is biggest in the list
	this->m_Array[this->m_Length]=data;
	this->m_Length++;
	return 1;
}

// delete the data which you want to delete in the list.
template <typename T>
int SortedList<T>::Delete(T data){
	// check list is empty
	if (this->IsEmpty()) {
		return 0;
	}
	// get the data you want to delete from the list
	if (this->Get(data)==0) { // if there is no same id in the list, return 0;
		return 0;
	}

	for (int i = this->m_CurPointer; i < this->m_Length-1; i++) {
		this->m_Array[i]=this->m_Array[i+1];
	} // if data is deleted, data which are backward position than deleted one move one index forward
	this->m_Length--;
	return 1;
}

// update the data which you want to update in the list.
template <typename T>
int SortedList<T>::Replace(T &data){
	// get the data you want to delete from the list
	T* temp;
	if (!(temp=this->GetPtr(data))) { // if there is no same id in the list, return 0;
		return 0;
	}
	temp=data; // put updated data in same reference
	return 1;
}

// Doing Deep copy by copy assignment operator.
template <typename T>
SortedList<T>& SortedList<T>::operator= (const SortedList& SList){
	if (this!=&SList) {
		delete [] this->m_Array;
		this->m_Array=new T[SList.maxSize];
		if (SList.m_Length!=0) {
			for (int i = 0; i < SList.m_Length; i++) {
				*(this->m_Array+i)=*(SList.m_Array+i);
			}
		}
		this->m_Length=SList.m_Length;
		this->m_CurPointer=SList.m_CurPointer;
		this->maxSize=SList.maxSize;
	}
	return *this;
}



#endif	/* _SORTEDLIST_HPP */
