#ifndef _APPLICATION_H
#define _APPLICATION_H

#include <iostream>
#include <fstream>
#include <string>
using namespace std;

#include "DoublySortedLinkedList.h"


#define FILENAMESIZE 1024

/**
*	아이템을 관리하기 위한 Application 클래스.
*/
class Application
{
public:
	/**
	*	디폴트 생성자.
	*/
	Application()
	{
		m_Command = 0;
	}
	
	/**
	*	소멸자.
	*/
	~Application()	{}

	/**
	*	@brief	프로그램을 실행한다.
	*	@pre	프로그램이 시작한다.
	*	@post	프로그램이 끝난다.
	*/
	void Run();

	/**
	*	@brief	command를 스크린에 출력하고 키보드로부터 command를 입력받는다.
	*	@pre	없음.
	*	@post	없음.
	*	@return	유저의 command.
	*/
	int GetCommand();

	/**
	*	@brief	새로운 아이템의 정보를 리스트에 추가한다.
	*	@pre	리스트는 초기화되어야 한다.
	*	@post	리스트에 새 아이템의 정보가 추가된다.
	*	@return	함수가 잘 작동하면 1을 리턴하고, 그렇지 않으면 0을 리턴한다.
	*/
	int AddItem();

	/**
	*	@brief	리스트의 모든 아이템 정보들을 스크린에 출력한다.
	*	@pre	없음.
	*	@post	없음.
	*/
	void DisplayAllItem();

	/**
	*	@brief	정보를 불러올 파일을 파일 디스크립트를 이용해 연다.
	*	@pre	정보를 불러올 파일이 존재해야한다.
	*	@post	읽기 위한 파일을 연다.
	*	@param	fileName	정보를 불러오기 위해 여는 파일의 이름.
	*	@return	함수가 잘 작동하면 1을 리턴하고, 그렇지 않으면 0을 리턴한다.
	*/
	int OpenInFile(char *fileName);

	/**
	*	@brief	정보를 저장할 파일을 파일 디스크립트를 이용해 연다.
	*	@pre	리스트가 초기화되어있어야 한다.
	*	@post	쓰기 위한 파일을 연다.
	*	@param	fileName	정보를 쓰기 위해 여는 파일의 이름.
	*	@return	함수가 잘 작동하면 1을 리턴하고, 그렇지 않으면 0을 리턴한다.
	*/
	int OpenOutFile(char *fileName);

	/**
	*	@brief	읽기 위한 파일을 열어 파일에 있는 모든 데이터를 불러오고 데이터들로 리스트를 만든다.
	*	@pre	파일이 열려있지 않다.
	*	@post	리스트에 파일의 모든 아이템 정보들을 넣는다.
	*	@return	함수가 잘 작동하면 1을 리턴하고, 그렇지 않으면 0을 리턴한다.
	*/
	int ReadDataFromFile();

	/**
	*	@brief	O쓰기 위한 파일을 열어 리스트의 모든 정보들을 저장한다.
	*	@pre	파일이 열려있지 않다.
	*	@post	저장하는 파일에 리스트가 저장된다.
	*	@return	함수가 잘 작동하면 1을 리턴하고, 그렇지 않으면 0을 리턴한다.
	*/
	int WriteDataToFile();

	/**
	*	@brief	입력받은 ID로 아이템 정보를 찾아내어 스크린에 출력한다.
	*	@pre	리스트에 아이템들의 정보가 저장되어 있다.
	*	@post	리스트에서 아이템을 찾아 출력한다.
	*	@return	함수가 잘 작동하면 1을 리턴하고, 그렇지 않으면 0을 리턴한다.
	*/
	int SearchItembyID();

	/**
	*	@brief	리스트를 비운다.
	*	@pre	리스트에 아이템들의 정보가 저장되어 있다.
	*	@post	리스트가 비워진다.
	*/
	void MakeEmptyList();
	
	/**
	*	@brief	입력받은 ID로 아이템을 찾아내어 삭제한다.
	*	@pre	리스트에 아이템들의 정보가 저장되어 있다.
	*	@post	리스트에서 아이템을 찾아 삭제한다.
	*	@return	함수가 잘 작동하면 1을 리턴하고, 그렇지 않으면 0을 리턴한다.
	*/
	int DeleteItem();
	
	/**
	*	@brief	입력받은 ID로 아이템 정보를 찾아내어 수정한다.
	*	@pre	리스트에 아이템들의 정보가 저장되어 있다.
	*	@post	리스트에서 아이템을 찾아 정보를 수정한다.
	*	@return	함수가 잘 작동하면 1을 리턴하고, 그렇지 않으면 0을 리턴한다.
	*/
	int UpdateInfo();

	/**
	*	@brief	이름을 입력받아 그 정보를 반환한다.
	*	@pre	없음.
	*	@post	이름을 입력받은 정보가 반환된다.
	*	@return	입력된 이름의 객체를 반환한다.
	*/
	ItemType RetreiveRecordByName();

	/**
	*	@brief	이름을 입력받아 같은 이름을 가지느 모든 아이템들을 출력한다.
	*	@pre	이름을 입력받는다.
	*	@post	리스트에서 같은 이름을 가진 모든 아이템들이 출력된다.
	*/
	void SearchByName(ItemType target);


private:
	ifstream m_InFile;		///< 입력 파일 디스크립터.
	ofstream m_OutFile;		///< 출력 파일 디스크립터.
	DoublySortedLinkedList<ItemType>m_List; ///< 아이템 리스트.
	int m_Command;			///< 현재 command 숫자.
};

#endif	// _APPLICATION_H