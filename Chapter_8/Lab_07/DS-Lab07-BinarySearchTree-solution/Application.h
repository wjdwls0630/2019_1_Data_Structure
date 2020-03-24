#pragma once
#ifndef APPLICATION_H
#define APPLICATION_H

#include "BinarySearchTree.h"
#include <iostream>
using namespace std;

class Application
{
public:
	// 생성자
	Application() 
	{
		command = 0;
	}
	// 소멸자
	~Application(){}

	// Application 실행 함수
	void Run();
	
	/**
	*	@brief	command 번호를 입력받음
	*	@pre	none
	*	@post	command 값이 저장됨
	*	@return command 값을 리턴함
	*/
	int GetCommand();

	/**
	*	@brief	Tree에 item을 추가
	*	@pre	none
	*	@post	Tree에 item이 추가됨
	*/
	void InsertItem();

	/**
	*	@brief	Tree에서 item을 지움
	*	@pre	none
	*	@post	Tree에서 item이 지워짐
	*/
	void RemoveItem();

	/**
	*	@brief	Tree의 모든 item을 출력함
	*	@pre	none
	*	@post	Tree의 모든 노드들이 출력됨
	*/
	void DisplayItem();

	/**
	*	@brief	Tree에서 item이 있는지 검색함
	*	@pre	none
	*	@post	Tree에 있으면 관련 정보도 같이 출력, 없으면 없다는 문구 출력
	*/
	void SearchItem();

private:
	BinarySearchTree<ItemType> Tree;		// BinarySearchTree 객체
	int command;							// command

};
#endif