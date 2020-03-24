#include "Application.h"


/*====================================================================================
// Function	: default constructor, Initialize member variables.
// Pre		: None
// Post		: None
=====================================================================================*/
Application::Application()
{
}

/*====================================================================================
// Function	: default destructor,
// Pre		: None
// Post		: None
=====================================================================================*/
Application::~Application()
{
}

/*====================================================================================
// Function	: Program driver
// Pre		: none
// Post		: none
=====================================================================================*/
void Application::Run()
{
	Polygon* newData;
	int ex = 1;
	int command;
	while(ex)
	{
		system("cls");
		newData = NULL;

		switch(command = GetCommand())
		{
		case 0:
			ex = 0;
			break;
		case 1:
			newData = new Circle();
			break;
		case 2:
			newData = new Triangle();
			break;
		case 3:
			newData = new Rectangle();
			break;
		case 4:
			DisplayAll();
			break;
		default:
			cout << " Invalid Command. Try Again \n";
		}

		if (newData != NULL)
		{
			m_List.Add(newData);
		}
		cout << "\n";
		system("pause");
	}
}

/*====================================================================================
// Function: Display command on screen and get a input from keyboard
// Pre: 
// Post : get command number.
=====================================================================================*/
int Application::GetCommand()
{
	int cmmd;
	cout << "\n\t << Menu >>\n";
	cout << "\t 1: Input Circle       \n";
	cout << "\t 2: Input Triangle Draw   \n";
	cout << "\t 3: Input Rectangle Draw   \n";
	cout << "\t 4: Display All    \n";
	cout << "\t 0: Quit          \n";
	
	cout << "\n\t 입력 -> ";
	cin >> cmmd;
	cout << "\n";

	return cmmd;
}


void Application::DisplayAll()
{
	// list의 모든 데이터를 화면에 출력
	Polygon* data;
	DoublyIterator<Polygon*> itor(m_List);
	data = itor.Next();
	while (itor.NextNotNull())
	{
		data->display();
		data = itor.Next();
	}
}