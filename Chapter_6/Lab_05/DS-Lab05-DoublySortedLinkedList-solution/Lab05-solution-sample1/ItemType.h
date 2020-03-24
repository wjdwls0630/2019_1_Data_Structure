#pragma once
#ifndef _ITEMTYPE_H
#define _ITEMTYPE_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;


/**
*	두 아이템 사이의 관계에 대한 열거형 선언
*/
enum RelationType {LESS, GREATER, EQUAL};


/**
*	아이템의 정보를 담고 있는 클래스
*/
class ItemType
{
public:
	/**
	*	디폴트 생성자
	*/
	ItemType()
	{
		m_Id = -1;
		m_sName = "";
		m_sManufacturer = "";
	}

	/**
	*	생성자
	*/
	ItemType(int Id)
	{
		m_Id = Id;
		m_sName = "";
		m_sManufacturer = "";
	}

	/**
	*	소멸자
	*/
	~ItemType()	{}

	/**
	*	@brief	아이템의 ID를 가져온다.
	*	@pre	아이템의 ID를 설정한다.
	*	@post	없음.
	*	@return	아이템의 ID.
	*/
	int GetId()
	{
		return m_Id;
	}

	/**
	*	@brief	아이템의 이름을 가져온다.
	*	@pre	아이템의 이름을 설정한다.
	*	@post	없음.
	*	@return	아이템의 이름.
	*/
	string GetName()
	{
		return m_sName;
	}

	/**
	*	@brief	제조자의 이름을 가져온다.
	*	@pre	제조자의 이름을 설정한다.
	*	@post	없음.
	*	@return	제조자의 이름.
	*/
	string GetManufacturer()
	{
		return m_sManufacturer;
	}

	/**
	*	@brief	아이템의 ID를 설정한다.
	*	@pre	없음.
	*	@post	아이템의 ID를 설정한다.
	*	@param	inId	아이템의 ID.
	*/
	void SetId(int inId)
	{
		m_Id = inId;
	}
	
	/**
	*	@brief	아이템의 이름을 설정한다.
	*	@pre	없음.
	*	@post	아이템의 이름을 설정한다.
	*	@param	inName	아이템의 이름.
	*/
	void SetName(string inName)
	{
		m_sName = inName;
	}
	
	/**
	*	@brief	제조자의 이름을 설정한다.
	*	@pre	없음.
	*	@post	제조자의 이름을 설정한다.
	*	@param	inManufacturer	제조자의 이름.
	*/
	void SetManufacturer(string inManufacturer)
	{
		m_sManufacturer = inManufacturer;
	}
	
	/**
	*	@brief	아이템의 레코드를 설정한다.
	*	@pre	없음.
	*	@post	아이템의 레코드를 설정한다.
	*	@param	inId	아이템의 ID.
	*	@param	inName	아이템의 이름.
	*	@param	inManufacturer	제조자의 이름.
	*/
	void SetRecord(int inId, string inName, string inManufacturer)
	{
		SetId(inId);
		SetName(inName);
		SetManufacturer(inManufacturer);
	}

	/**
	*	@brief	아이템의 ID를 스크린에 출력한다.
	*	@pre	아이템의 ID를 설정한다.
	*	@post	아이템의 ID를 출력한다.
	*/
	void DisplayIdOnScreen() 
	{
		cout << "\tID   : " << m_Id << endl; 
	};

	/**
	*	@brief	아이템의 이름을 스크린에 출력한다.
	*	@pre	아이템의 이름을 설정한다.
	*	@post	아이템의 이름을 출력한다.
	*/
	void DisplayNameOnScreen() 
	{
		cout << "\tName : " << m_sName << endl; 
	};

	/**
	*	@brief	제조자의 이름을 스크린에 출력한다.
	*	@pre	제조자의 이름을 설정한다.
	*	@post	제조자의 이름을 출력한다.
	*/
	void DisplayManufacturerOnScreen() 
	{
		cout << "\tManufacturer : " << m_sManufacturer << endl; 
	};

	/**
	*	@brief	아이템의 모든 정보를 스크린에 출력한다.
	*	@pre	아이템의 모든 정보를 설정한다.
	*	@post	아이템의 모든 정보를 출력한다.
	*/
	void DisplayRecordOnScreen()
	{
		DisplayIdOnScreen();
		DisplayNameOnScreen();
		DisplayManufacturerOnScreen();
	};

	/**
	*	@brief	키보드로부터 아이템의 ID를 입력받는다.
	*	@pre	없음.
	*	@post	아이템의 ID를 설정한다.
	*/
	void SetIdFromKB();

	/**
	*	@brief	키보드로부터 아이템의 이름을 입력받는다.
	*	@pre	없음.
	*	@post	아이템의 이름을 설정한다.
	*/
	void SetNameFromKB();

	/**
	*	@brief	키보드로부터 제조자의 이름을 입력받는다.
	*	@pre	없음.
	*	@post	제조자의 이름을 설정한다.
	*/
	void SetManufacturerFromKB();
	
	/**
	*	@brief	키보드로부터 아이템의 모든 정보를 입력받는다.
	*	@pre	없음.
	*	@post	아이템의 모든 정보를 설정한다.
	*/
	void SetRecordFromKB();

	/**
	*	@brief	파일로부터 아이템의 모든 정보를 읽어온다.
	*	@pre	정해진 파일을 연다.
	*	@post	아이템의 모든 정보를 설정한다.
	*	@param	fin		파일 디스크립터.
	*	@return	함수가 잘 작동하면 1을 리턴하고, 그렇지 않으면 0을 리턴한다.
	*/
	int ReadDataFromFile(ifstream& fin);

	/**
	*	@brief	파일에 아이템의 모든 정보를 쓴다.
	*	@pre	정해진 파일을 열고, 리스트를 초기화한다.
	*	@post	정해진 파일에 새로운 아이템들을 설정한다.
	*	@param	fout	파일 디스크립터.
	*	@return	함수가 잘 작동하면 1을 리턴하고, 그렇지 않으면 0을 리턴한다.
	*/
	int WriteDataToFile(ofstream& fout);
	
	/**
	*	두 아이템을 비교한다.
	*	@brief	아이템의 ID로 두 아이템을 비교한다.
	*	@pre	두 아이템들은 초기화되어야한다.
	*	@post	두 아이템을 비교하여 결과를 리턴한다.
	*	@param	data	비교하기 위한 변수.
	*	@return	this.id < data.id일 때 LESS를 리턴, 
	*			if this.id > data.id일 때 GREATER를 리턴,
	*			그렇지 않을 때 EQUAL을 리턴.
	*/
	RelationType CompareByID(const ItemType &data);
	
	/**
	*	@brief	'<'를 재정의한다.
	*	@pre	기존 '<'으로 정의 되어있다.
	*	@post	'<' 재정의 된 것으로 사용할 수 있다.
	*	@return	해당 케이스면 TRUE, 그렇지 않으면 FALSE.
	*/
	bool ItemType::operator < (ItemType &data)
	{
		if(this -> GetId() < data.m_Id)
			return true;
		else
			return false;
	}

	/**
	*	@brief	'>'를 재정의한다.
	*	@pre	기존 '>'으로 정의 되어있다.
	*	@post	'>' 재정의 된 것으로 사용할 수 있다.
	*	@return	해당 케이스면 TRUE, 그렇지 않으면 FALSE.
	*/
	bool ItemType::operator > (ItemType &data)
	{
		if(this -> GetId() > data.m_Id)
			return true;
		else
			return false;
	}

	/**
	*	@brief	'=='를 재정의한다.
	*	@pre	기존 '=='으로 정의 되어있다.
	*	@post	'==' 재정의 된 것으로 사용할 수 있다.
	*	@return	해당 케이스면 TRUE, 그렇지 않으면 FALSE.
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
	*	@brief	'='를 재정의한다.
	*	@pre	기존 '='으로 정의 되어있다.
	*	@post	'=' 재정의 된 것으로 사용할 수 있다.
	*	@return	해당 케이스면 TRUE, 그렇지 않으면 FALSE.
	*/
	ItemType& operator=(ItemType& data)
	{
		this -> SetName(data.GetName());
		this -> SetId(data.GetId());
		this -> SetManufacturer(data.GetManufacturer());
		return *this;
	}

	/**
	*	@brief	'>>'를 재정의한다.
	*	@pre	기존 '>>'으로 정의 되어있다.
	*	@post	'>>' 재정의 된 것으로 사용할 수 있다.
	*	@return	해당 케이스면 TRUE, 그렇지 않으면 FALSE.
	*/
	friend istream& operator >> (istream& os, ItemType& data)
	{
		os >> data.m_Id >> data.m_sName >> data.m_sManufacturer;
		return os;
	}

protected:
	int m_Id;				///< 아이템의 ID.
	string m_sName;			///< 아이템의 이름.
	string m_sManufacturer;	///< 제조자의 이름.
};

#endif  // _ITEMTYPE_H
