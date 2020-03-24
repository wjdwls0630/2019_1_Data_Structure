#pragma once
#ifndef _DOUBLYSORTEDLINKEDLIST_H
#define _DOUBLYSORTEDLINKEDLIST_H

#include "ItemType.h"
#include "DoublyIterator.h"

#define min ItemType(INT_MIN)
#define max ItemType(INT_MAX)

template<typename T>
class DoublyIterator;

/**
*	연결리스트에서 쓰이는 NodeType의 구조체
*/
template <typename T>
struct DoublyNodeType
{
	T data; ///< 각 노드의 데이터.
	DoublyNodeType *prev; ///< 노드의 앞을 가리키는 포인터.
	DoublyNodeType *next; ///< 노드의 다음를 가리키는 포인터.
};

/**
*	정렬된 더블연결리스트 클래스
*/
template <typename T>
class DoublySortedLinkedList
{
	friend class DoublyIterator<T>; ///< DoublyIterator와 친구 클래스.
public:
	/**
	*	디폴트 생성자.
	*/
	DoublySortedLinkedList();

	/**
	*	소멸자.
	*/
	~DoublySortedLinkedList();

	/**
	*	@brief	리스트가 비었는지 아닌지 검사한다.
	*	@pre	m_nLength가 값을 가지고 있어야 한다.
	*	@post	비었는지 아닌지를 알려준다.
	*	@return	비어있으면 true, 아니면 false를 반환.
	*/
	bool IsEmpty();

	/**
	*	@brief	리스트가 가득 찼는지 아닌지 검사한다.
	*	@pre	m_nLength가 값을 가지고 있어야 한다.
	*	@post	가득 찼는지 아닌지를 알려준다.
	*	@return	가득 차있으면 true, 아니면 false를 반환.
	*/
	bool IsFull();

	/**
	*	@brief	리스트를 비운다.
	*	@pre	없음.
	*	@post	m_pFirst와 m_pLast를 제외한 모든 데이터를 지운다.
	*/
	void MakeEmpty();

	/**
	*	@brief	리스트의 길이를 반환한다.
	*	@pre	없음.
	*	@post	리스트의 길이를 반환.
	*	@return	m_nLength 리스트의 길이 반환.
	*/
	int GetLength() const;

	/**
	*	@brief	새로운 아이템을 리스트에 추가한다.
	*	@pre	item을 입력받는다.
	*	@post	아이템을 리스트에 추가한다.
	*	@return	같은 아이템이 있으면 0을 반환하고, 입력에 성공하면 1을 반환.
	*/
	int Add(T item);

	/**
	*	@brief	입력받은 아이템을 리스트에서 삭제한다.
	*	@pre	item을 입력받는다.
	*	@post	입력받은 아이템을 리스트에서 찾아 삭제한다.
	*/
	void Delete(T item);

	/**
	*	@brief	입력받은 아이템으로 정보를 바꾼다.
	*	@pre	item을 입력받는다.
	*	@post	새로운 정보로 교체된다.
	*/
	void Replace(T item);

	/**
	*	@brief	입력받은 아이템의 정보와 비교하여 같은 리스트의 아이템을 가져온다.
	*	@pre	item을 입력받는다.
	*	@post	검색된 데이터를 아이템에 넣는다.
	*	@return	일치하는 데이터를 찾으면 1, 그렇지 않으면 0을 반환.
	*/
	int Get(T &item);

private:
	DoublyNodeType<T>* m_pFirst; ///< 최소값을 가지는 리스트의 맨 처음.
	DoublyNodeType<T>* m_pLast; ///< 최댓값을 가지는 리스트의 맨 끝.
	int m_nLength; ///< 리스트의 길이.
};

// 리스트의 맨 처음과 끝이 서로를 가리키게 설정하고 리스트의 길이를 0으로 초기화시켜놓는다.
template <typename T>
DoublySortedLinkedList<T> :: DoublySortedLinkedList()
{
	m_pFirst = new DoublyNodeType<T>;
	m_pLast = new DoublyNodeType<T>;

	m_pFirst->data = min; // 최솟값.
	m_pFirst->next = m_pLast; // 끝과 처음이 서로를 가리키게 초기화.
	m_pFirst->prev = NULL; // 처음.

	m_pLast->data = max; //  최댓값.
	m_pLast->next = NULL; // 끝.
	m_pLast->prev = m_pFirst; // 끝과 처음이 서로를 가리키게 초기화.

	m_nLength = 0; // 길이는 0.
}

// 소멸자.
template <typename T>
DoublySortedLinkedList<T>::~DoublySortedLinkedList()
{
	delete m_pFirst;
	delete m_pLast;
}

// 리스트가 비었는지 검사한다.
template <typename T>
bool DoublySortedLinkedList<T>::IsEmpty()
{
	if(m_nLength == 0)
		return true;
	else
		return false;
}

// 리스트가 꽉 차있는지 검사한다.
template <typename T>
bool DoublySortedLinkedList<T>::IsFull()
{
	if(m_nLength == 10)
		return true;
	else
		return false;
}

// 리스트를 비운다.
template <typename T>
void DoublySortedLinkedList<T>::MakeEmpty()
{
	DoublyNodeType<T> *pItem;
	DoublyIterator<T> itor(*this);
	itor.Next(); // 다음으로 이동.

	while(itor.NextNotNull())
	{
		pItem = itor.m_pCurPointer;
		itor.Next(); // 현재 포인터를 다음으로 이동.
		delete pItem; 
	}

	m_pFirst->next = m_pLast;
	m_pFirst->prev = NULL;
	m_pLast->prev = m_pFirst;
	m_pLast->next = NULL;

	return;
}

// 리스트의 길이를 반환한다.
template <typename T>
int DoublySortedLinkedList<T>::GetLength() const
{
	return m_nLength;
}

// 아이템을 입력받아 리스트의 맞는 자리를 찾아 삽입한다.
template <typename T>
int DoublySortedLinkedList<T>::Add(T item)
{
	DoublyIterator<T> itor(*this);
	itor.Next(); // 다음으로 이동.

	if(IsEmpty()) // 처음 삽입할 때
	{
		DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
		pItem->data = item;
		m_pFirst->next = pItem;
		pItem->prev = m_pFirst;
		pItem->next = m_pLast;
		m_pLast->prev = pItem; // 처음과 끝 사이에 삽입.
		m_nLength++;
		return 1;
	}
	else // 처음이 아닐 때
	{
		while(1)
		{
			if(item < itor.m_pCurPointer->data) // 맞는 자리를 찾는다.
			{
				DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
				pItem->data = item;
				pItem->prev = itor.m_pCurPointer->prev;
				pItem->next = itor.m_pCurPointer;
				itor.m_pCurPointer->prev->next = pItem;
				itor.m_pCurPointer->prev = pItem; // 아이템을 삽입.
				m_nLength++;
				return 1;
			}
			else if(item == itor.m_pCurPointer->data) // 같은 정보의 아이템이 있으면
				return 0; // 0을 반환.
			else
				itor.Next(); // 다음으로 이동.
		}
	}
}

// 입력받은 아이템을 데이터에서 찾아내어 삭제한다.
template <typename T>
void DoublySortedLinkedList<T>::Delete(T item)
{
	DoublyIterator<T> itor(*this);
	itor.Next(); // 다음으로 이동.

	while(itor.m_pCurPointer != m_pLast)
	{
		if(itor.m_pCurPointer->data == item) // 일치하는 데이터를 찾는다.
		{
			DoublyNodeType<T> *pItem = new DoublyNodeType<T>;
			pItem = itor.m_pCurPointer;
			itor.Next();
			pItem->prev->next = itor.m_pCurPointer;
			itor.m_pCurPointer->prev = pItem->prev; // 삭제하는 노드의 앞과 뒤를 서로 이어준다.
			delete pItem; // 삭제.
			return;
		}
		else
			itor.Next();
	}
	m_nLength--; // 길이 감소.
	return;
}

// 입력받은 아이템의 정보를 교체한다.
template <typename T>
void DoublySortedLinkedList<T>::Replace(T item)
{
	DoublyIterator<T> itor(*this);
	itor.Next(); // 다음으로 이동.
	 
	while(itor.m_pCurPointer != m_pLast)
	{
		if(itor.m_pCurPointer->data == item)
		{
			itor.m_pCurPointer->data = item; // 정보를 교체.
			return;
		}
		else
			itor.Next();
	}

	return;
}

// 입력받은 아이템과 일치하는 아이템을 리스트에서 찾아 가져온다.
template <typename T>
int DoublySortedLinkedList<T>::Get(T &item)
{
	DoublyIterator<T> itor(*this);
	itor.Next();

	while(itor.m_pCurPointer != m_pLast)
	{
		if(itor.m_pCurPointer->data == item)
		{
			item = itor.m_pCurPointer->data;
			return 1; // 일치하면 1을 반환.
		}
		else
			itor.Next(); // 다음으로 이동.
	}

	return 0; // 일치하지 않으면 0을 반환.
}

#endif _DOUBLYSORTEDLINKEDLIST_H