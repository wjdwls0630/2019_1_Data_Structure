#include "Application.hpp"


// Program driver.
void Application::Run(){
	while ((this->m_Command = GetCommand())){
		switch (this->m_Command){
			case 1:		// created folder				'
				this->NewFolder();
				break;
			case 2:		// retrieve folder
				this->RetrieveFolderByName();
				break;
			case 3:		// delete folder
				this->DeleteFolder();
				break;
			case 4:		// Display current folder information
				this->DisplayInfo();
				break;
			case 5:		// Display All folders in current folder
				this->DisplayAllFolders(); //application dmfh eocp alc djqtdmfEosms empty Emldna
				break;
			case 6:		// change directory
			  this->ChangeDirectory();
				break;
			case 7:		// load data of Folder Info from a file.
				this->ReadDataFromFile();
				break;
			case 8:		// save list data of Folder Info into a file.
				this->WriteDataToFile();
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
			std::cout << "\t ~" <<this->m_fdCurPointer->GetPath() <<"$"<<'\n';
			std::cout << std::endl << std::endl;
			std::cout << "\t---ID -- Command ------ " << std::endl;
			std::cout << "\t   1 : New Folder" << std::endl;
			std::cout << "\t   2 : Retrieve Folder" << std::endl;
			std::cout << "\t   3 : Delete Folder" << std::endl;
			std::cout << "\t   4 : Display Info" << std::endl;
			std::cout << "\t   5 : Display All Folders" << std::endl;
			std::cout << "\t   6 : Change Directory" << std::endl;
			std::cout << "\t   7 : Get from file" << std::endl;
			std::cout << "\t   8 : Put to file " << std::endl;
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

// Create New Folder in Current Folder.
int Application::NewFolder(){
	//set the folder name to add
	FolderType Temp_Data;
	Temp_Data.SetNameFromKB(); // Set SubFolder Name
	if (this->m_fdCurPointer->AddFolder(Temp_Data)) {
		this->m_fdCurPointer->DisplayAllFolders();
		return 1; //Create New Folder
	}
	return 0;
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
		this->m_fdCurPointer->DisplayAllFolders();
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
	}
}

// Change current dircectory you want.
int Application::ChangeDirectory(){
	//set the folder name to find
	FolderType Temp_Folder;
	try {
		int key;
		std::cout << std::endl << std::endl;
		std::cout << "\t---ID ----- key ------ " << std::endl;
		std::cout << "\t   1 : Go to folder name" << std::endl;
		std::cout << "\t   2 : Go to back" << std::endl;
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
		switch (key) {
			case 1:
			Temp_Folder.SetNameFromKB();
			FolderType* Temp_Pointer;
			if((Temp_Pointer=this->m_fdCurPointer->RetrieveFolderPtrByName(Temp_Folder))){
				this->m_fdBackPointer=this->m_fdCurPointer;
				this->m_fdCurPointer=Temp_Pointer;
				return 1;
		  }
			case 2:
			if (this->m_fdBackPointer) { // If history exists
				this->m_fdForwardPointer=this->m_fdCurPointer;
				this->m_fdCurPointer=this->m_fdBackPointer;
				return 1;
			}
			throw NoHistory();
			case 3:
			this->m_fdBackPointer=this->m_fdCurPointer;
			this->m_fdCurPointer=&this->Root;
			return 1;
	  }
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
		return 0;
	}
}
// read all Info of the Current Folder on the file, and set Folder by the data.
int Application::ReadDataFromFile(){
	if (this->m_fdCurPointer->ReadDataFromFile(this->m_InFile)) {
		return 1;
	}
	return 0;
}


// write all Info of the Current Folder into the file,
int Application::WriteDataToFile(){
	if (this->m_fdCurPointer->WriteDataToFile(this->m_OutFile)) {
		return 1;
	}
	return 0;
}
