#pragma once
#ifndef _QUEUE_H
#define _QUEUE_H
#include <iostream>

using namespace std;

/**
*	@brief	큐가 꽉찼을 때 예외 클래스.
*/
class FullQueue
{
public:
	/**
	*	@brief	큐가 꽉찼을 때 메세지 출력.
	*/
	void print()
	{
		cout << "FullQueue exception thrown." << endl;
	}
};

/**
*	@brief	큐가 비었을 때 예외 클래스.
*/
class EmptyQueue
{
public:
	/**
	*	@brief	큐가 비었을 때 메세지 출력.
	*/
	void print()
	{
		cout << "EmtpyQueue exception thrown." << endl;
	}
};

/**
*	@brief	큐 클래스.
*/
template <class T>
class Queue
{
private:
	int m_iFront;			//큐의 앞을 나타내는 플래그
	int m_iRear;			//큐의 뒤를 나타내는 플래그
	int m_nMaxQueue;
	T* m_pItems;		// 아이템타입 포인터 변수

public:
	/**
	*	@brief	Default MAXITEM 만큼의 사이즈를 가진 큐를 초기화한다.
	*	@pre	Default MAXITEM 가 정의되어야한다.
	*	@post	할당된 리스트를 가르킨다.
	*/
	Queue();

	/**
	*	@brief	Parameter로 전해진 MAX 만큼의 사이즈를 가진 큐를 초기화한다.
	*	@pre	Parameter로 전해진 MAX가 정의되어야한다.
	*	@post	할당된 리스트를 가르킨다.
	*	@param	큐의 사이즈
	*/
	Queue(int max);

	/**
	*	@brief	소멸자
	*/
	~Queue();

	/**
	*	@brief	큐가 꽉찼는지 확인.
	*	@pre	큐가 초기화.
	*	@post	없음.
	*	@return	큐가 꽉찼으면 1, 아닌 경우에 0을 출력.
	*/
	bool IsFull();

	/**
	*	@brief	큐가 비었는지 확인.
	*	@pre	큐가 초기화.
	*	@post	없음.
	*	@return	큐가 비었으면 1, 아닌 경우에 0을 출력.
	*/
	bool IsEmpty();

	/**
	*	@brief	큐안의 내용을 모두 삭제한다.
	*	@pre	큐가 존재해야한다.
	*	@post	큐가 비워진다.
	*/
	void MakeEmpty();

	/**
	*	@brief	큐에 새로운 자료를 추가한다.
	*	@pre	큐가 존재해야한다.
	*	@post	큐에 새로운 자료를 추가된다.
	*/
	void EnQueue(T newItem);

	/**
	*	@brief	큐의 제일 먼저 들어온 자료부터 삭제한다.
	*	@pre	큐가 존재해야한다.
	*	@post	큐의 데이터를 삭제한다.
	*/
	void DeQueue(T& item);

	/**
	*	@brief	큐에 모든 아이템을 출력한다
	*	@pre	큐가 존재해야한다.
	*	@post	없음.
	*/
	void Print();

	/**
	*	@brief	m_iFront을 출력한다
	*	@pre	큐가 존재해야한다.
	*	@post	없음.
	*	@return m_iFront
	*/
	int Front();

	/**
	*	@brief	m_iRear을 출력한다
	*	@pre	큐가 존재해야한다.
	*	@post	없음.
	*	@return m_iRear
	*/
	int Rear();

	/**
	*	@brief	m_nMaxQueue을 출력한다.
	*	@pre	큐가 존재해야한다.
	*	@post	없음.
	*	@return m_nMaxQueue
	*/
	int MAX();

	/**
	*	@brief	큐에 아이템이 존재하면 삭제한다.
	*	@pre	큐가 존재해야한다.
	*	@post	아이템이 삭제된다.
	*	@return 삭제에 성공하면 1을, 아닌경우에 0을 반환한다.
	*/
	int Deduplication(T inData);
};

// MAXITEM이 30인 원형 큐를 동적할당함
template <class T>
Queue<T>::Queue()
{
	m_nMaxQueue = MAXITEM + 1;		// 원형 큐의 최대 크기를 MAX_ITEM +1로 선언해서 한칸은 비게한다.
	m_iFront = m_nMaxQueue - 1;		// 원형 큐의 선두를 최대크기 -1 로 선언, 즉 30
	m_iRear = m_nMaxQueue - 1;			// 원형 큐의 후미를 최대크기 -1 로 선언, 즉 30
	m_pItems = new T[m_nMaxQueue];
}

// 큐의 사이즈를 받아온 만큼 할당해준다.
template <class T>
Queue<T>::Queue(int max)
{
	m_nMaxQueue = max + 1;			// 원형 큐의 최대 크기를 max로 선언해서 한칸은 비게한다.
	m_iFront = m_nMaxQueue - 1;			// 원형 큐의 선두를 최대크기 -1 로 선언
	m_iRear = m_nMaxQueue - 1;			// 원형 큐의 후미를 최대크기 -1 로 선언
	m_pItems = new T[m_nMaxQueue];
}

//소멸자
template <class T>
Queue<T>::~Queue()
{
	delete[] m_pItems;
}

//Queue가 가득 찼는지 확인
template <class T>
bool Queue<T>::IsFull()
{
	if ((m_iRear + 1) % m_nMaxQueue == m_iFront)  // 선두와 후미의 위치를 비교하여 큐가 꽉차있는지 확인. 후미가 선두를 교차하면 안됨.
		return true;
	else
		return false;
}

// Queue가 비었는지 확인
template <class T>
bool Queue<T>::IsEmpty()
{
	if (m_iFront == m_iRear) // 선두와 후미의 위치를 비교 둘이 같은 곳에 있다면 큐가 비어있음
		return true;
	else
		return false;
}

//큐를 비워준다.
template <class T>
void Queue<T>::MakeEmpty()
{
	m_iFront = m_iRear;				// 선두와 후미의 위치를 같게 하여 큐를 비움
}

// 새로운 아이템을 Queue에 가장 위에 넣음
template <class T>
void Queue<T>::EnQueue(T newItem)
{
	if (IsFull())
	{
		throw FullQueue();
	}
	else
	{
		m_iRear = (m_iRear + 1) % m_nMaxQueue;		// 큐가 꽉차지 않았다면 후미의 위치를 한단계 옮기고
		m_pItems[m_iRear] = newItem;				// 옮긴 위치에 새로운 아이템 배열을 추가
	}
}

// Queue에 가장 먼저 있는 아이템을 지우기
template <class T>
void Queue<T>::DeQueue(T & item)
{
	if (IsEmpty())
	{
		throw EmptyQueue();
	}
	else
	{
		m_iFront = (m_iFront + 1) % m_nMaxQueue;		// 큐가 비어있지 않다면 선두의 위치를 한단계 옮기고
		item = m_pItems[m_iFront];					// 옮긴 위치의 아이템 배열을 삭제
	}
}

// Print all the items in the queue on screen
template <class T>
void Queue<T>::Print()
{
	// Queue 내의 모든 element 출력.
	for (int i = (m_iFront + 1) % m_nMaxQueue; i != (m_iRear + 1) % m_nMaxQueue; i = (i + 1) % m_nMaxQueue) //큐의 처음+1에서 출발해서 큐의 마지막까지 확인한다. 모든 검색시 mod로 순환하게 한다.
	{
		cout << m_pItems[i] << " - ";
	}
	cout << endl;
}

template <class T>
int Queue<T>::Deduplication(T inData)
{
	// Queue 내의 모든 element 출력.
	for (int i = (m_iFront + 1) % m_nMaxQueue; i != (m_iRear + 1) % m_nMaxQueue; i = (i + 1) % m_nMaxQueue) //큐의 처음+1에서 출발해서 큐의 마지막까지 확인한다. 모든 검색시 mod로 순환하게 한다.
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
