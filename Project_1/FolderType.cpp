#include "FolderType.hpp"

//Doing Deep copy by copy assignment operator.
FolderType& FolderType::operator= (const FolderType& fd){
	if (this!=&fd) {

		//file part
		FileType Temp_File;
		if (fd.fdSubFileNum!=0) {
			if (this->fdSubFileNum!=0) {
				delete this->fdSubFileList;
				this->fdSubFileList=new SLinkedList<FileType>;
			} else{
				this->fdSubFileList=new SLinkedList<FileType>;
			}
			fd.fdSubFileList->ResetList();
			while(fd.fdSubFileList->GetNextItem(Temp_File)){
				Temp_File.SetPath(fd.GetPath()+"/"+Temp_File.GetName());
				this->fdSubFileList->Add(Temp_File);
			}
	  }

		//folder part
		FolderType Temp_Folder;
		FolderType* Temp_FolderPtr;
		FolderType Copy_Folder;
		if (fd.fdSubFolderNum!=0) {
			if (this->fdSubFolderNum!=0) {
				this->fdSubFolderList->ResetList();
				while ((Temp_FolderPtr=this->fdSubFolderList->GetNextItemPtr())) {
					if (Temp_FolderPtr->GetSubItemrNum()!=0) {
						delete Temp_FolderPtr;
					}
				}
				//delete this->fdSubFolderList;
			} else{
				this->fdSubFolderList=new SLinkedList<FolderType>;
			}
			//*this->fdSubFolderList=*fd.fdSubFolderList;
			fd.fdSubFolderList->ResetList();
			while (fd.fdSubFolderList->GetNextItem(Temp_Folder)) {
				if (Temp_Folder.GetSubItemrNum()!=0) { //if temp folder has subitem
					Copy_Folder=Temp_Folder;// call recursive
					Copy_Folder.SetPath(fd.GetPath()+"/"+Copy_Folder.GetName());
					this->fdSubFolderList->Add(Copy_Folder);
				} else{
					Temp_Folder.SetPath(fd.GetPath()+"/"+Temp_Folder.GetName());
					this->fdSubFolderList->Add(Temp_Folder);
				}

			}

		}

		// other property
		this->ItemType::operator=(fd);
		this->fdSubFolderNum=fd.fdSubFolderNum; // set 0
		this->fdSubItemNum=fd.fdSubItemNum;
		this->fdSubFileNum=fd.fdSubFileNum; //set 0
    this->fdParentPtr=fd.fdParentPtr;
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
			this->fdSubFolderList=new SLinkedList<FolderType>;
		}
		fd.fdSubFolderList->ResetList();
		for (int i = 0; i < fd.fdSubFolderNum; i++) {
			fd.fdSubFolderList->GetNextItem(Folder_Data);
			this->fdSubFolderList->Add(Folder_Data);
		}
	}

	//file part
	if (fd.fdSubFileNum!=0) {
		if (this->fdSubFileNum==0) {
			this->fdSubFileList=new SLinkedList<FileType>;
		}
		fd.fdSubFileList->ResetList();
		for (int i = 0; i < fd.fdSubFileNum; i++) {
			fd.fdSubFileList->GetNextItem(File_Data);
			this->fdSubFileList->Add(File_Data);
		}
	}

	//other property
	this->fdSubItemNum+=fd.fdSubItemNum;
	this->fdSubFolderNum+=fd.fdSubFolderNum;
	this->fdSubFileNum+=fd.fdSubFileNum;

	return *this;
}



// Create New Folder in Current Folder.
int FolderType::NewFolder(FolderType Temp_Folder){
	if (this->fdSubFolderNum==0) {
		this->fdSubFolderList=new SLinkedList<FolderType>; //If there is no Subfolder, then create the FolderList
	}
	std::string Temp_Name;
	int OverLapCount=0; // 수정 부분
	while (this->fdSubFolderList->Get(Temp_Folder)) {// if Folder is overlap
		if (OverLapCount==0) {
			OverLapCount++;
			Temp_Folder.SetName(Temp_Folder.GetName()+"_"+std::to_string(OverLapCount));
			Temp_Folder.SetPath(this->GetPath()+"/"+Temp_Folder.GetName()); // Set SubFolder path
			continue;
		}
		Temp_Name=Temp_Folder.GetName();
		Temp_Name.pop_back();
		OverLapCount++;
		Temp_Name+=std::to_string(OverLapCount);
		Temp_Folder.SetName(Temp_Name);
		// If Folder OverLap Set new Path
		Temp_Folder.SetPath(this->GetPath()+"/"+Temp_Folder.GetName()); // Set SubFolder path
	}

	if (this->fdSubFolderList->Add(Temp_Folder)) {
		this->fdSubFolderNum++;
		this->fdSubItemNum++;
		Temp_Folder.SetParentPtr(this); //set parent ptr this added folder
	}
	return 1;
}

// Create New File in Current Folder.
int FolderType::NewFile(FileType Temp_File){
	if (this->fdSubFileNum==0) {
		this->fdSubFileList=new SLinkedList<FileType>; //If there is no Subfile then create the FileList
	}

	std::string Temp_Name;
	int OverLapCount=0; // 수정 부분
	while (this->fdSubFileList->Get(Temp_File)) {// if File is overlap
		Temp_Name=Temp_File.GetName().substr(0,Temp_File.GetName().find('.') );
		if (OverLapCount==0) {
			OverLapCount++;
			Temp_File.SetName(Temp_Name+"_"+std::to_string(OverLapCount)+'.'+Temp_File.GetExtensions());
			Temp_File.SetPath(this->GetPath()+"/"+Temp_File.GetName()); // Set SubFolder path
			continue;
		}
		Temp_Name.pop_back();
		OverLapCount++;
		Temp_File.SetName(Temp_Name+std::to_string(OverLapCount)+'.'+Temp_File.GetExtensions());
		// If Folder OverLap Set new Path
	  Temp_File.SetPath(this->GetPath()+"/"+Temp_File.GetName()); // Set SubFolder path
	}

	if (this->fdSubFileList->Add(Temp_File)) {
		this->fdSubFileNum++;
		this->fdSubItemNum++;
	}
	return 1;
}

// Delete Folder in Current Folder.
int FolderType::DeleteFolder(FolderType Temp_Folder){
	if (this->fdSubFolderNum==0) {
		throw ItemNotFound(Temp_Folder.GetName()); // If there is no SubFolder in the Folder, Throw Error
	}

	//If Data is not in the List
	if (!this->fdSubFolderList->Get(Temp_Folder)) {
		throw ItemNotFound(Temp_Folder.GetName());
	}

	//If Data is in the List
	if(this->fdSubFolderList->Delete(Temp_Folder)){
		this->fdSubFolderNum--;
		this->fdSubItemNum--;
	}
	if (this->fdSubFolderNum==0) { // if subfoldernum 0 delete fdFolderList
		delete this->fdSubFolderList;
	}
	return 1;
}

// 	Retrieve one Folder you search in Current Folder.
int FolderType::DeleteFile(FileType Temp_File){
	if (this->fdSubFileNum==0) {
		throw ItemNotFound(Temp_File.GetName()); // If there is no SubItem in the Folder, Throw Error
	}

	//If Data is not in the List
	if (!this->fdSubFileList->Get(Temp_File)) {
		throw ItemNotFound(Temp_File.GetName());
	}

	//If Data is in the List
	if(this->fdSubFileList->Delete(Temp_File)){
		this->fdSubFileNum--;
		this->fdSubItemNum--;
	}
	if (this->fdSubFileNum==0) { // if subfoldernum 0 delete fdFolderList
		delete this->fdSubFileList;
	}
	return 1;
}

// 	Retrieve one Folder you search in Current Folder.
int FolderType::RetrieveFolderByName(FolderType& Target_Folder){

	if (this->fdSubFolderNum==0) {
		throw ItemNotFound(Target_Folder.GetName());
	}

	//If Folder is not in the Current Folder
	if (!this->fdSubFolderList->Get(Target_Folder)) {
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
	if (!this->fdSubFileList->Get(Target_File)) {
		throw ItemNotFound(Target_File.GetName());
	}
	return 1;

}

// 	Retrieve one Folder you search in Current Folder.
FolderType* FolderType::RetrieveFolderPtrByName(FolderType& Target_Folder){
	if (this->fdSubFolderNum==0) {
		throw ItemNotFound(Target_Folder.GetName());
	}

	FolderType* Target_FolderPtr;
	//If Folder is not in the Current Folder
	if (!(Target_FolderPtr=this->fdSubFolderList->GetPtr(Target_Folder))) {
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
	if (!(Target_FilePtr=this->fdSubFileList->GetPtr(Target_File))) {
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
		this->fdSubFileList->ResetList();
		for (int i = 0; i < this->fdSubFileNum; i++) {
			this->fdSubFileList->GetNextItem(Temp_File);
			if (Temp_File.GetName().find(KeyWord)!=std::string::npos) {
				Retrieve_Folders.NewFile(Temp_File);
			}
		}
	} else{
		if (this->fdSubFileNum==0) { //folder not 0 && file 0
			this->fdSubFolderList->ResetList();
			for (int i = 0; i < this->fdSubFolderNum; i++) {
				this->fdSubFolderList->GetNextItem(Temp_Folder);
				if (Temp_Folder.GetName().find(KeyWord)!=std::string::npos) {
					Retrieve_Folders.NewFolder(Temp_Folder);
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
			this->fdSubFolderList->ResetList();
			for (int i = 0; i < this->fdSubFolderNum; i++) {
				this->fdSubFolderList->GetNextItem(Temp_Folder);
				if (Temp_Folder.GetName().find(KeyWord)!=std::string::npos) {
					Retrieve_Folders.NewFolder(Temp_Folder);
				}

				// call recursive when catch error, end the loop
				try{
					Retrieve_Folders+=Temp_Folder.RetrieveItemsByName(KeyWord);
				} catch(std::exception &ex){
					continue;
				}
			}

			//File
			this->fdSubFileList->ResetList();
			for (int i = 0; i < this->fdSubFileNum; i++) {
				this->fdSubFileList->GetNextItem(Temp_File);
				if (Temp_File.GetName().find(KeyWord)!=std::string::npos) {
					Retrieve_Folders.NewFile(Temp_File);
				}
		  }
	  }
  }
	return Retrieve_Folders;
}

// Sort SubItem list
void FolderType::SortSubItems(std::string Value){

	if (this->fdSubFolderNum==0) {
		if (this->fdSubFileNum==0) { //folder && file 0
			return ;  //do nothing
		} else{ //folder 0 file not 0
			this->fdSubFileList->ResetList();
			for (int i = 0; i < this->fdSubFileNum; i++) { //문제 다꺼내서 다 키값을 맞춰야함
				this->fdSubFileList->GetNextItemPtr()->SetKeyValue(Value);
			}
			this->fdSubFileList->Sort();
		}
	} else{
		if (this->fdSubFileNum==0) { //folder not 0 file 0
			this->fdSubFolderList->ResetList();
			for (int i = 0; i < this->fdSubFolderNum; i++) {
				this->fdSubFolderList->GetNextItemPtr()->SetKeyValue(Value);
			}
			this->fdSubFolderList->Sort();
		} else{
			// folder part
			this->fdSubFolderList->ResetList();
			for (int i = 0; i < this->fdSubFolderNum; i++) {
				this->fdSubFolderList->GetNextItemPtr()->SetKeyValue(Value);
			}
			this->fdSubFolderList->Sort();

			//file part
			this->fdSubFileList->ResetList();
			for (int i = 0; i < this->fdSubFileNum; i++) { //문제 다꺼내서 다 키값을 맞춰야함
				this->fdSubFileList->GetNextItemPtr()->SetKeyValue(Value);
			}
			this->fdSubFileList->Sort();
		}
	}
	return ;

}

// Sort SubItem list
void FolderType::SortSubItems(int inKey){

	if (this->fdSubFolderNum==0) {
		if (this->fdSubFileNum==0) { //folder && file 0
			return ;  //do nothing
		} else{ //folder 0 file not 0
			this->fdSubFileList->ResetList();
			for (int i = 0; i < this->fdSubFileNum; i++) { //문제 다꺼내서 다 키값을 맞춰야함
				this->fdSubFileList->GetNextItemPtr()->SetKeyValue(inKey);
			}
			this->fdSubFileList->Sort();
		}
	} else{
		if (this->fdSubFileNum==0) { //folder not 0 file 0
			this->fdSubFolderList->ResetList();
			for (int i = 0; i < this->fdSubFolderNum; i++) {
				this->fdSubFolderList->GetNextItemPtr()->SetKeyValue(inKey);
			}
			this->fdSubFolderList->Sort();
		} else{
			// folder part
			this->fdSubFolderList->ResetList();
			for (int i = 0; i < this->fdSubFolderNum; i++) {
				this->fdSubFolderList->GetNextItemPtr()->SetKeyValue(inKey);
			}
			this->fdSubFolderList->Sort();

			//file part
			this->fdSubFileList->ResetList();
			for (int i = 0; i < this->fdSubFileNum; i++) { //문제 다꺼내서 다 키값을 맞춰야함
				this->fdSubFileList->GetNextItemPtr()->SetKeyValue(inKey);
			}
			this->fdSubFileList->Sort();
		}
	}
	return ;

}

// Display SubFolders name on screen.
void FolderType::DisplayAllSubItems(){
	FolderType Temp_Folder;
	FileType Temp_File;

	if (this->fdSubFolderNum==0) {
		if (this->fdSubFileNum==0) {//fdSubFolderNum&& file num ==0
			throw EmptyFolder();
		} else{ //folder 0 file not 0

			std::cout << "============ SubFile list ============" << '\n';
			this->fdSubFileList->ResetList();
			for (int i = 0; i < this->fdSubFileNum; i++) {
				this->fdSubFileList->GetNextItem(Temp_File);
				std::cout <<Temp_File<<'\n';
			}
			std::cout << "======================================" << '\n';
		}
	} else{
		if (this->fdSubFileNum==0) {//fdfoldernum not 0 file num 0
			std::cout << "=========== SubFolder list ===========" << '\n';
			this->fdSubFolderList->ResetList();
			for (int i = 0; i < this->fdSubFolderNum; i++) {
				this->fdSubFolderList->GetNextItem(Temp_Folder);
				std::cout <<Temp_Folder<<'\n';
			}
			std::cout << "======================================" << '\n';
		} else{//folder is not 0 file not 0

			//folder
			std::cout << "=========== SubFolder list ===========" << '\n';
			this->fdSubFolderList->ResetList();
			for (int i = 0; i < this->fdSubFolderNum; i++) {
				this->fdSubFolderList->GetNextItem(Temp_Folder);
				std::cout <<Temp_Folder<<'\n';
			}
			std::cout << "======================================" << '\n';

      //file
			std::cout << "============ SubFile list ============" << '\n';
			this->fdSubFileList->ResetList();
			for (int i = 0; i < this->fdSubFileNum; i++) {
				this->fdSubFileList->GetNextItem(Temp_File);
				std::cout <<Temp_File<<'\n';
			}
			std::cout << "======================================" << '\n';

		}
	}

}

// Display SubFolders name on screen.
void FolderType::DisplayAllSubItemsDetail(){
	FolderType Temp_Folder;
	FileType Temp_File;

	if (this->fdSubFolderNum==0) {
		if (this->fdSubFileNum==0) {//fdSubFolderNum&& file num ==0
			throw EmptyFolder();
		} else{ //folder 0 file not 0

			std::cout << "============ SubFile list ============" << '\n';
			this->fdSubFileList->ResetList();
			for (int i = 0; i < this->fdSubFileNum; i++) {
				this->fdSubFileList->GetNextItem(Temp_File);
				std::cout <<Temp_File<<"   "<<Temp_File.GetPath()<<"   "<<"1"<<"   "<<this->MakeMonthToWord(this->GetAccessTime().substr(4,2))<<" "<<this->GetAccessTime().substr(6,2)
		    <<" "<<this->MakeHourMinuteToWord(this->GetAccessTime().substr(8, 4))<<'\n';
			}
			std::cout << "======================================" << '\n';
		}
	} else{
		if (this->fdSubFileNum==0) {//fdfoldernum not 0 file num 0
			std::cout << "=========== SubFolder list ===========" << '\n';
			this->fdSubFolderList->ResetList();
			for (int i = 0; i < this->fdSubFolderNum; i++) {
				this->fdSubFolderList->GetNextItem(Temp_Folder);
				std::cout <<Temp_Folder<<"   "<<Temp_Folder.GetPath()<<"   "<<Temp_Folder.GetSubItemrNum()<<"   "<<this->MakeMonthToWord(this->GetAccessTime().substr(4,2))<<" "<<this->GetAccessTime().substr(6,2)
		    <<" "<<this->MakeHourMinuteToWord(this->GetAccessTime().substr(8, 4))<<" "<<'\n';
			}
			std::cout << "======================================" << '\n';
		} else{//folder is not 0 file not 0

			//folder
			std::cout << "=========== SubFolder list ===========" << '\n';
			this->fdSubFolderList->ResetList();
			for (int i = 0; i < this->fdSubFolderNum; i++) {
				this->fdSubFolderList->GetNextItem(Temp_Folder);
				std::cout <<Temp_Folder<<"   "<<Temp_Folder.GetPath()<<"   "<<Temp_Folder.GetSubItemrNum()<<"   "<<this->MakeMonthToWord(this->GetAccessTime().substr(4,2))<<" "<<this->GetAccessTime().substr(6,2)
		    <<" "<<this->MakeHourMinuteToWord(this->GetAccessTime().substr(8, 4))<<" "<<'\n';
			}
			std::cout << "======================================" << '\n';

      //file
			std::cout << "============ SubFile list ============" << '\n';
			this->fdSubFileList->ResetList();
			for (int i = 0; i < this->fdSubFileNum; i++) {
				this->fdSubFileList->GetNextItem(Temp_File);
				std::cout <<Temp_File<<"   "<<Temp_File.GetPath()<<"   "<<"1"<<"   "<<this->MakeMonthToWord(this->GetAccessTime().substr(4,2))<<" "<<this->GetAccessTime().substr(6,2)
		    <<" "<<this->MakeHourMinuteToWord(this->GetAccessTime().substr(8, 4))<<'\n';
			}
			std::cout << "======================================" << '\n';

		}
	}
}

// Reset all items key
void FolderType::ResetFolderKey(){
	if (this->fdSubFolderNum==0) {
		if (this->fdSubFileNum==0) { //folder && file 0
			return ;  //do nothing
		} else{ //folder 0 file not 0
			this->fdSubFileList->ResetList();
			for (int i = 0; i < this->fdSubFileNum; i++) { //문제 다꺼내서 다 키값을 맞춰야함
				this->fdSubFileList->GetNextItemPtr()->SetKeyValue(0);
			}
		}
	} else{
		if (this->fdSubFileNum==0) { //folder not 0 file 0
			this->fdSubFolderList->ResetList();
			for (int i = 0; i < this->fdSubFolderNum; i++) {
				this->fdSubFolderList->GetNextItemPtr()->SetKeyValue(0);
			}
		} else{
			// folder part
			this->fdSubFolderList->ResetList();
			for (int i = 0; i < this->fdSubFolderNum; i++) {
				this->fdSubFolderList->GetNextItemPtr()->SetKeyValue(0);
			}

			//file part
			this->fdSubFileList->ResetList();
			for (int i = 0; i < this->fdSubFileNum; i++) { //문제 다꺼내서 다 키값을 맞춰야함
				this->fdSubFileList->GetNextItemPtr()->SetKeyValue(0);
			}
		}
	}
	return ;
}

/*
void FolderType::MakeDisplayQueue(LinkedQueue<ItemType*> &LQueue){
	FolderType Temp_Folder;
	FileType Temp_File;
	LinkedQueue<ItemType*> Temp_Queue;

	this->fdSubFolderList->ResetList();
	this->fdSubFileList->ResetList();
	while (1) {
		this->fdSubFolderList->GetNextItem(Temp_Folder);
		this->fdSubFileList->GetNextItem(Temp_File);
		if (Temp_Folder<Temp_File) {
			LQueue.EnQueue(&Temp_Folder);
			Temp_Queue.EnQueue(&Temp_File);
		}

	}
	this->fdSubFolderList->ResetList();
	this->fdSubFileList->ResetList();
	for (int i =0; i < this->fdSubFolderNum; i++) {
		this->fdSubFileList->GetNextItem(Temp_File);
	}
	for (int i = 0; i < this->fdSubFileNum; i++) {
		this->fdSubFolderList->GetNextItem(Temp_Folder);
		this->fdSubFileList->GetNextItem(Temp_File);
	}

}
*/
