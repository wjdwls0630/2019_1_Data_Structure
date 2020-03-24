#include "Application.h"


// 프로그램 구동.
void Application::Run()
{
	WhatHeap();

	while(1)
	{
		m_nCurCommand = GetCommand();

		switch(m_nCurCommand)
		{
		case 1:		// 추가
			AddItem();
			break;
		case 2:		// 삭제
			DeleteItem();
			break;
		case 3:		// 삭제
			DequeueItem();
			break;
		case 4:		// 출력
			DisplayItem();
			break;
		case 5:		// 검색
			SearchItem();
			break;
		case 0:		// 종료
			return;
		default:	// 그 외
			cout << "\tIllegal sellection...\n";
			break;
		}
	}	
}


// MaxHeap와 MinHeap 둘 중 하나를 선택하는 함수.
void Application::WhatHeap()
{
	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Max Heap" << endl;
	cout << "\t   2 : Min Heap" << endl;
	cout << "\t   0 : Quit " << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	switch(command)
		{
		case 1:		// Max Heap
			m_List = new CMaxHeap<ItemType>(10);
			break;
		case 2:		// Min Heap
			m_List = new CMinHeap<ItemType>(10);
			break;
		case 0:		// 종료
			return;
		default:	// 그 외
			cout << "\tIllegal sellection...\n";
			break;
		}

}


// 화면에 메뉴가 뜨고 키보드로 입력하는 함수.
int Application::GetCommand()
{
	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Add item" << endl;
	cout << "\t   2 : Delete item" << endl;
	cout << "\t   3 : Dequeue item" << endl;
	cout << "\t   4 : Display item" << endl;
	cout << "\t   5 : Search item" << endl;
	cout << "\t   0 : Quit " << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}

// Heap에 새 제품정보를 추가하기 위한 함수.
int Application::AddItem()
{
	ItemType item;

	item.SetRecordFromKB(); // 제품정보 입력

	if(!m_List->IsFull()) // Heap가 Full인지 아닌지 검사
	{
		m_List->Add(item); // 제품정보 추가
		return 1;
	}
	else
		cout << "\tFull!!!" << endl;

	return 1;
}


// Heap에서 제품정보를 삭제하기 위한 함수.
int Application::DeleteItem()
{	
	ItemType item;
	
	if(!m_List->IsEmpty()) // Heap가 Empty인지 아닌지 검사
	{
		item.SetIdFromKB(); // 삭제할 제품ID 입력

		if(!m_List->Delete(item)) // 제품정보 삭제
			cout << "\n\tNo Data" << endl; 
	}
	else
		cout << "\tEmpty!!!" << endl;

	return 1;
}


// Heap에서 첫번째 제품정보를 삭제하기 위한 함수.
int Application::DequeueItem()
{		
	if(!m_List->IsEmpty()) // Heap가 Empty인지 아닌지 검사
	{
		m_List->Dequeue(); // 첫번째 제품정보 삭제
	}
	else
	{
		cout << "\tEmpty!!!" << endl;
	}
	return 1;
}


// Heap에 있는 제품정보를 출력하기 위한 함수.
void Application::DisplayItem()
{
	if(!m_List->IsEmpty()) // Heap가 Empty인지 아닌지 검사
	{
		m_List->PrintHeap(); // 제품정보 출력
	}
	else
		cout << "\tEmpty!!!" << endl;
}


// Heap에서 제품정보를 검색하기 위한 함수.
int Application::SearchItem()
{
	ItemType item;
	bool found = false;
	
	if(!m_List->IsEmpty()) // Heap가 Empty인지 아닌지 검사
	{
		item.SetIdFromKB(); // 검색할 제품ID 입력

		m_List->RetrieveItem(item, found); // 제품정보 검색

		// Heap에서 제품을 찾았는지 못찾았는지 판단
		if(found)
		{
			cout << "\n\tFound!!" << endl;
			item.DisplayRecordOnScreen(); // 검색한 제품정보 출력
		}
		else
			cout << "\n\tNo Data" << endl;
	}
	else
	{
		cout << "\tEmpty!!!" << endl;
	}

	return 1;
}
