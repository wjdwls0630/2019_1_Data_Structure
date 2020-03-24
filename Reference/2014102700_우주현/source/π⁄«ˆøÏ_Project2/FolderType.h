#pragma once

#include <iostream>
#include <string>
#include <ctime>
#include <time.h>

#include "Queue.h"
#include "DoublyLinkedList.h"
#include "ArraryList.h"
#include "ItemType.h"

template<typename T>
class DoublyLinkedList;

template<typename T>
class ArrayList;

using namespace std;

class FolderType
{
protected:
	string m_fdName; //폴더 이름
	string m_fdPath; //폴더 경로
	string m_fdCreatTime; //폴더 생성시간
	int m_fdNum; //폴더 개수
	int m_ItNum; //아이템리스트 개수
	ArrayList<FolderType>* m_fdList; //폴더리스트
	DoublyLinkedList<ItemType>* m_itList; //아이템 리스트

public:
	/**
	*	생성자 초기화
	*/
	FolderType()
	{
		m_fdName = ""; //폴더 이름 default 공백
		m_fdPath = "";  //폴더 경로 default 공백
		m_fdCreatTime = "";  //폴더 생성시간 default 공백
		m_fdNum = 0; //폴더리스트 숫자
		m_ItNum = 0; //아이템리스트 숫자
		m_fdList = NULL;
		m_itList = NULL;
	}

	/**
	*	소멸자.
	*/
	~FolderType()
	{
	}

	RelationType CompareByName(const FolderType& data);

	/**
	*	@brief	폴더 이름을 불러오기
	*	@pre	폴더 이름을 입력받음
	*	@post	없음.
	*	@return	폴더 이름.
	*/
	string GetName()
	{
		return m_fdName;
	}

	/**
	*	@brief	폴더 경로를 불러오기
	*	@pre	폴더 경로를 입력받음
	*	@post	없음.
	*	@return	폴더 경로.
	*/
	string GetPath()
	{
		return m_fdPath;
	}

	/**
	*	@brief	폴더 생성시간을 불러오기
	*	@pre	폴더 생성시간을 입력받음
	*	@post	없음.
	*	@return	폴더 생성시간.
	*/
	string GetCreatTime()
	{
		return m_fdCreatTime;
	}

	/**
	*	@brief	서브폴더 개수를 불러오기
	*	@pre	서브폴더 개수를 입력받음
	*	@post	없음.
	*	@return	서브폴더 개수.
	*/
	int GetSubFolderNum()
	{
		return m_fdNum;
	}

	/**
*	@brief	폴더 내 아이템 개수 가져오기
*	@pre	폴더 내 아이템이 존재해야함
*	@post	없음.
*	@return	폴더 내 아이템 개수.
*/
	int GetSubItNum() {
		this->m_ItNum = m_itList->GetLength();
	};

	/**
	*	@brief	현재시간을 불러오기
	*	@pre	없음.
	*	@post	없음.
	*	@return	현재시간을 불러옴.
	*/
	string GetCurTime()
	{
		time_t curr_time;
		struct tm* curr_tm;
		curr_time = time(NULL);
		curr_tm = localtime(&curr_time);

		string year = to_string(curr_tm->tm_year + 1900) + "년 ";
		string month = to_string(curr_tm->tm_mon + 1) + "월 ";
		string day = to_string(curr_tm->tm_mday) + "일 / ";
		string hour = to_string(curr_tm->tm_hour) + "시 ";
		string minute = to_string(curr_tm->tm_min) + "분 ";
		string second = to_string(curr_tm->tm_sec) + "초 ";
		string curTime = year + month + day + hour + minute + second;

		return curTime;
	}

	/**
	*	@brief	폴더 이름을 설정
	*	@pre	없음.
	*	@post	폴더 이름이 입력됨.
	*	@param	inName	폴더 이름.
	*/
	void SetName(string name)
	{
		m_fdName = name;
	}

	ArrayList<FolderType>* GetFdList()
	{
		return m_fdList;
	}
	/**
	*	@brief 입력된 정보로 폴더의 경로를 설정
	*	@pre	폴더이름을 입력받음
	*	@post	입력받은 이름으로 폴더 경로 설정
	*	@return	없음
	*/
	void SetPath(string path)
	{
		m_fdPath = path;
	}

	/**
	*	@brief	폴더 생성시간을 만드는 함수
	*	@pre	없음
	*	@post	변수에 폴더 생성시간이 입력됨
	*	@return	없음
	*/
	void SetCreatTime(string creatTime)
	{
		m_fdCreatTime = creatTime;
	}

	/**
	*	@brief	폴더의 속성을 화면에 표시.
	*	@pre	폴더 속성이 입력됨.
	*	@post	현재 폴더의 속성이 표시됨.
	*/
	void DisplayRecordOnScreen()
	{
		cout << "\tName   : " << m_fdName << endl;
		cout << "\tPath   : " << m_fdPath << endl;
		cout << "\tCreatTime   : " << m_fdCreatTime << endl;
		cout << "\tSubFolderNum   : " << m_fdNum << endl;
		cout << "\n";
	}

	/**
	*	@brief	키보드로 폴더 이름을 입력받음.
	*	@pre	없음.
	*	@post	폴더 이름이 설정됨.
	*/
	void SetNameFromKB();

	/**
	*	@brief	키보드로 폴더 속성을 입력받음.
	*	@pre	없음.
	*	@post	폴더 속성이 설정됨.
	*/
	void SetRecordFromKB();

	/**
	*	@brief 입력된 정보로 리스트에서 폴더정보를 찾아 갱신
	*	@pre	id를 입력받음
	*	@post	갱신하고 싶은 정보를 갱신
	*	@return	없음
	*/
	void ReplaceFolder();


	/**
	*	두 데이터를 비교.
	*	@brief	이름 통해서 두 폴더를 비교.
	*	@pre	두 폴더정보는 초기화 되어야한다.
	*	@post	새로운 폴더정보를 포함하고 있어야함.
	*	@param	data	비교를 위한 폴더정보.
	*	@return	if this.id < data.id면 LESS를 return
	*			if this.id > data.id면 return GREATER ,
	*			그렇지않으면 return EQUAL.
	*/

	/**
	*	@brief	새로운 폴더를 생성하는 함수
	*	@return	폴더 생성에 성공하면 1, 그렇지 않다면 0을 리턴.
	*/
	int AddFolder();

	/**
	*	@brief	 폴더를 삭제하는 함수
	*	@return	폴더 삭제에 성공하면 1, 그렇지 않다면 0을 리턴.
	*/
	int DeleteFolder();

	/**
	*	@brief	폴더 이름을 입력받아 해당 이름을 가지고있는 폴더를 search
	*	@pre	폴더가 생성되어 있음
	*	@post	입력받은 이름을 포함하는 폴더들의 속성을 화면에 표시
	*	@return	함수실행에 성공하면 1, 그렇지 않다면 0을 리턴.
	*/

	void OpenFolder();

	int RetrieveFolderByName();

	/**
	*	@brief	현재 위치에서 모든 서브폴더의 속성 출력
	*	@pre	폴더가 생성되어 있음
	*	@post	현재 위치의 서브폴더들의 속성을 화면에 출력
	*	@return	없음
	*/
	void DisplayAllFolderName();

	FolderType& operator= (const FolderType & data)
	{
		this->m_fdName = data.m_fdName;
		this->m_fdPath = data.m_fdPath;
		this->m_fdCreatTime = data.m_fdCreatTime;
		this->m_fdNum = data.m_fdNum;
		this->m_ItNum = data.m_ItNum;

		if (m_fdNum != 0)
		{
			this->m_fdList = data.m_fdList;
		}

		return *this;
	}

	bool operator == (FolderType & data)
	{
		if (this->GetPath() == data.m_fdPath || this->GetName() == data.m_fdName || this->GetCreatTime() == data.m_fdCreatTime)
		{
			return true;
		}
		else
			return false;
	}

	bool operator < (FolderType & data)
	{
		if (this->GetName() < data.m_fdName)
			return true;
		else
			return false;
	}
};