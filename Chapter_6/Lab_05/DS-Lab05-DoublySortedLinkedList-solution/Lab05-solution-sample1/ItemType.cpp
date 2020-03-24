#include "ItemType.h"


// 키보드로부터 ID를 입력받는 함수
void ItemType::SetIdFromKB()
{
	cout << "\tID : ";
	cin >> m_Id;
}


// 키보드로부터 아이템 이름을 입력받는 함수
void ItemType::SetNameFromKB()
{
	cout << "\tName : ";
	cin >> m_sName;
}


// 키보드로부터 제조자를 입력받는 함수
void ItemType::SetManufacturerFromKB()
{
	cout << "\tManufacturer : ";
	cin >> m_sManufacturer;
}


// 아이템의 ID, 이름, 제조자를 입력받는다.
void ItemType::SetRecordFromKB()
{
	SetIdFromKB();
	SetNameFromKB();
	SetManufacturerFromKB();
}


// 파일에서 아이템의 ID, 이름, 제조자를 가져온다.
int ItemType::ReadDataFromFile(ifstream& fin)
{
	fin >> m_Id;
	fin >> m_sName;
	fin >> m_sManufacturer;

	return 1;
};


// 파일에 아이템의 ID, 이름, 제조자를 입력한다.
int ItemType::WriteDataToFile(ofstream& fout)
{
	fout << endl;
	fout << m_Id << " ";
	fout << m_sName << " ";
	fout << m_sManufacturer << " ";

	return 1;
}


// 두 아이템의 ID를 비교하는 함수
RelationType ItemType::CompareByID(const ItemType &data)
{
	if(this->m_Id > data.m_Id)
		return GREATER;
	else if(this->m_Id < data.m_Id)
		return LESS;
	else
		return EQUAL;
}
