#include "FolderType.hpp"

//Doing Deep copy by copy assignment operator.
FolderType& FolderType::operator= (const FolderType& fd){
	if (this!=&fd) {
		if (fd.fdSubItemNum!=0) { //initialize
			this->MakeEmptyFolder();
		}

		//file part
		if (fd.fdSubFileNum!=0) {
			this->fdSubFileList=new DSLinkedList<FileType>;
			DoublyIterator<FileType>fi_iter(*fd.fdSubFileList);
			while (!fi_iter.NextIsTail()) {
				fi_iter.Next().SetPath(fd.GetPath()+"/"+fi_iter.Cur().GetName());
				this->fdSubFileList->Add(fi_iter.Cur());
			}
	  }

		//folder part
		FolderType Copy_Folder;
		if (fd.fdSubFolderNum!=0) {
			this->fdSubFolderList=new DSLinkedList<FolderType>;
			DoublyIterator<FolderType>fd_iter(*fd.fdSubFolderList);
      while (!fd_iter.NextIsTail()) {
        if (fd_iter.Next().GetSubItemNum()!=0) {
          Copy_Folder=fd_iter.Cur();
          Copy_Folder.SetPath(fd.GetPath()+"/"+Copy_Folder.GetName());
          this->fdSubFolderList->Add(Copy_Folder);
        } else{
          fd_iter.Cur().SetPath(fd.GetPath()+"/"+fd_iter.Cur().GetName());
          this->fdSubFolderList->Add(fd_iter.Cur());
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
			this->fdSubFolderList=new DSLinkedList<FolderType>;
		}
		DoublyIterator<FolderType> fd_iter(*fd.fdSubFolderList);
		while (!fd_iter.NextIsTail()) {
			this->fdSubFolderList->Add(fd_iter.Next());
		}
	}

	//file part
	if (fd.fdSubFileNum!=0) {
		if (this->fdSubFileNum==0) {
			this->fdSubFileList=new DSLinkedList<FileType>;
		}
		DoublyIterator<FileType> fi_iter(*fd.fdSubFileList);
		while (!fi_iter.NextIsTail()) {
			this->fdSubFileList->Add(fi_iter.Next());
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
		this->fdSubFolderList=new DSLinkedList<FolderType>; //If there is no Subfolder, then create the FolderList
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
		this->fdSubFileList=new DSLinkedList<FileType>; //If there is no Subfile then create the FileList
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
	if (this->fdSubFolderNum==0) {
		if (this->fdSubFileNum==0) { //folder && file 0
			throw EmptyFolder();
		}
		// folder 0 && file not 0, no sub folder
		DoublyIterator<FileType> fi_iter(*this->fdSubFileList);
		while (!fi_iter.NextIsTail()) {
			if (fi_iter.Next().GetName().find(KeyWord)!=std::string::npos) {
				Retrieve_Folders.NewFile(fi_iter.Cur());
			}
		}
	} else{
		if (this->fdSubFileNum==0) { //folder not 0 && file 0
			DoublyIterator<FolderType> fd_iter(*this->fdSubFolderList);
			while (!fd_iter.NextIsTail()) {
				if (fd_iter.Next().GetName().find(KeyWord)!=std::string::npos) {
					Retrieve_Folders.NewFolder(fd_iter.Cur());
				}
				// call recursive when catch, end the loop
				try{
					Retrieve_Folders+=fd_iter.Cur().RetrieveItemsByName(KeyWord);
				} catch(std::exception &ex){
					continue;
				}
			}
		} else{ // folder && file not 0
			//Folder
			DoublyIterator<FolderType> fd_iter(*this->fdSubFolderList);
			while (!fd_iter.NextIsTail()) {
				if (fd_iter.Next().GetName().find(KeyWord)!=std::string::npos) {
					Retrieve_Folders.NewFolder(fd_iter.Cur());
				}
				// call recursive when catch, end the loop
				try{
					Retrieve_Folders+=fd_iter.Cur().RetrieveItemsByName(KeyWord);
				} catch(std::exception &ex){
					continue;
				}
			}

			//File
			DoublyIterator<FileType> fi_iter(*this->fdSubFileList);
			while (!fi_iter.NextIsTail()) {
				if (fi_iter.Next().GetName().find(KeyWord)!=std::string::npos) {
					Retrieve_Folders.NewFile(fi_iter.Cur());
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
			DoublyIterator<FileType> fi_iter(*this->fdSubFileList);
			while (!fi_iter.NextIsTail()) { //문제 다꺼내서 다 키값을 맞춰야함
				fi_iter.NextPtr()->SetKeyValue(Value);
			}
			this->fdSubFileList->Sort();
		}
	} else{
		if (this->fdSubFileNum==0) { //folder not 0 file 0
			DoublyIterator<FolderType> fd_iter(*this->fdSubFolderList);
			while (!fd_iter.NextIsTail()) { //문제 다꺼내서 다 키값을 맞춰야함
				fd_iter.NextPtr()->SetKeyValue(Value);
			}
			this->fdSubFolderList->Sort();
		} else{
			// folder part
			DoublyIterator<FolderType> fd_iter(*this->fdSubFolderList);
			while (!fd_iter.NextIsTail()) { //문제 다꺼내서 다 키값을 맞춰야함
				fd_iter.NextPtr()->SetKeyValue(Value);
			}
			this->fdSubFolderList->Sort();

			//file part
			DoublyIterator<FileType> fi_iter(*this->fdSubFileList);
			while (!fi_iter.NextIsTail()) { //문제 다꺼내서 다 키값을 맞춰야함
				fi_iter.NextPtr()->SetKeyValue(Value);
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
			DoublyIterator<FileType> fi_iter(*this->fdSubFileList);
			while (!fi_iter.NextIsTail()) { //문제 다꺼내서 다 키값을 맞춰야함
				fi_iter.NextPtr()->SetKeyValue(inKey);
			}
			this->fdSubFileList->Sort();
		}
	} else{
		if (this->fdSubFileNum==0) { //folder not 0 file 0
			DoublyIterator<FolderType> fd_iter(*this->fdSubFolderList);
			while (!fd_iter.NextIsTail()) { //문제 다꺼내서 다 키값을 맞춰야함
				fd_iter.NextPtr()->SetKeyValue(inKey);
			}
			this->fdSubFolderList->Sort();
		} else{
			// folder part
			DoublyIterator<FolderType> fd_iter(*this->fdSubFolderList);
			while (!fd_iter.NextIsTail()) { //문제 다꺼내서 다 키값을 맞춰야함
				fd_iter.NextPtr()->SetKeyValue(inKey);
			}
			this->fdSubFolderList->Sort();

			//file part
			DoublyIterator<FileType> fi_iter(*this->fdSubFileList);
			while (!fi_iter.NextIsTail()) { //문제 다꺼내서 다 키값을 맞춰야함
				fi_iter.NextPtr()->SetKeyValue(inKey);
			}
			this->fdSubFileList->Sort();
		}
	}
	return ;

}

// Display SubFolders name on screen.
void FolderType::DisplayAllSubItems(){
	if (this->fdSubFolderNum==0) {
		if (this->fdSubFileNum==0) {//fdSubFolderNum&& file num ==0
			throw EmptyFolder();
		} else{ //folder 0 file not 0

			std::cout << "============ SubFile list ============" << '\n';
			DoublyIterator<FileType> fi_iter(*this->fdSubFileList);
			while (!fi_iter.NextIsTail()) {
				std::cout << fi_iter.Next() << '\n';
			}
			std::cout << "======================================" << '\n';
		}
	} else{
		if (this->fdSubFileNum==0) {//fdfoldernum not 0 file num 0
			std::cout << "=========== SubFolder list ===========" << '\n';
			DoublyIterator<FolderType> fd_iter(*this->fdSubFolderList);
			while (!fd_iter.NextIsTail()) {
				std::cout << fd_iter.Next() << '\n';
			}
			std::cout << "======================================" << '\n';
		} else{//folder is not 0 file not 0

			//folder
			std::cout << "=========== SubFolder list ===========" << '\n';
			DoublyIterator<FolderType> fd_iter(*this->fdSubFolderList);
			while (!fd_iter.NextIsTail()) {
				std::cout << fd_iter.Next() << '\n';
			}
			std::cout << "======================================" << '\n';

      //file
			std::cout << "============ SubFile list ============" << '\n';
			DoublyIterator<FileType> fi_iter(*this->fdSubFileList);
			while (!fi_iter.NextIsTail()) {
				std::cout << fi_iter.Next() << '\n';
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
			DoublyIterator<FileType> fi_iter(*this->fdSubFileList);
			while (!fi_iter.NextIsTail()) {
				std::cout << fi_iter.Next() <<"   "<<fi_iter.Cur().GetPath()<<"   "<<"1"<<"   "<<this->MakeMonthToWord(fi_iter.Cur().GetAccessTime().substr(4,2))<<" "<<fi_iter.Cur().GetAccessTime().substr(6,2)
		    <<" "<<this->MakeHourMinuteToWord(fi_iter.Cur().GetAccessTime().substr(8, 4))<<" "<<'\n';
			}
			std::cout << "======================================" << '\n';
		}
	} else{
		if (this->fdSubFileNum==0) {//fdfoldernum not 0 file num 0
			std::cout << "=========== SubFolder list ===========" << '\n';
			DoublyIterator<FolderType> fd_iter(*this->fdSubFolderList);
			while (!fd_iter.NextIsTail()) {
				std::cout << fd_iter.Next() <<"   "<<fd_iter.Cur().GetPath()<<"   "<<fd_iter.Cur().GetSubItemNum()<<"   "<<this->MakeMonthToWord(fd_iter.Cur().GetAccessTime().substr(4,2))<<" "<<fd_iter.Cur().GetAccessTime().substr(6,2)
		    <<" "<<this->MakeHourMinuteToWord(fd_iter.Cur().GetAccessTime().substr(8, 4))<<" "<<'\n';
			}
			std::cout << "======================================" << '\n';
		} else{//folder is not 0 file not 0

			//folder
			std::cout << "=========== SubFolder list ===========" << '\n';
			DoublyIterator<FolderType> fd_iter(*this->fdSubFolderList);
			while (!fd_iter.NextIsTail()) { //문제 다꺼내서 다 키값을 맞춰야함
				std::cout << fd_iter.Next() <<"   "<<fd_iter.Cur().GetPath()<<"   "<<fd_iter.Cur().GetSubItemNum()<<"   "<<this->MakeMonthToWord(fd_iter.Cur().GetAccessTime().substr(4,2))<<" "<<fd_iter.Cur().GetAccessTime().substr(6,2)
		    <<" "<<this->MakeHourMinuteToWord(fd_iter.Cur().GetAccessTime().substr(8, 4))<<" "<<'\n';
			}
			std::cout << "======================================" << '\n';

      //file
			std::cout << "============ SubFile list ============" << '\n';
			DoublyIterator<FileType> fi_iter(*this->fdSubFileList);
			while (!fi_iter.NextIsTail()) {
				std::cout << fi_iter.Next() <<"   "<<fi_iter.Cur().GetPath()<<"   "<<"1"<<"   "<<this->MakeMonthToWord(fi_iter.Cur().GetAccessTime().substr(4,2))<<" "<<fi_iter.Cur().GetAccessTime().substr(6,2)
		    <<" "<<this->MakeHourMinuteToWord(fi_iter.Cur().GetAccessTime().substr(8, 4))<<" "<<'\n';
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
			DoublyIterator<FileType> fi_iter(*this->fdSubFileList);
			while (!fi_iter.NextIsTail()) { //문제 다꺼내서 다 키값을 맞춰야함
				fi_iter.NextPtr()->SetKeyValue(0);
			}
		}
	} else{
		if (this->fdSubFileNum==0) { //folder not 0 file 0
			DoublyIterator<FolderType> fd_iter(*this->fdSubFolderList);
			while (!fd_iter.NextIsTail()) { //문제 다꺼내서 다 키값을 맞춰야함
				fd_iter.NextPtr()->SetKeyValue(0);
			}
		} else{
			// folder part
			DoublyIterator<FolderType> fd_iter(*this->fdSubFolderList);
			while (!fd_iter.NextIsTail()) { //문제 다꺼내서 다 키값을 맞춰야함
				fd_iter.NextPtr()->SetKeyValue(0);
			}

			//file part
			DoublyIterator<FileType> fi_iter(*this->fdSubFileList);
			while (!fi_iter.NextIsTail()) { //문제 다꺼내서 다 키값을 맞춰야함
				fi_iter.NextPtr()->SetKeyValue(0);
			}
		}
	}
	return ;
}
