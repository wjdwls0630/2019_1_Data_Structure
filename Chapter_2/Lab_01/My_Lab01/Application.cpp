#include "Application.h"


// Program driver.
void Application::Run()
{
	while (1)
	{
		this->m_Command = GetCommand();
		cout.setf(ios::left, ios::adjustfield);
		switch (m_Command)
		{
		case 1:		// ����� ������ �Է� �޾� ����Ʈ�� �߰�					'
			AddItem();
			break;
		case 2:		// ����� ������ �Է� �޾� ����Ʈ���� ����
			DeleteItem();
			break;
		case 3:		// ����� ������ �Է� �޾� ����Ʈ���� ����
			ReplaceItem();
			break;
		case 4:		// �Էµ� ������ ����Ʈ���� ����ڸ� ã�� �������
			DisplayItem();
			break;
		case 5:		// ����Ʈ�� �Էµ� ��� ����� ���� ���
			DisplayAllItem();
			break;
		case 6: 		// ����Ʈ�� �Էµ� ��� ����� ���� ����
			MakeEmpty();
			break;
		case 7:		// load list data from a file.
			ReadDataFromFile();
			break;
		case 8:		// save list data into a file.
			WriteDataToFile();
			break;
		case 0:
			return;
		default:
			cout << "\t Illegal selection...\n";
			break;
		}
	}
}


// Display command on screen and get a input from keyboard.
int Application::GetCommand()
{
	int command;
	while (1) {
		cout << endl << endl;
		cout << "\t---ID -- Command ----- " << endl;
		cout << "\t   1 : Add item" << endl;
		cout << "\t   2 : Delete item" << endl;
		cout << "\t   3 : Replace item" << endl;
		cout << "\t   4 : Print item on screen" << endl;
		cout << "\t   5 : Print all on screen" << endl;
		cout << "\t   6 : Make empty list" << endl;
		cout << "\t   7 : Get from file" << endl;
		cout << "\t   8 : Put to file " << endl;
		cout << "\t   0 : Quit" << endl;
		cout << endl << "\t Choose a Command--> ";
		if ((cin.fail()) || !(cin >> command) || command < 0 || command>8)   // input fail or input value is out of bound
		{
		  cout<<"\t ### Invalid Command Number. Select again ####"<<endl;
		  cin.clear();   //clear flag
		  cin.ignore(INT_MAX, '\n');   //empty input buffer
		}
		else {
		  cin.clear();  // clear flag
		  cin.ignore(INT_MAX, '\n');  // empty input buffer
		  return command;
		}
	}
}


// Add new record into list.
int Application::AddItem()
{
	// �Է¹��� ���ڵ带 ����Ʈ�� add, ����Ʈ�� full�� ���� add���� �ʰ� 0�� ����
	if(m_List.IsFull())
	{
		cout << "\t List is full" << endl;
		return 0;
	}

	ItemType item;
	std::cout << "\t Enter Student Record for Add"<<'\n';

	item.SetRecordFromKB();
	m_List.Add(item);

	// ���� list ���
	DisplayAllItem();

	return 1;
}

// Delete the record in the list.
int Application::DeleteItem(){
	//If list is empty , don't delete anything , return 0
	//If it is not empty, delete the record searched from Get
	if (this->m_List.IsEmpty()) {
		std::cout << "\t List is Empty" << '\n';
		return 0;
	}

	ItemType Delete_Item;
	std::cout << "\t Enter Student ID for Delete"<<'\n';

	Delete_Item.SetIdFromKB();
	this->m_List.Delete(Delete_Item);

	// Display Current list
	this->DisplayAllItem();

	return 1;
}

//Update the record in the list.
int Application::ReplaceItem(){
	//If list is empty , don't update anything , return 0
	//If it is not empty, update the record searched from Get
	if (this->m_List.IsEmpty()) {
		std::cout << "\t List is Empty" << '\n';
		return 0;
	}

	ItemType Replace_Item;
	std::cout << "\t Enter Student ID for Replace"<<'\n';

	Replace_Item.SetIdFromKB();
	std::cout << "\t Enter New Student Record"<<'\n';
	this->m_List.Replace(Replace_Item);

	// Display Current list
	this->DisplayAllItem();
	return 1;

}

//Display the record in the list.
void Application::DisplayItem(){

	ItemType Display_Item;
	std::cout << "\t Enter Student ID for Search"<<'\n';

	Display_Item.SetIdFromKB();
	this->m_List.Get(Display_Item);

	//Display the data that you searched
	Display_Item.DisplayRecordOnScreen();
}

// Display all records in the list on screen.
void Application::DisplayAllItem()
{
	ItemType data;

	cout << "\n\t Current list" << endl;

	// list�� ��� �����͸� ȭ�鿡 ���
	m_List.ResetList();
	int length = m_List.GetLength();
	int curIndex = m_List.GetNextItem(data);
	while(curIndex < length && curIndex != -1)
	{
		data.DisplayRecordOnScreen();
		curIndex = m_List.GetNextItem(data);
	}
}

// Make list empty.
void Application::MakeEmpty(){
	this->m_List.MakeEmpty();
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
	//int index = 0;
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
	DisplayAllItem();

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

	// list�� ��� �����͸� ���Ͽ� ����
	int length = m_List.GetLength();
	int curIndex = m_List.GetNextItem(data);
	while(curIndex < length && curIndex != -1)
	{
		data.WriteDataToFile(m_OutFile);
		curIndex = m_List.GetNextItem(data);
	}

	m_OutFile.close();	// file close

	return 1;
}
