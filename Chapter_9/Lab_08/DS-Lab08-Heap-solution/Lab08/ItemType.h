#ifndef _ITEMTYPE_H
#define _ITEMTYPE_H

#include <iostream>
#include <string>

using namespace std;


/**
*	제품 정보 클래스.
*	@author	김병우
*	@date	2014.11.20
*/
class ItemType
{
public:
	/**
	*	생성자.
	*/
	ItemType()
	{
		m_Id = -1;
		m_sName = "";
		m_sManufacturer = "";
	}

	/**
	*	소멸자.
	*/
	~ItemType()	{}

	/**
	*	@brief	제품 ID 반환 함수.
	*	@pre	제품 ID가 저장된다.
	*	@post	none.
	*	@return	제품 ID를 반환한다.
	*/
	int GetId()
	{
		return m_Id;
	}

	/**
	*	@brief	제품명 반환 함수.
	*	@pre	제품명이 저장된다.
	*	@post	none.
	*	@return	제품명을 반환한다.
	*/
	string GetName()
	{
		return m_sName;
	}

	/**
	*	@brief	제조업자 반환 함수.
	*	@pre	제조업자가 저장된다.
	*	@post	none.
	*	@return	제조업자를 반환한다.
	*/
	string GetManufacturer()
	{
		return m_sManufacturer;
	}

	/**
	*	@brief	제품 ID 입력 함수.
	*	@pre	none.
	*	@post	제품 ID가 입력된다.
	*	@param	inId	제품 ID.
	*/
	void SetId(int inId)
	{
		m_Id = inId;
	}
	
	/**
	*	@brief	제품명 입력 함수.
	*	@pre	none.
	*	@post	제품명이 입력된다.
	*	@param	inName	제품명.
	*/
	void SetName(string inName)
	{
		m_sName = inName;
	}
	
	/**
	*	@brief	제조업자 입력 함수.
	*	@pre	none.
	*	@post	제조업자가 입력된다.
	*	@param	inManufacturer	제조업자.
	*/
	void SetManufacturer(string inManufacturer)
	{
		m_sManufacturer = inManufacturer;
	}
	
	/**
	*	@brief	제품 정보 입력 함수.
	*	@pre	none.
	*	@post	제품 정보가 입력된다.
	*	@param	inId	제품 ID.
	*	@param	inName	제품명.
	*	@param	inManufacturer	제조업자제.
	*/
	void SetRecord(int inId, string inName, string inManufacturer)
	{
		SetId(inId);
		SetName(inName);
		SetManufacturer(inManufacturer);
	}

	/**
	*	@brief	제품 ID 출력 함수.
	*	@pre	제품 ID가 존재한다.
	*	@post	제품 ID가 출력된다.
	*/
	void DisplayIdOnScreen() 
	{
		cout << "\tID   : " << m_Id << endl; 
	};

	/**
	*	@brief	제품명 출력 함수.
	*	@pre	제품명이 존재한다.
	*	@post	제품명이 출력된다.
	*/
	void DisplayNameOnScreen() 
	{
		cout << "\tName : " << m_sName << endl; 
	};

	/**
	*	@brief	제조업자 출력 함수.
	*	@pre	제조업자가 존재한다.
	*	@post	제조업자가 출력된다.
	*/
	void DisplayManufacturerOnScreen() 
	{
		cout << "\tManufacturer : " << m_sManufacturer << endl; 
	};

	/**
	*	@brief	제품정보 출력 함수.
	*	@pre	제품정보가 존재한다.
	*	@post	제품정보가 출력된다.
	*/
	void DisplayRecordOnScreen()
	{
		DisplayIdOnScreen();
		DisplayNameOnScreen();
		DisplayManufacturerOnScreen();
	};

	/**
	*	@brief	키보드로 ID 입력 함수.
	*	@pre	none.
	*	@post	제품 ID가 저장된다.
	*/
	void SetIdFromKB();

	/**
	*	@brief	키보드로 제품명 입력 함수.
	*	@pre	none.
	*	@post	제품명이 저장된다.
	*/
	void SetNameFromKB();

	/**
	*	@brief	키보드로 제조업자 입력 함수.
	*	@pre	none.
	*	@post	제조업자가 저장된다.
	*/
	void SetManufacturerFromKB();
	
	/**
	*	@brief	키보드로 제품정보 입력 함수.
	*	@pre	none.
	*	@post	제품정보가 저장된다.
	*/
	void SetRecordFromKB();
	
	/**
	*	@brief	크기비교 연산자 오버로딩 <
	*	@pre	두개의 ItemType의 정보를 호출한다.
	*	@post	호출한 ItemType의 ID의 크기를 비교한다.
	*	@param	item	ItemType형 변수.
	*	@return	맞으면 True, 틀리면 False를 반환한다.
	*/
	bool operator<(ItemType item);

	/**
	*	@brief	크기비교 연산자 오버로딩 >
	*	@pre	두개의 ItemType의 정보를 호출한다.
	*	@post	호출한 ItemType의 ID의 크기를 비교한다.
	*	@param	item	ItemType형 변수.
	*	@return	맞으면 True, 틀리면 False를 반환한다.
	*/
	bool operator>(ItemType item);

	/**
	*	@brief	크기비교 연산자 오버로딩 ==
	*	@pre	두개의 ItemType의 정보를 호출한다.
	*	@post	호출한 ItemType의 ID의 크기를 비교한다.
	*	@param	item	ItemType형 변수.
	*	@return	맞으면 True, 틀리면 False를 반환한다.
	*/
	bool operator==(ItemType item);

	/**
	*	@brief	출력 연산자 오버로딩 <<
	*	@pre	ItemType의 정보를 호출한다.
	*	@post	호출한 ItemType의 정보를 출력한다.
	*	@param	item	ItemType형 변수.
	*/
	void operator<<(ItemType item);
	

protected:
	int m_Id;				///< 제품 ID.
	string m_sName;			///< 제품명.
	string m_sManufacturer;	///< 제조업자.
};

#endif	// _ITEMTYPE_H
