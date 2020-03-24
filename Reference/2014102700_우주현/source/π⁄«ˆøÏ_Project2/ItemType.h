#pragma once
#ifndef _ITEMTYPE_H
#define _ITEMTYPE_H

#include <iostream>	
#include <string>
#include "DoublyLinkedList.h"

using namespace std;

class ItemType
{
protected:
	string m_itName;		// 폴더 이름.
	string m_itAddress;	// 폴더 위치.
	int m_itBytes;		// 폴더 크기.
	string m_itDate;		// 생성 날짜.

public:
	/**
	*	@brief	기본 생성자.
	*/
	ItemType()
	{
		m_itName = "";
		m_itAddress = "";
		m_itBytes = 0;
		m_itDate = GetCurrentTimes();
	}

	/**
	*	@brief 소멸자.
	*/
	~ItemType()
	{
	}

	/**
	*	@brief	파일 이름 가져오기.
	*	@pre	파일 이름이 존재해야한다.
	*	@post	없음.
	*	@return	파일 이름.
	*/
	virtual string GetName();
	/**
	*	@brief	파일 위치 가져오기.
	*	@pre	파일 위치가 존재해야한다.
	*	@post	없음.
	*	@return	파일 위치.
	*/
	virtual string GetAddress();

	/**
	*	@brief	폴더 크기 가져오기.
	*	@pre	폴더 크기가 존재해야한다.
	*	@post	없음.
	*	@return	폴더 크기.
	*/
	virtual int GetBytes();
	/**
	*	@brief	생성 날짜 가져오기.
	*	@pre	생성 날짜가 존재해야한다.
	*	@post	없음.
	*	@return	생성 날짜.
	*/
	virtual string GetDate();
	/**
	*	@brief	폴더 이름 지정.
	*	@pre	없음.
	*	@post	폴더 이름이 지정된다.
	*	@param	inName	폴더 이름.
	*/
	virtual void SetName(string inName);

	/**
	*	@brief	폴더 위치 지정.
	*	@pre	없음.
	*	@post	폴더 위치가 지정된다.
	*	@param	inAddress	폴더 위치.
	*/
	virtual void SetAddress(string inAddress);

	/**
	*	@brief	폴더 크기 지정.
	*	@pre	없음.
	*	@post	폴더 크기가 지정된다.
	*	@param	inBytes	폴더 크기.
	*/
	virtual void SetBytes(int inBytes);

	/**
	*	@brief	생성 날짜 지정.
	*	@pre	없음.
	*	@post	생성 날짜가 지정된다.
	*	@param	inDate	생성 날짜.
	*/
	virtual void SetDate(string inDate);

	/**
	*	@brief	폴더 정보 기록.
	*	@pre	없음.
	*	@post	폴더 정보가 지정된다.
	*	@param	inName	폴더 이름.
	*	@param	inAddress	폴더 위치.
	*	@param	inBytes	폴더 크기.
	*	@param	inDate	생성 날짜.
	*/
	virtual void SetRecord(string inName, string inAddress, int inBytes, string inDate);

	/**
	*	@brief	폴더 이름 출력.
	*	@pre	폴더 이름이 존재해야한다.
	*	@post	폴더 이름이 출력된다.
	*/
	virtual void DisplayNameOnScreen();

	/**
	*	@brief	폴더 위치 출력.
	*	@pre	폴더 위치가 존재해야한다.
	*	@post	폴더 위치가 출력된다.
	*/
	virtual void DisplayAddressOnScreen();

	/**
	*	@brief	폴더 크기 출력.
	*	@pre	폴더 크기가 존재해야한다.
	*	@post	폴더 크기가 출력된다.
	*/
	virtual void DisplayBytesOnScreen();

	/**
	*	@brief	생성 날짜 출력.
	*	@pre	생성 날짜가 존재해야한다.
	*	@post	생성 날짜가 출력된다.
	*/
	virtual void DisplayDateOnScreen();

	/**
	*	@brief	파일 정보 출력.
	*	@pre	파일 정보가 존재해야한다.
	*	@post	파일 정보가 출력된다.
	*/
	virtual void DisplayRecordOnScreen();


	/**
	*	@brief	키보드로부터 폴더 이름을 입력받는다.
	*	@pre	없음.
	*	@post	폴더 이름 set.
	*/
	virtual void SetNameFromKB();

	/**
	*	@brief	키보드로부터 폴더 위치를 입력받는다.
	*	@pre	없음.
	*	@post	폴더 위치 set.
	*/
	virtual void SetAddressFromKB();

	/**
	*	@brief	키보드로부터 폴더 크기를 입력받는다.
	*	@pre	없음.
	*	@post	폴더 크기 set.
	*/
	virtual void SetBytesFromKB();

	/**
	*	@brief	키보드로부터 생성 날짜를 입력받는다.
	*	@pre	없음.
	*	@post	생성 날짜 set.
	*/
	virtual void SetDateFromKB();

	/**
	*	@brief	키보드로부터 폴더 정보를 입력받는다.
	*	@pre	없음.
	*	@post	폴더 정보 set.
	*/
	virtual void SetRecordFromKB();

	/**
	*	@brief	현재 시간 가져오기.
	*	@pre	없음.
	*	@post	현재 시간을 가져온다.
	*	@return	현재 시간.
	*/
	virtual string GetCurrentTimes();

	/**
	*	@brief	Read a record from file.
	*	@pre	the target file is opened.
	*	@post	student record is set.
	*	@param	fin	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	virtual int ReadDataFromFile(ifstream& fin);

	/**
	*	@brief	Write a record into file.
	*	@pre	the target file is opened. And the list should be initialized.
	*	@post	the target file is included the new student record.
	*	@param	fout	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	virtual int WriteDataToFile(ofstream& fout);

	virtual RelationType CompareByName(const ItemType& data);

	/**
	연산자 오버로딩
	*/
	virtual ItemType operator= (const ItemType& data);
	/**
	*	@brief	연산자 오퍼레이터 < 오버로딩
	*/
	virtual bool operator< (const ItemType& data);

	/**
	*	@brief	연산자 오퍼레이터 > 오버로딩
	*/
	virtual  bool operator> (const ItemType& data);

	/**
	*	@brief	연산자 오퍼레이터 == 오버로딩
	*/
	virtual bool operator== (const ItemType& data);

};
#endif // !_ITEMTYPE_H
