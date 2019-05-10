#include "BaseApplication.hpp"


// Program driver.
void BaseApplication::Run(){


// for using temp and target and process command
	FolderType Temp_Folder;
	FolderType Target_Folder;
	FolderType* Target_FolderPtr;

	LinkedQueue<std::string>PathQueue; // << for store path
	LinkedQueue<std::string>CheckQueue; // << for store path

	// command
	int command_count;
	std::string Temp;
	std::string Temp_List[3];
	std::string Operation;
	std::string Option;
	std::string Value;
	std::string current_time;

	//start to store history of root

	this->m_History.Push(&this->Root);

	// check to move current folder by command cd
	FolderType* Check_CurPtr=this->m_fdCurPointer;


	// this->m_Command 기록 저장할 방법 생각해보기
	while (this->GetCommand(this->m_Command)) {
		//make command to operation and target (initiallize)
		if (Check_CurPtr!=this->m_fdCurPointer) {
			Check_CurPtr->ResetFolderKey();
			Check_CurPtr->SortSubItems("");
		}

		// make path queue clear
		PathQueue.MakeEmpty();

		// command initiallize
		command_count=0;
		Temp="";
	  //initiallize Temp_List
		for (int i = 0; i < 3; i++) {
			*(Temp_List+i)="";
		}
	  Operation="";
	  Option="";
	  Value="";
	  current_time="";

		//Split the [operation] [option] [value]
		for (std::stringstream ss(this->m_Command); (ss>>Temp)&&command_count<3; command_count++) {
			*(Temp_List+command_count)=Temp;
		}

		// set [operation] [option/target] [value]
		Operation=*(Temp_List);
		Option=*(Temp_List+1);
		Value=*(Temp_List+2);

		if (Operation=="") {
			continue; //re-command
		}

		if (Value=="") { // if only has [operation] [value]
			Value=Option;
		}

		switch (this->GetOpCode(Operation)) {
			case 1: //pwd
			this->m_fdCurPointer->DisplayPathOnScreen();
			break;

			case 2: //cd
			try{
				if (Value=="") { //if no value
					break;
				}

				if (Value=="../") {// go to parent

					if (this->m_fdCurPointer==&this->Root) { // if cur fold pointer is root
						throw NoParent(); // if there is no parent folder throw no history
					}
					this->m_fdCurPointer=this->m_fdCurPointer->GetParentPtr(); // move to parent directory
					this->m_History.Push(this->m_fdCurPointer); //store history

					//add recent item
					this->AddRecentItem(this->m_fdCurPointer);
					// Set Access Time
					this->m_fdCurPointer->GenerateTime(current_time);
					this->m_fdCurPointer->SetAccessTime(current_time);

				} else if (Value=="./") {//left current folder
					break; //do nothing
				} else if (Value=="<") {//go to back

					if (this->m_History.IsEmpty()) {
						throw NoHistory();
					}

					this->m_History.Next(); // move history cur to backward

					this->m_fdCurPointer=this->m_History.Cur(); // point cur
					//add recent item
					this->AddRecentItem(this->m_fdCurPointer);
					// Set Access Time
					this->m_fdCurPointer->GenerateTime(current_time);
					this->m_fdCurPointer->SetAccessTime(current_time);

				} else if (Value==">"){ //go to front

					if (this->m_History.IsEmpty()) {
					  throw NoHistory();
					}
					this->m_History.Prev(); // move history cur to forward

					this->m_fdCurPointer=this->m_History.Cur();// point cur

					//add recent item
					this->AddRecentItem(this->m_fdCurPointer);
					// Set Access Time
					this->m_fdCurPointer->GenerateTime(current_time);
					this->m_fdCurPointer->SetAccessTime(current_time);

				} else if (Value=="~"){ //go to root
					this->m_fdCurPointer=&this->Root;
					// store history
					this->m_History.Push(this->m_fdCurPointer);

					//add recent item
					this->AddRecentItem(this->m_fdCurPointer); // AddRecentlyFolder get parameter for reference, assign temp
					// Set Access Time
					this->m_fdCurPointer->GenerateTime(current_time);
					this->m_fdCurPointer->SetAccessTime(current_time);
				} else{ // no special value
					switch (this->PathProcessor(Value,CheckQueue)) {
						case -1: // has no path, move in current folder
						switch (this->CheckValueItemType(Value)) {
							case 0: //if file
							throw NameError(Value);

							case 1: //if folder
							Target_Folder.SetName(Value);
							Target_Folder.SetPath(this->m_fdCurPointer->GetPath()+"/"+Value);
							if (!(Target_FolderPtr=this->m_fdCurPointer->RetrieveFolderPtrByName(Target_Folder))) { // if not found
								throw ItemNotFound(Target_Folder.GetName());
							}
							// move to find
							this->m_fdCurPointer=Target_FolderPtr;

							// store History
							this->m_History.Push(this->m_fdCurPointer);

							//add recent item
							this->AddRecentItem(this->m_fdCurPointer);
							// Set Access Time
							this->m_fdCurPointer->GenerateTime(current_time);
							this->m_fdCurPointer->SetAccessTime(current_time);
							break;
						}
						break;

						case 0: // has path and last is file
						throw NameError(Value);

						case 1: // has path and last is folder(loop)
						if (this->GetTargetFolderPtrInPath(Value, Target_FolderPtr)) {

							//find
							this->m_fdCurPointer=Target_FolderPtr;

							// store History
							this->m_History.Push(this->m_fdCurPointer);

							//add recent item
							this->AddRecentItem(this->m_fdCurPointer);
							// Set Access Time
							this->m_fdCurPointer->GenerateTime(current_time);
							this->m_fdCurPointer->SetAccessTime(current_time);
						}
						break;
					}
				}
				break;
			}	catch(std::exception &ex){
				std::cout <<"cd : " <<ex.what() << '\n';
				break;
			}

			case 3: //mkdir (only control in current folder)
			try{
				if (Value=="") { //if no value
					break;
				} else if (Value.find('/')!=std::string::npos) { // filter of path
					throw NameError(Value);
				} else if (Value.find('.')!=std::string::npos) { // if file name
					throw NameError(Value);
				} else if (Option!=Value) { // mkdir [Option] [Value]
					if (Option=="-o") { // mkdir -o [Value] make and open
						this->NewItem(Value);
						// set item info to find
						Temp_Folder.SetName(Value);
						Temp_Folder.SetPath(this->m_fdCurPointer->GetPath()+"/"+Value);
						//move folder made
						this->m_fdCurPointer=this->m_fdCurPointer->RetrieveFolderPtrByName(Temp_Folder);

						// store History
						this->m_History.Push(this->m_fdCurPointer);
						// Set Access Time
						this->m_fdCurPointer->GenerateTime(current_time);
						this->m_fdCurPointer->SetAccessTime(current_time);
						//add recent item
						this->AddRecentItem(this->m_fdCurPointer);
						break;
					} else{
						throw InvalidOperation();
					}
				}
				// general case make folder
				this->NewItem(Value);
				break;
			} catch(InvalidOperation &InVaOpex){
				std::cout <<"mkdir : " <<InVaOpex.what() << '\n';
				std::cout << "usage : " <<"mkdir [Value]" <<'\n';
				std::cout << "Command \'help mkdir\' give more information to you" << '\n';
				break;
			} catch(std::exception &ex){
				std::cout <<"mkdir : " <<ex.what() << '\n';
				break;
			}

			case 4: // touch (only control in current folder)
			try{
				if (Value=="") { //if no value
					break;
				} else if (Value.find('.')==std::string::npos) { // if folder name
					throw NameError(Value);
				} else if (Option!=Value) { // touch [Option] [Value]
					if (Option=="-r") { //touch -r [Value] make file and run
						this->NewItem(Value);
						this->RunFile(Value);
					} else{
						throw InvalidOperation();
					}
				}
				// general case make file
				this->NewItem(Value);
				break;
			} catch(InvalidOperation &InVaOpex){
				std::cout <<"touch : " <<InVaOpex.what() << '\n';
				std::cout << "usage : " <<"touch [Option] [Value]" <<'\n';
				std::cout << "Command \'help touch\' give more information to you" << '\n';
				break;
			} catch(std::exception &ex){
				std::cout <<"touch : " <<ex.what() << '\n';
				break;
			}

			case 5: //rm (only control in current folder)
			try{
				if (Value.find('/')!=std::string::npos) { //filter of path
					throw NameError(Value);
				} else if (Value=="*") { //delete all rm *
					this->m_fdCurPointer->MakeEmptyFolder();
					break;
				} else if(Value==""){ //if no value
				  break; //do nothing
			  } else if (Option!=Value){
					throw InvalidOperation();
				}
				//Value has name
				this->DeleteItem(Value);
				break;
			} catch(InvalidOperation &InVaOpex){
				std::cout <<"rm : " <<InVaOpex.what() << '\n';
				std::cout << "usage : " <<"rm [Value]" <<'\n';
				std::cout << "Command \'help rm\' give more information to you" << '\n';
				break;
			} catch(std::exception &ex){
				std::cout <<"rm : " <<ex.what() << '\n';
				break;
			}

			case 6: //update (only control in current folder)
			try{
				if (Option==Value) { // update or update [Target]
					break; // do nothing
				} else if (Option!=Value){ //update [Target] [Name]
					if (Value.find('/')!=std::string::npos||Option.find('/')!=std::string::npos) { //filter of path (value) update [Target] [Name]
						throw NameError(Value);
					}
					this->UpdateItemName(Option,Value);
					this->SortAllItems("");
				}
				break;
			} catch(std::exception &ex){
				std::cout <<"update : " <<ex.what() << '\n';
				break;
			}

			case 7:// run (only control in current folder)
			try{
				if (Option!=Value) { // run [Option] [Value]
					throw InvalidOperation();
				}
				if (Option=="") { //run
					break; //do nothing
				}
				this->RunFile(Value);
				break;
			} catch(InvalidOperation &InVaOpex){
				std::cout <<"run : " <<InVaOpex.what() << '\n';
				std::cout << "usage : " <<"run [Value]" <<'\n';
				std::cout << "Command \'help run\' give more information to you" << '\n';
				break;
			} catch(std::exception &ex){
				std::cout <<"run : " <<ex.what() << '\n';
				break;
			}

			case 8: //copy
			try{
				if (Option==""){// copy
					//do nothing
					break;
				} else if (Option==Value) {  // copy [target]
					//copy the data
					this->CopyItem(Option); //copy target and store in heap
				} else{ // copy [target] [value]
					//all condition is satisfied
					this->CopyItem(Option);
					this->Paste(Value);
				}
				break;
			} catch(std::exception &ex){
				std::cout <<"copy : " <<ex.what() << '\n';
				break;
			}
			break;

			case 9: //cut
			try{
				if (Option=="") { // cut
					//do nothing
					break;
				} else if (Option==Value) { // cut [target]
					//cut the data
					this->CutItem(Option);
				} else{ // cut [target] [value]
					this->CutItem(Option);
					this->Paste(Value);
				}
			} catch(std::exception &ex){
				std::cout <<"cut : " <<ex.what() << '\n';
				break;
			}
			break;

			case 10: //move
			try{
				if (Option=="") { // move
					//do nothing
					break;
				} else if (Option==Value) { // move [target]
					throw InvalidOperation();

				} else{ // move [target] [value]
					this->CutItem(Option);
					this->Paste(Value);
				}
			} catch(InvalidOperation &InVaOpex){
				std::cout <<"move : " <<InVaOpex.what() << '\n';
				std::cout << "usage : " <<"move [Target] [Where]" <<'\n';
				std::cout << "Command \'help move\' give more information to you" << '\n';
				break;
			} catch(std::exception &ex){
				std::cout <<"move : " <<ex.what() << '\n';
				break;
			}
			break;

			case 11: //duplicate (only control in current folder)
			try{
				if (Option=="") { // dupl
          // do nothing
					break;
				} else if (Option!=Value) { // dupl [target] [where] throw InvalidOperation
					throw InvalidOperation();
				} else{ // dupl [target] ( target is must be in the current folder)
					if (Option.find('/')!=std::string::npos) {
						throw NameError(Option);
					}
					// copy
					this->CopyItem(Option);
					//paste current folder
					this->Paste();
				}

			} catch(InvalidOperation &InVaOpex){
				std::cout <<"dupl : " <<InVaOpex.what() << '\n';
				std::cout << "usage : " <<"dupl [Target]" <<'\n';
				std::cout << "Command \'help dupl\' give more information to you" << '\n';
				break;
			} catch(std::exception &ex){
				std::cout <<"dupl : " <<ex.what() << '\n';
				break;
			}
			break;

			case 12: //paste
			try{
				if (Option=="") { //paste (paste in current folder)
					this->Paste();
				} else if (Option!=Value ){ // paste [target] [where] throw InvalidOperation
					throw InvalidOperation();
				} else{ // paste [Value](where)
					this->Paste(Value);
				}

			} catch(InvalidOperation &InVaOpex){
				std::cout <<"paste : " <<InVaOpex.what() << '\n';
				std::cout << "usage : " <<"paste [Where]" <<'\n';
				std::cout << "Command \'help paste\' give more information to you" << '\n';
				break;
			} catch(std::exception &ex){
				std::cout <<"paste : " <<ex.what() << '\n';
				break;
			}
			break;
			case 13: //search keyword
			try{
				if (Option=="") { //search
					throw InvalidOperation();
				} else if (Option!=Value ){ //search [Option] [Value]
					throw InvalidOperation();
				}
				this->SearchItemsByName(Value);
				break;
			} catch(InvalidOperation &InVaOpex){
				std::cout <<"search : " <<InVaOpex.what() << '\n';
				std::cout << "usage : " <<"search [KeyWord]" <<'\n';
				std::cout << "Command \'help search\' give more information to you" << '\n';
				break;
			} catch(std::exception &ex){
				std::cout <<"sort : " <<ex.what() << '\n';
				break;
			}

			break;

			case 14: //sort (only control in current folder)
			try{
			  if (Option==Value){
					if ((Option!="")&&(Option!="name")&&(Option!="created")&&(Option!="modified")&&(Option!="access")) {
						// sort [Key] (Options must be key value) //if option =="" default is key value
						throw InvalidOperation();
					}
					this->m_fdCurPointer->SetDirection(1);
					this->SortAllItems(Option);
					break;
				} else if (Option!=Value){
					if (Option=="-d") { // sort -d [Value] sort direction is DESCENDING(0)
						if ((Value!="")&&(Value!="name")&&(Value!="created")&&(Value!="modified")&&(Value!="access")) {
							// sort [Key] (Options must be key value) //if option =="" default is key value
							throw InvalidOperation();
						}
						this->m_fdCurPointer->SetDirection(0);
						this->SortAllItems(Value);
					} else {
						throw InvalidOperation();
					}
					break;
				}

				break;
			} catch(InvalidOperation &InVaOpex){
				std::cout <<"sort : " <<InVaOpex.what() << '\n';
				std::cout << "usage : " <<"sort [Key]" <<'\n';
				std::cout << "Command \'help sort\' give more information to you" << '\n';
				break;
			} catch(std::exception &ex){
				std::cout <<"sort : " <<ex.what() << '\n';
				break;
			}

			break;
			case 15: //ls (only control in current folder)
			try{
				if (Option=="") { //ls// ls [option] [value]
					this->DisplayAllItems();
				} else if(Option=="a") { // ls a
					this->DisplayAllItemsDetail();
				} else{
					throw InvalidOperation();
				}
				break;
			} catch(InvalidOperation &InVaOpex){
				std::cout <<"ls : " <<InVaOpex.what() << '\n';
				std::cout << "usage : " <<"ls [Option]" <<'\n';
				std::cout << "Command \'help ls\' give more information to you" << '\n';
				break;
			} catch(std::exception &ex){
				std::cout <<"ls : " <<ex.what() << '\n';
				break;
			}
			case 16: //info (only control in current folder)
			try{
				if (Option!=Value) { //info [Option] [Value]
					throw InvalidOperation();
				}
				if (Value.find('/')!=std::string::npos) { //filter of path
					throw NameError(Value);
				}	else if (Value!="") { //display item named Value info
					this->DisplayItemInfo(Value);
				} else{ //Value="" default display info of current folder
					this->DisplayCurFolderInfo();
				}
				break;
			} catch(InvalidOperation &InVaOpex){
				std::cout <<"info : " <<InVaOpex.what() << '\n';
				std::cout << "usage : " <<"info [Target]" <<'\n';
				std::cout << "Command \'help info\' give more information to you" << '\n';
				break;
			} catch(std::exception &ex){
				std::cout <<"info : " <<ex.what() << '\n';
				break;
			}
			case 17: //recent (only control in current folder)
			try{
				if (Option!="") { //recent [Option] or recent [Option] [Value]
					throw InvalidOperation();
				}
				this->DisplayRecentFolder();
				break;
			} catch(InvalidOperation &InVaOpex){
				std::cout <<"recent : " <<InVaOpex.what() << '\n';
				std::cout << "usage : " <<"recent" <<'\n';
				std::cout << "Command \'help recent\' give more information to you" << '\n';
				break;
			} catch(std::exception &ex){
				std::cout <<"info : " <<ex.what() << '\n';
				break;
			}
			case -1: //nothing operation
			std::cout << "Error : Command Not Found : " <<Operation <<'\n';
			break;
			case 0: //Exit
			std::cout << "Exit Program..." << '\n';
			return;
		}
	}
}

// get a command from keyboard.
int BaseApplication::GetCommand(std::string &Command){
	while (1) {
		try{
			std::cout << "~" <<this->m_fdCurPointer->GetName() <<"$ ";
			if ((std::cin.fail()) || !(std::getline(std::cin,Command))){   // input fail or input value is out of bound
			  std::cin.clear();   //clear flag
			  std::cin.ignore(INT_MAX,'\n');   //empty input buffer
				throw InvalidOperation();
			}
			else {
			  std::cin.clear();  // clear flag
        //std::cin.ignore(INT_MAX,'\n'); //empty input buffer
			  return 1;
			}
		} catch(std::exception &ex){
			std::cout << ex.what() << '\n';
			continue;
		}
	}
}

// get operation code.
int BaseApplication::GetOpCode(std::string Operation){
	int code;
	if (Operation=="pwd") {
		code=1;
	} else if(Operation=="cd"){
		code=2;
	} else if(Operation=="mkdir"){
		code=3;
	} else if(Operation=="touch"){
		code=4;
	}else if(Operation=="rm"){
		code=5;
	} else if(Operation=="update"){
		code=6;
	} else if(Operation=="run"){
		code=7;
	} else if(Operation=="copy"){
		code=8;
	} else if(Operation=="cut"){
		code=9;
	} else if(Operation=="move"){
		code=10;
	} else if(Operation=="dupl"){
		code=11;
	} else if(Operation=="paste"){
		code=12;
	} else if(Operation=="search"){
		code=13;
	} else if(Operation=="sort"){
		code=14;
	} else if(Operation=="ls"){
		code=15;
	} else if(Operation=="info"){
		code=16;
	} else if(Operation=="recent"){
		code=17;
	} else if(Operation=="exit"){
		code=0;
	} else{
		code= -1;
	}
	return code;
}

// Check ItemType and Value is right.
int BaseApplication::CheckValueItemType(std::string Value){
	if ((Value.find("../")!=std::string::npos)||(Value.find("./")!=std::string::npos)||(Value.find(">")!=std::string::npos)
		 ||(Value.find("<")!=std::string::npos)||(Value.find("~")!=std::string::npos)) { // if it is not folder name type
		// cd operation and contain .(execution) throw namerror
		throw NameError(Value);
	}
	// check name error finish , then check file or folder
	if ((Value.find(".txt")!=std::string::npos)||(Value.find(".jpg")!=std::string::npos)) { // if find .(extensions) it is file
		//다른 확장자도 추가하기
		return 0;
	}
	return 1; // it is folder
}

// Split the path in PathQueue
int BaseApplication::PathProcessor(std::string Path, LinkedQueue<std::string> &PathQueue){
	if (Path.find('/')==std::string::npos) { //if just move in current folder subfolder
		return -1; // return -1
	}
	int pos=0;
	int NameLastIndex=0;
	std::string Name="";

	//spliting path
	while (Path.find('/',pos)!=std::string::npos) {// loop for find all '/'
	  //initiallize
	  pos=0;
		NameLastIndex=0;
		Name="";
		//search
	  NameLastIndex=(int)Path.find('/',pos)-1; // set name last index
		Name=Path.substr(0,NameLastIndex+1); // split
		if (Name!="") { // if name is real data
			PathQueue.EnQueue(Name);
		}
		//erase
		Path.erase(0,NameLastIndex+2);
	}
	//last word test folder or file
	Name=Path.substr(0);
	if (Name!="") {
		PathQueue.EnQueue(Name);
	}
	return this->CheckValueItemType(Name); // file return 0, folder return 1;
}

// using Path processor find TargetFolder
int BaseApplication::GetTargetFolderPtrInPath(std::string Target, FolderType*& Target_FolderPtr, FolderType* Temp_curFolderPtr){
	FolderType Target_Folder;
	FolderType Temp_Folder;
	FolderType* Temp_FolderPtr;


	// for path process
	LinkedQueue<std::string> PathQueue;

  Temp_curFolderPtr = this->m_fdCurPointer; //temp cur pointer

	// Split [Target]
	switch (this->PathProcessor(Target,PathQueue)) {
		case -1: // has no path, find in current folder
		switch (this->CheckValueItemType(Target)) {
			case 0: // if target is file in current Folder
			throw NameError(Target);

			case 1: //if target is folder in current folder
			Target_Folder.SetName(Target);
			Target_Folder.SetPath(this->m_fdCurPointer->GetPath()+"/"+Target);
			if (!(Target_FolderPtr=this->m_fdCurPointer->RetrieveFolderPtrByName(Target_Folder))) { //if no find
				throw ItemNotFound(Target);
			}
			return 1;
		}
		break;

		case 0: // has path and last is file (loop)
		throw NameError(Target);

		case 1: // has path and last is folder(loop)

		try{
			while (1) {
				if (PathQueue.GetLength()==1) { // if end of search it remain folder
					//this->m_fdCurPointer not move
					break;
				}

				//set condition //for search
				if (PathQueue.Front()=="..") { //move to parent
					if (!(Temp_curFolderPtr=Temp_curFolderPtr->GetParentPtr())) { //if Temp_Cur point root
						throw NoParent();
					}
					Temp_Folder.SetName(Temp_curFolderPtr->GetName());
					Temp_Folder.SetPath(Temp_curFolderPtr->GetPath()+"/"+Temp_curFolderPtr->GetName());
					PathQueue.DeQueue();
					continue;

				} else if (PathQueue.Front()=="."){ //stay in current folder
					Temp_Folder.SetName(Temp_curFolderPtr->GetName());
					Temp_Folder.SetPath(Temp_curFolderPtr->GetPath()+"/"+Temp_curFolderPtr->GetName());
					PathQueue.DeQueue();
					continue;

				} else{
					Temp_Folder.SetName(PathQueue.Front());
					Temp_Folder.SetPath(Temp_curFolderPtr->GetPath()+"/"+PathQueue.Front());
					//search
					Temp_FolderPtr=Temp_curFolderPtr->RetrieveFolderPtrByName(Temp_Folder);
					PathQueue.DeQueue(); // DeQueue
					Temp_curFolderPtr=Temp_FolderPtr; // set cur pointer again
				}
			}

			// Set the folder info PathQueue last word
			if (PathQueue.Front()=="..") { //move to parent
				if (!(Target_FolderPtr=Temp_curFolderPtr->GetParentPtr())) { //if Temp_Cur point root
					throw NoParent();
				}
				return 1;

			} else if (PathQueue.Front()=="."){ //stay in current folder
				Target_FolderPtr=Temp_curFolderPtr;
				return 1;

			} else{
				Target_Folder.SetName(PathQueue.Front());
				Target_Folder.SetPath(Temp_curFolderPtr->GetPath()+"/"+PathQueue.Front());
				if (!(Target_FolderPtr=Temp_curFolderPtr->RetrieveFolderPtrByName(Target_Folder))) {
					throw ItemNotFound(Target);
				}
				return 1;
			}
		} catch(ItemNotFound &itex){// for no search result
				throw itex;
		} catch(EmptyQueue &eqex){
				break;
		}
		break;
	}
	//if all fail
	return 0;
}

// using Path processor find TargetFile
int BaseApplication::GetTargetFilePtrInPath(std::string Target, FileType*& Target_FilePtr, FolderType* Temp_curFolderPtr){
	FileType Target_File;
	FolderType Temp_Folder;
	FolderType* Temp_FolderPtr;


	// for path process
	LinkedQueue<std::string> PathQueue;

	Temp_curFolderPtr = this->m_fdCurPointer; //temp cur pointer

	// Split [Target]
	switch (this->PathProcessor(Target,PathQueue)) {
		case -1: // has no path, find in current folder
		switch (this->CheckValueItemType(Target)) {
			case 0: // if target is file in current Folder
			Target_File.SetName(Target);
			Target_File.SetPath(this->m_fdCurPointer->GetPath()+"/"+Target);
			if (!(Target_FilePtr=this->m_fdCurPointer->RetrieveFilePtrByName(Target_File))) { //if no find
				throw ItemNotFound(Target);
			}
			return 1;

			case 1: //if target is folder in current folder
			throw NameError(Target);
		}
		break;

		case 0: // has path and last is file (loop)

		try{
			while (1) {
				if (PathQueue.GetLength()==1) { // if end of search it remain folder
					//this->m_fdCurPointer not move
					break;
				}

				//set condition //for search
				if (PathQueue.Front()=="..") { //move to parent
					if (!(Temp_curFolderPtr=Temp_curFolderPtr->GetParentPtr())) { //if Temp_Cur point root
						throw NoParent();
					}
					Temp_Folder.SetName(Temp_curFolderPtr->GetName());
					Temp_Folder.SetPath(Temp_curFolderPtr->GetPath()+"/"+Temp_curFolderPtr->GetName());
					PathQueue.DeQueue();
					continue;

				} else if (PathQueue.Front()=="."){ //stay in current folder
					Temp_Folder.SetName(Temp_curFolderPtr->GetName());
					Temp_Folder.SetPath(Temp_curFolderPtr->GetPath()+"/"+Temp_curFolderPtr->GetName());
					PathQueue.DeQueue();
					continue;

				} else{
					Temp_Folder.SetName(PathQueue.Front());
					Temp_Folder.SetPath(Temp_curFolderPtr->GetPath()+"/"+PathQueue.Front());
					//search
					Temp_FolderPtr=Temp_curFolderPtr->RetrieveFolderPtrByName(Temp_Folder);
					PathQueue.DeQueue(); // DeQueue
					Temp_curFolderPtr=Temp_FolderPtr; // set cur pointer again
				}
			}

			// Set the folder info PathQueue last word
			Target_File.SetName(PathQueue.Front());
			Target_File.SetPath(Temp_curFolderPtr->GetPath()+"/"+PathQueue.Front());
			if (!(Target_FilePtr=Temp_curFolderPtr->RetrieveFilePtrByName(Target_File))) {
				throw ItemNotFound(Target);
			}
			return 1;

		} catch(ItemNotFound &itex){// for no search result
			throw itex;
		} catch(EmptyQueue &eqex){
			break;
		}
		break;
		case 1: // has path and last is folder(loop)
		throw NameError(Target);
	}
	//if all fail
	return 0;
}

// Create New Item in Current Folder.
int BaseApplication::NewItem(std::string Value){
	FolderType Temp_Folder;
	FileType Temp_File;
	switch (this->CheckValueItemType(Value)) {
		case 0://file
		//set the file info to add
		Temp_File.SetName(Value); // Set SubFile Name
		Temp_File.SetPath(this->m_fdCurPointer->GetPath()+"/"+Value); // Set SubFile Path
		Temp_File.SetExtensions(Value.substr(Value.find('.')+1));
		if (this->m_fdCurPointer->NewFile(Temp_File)) {
			return 1; //Create New file
		}
		break;
		case 1://folder
		//set the folder info to add
		Temp_Folder.SetName(Value); // Set SubFolder Name
		Temp_Folder.SetPath(this->m_fdCurPointer->GetPath()+"/"+Value); // Set SubFolder Path
		Temp_Folder.SetParentPtr(this->m_fdCurPointer);
		if (this->m_fdCurPointer->NewFolder(Temp_Folder)) {
			return 1; //Create New Folder
		}
		break;
	}
	return 0;
}

// Delete Item you search in Current Folder.
int BaseApplication::DeleteItem(std::string Value){
	FileType Temp_File;
	FolderType Temp_Folder;

	switch (this->CheckValueItemType(Value)) {
		case 0://file
		//set the file info to delete
		Temp_File.SetName(Value); // Set SubFile Name
		Temp_File.SetPath(this->m_fdCurPointer->GetPath()+"/"+Value); // Set SubFile Path
		if (this->m_fdCurPointer->DeleteFile(Temp_File)) {
			return 1; //Delete file
		}
		break;
		case 1://folder
		//set the folder info to delete
		Temp_Folder.SetName(Value); // Set SubFolder Name
		Temp_Folder.SetPath(this->m_fdCurPointer->GetPath()+"/"+Value); // Set SubFolder Path
		if (this->m_fdCurPointer->DeleteFolder(Temp_Folder)) {
			return 1; //Delete Folder
		}
		break;
	}
	return 0;
}

// Update Item Name you search in Current Folder.
int BaseApplication::UpdateItemName(std::string Target, std::string Value){
	FileType Temp_File;
	FileType* Temp_FilePtr;
	FolderType Temp_Folder;
	FolderType* Temp_FolderPtr;
	std::string current_time;

	switch (this->CheckValueItemType(Target)) { //check Target First
		case 0://file(Target)
		switch (this->CheckValueItemType(Value)) {
			case 0: //file(Value)
			//set the file info to update
			Temp_File.SetName(Target); // Set SubFile Name
			Temp_File.SetPath(this->m_fdCurPointer->GetPath()+"/"+Target); // Set SubFile Path
			if (!(Temp_FilePtr=this->m_fdCurPointer->RetrieveFilePtrByName(Temp_File))) { //if not found
				throw ItemNotFound(Target);
			}
			Temp_FilePtr->SetName(Value); // Update SubFile Name
			Temp_FilePtr->SetPath(this->m_fdCurPointer->GetPath()+"/"+Value); // Update SubFile Path

			//set access time
			Temp_FilePtr->GenerateTime(current_time);
			Temp_FilePtr->SetModifiedTime(current_time);
			return 1; //Update file
			case 1: //folder(Value)
			throw NameError(Value);
		}
		case 1://Folder(Target)
		switch (this->CheckValueItemType(Value)) {
			case 0: //file(Value)
			throw NameError(Value);
			case 1: //folder(Value)
			//set the folder info to update
			Temp_Folder.SetName(Target); // Set SubFolder Name
			Temp_Folder.SetPath(this->m_fdCurPointer->GetPath()+"/"+Target); // Set SubFolder Path
			if (!(Temp_FolderPtr=this->m_fdCurPointer->RetrieveFolderPtrByName(Temp_Folder))) { //if not found
				throw ItemNotFound(Target);
			}
			Temp_FolderPtr->SetName(Value); // Update SubFolder Name
			Temp_FolderPtr->SetPath(this->m_fdCurPointer->GetPath()+"/"+Value); // Update SubFolder Path

			//set access time
			Temp_FolderPtr->GenerateTime(current_time);
			Temp_FolderPtr->SetModifiedTime(current_time);
			return 1; //Update Folder
		}
	}
	return 0;
}

// Run File.
int BaseApplication::RunFile(std::string Target){
	//already filter folder in Run()

	//for setting value;
	FileType* Target_FilePtr =nullptr;
	std::string current_time;

	if(this->GetTargetFilePtrInPath(Target,Target_FilePtr)){
		Target_FilePtr->Run();

		// add recent item
		this->AddRecentItem(Target_FilePtr);

		//set access time
		Target_FilePtr->GenerateTime(current_time);
		Target_FilePtr->SetAccessTime(current_time);
		return 1;
	}
	return 0;
}

// Copy Item.
int BaseApplication::CopyItem(std::string Target){
	//already filter Target=="" in this->Run()

	FileType Target_File;
	FileType* Target_FilePtr=nullptr;
	FolderType Target_Folder;
	FolderType* Target_FolderPtr=nullptr ;

	// for path check
	LinkedQueue<std::string> CheckQueue;

	// Copy [Target]
	switch (this->PathProcessor(Target,CheckQueue)) { // check it has path or no
		case -1: // has no path, find in current folder

		switch (this->CheckValueItemType(Target)) {
			case 0: // if target is file in current Folder
			Target_File.SetName(Target);
			Target_File.SetPath(this->m_fdCurPointer->GetPath()+"/"+Target);
			if (!(Target_FilePtr=this->m_fdCurPointer->RetrieveFilePtrByName(Target_File))) {
				throw ItemNotFound(Target);
			}
			// if Heap has another memory
			if (this->Heap!=nullptr) {
				delete this->Heap;
			}
			this->Heap = new FileType;
			//copy
			*dynamic_cast<FileType*>(this->Heap) = *Target_FilePtr;
			return 1;

			case 1: //if target is folder in current folder
			Target_Folder.SetName(Target);
			Target_Folder.SetPath(this->m_fdCurPointer->GetPath()+"/"+Target);
			if (!(Target_FolderPtr=this->m_fdCurPointer->RetrieveFolderPtrByName(Target_Folder))) { //if no find
				throw ItemNotFound(Target);
			}

			// if Heap has another memory
			if (this->Heap!=nullptr) {
				delete this->Heap;
			}
			this->Heap = new FolderType;
			//copy
			*dynamic_cast<FolderType*>(this->Heap) = *Target_FolderPtr;
			return 1;
		}
		break;

		case 0: // has path and last is file (loop)
		if(this->GetTargetFilePtrInPath(Target, Target_FilePtr)){
			// if Heap has another memory
			if (this->Heap!=nullptr) {
				delete this->Heap;
			}
			this->Heap = new FileType;
			//copy
			*dynamic_cast<FileType*>(this->Heap) = *Target_FilePtr;
			return 1;
		}
		break;

		case 1: // has path and last is folder(loop)
		if (this->GetTargetFolderPtrInPath(Target,Target_FolderPtr)) {
			// if Heap has another memory
			if (this->Heap!=nullptr) {
				delete this->Heap;
			}
			this->Heap = new FolderType;
			//copy
			*dynamic_cast<FolderType*>(this->Heap) = *Target_FolderPtr;
			return 1;
		}
		break;
	}
	//if all fail
	return 0;
}

// Cut/move Item.
int BaseApplication::CutItem(std::string Target){
	//already filter Target=="" in this->Run()

	FileType Target_File;
	FileType* Target_FilePtr =nullptr;
	FolderType Target_Folder;
	FolderType* Target_FolderPtr =nullptr;

	// for path process
	LinkedQueue<std::string> CheckQueue;
	FolderType* Temp_curFolderPtr =nullptr;

	// Copy [Target]
	// Paste data in path to want
	switch (this->PathProcessor(Target,CheckQueue)) {
		case -1: // has no path, find in current folder

		switch (this->CheckValueItemType(Target)) {
			case 0: // if target is file in current Folder
			Target_File.SetName(Target);
			Target_File.SetPath(this->m_fdCurPointer->GetPath()+"/"+Target);
			if (!(Target_FilePtr=this->m_fdCurPointer->RetrieveFilePtrByName(Target_File))) {
				throw ItemNotFound(Target);
			}
			// if Heap has another memory
			if (this->Heap!=nullptr) {
				delete this->Heap;
			}
			this->Heap = new FileType;
			//copy
			*dynamic_cast<FileType*>(this->Heap) = *Target_FilePtr;

			//delete
			if (!this->m_fdCurPointer->DeleteFile(Target_File)) {
				throw ItemNotFound(Target_File.GetName());
			}
			return 1;

			case 1: //if target is folder in current folder
			Target_Folder.SetName(Target);
			Target_Folder.SetPath(this->m_fdCurPointer->GetPath()+"/"+Target);
			if (!(Target_FolderPtr=this->m_fdCurPointer->RetrieveFolderPtrByName(Target_Folder))) { //if no find
				throw ItemNotFound(Target);
			}

			// if Heap has another memory
			if (this->Heap!=nullptr) {
				delete this->Heap;
			}
			this->Heap = new FolderType;
			//copy
			*dynamic_cast<FolderType*>(this->Heap) = *Target_FolderPtr;

			//delete
			if (!this->m_fdCurPointer->DeleteFolder(Target_Folder)) {
				throw ItemNotFound(Target_Folder.GetName());
			}
			return 1;
		}
		break;

		case 0: // has path and last is file (loop)

		if(this->GetTargetFilePtrInPath(Target, Target_FilePtr,Temp_curFolderPtr)){
			// if Heap has another memory
			if (this->Heap!=nullptr) {
				delete this->Heap;
			}
			this->Heap = new FileType;
			//copy
			*dynamic_cast<FileType*>(this->Heap) = *Target_FilePtr;
			//delete
			if (!Temp_curFolderPtr->DeleteFile(*Target_FilePtr)) {
				throw ItemNotFound(Target_FilePtr->GetName());
			}

			return 1;
		}
		break;

		case 1: // has path and last is folder(loop)


		if(this->GetTargetFolderPtrInPath(Target, Target_FolderPtr,Temp_curFolderPtr)){
			// if Heap has another memory
			if (this->Heap!=nullptr) {
				delete this->Heap;
			}
			this->Heap = new FolderType;
			//copy
			*dynamic_cast<FolderType*>(this->Heap) = *Target_FolderPtr;
			//delete
			if (!Temp_curFolderPtr->DeleteFolder(*Target_FolderPtr)) {
				throw ItemNotFound(Target_FolderPtr->GetName());
			}

			return 1;
		}
		break;
	}
	//if all fail
	return 0;
}

// Paste Item.
int BaseApplication::Paste(std::string Value){
	if (this->Heap==nullptr) { // if has no data in heap do nothing
		return 0;
	}

	if (Value=="") {//if Value=="" paste on current folder
	  //set heap new path
	  this->Heap->SetPath(this->m_fdCurPointer->GetPath()+"/"+this->Heap->GetName());
		if (this->Heap->WhatIs()=="Folder") {
			this->m_fdCurPointer->NewFolder(*dynamic_cast<FolderType*>(this->Heap));
		} else{
			this->m_fdCurPointer->NewFile(*dynamic_cast<FileType*>(this->Heap));
		}
		return 1;
	}

	// for path process
	LinkedQueue<std::string> CheckQueue;
	FolderType Temp_Folder;
	FolderType* Temp_FolderPtr=nullptr;

	// Paste [Value](Where)
	// Paste data in path to want
	switch (this->PathProcessor(Value,CheckQueue)) {
		case -1: // has no path, find in current folder
		//already filter Value==""
		switch (this->CheckValueItemType(Value)) {
			case 0: //file
			throw NameError(Value);

			case 1: //folder
			Temp_Folder.SetName(Value);
			Temp_Folder.SetPath(this->m_fdCurPointer->GetPath()+"/"+Value);
			if (!(Temp_FolderPtr=this->m_fdCurPointer->RetrieveFolderPtrByName(Temp_Folder))) { //if no find
				throw ItemNotFound(Value);
			}
			//paste
			//set heap new path
			this->Heap->SetPath(Temp_FolderPtr->GetPath()+"/"+this->Heap->GetName());
			if (this->Heap->WhatIs()=="Folder") {
				Temp_FolderPtr->NewFolder(*dynamic_cast<FolderType*>(this->Heap));
			} else{
				Temp_FolderPtr->NewFile(*dynamic_cast<FileType*>(this->Heap));
			}
			return 1;
		}
		break;

		case 0: // has path and last is file
		throw NameError(Value);

		case 1: // has path and last is folder(loop)
		if (this->GetTargetFolderPtrInPath(Value, Temp_FolderPtr)) {
			//paste
			//set heap new path
			this->Heap->SetPath(Temp_FolderPtr->GetPath()+"/"+this->Heap->GetName());
			if (this->Heap->WhatIs()=="Folder") {
				Temp_FolderPtr->NewFolder(*dynamic_cast<FolderType*>(this->Heap));
			} else{
				Temp_FolderPtr->NewFile(*dynamic_cast<FileType*>(this->Heap));
			}
			return 1;
		}

	}
	return 0;
}

// Retrieve and Display all Items that contain the keword in all child path.
void BaseApplication::SearchItemsByName(std::string Value){
	// store current key
	int Cur_Key =this->m_fdCurPointer->GetKey();

	// searching more fast when it sorted by name so change criteria to name
	// reset key to name
	this->m_fdCurPointer->ResetFolderKey();

	// and sort
	this->m_fdCurPointer->SortSubItems("");

	//searchinig
	FolderType Retrieve_Folder;
	Retrieve_Folder=this->m_fdCurPointer->RetrieveItemsByName(Value);
	Retrieve_Folder.DisplayAllSubItemsDetail();

	// and reset to current(original)
	this->m_fdCurPointer->SortSubItems(Cur_Key);
}

// sort items in curret folder by value criteria.(string)
void BaseApplication::SortAllItems(std::string Value){
	//defalut name
	//sorting
	this->m_fdCurPointer->SortSubItems(Value);
}

// sort items in curret folder by value criteria.(int)
void BaseApplication::SortAllItems(int inKey){
	//defalut name
	//sorting
	this->m_fdCurPointer->SortSubItems(inKey);
}

// Display the Current Folder's SubItem List on Screen.
void BaseApplication::DisplayAllItems(){
	//display
	this->m_fdCurPointer->DisplayAllSubItems();
}

// Display the Current Folder's SubItem List of info on Screen.
void BaseApplication::DisplayAllItemsDetail(){
	//display
  this->m_fdCurPointer->DisplayAllSubItemsDetail();
}

// Display the Current Item Information which is in currentfolder on Screen.
void BaseApplication::DisplayItemInfo(std::string Value){
	FileType Temp_File;
	FolderType Temp_Folder;
	switch (this->CheckValueItemType(Value)) {
		case 0://file
		//set the file info to find
		Temp_File.SetName(Value); // Set SubFile Name
		Temp_File.SetPath(this->m_fdCurPointer->GetPath()+"/"+Value); // Set SubFile Path
		if (this->m_fdCurPointer->RetrieveFileByName(Temp_File)) {
			Temp_File.DisplayInfoOnScreen();
			return ;
		}
		break;
		case 1://folder
		//set the folder info to find
		Temp_Folder.SetName(Value); // Set SubFolder Name
		Temp_Folder.SetPath(this->m_fdCurPointer->GetPath()+"/"+Value); // Set SubFolder Path
		if (this->m_fdCurPointer->RetrieveFolderByName(Temp_Folder)) {
			Temp_Folder.DisplayInfoOnScreen();
			return ;
		}
		break;
	}
	return ;
}

// Display the Current Folder Information on Screen.
void BaseApplication::DisplayCurFolderInfo(){
	//display
	this->m_fdCurPointer->DisplayInfoOnScreen();
}

// Add Item record in Recently Folder.
int BaseApplication::AddRecentItem(ItemType *Temp_Item){
	try{
		if (this->m_RecentFolder.GetLength()==0) { //if no data in queue
			this->m_RecentFolder.EnQueue(Temp_Item);
			return 1;
		}

		if (this->m_RecentFolder.GetLength()>30) { //max size is 30
			this->m_RecentFolder.DeQueue();
		}

		LinkedQueue<ItemType*> Temp_Queue; //for store
		int length=this->m_RecentFolder.GetLength(); //when call deque length is changed
		for (int i = 0; i < length; i++) {
			if (this->m_RecentFolder.Front()->GetPath()!=Temp_Item->GetPath()) { // if data is not overlap (if directory is changed name can be overlaped)
				Temp_Queue.EnQueue(this->m_RecentFolder.Front());
			}
			this->m_RecentFolder.DeQueue();
		}
		this->m_RecentFolder=Temp_Queue; // deep copy
		this->m_RecentFolder.EnQueue(Temp_Item); // and enqueue data finally
		return 1;
	} catch(std::exception &ex){
		std::cout << ex.what() << '\n';
		return 0;
	}
}

// Display the Recently Folder on Screen.
void BaseApplication::DisplayRecentFolder(){
	if (this->m_RecentFolder.GetLength()==0) { //if has no recent item
		std::cout << "No Result" << '\n';
		return ;
	}
	LinkedQueue<ItemType*> Temp_Queue; // for store
	ItemType* Temp_Item;
	int length=this->m_RecentFolder.GetLength(); //when call deque length is changed
	std::cout << "========= Recent Item List =========" << '\n';
	for (int i = 0; i < length; i++) {
		Temp_Item=this->m_RecentFolder.Front();

		//display
		std::cout <<*Temp_Item<<"   "<<this->m_RecentFolder.Front()->GetPath()<<"   "
		<<Temp_Item->MakeMonthToWord(Temp_Item->GetAccessTime().substr(4,2))<<" "<<Temp_Item->GetAccessTime().substr(6,2)
		<<" "<<Temp_Item->MakeHourMinuteToWord(Temp_Item->GetAccessTime().substr(8, 4))<<'\n';
		Temp_Queue.EnQueue(this->m_RecentFolder.Front());
		this->m_RecentFolder.DeQueue();
	}
	this->m_RecentFolder=Temp_Queue; // deep copy
	std::cout << "====================================" << '\n';
}
