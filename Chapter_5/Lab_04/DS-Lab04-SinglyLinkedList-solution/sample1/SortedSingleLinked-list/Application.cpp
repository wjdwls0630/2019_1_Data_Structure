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
	item.SetRecordFromKB();	//추가할 정보를 입력한다.
	
	m_List.Add(item);	//리스트에 항목을 추가한다.
	DisplayAll();	//리스트를 화면에 출력한다.

	return 1;
}

//Delete record into list.
int Application::DeleteItem()
{
	ItemType item;

	cout << "Delete item : ";
	item.SetIdFromKB();	//삭제할 항목의 id를 입력

	if(m_List.Delete(item))
	{
		cout << "Deleted " << item.GetId() << " Successfully." << endl;
		return 1;
	}	//삭제에 성공하면 성공 메시지를 출력
	else
	{
		cout << item.GetId() << " is not found." << endl;
		return 0;
	}	//해당 항목을 찾을 수 없으면 찾지 못했다는 메시지를 출력
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
	item.SetIdFromKB();	//찾을 항목의 id를 입력

	if(m_List.Get(item))
	{
		cout << "Target item exists in the list." << endl;
		item.DisplayRecordOnScreen();
		return 1;
	}	//찾는것을 성공하면 해당 항목의 정보를 화면에 출력
	else
	{
		cout << "Target item is not in the list." << endl;
		return 0;
	}	//찾을 수 없다면 찾을 수 없다는 메시지 출력
}

//Change item's value in the list.
int Application::Update()
{
	ItemType item;
	cout << "Enter a item's ID for search : ";
	item.SetIdFromKB();	//정보를 수정할 항목의 id를 입력

	if(!m_List.Get(item))
	{
		cout << "Target item is not in the list." << endl;
		return 0;
	}	//해당 항목이 리스트에 없으면 찾지 못했다는 메시지 출력
	else
	{
		item.SetNameFromKB();
		item.SetAddressFromKB();	//나머지 정보 입력
		if(m_List.Replace(item))	//입력받은 값들을 리스트에 반영
			cout << "수정 완료" << endl;
		else
			cout << "수정 실패" << endl;
	}
	return 1;
}

// Open a file by file descriptor as an input file.
int Application::OpenInFile(char *fileName)
{
	m_InFile.open(fileName);	// file open for reading.
	
	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if(!m_InFile)	return 0;
	else	return 1;
}


// Open a file by file descriptor as an output file.
int Application::OpenOutFile(char *fileName)
{
	m_OutFile.open(fileName);	// file open for writing.

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if(!m_OutFile)	return 0;
	else	return 1;
}


// Open a file as a read mode, read all data on the file, and set list by the data.
int Application::ReadDataFromFile()
{
	int index = 0;
	ItemType data;	// 읽기용 임시 변수
	
	char filename[FILENAMESIZE];
	cout << "\n\tEnter Input file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if(!OpenInFile(filename))
		return 0;

	// 파일의 모든 내용을 읽어 list에 추가
	while(!m_InFile.eof())
	{
		// array에 학생들의 정보가 들어있는 structure 저장
		data.ReadDataFromFile(m_InFile);
		m_List.Add(data);
	}

	m_InFile.close();	// file close

	// 현재 list 출력
	DisplayAll();

	return 1;
}


// Open a file as a write mode, and write all data into the file,
int Application::WriteDataToFile()
{
	ItemType data;	// 쓰기용 임시 변수

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if(!OpenOutFile(filename))
		return 0;

	// list 포인터를 초기화
	m_List.ResetList();

	// list의 길이를 리턴받아 저장
	int length = m_List.GetLength();

	// iteration을 이용하여 모든 item 출력
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