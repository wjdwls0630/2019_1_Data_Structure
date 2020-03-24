//typedef char ItemType;

#ifndef _ITEMTYPE_H
#define _ITEMTYPE_H

#include <iostream>
#include <fstream>
#include <string>

using namespace std;


/**
*	2 아이템 사이의 관계 설정
*/
enum RelationType { LESS, GREATER, EQUAL };


/**
*	아이템 정보 클래스
*/
class ItemType
{
public:
	/**
	*	기본 생성자
	*/
	ItemType()
	{
		m_Id = -1;
		m_sName = "";
		m_sAddress = "";
	}

	/**
	*	소멸자.
	*/
	~ItemType() {}

	/**
	*	@brief	학생 ID를 얻는다
	*	@pre	학생 ID를 입력받는다
	*	@post	none
	*	@return	학생 ID를 리턴
	*/
	int GetId() const
	{
		return m_Id;
	}

	/**
	*	@brief	학생 이름을 얻는다
	*	@pre	학생 이름을 입력받는다
	*	@post	none
	*	@return	학생 이름을 리턴
	*/
	string GetName() const
	{
		return m_sName;
	}

	/**
	*	@brief	학생 주소를 얻는다
	*	@pre	학생 주소를 입력받는다
	*	@post	none
	*	@return	학생 주소를 리턴
	*/
	string GetAddress() const
	{
		return m_sAddress;
	}

	/**
	*	@brief	학생 ID를 입력받는다
	*	@pre	none
	*	@post	학생 ID가 입력됨
	*	@param	inId	student id.
	*/
	void SetId(int inId)
	{
		m_Id = inId;
	}

	/**
	*	@brief	학생 이름을 입력받는다
	*	@pre	none
	*	@post	학생 이름이 입력됨
	*	@param	inName	student name.
	*/
	void SetName(string inName)
	{
		m_sName = inName;
	}

	/**
	*	@brief	학생 주소를 입력받는다
	*	@pre	none
	*	@post	학생 주소가 입력됨
	*	@param	inAddress	student address
	*/
	void SetAddress(string inAddress)
	{
		m_sAddress = inAddress;
	}

	/**
	*	@brief	학생 정보(레코드)를 입력
	*	@pre	none
	*	@post	학생 정보가 입력됨
	*	@param	inId	student id
	*	@param	inName	student name
	*	@param	inAddress	student address
	*/
	void SetRecord(int inId, string inName, string inAddress)
	{
		SetId(inId);
		SetName(inName);
		SetAddress(inAddress);
	}

	/**
	*	@brief	학생 ID를 스크린에 출력
	*	@pre	학생 ID가 입력됨
	*	@post	학생 ID가 스크린에 출력됨
	*/
	void DisplayIdOnScreen()
	{
		cout << "\tID   : " << m_Id << endl;
	};

	/**
	*	@brief	학생 이름을 스크린에 출력
	*	@pre	학생 이름이 입력됨
	*	@post	학생 이름이 스크린에 출력됨
	*/
	void DisplayNameOnScreen()
	{
		cout << "\tName : " << m_sName << endl;
	};

	/**
	*	@brief	학생 주소를 스크린에 출력
	*	@pre	학생 주소가 입력됨
	*	@post	학생 주소가 스크린에 출력됨
	*/
	void DisplayAddressOnScreen()
	{
		cout << "\tAddress : " << m_sAddress << endl;
	};

	/**
	*	@brief	학생 정보(레코드)를 스크린에 출력
	*	@pre	학생 정보가 입력됨
	*	@post	학생 정보가 스크린에 출력됨
	*/
	void DisplayRecordOnScreen()
	{
		DisplayIdOnScreen();
		DisplayNameOnScreen();
		DisplayAddressOnScreen();
	};

	/**
	*	@brief	키보드로부터 학생 ID를 입력받음
	*	@pre	none
	*	@post	학생 ID가 입력됨
	*/
	void SetIdFromKB();

	/**
	*	@brief	키보드로부터 학생 이름을 입력받음
	*	@pre	none
	*	@post	학생 이름이 입력됨
	*/
	void SetNameFromKB();

	/**
	*	@brief	키보드로부터 학생 주소를 입력받음
	*	@pre	none
	*	@post	학생 주소가 입력됨
	*/
	void SetAddressFromKB();

	/**
	*	@brief	키보드로부터 학생 정보를 입력받음
	*	@pre	none
	*	@post	학생 정보가 입력됨
	*/
	void SetRecordFromKB();

	/**
	*	@brief	파일에서 레코드를 읽는다
	*	@pre	타겟 파일이 오픈되어있음
	*	@post	학생 정보가 입력됨
	*	@param	fin	file descriptor.
	*	@return	함수가 잘 돌아가면 1을 리턴 아니면 0을 리턴
	*/
	int ReadDataFromFile(ifstream& fin);

	/**
	*	@brief	파일에 정보를 쓴다
	*	@pre	타겟 파일이 오픈되어있음, 리스트가 초기화됨
	*	@post	타겟 파일이 새 학생 정보를 포함함
	*	@param	fout	file descriptor.
	*	@return	함수가 잘 돌아가면 1을 리턴 아니면 0을 리턴
	*/
	int WriteDataToFile(ofstream& fout);

	/**
	*	두 아이템타입을 비교한다
	*	@brief	Item ID로 두 아이템타입을 비교한다
	*	@pre	두 아이템타입이 초기화되어야한다
	*	@post	타겟 파일이 새 학생 정보를 포함함
	*	@param	data	target item for comparing.
	*	@return	현재ID가 DATA의 ID보다 작을 경우 LESS를 리턴,
	*			현재ID가 DATA의 ID보다 클 경우 GREATER를 리턴,
	*			아니면 EQUAL을 리턴
	*/
	RelationType ComparedTo(const ItemType &data);


	// operator overloading
	bool operator == (const ItemType& item)
	{
		if (this->m_Id == item.GetId())
			return 1;
		else
			return 0;
	}

	// operator overloading
	bool operator > (const ItemType& item)
	{
		if (this->m_Id > item.GetId())
			return 1;
		else
			return 0;
	}

	// operator overloading
	bool operator < (const ItemType& item)
	{
		if (this->m_Id < item.GetId())
			return 1;
		else
			return 0;
	}

	// operator overloading
	friend ostream& operator << (ostream& out, ItemType& item)
	{
		out << "ID : " << item.GetId() << endl;
		out << "Name : " << item.GetName() << endl;
		out << "Address : " << item.GetAddress() << endl;

		return out;
	}

protected:
	int m_Id;			///< 학생 ID
	string m_sName;		///< 학생 이름
	string m_sAddress;	///< 학생 주소
};

#endif	// _ITEMTYPE_H
