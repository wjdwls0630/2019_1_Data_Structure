#ifndef _DOUBLY_ITERATOR_H
#define _DOUBLY_ITERATOR_H

#include "LinkedList.h"

/**
*	template ���� ���� ����
*/
template <typename T>
class DoublySortedLinkedList;

/**
*	template ���� ���� ����
*/
template <typename T>
struct DoublyNodeType;

/**
*	Iterator class for DoublySortedLinkedList.  (not using header and trailer nodes).
*	���õ� ADT�� ���� ����
*	- ��ü return�ϴ� �޼��忡�� ����� null�� ��� return�� ���� ���� �߻�
*	- ��ü ���ٴ� �����Ͱ� (nullptr�� ����) �� �������� �б⹮ ������ ���� ���� �� ����.
*/
template <typename T>
class DoublyIterator {
	friend class DoublySortedLinkedList<T>;
public:
	/**
	*	Initialize m_List and m_pCurPointer. (constructor overloading)
	*/
	DoublyIterator(const DoublySortedLinkedList<T>& list) : m_List(list), m_pCurPointer(list.m_pFirst) {}

	/**
	*	@brief	���� ��带 ����Ű�� �����Ͱ� null���� �ƴ��� �Ǵ��ϴ� �޼���.
	*	@pre	Iterator has been initialized.
	*	@post	None.
	*	@return	nullptr true, otherwise false.
	*/
	bool NotNull();	

	/**
	*	@brief	���� ��� �������� ���� ��尡 null���� �ƴ��� �Ǵ��ϴ� �޼���.
	*	@pre	Iterator has been initialized.
	*	@post	None.
	*	@return	nullptr true, otherwise false.
	*/
	bool NextNotNull();

	/**
	*	@brief	Get first data of the list.
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved to the first node.
	*	@return	Return first data of the list.
	*/
	T First();

	/**
	*	@brief	Get next data of the current pointer.
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved to the next node.
	*	@return	Return next data of the list.
	*/
	T Next();

	/**
	*	@brief	Get current data of the list and go to the next node. ���� ���. ��ü��ȯ�� return by value
	*	@pre	Iterator has been initialized.
	*	@post	Current pointer is moved to next node.
	*	@return	Return current data of the list.
	*/
	DoublyNodeType<T> GetCurrentNode();




private:
	const DoublySortedLinkedList<T>& m_List;	///< ����� ����Ʈ�� ���� ����
	DoublyNodeType<T>* m_pCurPointer;	///< Node pointer for pointing current node to use iteration.
};


// ���� ���Ұ� null���� �˻�
template <typename T>
bool DoublyIterator<T>::NotNull() {
	if (m_pCurPointer == nullptr) {
		return false;
	}
	else return true;
}

// ���� ���Ұ� null���� �˻�
template <typename T>
bool DoublyIterator<T>::NextNotNull() {
	if (m_pCurPointer->next == nullptr) {
	
		return false;
	}
	else return true;
}

// ù ��° node
template <typename T>
T DoublyIterator<T>::First() {
	if (m_List.IsEmpty()) {
		m_pCurPointer = m_List.m_pFirst;
		return m_pCurPointer->data;
	}
}

// ���� node�� �̵� �� item�� return.
template <typename T>
T DoublyIterator<T>::Next() {
	T output = m_pCurPointer->data; 
	if (NotNull()) {
		m_pCurPointer = m_pCurPointer->next;
	}
	return output;
}

// ���� node�� return
template <typename T>
DoublyNodeType<T> DoublyIterator<T>::GetCurrentNode() {
	if (m_pCurPointer!=nullptr) {
		return *m_pCurPointer;
	}
}




#endif // !_DOUBLY_ITERATOR_H
