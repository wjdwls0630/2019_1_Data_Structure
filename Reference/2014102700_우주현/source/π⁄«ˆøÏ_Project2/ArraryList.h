#pragma once
#ifndef _ARRAYLIST_H
#define _ARRAYLIST_H
#include <iostream>
using namespace std;

/**
*	@brief 두 개체 사이의 관계.
*/
enum RelationType { LESS, GREATER, EQUAL };

template<typename T>
class ArraryList
{
private:
	T* m_Array;					///< 리스트 어레이
	int m_Length;				///< number of elements in list.
	int m_CurPointer;			///< iterator pointer.
	int MAXSIZE;				///< 리스트 최대 사이즈
public:
	/**
	*	@brief 생성자.
	*/
	ArraryList();

	/**
	*	@brief 소멸자.
	*/
	~ArraryList();

	/**
	*	@brief	리스트 비우기.
	*	@pre	없음.
	*	@post	리스트가 비워진다.
	*/
	void MakeEmpty();

	/**
	*	@brief	현재 리스트의 데이터 수를 받아온다.
	*	@pre	없음.
	*	@post	없음.
	*	@return	리스트의 데이터 수.
	*/
	int GetLength();

	/**
	*	@brief	리스트가 비어있는지 확인.
	*	@pre	없음.
	*	@post	없음.
	*	@return	비어있으면 True, 아닌 경우에 False를 반환한다.
	*/
	bool IsEmpty();

	/**
	*	@brief	리스트가 가득 차있는지 확인.
	*	@pre	없음.
	*	@post	없음.
	*	@return	가득 차있으면 True, 아닌 경우에 False를 반환한다.
	*/
	bool IsFull();

	/**
	*	@brief	리스트에 새로운 데이터 추가.
	*	@pre	리스트가 선언되어야 한다.
	*	@post	리스트에 새로운 데이터가 추가된다.
	*	@param	data	새로운 데이터.
	*	@return	잘 작동하면 1을, 아닌 경우에 0을 반환한다.
	*/
	int Add(T data);
	//	int AddByBytes(T data);
	//	int AddByDates(T data);

		/**
		*	@brief	리스트 iterator를 리세함.
		*	@pre	리스트가 초기화 되어야함.
		*	@post	iterator가 리셋됨.
		*/
	void ResetList();

	/**
	*	@brief	list iterator를 다음 아이템으로 옮겨서 데이터를 가져옴
	*	@pre	list와 list iterator는 초기화 되어서는 안된다.
	*	@post	iterator가 다음 아이템으로 넘어감
	*	@param	현재 iterator가 가르키는 아이템을 파라미터로 받음, 초기화되어서는 안된다.
	*	@return	리스트에 끝에 도달하지 않았다면 인덱스 반환, 그렇지 않은 경우 -1 반환.
	*/
	int GetNextItem(T& data);

	/**
	*	@brief	item을 찾아서 해당 item을 반환한다.
	*	@pre	인수 data에 있는 id가 list 내에 존재하는 값이어야 한다.
	*	@post	list 내에서 찾은 item이 data에 입력된다.
	*	@param	data	찾고자 하는 id가 입력된 ItemType값. 발견한 item이 리턴된다.
	*	@return	성공(발견)시 1, 실패시 0을 리턴한다.
	*/
	int Get(T& data);

	/**
	*	@brief	id가 일치하는 item을 찾아서 해당 item을 제거한다.
	*	@pre	인수 data에 있는 id가 list 내에 존재하는 값이어야 한다.
	*	@post	list 내에 해당 item이 제거된다.
	*	@param	data	제거하고자 하는 id가 입력된 ItemType값.
	*	@return	성공시 1, 실패시 0을 리턴한다.
	*/
	int Delete(T data);

	/**
	*	@brief	id가 일치하는 list내 item을 찾아서 변경한다.
	*	@pre	인수 data에 있는 id가 list 내에 존재하는 값이어야 한다.
	*	@post	배열 내에 넘겨받은 item과 id가 일치하는 값이 넘겨받은 item의 내용으로 변경된다.
	*	@param	data	교체하고자 하는 id와 레코드를 가진 ItemType값.
	*	@return	성공시 1, 실패시 0을 리턴한다.
	*/
	int Replace(T data);

	/**
	*	@brief	이진탐색을 통해 id가 일치하는 list내 item을 찾아서 반환한다.
	*	@pre	없음.
	*	@post	배열 내에 넘겨받은 item과 id가 일치하는 값을 찾아서 data로 반환된다.
	*	@param	data	찾고자 하는 id가 입력된 ItemType값.
	*	@return	성공(발견)시 1, 실패시 0을 리턴한다.
	*/
	//	int GetBinarySearch(T& data);

		/**
		*	@brief	배열 가져오기
		*	@pre	없음.
		*	@post	없음.
		*	@return	m_Array.
		*/
	T* GetArray();

	T* GetPoint();
	/**
*	@brief	배열 출력
*	@pre	iterator가 reset됨
*	@post	iterator가 리스트의 마지막을 가르킴
*	@return	m_Array.
*/
	void DisplayArray();

	ArraryList<T>* operator=(const ArraryList<T>& list);
};

template<typename T>
ArraryList<T> ::ArraryList()
{
	MAXSIZE = 5; //배열의 최대 크기 5로 설정
	m_Length = 0; //아이템이 아무것도 들어가지 않은 상태
	m_Array = new T[MAXSIZE]; //동적할당
	ResetList();
}

template<typename T>
ArraryList<T>:: ~ArraryList()
{
	delete[] m_Array;
}

template<typename T>
void ArraryList<T>::MakeEmpty()
{
	delete[] m_Array;	//배열 뒤에걸 앞으로 하나씩 땡김
	MAXSIZE = 5; //새로 생성자 시작
	m_Array = new T[MAXSIZE];
	m_Length = 0;
	ResetList();
}

template<typename T>
int ArraryList<T>::GetLength()
{
	return m_Length; //아이템이 몇개 들어가있는지 반환
}

template<typename T>
bool ArraryList<T>::IsEmpty()
{
	if (m_Length == 0) //만약 리스트에 아이템이 하나도 없다면
		return true;
	else
		return false;
}

template<typename T>
bool ArraryList<T>::IsFull()
{
	if (m_Length > MAXSIZE - 1) //만약 리스트가 가득 찼다면
		return true;
	else
		return false;
}

template<typename T>
int ArraryList<T>::Add(T inData)
{
	if (!IsFull()) //만약 리스트가 차지 않은 상태라면
	{
		T CurItem; //현재 아이템을 보일 변수
		ResetList();	//iterator 초기화
		GetNextItem(CurItem); //첫아이템을 가져옴

		while (m_CurPointer <= m_Length) //m_CurPointer가 0에서 시작해서 아이템 개수 만큼 돌 동안
		{
			if (CurItem.CompareByName(inData) == GREATER || m_CurPointer == m_Length)	//만약 CurItem>inData일경우 혹은 배열의 마지막이라서 비교대상이 없는경우
			{
				for (int i = m_Length; i > m_CurPointer; i--)	//맨뒤에서 부터 하나씩 땡긴다.
					m_Array[i] = m_Array[i - 1];	//배열 밀기
				m_Array[m_CurPointer] = inData;	//배열 밀은 후 현재 포인터에 아이템 넣는다.
				m_Length++;	//개수 증가
				break;
			}
			GetNextItem(CurItem);	//다음아이템으로 넘어감
		}
	}
	else //만약 배열이 모두 채워진 상태라면 
	{
		T* copyArray = new T[MAXSIZE * 2]; //새로운 배열을 생성하는데, 이때 사이즈는 기존 사이즈의 2배가 됨.
		memcpy(copyArray, m_Array, MAXSIZE * sizeof(T));
		MAXSIZE = MAXSIZE * 2;
		m_Array = copyArray; //m_Array에 넣어주기
		if (Add(inData))
			return 1;
		return 0;
	}

	return 1;
}

template<typename T>
void ArraryList<T>::ResetList()
{
	m_CurPointer = -1;
}


template<typename T>
int ArraryList<T>::GetNextItem(T & data)
{
	m_CurPointer++;	// list pointer 증가
	if (m_CurPointer == MAXSIZE)	// end of list이면 -1을 리턴
		return -1;
	data = m_Array[m_CurPointer];	// 현재 list pointer의 레코드를 복사

	return m_CurPointer;
}


template<typename T>
int ArraryList<T>::Get(T & data)
{
	T CurItem;

	ResetList();	//iterator 초기화
	GetNextItem(CurItem);	//첫아이템 가져옴
	while (m_CurPointer < m_Length)	//처음부터 끝까지
	{
		switch (CurItem.CompareByName(data))	//입력 아이템과 현재 아이템을 비교
		{
		case EQUAL:	//일치하면
			data = CurItem;	//data에 현재 아이템을 반환
			return 1;	//성공(1)을 리턴
			break;
		case GREATER:	//현재 아이템의 id가 더 크면(정렬되있으므로 나머지에 찾는게 없다)
			return 0;	//실패(0)을 리턴
			break;
		default:	//현재 아이템의 id가 더 작으면
			GetNextItem(CurItem);	//다음 아이템을 가져온다.(계속 탐색)
			break;
		}
	}
	return 0; //실패시0
}

template<typename T>
int ArraryList<T>::Delete(T data)
{
	if (Get(data))	//id가 일치하는 item을 발견한다면(1)
	{
		for (int i = m_CurPointer; i < m_Length; i++)	//현재 포인터부터 입력된 배열 끝까지 반복
			m_Array[i] = m_Array[i + 1];	//배열 뒤에걸 앞으로 하나씩 땡김
		m_Length--;	//아이템 개수를 하나 줄임
		return 1;	//성공(1)을 리턴
	}
	return 0;	//id일치하는 item을 찾지 못한다면 실패(0)을 리턴
}

template<typename T>

int ArraryList<T>::Replace(T data)

{

	cout << "\n\t바꾸고자 하는 폴더의 이름을 입력하세요 : " << endl;

	data.SetNameFromKB();

	data.SetPath("/root");

	for (int i = 0; i < m_Length; i++)

	{

		if (data.CompareByName(m_Array[i]) == EQUAL)    //같은 데이터값이 있으면 지우고 위치를 당겨준다

		{

			cout << "\t - 새로운 폴더 설정 - " << endl;

			data.SetRecordFromKB();

			m_Array[i] = data;

			cout << "\t완료되었습니다!!" << endl;

			return 1;

		}

	}

	cout << "\t일치하는 이름의 파일/폴더를 찾을 수 없습니다!!" << endl;

	return 1;

}

template<typename T>
T* ArraryList<T>::GetArray()
{
	return m_Array;
}


template<typename T>
void ArraryList<T>::DisplayArray()
{
	T CurItem;

	ResetList();	//iterator 초기화
	GetNextItem(CurItem);	//첫아이템 가져옴
	while (m_CurPointer < m_Length)	//처음부터 끝까지
	{
		cout << m_Array[m_CurPointer] << endl;
		GetNextItem(CurItem);	//다음아이템으로
	}
}


template <typename T>
ArraryList<T>* ArraryList<T>::operator=(const ArraryList<T> & list) {
	T* copy;
	if (list.m_Array == NULL)
	{
		this->m_Array = NULL;
		this->m_Length = list.m_Length;
		this->m_CurPointer = list.m_CurPointer;
	}
	else
	{
		copy = new T;		// copy를 계속하여 동적할당
		T* temp;
		temp = list.m_Array;

		this->m_Array = copy;
		copy->m_fName = temp->m_fName;
		copy->m_fAddress = temp->m_fAddress;
		copy->m_fBytes = temp->m_fBytes;
		copy->m_fDate = temp->m_fDate;
		copy->m_fNumber = temp->m_fNumber;
		copy->m_fList = temp->m_fList;
		copy->prevFolder = temp->prevFolder;
		this->m_nLength = list.m_nLength;
		this->m_CurPointer = list.m_CurPointer;
	}
	return *this;
}

#endif	// _ARRAYLIST_H