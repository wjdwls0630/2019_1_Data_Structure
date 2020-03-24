#pragma once
#ifndef _QUEUE_H
#define _QUEUE_H
#include <iostream>

using namespace std;

/**
*	@brief	ť�� ��á�� �� ���� Ŭ����.
*/
class FullQueue
{
public:
	/**
	*	@brief	ť�� ��á�� �� �޼��� ���.
	*/
	void print()
	{
		cout << "FullQueue exception thrown." << endl;
	}
};

/**
*	@brief	ť�� ����� �� ���� Ŭ����.
*/
class EmptyQueue
{
public:
	/**
	*	@brief	ť�� ����� �� �޼��� ���.
	*/
	void print()
	{
		cout << "EmtpyQueue exception thrown." << endl;
	}
};

/**
*	@brief	ť Ŭ����.
*/
template <class T>
class Queue
{
private:
	int m_iFront;			//ť�� ���� ��Ÿ���� �÷���
	int m_iRear;			//ť�� �ڸ� ��Ÿ���� �÷���
	int m_nMaxQueue;
	T* m_pItems;		// ������Ÿ�� ������ ����

public:
	/**
	*	@brief	Default MAXITEM ��ŭ�� ����� ���� ť�� �ʱ�ȭ�Ѵ�.
	*	@pre	Default MAXITEM �� ���ǵǾ���Ѵ�.
	*	@post	�Ҵ�� ����Ʈ�� ����Ų��.
	*/
	Queue();

	/**
	*	@brief	Parameter�� ������ MAX ��ŭ�� ����� ���� ť�� �ʱ�ȭ�Ѵ�.
	*	@pre	Parameter�� ������ MAX�� ���ǵǾ���Ѵ�.
	*	@post	�Ҵ�� ����Ʈ�� ����Ų��.
	*	@param	ť�� ������
	*/
	Queue(int max);

	/**
	*	@brief	�Ҹ���
	*/
	~Queue();

	/**
	*	@brief	ť�� ��á���� Ȯ��.
	*	@pre	ť�� �ʱ�ȭ.
	*	@post	����.
	*	@return	ť�� ��á���� 1, �ƴ� ��쿡 0�� ���.
	*/
	bool IsFull();

	/**
	*	@brief	ť�� ������� Ȯ��.
	*	@pre	ť�� �ʱ�ȭ.
	*	@post	����.
	*	@return	ť�� ������� 1, �ƴ� ��쿡 0�� ���.
	*/
	bool IsEmpty();

	/**
	*	@brief	ť���� ������ ��� �����Ѵ�.
	*	@pre	ť�� �����ؾ��Ѵ�.
	*	@post	ť�� �������.
	*/
	void MakeEmpty();

	/**
	*	@brief	ť�� ���ο� �ڷḦ �߰��Ѵ�.
	*	@pre	ť�� �����ؾ��Ѵ�.
	*	@post	ť�� ���ο� �ڷḦ �߰��ȴ�.
	*/
	void EnQueue(T newItem);

	/**
	*	@brief	ť�� ���� ���� ���� �ڷ���� �����Ѵ�.
	*	@pre	ť�� �����ؾ��Ѵ�.
	*	@post	ť�� �����͸� �����Ѵ�.
	*/
	void DeQueue(T& item);

	/**
	*	@brief	ť�� ��� �������� ����Ѵ�
	*	@pre	ť�� �����ؾ��Ѵ�.
	*	@post	����.
	*/
	void Print();

	/**
	*	@brief	m_iFront�� ����Ѵ�
	*	@pre	ť�� �����ؾ��Ѵ�.
	*	@post	����.
	*	@return m_iFront
	*/
	int Front();

	/**
	*	@brief	m_iRear�� ����Ѵ�
	*	@pre	ť�� �����ؾ��Ѵ�.
	*	@post	����.
	*	@return m_iRear
	*/
	int Rear();

	/**
	*	@brief	m_nMaxQueue�� ����Ѵ�.
	*	@pre	ť�� �����ؾ��Ѵ�.
	*	@post	����.
	*	@return m_nMaxQueue
	*/
	int MAX();

	/**
	*	@brief	ť�� �������� �����ϸ� �����Ѵ�.
	*	@pre	ť�� �����ؾ��Ѵ�.
	*	@post	�������� �����ȴ�.
	*	@return ������ �����ϸ� 1��, �ƴѰ�쿡 0�� ��ȯ�Ѵ�.
	*/
	int Deduplication(T inData);
};

// MAXITEM�� 30�� ���� ť�� �����Ҵ���
template <class T>
Queue<T>::Queue()
{
	m_nMaxQueue = MAXITEM + 1;		// ���� ť�� �ִ� ũ�⸦ MAX_ITEM +1�� �����ؼ� ��ĭ�� ����Ѵ�.
	m_iFront = m_nMaxQueue - 1;		// ���� ť�� ���θ� �ִ�ũ�� -1 �� ����, �� 30
	m_iRear = m_nMaxQueue - 1;			// ���� ť�� �Ĺ̸� �ִ�ũ�� -1 �� ����, �� 30
	m_pItems = new T[m_nMaxQueue];
}

// ť�� ����� �޾ƿ� ��ŭ �Ҵ����ش�.
template <class T>
Queue<T>::Queue(int max)
{
	m_nMaxQueue = max + 1;			// ���� ť�� �ִ� ũ�⸦ max�� �����ؼ� ��ĭ�� ����Ѵ�.
	m_iFront = m_nMaxQueue - 1;			// ���� ť�� ���θ� �ִ�ũ�� -1 �� ����
	m_iRear = m_nMaxQueue - 1;			// ���� ť�� �Ĺ̸� �ִ�ũ�� -1 �� ����
	m_pItems = new T[m_nMaxQueue];
}

//�Ҹ���
template <class T>
Queue<T>::~Queue()
{
	delete[] m_pItems;
}

//Queue�� ���� á���� Ȯ��
template <class T>
bool Queue<T>::IsFull()
{
	if ((m_iRear + 1) % m_nMaxQueue == m_iFront)  // ���ο� �Ĺ��� ��ġ�� ���Ͽ� ť�� �����ִ��� Ȯ��. �Ĺ̰� ���θ� �����ϸ� �ȵ�.
		return true;
	else
		return false;
}

// Queue�� ������� Ȯ��
template <class T>
bool Queue<T>::IsEmpty()
{
	if (m_iFront == m_iRear) // ���ο� �Ĺ��� ��ġ�� �� ���� ���� ���� �ִٸ� ť�� �������
		return true;
	else
		return false;
}

//ť�� ����ش�.
template <class T>
void Queue<T>::MakeEmpty()
{
	m_iFront = m_iRear;				// ���ο� �Ĺ��� ��ġ�� ���� �Ͽ� ť�� ���
}

// ���ο� �������� Queue�� ���� ���� ����
template <class T>
void Queue<T>::EnQueue(T newItem)
{
	if (IsFull())
	{
		throw FullQueue();
	}
	else
	{
		m_iRear = (m_iRear + 1) % m_nMaxQueue;		// ť�� ������ �ʾҴٸ� �Ĺ��� ��ġ�� �Ѵܰ� �ű��
		m_pItems[m_iRear] = newItem;				// �ű� ��ġ�� ���ο� ������ �迭�� �߰�
	}
}

// Queue�� ���� ���� �ִ� �������� �����
template <class T>
void Queue<T>::DeQueue(T & item)
{
	if (IsEmpty())
	{
		throw EmptyQueue();
	}
	else
	{
		m_iFront = (m_iFront + 1) % m_nMaxQueue;		// ť�� ������� �ʴٸ� ������ ��ġ�� �Ѵܰ� �ű��
		item = m_pItems[m_iFront];					// �ű� ��ġ�� ������ �迭�� ����
	}
}

// Print all the items in the queue on screen
template <class T>
void Queue<T>::Print()
{
	// Queue ���� ��� element ���.
	for (int i = (m_iFront + 1) % m_nMaxQueue; i != (m_iRear + 1) % m_nMaxQueue; i = (i + 1) % m_nMaxQueue) //ť�� ó��+1���� ����ؼ� ť�� ���������� Ȯ���Ѵ�. ��� �˻��� mod�� ��ȯ�ϰ� �Ѵ�.
	{
		cout << m_pItems[i] << " - ";
	}
	cout << endl;
}

template <class T>
int Queue<T>::Deduplication(T inData)
{
	// Queue ���� ��� element ���.
	for (int i = (m_iFront + 1) % m_nMaxQueue; i != (m_iRear + 1) % m_nMaxQueue; i = (i + 1) % m_nMaxQueue) //ť�� ó��+1���� ����ؼ� ť�� ���������� Ȯ���Ѵ�. ��� �˻��� mod�� ��ȯ�ϰ� �Ѵ�.
	{
		if (inData == m_pItems[i])
		{
			for (; i != (m_iRear + 1) % m_nMaxQueue; i = (i + 1) % m_nMaxQueue)
			{
				m_pItems[i] = m_pItems[i + 1];
			}
			if (m_iRear == 0)
				m_iRear = m_nMaxQueue - 1;
			else
				m_iRear = m_iRear - 1;
			return 1;
		}
	}
	return 0;
}


template <class T>
int Queue<T>::Front()
{
	return m_iFront;
}


template <class T>
int Queue<T>::Rear()
{
	return m_iRear;
}


template <class T>
int Queue<T>::MAX()
{
	return m_nMaxQueue;
}
#endif // !_QUEUE_H
