#include "FileType.h"

// Set student name from keyboard.
void FileType::SetNameFromKB()
{
	cout << "\tName : ";
	cin >> m_dfName;
}


// Set student address from keyboard.
void FileType::SetAddressFromKB()
{
	cout << "\tAddress : ";
	cin >> m_dfAddress;
}


// Set student address from keyboard.
void FileType::SetBytesFromKB()
{
	cout << "\tBytes : ";
	cin >> m_dfBytes;
}


// Set student address from keyboard.
void FileType::SetDateFromKB()
{
	cout << "\tDate : ";
	cin >> m_dfDate;
}


// Set student record from keyboard.
void FileType::SetRecordFromKB()
{
	SetNameFromKB();
	SetAddressFromKB();
	SetBytesFromKB();
	SetDateFromKB();
}

// Read a record from file.
int FileType::ReadDataFromFile(ifstream& fin)
{
	fin >> m_dfName;
	fin >> m_dfAddress;
	fin >> m_dfBytes;
	fin >> m_dfDate;
	return 1;
};

// Write a record into file.
int FileType::WriteDataToFile(ofstream& fout)
{
	fout << endl;
	fout << m_dfName << " ";
	fout << m_dfAddress << " ";
	fout << m_dfBytes << " ";
	fout << m_dfDate << " ";

	return 1;
}


// Compare two itemtypes.
RelationType FileType::CompareByName(const FileType& data)
{
	if (this->m_dfName > data.m_dfName)
		return GREATER;
	else if (this->m_dfName < data.m_dfName)
		return LESS;
	else
		return EQUAL;
}




// Get current time for record
string FileType::GetCurrentTimes()
{
	time_t r;
	struct tm* pTime;
	time(&r);
	pTime = localtime(&r);
	int cTime1 =
		(10000) * (pTime->tm_year + 1900) +
		(100) * (pTime->tm_mon + 1) +
		(pTime->tm_mday);
	int cTime2 =
		(10000) * (pTime->tm_hour) +
		(100) * (pTime->tm_min) +
		pTime->tm_sec;
	string cTime2ToStr;
	if (cTime2 < 100000)
		cTime2ToStr = "0" + to_string(cTime2);
	else
		cTime2ToStr = to_string(cTime2);
	return to_string(cTime1) + cTime2ToStr;
}