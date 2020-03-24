#pragma once
#ifndef _APPLICATION_H
#define _APPLICATION_H

#include "ArraryList.h"
#include "FolderType.h"
#include "Queue.h"
#include "ItemType.h"
#include "DoublyLinkedList.h"

class Application
{
private:
	FolderType m_RootFolder;		///< item list.criptor.
	FolderType* m_curFolder;		///< item list.
	FolderType m_iterator;
	ItemType* m_curItem;
	int m_Command;			///< current command number.
	Queue<FolderType*> m_RecentlyFolder;
public:
	Application()
	{
		m_Command = 0;

		m_RootFolder.SetName("root");
		m_RootFolder.SetPath("/root");
		m_RootFolder.SetCreatTime(m_RootFolder.GetCurTime());
		m_RootFolder.GetSubFolderNum();
		m_curFolder = &m_RootFolder;
		// m_curFile = &m_

	}

	~Application() {}
	/**
	*	@brief	프로그램 driver.
	*	@pre	프로그램이 시작됨.
	*	@post	프로그램이 종료됨.
	*/
	void Run();

	/**
	*	@brief	명령어를 화면에 출력하고 명령어를 키보드로부터 입력받는다.
	*	@pre	없음.
	*	@post	없음.
	*	@return	사용자의 명령어 return.
	*/
	int GetCommand();

	/** @1: 새 폴더 생성
	*	@brief	새로운 폴더를 list에 추가.
	*	@pre	list는 초기화되어야 한다.
	*	@post	새로운 폴더가 list에 추가됨.
	*	@return	함수가 잘 작동하면 1을 return, 그렇지않으면 0을 return
	*/
	int NewFolder();

	/** @2: 이름으로 폴더 검색
	*	@brief	사용자로부터 입력받은 이름으로 폴더를 검색함
	*	@pre	iterator가 리스트 맨 처음에서 시작.
	*	@post	iterator가 리스트 맨 끝 방향으로 이동.
	*	@return	함수가 잘 작동하면 1을 return, 그렇지않으면 메세지 출력과 함께 0을 return
	*/
	int RetrieveFolderByName();

	/** @3: 폴더 삭제
	*	@brief	폴더이름을 정보를 입력받아 리스트에서 삭제
	*	@pre	list는 초기화되어야 한다.
	*	@post	지우고자 하는 폴더가 list에서 삭제됨.
	*/
	int DeleteFolder();

	/** @4: 폴더 열기
	*	@brief	폴더이름을 입력받아 서브폴더를 검색
	*	@pre	list는 초기화되어야 한다 & Queue 준비
	*	@post	검색하고자하는 서브폴더가 list에서 출력됨 & Queue에 기록
	*/
	void OpenFolder();

	/** @5: 폴더 이름 변경하기
	*	@brief 입력된 정보로 리스트에서 폴더정보를 찾아 이름갱신
	*	@pre	id를 입력받음
	*	@post	갱신하고 싶은 정보를 갱신
	*	@return	없음
	*/

	void ReplaceFolder();

	/** @6 : 현재 폴더 속성
 :	*	@brief	폴더 이름을 입력받아 리스트에서 찾아서 속성 출력
	*	@pre	list는 초기화되어야 한다.
	*	@post	표시하고 싶은 폴더속성이 화면에 출력됨.
	*/
	void DisplayProperty();

	/** @7 : 최근 연 폴더 목록
	*	@brief	최근 열어본 폴더목록을 화면에 표시
	*	@pre	Queue안에 최근에 열어본 폴더 이름이 입력됨
	*	@post	최근 열어본 폴더 목록들이 화면에 출력됨.
	*/
	void RecentlyFolder();

	/** @8 : 하위 폴더로 이동
	*	@brief	상위폴더로 이동하는 함수
	*	@pre	이동한 폴더들이 Stack에 쌓인다
	*	@post	상위폴더로 이동한다.
	*/
	void MoveBack();

	/** @9 : 상위 폴더로 이동
	*	@brief	서브폴더로 이동하는 함수
	*	@pre	서브폴더가 존재함
	*	@post	서브폴더로 이동한다.
	*/
	void MoveTo();

	/** @10 : 새로운 자료 생성
	*	@brief	새로운 자료를 Itemlist에 추가.
	*	@pre	list는 초기화되어야 한다.
	*	@post	새로운 파일이 list에 추가됨.
	*	@return	함수가 잘 작동하면 1을 return, 그렇지않으면 0을 return
	*/
	int NewItem();

	/** @11: 이름으로 자료 검색
	*	@brief	사용자로부터 입력받은 이름으로 자료를 검색함
	*	@pre	iterator가 리스트 맨 처음에서 시작.
	*	@post	iterator가 리스트 맨 끝 방향으로 이동.
	*	@return	함수가 잘 작동하면 1을 return, 그렇지않으면 메세지 출력과 함께 0을 return
	*/
	int RetrieveItemByName();

	/** @12 : 자료 삭제
	*	@brief	파일이름을 정보를 입력받아 파일리스트에서 삭제
	*	@pre	list는 초기화되어야 한다.
	*	@post	지우고자 하는 파일 list에서 삭제됨.
	*/
	int DeleteItem();

	/** @13 : 자료 열기
	*	@brief	파일이름을 정보를 입력받아 파일을 연다
	*	@pre	list는 초기화되어야 한다.
	*	@post	파일내용이 화면에 출력됨.
	*/
	void OpenItem();

	/** @14 : 자료 이름 변경
	*	@brief 입력된 정보로 리스트에서 파일정보를 찾아 갱신
	*	@pre	id를 입력받음
	*	@post	갱신하고 싶은 정보를 갱신
	*	@return	없음
	*/
	void ReplaceItem();
};
#endif // !_APPLICATION_H
