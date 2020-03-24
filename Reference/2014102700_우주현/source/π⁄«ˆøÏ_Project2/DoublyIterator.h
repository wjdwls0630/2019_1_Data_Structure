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
	//���� ��ũ�� ����Ʈ Ŭ������ friend class�� ����
	friend class DoublyLinkedList<T>;
public:
	DoublyIterator(const DoublyLinkedList<T>& list)
		: m_List(list), m_pCurPointer(list.m_pFirst)
	{
	};
	~DoublyIterator()
	{};
	bool NotNull();	//���� ���Ұ� Null������ �ƴ��� �˻�
	bool NextNotNull(); //���� ���Ұ� Null������ �ƴ��� �˻�
	T First();	//ù��° ����� �������� ����
	T Next();	//���� ����� �������� ����
	DoublyNodeType<T>* GetCurrentNode();	//���� node�� ����

private:
	const DoublyLinkedList<T>& m_List;	//����� ����Ʈ�� �ּҰ�
	DoublyNodeType<T>* m_pCurPointer;	//curpointer
};


template <typename T>
bool DoublyIterator<T>::NotNull()
{
	if (m_pCurPointer == NULL)	//m_pCurPointer�� NULL�̸� 1, �ƴϸ� 0
		return 1;
	return 0;
}
template <typename T>
bool DoublyIterator<T>::NextNotNull()
{
	m_pCurPointer = m_pCurPointer->next;	//m_pCurPointer�� ���� ��尡 NULL�̸� 1, �ƴϸ� 0
	if (m_pCurPointer == NULL)
		return 1;
	return 0;
}
template <typename T>
T DoublyIterator<T>::First()	//first�� ����Ű�� iterator
{
	m_pCurPointer = this->m_List.m_pFirst;
	return m_pCurPointer->data;	//ù��° �����۰��� ����
}
template <typename T>
T DoublyIterator<T>::Next()
{
	m_pCurPointer = m_pCurPointer->next;	//curpointer�� �������� �ű�
	return m_pCurPointer->data;
}
template <typename T>
DoublyNodeType<T>* DoublyIterator<T>::GetCurrentNode()
{
	return m_pCurPointer;	//���� ��� ����
}


#endif	// _DOUBLY_ITERATOR_H