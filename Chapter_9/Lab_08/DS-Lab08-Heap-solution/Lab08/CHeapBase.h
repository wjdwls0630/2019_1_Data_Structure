#ifndef _HEAPBASE_H
#define _HEAPBASE_H

#include "ItemType.h"


/**
*	CHeapBase Ŭ����.
*	@author	�躴��
*	@date	2014.11.20
*/
template <typename T>
class CHeapBase
{
public :
	/**
	*	������.
	*/
	CHeapBase();

	/**
	*	�Ҹ���.
	*/
	virtual ~CHeapBase();

	/**
	*	@brief	Heap�� Empty���� �ƴ��� Ȯ���ϴ� �Լ�.
	*	@pre	none.
	*	@post	none.
	*	@return	Heap�� Empty�̸� true�� ��ȯ, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsEmpty();

	/**
	*	@brief	Heap�� Full���� �ƴ��� Ȯ���ϴ� �Լ�.
	*	@pre	none.
	*	@post	none.
	*	@return	Heap�� Full�̸� true�� ��ȯ, �ƴϸ� false�� ��ȯ�Ѵ�.
	*/
	bool IsFull();

	/**
	*	@brief	Heap�� ������ ���� ��ȯ�ϴ� �Լ�.
	*	@pre	none.
	*	@post	Heap�� ������ ������ ��ȯ�Ѵ�.
	*	@return	Heap�� ������ ��
	*/
	int GetLength() const;

	/**
	*	@brief	Heap�� �ʱ�ȭ �ϴ� �Լ�.
	*	@pre	none.
	*	@post	Heap�� �ʱ�ȭ�ȴ�.
	*/
	void MakeEmpty();

	/**
	*	@brief	Heap�� ���ο� �����͸� �߰��ϴ� �����Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� ���ο� �����͸� �߰��Ѵ�.
	*	@param	item	ItemType���� ���ο� ������.
	*	@return	�� �۵��ϸ� 1�� ��ȯ
	*/
	virtual int Add(T item);

	/**
	*	@brief	Heap�� �����͸� �����ϴ� �����Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� �����Ѵ�.
	*	@param	item	ItemType���� ���� �� ������.
	*	@return	�� �۵��ϸ� 1�� ��ȯ
	*/
	virtual int Delete(T item);

	/**
	*	@brief	Heap�� ù��° �����͸� �����ϴ� �����Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� ù��° �����͸� �����Ѵ�.
	*	@return	������ ������ ��ȯ
	*/
	virtual T Dequeue();

	/**
	*	@brief	Heap�� �����͸� �˻��ϴ� �����Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� �˻��Ѵ�.
	*	@param	item	ItemType���� �˻� �� ������.
	*	@param	found	ã�Ҵ��� ��ã�Ҵ��� �Ǵ�.
	*/
	virtual void RetrieveItem(T &item, bool &found);

	/**
	*	@brief	Heap�� �����͸� ����ϴ� �����Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� ����Ѵ�.
	*/
	virtual void PrintHeap();

	/**
	*	@brief	������ �Ʒ��� �������鼭 Heap ũ�⸦ ���Ͽ� �����ϴ� ���������Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� ���Ͽ� �����Ѵ�.
	*	@param	iparent	�������� ������.
	*	@param	ibottom	������ ������.
	*/
	virtual void ReheapDown(int iparent, int ibottom) = 0;

	/**
	*	@brief	�Ʒ����� ���� �ö󰡸鼭 Heap ũ�⸦ ���Ͽ� �����ϴ� ���������Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� ���Ͽ� �����Ѵ�.
	*	@param	iroot	ù��° ������.
	*	@param	ibottom	�ö󰡴� ������.
	*/
	virtual void ReheapUp(int iroot, int ibottom) = 0;

	/**
	*	@brief	Heap�� �����͸� �����ϴ� ���������Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� �����Ѵ�.
	*	@param	item	ItemType���� ���� �� ������.
	*	@param	found	������ �����͸� ã�Ҵ��� �ƴ��� Ȯ��.
	*	@param	ibottom	�˻� ���� �迭 ��ġ.
	*/
	virtual void Delete(T item, bool &found, int iparent) = 0;

	/**
	*	@brief	Heap�� �����͸� �˻��ϴ� ���������Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �����͸� �˻��Ѵ�.
	*	@param	item	ItemType���� �˻� �� ������.
	*	@param	found	�˻��� �����͸� ã�Ҵ��� �ƴ��� Ȯ��.
	*	@param	ibottom	�˻� ���� �迭 ��ġ.
	*/
	virtual void Retrieve(T &item, bool &found, int iparent) = 0;

	/**
	*	@brief	Heap�� �ΰ��� �����͸� �ٲٴ� �Լ�.
	*	@pre	�ΰ��� �����Ͱ� �����Ѵ�.
	*	@post	�� �������� ��ġ�� �ٲ��.
	*	@param	iparent	�ٲ� �� ������.
	*	@param	ibottom	�ٲ� �Ʒ� ������.
	*/
	void Swap(int iparent, int ibottom);

protected :
	T *m_pHeap;			// �迭
	int m_iLastNode;	// �迭�� ��
	int m_nMaxSize;		// �迭�� �ִ����
};


// ������
template <typename T>
CHeapBase<T>::CHeapBase()
{
	m_iLastNode = 0;
}


// �Ҹ���
template <typename T>
CHeapBase<T>::~CHeapBase()
{
	MakeEmpty();
}


// Heap�� Empty���� �ƴ��� Ȯ���ϴ� �Լ�.
template <typename T>
bool CHeapBase<T>::IsEmpty()
{
	if(m_iLastNode == 0)
		return 1;
	else 
		return 0;
}


template <typename T>
bool CHeapBase<T>::IsFull()
{
	if(m_iLastNode == m_nMaxSize)
		return 1;
	else 
		return 0;
}


// Heap�� Full���� �ƴ��� Ȯ���ϴ� �Լ�.
template <typename T>
int CHeapBase<T>::GetLength() const
{
	return m_iLastNode;
}


// Heap�� �ʱ�ȭ �ϴ� �Լ�.
template <typename T>
void CHeapBase<T>::MakeEmpty()
{
	delete [] m_pHeap;
}


// Heap�� ���ο� �����͸� �߰��ϴ� �����Լ�
template <typename T>
int CHeapBase<T>::Add(T item)
{
	m_pHeap[m_iLastNode] = item; // �� ������ �߰�

	ReheapUp(0, m_iLastNode); // ������ ����

	m_iLastNode++; // ������ �� ����

	return 1;
}


// Heap�� �����͸� �����ϴ� �����Լ�.
template <typename T>
int CHeapBase<T>::Delete(T item)
{
	bool found = false;

	Delete(item, found, 0); // ������ ����

	if(found)
		m_iLastNode--; // ������ �� ����
	else
		return 0;

	return 1;
}


// Heap�� ù��° �����͸� �����ϴ� �����Լ�.
template <typename T>
T CHeapBase<T>::Dequeue()
{
	T item = m_pHeap[0];

	Delete(item); // ù��° ������ ����

	return item;
}


// Heap�� �����͸� �˻��ϴ� �����Լ�.
template <typename T>
void CHeapBase<T>::RetrieveItem(T &item, bool &found)
{
	Retrieve(item, found, 0); // ������ �˻�
}


// Heap�� �����͸� ����ϴ� �����Լ�.
template <typename T>
void CHeapBase<T>::PrintHeap()
{
	T item;

	for(int i=0; i<m_iLastNode; i++)
	{
		item << m_pHeap[i];
	}
}


// Heap�� �ΰ��� �����͸� �ٲٴ� �Լ�.
template <typename T>
void CHeapBase<T>::Swap(int iparent, int ibottom)
{
	T temp = m_pHeap[iparent];
	m_pHeap[iparent] = m_pHeap[ibottom];
	 m_pHeap[ibottom] = temp;
}



#endif	// _HEAPBASE_H