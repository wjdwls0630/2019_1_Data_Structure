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
*	제품정보 관리를 위한 application 클래스.
*	@author	김병우
*	@date	2014.11.20
*/
class Application
{
public:
	/**
	*	생성자.
	*/
	Application()
	{
		m_nCurCommand = 0;
	}

	/**
	*	소멸자.
	*/
	~Application()
	{
	}
	
	/**
	*	@brief	프로그램 구동.
	*	@pre	프로그램 시작.
	*	@post	프로그램 종료.
	*/
	void Run();

	/**
	*	@brief	MaxHeap와 MinHeap 둘 중 하나를 선택하는 함수.
	*	@pre	none.
	*	@post	none.
	*/
	void WhatHeap();

	/**
	*	@brief	화면에 메뉴가 뜨고 키보드로 입력하는 함수.
	*	@pre	none.
	*	@post	none.
	*	@return	메뉴를 반환한다.
	*/
	int GetCommand();

	/**
	*	@brief	Heap에 새 제품정보를 추가하기 위한 함수.
	*	@pre	Heap가 초기화되어야한다.
	*	@post	Heap에 새 제품정보를 추가한다.
	*	@return	잘 작동하면 1을 반환하고 아니면 0을 반환한다.
	*/
	int AddItem();

	/**
	*	@brief	Heap에서 제품정보를 삭제하기 위한 함수.
	*	@pre	Heap가 비어있으면 안된다.
	*	@post	Heap에서 제품정보를 삭제한다.
	*	@return	잘 작동하면 1을 반환하고 아니면 0을 반환한다.
	*/
	int DeleteItem();

	/**
	*	@brief	Heap에서 첫번째 제품정보를 삭제하기 위한 함수.
	*	@pre	Heap가 비어있으면 안된다.
	*	@post	Heap에서 첫번째 제품정보를 삭제한다.
	*	@return	잘 작동하면 1을 반환하고 아니면 0을 반환한다.
	*/
	int DequeueItem();

	/**
	*	@brief	Heap에 있는 제품정보를 출력하기 위한 함수.
	*	@pre	none.
	*	@post	Heap에 있는 제품정보가 출력된다.
	*/
	void DisplayItem();

	/**
	*	@brief	Heap에서 제품정보를 검색하기 위한 함수.
	*	@pre	Heap가 비어있으면 안된다.
	*	@post	Heap에서 제품정보를 검색한다.
	*	@return	잘 작동하면 1을 반환하고 아니면 0을 반환한다.
	*/
	int SearchItem();

private:
	CHeapBase<ItemType> *m_List;	///< Heap for ItemType.
	int m_nCurCommand;	///< 현재 선택한 메뉴 번호
};

#endif	// _APPLICATION_H