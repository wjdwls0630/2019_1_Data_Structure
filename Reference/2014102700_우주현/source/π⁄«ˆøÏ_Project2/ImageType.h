#pragma once
#ifndef _IMAGETYPE_H
#define _IMAGETYPE_H

#include <iostream>
#include <string>
#include <Windows.h>
#include <mmsystem.h>
#include "ItemType.h"

using namespace std;

class ImageType : public ItemType
{
protected:
	string m_ifName;		// �̹������� �̸�.
	string m_ifAddress;	// �̹������� ��ġ.
	int m_ifBytes;		// �̹������� ũ��.
	string m_ifDate;		// ���� ��¥.
public:
	/**
	*	@brief	�⺻ ������.
	*/
	ImageType()
	{
		m_ifName = "";
		m_ifAddress = "";
		m_ifBytes = 0;
		m_ifDate = GetCurrentTimes();
	}

	/**
	*	@brief �Ҹ���.
	*/
	~ImageType()
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
		return m_ifName;
	}

	/**
	*	@brief	���� ��ġ ��������.
	*	@pre	���� ��ġ�� �����ؾ��Ѵ�.
	*	@post	����.
	*	@return	���� ��ġ.
	*/
	string GetAddress()
	{
		return m_ifAddress;
	}

	/**
	*	@brief	�̹������� ũ�� ��������.
	*	@pre	�̹������� ũ�Ⱑ �����ؾ��Ѵ�.
	*	@post	����.
	*	@return	�̹������� ũ��.
	*/
	int GetBytes()
	{
		return m_ifBytes;
	}

	/**
	*	@brief	���� ��¥ ��������.
	*	@pre	���� ��¥�� �����ؾ��Ѵ�.
	*	@post	����.
	*	@return	���� ��¥.
	*/
	string GetDate()
	{
		return m_ifDate;
	}

	/**
	*	@brief	�̹������� �̸� ����.
	*	@pre	����.
	*	@post	�̹������� �̸��� �����ȴ�.
	*	@param	inName	�̹������� �̸�.
	*/
	void SetName(string inName)
	{
		m_ifName = inName;
	}

	/**
	*	@brief	�̹������� ��ġ ����.
	*	@pre	����.
	*	@post	�̹������� ��ġ�� �����ȴ�.
	*	@param	inAddress	�̹������� ��ġ.
	*/
	void SetAddress(string inAddress)
	{
		m_ifAddress = inAddress;
	}

	/**
	*	@brief	�̹������� ũ�� ����.
	*	@pre	����.
	*	@post	�̹������� ũ�Ⱑ �����ȴ�.
	*	@param	inBytes	�̹������� ũ��.
	*/
	void SetBytes(int inBytes)
	{
		m_ifBytes = inBytes;
	}

	/**
	*	@brief	���� ��¥ ����.
	*	@pre	����.
	*	@post	���� ��¥�� �����ȴ�.
	*	@param	inDate	���� ��¥.
	*/
	void SetDate(string inDate)
	{
		m_ifDate = inDate;
	}

	/**
	*	@brief	�̹������� ���� ���.
	*	@pre	����.
	*	@post	�̹������� ������ �����ȴ�.
	*	@param	inName	�̹������� �̸�.
	*	@param	inAddress	�̹������� ��ġ.
	*	@param	inBytes	�̹������� ũ��.
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
	*	@brief	�̹������� �̸� ���.
	*	@pre	�̹������� �̸��� �����ؾ��Ѵ�.
	*	@post	�̹������� �̸��� ��µȴ�.
	*/
	void DisplayNameOnScreen()
	{
		cout << "\tName : " << m_ifName << endl;
	};

	/**
	*	@brief	�̹������� ��ġ ���.
	*	@pre	�̹������� ��ġ�� �����ؾ��Ѵ�.
	*	@post	�̹������� ��ġ�� ��µȴ�.
	*/
	void DisplayAddressOnScreen()
	{
		cout << "\tAddress : " << m_ifAddress << endl;
	};

	/**
	*	@brief	�̹������� ũ�� ���.
	*	@pre	�̹������� ũ�Ⱑ �����ؾ��Ѵ�.
	*	@post	�̹������� ũ�Ⱑ ��µȴ�.
	*/
	void DisplayBytesOnScreen()
	{
		cout << "\tBytes : " << m_ifBytes << endl;
	};

	/**
	*	@brief	���� ��¥ ���.
	*	@pre	���� ��¥�� �����ؾ��Ѵ�.
	*	@post	���� ��¥�� ��µȴ�.
	*/
	void DisplayDateOnScreen()
	{
		cout << "\tDate : " << m_ifDate << endl;
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
	*	@brief	Ű����κ��� �̹������� �̸��� �Է¹޴´�.
	*	@pre	����.
	*	@post	�̹������� �̸� set.
	*/
	void SetNameFromKB();

	/**
	*	@brief	Ű����κ��� �̹������� ��ġ�� �Է¹޴´�.
	*	@pre	����.
	*	@post	�̹������� ��ġ set.
	*/
	void SetAddressFromKB();

	/**
	*	@brief	Ű����κ��� �̹������� ũ�⸦ �Է¹޴´�.
	*	@pre	����.
	*	@post	�̹������� ũ�� set.
	*/
	void SetBytesFromKB();

	/**
	*	@brief	Ű����κ��� ���� ��¥�� �Է¹޴´�.
	*	@pre	����.
	*	@post	���� ��¥ set.
	*/
	void SetDateFromKB();

	/**
	*	@brief	Ű����κ��� �̹������� ������ �Է¹޴´�.
	*	@pre	����.
	*	@post	�̹������� ���� set.
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
	int OpenMusic(ImageType T);

	RelationType CompareByName(const ImageType& data);

};
#endif // !_IMAGETYPE_H


