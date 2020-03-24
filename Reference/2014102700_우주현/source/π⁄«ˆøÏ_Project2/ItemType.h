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
	string m_itName;		// ���� �̸�.
	string m_itAddress;	// ���� ��ġ.
	int m_itBytes;		// ���� ũ��.
	string m_itDate;		// ���� ��¥.

public:
	/**
	*	@brief	�⺻ ������.
	*/
	ItemType()
	{
		m_itName = "";
		m_itAddress = "";
		m_itBytes = 0;
		m_itDate = GetCurrentTimes();
	}

	/**
	*	@brief �Ҹ���.
	*/
	~ItemType()
	{
	}

	/**
	*	@brief	���� �̸� ��������.
	*	@pre	���� �̸��� �����ؾ��Ѵ�.
	*	@post	����.
	*	@return	���� �̸�.
	*/
	virtual string GetName();
	/**
	*	@brief	���� ��ġ ��������.
	*	@pre	���� ��ġ�� �����ؾ��Ѵ�.
	*	@post	����.
	*	@return	���� ��ġ.
	*/
	virtual string GetAddress();

	/**
	*	@brief	���� ũ�� ��������.
	*	@pre	���� ũ�Ⱑ �����ؾ��Ѵ�.
	*	@post	����.
	*	@return	���� ũ��.
	*/
	virtual int GetBytes();
	/**
	*	@brief	���� ��¥ ��������.
	*	@pre	���� ��¥�� �����ؾ��Ѵ�.
	*	@post	����.
	*	@return	���� ��¥.
	*/
	virtual string GetDate();
	/**
	*	@brief	���� �̸� ����.
	*	@pre	����.
	*	@post	���� �̸��� �����ȴ�.
	*	@param	inName	���� �̸�.
	*/
	virtual void SetName(string inName);

	/**
	*	@brief	���� ��ġ ����.
	*	@pre	����.
	*	@post	���� ��ġ�� �����ȴ�.
	*	@param	inAddress	���� ��ġ.
	*/
	virtual void SetAddress(string inAddress);

	/**
	*	@brief	���� ũ�� ����.
	*	@pre	����.
	*	@post	���� ũ�Ⱑ �����ȴ�.
	*	@param	inBytes	���� ũ��.
	*/
	virtual void SetBytes(int inBytes);

	/**
	*	@brief	���� ��¥ ����.
	*	@pre	����.
	*	@post	���� ��¥�� �����ȴ�.
	*	@param	inDate	���� ��¥.
	*/
	virtual void SetDate(string inDate);

	/**
	*	@brief	���� ���� ���.
	*	@pre	����.
	*	@post	���� ������ �����ȴ�.
	*	@param	inName	���� �̸�.
	*	@param	inAddress	���� ��ġ.
	*	@param	inBytes	���� ũ��.
	*	@param	inDate	���� ��¥.
	*/
	virtual void SetRecord(string inName, string inAddress, int inBytes, string inDate);

	/**
	*	@brief	���� �̸� ���.
	*	@pre	���� �̸��� �����ؾ��Ѵ�.
	*	@post	���� �̸��� ��µȴ�.
	*/
	virtual void DisplayNameOnScreen();

	/**
	*	@brief	���� ��ġ ���.
	*	@pre	���� ��ġ�� �����ؾ��Ѵ�.
	*	@post	���� ��ġ�� ��µȴ�.
	*/
	virtual void DisplayAddressOnScreen();

	/**
	*	@brief	���� ũ�� ���.
	*	@pre	���� ũ�Ⱑ �����ؾ��Ѵ�.
	*	@post	���� ũ�Ⱑ ��µȴ�.
	*/
	virtual void DisplayBytesOnScreen();

	/**
	*	@brief	���� ��¥ ���.
	*	@pre	���� ��¥�� �����ؾ��Ѵ�.
	*	@post	���� ��¥�� ��µȴ�.
	*/
	virtual void DisplayDateOnScreen();

	/**
	*	@brief	���� ���� ���.
	*	@pre	���� ������ �����ؾ��Ѵ�.
	*	@post	���� ������ ��µȴ�.
	*/
	virtual void DisplayRecordOnScreen();


	/**
	*	@brief	Ű����κ��� ���� �̸��� �Է¹޴´�.
	*	@pre	����.
	*	@post	���� �̸� set.
	*/
	virtual void SetNameFromKB();

	/**
	*	@brief	Ű����κ��� ���� ��ġ�� �Է¹޴´�.
	*	@pre	����.
	*	@post	���� ��ġ set.
	*/
	virtual void SetAddressFromKB();

	/**
	*	@brief	Ű����κ��� ���� ũ�⸦ �Է¹޴´�.
	*	@pre	����.
	*	@post	���� ũ�� set.
	*/
	virtual void SetBytesFromKB();

	/**
	*	@brief	Ű����κ��� ���� ��¥�� �Է¹޴´�.
	*	@pre	����.
	*	@post	���� ��¥ set.
	*/
	virtual void SetDateFromKB();

	/**
	*	@brief	Ű����κ��� ���� ������ �Է¹޴´�.
	*	@pre	����.
	*	@post	���� ���� set.
	*/
	virtual void SetRecordFromKB();

	/**
	*	@brief	���� �ð� ��������.
	*	@pre	����.
	*	@post	���� �ð��� �����´�.
	*	@return	���� �ð�.
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
	������ �����ε�
	*/
	virtual ItemType operator= (const ItemType& data);
	/**
	*	@brief	������ ���۷����� < �����ε�
	*/
	virtual bool operator< (const ItemType& data);

	/**
	*	@brief	������ ���۷����� > �����ε�
	*/
	virtual  bool operator> (const ItemType& data);

	/**
	*	@brief	������ ���۷����� == �����ε�
	*/
	virtual bool operator== (const ItemType& data);

};
#endif // !_ITEMTYPE_H
