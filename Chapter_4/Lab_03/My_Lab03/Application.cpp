#include "Application.hpp"


// Program driver.
void Application::Run(){
	while ((this->m_Command = GetCommand())){
		switch (this->m_Command){
			case 1:		// created folder				'
				this->NewFolder();
				break;
			case 2:
				this->DeleteFolder(); // delete folder
				break;
			case 3:		// change directory
				this->ChangeDirectory();
				break;
			case 4:		// retrieve folder
				this->RetrieveFoldersByName();
				break;
			case 5:		// Display All folders in current folder
			  this->DisplayRecentlyFolder();
				break;
			case 6:		// Display current folder information
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
			this->DisplayAllFolders();
			std::cout << "\t ===============================" << '\n';
			std::cout << std::endl << std::endl;
			std::cout << "\t---ID -- Command ------ " << std::endl;
			std::cout << "\t   1 : New Folder" << std::endl;
			std::cout << "\t   2 : Delete Folder" << std::endl;
			std::cout << "\t   3 : Change Directory" << std::endl;
			std::cout << "\t   4 : Retrieve Folders" << std::endl;
			std::cout << "\t   5 : Display Recently" << std::endl;
			std::cout << "\t   6 : Display Info" << std::endl;
			std::cout << "\t   0 : Quit" << std::endl;
			std::cout << std::endl << "\t Choose a Command--> ";
			if ((std::cin.fail()) || !(std::cin >> command) || command < 0 || command>6){   // input fail or input value is out of bound
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

// Create New Folder in Current Folder.
int Application::NewFolder(){
	//set the folder name to add
	FolderType Temp_Data;
	Temp_Data.SetNameFromKB(); // Set SubFolder Name
	if (this->m_fdCurPointer->AddFolder(Temp_Data)) {
		return 1; //Create New Folder
	}
	return 0;
}

// Delete Folder you search in Current Folder.
int Application::DeleteFolder(){

	//set the folder name to delete
	FolderType Temp_Data;
	std::cout << "\t Enter the folder name to delete" << '\n';
	Temp_Data.SetNameFromKB();
	if (this->m_fdCurPointer->DeleteFolder(Temp_Data)) {
		return 1; //Delete folder success
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
		FolderType* Temp_Pointer;
		switch (key) {
			case 1:
			  Temp_Folder.SetNameFromKB();
			  if((Temp_Pointer=this->m_fdCurPointer->RetrieveFolderPtrByName(Temp_Folder))){
				  this->m_ParentFolder.Push(*this->m_fdCurPointer);
				  this->m_fdCurPointer=Temp_Pointer;
				  this->AddRecentlyFolder(*this->m_fdCurPointer);
		    }
			  break;
			case 2:
			  if (!this->m_ParentFolder.IsEmpty()) { // If history exists
				  this->m_fdCurPointer=this->m_ParentFolder.TopPtr();
				  this->m_ParentFolder.Pop();
				  this->AddRecentlyFolder(*this->m_fdCurPointer);
			  }else{
					throw NoHistory(); // if there is no parent folder throw no history
				}
			  break;
			case 3:
			  this->m_fdCurPointer=&this->Root;
				this->m_ParentFolder.MakeEmpty(); //Root has no parent folder
				Temp_Folder=this->Root;
			  this->AddRecentlyFolder(Temp_Folder); // AddRecentlyFolder get parameter for reference, assign temp
			  break;
	  }
		return 1;
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
		return 0;
	}
}


// Retrieve and Display one Folder that the name is exactly same youin Current Folder.
int Application::RetrieveFolderByName(){
	FolderType Target_Folder;
	if (this->m_fdCurPointer->RetrieveFolderByName(Target_Folder)) {
		Target_Folder.DisplayInfoOnScreen(); //Display Info of Folder
		return 1; //return 1;
	}
	return 0; // return 0;
}

// Retrieve and Display one Folder that the name is exactly same youin Current Folder.
int Application::RetrieveFoldersByName(){
	FolderType Temp_Folder;

	std::string KeyWord;
	std::cout << "\t Enter the Word to Search : ";
	std::cin >> KeyWord;
	Temp_Folder=this->m_fdCurPointer->RetrieveFoldersByName(KeyWord);
	if (Temp_Folder.GetSubFolderNum()==0) {
		std::cout << "\t No Result" << '\n';
		return 0;
	}
	std::cout << "\t =====  Search Folder List =====" << '\n';
	Temp_Folder.DisplayAllSubFolders();
  std::cout << "\t ===============================" << '\n';
	return 1; // return 0;
}



// Display the Current Folder Information on Screen.
void Application::DisplayInfo(){
	this->m_fdCurPointer->DisplayInfoOnScreen();
}

// Display the Current Folder's SubFolder List on Screen.
void Application::DisplayAllFolders(){
	try{
		if (this->m_fdCurPointer->GetSubFolderNum()==0) {
			throw EmptyFolder();
		}
		this->m_fdCurPointer->DisplayAllSubFolders();
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
		return;
	}
}

// Add Folder record in Recently Folder.
int Application::AddRecentlyFolder(FolderType &Temp_Data){
	try{
		if (this->m_RecentlyFolder.GetLength()==0) { //if no data in queue
			this->m_RecentlyFolder.EnQueue(Temp_Data);
			return 1;
		}

		CircularQueue<FolderType> Temp_Queue; //for store
		int length=this->m_RecentlyFolder.GetLength(); //when call deque length is changed
		for (int i = 0; i < length; i++) {
			if (this->m_RecentlyFolder.Front().GetPath()!=Temp_Data.GetPath()) { // if data is not overlap (if directory is changed name can be overlaped)
				Temp_Queue.EnQueue(this->m_RecentlyFolder.Front());
			}
			this->m_RecentlyFolder.DeQueue();
		}
		this->m_RecentlyFolder=Temp_Queue; // deep copy
		this->m_RecentlyFolder.EnQueue(Temp_Data); // and enqueue data finally
		return 1;
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
		return 0;
	}
}

// Display the Recently Folder on Screen.
void Application::DisplayRecentlyFolder(){
	if (this->m_RecentlyFolder.GetLength()==0) {
		std::cout << "\t No Result" << '\n';
		return ;
	}
	CircularQueue<FolderType> Temp_Queue; // for store
	int length=this->m_RecentlyFolder.GetLength(); //when call deque length is changed
	std::cout << "\t ====== Recent Folder List ======" << '\n';
	for (int i = 0; i < length; i++) {
		std::cout << "\t " << this->m_RecentlyFolder.Front()<<'\n';
		Temp_Queue.EnQueue(this->m_RecentlyFolder.Front());
		this->m_RecentlyFolder.DeQueue();
	}
	this->m_RecentlyFolder=Temp_Queue; // deep copy
	std::cout << "\t ===============================" << '\n';
}
