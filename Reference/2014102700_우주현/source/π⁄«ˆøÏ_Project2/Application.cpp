#include "Application.h"
// Program driver.

void Application::Run()
{

	while (1)
	{
		m_Command = GetCommand();

		switch (m_Command)
		{
		case 1:		// 데이터를 리스트로부터 읽어오고 추가함
			NewFolder();
			break;
		case 2:		//search by id.
			RetrieveFolderByName();
			break;
		case 3:	//search by binary search.
			DeleteFolder();
			break;
		case 4:	//search by binary search.
			OpenFolder();
			break;
		case 5:
			ReplaceFolder();
			break;
		case 6:		//search by name.
			DisplayProperty();
			break;
		case 7:
			RecentlyFolder();
			break;
		case 8:
			MoveTo();
			break;
		case 9:
			MoveBack();
			break;
		case 10:
			NewItem();
			break;
		case 11:
			RetrieveItemByName();
			break;
		case 12:
			DeleteItem();
			break;
		case 13:
			OpenItem();
			break;
		case 14:
			ReplaceItem();
			break;
		case 0:
			return;
		default:
			cout << "\t잘못된 명령어입니다...\n";
			break;
		}
	}
}


// Display command on screen and get a input from keyboard.
int Application::GetCommand()
{
	int command;
	cout << endl << endl;
	cout << "\t********** 폴더 기능 ***********" << endl;
	cout << "\t***   1 : 새 폴더 생성       ***" << endl;
	cout << "\t***   2 : 이름으로 폴더 검색 ***" << endl;
	cout << "\t***   3 : 폴더 삭제          ***" << endl;
	cout << "\t***   4 : 폴더 열기          ***" << endl;
	cout << "\t***   5 : 폴더 이름 변경     ***" << endl;
	cout << "\t***   6 : 현재 폴더 속성     ***" << endl;
	cout << "\t***   7 : 최근 연 폴더 목록  ***" << endl;
	cout << "\t***   8 : 하위 폴더로 이동   ***" << endl;
	cout << "\t***   9 : 상위 폴더로 이동   ***" << endl;
	cout << "\t***                          ***" << endl;
	cout << "\t********** 자료 기능 ***********" << endl;
	cout << "\t***   10 : 새로운 자료 생성  ***" << endl;
	cout << "\t***   11 : 이름으로 자료 검색***" << endl;
	cout << "\t***   12 : 자료 삭제         ***" << endl;
	cout << "\t***   13 : 자료 열기         ***" << endl;
	cout << "\t***   14 : 자료 이름 변경    ***" << endl;
	cout << "\t***                          ***" << endl;
	cout << "\t********************************" << endl;
	cout << "\t***    0 : 종료              ***" << endl;
	cout << "\t********************************" << endl;

	cout << endl << "\t 원하는 기능의 숫자를 누르세요--> ";
	cin >> command;
	cout << endl;

	return command;
}


int Application::NewFolder()
{

	return m_curFolder->AddFolder();


	//m_curFolder->AddFolder();
	//m_RecentlyFolder.EnQueue(m_curFolder);
	//m_UpperFolder.Push(m_curFolder);
	//return 1;
}


int Application::DeleteFolder()
{
	return m_curFolder->DeleteFolder();
}

void Application::ReplaceFolder()
{
	return m_curFolder->ReplaceFolder();
}

void Application::OpenFolder()
{
	return m_curFolder->OpenFolder();
}

int Application::RetrieveFolderByName()
{
	return m_curFolder->RetrieveFolderByName();
}


void Application::DisplayProperty()
{
	m_curFolder->DisplayRecordOnScreen();
}

void Application::RecentlyFolder()
{
	m_RecentlyFolder.Print();
}

void Application::MoveBack() {
	;
}

void Application::MoveTo()
{
	FolderType data;
	cout << "\n\t이동하려는 폴더의 이름을 입력하세요 ";
	data.SetNameFromKB();

	FolderType* temp;
	int length = m_curFolder->GetSubFolderNum();
	for (int i = 0; i < length; i++)
		if (m_curFolder->CompareByName(data) == EQUAL)
		{
			temp = m_curFolder;
			temp->SetName(data.GetName());
			temp->SetPath(data.GetPath() + "/" + data.GetName());
			temp->SetCreatTime(data.GetCreatTime());
			temp->GetSubFolderNum();
		}
}


int Application::NewItem()
{
	return 1;
}

int Application::RetrieveItemByName()
{
	return 1;
}

int Application::DeleteItem()
{
	return 1;
}

void Application::OpenItem()
{
	string name;
	cout << "이름을 입력하세요";
	cin >> name;

}

void Application::ReplaceItem()
{


}