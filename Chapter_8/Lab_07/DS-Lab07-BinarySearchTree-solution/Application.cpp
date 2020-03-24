#include "Application.h"

// Application 실행 함수
void Application::Run()
{
	while (1)
	{
		command = GetCommand();

		switch (command)
		{
		case 1: 
			InsertItem();
			break;
		case 2:
			RemoveItem();
			break;
		case 3:
			DisplayItem();
			break;
		case 4:
			SearchItem();
			break;
		case 0:
			return;
		default:
			cout << "\tIllegal sellection...\n";
			break;
		}
	}
}

// command 값 입력받는 함수
int Application::GetCommand()
{
	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Add Item" << endl;
	cout << "\t   2 : Delete Item" << endl;
	cout << "\t   3 : Display Item" << endl;
	cout << "\t   4 : Search Item" << endl;
	cout << "\t   0 : Quit " << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}

// Tree에 item을 추가하는 함수 
void Application::InsertItem()
{
	ItemType item;
	cout << "Insert Item : " << endl;
	item.SetRecordFromKB();				// Tree에 추가할 item 값을 키보드로부터 입력받음

	Tree.Add(item);						// Add함수를 통해서 item을 Tree에 추가함
	DisplayItem();						// 현재 Tree의 node를 모두 출력함
}

// Tree에서 item을 지우는 함수
void Application::RemoveItem()
{
	ItemType item;
	cout << "Input Id to delete item : " << endl;
	item.SetIdFromKB();					// Tree에서 지우려고 하는 item 값을 키보드로부터 입력받음

	bool found;							// 검색여부에 따른 결과를 저장할 found
	Tree.RetrieveItem(item, found);		// RetrieveItem 함수를 통해서 Tree에서 검색

	if (found == true)					// Tree에 item이 있으면
	{
		Tree.DeleteItem(item);			// DeleteItem함수를 통해서 Tree에서 item값에 해당하는 노드를 삭제함
		DisplayItem();					// 지우고 나서의 Tree를 출력
	}
	else
		cout << "No item to delete" << endl;	// 지우려고 하는 값의 node가 없을 경우 
}

// 현재 Tree의 모든 노드를 출력하는 함수
void Application::DisplayItem()
{
	Tree.PrintTree(cout);				// PrintTree함수를 통해서 출력
}

// Tree에서 찾고자 하는 값의 노드를 검색하는 함수
void Application::SearchItem()
{
	ItemType item;
	cout << "Input Id to search item : " << endl;
	item.SetIdFromKB();								// 검색하고자 하는 값(Id)을 키보드로부터 입력받음

	bool found;										// 겁색여부를 저장할 found
	Tree.RetrieveItem(item, found);					// RetrieveItem 함수를 통해 Tree에서 검색
	if (found == true)								// 찾으면 찾았다는 문구와 함께, 관련 정보까지 출력
	{
		cout << "Target item exists in the list." << endl;
		item.DisplayRecordOnScreen();
	}
	else
		cout << "Target item is not in the list." << endl;		// 못 찾았으면 못 찾았다는 문구를 출력
}