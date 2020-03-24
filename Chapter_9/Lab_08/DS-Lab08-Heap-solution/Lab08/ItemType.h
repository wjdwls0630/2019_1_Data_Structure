#ifndef _ITEMTYPE_H
#define _ITEMTYPE_H

#include <iostream>
#include <string>

using namespace std;


/**
*	��ǰ ���� Ŭ����.
*	@author	�躴��
*	@date	2014.11.20
*/
class ItemType
{
public:
	/**
	*	������.
	*/
	ItemType()
	{
		m_Id = -1;
		m_sName = "";
		m_sManufacturer = "";
	}

	/**
	*	�Ҹ���.
	*/
	~ItemType()	{}

	/**
	*	@brief	��ǰ ID ��ȯ �Լ�.
	*	@pre	��ǰ ID�� ����ȴ�.
	*	@post	none.
	*	@return	��ǰ ID�� ��ȯ�Ѵ�.
	*/
	int GetId()
	{
		return m_Id;
	}

	/**
	*	@brief	��ǰ�� ��ȯ �Լ�.
	*	@pre	��ǰ���� ����ȴ�.
	*	@post	none.
	*	@return	��ǰ���� ��ȯ�Ѵ�.
	*/
	string GetName()
	{
		return m_sName;
	}

	/**
	*	@brief	�������� ��ȯ �Լ�.
	*	@pre	�������ڰ� ����ȴ�.
	*	@post	none.
	*	@return	�������ڸ� ��ȯ�Ѵ�.
	*/
	string GetManufacturer()
	{
		return m_sManufacturer;
	}

	/**
	*	@brief	��ǰ ID �Է� �Լ�.
	*	@pre	none.
	*	@post	��ǰ ID�� �Էµȴ�.
	*	@param	inId	��ǰ ID.
	*/
	void SetId(int inId)
	{
		m_Id = inId;
	}
	
	/**
	*	@brief	��ǰ�� �Է� �Լ�.
	*	@pre	none.
	*	@post	��ǰ���� �Էµȴ�.
	*	@param	inName	��ǰ��.
	*/
	void SetName(string inName)
	{
		m_sName = inName;
	}
	
	/**
	*	@brief	�������� �Է� �Լ�.
	*	@pre	none.
	*	@post	�������ڰ� �Էµȴ�.
	*	@param	inManufacturer	��������.
	*/
	void SetManufacturer(string inManufacturer)
	{
		m_sManufacturer = inManufacturer;
	}
	
	/**
	*	@brief	��ǰ ���� �Է� �Լ�.
	*	@pre	none.
	*	@post	��ǰ ������ �Էµȴ�.
	*	@param	inId	��ǰ ID.
	*	@param	inName	��ǰ��.
	*	@param	inManufacturer	����������.
	*/
	void SetRecord(int inId, string inName, string inManufacturer)
	{
		SetId(inId);
		SetName(inName);
		SetManufacturer(inManufacturer);
	}

	/**
	*	@brief	��ǰ ID ��� �Լ�.
	*	@pre	��ǰ ID�� �����Ѵ�.
	*	@post	��ǰ ID�� ��µȴ�.
	*/
	void DisplayIdOnScreen() 
	{
		cout << "\tID   : " << m_Id << endl; 
	};

	/**
	*	@brief	��ǰ�� ��� �Լ�.
	*	@pre	��ǰ���� �����Ѵ�.
	*	@post	��ǰ���� ��µȴ�.
	*/
	void DisplayNameOnScreen() 
	{
		cout << "\tName : " << m_sName << endl; 
	};

	/**
	*	@brief	�������� ��� �Լ�.
	*	@pre	�������ڰ� �����Ѵ�.
	*	@post	�������ڰ� ��µȴ�.
	*/
	void DisplayManufacturerOnScreen() 
	{
		cout << "\tManufacturer : " << m_sManufacturer << endl; 
	};

	/**
	*	@brief	��ǰ���� ��� �Լ�.
	*	@pre	��ǰ������ �����Ѵ�.
	*	@post	��ǰ������ ��µȴ�.
	*/
	void DisplayRecordOnScreen()
	{
		DisplayIdOnScreen();
		DisplayNameOnScreen();
		DisplayManufacturerOnScreen();
	};

	/**
	*	@brief	Ű����� ID �Է� �Լ�.
	*	@pre	none.
	*	@post	��ǰ ID�� ����ȴ�.
	*/
	void SetIdFromKB();

	/**
	*	@brief	Ű����� ��ǰ�� �Է� �Լ�.
	*	@pre	none.
	*	@post	��ǰ���� ����ȴ�.
	*/
	void SetNameFromKB();

	/**
	*	@brief	Ű����� �������� �Է� �Լ�.
	*	@pre	none.
	*	@post	�������ڰ� ����ȴ�.
	*/
	void SetManufacturerFromKB();
	
	/**
	*	@brief	Ű����� ��ǰ���� �Է� �Լ�.
	*	@pre	none.
	*	@post	��ǰ������ ����ȴ�.
	*/
	void SetRecordFromKB();
	
	/**
	*	@brief	ũ��� ������ �����ε� <
	*	@pre	�ΰ��� ItemType�� ������ ȣ���Ѵ�.
	*	@post	ȣ���� ItemType�� ID�� ũ�⸦ ���Ѵ�.
	*	@param	item	ItemType�� ����.
	*	@return	������ True, Ʋ���� False�� ��ȯ�Ѵ�.
	*/
	bool operator<(ItemType item);

	/**
	*	@brief	ũ��� ������ �����ε� >
	*	@pre	�ΰ��� ItemType�� ������ ȣ���Ѵ�.
	*	@post	ȣ���� ItemType�� ID�� ũ�⸦ ���Ѵ�.
	*	@param	item	ItemType�� ����.
	*	@return	������ True, Ʋ���� False�� ��ȯ�Ѵ�.
	*/
	bool operator>(ItemType item);

	/**
	*	@brief	ũ��� ������ �����ε� ==
	*	@pre	�ΰ��� ItemType�� ������ ȣ���Ѵ�.
	*	@post	ȣ���� ItemType�� ID�� ũ�⸦ ���Ѵ�.
	*	@param	item	ItemType�� ����.
	*	@return	������ True, Ʋ���� False�� ��ȯ�Ѵ�.
	*/
	bool operator==(ItemType item);

	/**
	*	@brief	��� ������ �����ε� <<
	*	@pre	ItemType�� ������ ȣ���Ѵ�.
	*	@post	ȣ���� ItemType�� ������ ����Ѵ�.
	*	@param	item	ItemType�� ����.
	*/
	void operator<<(ItemType item);
	

protected:
	int m_Id;				///< ��ǰ ID.
	string m_sName;			///< ��ǰ��.
	string m_sManufacturer;	///< ��������.
};

#endif	// _ITEMTYPE_H
