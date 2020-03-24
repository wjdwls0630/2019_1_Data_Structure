#pragma once
#ifndef _MUSICTYPE_H
#define _MUSICTYPE_H

#include <string>
#include <stdio.h>
#include <Windows.h>
#include <mmsystem.h>
#include <iostream>
#include "ItemType.h"
#pragma comment(lib,"Winmm.lib")

using namespace std;

class MusicType : public ItemType
{
protected:
	string m_sfName;		// 음악파일 이름.
	string m_sfAddress;	// 음악파일 위치.
	int m_sfBytes;		// 음악파일 크기.
	string m_sfDate;		// 생성 날짜.

public:
	/**
	*	@brief	기본 생성자.
	*/
	MusicType()
	{
		m_sfName = "";
		m_sfAddress = "";
		m_sfBytes = 0;
		m_sfDate = GetCurrentTimes();
	}

	/**
	*	@brief 소멸자.
	*/
	~MusicType()
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
		return m_sfName;
	}

	/**
	*	@brief	파일 위치 가져오기.
	*	@pre	파일 위치가 존재해야한다.
	*	@post	없음.
	*	@return	파일 위치.
	*/
	string GetAddress()
	{
		return m_sfAddress;
	}

	/**
	*	@brief	음악파일 크기 가져오기.
	*	@pre	음악파일 크기가 존재해야한다.
	*	@post	없음.
	*	@return	음악파일 크기.
	*/
	int GetBytes()
	{
		return m_sfBytes;
	}

	/**
	*	@brief	생성 날짜 가져오기.
	*	@pre	생성 날짜가 존재해야한다.
	*	@post	없음.
	*	@return	생성 날짜.
	*/
	string GetDate()
	{
		return m_sfDate;
	}

	/**
	*	@brief	음악파일 이름 지정.
	*	@pre	없음.
	*	@post	음악파일 이름이 지정된다.
	*	@param	inName	음악파일 이름.
	*/
	void SetName(string inName)
	{
		m_sfName = inName;
	}

	/**
	*	@brief	음악파일 위치 지정.
	*	@pre	없음.
	*	@post	음악파일 위치가 지정된다.
	*	@param	inAddress	음악파일 위치.
	*/
	void SetAddress(string inAddress)
	{
		m_sfAddress = inAddress;
	}

	/**
	*	@brief	음악파일 크기 지정.
	*	@pre	없음.
	*	@post	음악파일 크기가 지정된다.
	*	@param	inBytes	음악파일 크기.
	*/
	void SetBytes(int inBytes)
	{
		m_sfBytes = inBytes;
	}

	/**
	*	@brief	생성 날짜 지정.
	*	@pre	없음.
	*	@post	생성 날짜가 지정된다.
	*	@param	inDate	생성 날짜.
	*/
	void SetDate(string inDate)
	{
		m_sfDate = inDate;
	}

	/**
	*	@brief	음악파일 정보 기록.
	*	@pre	없음.
	*	@post	음악파일 정보가 지정된다.
	*	@param	inName	음악파일 이름.
	*	@param	inAddress	음악파일 위치.
	*	@param	inBytes	음악파일 크기.
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
	*	@brief	음악파일 이름 출력.
	*	@pre	음악파일 이름이 존재해야한다.
	*	@post	음악파일 이름이 출력된다.
	*/
	void DisplayNameOnScreen()
	{
		cout << "\tName : " << m_sfName << endl;
	};

	/**
	*	@brief	음악파일 위치 출력.
	*	@pre	음악파일 위치가 존재해야한다.
	*	@post	음악파일 위치가 출력된다.
	*/
	void DisplayAddressOnScreen()
	{
		cout << "\tAddress : " << m_sfAddress << endl;
	};

	/**
	*	@brief	음악파일 크기 출력.
	*	@pre	음악파일 크기가 존재해야한다.
	*	@post	음악파일 크기가 출력된다.
	*/
	void DisplayBytesOnScreen()
	{
		cout << "\tBytes : " << m_sfBytes << endl;
	};

	/**
	*	@brief	생성 날짜 출력.
	*	@pre	생성 날짜가 존재해야한다.
	*	@post	생성 날짜가 출력된다.
	*/
	void DisplayDateOnScreen()
	{
		cout << "\tDate : " << m_sfDate << endl;
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
	*	@brief	키보드로부터 음악파일 이름을 입력받는다.
	*	@pre	없음.
	*	@post	음악파일 이름 set.
	*/
	void SetNameFromKB();

	/**
	*	@brief	키보드로부터 음악파일 위치를 입력받는다.
	*	@pre	없음.
	*	@post	음악파일 위치 set.
	*/
	void SetAddressFromKB();

	/**
	*	@brief	키보드로부터 음악파일 크기를 입력받는다.
	*	@pre	없음.
	*	@post	음악파일 크기 set.
	*/
	void SetBytesFromKB();

	/**
	*	@brief	키보드로부터 생성 날짜를 입력받는다.
	*	@pre	없음.
	*	@post	생성 날짜 set.
	*/
	void SetDateFromKB();

	/**
	*	@brief	키보드로부터 음악파일 정보를 입력받는다.
	*	@pre	없음.
	*	@post	음악파일 정보 set.
	*/
	void SetRecordFromKB();

	/**
	*	@brief	현재 시간 가져오기.
	*	@pre	없음.
	*	@post	현재 시간을 가져온다.
	*	@return	현재 시간.
	*/
	string GetCurrentTimes();

	/// LPCSTR 변환용 함수
	LPTSTR stringtoLPTSTR(const string& s)
	{
		string my_str = s;
		LPTSTR long_string = new TCHAR[my_str.size() + 1];
		strcpy(long_string, my_str.c_str());
		return long_string;
	};

	//음악 파일 열기 및 재생
	int OpenMusic(MusicType T);

	RelationType CompareByName(const MusicType& data);

};
#endif // !_MUSICTYPE_H
