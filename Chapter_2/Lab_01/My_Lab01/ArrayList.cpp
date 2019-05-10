#include "ArrayList.h"


// Make list empty.
void ArrayList::MakeEmpty()
{
	m_Length = 0;
}


// Get a number of records in current list.
int ArrayList::GetLength()
{
	return m_Length;
}


// Check capacity of list is full.
bool ArrayList::IsFull()
{
	if(m_Length > MAXSIZE - 1)
		return true;
	else
		return false;
}

//Check capacity of list is empty.
bool ArrayList::IsEmpty(){
	if (this->m_Length==0) {
		return true;
	} else {
		return false;
	}
}


// add a new data into list.
int ArrayList::Add(ItemType inData)
{
	if(!IsFull())
	{
		m_Array[m_Length] = inData;
		m_Length++;
	}
	else
		return 0;

	return 1;
}


// Initialize list iterator.
void ArrayList::ResetList()
{
	m_CurPointer = -1;
}


// move list iterator to the next item in list and get that item.
int ArrayList::GetNextItem(ItemType& data)
{
	m_CurPointer++;	// list pointer 증가
	if(m_CurPointer == MAXSIZE)	// end of list이면 -1을 리턴
		return -1;
	data = m_Array[m_CurPointer];	// 현재 list pointer의 레코드를 복사

	return m_CurPointer;
}

// using member function GetNextItem and get the data which has same id in the list.
int ArrayList::Get(ItemType& data){
	ItemType iter;
	this->ResetList(); // Initialize the list pointer
	for (int i = 0; i < this->m_Length; i++) {
		this->GetNextItem(iter);
		if (data.CompareByID(iter)==EQUAL) { // if data and iter has same id,
			data=iter; // deep copy data from iter
			return 1; // return the data index
		}
	}
	return 0;
}

// using member function Get and delete the data which you want to delete in the list.
int ArrayList::Delete(ItemType data){
  // get the data you want to delete from the list
	if (this->Get(data)==0) { // if there is no same id in the list, return 0;
		std::cout << "\t Student is not in Array" << '\n';
		return 0;
	} else{
		for (int i = this->m_CurPointer; i < this->m_Length-1; i++) {
			this->m_Array[i]=this->m_Array[i+1];
		} // if data is deleted, data which are backward position than deleted one move one index forward
		this->m_Length--;
		return 1;
	}
}

// using member function Get and update the data which you want to update in the list.
int ArrayList::Replace(ItemType data){
  // get the data you want to delete from the list
	if (this->Get(data)==0) { // if there is no same id in the list, return 0;
		std::cout << "\t Student is not in Array" << '\n';
		return 0;
	} else{
		data.SetRecordFromKB(); // set the new record on data
		this->m_Array[this->m_CurPointer]=data; // put updated data in same index
		return 1;
	}
}
