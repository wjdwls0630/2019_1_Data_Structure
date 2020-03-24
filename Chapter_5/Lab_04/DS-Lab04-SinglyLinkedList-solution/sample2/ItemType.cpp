#include "ItemType.h"


ItemType::ItemType(void)
{
}
int ItemType::get_id()
{
	return student_id;
}
string ItemType::get_name()
{
	return name;
}
string ItemType::get_address()
{
	return address;
}
void ItemType::set_student(int mid, string mname, string maddress)
{
	student_id=mid;
	name=mname;
	address=maddress;
}

void ItemType::set_student_id(int mid)
{
	student_id=mid;
}

ItemType::~ItemType(void)
{
}
