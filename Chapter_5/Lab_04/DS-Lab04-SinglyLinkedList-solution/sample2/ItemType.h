#pragma once
#include <iostream>
#include <string>
using namespace std;
class ItemType
{
public:
	ItemType(void);
	~ItemType(void);
	/**
	*	@brief  �й������� �񱳷� ������ �����ε�		
	*	@pre	none.
	*	@post	none.
	*	@return	�����ڿ� �´� true, false ��
	*/
	bool operator <(const ItemType& a)
	{
		if( this->student_id < a.student_id )
			return true;
		else
			return false;
	}
	/**
	*	@brief  �й������� �񱳷� ������ �����ε�		
	*	@pre	none.
	*	@post	none.
	*	@return	�����ڿ� �´� true, false ��
	*/
	bool operator >(const ItemType& a)
	{
		if( this->student_id > a.student_id )
			return true;
		else
			return false;
	}
	/**
	*	@brief  �й������� �񱳷� ������ �����ε�		
	*	@pre	none.
	*	@post	none.
	*	@return	�����ڿ� �´� true, false ��
	*/
	bool operator!=(const ItemType& a)
	{
		if(this->student_id!=a.student_id)
			return true;
		else
			return false;
	}
	/**
	*	@brief  �й������� �񱳷� ������ �����ε�		
	*	@pre	none.
	*	@post	none.
	*	@return	�����ڿ� �´� true, false ��
	*/
	bool operator==(const ItemType& a)
	{
		if(this->student_id==a.student_id)
			return true;
		else
			return false;
	}
	int get_id();
	string get_name();
	string get_address();
	void set_student_id(int mid);
	void set_student(int mid, string mname, string maddress);
private:
	int student_id;
	string name;
	string address;
};

