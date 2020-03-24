#ifndef _DOUBLY_ITERATOR_H
#define _DOUBLY_ITERATOR_H

#include "DoublyLinkedList.h"

template <typename T>
struct DoublyNodeType;
template <typename T>
class DoublyLinkedList;


template <typename T>
class DoublyIterator
{
	//더블 링크드 리스트 클래스를 friend class로 설정
	friend class DoublyLinkedList<T>;
public:
	DoublyIterator(const DoublyLinkedList<T>& list)
		: m_List(list), m_pCurPointer(list.m_pFirst)
	{
	};
	~DoublyIterator()
	{};
	bool NotNull();	//현재 원소가 Null값인지 아닌지 검사
	bool NextNotNull(); //다음 원소가 Null값인지 아닌지 검사
	T First();	//첫번째 노드의 아이템을 리턴
	T Next();	//다음 노드의 아이템을 리턴
	DoublyNodeType<T>* GetCurrentNode();	//현재 node를 리턴

private:
	const DoublyLinkedList<T>& m_List;	//사용할 리스트의 주소값
	DoublyNodeType<T>* m_pCurPointer;	//curpointer
};


template <typename T>
bool DoublyIterator<T>::NotNull()
{
	if (m_pCurPointer == NULL)	//m_pCurPointer이 NULL이면 1, 아니면 0
		return 1;
	return 0;
}
template <typename T>
bool DoublyIterator<T>::NextNotNull()
{
	m_pCurPointer = m_pCurPointer->next;	//m_pCurPointer의 다음 노드가 NULL이면 1, 아니면 0
	if (m_pCurPointer == NULL)
		return 1;
	return 0;
}
template <typename T>
T DoublyIterator<T>::First()	//first를 가리키는 iterator
{
	m_pCurPointer = this->m_List.m_pFirst;
	return m_pCurPointer->data;	//첫번째 아이템값을 리턴
}
template <typename T>
T DoublyIterator<T>::Next()
{
	m_pCurPointer = m_pCurPointer->next;	//curpointer를 다음노드로 옮김
	return m_pCurPointer->data;
}
template <typename T>
DoublyNodeType<T>* DoublyIterator<T>::GetCurrentNode()
{
	return m_pCurPointer;	//현재 노드 리턴
}


#endif	// _DOUBLY_ITERATOR_H