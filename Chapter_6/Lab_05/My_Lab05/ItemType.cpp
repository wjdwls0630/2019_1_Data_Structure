#include "ItemType.hpp"

// Set Set Item Name from keyboard.
void ItemType::SetNameFromKB(){
	std::cout << "\t Name : ";
	std::cin >> this->itName;
}


// Set student name from keyboard.
void ItemType::SetPathFromKB(){
	std::cout << "\t Where : ";
	std::cin >> this->itPath;
}

// generate string type time using the current time.
int ItemType::GenerateTime(std::string &data){
  // Declaring argument for time()
  time_t tt;
  // Declaring variable to store return value of localtime()
  struct tm * ti;
  // Applying time()
  time (&tt);
  // Using localtime()
  ti = localtime(&tt);
  std::stringstream ss;
  ss << std::setw(4)<<ti->tm_year+1900<<std::setfill('0')<<std::setw(2)<<ti->tm_mon+1<<std::setfill('0') <<std::setw(2)<<ti->tm_mday<<std::setfill('0')<<std::setw(2)<<ti->tm_hour<<std::setfill('0')<<std::setw(2) <<ti->tm_min<<std::setfill('0')<<std::setw(2)<<ti->tm_sec<<"\0";
  data=ss.str();
	return 1;
}

// MakeMonth to word
std::string ItemType::MakeMonthToWord(std::string month){
	std::string make_month;
	if (month=="01") {
		make_month="Jan";
	} else if (month=="02") {
		make_month="Feb";
	} else if (month=="03") {
		make_month="March";
	} else if (month=="04") {
		make_month="April";
	} else if (month=="05") {
		make_month="May";
	} else if (month=="06") {
		make_month="June";
	} else if (month=="07") {
		make_month="July";
	} else if (month=="08") {
		make_month="Aug";
	} else if (month=="09") {
		make_month="Sep";
	} else if (month=="10") {
		make_month="Oct";
	} else if (month=="12") {
		make_month="Nov";
	} else {
		make_month="Dec";
	}
	return make_month;
}

// Make Hour (param) to Am,Pm(return)
std::string ItemType::MakeHourMinuteToWord(std::string time){
	std::string Am_Pm;
	std::string hour;
	int temp;// for temp
	if ((hour=time.substr(0,2))>="12") { //hour >=12
		Am_Pm="PM";
		temp=std::atoi(hour.c_str())-12;
		if (temp<10) {
			hour="0"+std::to_string(temp);
		} else{
			hour=std::to_string(temp);
		}
	} else{
		Am_Pm="AM";
	}

	return hour+":"+time.substr(2,2)+" "+Am_Pm;
}

// Doing Deep copy by copy assignment operator.
ItemType& ItemType::operator= (const ItemType& item){
	if (this!=&item) {
		this->itName=item.itName;
		this->itPath=item.itPath;
		this->itCreatedTime=item.itCreatedTime;
		this->itModifiedTime=item.itModifiedTime;
		this->itAccessTime=item.itAccessTime;
	}
	return *this;
}
