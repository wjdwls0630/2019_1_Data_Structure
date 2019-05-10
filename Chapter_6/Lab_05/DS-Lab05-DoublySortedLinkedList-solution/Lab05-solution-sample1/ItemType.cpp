#include "ItemType.h"


// Ű����κ��� ID�� �Է¹޴� �Լ�
void ItemType::SetIdFromKB()
{
	cout << "\tID : ";
	cin >> m_Id;
}


// Ű����κ��� ������ �̸��� �Է¹޴� �Լ�
void ItemType::SetNameFromKB()
{
	cout << "\tName : ";
	cin >> m_sName;
}


// Ű����κ��� �����ڸ� �Է¹޴� �Լ�
void ItemType::SetManufacturerFromKB()
{
	cout << "\tManufacturer : ";
	cin >> m_sManufacturer;
}


// �������� ID, �̸�, �����ڸ� �Է¹޴´�.
void ItemType::SetRecordFromKB()
{
	SetIdFromKB();
	SetNameFromKB();
	SetManufacturerFromKB();
}


// ���Ͽ��� �������� ID, �̸�, �����ڸ� �����´�.
int ItemType::ReadDataFromFile(ifstream& fin)
{
	fin >> m_Id;
	fin >> m_sName;
	fin >> m_sManufacturer;

	return 1;
};


// ���Ͽ� �������� ID, �̸�, �����ڸ� �Է��Ѵ�.
int ItemType::WriteDataToFile(ofstream& fout)
{
	fout << endl;
	fout << m_Id << " ";
	fout << m_sName << " ";
	fout << m_sManufacturer << " ";

	return 1;
}


// �� �������� ID�� ���ϴ� �Լ�
RelationType ItemType::CompareByID(const ItemType &data)
{
	if(this->m_Id > data.m_Id)
		return GREATER;
	else if(this->m_Id < data.m_Id)
		return LESS;
	else
		return EQUAL;
}
