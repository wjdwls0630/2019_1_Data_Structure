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
	string m_fdName; //���� �̸�
	string m_fdPath; //���� ���
	string m_fdCreatTime; //���� �����ð�
	int m_fdNum; //���� ����
	int m_ItNum; //�����۸���Ʈ ����
	ArrayList<FolderType>* m_fdList; //��������Ʈ
	DoublyLinkedList<ItemType>* m_itList; //������ ����Ʈ

public:
	/**
	*	������ �ʱ�ȭ
	*/
	FolderType()
	{
		m_fdName = ""; //���� �̸� default ����
		m_fdPath = "";  //���� ��� default ����
		m_fdCreatTime = "";  //���� �����ð� default ����
		m_fdNum = 0; //��������Ʈ ����
		m_ItNum = 0; //�����۸���Ʈ ����
		m_fdList = NULL;
		m_itList = NULL;
	}

	/**
	*	�Ҹ���.
	*/
	~FolderType()
	{
	}

	RelationType CompareByName(const FolderType& data);

	/**
	*	@brief	���� �̸��� �ҷ�����
	*	@pre	���� �̸��� �Է¹���
	*	@post	����.
	*	@return	���� �̸�.
	*/
	string GetName()
	{
		return m_fdName;
	}

	/**
	*	@brief	���� ��θ� �ҷ�����
	*	@pre	���� ��θ� �Է¹���
	*	@post	����.
	*	@return	���� ���.
	*/
	string GetPath()
	{
		return m_fdPath;
	}

	/**
	*	@brief	���� �����ð��� �ҷ�����
	*	@pre	���� �����ð��� �Է¹���
	*	@post	����.
	*	@return	���� �����ð�.
	*/
	string GetCreatTime()
	{
		return m_fdCreatTime;
	}

	/**
	*	@brief	�������� ������ �ҷ�����
	*	@pre	�������� ������ �Է¹���
	*	@post	����.
	*	@return	�������� ����.
	*/
	int GetSubFolderNum()
	{
		return m_fdNum;
	}

	/**
*	@brief	���� �� ������ ���� ��������
*	@pre	���� �� �������� �����ؾ���
*	@post	����.
*	@return	���� �� ������ ����.
*/
	int GetSubItNum() {
		this->m_ItNum = m_itList->GetLength();
	};

	/**
	*	@brief	����ð��� �ҷ�����
	*	@pre	����.
	*	@post	����.
	*	@return	����ð��� �ҷ���.
	*/
	string GetCurTime()
	{
		time_t curr_time;
		struct tm* curr_tm;
		curr_time = time(NULL);
		curr_tm = localtime(&curr_time);

		string year = to_string(curr_tm->tm_year + 1900) + "�� ";
		string month = to_string(curr_tm->tm_mon + 1) + "�� ";
		string day = to_string(curr_tm->tm_mday) + "�� / ";
		string hour = to_string(curr_tm->tm_hour) + "�� ";
		string minute = to_string(curr_tm->tm_min) + "�� ";
		string second = to_string(curr_tm->tm_sec) + "�� ";
		string curTime = year + month + day + hour + minute + second;

		return curTime;
	}

	/**
	*	@brief	���� �̸��� ����
	*	@pre	����.
	*	@post	���� �̸��� �Էµ�.
	*	@param	inName	���� �̸�.
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
	*	@brief �Էµ� ������ ������ ��θ� ����
	*	@pre	�����̸��� �Է¹���
	*	@post	�Է¹��� �̸����� ���� ��� ����
	*	@return	����
	*/
	void SetPath(string path)
	{
		m_fdPath = path;
	}

	/**
	*	@brief	���� �����ð��� ����� �Լ�
	*	@pre	����
	*	@post	������ ���� �����ð��� �Էµ�
	*	@return	����
	*/
	void SetCreatTime(string creatTime)
	{
		m_fdCreatTime = creatTime;
	}

	/**
	*	@brief	������ �Ӽ��� ȭ�鿡 ǥ��.
	*	@pre	���� �Ӽ��� �Էµ�.
	*	@post	���� ������ �Ӽ��� ǥ�õ�.
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
	*	@brief	Ű����� ���� �̸��� �Է¹���.
	*	@pre	����.
	*	@post	���� �̸��� ������.
	*/
	void SetNameFromKB();

	/**
	*	@brief	Ű����� ���� �Ӽ��� �Է¹���.
	*	@pre	����.
	*	@post	���� �Ӽ��� ������.
	*/
	void SetRecordFromKB();

	/**
	*	@brief �Էµ� ������ ����Ʈ���� ���������� ã�� ����
	*	@pre	id�� �Է¹���
	*	@post	�����ϰ� ���� ������ ����
	*	@return	����
	*/
	void ReplaceFolder();


	/**
	*	�� �����͸� ��.
	*	@brief	�̸� ���ؼ� �� ������ ��.
	*	@pre	�� ���������� �ʱ�ȭ �Ǿ���Ѵ�.
	*	@post	���ο� ���������� �����ϰ� �־����.
	*	@param	data	�񱳸� ���� ��������.
	*	@return	if this.id < data.id�� LESS�� return
	*			if this.id > data.id�� return GREATER ,
	*			�׷��������� return EQUAL.
	*/

	/**
	*	@brief	���ο� ������ �����ϴ� �Լ�
	*	@return	���� ������ �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	*/
	int AddFolder();

	/**
	*	@brief	 ������ �����ϴ� �Լ�
	*	@return	���� ������ �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	*/
	int DeleteFolder();

	/**
	*	@brief	���� �̸��� �Է¹޾� �ش� �̸��� �������ִ� ������ search
	*	@pre	������ �����Ǿ� ����
	*	@post	�Է¹��� �̸��� �����ϴ� �������� �Ӽ��� ȭ�鿡 ǥ��
	*	@return	�Լ����࿡ �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	*/

	void OpenFolder();

	int RetrieveFolderByName();

	/**
	*	@brief	���� ��ġ���� ��� ���������� �Ӽ� ���
	*	@pre	������ �����Ǿ� ����
	*	@post	���� ��ġ�� ������������ �Ӽ��� ȭ�鿡 ���
	*	@return	����
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