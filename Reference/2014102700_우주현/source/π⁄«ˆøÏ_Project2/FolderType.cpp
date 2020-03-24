#include "FolderType.h"

void FolderType::SetNameFromKB()
{
	cout << "\t������ �̸��� �Է��ϼ��� : ";
	cin >> m_fdName;
}


void FolderType::SetRecordFromKB()
{
	// ���� �̸�
	SetNameFromKB();

	// ���� ���
	SetPath(m_fdPath + "/" + m_fdName);

	// ���� ����
	SetCreatTime(GetCurTime());

	// ���� ���� ��
	GetSubFolderNum();
}

RelationType FolderType::CompareByName(const FolderType & data)
{
	if (this->m_fdName > data.m_fdName)
		return GREATER;
	else if (this->m_fdName < data.m_fdName)
		return LESS;
	else
		return EQUAL;
}


int FolderType::AddFolder()
{
	if (m_fdNum == 0) {
		m_fdList = new ArrayList<FolderType>;
		//mQueue = new Queue<FolderType>;
	}

	FolderType data;
	data.SetPath(m_fdPath);
	data.SetRecordFromKB();

	if (m_fdList->Add(data))
		m_fdNum++;
	//mQueue->EnQueue(data);
	DisplayAllFolderName();

	return 1;
}


int FolderType::DeleteFolder()
{
	if (m_fdNum != 0)
	{
		FolderType data;

		data.SetNameFromKB();
		if (m_fdList->Delete(data))
		{
			cout << "\t������ �Ϸ��߽��ϴ�." << endl;
			m_fdNum--;
		}
		else
			cout << "\t�������� ���߽��ϴ�. ��ġ�ϴ� �׸��� ã�� �� �����ϴ�." << endl;

		DisplayAllFolderName();

	}

	return 1;
}

void FolderType::ReplaceFolder()
{
	FolderType data;
	m_fdList->Replace(data);
}

void FolderType::OpenFolder()
{
	FolderType data;
	m_fdList->Replace(data);
}

int FolderType::RetrieveFolderByName()
{
	if (m_fdList != 0)
	{
		FolderType data;
		data.SetNameFromKB();

		FolderType temp;

		cout << "\n\t-�˻� ���-" << endl;

		// list�� ��� �����͸� ȭ�鿡 ���
		m_fdList->ResetList();
		int length = m_fdList->GetLength();
		int curIndex = m_fdList->GetNextItem(temp);
		while (curIndex < length && curIndex != -1)
		{
			if (temp.GetName().find(data.GetName()) != string::npos)
				temp.DisplayRecordOnScreen();


			curIndex = m_fdList->GetNextItem(temp);
		}
		return 1;
	}
	return 0;
}


void FolderType::DisplayAllFolderName()
{
	if (m_fdNum != 0)
	{
		//textcolor(YELLOW,0);
		FolderType data;
		cout << "\n\t-���� ��ġ:/root" << endl;

		cout << "\n\t-���� ���� ����Ʈ-" << endl;

		// list�� ��� �����͸� ȭ�鿡 ���
		m_fdList->ResetList();
		int length = m_fdList->GetLength();
		int curIndex = m_fdList->GetNextItem(data);
		while (curIndex < length && curIndex != -1)
		{
			cout << "\t" << data.GetName() << "\n";
			curIndex = m_fdList->GetNextItem(data);
		}
	}
}