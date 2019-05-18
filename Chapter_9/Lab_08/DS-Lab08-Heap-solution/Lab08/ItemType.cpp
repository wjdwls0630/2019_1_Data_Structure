#include "ItemType.h"


// Ű����� ID �Է� �Լ�.
void ItemType::SetIdFromKB()
{
	cout << "\tID : ";
	cin >> m_Id;
}


// Ű����� ��ǰ�� �Է� �Լ�.
void ItemType::SetNameFromKB()
{
	cout << "\tName : ";
	cin >> m_sName;
}


// Ű����� �������� �Է� �Լ�.
void ItemType::SetManufacturerFromKB()
{
	cout << "\tManufacturer : ";
	cin >> m_sManufacturer;
}


// Ű����� ��ǰ���� �Է� �Լ�.
void ItemType::SetRecordFromKB()
{
	SetIdFromKB();
	SetNameFromKB();
	SetManufacturerFromKB();
}

// ũ��� ������ �����ε� <
bool ItemType::operator<(ItemType item)
{
	return ( GetId() < item.GetId() );
}


// ũ��� ������ �����ε� >
bool ItemType::operator>(ItemType item)
{
	return ( GetId() > item.GetId() );
}


// ũ��� ������ �����ε� ==
bool ItemType::operator==(ItemType item)
{
	return ( GetId() == item.GetId() );
}


// ��� ������ �����ε� <<
void ItemType::operator<<(ItemType item)
{
	item.DisplayRecordOnScreen();
}



