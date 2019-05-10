#pragma once
#ifndef _ITEMTYPE_H
#define _ITEMTYPE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


/**
*	�� ������ ������ ���迡 ���� ������ ����
*/
enum RelationType {LESS, GREATER, EQUAL};


/**
*	�������� ������ ��� �ִ� Ŭ����
*/
class ItemType
{
public:
	/**
	*	����Ʈ ������
	*/
	ItemType()
	{
		m_Id = -1;
		m_sName = "";
		m_sManufacturer = "";
	}

	/**
	*	������
	*/
	ItemType(int Id)
	{
		m_Id = Id;
		m_sName = "";
		m_sManufacturer = "";
	}

	/**
	*	�Ҹ���
	*/
	~ItemType()	{}

	/**
	*	@brief	�������� ID�� �����´�.
	*	@pre	�������� ID�� �����Ѵ�.
	*	@post	����.
	*	@return	�������� ID.
	*/
	int GetId()
	{
		return m_Id;
	}

	/**
	*	@brief	�������� �̸��� �����´�.
	*	@pre	�������� �̸��� �����Ѵ�.
	*	@post	����.
	*	@return	�������� �̸�.
	*/
	string GetName()
	{
		return m_sName;
	}

	/**
	*	@brief	�������� �̸��� �����´�.
	*	@pre	�������� �̸��� �����Ѵ�.
	*	@post	����.
	*	@return	�������� �̸�.
	*/
	string GetManufacturer()
	{
		return m_sManufacturer;
	}

	/**
	*	@brief	�������� ID�� �����Ѵ�.
	*	@pre	����.
	*	@post	�������� ID�� �����Ѵ�.
	*	@param	inId	�������� ID.
	*/
	void SetId(int inId)
	{
		m_Id = inId;
	}
	
	/**
	*	@brief	�������� �̸��� �����Ѵ�.
	*	@pre	����.
	*	@post	�������� �̸��� �����Ѵ�.
	*	@param	inName	�������� �̸�.
	*/
	void SetName(string inName)
	{
		m_sName = inName;
	}
	
	/**
	*	@brief	�������� �̸��� �����Ѵ�.
	*	@pre	����.
	*	@post	�������� �̸��� �����Ѵ�.
	*	@param	inManufacturer	�������� �̸�.
	*/
	void SetManufacturer(string inManufacturer)
	{
		m_sManufacturer = inManufacturer;
	}
	
	/**
	*	@brief	�������� ���ڵ带 �����Ѵ�.
	*	@pre	����.
	*	@post	�������� ���ڵ带 �����Ѵ�.
	*	@param	inId	�������� ID.
	*	@param	inName	�������� �̸�.
	*	@param	inManufacturer	�������� �̸�.
	*/
	void SetRecord(int inId, string inName, string inManufacturer)
	{
		SetId(inId);
		SetName(inName);
		SetManufacturer(inManufacturer);
	}

	/**
	*	@brief	�������� ID�� ��ũ���� ����Ѵ�.
	*	@pre	�������� ID�� �����Ѵ�.
	*	@post	�������� ID�� ����Ѵ�.
	*/
	void DisplayIdOnScreen() 
	{
		cout << "\tID   : " << m_Id << endl; 
	};

	/**
	*	@brief	�������� �̸��� ��ũ���� ����Ѵ�.
	*	@pre	�������� �̸��� �����Ѵ�.
	*	@post	�������� �̸��� ����Ѵ�.
	*/
	void DisplayNameOnScreen() 
	{
		cout << "\tName : " << m_sName << endl; 
	};

	/**
	*	@brief	�������� �̸��� ��ũ���� ����Ѵ�.
	*	@pre	�������� �̸��� �����Ѵ�.
	*	@post	�������� �̸��� ����Ѵ�.
	*/
	void DisplayManufacturerOnScreen() 
	{
		cout << "\tManufacturer : " << m_sManufacturer << endl; 
	};

	/**
	*	@brief	�������� ��� ������ ��ũ���� ����Ѵ�.
	*	@pre	�������� ��� ������ �����Ѵ�.
	*	@post	�������� ��� ������ ����Ѵ�.
	*/
	void DisplayRecordOnScreen()
	{
		DisplayIdOnScreen();
		DisplayNameOnScreen();
		DisplayManufacturerOnScreen();
	};

	/**
	*	@brief	Ű����κ��� �������� ID�� �Է¹޴´�.
	*	@pre	����.
	*	@post	�������� ID�� �����Ѵ�.
	*/
	void SetIdFromKB();

	/**
	*	@brief	Ű����κ��� �������� �̸��� �Է¹޴´�.
	*	@pre	����.
	*	@post	�������� �̸��� �����Ѵ�.
	*/
	void SetNameFromKB();

	/**
	*	@brief	Ű����κ��� �������� �̸��� �Է¹޴´�.
	*	@pre	����.
	*	@post	�������� �̸��� �����Ѵ�.
	*/
	void SetManufacturerFromKB();
	
	/**
	*	@brief	Ű����κ��� �������� ��� ������ �Է¹޴´�.
	*	@pre	����.
	*	@post	�������� ��� ������ �����Ѵ�.
	*/
	void SetRecordFromKB();

	/**
	*	@brief	���Ϸκ��� �������� ��� ������ �о�´�.
	*	@pre	������ ������ ����.
	*	@post	�������� ��� ������ �����Ѵ�.
	*	@param	fin		���� ��ũ����.
	*	@return	�Լ��� �� �۵��ϸ� 1�� �����ϰ�, �׷��� ������ 0�� �����Ѵ�.
	*/
	int ReadDataFromFile(ifstream& fin);

	/**
	*	@brief	���Ͽ� �������� ��� ������ ����.
	*	@pre	������ ������ ����, ����Ʈ�� �ʱ�ȭ�Ѵ�.
	*	@post	������ ���Ͽ� ���ο� �����۵��� �����Ѵ�.
	*	@param	fout	���� ��ũ����.
	*	@return	�Լ��� �� �۵��ϸ� 1�� �����ϰ�, �׷��� ������ 0�� �����Ѵ�.
	*/
	int WriteDataToFile(ofstream& fout);
	
	/**
	*	�� �������� ���Ѵ�.
	*	@brief	�������� ID�� �� �������� ���Ѵ�.
	*	@pre	�� �����۵��� �ʱ�ȭ�Ǿ���Ѵ�.
	*	@post	�� �������� ���Ͽ� ����� �����Ѵ�.
	*	@param	data	���ϱ� ���� ����.
	*	@return	this.id < data.id�� �� LESS�� ����, 
	*			if this.id > data.id�� �� GREATER�� ����,
	*			�׷��� ���� �� EQUAL�� ����.
	*/
	RelationType CompareByID(const ItemType &data);
	
	/**
	*	@brief	'<'�� �������Ѵ�.
	*	@pre	���� '<'���� ���� �Ǿ��ִ�.
	*	@post	'<' ������ �� ������ ����� �� �ִ�.
	*	@return	�ش� ���̽��� TRUE, �׷��� ������ FALSE.
	*/
	bool ItemType::operator < (ItemType &data)
	{
		if(this -> GetId() < data.m_Id)
			return true;
		else
			return false;
	}

	/**
	*	@brief	'>'�� �������Ѵ�.
	*	@pre	���� '>'���� ���� �Ǿ��ִ�.
	*	@post	'>' ������ �� ������ ����� �� �ִ�.
	*	@return	�ش� ���̽��� TRUE, �׷��� ������ FALSE.
	*/
	bool ItemType::operator > (ItemType &data)
	{
		if(this -> GetId() > data.m_Id)
			return true;
		else
			return false;
	}

	/**
	*	@brief	'=='�� �������Ѵ�.
	*	@pre	���� '=='���� ���� �Ǿ��ִ�.
	*	@post	'==' ������ �� ������ ����� �� �ִ�.
	*	@return	�ش� ���̽��� TRUE, �׷��� ������ FALSE.
	*/
	bool ItemType::operator == (ItemType &data)
	{
		if(this -> GetId() == data.m_Id || this -> GetName() == data.m_sName) 
		{
			return true;
		} 
		else
			return false;
	}

	/**
	*	@brief	'='�� �������Ѵ�.
	*	@pre	���� '='���� ���� �Ǿ��ִ�.
	*	@post	'=' ������ �� ������ ����� �� �ִ�.
	*	@return	�ش� ���̽��� TRUE, �׷��� ������ FALSE.
	*/
	ItemType& operator=(ItemType& data)
	{
		this -> SetName(data.GetName());
		this -> SetId(data.GetId());
		this -> SetManufacturer(data.GetManufacturer());
		return *this;
	}

	/**
	*	@brief	'>>'�� �������Ѵ�.
	*	@pre	���� '>>'���� ���� �Ǿ��ִ�.
	*	@post	'>>' ������ �� ������ ����� �� �ִ�.
	*	@return	�ش� ���̽��� TRUE, �׷��� ������ FALSE.
	*/
	friend istream& operator >> (istream& os, ItemType& data)
	{
		os >> data.m_Id >> data.m_sName >> data.m_sManufacturer;
		return os;
	}

protected:
	int m_Id;				///< �������� ID.
	string m_sName;			///< �������� �̸�.
	string m_sManufacturer;	///< �������� �̸�.
};

#endif  // _ITEMTYPE_H
