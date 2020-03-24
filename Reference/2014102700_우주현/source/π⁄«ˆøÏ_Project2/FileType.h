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
	string m_dfName;		// ���� �̸�.
	string m_dfAddress;	// ���� ��ġ.
	int m_dfBytes;		// ���� ũ��.
	string m_dfDate;		// ���� ���� ��¥.
public:
	/**
	*	@brief	�⺻ ������.
	*/
	FileType()
	{
		m_dfName = "";
		m_dfAddress = "";
		m_dfBytes = 0;
		m_dfDate = GetCurrentTimes();
	}

	/**
	*	@brief �Ҹ���.
	*/
	~FileType()
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
		return m_dfName;
	}

	/**
	*	@brief	���� ��ġ ��������.
	*	@pre	���� ��ġ�� �����ؾ��Ѵ�.
	*	@post	����.
	*	@return	���� ��ġ.
	*/
	string GetAddress()
	{
		return m_dfAddress;
	}

	/**
	*	@brief	���� ũ�� ��������.
	*	@pre	���� ũ�Ⱑ �����ؾ��Ѵ�.
	*	@post	����.
	*	@return	���� ũ��.
	*/
	int GetBytes()
	{
		return m_dfBytes;
	}

	/**
	*	@brief	���� ��¥ ��������.
	*	@pre	���� ��¥�� �����ؾ��Ѵ�.
	*	@post	����.
	*	@return	���� ��¥.
	*/
	string GetDate()
	{
		return m_dfDate;
	}

	/**
	*	@brief	���� �̸� ����.
	*	@pre	����.
	*	@post	���� �̸��� �����ȴ�.
	*	@param	inName	���� �̸�.
	*/
	void SetName(string inName)
	{
		m_dfName = inName;
	}

	/**
	*	@brief	���� ��ġ ����.
	*	@pre	����.
	*	@post	���� ��ġ�� �����ȴ�.
	*	@param	inAddress	���� ��ġ.
	*/
	void SetAddress(string inAddress)
	{
		m_dfAddress = inAddress;
	}

	/**
	*	@brief	���� ũ�� ����.
	*	@pre	����.
	*	@post	���� ũ�Ⱑ �����ȴ�.
	*	@param	inBytes	���� ũ��.
	*/
	void SetBytes(int inBytes)
	{
		m_dfBytes = inBytes;
	}

	/**
	*	@brief	���� ��¥ ����.
	*	@pre	����.
	*	@post	���� ��¥�� �����ȴ�.
	*	@param	inDate	���� ��¥.
	*/
	void SetDate(string inDate)
	{
		m_dfDate = inDate;
	}

	/**
	*	@brief	���� ���� ���.
	*	@pre	����.
	*	@post	���� ������ �����ȴ�.
	*	@param	inName	���� �̸�.
	*	@param	inAddress	���� ��ġ.
	*	@param	inBytes	���� ũ��.
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
	*	@brief	���� �̸� ���.
	*	@pre	���� �̸��� �����ؾ��Ѵ�.
	*	@post	���� �̸��� ��µȴ�.
	*/
	void DisplayNameOnScreen()
	{
		cout << "\tName : " << m_dfName << endl;
	};

	/**
	*	@brief	���� ��ġ ���.
	*	@pre	���� ��ġ�� �����ؾ��Ѵ�.
	*	@post	���� ��ġ�� ��µȴ�.
	*/
	void DisplayAddressOnScreen()
	{
		cout << "\tAddress : " << m_dfAddress << endl;
	};

	/**
	*	@brief	���� ũ�� ���.
	*	@pre	���� ũ�Ⱑ �����ؾ��Ѵ�.
	*	@post	���� ũ�Ⱑ ��µȴ�.
	*/
	void DisplayBytesOnScreen()
	{
		cout << "\tBytes : " << m_dfBytes << endl;
	};

	/**
	*	@brief	���� ��¥ ���.
	*	@pre	���� ��¥�� �����ؾ��Ѵ�.
	*	@post	���� ��¥�� ��µȴ�.
	*/
	void DisplayDateOnScreen()
	{
		cout << "\tDate : " << m_dfDate << endl;
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
	*	@brief	Ű����κ��� ���� �̸��� �Է¹޴´�.
	*	@pre	����.
	*	@post	���� �̸� set.
	*/
	void SetNameFromKB();

	/**
	*	@brief	Ű����κ��� ���� ��ġ�� �Է¹޴´�.
	*	@pre	����.
	*	@post	���� ��ġ set.
	*/
	void SetAddressFromKB();

	/**
	*	@brief	Ű����κ��� ���� ũ�⸦ �Է¹޴´�.
	*	@pre	����.
	*	@post	���� ũ�� set.
	*/
	void SetBytesFromKB();

	/**
	*	@brief	Ű����κ��� ���� ��¥�� �Է¹޴´�.
	*	@pre	����.
	*	@post	���� ��¥ set.
	*/
	void SetDateFromKB();

	/**
	*	@brief	Ű����κ��� ���� ��¥�� �Է¹޴´�.
	*	@pre	����.
	*	@post	���� ��¥ set.
	*/
	void SetExtensionFromKB();

	/**
	*	@brief	Ű����κ��� ���� ������ �Է¹޴´�.
	*	@pre	����.
	*	@post	���� ���� set.
	*/
	void SetRecordFromKB();

	/**
	*	@brief	���� �ð� ��������.
	*	@pre	����.
	*	@post	���� �ð��� �����´�.
	*	@return	���� �ð�.
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
