#include "ItemType.h"


// 키보드로 ID 입력 함수.
void ItemType::SetIdFromKB()
{
	cout << "\tID : ";
	cin >> m_Id;
}


// 키보드로 제품명 입력 함수.
void ItemType::SetNameFromKB()
{
	cout << "\tName : ";
	cin >> m_sName;
}


// 키보드로 제조업자 입력 함수.
void ItemType::SetManufacturerFromKB()
{
	cout << "\tManufacturer : ";
	cin >> m_sManufacturer;
}


// 키보드로 제품정보 입력 함수.
void ItemType::SetRecordFromKB()
{
	SetIdFromKB();
	SetNameFromKB();
	SetManufacturerFromKB();
}

// 크기비교 연산자 오버로딩 <
bool ItemType::operator<(ItemType item)
{
	return ( GetId() < item.GetId() );
}


// 크기비교 연산자 오버로딩 >
bool ItemType::operator>(ItemType item)
{
	return ( GetId() > item.GetId() );
}


// 크기비교 연산자 오버로딩 ==
bool ItemType::operator==(ItemType item)
{
	return ( GetId() == item.GetId() );
}


// 출력 연산자 오버로딩 <<
void ItemType::operator<<(ItemType item)
{
	item.DisplayRecordOnScreen();
}



