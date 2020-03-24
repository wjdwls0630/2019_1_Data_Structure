#include "FolderType.h"

void FolderType::SetNameFromKB()
{
	cout << "\t폴더의 이름을 입력하세요 : ";
	cin >> m_fdName;
}


void FolderType::SetRecordFromKB()
{
	// 폴더 이름
	SetNameFromKB();

	// 폴더 경로
	SetPath(m_fdPath + "/" + m_fdName);

	// 폴더 생성
	SetCreatTime(GetCurTime());

	// 서브 폴더 수
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
			cout << "\t삭제를 완료했습니다." << endl;
			m_fdNum--;
		}
		else
			cout << "\t삭제하지 못했습니다. 일치하는 항목을 찾을 수 없습니다." << endl;

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

		cout << "\n\t-검색 결과-" << endl;

		// list의 모든 데이터를 화면에 출력
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
		cout << "\n\t-현재 위치:/root" << endl;

		cout << "\n\t-현재 폴더 리스트-" << endl;

		// list의 모든 데이터를 화면에 출력
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