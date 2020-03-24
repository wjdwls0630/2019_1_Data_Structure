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
	string m_sfName;		// �������� �̸�.
	string m_sfAddress;	// �������� ��ġ.
	int m_sfBytes;		// �������� ũ��.
	string m_sfDate;		// ���� ��¥.

public:
	/**
	*	@brief	�⺻ ������.
	*/
	MusicType()
	{
		m_sfName = "";
		m_sfAddress = "";
		m_sfBytes = 0;
		m_sfDate = GetCurrentTimes();
	}

	/**
	*	@brief �Ҹ���.
	*/
	~MusicType()
	{
	}

	/**
	*	@brief	���� �̸� ��������.
	*	@pre	���� �̸��� �����ؾ��Ѵ�.
	*	@post	����.
	*	@return	���� �̸�.
	*/
	string GetName()
	{
		return m_sfName;
	}

	/**
	*	@brief	���� ��ġ ��������.
	*	@pre	���� ��ġ�� �����ؾ��Ѵ�.
	*	@post	����.
	*	@return	���� ��ġ.
	*/
	string GetAddress()
	{
		return m_sfAddress;
	}

	/**
	*	@brief	�������� ũ�� ��������.
	*	@pre	�������� ũ�Ⱑ �����ؾ��Ѵ�.
	*	@post	����.
	*	@return	�������� ũ��.
	*/
	int GetBytes()
	{
		return m_sfBytes;
	}

	/**
	*	@brief	���� ��¥ ��������.
	*	@pre	���� ��¥�� �����ؾ��Ѵ�.
	*	@post	����.
	*	@return	���� ��¥.
	*/
	string GetDate()
	{
		return m_sfDate;
	}

	/**
	*	@brief	�������� �̸� ����.
	*	@pre	����.
	*	@post	�������� �̸��� �����ȴ�.
	*	@param	inName	�������� �̸�.
	*/
	void SetName(string inName)
	{
		m_sfName = inName;
	}

	/**
	*	@brief	�������� ��ġ ����.
	*	@pre	����.
	*	@post	�������� ��ġ�� �����ȴ�.
	*	@param	inAddress	�������� ��ġ.
	*/
	void SetAddress(string inAddress)
	{
		m_sfAddress = inAddress;
	}

	/**
	*	@brief	�������� ũ�� ����.
	*	@pre	����.
	*	@post	�������� ũ�Ⱑ �����ȴ�.
	*	@param	inBytes	�������� ũ��.
	*/
	void SetBytes(int inBytes)
	{
		m_sfBytes = inBytes;
	}

	/**
	*	@brief	���� ��¥ ����.
	*	@pre	����.
	*	@post	���� ��¥�� �����ȴ�.
	*	@param	inDate	���� ��¥.
	*/
	void SetDate(string inDate)
	{
		m_sfDate = inDate;
	}

	/**
	*	@brief	�������� ���� ���.
	*	@pre	����.
	*	@post	�������� ������ �����ȴ�.
	*	@param	inName	�������� �̸�.
	*	@param	inAddress	�������� ��ġ.
	*	@param	inBytes	�������� ũ��.
	*	@param	inDate	���� ��¥.
	*/
	void SetRecord(string inName, string inAddress, int inBytes, string inDate)
	{
		SetName(inName);
		SetAddress(inAddress);
		SetBytes(inBytes);
		SetDate(inDate);
	}

	/**
	*	@brief	�������� �̸� ���.
	*	@pre	�������� �̸��� �����ؾ��Ѵ�.
	*	@post	�������� �̸��� ��µȴ�.
	*/
	void DisplayNameOnScreen()
	{
		cout << "\tName : " << m_sfName << endl;
	};

	/**
	*	@brief	�������� ��ġ ���.
	*	@pre	�������� ��ġ�� �����ؾ��Ѵ�.
	*	@post	�������� ��ġ�� ��µȴ�.
	*/
	void DisplayAddressOnScreen()
	{
		cout << "\tAddress : " << m_sfAddress << endl;
	};

	/**
	*	@brief	�������� ũ�� ���.
	*	@pre	�������� ũ�Ⱑ �����ؾ��Ѵ�.
	*	@post	�������� ũ�Ⱑ ��µȴ�.
	*/
	void DisplayBytesOnScreen()
	{
		cout << "\tBytes : " << m_sfBytes << endl;
	};

	/**
	*	@brief	���� ��¥ ���.
	*	@pre	���� ��¥�� �����ؾ��Ѵ�.
	*	@post	���� ��¥�� ��µȴ�.
	*/
	void DisplayDateOnScreen()
	{
		cout << "\tDate : " << m_sfDate << endl;
	};

	/**
	*	@brief	���� ���� ���.
	*	@pre	���� ������ �����ؾ��Ѵ�.
	*	@post	���� ������ ��µȴ�.
	*/
	void DisplayRecordOnScreen()
	{
		DisplayNameOnScreen();
		DisplayAddressOnScreen();
		DisplayBytesOnScreen();
		DisplayDateOnScreen();
	};


	/**
	*	@brief	Ű����κ��� �������� �̸��� �Է¹޴´�.
	*	@pre	����.
	*	@post	�������� �̸� set.
	*/
	void SetNameFromKB();

	/**
	*	@brief	Ű����κ��� �������� ��ġ�� �Է¹޴´�.
	*	@pre	����.
	*	@post	�������� ��ġ set.
	*/
	void SetAddressFromKB();

	/**
	*	@brief	Ű����κ��� �������� ũ�⸦ �Է¹޴´�.
	*	@pre	����.
	*	@post	�������� ũ�� set.
	*/
	void SetBytesFromKB();

	/**
	*	@brief	Ű����κ��� ���� ��¥�� �Է¹޴´�.
	*	@pre	����.
	*	@post	���� ��¥ set.
	*/
	void SetDateFromKB();

	/**
	*	@brief	Ű����κ��� �������� ������ �Է¹޴´�.
	*	@pre	����.
	*	@post	�������� ���� set.
	*/
	void SetRecordFromKB();

	/**
	*	@brief	���� �ð� ��������.
	*	@pre	����.
	*	@post	���� �ð��� �����´�.
	*	@return	���� �ð�.
	*/
	string GetCurrentTimes();

	/// LPCSTR ��ȯ�� �Լ�
	LPTSTR stringtoLPTSTR(const string& s)
	{
		string my_str = s;
		LPTSTR long_string = new TCHAR[my_str.size() + 1];
		strcpy(long_string, my_str.c_str());
		return long_string;
	};

	//���� ���� ���� �� ���
	int OpenMusic(MusicType T);

	RelationType CompareByName(const MusicType& data);

};
#endif // !_MUSICTYPE_H
