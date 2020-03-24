#include "ItemType.h"


// Set student id from keyboard.
void ItemType::SetIdFromKB()
{
	cout << "\tID : ";
	cin >> m_Id;
}


// Set student name from keyboard.
void ItemType::SetNameFromKB()
{
	cout << "\tName : ";
	cin >> m_sName;
}


// Set student address from keyboard.
void ItemType::SetAddressFromKB()
{
	cout << "\tAddress : ";
	cin >> m_sAddress;
}


// Set student record from keyboard.
void ItemType::SetRecordFromKB()
{
	SetIdFromKB();
	SetNameFromKB();
	SetAddressFromKB();
}


// Read a record from file.
int ItemType::ReadDataFromFile(ifstream& fin)
{
	fin >> m_Id;
	fin >> m_sName;
	fin >> m_sAddress;
	return 1;
};


// Write a record into file.
int ItemType::WriteDataToFile(ofstream& fout)
{
	fout << m_Id << " ";
	fout << m_sName << " ";
	fout << m_sAddress;
	return 1;
}


// Compare two itemtypes.
RelationType ItemType::CompareByID(const ItemType &data)
{
	if(this->m_Id > data.m_Id)
		return GREATER;
	else if(this->m_Id < data.m_Id)
		return LESS;
	else
		return EQUAL;
}

// Compare two item types by item id.
bool ItemType::operator>(ItemType item)
{
	return (this->GetId()>item.GetId());
}	//return 1 if this.id > data.id, 0 if not.

// Compare two item types by item id.
bool ItemType::operator==(ItemType item)
{
	return (this->GetId()==item.GetId());
}	//return 1 if this.id == data.id, 0 if not.