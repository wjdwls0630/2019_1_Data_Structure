#include "Application.h"


// ���α׷� ����.
void Application::Run()
{
	WhatHeap();

	while(1)
	{
		m_nCurCommand = GetCommand();

		switch(m_nCurCommand)
		{
		case 1:		// �߰�
			AddItem();
			break;
		case 2:		// ����
			DeleteItem();
			break;
		case 3:		// ����
			DequeueItem();
			break;
		case 4:		// ���
			DisplayItem();
			break;
		case 5:		// �˻�
			SearchItem();
			break;
		case 0:		// ����
			return;
		default:	// �� ��
			cout << "\tIllegal sellection...\n";
			break;
		}
	}	
}


// MaxHeap�� MinHeap �� �� �ϳ��� �����ϴ� �Լ�.
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
		case 0:		// ����
			return;
		default:	// �� ��
			cout << "\tIllegal sellection...\n";
			break;
		}

}


// ȭ�鿡 �޴��� �߰� Ű����� �Է��ϴ� �Լ�.
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

// Heap�� �� ��ǰ������ �߰��ϱ� ���� �Լ�.
int Application::AddItem()
{
	ItemType item;

	item.SetRecordFromKB(); // ��ǰ���� �Է�

	if(!m_List->IsFull()) // Heap�� Full���� �ƴ��� �˻�
	{
		m_List->Add(item); // ��ǰ���� �߰�
		return 1;
	}
	else
		cout << "\tFull!!!" << endl;

	return 1;
}


// Heap���� ��ǰ������ �����ϱ� ���� �Լ�.
int Application::DeleteItem()
{	
	ItemType item;
	
	if(!m_List->IsEmpty()) // Heap�� Empty���� �ƴ��� �˻�
	{
		item.SetIdFromKB(); // ������ ��ǰID �Է�

		if(!m_List->Delete(item)) // ��ǰ���� ����
			cout << "\n\tNo Data" << endl; 
	}
	else
		cout << "\tEmpty!!!" << endl;

	return 1;
}


// Heap���� ù��° ��ǰ������ �����ϱ� ���� �Լ�.
int Application::DequeueItem()
{		
	if(!m_List->IsEmpty()) // Heap�� Empty���� �ƴ��� �˻�
	{
		m_List->Dequeue(); // ù��° ��ǰ���� ����
	}
	else
	{
		cout << "\tEmpty!!!" << endl;
	}
	return 1;
}


// Heap�� �ִ� ��ǰ������ ����ϱ� ���� �Լ�.
void Application::DisplayItem()
{
	if(!m_List->IsEmpty()) // Heap�� Empty���� �ƴ��� �˻�
	{
		m_List->PrintHeap(); // ��ǰ���� ���
	}
	else
		cout << "\tEmpty!!!" << endl;
}


// Heap���� ��ǰ������ �˻��ϱ� ���� �Լ�.
int Application::SearchItem()
{
	ItemType item;
	bool found = false;
	
	if(!m_List->IsEmpty()) // Heap�� Empty���� �ƴ��� �˻�
	{
		item.SetIdFromKB(); // �˻��� ��ǰID �Է�

		m_List->RetrieveItem(item, found); // ��ǰ���� �˻�

		// Heap���� ��ǰ�� ã�Ҵ��� ��ã�Ҵ��� �Ǵ�
		if(found)
		{
			cout << "\n\tFound!!" << endl;
			item.DisplayRecordOnScreen(); // �˻��� ��ǰ���� ���
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
