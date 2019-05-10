#include "FolderType.hpp"

//Doing Deep copy by copy assignment operator.
FolderType& FolderType::operator= (const FolderType& fd){
	if (this!=&fd) {
		if (fd.fdSubItemNum!=0) { //initialize
			this->MakeEmptyFolder();
		}

		if (fd.fdSubItemNum!=0) {
			this->fdSubItemList=new DSLinkedList<ItemType*>;
			DoublyIterator<ItemType*>iter(*fd.fdSubItemList);
			ItemType* Copy_Folder; //for copy folder
			iter.Next(); // move iterator next
			while (!iter.IsTail()) {
				if (iter.Cur()->WhatIs()=="File") { // file type
					iter.Cur()->SetPath(fd.GetPath()+"/"+iter.Cur()->GetName());
					this->fdSubItemList->Add(iter.Cur());
				} else if (iter.Cur()->WhatIs()=="Folder"){ // folder type
					if (iter.Cur()->GetSubItemNum()!=0) { //if folder has sub items
						*dynamic_cast<FolderType*>(Copy_Folder) = *dynamic_cast<FolderType*>(iter.Cur()); // call recursive operator =
						Copy_Folder->SetPath(fd.GetPath()+"/"+Copy_Folder->GetName());
						this->fdSubItemList->Add(Copy_Folder);
					} else {
						iter.Cur()->SetPath(fd.GetPath()+"/"+iter.Cur()->GetName());
						this->fdSubItemList->Add(iter.Cur());
					}
					iter.Next(); //move iterator
				}
			}
		}

		// other property
		this->ItemType::operator=(fd);
		this->fdSubItemNum=fd.fdSubItemNum;
    this->fdParentPtr=fd.fdParentPtr;
  }
	return *this;
}

// Doing combine two different folder.
FolderType& FolderType::operator+=(const FolderType &fd){

	if (fd.fdSubItemNum!=0) { // if fd has subitems
		if (this->fdSubItemNum==0) { // and if this has no sub item
			this->fdSubItemList=new DSLinkedList<ItemType*>;
		}
		DoublyIterator<ItemType*> iter(*fd.fdSubItemList);
		while (!iter.NextIsTail()) {
			this->fdSubItemList->Add(iter.Next());
		}
	}
	//other property
	this->fdSubItemNum+=fd.fdSubItemNum;
	return *this;
}



// Create New Folder in Current Folder.
int FolderType::NewItem(ItemType* Temp_Item){
	if (this->fdSubItemNum==0) {
		this->fdSubItemList=new DSLinkedList<ItemType*>; //If there is no SubItem, then create the FolderList
	}
	std::string Temp_Name;
	int OverLapCount=0; // 수정 부분
	while (this->fdSubItemList->Get(Temp_Item)) {// if item is overlap
		if (Temp_Item->WhatIs()=="Folder") { //folder part
			if (OverLapCount==0) {
				OverLapCount++;
				Temp_Item->SetName(Temp_Item->GetName()+"_"+std::to_string(OverLapCount));
				Temp_Item->SetPath(this->GetPath()+"/"+Temp_Item->GetName()); // Set SubFolder path
				continue;
			}
			Temp_Name=Temp_Item->GetName();
			Temp_Name.pop_back();
			OverLapCount++;
			Temp_Name+=std::to_string(OverLapCount);
			Temp_Item->SetName(Temp_Name);
			// If Folder OverLap Set new Path
			Temp_Item->SetPath(this->GetPath()+"/"+Temp_Item->GetName()); // Set SubFolder path

		} else if (Temp_Item->WhatIs().find("File")!=std::string::npos){// if file

			Temp_Name=Temp_Item->GetName().substr(0,Temp_Item->GetName().find('.') );
			if (OverLapCount==0) {
				OverLapCount++;
				Temp_Item->SetName(Temp_Name+"_"+std::to_string(OverLapCount)+'.'+dynamic_cast<FileType*>(Temp_Item)->GetExtensions());
				Temp_Item->SetPath(this->GetPath()+"/"+Temp_Item->GetName()); // Set SubFolder path
				continue;
			}
			Temp_Name.pop_back();
			OverLapCount++;
			Temp_Item->SetName(Temp_Name+std::to_string(OverLapCount)+'.'+dynamic_cast<FileType*>(Temp_Item)->GetExtensions());
			// If Folder OverLap Set new Path
			Temp_Item->SetPath(this->GetPath()+"/"+Temp_Item->GetName()); // Set SubFolder path

		}
	}

	if (this->fdSubItemList->Add(Temp_Item)) {
		this->fdSubItemNum++;
		if (Temp_Item->WhatIs()=="Folder") {
			dynamic_cast<FolderType*>(Temp_Item)->SetParentPtr(this); //set parent ptr this added folder
		}
	}
	return 1;
}

// Delete Folder in Current Folder.
int FolderType::DeleteItem(ItemType* Temp_Item){
	if (this->fdSubItemNum==0) {
		throw ItemNotFound(Temp_Item->GetName()); // If there is no SubItem in the Folder, Throw Error
	}

	//If Data is not in the List
	if (!this->fdSubItemList->Get(Temp_Item)) {
		throw ItemNotFound(Temp_Item->GetName());
	}

	//If Data is in the List
	if(this->fdSubItemList->Delete(Temp_Item)){
		this->fdSubItemNum--;
	}
	if (this->fdSubItemNum==0) { // if subfoldernum 0 delete fdFolderList
		delete this->fdSubItemList;
	}
	return 1;
}

// 	Retrieve one Folder you search in Current Folder.
int FolderType::RetrieveItemByName(ItemType* Target_Item){

	if (this->fdSubItemNum==0) {
		throw ItemNotFound(Target_Item->GetName());
	}

	//If Folder is not in the Current Folder
	if (!this->fdSubItemList->Get(Target_Item)) {
		throw ItemNotFound(Target_Item->GetName());
	}
	return 1;
}

// Retrieve the pointer of the one File you search in Current Folder.
ItemType** FolderType::RetrieveItemPtrByName(ItemType*& Target_Item){
	if (this->fdSubItemNum==0) {
		throw ItemNotFound(Target_Item->GetName());
	}

	ItemType** Target_ItemPtr;
	//If File is not in the Current Folder
	if (!(Target_ItemPtr=this->fdSubItemList->GetPtr(Target_Item))) {
		throw ItemNotFound(Target_Item->GetName());
	}
	return Target_ItemPtr;
}
// Retrieve all SubItems that contain the name you search in All child folder.
FolderType FolderType::RetrieveItemsByName(std::string KeyWord){

	FolderType Retrieve_Folder;
	if (this->fdSubItemNum==0) {
		throw EmptyFolder();
		DoublyIterator<ItemType*> iter(*this->fdSubItemList);
		if (iter.Next()->GetName().find(KeyWord)!=std::string::npos) {
			Retrieve_Folder.NewItem(iter.Cur());
		}
		// call recursive when catch, end the loop
		Retrieve_Folder+=dynamic_cast<FolderType*>(iter.Cur())->RetrieveItemsByName(KeyWord);
	}

	return Retrieve_Folder;
}

// Sort SubItem list
void FolderType::SortSubItems(std::string Value){

	if (this->fdSubItemNum==0) {
		return ; //do nothing
	}
	DoublyIterator<ItemType*> iter(*this->fdSubItemList);
	while (!iter.NextIsTail()) {//문제 다꺼내서 다 키값을 맞춰야함
		iter.Next()->SetKeyValue(Value);
	}
	this->fdSubItemList->Sort();
	return ;

}

// Sort SubItem list
void FolderType::SortSubItems(int inKey){

	if (this->fdSubItemNum==0) {
		return ; //do nothing
	}
	DoublyIterator<ItemType*> iter(*this->fdSubItemList);
	while (!iter.NextIsTail()) {//문제 다꺼내서 다 키값을 맞춰야함
		iter.Next()->SetKeyValue(inKey);
	}
	this->fdSubItemList->Sort();
	return ;


}

// Display SubFolders name on screen.
void FolderType::DisplayAllSubItems(){
	if (this->fdSubItemNum==0) {
		throw EmptyFolder();
	}
	std::cout << "============ SubItem list ============" << '\n';
	DoublyIterator<ItemType*> iter(*this->fdSubItemList);
	while (!iter.NextIsTail()) {
		std::cout << *iter.Next() << '\n';
	}
	std::cout << "======================================" << '\n';
}

// Display SubFolders name on screen.
void FolderType::DisplayAllSubItemsDetail(){
	if (this->fdSubItemNum==0) {
		throw EmptyFolder();
	}
	std::cout << "============ SubItem list ============" << '\n';
	DoublyIterator<ItemType*> iter(*this->fdSubItemList);
	while (!iter.NextIsTail()) {
		if (iter.Next()->WhatIs()=="File") { // if File
			std::cout << iter.Cur() <<"   "<<iter.Cur()->GetPath()<<"   "<<"1"<<"   "<<this->MakeMonthToWord(iter.Cur()->GetAccessTime().substr(4,2))<<" "<<iter.Cur()->GetAccessTime().substr(6,2)
			<<" "<<this->MakeHourMinuteToWord(iter.Cur()->GetAccessTime().substr(8, 4))<<" "<<'\n';
		} else{
			std::cout << iter.Cur() <<"   "<<iter.Cur()->GetPath()<<"   "<<iter.Cur()->GetSubItemNum()<<"   "<<this->MakeMonthToWord(iter.Cur()->GetAccessTime().substr(4,2))<<" "<<iter.Cur()->GetAccessTime().substr(6,2)
			<<" "<<this->MakeHourMinuteToWord(iter.Cur()->GetAccessTime().substr(8, 4))<<" "<<'\n';
		}
	}
	std::cout << "======================================" << '\n';
}

// Reset all items key
void FolderType::ResetFolderKey(){
	if (this->fdSubItemNum==0) {
		return; //do nothing;
	}

	DoublyIterator<ItemType*> iter(*this->fdSubItemList);
	while (!iter.NextIsTail()) { //문제 다꺼내서 다 키값을 맞춰야함
		iter.Next()->SetKeyValue(0);
	}
	return ;
}
