#include "Application.hpp"


// Program driver.
void Application::Run(){
	while ((this->m_Command = GetCommand())){
		switch (this->m_Command){
			case 1:		// created Items				'
				this->NewItem();
				break;
			case 2:
				this->DeleteItem(); // delete Items
				break;
			case 3:
				this->UpdateItemName(); // update Items
				break;
			case 4:		// change directory
				this->ChangeDirectory();
				break;
			case 5:		// Run file
				this->RunFile();
				break;
			case 6:		// retrieve Items
				this->RetrieveItemsByName();
				break;
			case 7:		// Display All Items in Recently folder
			  this->DisplayRecentlyItems();
				break;
			case 8:		// Display current folder information
				this->DisplayInfo();
				break;
			case 0:
			  std::cout << "\t Exit Program..." << '\n';
				return;
		}
	}
}

// Display command on screen and get a input from keyboard.
int Application::GetCommand(){
	int command;
	while (1) {
		try{
			std::cout << std::endl << std::endl;
			this->m_fdCurPointer->DisplayPathOnScreen();
			std::cout << '\n' << '\n';
			std::cout << "\t ===== Current Folder List =====" << '\n';
			this->DisplayAllItems();
			std::cout << "\t ===============================" << '\n';
			std::cout << std::endl << std::endl;
			std::cout << "\t---ID -- Command ------ " << std::endl;
			std::cout << "\t   1 : New Item" << std::endl;
			std::cout << "\t   2 : Delete Item" << std::endl;
			std::cout << "\t   3 : Update Item(Name)" << std::endl;
			std::cout << "\t   4 : Change Directory" << std::endl;
			std::cout << "\t   5 : Run File" << std::endl;
			std::cout << "\t   6 : Retrieve Items" << std::endl;
			std::cout << "\t   7 : Display Recently" << std::endl;
			std::cout << "\t   8 : Display Info" << std::endl;
			std::cout << "\t   0 : Quit" << std::endl;
			std::cout << std::endl << "\t Choose a Command--> ";
			if ((std::cin.fail()) || !(std::cin >> command) || command < 0 || command>8){   // input fail or input value is out of bound
			  std::cin.clear();   //clear flag
			  std::cin.ignore(INT_MAX, '\n');   //empty input buffer
				throw InvalidOperation();
			}
			else {
			  std::cin.clear();  // clear flag
			  std::cin.ignore(INT_MAX, '\n');  // empty input buffer
			  return command;
			}
		} catch(std::exception &ex){
			std::cout << ex.what() << '\n';
			continue;
		}
	}
}

// Check ItemType and Value is right.
int Application::CheckValueItemType(std::string Value){
	//파일 입력할 때 .txt 직접 입력
	// check name error finish , then check file or folder
	if ((Value.find(".")!=std::string::npos)) { // if no find .(extensions) it is file
		return 0;
	}
	return 1; // it is folder
}

// Create New Item in Current Folder.
int Application::NewItem(){
	try{
		std::string Item_Name;
		// set the item name to create
		std::cout << "\t Enter the item name to create" << '\n';
		std::cout << "\t Name : ";
		std::cin >> Item_Name;
		FileType Temp_File;
		FolderType Temp_Folder;
		switch (this->CheckValueItemType(Item_Name)) {
			case 0://file
			//set the file info to add
			Temp_File.SetName(Item_Name); // Set SubFile Name
			Temp_File.SetPath(this->m_fdCurPointer->GetPath()+"/"+Item_Name); // Set SubFile Path
			if (this->m_fdCurPointer->AddFile(Temp_File)) {
				return 1; //Create New file
			}
			break;
			case 1://folder
			//set the folder info to add
			Temp_Folder.SetName(Item_Name); // Set SubFolder Name
			Temp_Folder.SetPath(this->m_fdCurPointer->GetPath()+"/"+Item_Name); // Set SubFolder Path
			if (this->m_fdCurPointer->AddFolder(Temp_Folder)) {
				return 1; //Create New Folder
			}
			break;
		}
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
	}
	return 0;
}

// Delete Folder you search in Current Folder.
int Application::DeleteItem(){
	try{
		std::string Item_Name;

		// set the item name to delete
		std::cout << "\t Enter the item name to delete" << '\n';
		std::cout << "\t Name : ";
		std::cin >> Item_Name;
		FileType Temp_File;
		FolderType Temp_Folder;

		switch (this->CheckValueItemType(Item_Name)) {
			case 0://file
			//set the file info to delete
			Temp_File.SetName(Item_Name); // Set SubFile Name
			Temp_File.SetPath(this->m_fdCurPointer->GetPath()+"/"+Item_Name); // Set SubFile Path
			if (this->m_fdCurPointer->DeleteFile(Temp_File)) {
				return 1; //Create New file
			}
			break;
			case 1://folder
			//set the folder info to delete
			Temp_Folder.SetName(Item_Name); // Set SubFolder Name
			Temp_Folder.SetPath(this->m_fdCurPointer->GetPath()+"/"+Item_Name); // Set SubFolder Path
			if (this->m_fdCurPointer->DeleteFolder(Temp_Folder)) {
				return 1; //Delete Folder
			}
			break;
		}
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
	}
	return 0;
}

// Update Item Name you search in Current Folder.
int Application::UpdateItemName(){
	try{
		std::string Item_Name;
		std::string Change_Name;

		// set the item name to delete
		std::cout << "\t Enter the item name to update" << '\n';
		std::cout << "\t Name : ";
		std::cin >> Item_Name;
		FileType Temp_File;
		FileType* Temp_FilePtr;
		FolderType Temp_Folder;
		FolderType* Temp_FolderPtr;

		switch (this->CheckValueItemType(Item_Name)) {
			case 0://file
			//set the file info to update
			Temp_File.SetName(Item_Name); // Set SubFile Name
			Temp_File.SetPath(this->m_fdCurPointer->GetPath()+"/"+Item_Name); // Set SubFile Path
			if ((Temp_FilePtr=this->m_fdCurPointer->RetrieveFilePtrByName(Temp_File))) {
				// set the item name to change
				std::cout << "\t Enter the item name to change" << '\n';
				std::cout << "\t Name : ";
				std::cin >> Change_Name;
				if (this->CheckValueItemType(Change_Name)==1) {
					throw NameError(Change_Name);
				}
				Temp_FilePtr->SetName(Change_Name);
				Temp_FilePtr->SetPath(this->m_fdCurPointer->GetPath()+"/"+Change_Name);
				return 1; //Create New file
			}
			break;
			case 1://folder
			//set the folder info to update
			Temp_Folder.SetName(Item_Name); // Set SubFolder Name
			Temp_Folder.SetPath(this->m_fdCurPointer->GetPath()+"/"+Item_Name); // Set SubFolder Path
			if ((Temp_FolderPtr=this->m_fdCurPointer->RetrieveFolderPtrByName(Temp_Folder))) {
				// set the item name to change
				std::cout << "\t Enter the item name to change" << '\n';
				std::cout << "\t Name : ";
				std::cin >> Change_Name;
				if (this->CheckValueItemType(Change_Name)==0) {
					throw NameError(Change_Name);
				}
				Temp_FolderPtr->SetName(Change_Name);
				Temp_FolderPtr->SetPath(this->m_fdCurPointer->GetPath()+"/"+Change_Name);
				return 1; //Create New Folder
			}
			break;
		}
	} catch (std::exception &ex){
		std::cout << ex.what() << '\n';
	}
	return 0;
}


// Change current dircectory you want.
int Application::ChangeDirectory(){
	try {
		int key;
		std::cout << std::endl << std::endl;
		std::cout << "\t---ID -- Command -------- " << std::endl;
		std::cout << "\t   1 : Go to folder name" << std::endl;
		std::cout << "\t   2 : Go to Parent" << std::endl;
		std::cout << "\t   3 : Go to Root" << std::endl;
		std::cout << std::endl << "\t Choose a Command--> ";
		if ((std::cin.fail()) || !(std::cin >> key) || key < 0 || key>4){   // input fail or input value is out of bound
			std::cin.clear();   //clear flag
			std::cin.ignore(INT_MAX, '\n');   //empty input buffer
			throw InvalidOperation();
		}
		else {
			std::cin.clear();  // clear flag
			std::cin.ignore(INT_MAX, '\n');  // empty input buffer
		}
		//set the folder name to find
		FolderType Temp_Folder;
		FolderType* Temp_FolderPtr;
		switch (key) {
			case 1:
			  Temp_Folder.SetNameFromKB();
				Temp_Folder.SetPath(this->m_fdCurPointer->GetPath()+"/"+Temp_Folder.GetName());
			  if((Temp_FolderPtr=this->m_fdCurPointer->RetrieveFolderPtrByName(Temp_Folder))){
				  this->m_ParentFolder.Push(this->m_fdCurPointer);
				  this->m_fdCurPointer=Temp_FolderPtr;
				  this->AddRecentlyFolder(this->m_fdCurPointer);
		    }
			  break;
			case 2:
			  if (!this->m_ParentFolder.IsEmpty()) { // If history exists
				  this->m_fdCurPointer=this->m_ParentFolder.Top();
				  this->m_ParentFolder.Pop();
				  this->AddRecentlyFolder(this->m_fdCurPointer);
			  }else{
					throw NoHistory(); // if there is no parent folder throw no history
				}
			  break;
			case 3:
			  this->m_fdCurPointer=&this->Root;
				this->m_ParentFolder.MakeEmpty(); //Root has no parent folder
				Temp_Folder=this->Root;
			  this->AddRecentlyFolder(this->m_fdCurPointer); // AddRecentlyFolder get parameter for reference, assign temp
			  break;
	  }
		return 1;
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
		return 0;
	}
}

int Application::RunFile(){
	try{
		std::string Item_Name;
		// set the item name to create
		std::cout << "\t Enter the file name to run" << '\n';
		std::cout << "\t Name : ";
		std::cin >> Item_Name;
		if (this->CheckValueItemType(Item_Name)==1) {
			throw NameError(Item_Name);
		}
		FileType Target_File;
		FileType* Target_FilePtr;
		Target_File.SetName(Item_Name); // Set SubFile Name
		Target_File.SetPath(this->m_fdCurPointer->GetPath()+"/"+Item_Name); // Set SubFile Path
		if ((Target_FilePtr=this->m_fdCurPointer->RetrieveFilePtrByName(Target_File))) {
			Target_File.Run();
		}
		this->AddRecentlyFile(Target_FilePtr);
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
	}
	return 0;

}

// Retrieve and Display all Items that contain the name in all Child Folder.
int Application::RetrieveItemsByName(){
	FolderType Retrieve_Folder;

	std::string KeyWord;
	std::cout << "\t Enter the Word to Search : ";
	std::cin >> KeyWord;
	Retrieve_Folder=this->m_fdCurPointer->RetrieveItemsByName(KeyWord);

	std::cout << "\t =====  Search Item List =====" << '\n';
	if (Retrieve_Folder.GetSubFolderNum()==0) {
		if (Retrieve_Folder.GetSubFileNum()==0) { //folder && file 0
			std::cout << "\t No Result" << '\n';
		} else{ // folder 0, file not 0
			Retrieve_Folder.DisplayAllSubFiles();
		}
	} else{
		if (Retrieve_Folder.GetSubFileNum()==0) { //folder not 0, file 0
			Retrieve_Folder.DisplayAllSubFolders();
		} else{ // folder && file not 0
			Retrieve_Folder.DisplayAllSubFolders();
			Retrieve_Folder.DisplayAllSubFiles();
		}
	}
  std::cout << "\t ===============================" << '\n';
	return 1;
}



// Display the Current Folder Information on Screen.
void Application::DisplayInfo(){
	this->m_fdCurPointer->DisplayInfoOnScreen();
}

// Display the Current Folder's SubItem List on Screen.
void Application::DisplayAllItems(){
	try{
		if (this->m_fdCurPointer->GetSubFolderNum()==0) {
			if (this->m_fdCurPointer->GetSubFileNum()==0) {
				throw EmptyFolder();
			}
			this->m_fdCurPointer->DisplayAllSubFiles();
		} else{
			if (this->m_fdCurPointer->GetSubFileNum()==0) {
				this->m_fdCurPointer->DisplayAllSubFolders();
				return ;
			}
			this->m_fdCurPointer->DisplayAllSubFolders();
			this->m_fdCurPointer->DisplayAllSubFiles();
		}

	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
		return;
	}
}

// Add Folder record in Recently Folder.
int Application::AddRecentlyFolder(FolderType* Temp_FolderPtr){
	try{
		if (this->m_RecentlyFolder.GetLength()==0) { //if no data in queue
			this->m_RecentlyFolder.EnQueue(Temp_FolderPtr);
			return 1;
		}

		CircularQueue<FolderType*> Temp_Queue; //for store
		int length=this->m_RecentlyFolder.GetLength(); //when call deque length is changed
		for (int i = 0; i < length; i++) {
			if (this->m_RecentlyFolder.Front()->GetPath()!=Temp_FolderPtr->GetPath()) { // if data is not overlap (if directory is changed name can be overlaped)
				Temp_Queue.EnQueue(this->m_RecentlyFolder.Front());
			}
			this->m_RecentlyFolder.DeQueue();
		}
		this->m_RecentlyFolder=Temp_Queue; // deep copy
		this->m_RecentlyFolder.EnQueue(Temp_FolderPtr); // and enqueue data finally
		return 1;
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
		return 0;
	}
}

int Application::AddRecentlyFile(FileType *Temp_FilePtr){
	try{
		if (this->m_RecentlyFile.GetLength()==0) { //if no data in queue
			this->m_RecentlyFile.EnQueue(Temp_FilePtr);
			return 1;
		}

		CircularQueue<FileType*> Temp_Queue; //for store
		int length=this->m_RecentlyFile.GetLength(); //when call deque length is changed
		for (int i = 0; i < length; i++) {
			if (this->m_RecentlyFile.Front()->GetPath()!=Temp_FilePtr->GetPath()) { // if data is not overlap (if directory is changed name can be overlaped)
				Temp_Queue.EnQueue(this->m_RecentlyFile.Front());
			}
			this->m_RecentlyFile.DeQueue();
		}
		this->m_RecentlyFile=Temp_Queue; // deep copy
		this->m_RecentlyFile.EnQueue(Temp_FilePtr); // and enqueue data finally
		return 1;
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
		return 0;
	}
}

// Display the Recently Folder on Screen.
void Application::DisplayRecentlyItems(){

	CircularQueue<FolderType*> Temp_Queue_Folder; // for store
	CircularQueue<FileType*> Temp_Queue_File; // for store
	int length_folder=this->m_RecentlyFolder.GetLength(); //when call deque length is changed
	int length_file=this->m_RecentlyFile.GetLength(); //when call deque length is changed
  std::cout << "\t ====== Recent Item List ======" << '\n';
	if (this->m_RecentlyFolder.GetLength()==0) {
		if (this->m_RecentlyFile.GetLength()==0) { //folder && file 0
			std::cout << "\t No Result" << '\n';
			std::cout << "\t ===============================" << '\n';
			return ;
		}

		//folder 0 file not 0
		for (int i = 0; i < length_file; i++) {
			std::cout << "\t " << *this->m_RecentlyFile.Front()<<'\n';
			Temp_Queue_File.EnQueue(this->m_RecentlyFile.Front());
			this->m_RecentlyFile.DeQueue();
		}
		this->m_RecentlyFile=Temp_Queue_File;
	} else{
		if (this->m_RecentlyFolder.GetLength()==0) { // folder not 0 file 0
			for (int i = 0; i < length_folder; i++) {
				std::cout << "\t " << *this->m_RecentlyFolder.Front()<<'\n';
				Temp_Queue_Folder.EnQueue(this->m_RecentlyFolder.Front());
				this->m_RecentlyFolder.DeQueue();
			}
			this->m_RecentlyFolder=Temp_Queue_Folder;
		} else{ // folder && file not 0
			//Folder
			for (int i = 0; i < length_folder; i++) {
				std::cout << "\t " << *this->m_RecentlyFolder.Front()<<'\n';
				Temp_Queue_Folder.EnQueue(this->m_RecentlyFolder.Front());
				this->m_RecentlyFolder.DeQueue();
			}
			this->m_RecentlyFolder=Temp_Queue_Folder;

      //File
			for (int i = 0; i < length_file; i++) {
				std::cout << "\t " << *this->m_RecentlyFile.Front()<<'\n';
				Temp_Queue_File.EnQueue(this->m_RecentlyFile.Front());
				this->m_RecentlyFile.DeQueue();
			}
			this->m_RecentlyFile=Temp_Queue_File;

		}
	}
	std::cout << "\t ===============================" << '\n';
}
