#include "Application.h"


// 프로그램을 실행시키는 함수
void Application::Run()
{
	while(1)
	{
		m_Command = GetCommand();

		switch(m_Command)
		{
		case 1:		// 리스트에 아이템을 추가한다.
			AddItem();
			break;	
		case 2:		// 스크린에 리스트의 모든 아이템 정보를 출력한다.
			DisplayAllItem();
			break;
		case 3:		// 리스트를 비운다.
			MakeEmptyList();
			break;
		case 4:		// ID를 이용하여 리스트에서 아이템을 찾는다.
			SearchItembyID();
			break;
		case 5:		// 이름을 이용하여 리스트에서 아이템을 찾는다.
			SearchByName(RetreiveRecordByName());
			break;
		case 6:		// ID를 이용하여 리스트에서 아이템을 찾아 삭제한다.
			DeleteItem();
			break;
		case 7:		// ID를 이용하여 리스트에서 아이템을 찾아 정보를 수정한다.
			UpdateInfo();
			break;
		case 8:		// 리스트의 모든 정보를 파일에서 불러온다.
			ReadDataFromFile();
			break;
		case 9:		// 리스트의 모든 정보를 파일에 저장한다.
			WriteDataToFile();
			break;
		case 0:		// 프로그램을 끝낸다.
			return;
		default:
			cout << "\tIllegal sellection...\n";
			break;
		}
	}
}


// 스크린에 command를 출력하고 키보드로부터 command를 입력받는다.
int Application::GetCommand()
{
	int command;
	cout << endl << endl;
	cout << "\t---ID -- Command ----- " << endl;
	cout << "\t   1 : Add new item" << endl;
	cout << "\t   2 : Print all on screen" << endl;
	cout << "\t   3 : Make empty list" << endl;
	cout << "\t   4 : Search item by ID" << endl;
	cout << "\t   5 : Search item by Name" << endl;
	cout << "\t   6 : Delete item" << endl;
	cout << "\t   7 : Update item info" << endl;
	cout << "\t   8 : Get from file" << endl; 
	cout << "\t   9 : Put to file " << endl; 
	cout << "\t   0 : Quit" << endl; 

	cout << endl << "\t Choose a Command--> ";
	cin >> command;
	cout << endl;

	return command;
}


// 리스트에 새로운 아이템 정보를 추가한다.
int Application::AddItem()
{
	// 입력받은 레코드를 리스트에 add, 리스트가 full일 경우는 add하지 않고 0을 리턴
	if(m_List.IsFull())
	{
		cout << "List is full" << endl;
		return 0;
	}

	ItemType item;

	item.SetRecordFromKB();

	if(m_List.Add(item) == 0) // 입력한 아이디와 같은 아이디가 이미 리스트에 있으면
	{
		cout << "Already has same ID! Try Again!" << endl; // 경고문구를 출력한다.
		return 0;
	}

	// 현재 list 출력
	DisplayAllItem();

	return 1;
}


// 스크린에 리스트의 모든 아이템 정보들을 출력한다.
void Application::DisplayAllItem()
{
	ItemType data;

	cout << "\n\tCurrent list" << endl;

	// list의 모든 데이터를 화면에 출력
	DoublyIterator<ItemType> itor(m_List);
	data = itor.Next();
	while(itor.NextNotNull())
	{
		data.DisplayRecordOnScreen();
		data = itor.Next();
	}
}


// 정보를 불러올 파일을 여는 함수
int Application::OpenInFile(char *fileName)
{
	m_InFile.open(fileName);	// 불러오기 위한 파일 열기
	
	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if(!m_InFile)	return 0;
	else	return 1;
}


// 정보를 저장할 파일을 여는 함수
int Application::OpenOutFile(char *fileName)
{
	m_OutFile.open(fileName);	// 저장하기 위한 파일 열기

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if(!m_OutFile)	return 0;
	else	return 1;
}


// 읽기 위한 파일을 열어 파일에 있는 모든 데이터를 불러오고 데이터들로 리스트를 만든다.
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

	m_InFile.close();	// 파일을 닫는다.

	// 현재 list 출력
	DisplayAllItem();

	return 1;
}


// 쓰기 위한 파일을 열어 리스트의 모든 정보들을 저장한다.
int Application::WriteDataToFile()
{
	ItemType data;	// 쓰기용 임시 변수

	char filename[FILENAMESIZE];
	cout << "\n\tEnter Output file Name : ";
	cin >> filename;

	// file open, open error가 발생하면 0을 리턴
	if(!OpenOutFile(filename))
		return 0;


	// list의 모든 데이터를 파일에 쓰기
	DoublyIterator<ItemType> itor(m_List);
	data = itor.Next();
	while(itor.NextNotNull())
	{
		data.WriteDataToFile(m_OutFile);
		data = itor.Next();
	}

	m_OutFile.close();	// 파일을 닫는다.

	return 1;
}


// 입력받은 ID로 아이템 정보를 찾아내어 스크린에 출력한다.
int Application::SearchItembyID()
{
	ItemType data;
	data.SetIdFromKB(); // 키보드로부터 ID를 입력받는다.
	if(m_List.Get(data) == 0)
		cout << "\tNo match. Try Again." << endl; // 리스트에 일치하는 아이템이 없는 경우 재시도 문구 출력
	else
		data.DisplayRecordOnScreen(); //리스트에 일치하는 아이템을 발견하면 그 아이템의 모든 정보를 출력

	return 1;
}


// 리스트를 비우는 함수
void Application::MakeEmptyList()
{
	m_List.MakeEmpty(); // 리스트를 비운다
	cout << "\tCompelete. List is Empty" << endl; // 리스트 비우기에 성공했다는 문구 출력
}


// 입력받은 ID로 아이템을 찾아내어 그 아이템의 모든 정보를 리스트에서 삭제한다.
int Application::DeleteItem()
{
	if(m_List.IsEmpty() == true) // 리스트가 비었을 때 데이터를 새로 추가하라는 문구 출력
	{
		cout << "\tData is Empty. Add new data and Try again." << endl;
		return 0;
	}
	ItemType data;
	data.SetIdFromKB(); // 키보드로부터 ID를 입력받는다.
	if(m_List.Get(data) == 0) // 일치하는 아이템이 없는 경우 재시도 문구 출력
	{
		cout << "\tNo Match. Try Again" << endl;
		return 0;
	}
	m_List.Delete(data); // 아이템의 정보를 삭제한다.
	cout << "\tDelete compelete." << endl; // 삭제 완료 문구 출력
	return 1;
}


// 입력받은 ID로 아이템을 찾아내어 그 아이템의 정보를 수정한다.
int Application::UpdateInfo()
{
	ItemType data;
	data.SetIdFromKB(); // 키보드로부터 ID를 입력받는다.
	if(m_List.Get(data) == 0) // 일치하는 아이템이 없는 경우 재시도 문구 출력
	{
		cout << "\tNo Match. Try Again" << endl;
		return 0;
	}
	data.SetNameFromKB();
	data.SetManufacturerFromKB();
	m_List.Replace(data); // 아이템의 정보를 수정한다.
	cout << "\tUpdate compelete." << endl; // 수정 완료 문구 출력
	return 1;
}


// 입력받은 이름을 가진 아이템을 반환한다.
ItemType Application::RetreiveRecordByName()
{
	ItemType data;
	data.SetNameFromKB(); // 키보드로부터 이름을 입력받는다.
	return data;
}

//이름을 입력받아 같은 이름을 가진 모든 아이템들을 출력한다.
void Application::SearchByName(ItemType target)
{
	ItemType data;

	cout << "\n\tCurrent list" << endl;

	DoublyIterator<ItemType> itor(m_List);								
	data = itor.Next(); // 다음으로 이동.				

	while ( itor.NextNotNull() )
	{		
		if ( data.GetName().find(target.GetName(),0) != -1 ) // 아이템의 이름을 비교
		{
			data.DisplayRecordOnScreen(); // 일치하면 출력
			data = itor.Next();	// 다음으로 이동.
		}
		else
			data = itor.Next();	// 그렇지 않으면 다음으로 이동.
	}

	return;
}