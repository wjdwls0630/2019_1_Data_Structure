#include "Application.h"
// Program driver.

void Application::Run()
{

	while (1)
	{
		m_Command = GetCommand();

		switch (m_Command)
		{
		case 1:		// �����͸� ����Ʈ�κ��� �о���� �߰���
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
			cout << "\t�߸��� ��ɾ��Դϴ�...\n";
			break;
		}
	}
}


// Display command on screen and get a input from keyboard.
int Application::GetCommand()
{
	int command;
	cout << endl << endl;
	cout << "\t********** ���� ��� ***********" << endl;
	cout << "\t***   1 : �� ���� ����       ***" << endl;
	cout << "\t***   2 : �̸����� ���� �˻� ***" << endl;
	cout << "\t***   3 : ���� ����          ***" << endl;
	cout << "\t***   4 : ���� ����          ***" << endl;
	cout << "\t***   5 : ���� �̸� ����     ***" << endl;
	cout << "\t***   6 : ���� ���� �Ӽ�     ***" << endl;
	cout << "\t***   7 : �ֱ� �� ���� ���  ***" << endl;
	cout << "\t***   8 : ���� ������ �̵�   ***" << endl;
	cout << "\t***   9 : ���� ������ �̵�   ***" << endl;
	cout << "\t***                          ***" << endl;
	cout << "\t********** �ڷ� ��� ***********" << endl;
	cout << "\t***   10 : ���ο� �ڷ� ����  ***" << endl;
	cout << "\t***   11 : �̸����� �ڷ� �˻�***" << endl;
	cout << "\t***   12 : �ڷ� ����         ***" << endl;
	cout << "\t***   13 : �ڷ� ����         ***" << endl;
	cout << "\t***   14 : �ڷ� �̸� ����    ***" << endl;
	cout << "\t***                          ***" << endl;
	cout << "\t********************************" << endl;
	cout << "\t***    0 : ����              ***" << endl;
	cout << "\t********************************" << endl;

	cout << endl << "\t ���ϴ� ����� ���ڸ� ��������--> ";
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
	cout << "\n\t�̵��Ϸ��� ������ �̸��� �Է��ϼ��� ";
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
	cout << "�̸��� �Է��ϼ���";
	cin >> name;

}

void Application::ReplaceItem()
{


}