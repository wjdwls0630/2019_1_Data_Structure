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
	*	@brief  학번을통한 비교로 연산자 오버로딩		
	*	@pre	none.
	*	@post	none.
	*	@return	연산자에 맞는 true, false 값
	*/
	bool operator <(const ItemType& a)
	{
		if( this->student_id < a.student_id )
			return true;
		else
			return false;
	}
	/**
	*	@brief  학번을통한 비교로 연산자 오버로딩		
	*	@pre	none.
	*	@post	none.
	*	@return	연산자에 맞는 true, false 값
	*/
	bool operator >(const ItemType& a)
	{
		if( this->student_id > a.student_id )
			return true;
		else
			return false;
	}
	/**
	*	@brief  학번을통한 비교로 연산자 오버로딩		
	*	@pre	none.
	*	@post	none.
	*	@return	연산자에 맞는 true, false 값
	*/
	bool operator!=(const ItemType& a)
	{
		if(this->student_id!=a.student_id)
			return true;
		else
			return false;
	}
	/**
	*	@brief  학번을통한 비교로 연산자 오버로딩		
	*	@pre	none.
	*	@post	none.
	*	@return	연산자에 맞는 true, false 값
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

