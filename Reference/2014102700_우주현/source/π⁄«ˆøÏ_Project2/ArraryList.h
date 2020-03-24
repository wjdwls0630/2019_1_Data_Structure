#pragma once
#ifndef _ARRAYLIST_H
#define _ARRAYLIST_H
#include <iostream>
using namespace std;

/**
*	@brief �� ��ü ������ ����.
*/
enum RelationType { LESS, GREATER, EQUAL };

template<typename T>
class ArraryList
{
private:
	T* m_Array;					///< ����Ʈ ���
	int m_Length;				///< number of elements in list.
	int m_CurPointer;			///< iterator pointer.
	int MAXSIZE;				///< ����Ʈ �ִ� ������
public:
	/**
	*	@brief ������.
	*/
	ArraryList();

	/**
	*	@brief �Ҹ���.
	*/
	~ArraryList();

	/**
	*	@brief	����Ʈ ����.
	*	@pre	����.
	*	@post	����Ʈ�� �������.
	*/
	void MakeEmpty();

	/**
	*	@brief	���� ����Ʈ�� ������ ���� �޾ƿ´�.
	*	@pre	����.
	*	@post	����.
	*	@return	����Ʈ�� ������ ��.
	*/
	int GetLength();

	/**
	*	@brief	����Ʈ�� ����ִ��� Ȯ��.
	*	@pre	����.
	*	@post	����.
	*	@return	��������� True, �ƴ� ��쿡 False�� ��ȯ�Ѵ�.
	*/
	bool IsEmpty();

	/**
	*	@brief	����Ʈ�� ���� ���ִ��� Ȯ��.
	*	@pre	����.
	*	@post	����.
	*	@return	���� �������� True, �ƴ� ��쿡 False�� ��ȯ�Ѵ�.
	*/
	bool IsFull();

	/**
	*	@brief	����Ʈ�� ���ο� ������ �߰�.
	*	@pre	����Ʈ�� ����Ǿ�� �Ѵ�.
	*	@post	����Ʈ�� ���ο� �����Ͱ� �߰��ȴ�.
	*	@param	data	���ο� ������.
	*	@return	�� �۵��ϸ� 1��, �ƴ� ��쿡 0�� ��ȯ�Ѵ�.
	*/
	int Add(T data);
	//	int AddByBytes(T data);
	//	int AddByDates(T data);

		/**
		*	@brief	����Ʈ iterator�� ������.
		*	@pre	����Ʈ�� �ʱ�ȭ �Ǿ����.
		*	@post	iterator�� ���µ�.
		*/
	void ResetList();

	/**
	*	@brief	list iterator�� ���� ���������� �Űܼ� �����͸� ������
	*	@pre	list�� list iterator�� �ʱ�ȭ �Ǿ�� �ȵȴ�.
	*	@post	iterator�� ���� ���������� �Ѿ
	*	@param	���� iterator�� ����Ű�� �������� �Ķ���ͷ� ����, �ʱ�ȭ�Ǿ�� �ȵȴ�.
	*	@return	����Ʈ�� ���� �������� �ʾҴٸ� �ε��� ��ȯ, �׷��� ���� ��� -1 ��ȯ.
	*/
	int GetNextItem(T& data);

	/**
	*	@brief	item�� ã�Ƽ� �ش� item�� ��ȯ�Ѵ�.
	*	@pre	�μ� data�� �ִ� id�� list ���� �����ϴ� ���̾�� �Ѵ�.
	*	@post	list ������ ã�� item�� data�� �Էµȴ�.
	*	@param	data	ã���� �ϴ� id�� �Էµ� ItemType��. �߰��� item�� ���ϵȴ�.
	*	@return	����(�߰�)�� 1, ���н� 0�� �����Ѵ�.
	*/
	int Get(T& data);

	/**
	*	@brief	id�� ��ġ�ϴ� item�� ã�Ƽ� �ش� item�� �����Ѵ�.
	*	@pre	�μ� data�� �ִ� id�� list ���� �����ϴ� ���̾�� �Ѵ�.
	*	@post	list ���� �ش� item�� ���ŵȴ�.
	*	@param	data	�����ϰ��� �ϴ� id�� �Էµ� ItemType��.
	*	@return	������ 1, ���н� 0�� �����Ѵ�.
	*/
	int Delete(T data);

	/**
	*	@brief	id�� ��ġ�ϴ� list�� item�� ã�Ƽ� �����Ѵ�.
	*	@pre	�μ� data�� �ִ� id�� list ���� �����ϴ� ���̾�� �Ѵ�.
	*	@post	�迭 ���� �Ѱܹ��� item�� id�� ��ġ�ϴ� ���� �Ѱܹ��� item�� �������� ����ȴ�.
	*	@param	data	��ü�ϰ��� �ϴ� id�� ���ڵ带 ���� ItemType��.
	*	@return	������ 1, ���н� 0�� �����Ѵ�.
	*/
	int Replace(T data);

	/**
	*	@brief	����Ž���� ���� id�� ��ġ�ϴ� list�� item�� ã�Ƽ� ��ȯ�Ѵ�.
	*	@pre	����.
	*	@post	�迭 ���� �Ѱܹ��� item�� id�� ��ġ�ϴ� ���� ã�Ƽ� data�� ��ȯ�ȴ�.
	*	@param	data	ã���� �ϴ� id�� �Էµ� ItemType��.
	*	@return	����(�߰�)�� 1, ���н� 0�� �����Ѵ�.
	*/
	//	int GetBinarySearch(T& data);

		/**
		*	@brief	�迭 ��������
		*	@pre	����.
		*	@post	����.
		*	@return	m_Array.
		*/
	T* GetArray();

	T* GetPoint();
	/**
*	@brief	�迭 ���
*	@pre	iterator�� reset��
*	@post	iterator�� ����Ʈ�� �������� ����Ŵ
*	@return	m_Array.
*/
	void DisplayArray();

	ArraryList<T>* operator=(const ArraryList<T>& list);
};

template<typename T>
ArraryList<T> ::ArraryList()
{
	MAXSIZE = 5; //�迭�� �ִ� ũ�� 5�� ����
	m_Length = 0; //�������� �ƹ��͵� ���� ���� ����
	m_Array = new T[MAXSIZE]; //�����Ҵ�
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
	delete[] m_Array;	//�迭 �ڿ��� ������ �ϳ��� ����
	MAXSIZE = 5; //���� ������ ����
	m_Array = new T[MAXSIZE];
	m_Length = 0;
	ResetList();
}

template<typename T>
int ArraryList<T>::GetLength()
{
	return m_Length; //�������� � ���ִ��� ��ȯ
}

template<typename T>
bool ArraryList<T>::IsEmpty()
{
	if (m_Length == 0) //���� ����Ʈ�� �������� �ϳ��� ���ٸ�
		return true;
	else
		return false;
}

template<typename T>
bool ArraryList<T>::IsFull()
{
	if (m_Length > MAXSIZE - 1) //���� ����Ʈ�� ���� á�ٸ�
		return true;
	else
		return false;
}

template<typename T>
int ArraryList<T>::Add(T inData)
{
	if (!IsFull()) //���� ����Ʈ�� ���� ���� ���¶��
	{
		T CurItem; //���� �������� ���� ����
		ResetList();	//iterator �ʱ�ȭ
		GetNextItem(CurItem); //ù�������� ������

		while (m_CurPointer <= m_Length) //m_CurPointer�� 0���� �����ؼ� ������ ���� ��ŭ �� ����
		{
			if (CurItem.CompareByName(inData) == GREATER || m_CurPointer == m_Length)	//���� CurItem>inData�ϰ�� Ȥ�� �迭�� �������̶� �񱳴���� ���°��
			{
				for (int i = m_Length; i > m_CurPointer; i--)	//�ǵڿ��� ���� �ϳ��� �����.
					m_Array[i] = m_Array[i - 1];	//�迭 �б�
				m_Array[m_CurPointer] = inData;	//�迭 ���� �� ���� �����Ϳ� ������ �ִ´�.
				m_Length++;	//���� ����
				break;
			}
			GetNextItem(CurItem);	//�������������� �Ѿ
		}
	}
	else //���� �迭�� ��� ä���� ���¶�� 
	{
		T* copyArray = new T[MAXSIZE * 2]; //���ο� �迭�� �����ϴµ�, �̶� ������� ���� �������� 2�谡 ��.
		memcpy(copyArray, m_Array, MAXSIZE * sizeof(T));
		MAXSIZE = MAXSIZE * 2;
		m_Array = copyArray; //m_Array�� �־��ֱ�
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
	m_CurPointer++;	// list pointer ����
	if (m_CurPointer == MAXSIZE)	// end of list�̸� -1�� ����
		return -1;
	data = m_Array[m_CurPointer];	// ���� list pointer�� ���ڵ带 ����

	return m_CurPointer;
}


template<typename T>
int ArraryList<T>::Get(T & data)
{
	T CurItem;

	ResetList();	//iterator �ʱ�ȭ
	GetNextItem(CurItem);	//ù������ ������
	while (m_CurPointer < m_Length)	//ó������ ������
	{
		switch (CurItem.CompareByName(data))	//�Է� �����۰� ���� �������� ��
		{
		case EQUAL:	//��ġ�ϸ�
			data = CurItem;	//data�� ���� �������� ��ȯ
			return 1;	//����(1)�� ����
			break;
		case GREATER:	//���� �������� id�� �� ũ��(���ĵ������Ƿ� �������� ã�°� ����)
			return 0;	//����(0)�� ����
			break;
		default:	//���� �������� id�� �� ������
			GetNextItem(CurItem);	//���� �������� �����´�.(��� Ž��)
			break;
		}
	}
	return 0; //���н�0
}

template<typename T>
int ArraryList<T>::Delete(T data)
{
	if (Get(data))	//id�� ��ġ�ϴ� item�� �߰��Ѵٸ�(1)
	{
		for (int i = m_CurPointer; i < m_Length; i++)	//���� �����ͺ��� �Էµ� �迭 ������ �ݺ�
			m_Array[i] = m_Array[i + 1];	//�迭 �ڿ��� ������ �ϳ��� ����
		m_Length--;	//������ ������ �ϳ� ����
		return 1;	//����(1)�� ����
	}
	return 0;	//id��ġ�ϴ� item�� ã�� ���Ѵٸ� ����(0)�� ����
}

template<typename T>

int ArraryList<T>::Replace(T data)

{

	cout << "\n\t�ٲٰ��� �ϴ� ������ �̸��� �Է��ϼ��� : " << endl;

	data.SetNameFromKB();

	data.SetPath("/root");

	for (int i = 0; i < m_Length; i++)

	{

		if (data.CompareByName(m_Array[i]) == EQUAL)    //���� �����Ͱ��� ������ ����� ��ġ�� ����ش�

		{

			cout << "\t - ���ο� ���� ���� - " << endl;

			data.SetRecordFromKB();

			m_Array[i] = data;

			cout << "\t�Ϸ�Ǿ����ϴ�!!" << endl;

			return 1;

		}

	}

	cout << "\t��ġ�ϴ� �̸��� ����/������ ã�� �� �����ϴ�!!" << endl;

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

	ResetList();	//iterator �ʱ�ȭ
	GetNextItem(CurItem);	//ù������ ������
	while (m_CurPointer < m_Length)	//ó������ ������
	{
		cout << m_Array[m_CurPointer] << endl;
		GetNextItem(CurItem);	//��������������
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
		copy = new T;		// copy�� ����Ͽ� �����Ҵ�
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