#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "ItemType.h"
#include "CHeapBase.h"
#include "CMaxHeap.h"
#include "CMinHeap.h"

#include <iostream>
#include <string>
using namespace std;

/**
*	��ǰ���� ������ ���� application Ŭ����.
*	@author	�躴��
*	@date	2014.11.20
*/
class Application
{
public:
	/**
	*	������.
	*/
	Application()
	{
		m_nCurCommand = 0;
	}

	/**
	*	�Ҹ���.
	*/
	~Application()
	{
	}
	
	/**
	*	@brief	���α׷� ����.
	*	@pre	���α׷� ����.
	*	@post	���α׷� ����.
	*/
	void Run();

	/**
	*	@brief	MaxHeap�� MinHeap �� �� �ϳ��� �����ϴ� �Լ�.
	*	@pre	none.
	*	@post	none.
	*/
	void WhatHeap();

	/**
	*	@brief	ȭ�鿡 �޴��� �߰� Ű����� �Է��ϴ� �Լ�.
	*	@pre	none.
	*	@post	none.
	*	@return	�޴��� ��ȯ�Ѵ�.
	*/
	int GetCommand();

	/**
	*	@brief	Heap�� �� ��ǰ������ �߰��ϱ� ���� �Լ�.
	*	@pre	Heap�� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	Heap�� �� ��ǰ������ �߰��Ѵ�.
	*	@return	�� �۵��ϸ� 1�� ��ȯ�ϰ� �ƴϸ� 0�� ��ȯ�Ѵ�.
	*/
	int AddItem();

	/**
	*	@brief	Heap���� ��ǰ������ �����ϱ� ���� �Լ�.
	*	@pre	Heap�� ��������� �ȵȴ�.
	*	@post	Heap���� ��ǰ������ �����Ѵ�.
	*	@return	�� �۵��ϸ� 1�� ��ȯ�ϰ� �ƴϸ� 0�� ��ȯ�Ѵ�.
	*/
	int DeleteItem();

	/**
	*	@brief	Heap���� ù��° ��ǰ������ �����ϱ� ���� �Լ�.
	*	@pre	Heap�� ��������� �ȵȴ�.
	*	@post	Heap���� ù��° ��ǰ������ �����Ѵ�.
	*	@return	�� �۵��ϸ� 1�� ��ȯ�ϰ� �ƴϸ� 0�� ��ȯ�Ѵ�.
	*/
	int DequeueItem();

	/**
	*	@brief	Heap�� �ִ� ��ǰ������ ����ϱ� ���� �Լ�.
	*	@pre	none.
	*	@post	Heap�� �ִ� ��ǰ������ ��µȴ�.
	*/
	void DisplayItem();

	/**
	*	@brief	Heap���� ��ǰ������ �˻��ϱ� ���� �Լ�.
	*	@pre	Heap�� ��������� �ȵȴ�.
	*	@post	Heap���� ��ǰ������ �˻��Ѵ�.
	*	@return	�� �۵��ϸ� 1�� ��ȯ�ϰ� �ƴϸ� 0�� ��ȯ�Ѵ�.
	*/
	int SearchItem();

private:
	CHeapBase<ItemType> *m_List;	///< Heap for ItemType.
	int m_nCurCommand;	///< ���� ������ �޴� ��ȣ
};

#endif	// _APPLICATION_H