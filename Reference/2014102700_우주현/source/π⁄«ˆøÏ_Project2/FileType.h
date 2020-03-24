#pragma once
#ifndef _FILETYPE_H
#define _FILETYPE_H

#include <iostream>
#include <fstream>
#include <string>
#include <iomanip>
#include <time.h>
#include "DoublyLinkedList.h"
#include "ItemType.h"
using namespace std;

class FileType : public ItemType
{
protected:
	string m_dfName;		// 파일 이름.
	string m_dfAddress;	// 파일 위치.
	int m_dfBytes;		// 파일 크기.
	string m_dfDate;		// 파일 생성 날짜.
public:
	/**
	*	@brief	기본 생성자.
	*/
	FileType()
	{
		m_dfName = "";
		m_dfAddress = "";
		m_dfBytes = 0;
		m_dfDate = GetCurrentTimes();
	}

	/**
	*	@brief 소멸자.
	*/
	~FileType()
	{
	}

	/**
	*	@brief	파일 이름 가져오기.
	*	@pre	파일 이름이 존재해야한다.
	*	@post	없음.
	*	@return	파일 이름.
	*/
	string GetName()
	{
		return m_dfName;
	}

	/**
	*	@brief	파일 위치 가져오기.
	*	@pre	파일 위치가 존재해야한다.
	*	@post	없음.
	*	@return	파일 위치.
	*/
	string GetAddress()
	{
		return m_dfAddress;
	}

	/**
	*	@brief	폴더 크기 가져오기.
	*	@pre	폴더 크기가 존재해야한다.
	*	@post	없음.
	*	@return	폴더 크기.
	*/
	int GetBytes()
	{
		return m_dfBytes;
	}

	/**
	*	@brief	생성 날짜 가져오기.
	*	@pre	생성 날짜가 존재해야한다.
	*	@post	없음.
	*	@return	생성 날짜.
	*/
	string GetDate()
	{
		return m_dfDate;
	}

	/**
	*	@brief	폴더 이름 지정.
	*	@pre	없음.
	*	@post	폴더 이름이 지정된다.
	*	@param	inName	폴더 이름.
	*/
	void SetName(string inName)
	{
		m_dfName = inName;
	}

	/**
	*	@brief	폴더 위치 지정.
	*	@pre	없음.
	*	@post	폴더 위치가 지정된다.
	*	@param	inAddress	폴더 위치.
	*/
	void SetAddress(string inAddress)
	{
		m_dfAddress = inAddress;
	}

	/**
	*	@brief	폴더 크기 지정.
	*	@pre	없음.
	*	@post	폴더 크기가 지정된다.
	*	@param	inBytes	폴더 크기.
	*/
	void SetBytes(int inBytes)
	{
		m_dfBytes = inBytes;
	}

	/**
	*	@brief	생성 날짜 지정.
	*	@pre	없음.
	*	@post	생성 날짜가 지정된다.
	*	@param	inDate	생성 날짜.
	*/
	void SetDate(string inDate)
	{
		m_dfDate = inDate;
	}

	/**
	*	@brief	폴더 정보 기록.
	*	@pre	없음.
	*	@post	폴더 정보가 지정된다.
	*	@param	inName	폴더 이름.
	*	@param	inAddress	폴더 위치.
	*	@param	inBytes	폴더 크기.
	*	@param	inDate	생성 날짜.
	*/
	void SetRecord(string inName, string inAddress, int inBytes, string inDate)
	{
		SetName(inName);
		SetAddress(inAddress);
		SetBytes(inBytes);
		SetDate(inDate);
	}

	/**
	*	@brief	폴더 이름 출력.
	*	@pre	폴더 이름이 존재해야한다.
	*	@post	폴더 이름이 출력된다.
	*/
	void DisplayNameOnScreen()
	{
		cout << "\tName : " << m_dfName << endl;
	};

	/**
	*	@brief	폴더 위치 출력.
	*	@pre	폴더 위치가 존재해야한다.
	*	@post	폴더 위치가 출력된다.
	*/
	void DisplayAddressOnScreen()
	{
		cout << "\tAddress : " << m_dfAddress << endl;
	};

	/**
	*	@brief	폴더 크기 출력.
	*	@pre	폴더 크기가 존재해야한다.
	*	@post	폴더 크기가 출력된다.
	*/
	void DisplayBytesOnScreen()
	{
		cout << "\tBytes : " << m_dfBytes << endl;
	};

	/**
	*	@brief	생성 날짜 출력.
	*	@pre	생성 날짜가 존재해야한다.
	*	@post	생성 날짜가 출력된다.
	*/
	void DisplayDateOnScreen()
	{
		cout << "\tDate : " << m_dfDate << endl;
	};

	/**
	*	@brief	파일 정보 출력.
	*	@pre	파일 정보가 존재해야한다.
	*	@post	파일 정보가 출력된다.
	*/
	void DisplayRecordOnScreen()
	{
		DisplayNameOnScreen();
		DisplayAddressOnScreen();
		DisplayBytesOnScreen();
		DisplayDateOnScreen();
	};


	/**
	*	@brief	키보드로부터 폴더 이름을 입력받는다.
	*	@pre	없음.
	*	@post	폴더 이름 set.
	*/
	void SetNameFromKB();

	/**
	*	@brief	키보드로부터 폴더 위치를 입력받는다.
	*	@pre	없음.
	*	@post	폴더 위치 set.
	*/
	void SetAddressFromKB();

	/**
	*	@brief	키보드로부터 폴더 크기를 입력받는다.
	*	@pre	없음.
	*	@post	폴더 크기 set.
	*/
	void SetBytesFromKB();

	/**
	*	@brief	키보드로부터 생성 날짜를 입력받는다.
	*	@pre	없음.
	*	@post	생성 날짜 set.
	*/
	void SetDateFromKB();

	/**
	*	@brief	키보드로부터 생성 날짜를 입력받는다.
	*	@pre	없음.
	*	@post	생성 날짜 set.
	*/
	void SetExtensionFromKB();

	/**
	*	@brief	키보드로부터 폴더 정보를 입력받는다.
	*	@pre	없음.
	*	@post	폴더 정보 set.
	*/
	void SetRecordFromKB();

	/**
	*	@brief	현재 시간 가져오기.
	*	@pre	없음.
	*	@post	현재 시간을 가져온다.
	*	@return	현재 시간.
	*/
	string GetCurrentTimes();

	/**
	*	@brief	Read a record from file.
	*	@pre	the target file is opened.
	*	@post	student record is set.
	*	@param	fin	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int ReadDataFromFile(ifstream& fin);

	/**
	*	@brief	Write a record into file.
	*	@pre	the target file is opened. And the list should be initialized.
	*	@post	the target file is included the new student record.
	*	@param	fout	file descriptor.
	*	@return	return 1 if this function works well, otherwise 0.
	*/
	int WriteDataToFile(ofstream& fout);

	RelationType CompareByName(const FileType& data);

};


#endif // !_FILETYPE_H
