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

//Doing Deep copy like explicit copy constructor.
FolderType& FolderType::operator= (const FolderType& data){
	if (this != &data) {
		this->fdSubFolderNum=data.fdSubFolderNum;
		this->fdPath=data.fdPath;
		this->fdName=data.fdName;
		this->fdCreatedTime=data.fdCreatedTime;
		this->fdModifiedTime=data.fdModifiedTime;
		if (this->fdSubFolderNum!=0) {
			this->fdFolderList=new SortedList<FolderType>;
			this->fdFolderList=data.fdFolderList;
			}
		}
	return *this;
}


// Create New Folder in Current Folder.
int FolderType::AddFolder(FolderType Temp_Data){
	try{
		if (this->fdSubFolderNum==0) {
			this->fdFolderList=new SortedList<FolderType>; //If there is no Subfolder, then create the FolderList
		}

		if (this->fdFolderList->Get(Temp_Data)){ // if Folder is overlap
			throw FolderOverLap();
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
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
		// If fail Add return 0;
		return 0;
	}
}

// Delete Folder in Current Folder.
int FolderType::DeleteFolder(FolderType Temp_Data){
	try{
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
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
		return 0;
	}
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
FolderType* FolderType::RetrieveFoldersByName(){
	try{
		if (this->fdSubFolderNum==0) {
			throw EmptyFolder();
		}
		FolderType Temp_Data;
		//SortedList<FolderType> Retrieve_Folders(100);
		FolderType* Retrieve_Folders;
		Retrieve_Folders=new FolderType [100];
		std::string Target_Name;
		std::cout << "\t Enter the folder name to find" << '\n';
		std::cout << "\t Name : ";
		std::cin >> Target_Name;
		this->fdFolderList->ResetList();
		for (int i = 0; i < this->fdSubFolderNum; i++) {
			this->fdFolderList->GetNextItem(Temp_Data);
			if (Temp_Data.GetName().find(Target_Name)!=std::string::npos) {
				*(Retrieve_Folders+i)=Temp_Data;
			}
		}
		return Retrieve_Folders;
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
		return NULL;
	}

}

// Display SubFolders name on screen.
void FolderType::DisplayAllFolders(){
	FolderType Temp_Data;
	this->fdFolderList->ResetList();
	std::cout << '\n' << '\n';
	std::cout <<"\t "<<std::setfill('=')<<std::setw(60)<< '\n';
	std::cout <<"\t |\t"<<std::setfill(' ')<<std::setw(10)<<"[Folder Name]"<<std::setfill(' ')<<std::setw(30)<<"[Created Time]"<<std::setfill(' ')<<std::setw(10)<<"|" << '\n';
	for (int i = 0; i < this->fdSubFolderNum; i++) {
		this->fdFolderList->GetNextItem(Temp_Data);
		std::cout << "\t | "<<i+1<<".   "<<Temp_Data.fdName<<std::setfill(' ')<<std::setw(40)<<Temp_Data.fdCreatedTime<<std::setfill(' ')<<std::setw(10)<<"|" <<'\n';
	}
	std::cout <<"\t "<<std::setfill('=')<<std::setw(60)<< '\n';
}

// Open a file by file descriptor as an input file.
int FolderType::OpenInFile(std::ifstream &ifs){
	ifs.open("Data/D_"+this->fdPath+".dat");	// file open for reading.

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if(!ifs)	return 0;
	else	return 1;
}

// Open a file by file descriptor as an output file.
int FolderType::OpenOutFile(std::ofstream &ofs){
	ofs.open("Data/D_"+this->fdPath+".dat");	// file open for writing.

	// 파일 오픈에 성공하면 1, 그렇지 않다면 0을 리턴.
	if(!ofs)	return 0;
	else	return 1;
}

// Open a file as a read mode, read all Folder Info on the file, and set SubFolderlist by the data.
int FolderType::ReadDataFromFile(std::ifstream &ifs){
	try{
		// file open, open error가 발생하면 0을 리턴
		if(!OpenInFile(ifs)){
			throw DataFileNotFound("Data/D_"+this->fdPath+".dat");
		}

		// Store SubFolders Information

		//read first line which has folder info
		int SubFolderNum;
		ifs>>this->fdName>>this->fdPath>>this->fdCreatedTime>>this->fdModifiedTime>>SubFolderNum;

		// Read all SubFolders list and add
		// Temporary data for subfolder
		FolderType Temp_Data; //for read
		int key; //for key
		int i;
		std::string temp;
		std::string info;
		std::string *info_list = new std::string[6];

		if (this->fdSubFolderNum==0) {
			this->fdFolderList=new SortedList<FolderType>;
		}
		while(std::getline(ifs,temp)){
			i=0;
			for(std::stringstream ss(temp);(ss>>info);i++){
				*(info_list+i)=info;
			}
			if (*(info_list)=="1") { // If it is folder,
				//set info
				Temp_Data.SetAllInfo(*(info_list+1),*(info_list+2),*(info_list+3),*(info_list+4));
				this->AddFolder(Temp_Data);
			}
		}
		ifs.close();	// file close
		return 1;
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
		return 0;
	}
}


// Open a file as a write mode, and write all Folder Info into the file,
int FolderType::WriteDataToFile(std::ofstream &ofs){
	try{
		// file open, open error가 발생하면 0을 리턴
		if(!OpenOutFile(ofs)){
			throw DataFileNotFound("Data/D_"+this->fdPath+".dat");
		}

		// Folder의 모든 데이터를 파일에 쓰기
		ofs << std::endl;
		ofs << this->fdName << " ";
		ofs << this->fdPath<< " ";
		ofs << this->fdCreatedTime<< " ";
		ofs << this->fdModifiedTime<< " ";
		ofs << this->fdSubFolderNum << "\n";

		if(this->fdSubFolderNum!=0){
			FolderType Temp_Data; //for write
			this->fdFolderList->ResetList();
			for (int i = 0; i < this->fdSubFolderNum; i++) {
				this->fdFolderList->GetNextItem(Temp_Data);
				//set key=1 if it is folder.
				ofs <<1<<" "<<Temp_Data.fdName<< " "<<Temp_Data.fdPath<< " "<<Temp_Data.fdCreatedTime<< " "<< Temp_Data.fdModifiedTime<<'\n';
			}
		}
		ofs.close();	// file close
		return 1;
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
		return 0;
	}
}
