#include "ItemType.h"

// 키보드로 통해 학생 ID를 입력받음
void ItemType::SetIdFromKB()
{
	cout << "\tID : ";
	cin >> m_Id;
}


// 키보드로 통해 학생 이름을 입력받음
void ItemType::SetNameFromKB()
{
	cout << "\tName : ";
	cin >> m_sName;
}


// 키보드로 통해 학생 주소를 입력받음
void ItemType::SetAddressFromKB()
{
	cout << "\tAddress : ";
	cin >> m_sAddress;
}


// 키보드로 통해 학생 정보를 입력받음
void ItemType::SetRecordFromKB()
{
	SetIdFromKB();
	SetNameFromKB();
	SetAddressFromKB();
}


// 파일에서 레코드를 읽는다
int ItemType::ReadDataFromFile(ifstream& fin)
{
	fin >> m_Id;
	fin >> m_sName;
	fin >> m_sAddress;

	return 1;
};


// 파일에 레코드를 쓴다
int ItemType::WriteDataToFile(ofstream& fout)
{
	fout << endl;
	fout << m_Id << " ";
	fout << m_sName << " ";
	fout << m_sAddress;

	return 1;
}


// 2개의 아이템타입을 비교한다
RelationType ItemType::ComparedTo(const ItemType &data)
{
	if (this->m_Id > data.m_Id)
		return GREATER;
	else if (this->m_Id < data.m_Id)
		return LESS;
	else
		return EQUAL;
}