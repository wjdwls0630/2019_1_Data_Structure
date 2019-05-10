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
		case 2:		// display all items
			DisplayAll();
			break;
		case 3:		// make the list empty
			MakeEmpty();
			break;
		case 4:		// retrieves item
			RetrieveItem();
			break;
		case 5:		// delete item
			DeleteItem();
			break;
		case 6:		// change value of an item
			Update();
			break;
		case 7:		// get data from data file
			ReadDataFromFile();
			break;
		case 8:		// put data to data file
			WriteDataToFile();
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
	cout << "\t   2 : Display all Item" << endl;
	cout << "\t   3 : Make empty list" << endl;
	cout << "\t   4 : Search item by ID" << endl;
	cout << "\t   5 : Delete Item" << endl;
	cout << "\t   6 : Update item" << endl;
	cout << "\t   7 : Get from file" << endl;
	cout << "\t   8 : Put to file" << endl;
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

	cout << "Input Item : ";
	item.SetRecordFromKB();	//�߰��� ������ �Է��Ѵ�.
	
	m_List.Add(item);	//����Ʈ�� �׸��� �߰��Ѵ�.
	DisplayAll();	//����Ʈ�� ȭ�鿡 ����Ѵ�.

	return 1;
}

//Delete record into list.
int Application::DeleteItem()
{
	ItemType item;

	cout << "Delete item : ";
	item.SetIdFromKB();	//������ �׸��� id�� �Է�

	if(m_List.Delete(item))
	{
		cout << "Deleted " << item.GetId() << " Successfully." << endl;
		return 1;
	}	//������ �����ϸ� ���� �޽����� ���
	else
	{
		cout << item.GetId() << " is not found." << endl;
		return 0;
	}	//�ش� �׸��� ã�� �� ������ ã�� ���ߴٴ� �޽����� ���
}


// Display all records in the list on screen.
void Application::DisplayAll()
{
	ItemType data;

	cout << "\n\tCurrent list" << endl;

	m_List.ResetList();	// ����Ʈ �ʱ�ȭ
	// list�� ��� �����͸� ȭ�鿡 ���
	for(int i = 0; i < m_List.GetLength(); i++)
	{
		m_List.GetNextItem(data);
		data.DisplayRecordOnScreen();
		cout << "\n\t\t|\n\n";
	}
}

//Make empty list.
int Application::MakeEmpty()
{
	m_List.MakeEmpty();
	cout << "List is now empty.";
	return 0;
}


// Retrieve item in the list.
int Application::RetrieveItem()
{
	ItemType item;
	cout << "Enter a item's ID for search : ";
	item.SetIdFromKB();	//ã�� �׸��� id�� �Է�

	if(m_List.Get(item))
	{
		cout << "Target item exists in the list." << endl;
		item.DisplayRecordOnScreen();
		return 1;
	}	//ã�°��� �����ϸ� �ش� �׸��� ������ ȭ�鿡 ���
	else
	{
		cout << "Target item is not in the list." << endl;
		return 0;
	}	//ã�� �� ���ٸ� ã�� �� ���ٴ� �޽��� ���
}

//Change item's value in the list.
int Application::Update()
{
	ItemType item;
	cout << "Enter a item's ID for search : ";
	item.SetIdFromKB();	//������ ������ �׸��� id�� �Է�

	if(!m_List.Get(item))
	{
		cout << "Target item is not in the list." << endl;
		return 0;
	}	//�ش� �׸��� ����Ʈ�� ������ ã�� ���ߴٴ� �޽��� ���
	else
	{
		item.SetNameFromKB();
		item.SetAddressFromKB();	//������ ���� �Է�
		if(m_List.Replace(item))	//�Է¹��� ������ ����Ʈ�� �ݿ�
			cout << "���� �Ϸ�" << endl;
		else
			cout << "���� ����" << endl;
	}
	return 1;
}

// Open a file by file descriptor as an input file.
int Application::OpenInFile(char *fileName)
{
	m_InFile.open(fileName);	// file open for reading.
	
	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if(!m_InFile)	return 0;
	else	return 1;
}


// Open a file by file descriptor as an output file.
int Application::OpenOutFile(char *fileName)
{
	m_OutFile.open(fileName);	// file open for writing.

	// ���� ���¿� �����ϸ� 1, �׷��� �ʴٸ� 0�� ����.
	if(!m_OutFile)	return 0;
	else	return 1;
}


// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::ReadDataFromFile()
{
	int index = 0;
	ItemType data;	// �б�� �ӽ� ����
	
	char filename[FILENAMESIZE];
	cout << "\n\tEnter Input file Name : ";
	cin >> filename;

	// file open, open error�� �߻��ϸ� 0�� ����
	if(!OpenInFile(filename))
		return 0;

	// ������ ��� ������ �о� list�� �߰�
	while(!m_InFile.eof())
	{
		// array�� �л����� ������ ����ִ� structure ����
		data.ReadDataFromFile(m_InFile);
		m_List.Add(data);
	}

	m_InFile.close();	// file close

	// ���� list ���
	DisplayAll();

	return 1;
}


// Open a file as a write mode, and write all data into the file,
int Application::WriteDataToFile()
{
	ItemType data;	// ����� �ӽ� ����

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error�� �߻��ϸ� 0�� ����
	if(!OpenOutFile(filename))
		return 0;

	// list �����͸� �ʱ�ȭ
	m_List.ResetList();

	// list�� ���̸� ���Ϲ޾� ����
	int length = m_List.GetLength();

	// iteration�� �̿��Ͽ� ��� item ���
	for(int i=0;i<length;i++)
	{
		m_List.GetNextItem(data);
		data.WriteDataToFile(m_OutFile);
		if(i!=length-1)
			m_OutFile << endl;
	}

	m_OutFile.close();	// file close

	return 1;
}