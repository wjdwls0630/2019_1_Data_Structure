#include "FolderType.hpp"

// Set Set Folder Name from keyboard.
void FolderType::SetNameFromKB(){
	std::cout << "\t Name : ";
	std::cin >> this->fdName;
}


// Set student name from keyboard.
void FolderType::SetPathFromKB(){
	std::cout << "\t Where : ";
	std::cin >> this->fdPath;
}

// generate string type time using the current time.
int FolderType::GenerateTime(std::string &data){
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

//Doing Deep copy by copy assignment operator.
FolderType& FolderType::operator= (const FolderType& data){
	if (this != &data) {
		if (data.fdSubFolderNum!=0) {
			if (this->fdSubFolderNum==0) {
				this->fdFolderList=new SortedList<FolderType>;
			} else{
				delete this->fdFolderList;
				this->fdFolderList=new SortedList<FolderType>;
			}
			*this->fdFolderList=*data.fdFolderList;
		}
		this->fdSubFolderNum=data.fdSubFolderNum;
		this->fdPath=data.fdPath;
		this->fdName=data.fdName;
		this->fdCreatedTime=data.fdCreatedTime;
	}
	return *this;
}

// display folder name by cout.
std::ostream & operator<<(std::ostream & os, const FolderType & fd){
	return os<<fd.fdName;
}


// Create New Folder in Current Folder.
int FolderType::AddFolder(FolderType Temp_Data){
	if (this->fdSubFolderNum==0) {
		this->fdFolderList=new SortedList<FolderType>; //If there is no Subfolder, then create the FolderList
	}
	int OverLapCount=0; // 수정 부분
	while (this->fdFolderList->Get(Temp_Data)) {// if Folder is overlap
		if (OverLapCount==0) {
			OverLapCount++;
			Temp_Data.fdName+="_"+std::to_string(OverLapCount);
			continue;
		}
		Temp_Data.fdName.pop_back();
		OverLapCount++;
		Temp_Data.fdName+=std::to_string(OverLapCount);
	}

	//If list is full, reallocate
	if (this->fdFolderList->IsFull()) {
		this->fdFolderList->ReAlloc();
	}

	// If Folder is not DataOverLap
	Temp_Data.SetPath(this->fdPath+"/"+Temp_Data.fdName); // Set SubFolder path

	if (this->fdFolderList->Add(Temp_Data)) {
		this->fdSubFolderNum++;
	}
	return 1;
}

// Delete Folder in Current Folder.
int FolderType::DeleteFolder(FolderType Temp_Data){
	if (this->fdSubFolderNum==0) {
		throw EmptyFolder(); // If there is no SubFolder in the Folder, Throw Error
	}

	//If Data is not in the List
	if (!this->fdFolderList->Get(Temp_Data)) {
		throw FolderNotFound();
	}

	//If Data is in the List
	if(this->fdFolderList->Delete(Temp_Data)){
		this->fdSubFolderNum--;
	}
	return 1;
}

// 	Retrieve one Folder you search in Current Folder.
int FolderType::RetrieveFolderByName(FolderType& Target_Folder){
	try{
		if (this->fdSubFolderNum==0) {
			throw EmptyFolder();
		}

		//If Folder is not in the Current Folder
		if (!this->fdFolderList->Get(Target_Folder)) {
			throw FolderNotFound();
		}
		return 1;
	}catch(std::exception &ex){
		std::cout << ex.what() << '\n';
		return 0;
	}
}

// 	Retrieve one Folder you search in Current Folder.
FolderType* FolderType::RetrieveFolderPtrByName(FolderType& Temp_Folder){
	try{
		if (this->fdSubFolderNum==0) {
			throw EmptyFolder();
		}

		FolderType* Target_Folder;
		//If Folder is not in the Current Folder
		if (!(Target_Folder=this->fdFolderList->GetPtr(Temp_Folder))) {
			throw FolderNotFound();
		}
		return Target_Folder;
	}catch(std::exception &ex){
		std::cout << ex.what() << '\n';
		return NULL;
	}
}

// Retrieve all Folder that contain the name you search in Current Folder.
FolderType FolderType::RetrieveFoldersByName(std::string KeyWord){
	if (this->fdSubFolderNum==0) {
		throw EmptyFolder();
	}
	FolderType Retrieve_Folders;
	FolderType Temp_Data;
	this->fdFolderList->ResetList();
	for (int i = 0; i < this->fdSubFolderNum; i++) {
    this->fdFolderList->GetNextItem(Temp_Data);
		if (Temp_Data.GetName().find(KeyWord)!=std::string::npos) {
			Retrieve_Folders.AddFolder(Temp_Data);
		}
	}
	return Retrieve_Folders; //if nothing is found, return NULL

}

// Display SubFolders name on screen.
void FolderType::DisplayAllSubFolders(){
	FolderType Temp_Data;
	this->fdFolderList->ResetList();
	for (int i = 0; i < this->fdSubFolderNum; i++) {
		this->fdFolderList->GetNextItem(Temp_Data);
		std::cout <<"\t "<<i+1<<". "<<Temp_Data<<'\n';
	}
}
