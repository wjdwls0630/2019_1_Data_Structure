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
FolderType& FolderType::operator= (const FolderType& fd){
	if (this != &fd) {

		//folder part
		if (fd.fdSubFolderNum!=0) {
			if (this->fdSubFolderNum==0) {
				this->fdFolderList=new SLinkedList<FolderType>;
			} else{
				delete this->fdFolderList;
				this->fdFolderList=new SLinkedList<FolderType>;
			}
			*this->fdFolderList=*fd.fdFolderList;
		}

		//file part
		if (fd.fdSubFileNum!=0) {
			if (this->fdSubFileNum==0) {
				this->fdFileList=new SLinkedList<FileType>;
			} else{
				delete this->fdFileList;
				this->fdFileList=new SLinkedList<FileType>;
			}
			*this->fdFileList=*fd.fdFileList;
		}

		//other property
		this->fdSubFolderNum=fd.fdSubFolderNum;
		this->fdSubFileNum=fd.fdSubFileNum;
		this->fdPath=fd.fdPath;
		this->fdName=fd.fdName;
		this->fdCreatedTime=fd.fdCreatedTime;
	}
	return *this;
}

// Doing combine two different folder.
FolderType& FolderType::operator+=(const FolderType &fd){

	FolderType Folder_Data;
	FileType File_Data;
	//folder part
	if (fd.fdSubFolderNum!=0) {
		if (this->fdSubFolderNum==0) {
			this->fdFolderList=new SLinkedList<FolderType>;
		}
		fd.fdFolderList->ResetList();
		for (int i = 0; i < fd.fdSubFolderNum; i++) {
			fd.fdFolderList->GetNextItem(Folder_Data);
			this->fdFolderList->Add(Folder_Data);
		}
	}

	//file part
	if (fd.fdSubFileNum!=0) {
		if (this->fdSubFileNum==0) {
			this->fdFileList=new SLinkedList<FileType>;
		}
		fd.fdFileList->ResetList();
		for (int i = 0; i < fd.fdSubFileNum; i++) {
			fd.fdFileList->GetNextItem(File_Data);
			this->fdFileList->Add(File_Data);
		}
	}

	//other property
	this->fdSubFolderNum+=fd.fdSubFolderNum;
	this->fdSubFileNum+=fd.fdSubFileNum;

	return *this;
}

// Create New Folder in Current Folder.
int FolderType::AddFolder(FolderType Temp_Folder){
	if (this->fdSubFolderNum==0) {
		this->fdFolderList=new SLinkedList<FolderType>; //If there is no Subfolder, then create the FolderList
	}
	int OverLapCount=0; // 수정 부분
	while (this->fdFolderList->Get(Temp_Folder)) {// if Folder is overlap
		if (OverLapCount==0) {
			OverLapCount++;
			Temp_Folder.fdName+="_"+std::to_string(OverLapCount);
			Temp_Folder.SetPath(this->fdPath+"/"+Temp_Folder.fdName); // Set SubFolder path
			continue;
		}
		Temp_Folder.fdName.pop_back();
		OverLapCount++;
		Temp_Folder.fdName+=std::to_string(OverLapCount);
		Temp_Folder.SetPath(this->fdPath+"/"+Temp_Folder.fdName); // Set SubFolder path
	}

	if (this->fdFolderList->Add(Temp_Folder)) {
		this->fdSubFolderNum++;
	}
	return 1;
}

// Create New File in Current Folder.
int FolderType::AddFile(FileType Temp_File){
	if (this->fdSubFileNum==0) {
		this->fdFileList=new SLinkedList<FileType>; //If there is no Subfile then create the FileList
	}

	std::string Temp_Name;
	int OverLapCount=0; // 수정 부분
	while (this->fdFileList->Get(Temp_File)) {// if File is overlap
		Temp_Name=Temp_File.GetName().substr(0,Temp_File.GetName().find('.') );
		if (OverLapCount==0) {
			OverLapCount++;
			Temp_File.SetName(Temp_Name+"_"+std::to_string(OverLapCount)+'.'+Temp_File.GetExtensions());
			continue;
		}
		Temp_Name.pop_back();
		OverLapCount++;
		Temp_File.SetName(Temp_Name+std::to_string(OverLapCount)+'.'+Temp_File.GetExtensions());
	}

	if (OverLapCount!=0) {
		// If File OverLap Set new Path
		Temp_File.SetPath(this->fdPath+"/"+Temp_File.GetName()); // Set SubFile path
	}

	if (this->fdFileList->Add(Temp_File)) {
		this->fdSubFileNum++;
	}
	return 1;
}

// Delete Folder in Current Folder.
int FolderType::DeleteFolder(FolderType Temp_Folder){
	if (this->fdSubFolderNum==0) {
		throw ItemNotFound(Temp_Folder.GetName()); // If there is no SubFolder in the Folder, Throw Error
	}

	//If Data is not in the List
	if (!this->fdFolderList->Get(Temp_Folder)) {
		throw ItemNotFound(Temp_Folder.GetName());
	}

	//If Data is in the List
	if(this->fdFolderList->Delete(Temp_Folder)){
		this->fdSubFolderNum--;
	}
	if (this->fdSubFolderNum==0) { // if subfoldernum 0 delete fdFolderList
		delete this->fdFolderList;
	}
	return 1;
}

// Delete Folder in Current Folder.
int FolderType::DeleteFile(FileType Temp_File){
	if (this->fdSubFileNum==0) {
		throw ItemNotFound(Temp_File.GetName()); // If there is no SubItem in the Folder, Throw Error
	}

	//If Data is not in the List
	if (!this->fdFileList->Get(Temp_File)) {
		throw ItemNotFound(Temp_File.GetName());
	}

	//If Data is in the List
	if(this->fdFileList->Delete(Temp_File)){
		this->fdSubFileNum--;
	}
	if (this->fdSubFileNum==0) { // if subfoldernum 0 delete fdFolderList
		delete this->fdFileList;
	}
	return 1;
}

// 	Retrieve one Folder you search in Current Folder.
int FolderType::RetrieveFolderByName(FolderType& Target_Folder){

	if (this->fdSubFolderNum==0) {
		throw ItemNotFound(Target_Folder.GetName());
	}

	//If Folder is not in the Current Folder
	if (!this->fdFolderList->Get(Target_Folder)) {
		throw ItemNotFound(Target_Folder.GetName());
	}
	return 1;
}

// Retrieve one File you search in Current Folder.
int FolderType::RetrieveFileByName(FileType& Target_File){
		if (this->fdSubFileNum==0) {
			throw ItemNotFound(Target_File.GetName());
		}

		//If Folder is not in the Current Folder
		if (!this->fdFileList->Get(Target_File)) {
			throw ItemNotFound(Target_File.GetName());
		}
		return 1;

}


// Retrieve the pointer of the one Folder you search in Current Folder.
FolderType* FolderType::RetrieveFolderPtrByName(FolderType& Target_Folder){
	if (this->fdSubFolderNum==0) {
		throw ItemNotFound(Target_Folder.GetName());
	}

	FolderType* Target_FolderPtr;
	//If Folder is not in the Current Folder
	if (!(Target_FolderPtr=this->fdFolderList->GetPtr(Target_Folder))) {
		throw ItemNotFound(Target_Folder.GetName());
	}
	return Target_FolderPtr;
}

// Retrieve the pointer of the one File you search in Current Folder.
FileType* FolderType::RetrieveFilePtrByName(FileType& Target_File){
	if (this->fdSubFileNum==0) {
		throw ItemNotFound(Target_File.GetName());
	}

	FileType* Target_FilePtr;
	//If File is not in the Current Folder
	if (!(Target_FilePtr=this->fdFileList->GetPtr(Target_File))) {
		throw ItemNotFound(Target_File.GetName());
	}
	return Target_FilePtr;
}


// Retrieve all SubItems that contain the name you search in All child folder.
FolderType FolderType::RetrieveItemsByName(std::string KeyWord){

	FolderType Retrieve_Folders;
	FolderType Temp_Folder;
	FileType Temp_File;

	if (this->fdSubFolderNum==0) {
		if (this->fdSubFileNum==0) { //folder && file 0
			throw EmptyFolder();
		}
		// folder 0 && file not 0, no sub folder
		this->fdFileList->ResetList();
		for (int i = 0; i < this->fdSubFileNum; i++) {
			this->fdFileList->GetNextItem(Temp_File);
			if (Temp_File.GetName().find(KeyWord)!=std::string::npos) {
				Retrieve_Folders.AddFile(Temp_File);
			}
		}
	} else{
		if (this->fdSubFileNum==0) { //folder not 0 && file 0
			this->fdFolderList->ResetList();
			for (int i = 0; i < this->fdSubFolderNum; i++) {
				this->fdFolderList->GetNextItem(Temp_Folder);
				if (Temp_Folder.GetName().find(KeyWord)!=std::string::npos) {
					Retrieve_Folders.AddFolder(Temp_Folder);
				}

				// call recursive when catch, end the loop
				try{
					Retrieve_Folders+=Temp_Folder.RetrieveItemsByName(KeyWord);
				} catch(std::exception &ex){
					continue;
				}
			}
		} else{ // folder && file not 0
			//Folder
			this->fdFolderList->ResetList();
			for (int i = 0; i < this->fdSubFolderNum; i++) {
				this->fdFolderList->GetNextItem(Temp_Folder);
				if (Temp_Folder.GetName().find(KeyWord)!=std::string::npos) {
					Retrieve_Folders.AddFolder(Temp_Folder);
				}

				// call recursive when catch error, end the loop
				try{
					Retrieve_Folders+=Temp_Folder.RetrieveItemsByName(KeyWord);
				} catch(std::exception &ex){
					continue;
				}
			}

			//File
			this->fdFileList->ResetList();
			for (int i = 0; i < this->fdSubFileNum; i++) {
				this->fdFileList->GetNextItem(Temp_File);
				if (Temp_File.GetName().find(KeyWord)!=std::string::npos) {
					Retrieve_Folders.AddFile(Temp_File);
				}
		  }
	  }
  }
	return Retrieve_Folders;
}


// Display SubFolders name on screen.
void FolderType::DisplayAllSubFolders(){
	FolderType Temp_Folder;
	this->fdFolderList->ResetList();
	for (int i = 0; i < this->fdSubFolderNum; i++) {
		this->fdFolderList->GetNextItem(Temp_Folder);
		std::cout <<"\t "<<Temp_Folder<<'\n';
	}
}

// Display SubFiles name on screen.
void FolderType::DisplayAllSubFiles(){
	FileType Temp_File;
	this->fdFileList->ResetList();
	for (int i = 0; i < this->fdSubFileNum; i++) {
		this->fdFileList->GetNextItem(Temp_File);
		std::cout <<"\t "<<Temp_File<<'\n';
	}
}
