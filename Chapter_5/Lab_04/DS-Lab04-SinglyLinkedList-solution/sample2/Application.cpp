#include "Application.h"


// Program driver.
void Application::Run()
{
	while(1)
	{
		m_nCurCommand = GetCommand();

		switch(m_nCurCommand)
		{
		case 1:		// inset item
			InsertItem();
			break;
		case 2:		// inset item
			DeleteItem();
			break;
		case 3:		// inset item
			ReplaceItem();
			break;
		case 4:		// retrieves item
			DisplayAll();
			break;
		case 5:
			RetrieveItem();
			break;
		case 0:	// quit
			return;
		default:
			cout << "\tIllegal sellection...\n";
			break;
		}
	}	
}


// Display command on screen and get a input from keyboard.
int Application::GetCommand()
{
	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Insert Item" << endl;
	cout << "\t   2 : delete Item" << endl;
	cout << "\t   3 : replace Item" << endl;
	cout << "\t   4 : Display all Item" << endl;
	cout << "\t   5 : Retrieve Item" << endl;
	cout << "\t   0 : Quit " << endl;

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}


// Add new record into list.
int Application::InsertItem()
{
	ItemType item;
	int id;
	string name;
	string address;


	cout << "Input Item studnet_id : ";
	cin>>id;
	
	cout << "Input Item studnet_name : ";
	cin>>name;
	
	cout << "Input Item studnet_address : ";
	cin>>address;
	item.set_student(id,name,address);
	m_List.Add(item);
	DisplayAll();

	return 1;
}


// Display all records in the list on screen.
void Application::DisplayAll()
{
	ItemType data;

	cout << "\n\tCurrent list" << endl;

	m_List.ResetList();	// 리스트 초기화
	// list의 모든 데이터를 화면에 출력
	for(int i = 0; i < m_List.GetLength(); i++)
	{
		m_List.GetNextItem(data);
		cout<<"student id: "<<data.get_id()<<" studnet_name: "<<data.get_name()<<" student_address: "<<data.get_address()<<endl;
	}
}


// Retrieve item in the list.
int Application::RetrieveItem()
{
	ItemType item;
	int id;
	cout << "Enter a item for search : ";
	
	cin>>id;
	item.set_student_id(id);
	if(m_List.Get(item))
	{
		cout << "Target item exists in the list." << endl;
		return 1;
	}
	else
	{
		cout << "Target item is not in the list." << endl;
		return 0;
	}
}

int Application::DeleteItem()
{
	int id;
	ItemType item;
	cout<<" 삭제할 id입력 : ";
	cin>>id;
	item.set_student_id(id);
	if(m_List.Delete(item))
	{
		cout<<"삭제되었습니다"<<endl;
		return 1;
	}
	else
	{
		cout<<"해당하는 값이 존재하지 않습니다"<<endl;
		return 0;
	}
}
int Application::ReplaceItem()
{
	int id;
	string name;
	string address;
	ItemType item;
	cout<<" 갱신할 id입력 : ";
	cin>>id;
	item.set_student_id(id);
	cout<<"바꿀 이름입력: ";
	cin>>name;
	cout<<"바꿀 주소입력: ";
	cin>>address;
	item.set_student(id,name,address);
	if(m_List.Replace(item))
	{
		cout<<"갱신되었습니다"<<endl;
		return 1;
	}
	else
	{
		cout<<"해당하는 값이 존재하지 않습니다"<<endl;
		return 0;
	}
}