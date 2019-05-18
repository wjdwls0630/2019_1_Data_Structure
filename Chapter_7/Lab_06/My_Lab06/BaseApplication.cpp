#include "BaseApplication.hpp"


// Program driver.
void BaseApplication::Run(){


// for using temp and target and process command
	FolderType Temp_Folder;
	FolderType Target_Folder;
	ItemType* Target_Item;
	ItemType** Target_ItemPtr;

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


	// this->m_Command ��� ������ ��� �����غ���
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
					if (Value.find('.')!=std::string::npos) { //filter of file
						throw NameError(Value);
					}

					if (this->GetTargetItemPtrInPath(Value, Target_ItemPtr)) {

						//find
						this->m_fdCurPointer=dynamic_cast<FolderType*>(*Target_ItemPtr);

						// store History
						this->m_History.Push(this->m_fdCurPointer);

						//add recent item
						this->AddRecentItem(this->m_fdCurPointer);
						// Set Access Time
						this->m_fdCurPointer->GenerateTime(current_time);
						this->m_fdCurPointer->SetAccessTime(current_time);
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
						Target_Item = new FolderType;
						// set item info to find
						Target_Item->SetName(Value);
						Target_Item->SetPath(this->m_fdCurPointer->GetPath()+"/"+Value);
						//move folder made
						this->m_fdCurPointer->RetrieveItemByName(Target_Item);
						this->m_fdCurPointer=dynamic_cast<FolderType*>(Target_Item);

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
				std::cout <<"search : " <<ex.what() << '\n';
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
	// if find .(extensions) it is file
	if (Value.find(".txt")!=std::string::npos) { // text file : 1
		return 1;
	} else if (Value.find(".jpg")!=std::string::npos) { // jpg file : 2
		return 2;
	} else if (Value.find(".mp3")!=std::string::npos) { // mp3 file : 3
		return 3;
	}
	return 0; // it is folder
}

// Split the path in PathQueue
int BaseApplication::PathProcessor(std::string Path, LinkedQueue<std::string> &PathQueue){
	if (Path.find('/')==std::string::npos) { //if just move in current folder subfolder
		PathQueue.EnQueue(Path);
		return this->CheckValueItemType(Path); // folder return 0, text file : 1  jpg file : 2 mp3 file : 3;
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
	return this->CheckValueItemType(Name); // folder return 0, text file : 1  jpg file : 2 mp3 file : 3;
}

// using Path processor find TargetFolder
int BaseApplication::GetTargetItemPtrInPath(std::string Target, ItemType**& Target_ItemPtr, FolderType* Temp_curFolderPtr){
	ItemType* Temp_Item = nullptr ; //for temp to move folder
	ItemType* Target_Item = nullptr ; // for find target item

	// for path process
	LinkedQueue<std::string> PathQueue;

  Temp_curFolderPtr = this->m_fdCurPointer; //temp cur pointer

	// Split [Target]
	switch (this->PathProcessor(Target,PathQueue)) {
		case 0: // has path and last is folder(loop) or current folder' sub folder
		Temp_Item= new FolderType;
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
					Temp_Item->SetName(Temp_curFolderPtr->GetName());
					Temp_Item->SetPath(Temp_curFolderPtr->GetPath()+"/"+Temp_curFolderPtr->GetName());
					PathQueue.DeQueue();
					continue;

				} else if (PathQueue.Front()=="."){ //stay in current folder
					Temp_Item->SetName(Temp_curFolderPtr->GetName());
					Temp_Item->SetPath(Temp_curFolderPtr->GetPath()+"/"+Temp_curFolderPtr->GetName());
					PathQueue.DeQueue();
					continue;

				} else{
					Temp_Item->SetName(PathQueue.Front());
					Temp_Item->SetPath(Temp_curFolderPtr->GetPath()+"/"+PathQueue.Front());
					//search
					Temp_curFolderPtr->RetrieveItemByName(Temp_Item);
					PathQueue.DeQueue(); // DeQueue
					Temp_curFolderPtr=dynamic_cast<FolderType*>(Temp_Item); // set cur pointer again
				}
			}

			// Set the folder info PathQueue last word
			Target_Item= new FolderType;
			if (PathQueue.Front()=="..") { //move to parent
				if (!(Target_Item=Temp_curFolderPtr->GetParentPtr())) { //if Temp_Cur point root
					throw NoParent();
				}
				return 1;
			} else if (PathQueue.Front()=="."){ //stay in current folder
				Target_Item=Temp_curFolderPtr;
				return 1;

			} else{
				Target_Item->SetName(PathQueue.Front());
				Target_Item->SetPath(Temp_curFolderPtr->GetPath()+"/"+PathQueue.Front());
				if (!(Target_ItemPtr=Temp_curFolderPtr->RetrieveItemPtrByName(Target_Item))) {
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

		case 1: // has path and last is file(loop) or current folder' sub file
		case 2:
		case 3:
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
					Temp_Item->SetName(Temp_curFolderPtr->GetName());
					Temp_Item->SetPath(Temp_curFolderPtr->GetPath()+"/"+Temp_curFolderPtr->GetName());
					PathQueue.DeQueue();
					continue;

				} else if (PathQueue.Front()=="."){ //stay in current folder
					Temp_Item->SetName(Temp_curFolderPtr->GetName());
					Temp_Item->SetPath(Temp_curFolderPtr->GetPath()+"/"+Temp_curFolderPtr->GetName());
					PathQueue.DeQueue();
					continue;

				} else{
					Temp_Item->SetName(PathQueue.Front());
					Temp_Item->SetPath(Temp_curFolderPtr->GetPath()+"/"+PathQueue.Front());
					//search
					Temp_curFolderPtr->RetrieveItemByName(Temp_Item);
					PathQueue.DeQueue(); // DeQueue
					Temp_curFolderPtr=dynamic_cast<FolderType*>(Temp_Item); // set cur pointer again
				}
			}

			// Set the file info PathQueue last word
			switch (this->CheckValueItemType(PathQueue.Front())) {
				// text file : 1  jpg file : 2 mp3 file : 3;
				case 1:
				Target_Item=new TextFileType;
				break;

				case 2:
				Target_Item=new JPGFileType;
				break;

				case 3:
				Target_Item=new MP3FileType;
				break;
			}

			Target_Item->SetName(PathQueue.Front());
			Target_Item->SetPath(Temp_curFolderPtr->GetPath()+"/"+PathQueue.Front());
			if (!(Temp_curFolderPtr->RetrieveItemPtrByName(Target_Item))) {
				throw ItemNotFound(Target);
			}
			return 1;

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

// Create New Item in Current Folder.
int BaseApplication::NewItem(std::string Value){
	ItemType* Temp_Item;
	switch (this->CheckValueItemType(Value)) {
		case 0://folder
		Temp_Item = new FolderType;
		break;

    //file
    // text file : 1  jpg file : 2 mp3 file : 3;
		case 1:
		Temp_Item = new TextFileType;
		break;

		case 2:
		Temp_Item = new JPGFileType;
		break;

		case 3:
		Temp_Item = new MP3FileType;
		break;
	}
	//set the item info to add
	Temp_Item->SetName(Value); // Set item Name
	Temp_Item->SetPath(this->m_fdCurPointer->GetPath()+"/"+Value); // Set SubFile Path
	if (this->m_fdCurPointer->NewItem(Temp_Item)) {
		return 1; //Create New item
	}
	return 0;
}

// Delete Item you search in Current Folder.
int BaseApplication::DeleteItem(std::string Value){
	ItemType* Temp_Item;
	switch (this->CheckValueItemType(Value)) {
		case 0://folder
		Temp_Item = new FolderType;
		break;

		//file
		// text file : 1  jpg file : 2 mp3 file : 3;
		case 1:
		Temp_Item = new TextFileType;
		break;

		case 2:
		Temp_Item = new JPGFileType;
		break;

		case 3:
		Temp_Item = new MP3FileType;
		break;
	}
	//set the item info to add
	Temp_Item->SetName(Value); // Set item Name
	Temp_Item->SetPath(this->m_fdCurPointer->GetPath()+"/"+Value); // Set SubFile Path
	if (this->m_fdCurPointer->DeleteItem(Temp_Item)) {
		return 1; //Create New file
	}
	return 0;
}

// Update Item Name you search in Current Folder.
int BaseApplication::UpdateItemName(std::string Target, std::string Value){
	ItemType* Temp_Item;
	std::string current_time;

	switch (this->CheckValueItemType(Target)) { //check Target First
		case 0://Folder(Target)
		switch (this->CheckValueItemType(Value)) {
			case 0: //folder(Value)
			//set the folder info to update
			Temp_Item=new FolderType;
			Temp_Item->SetName(Target); // Set SubFolder Name
			Temp_Item->SetPath(this->m_fdCurPointer->GetPath()+"/"+Target); // Set SubFolder Path
			if (!(this->m_fdCurPointer->RetrieveItemByName(Temp_Item))) { //if not found
				throw ItemNotFound(Target);
			}
			Temp_Item->SetName(Value); // Update SubFolder Name
			Temp_Item->SetPath(this->m_fdCurPointer->GetPath()+"/"+Value); // Update SubFolder Path

			//set modifed time
			Temp_Item->GenerateTime(current_time);
			Temp_Item->SetModifiedTime(current_time);
			return 1; //Update Folder

			case 1: //file(Value)
			case 2: //file(Value)
			case 3: //file(Value)
			throw NameError(Value);
		}

		case 1://file(Target)
		Temp_Item=new TextFileType;
		switch (this->CheckValueItemType(Value)) {
			case 0: //folder(Value)
			case 2: //file(Value)
			case 3: //file(Value)
			throw NameError(Value);
		}
		break;

		case 2://file(Target)
		Temp_Item=new JPGFileType;
		switch (this->CheckValueItemType(Value)) {
			case 0: //folder(Value)
			case 1: //file(Value)
			case 3: //file(Value)
			throw NameError(Value);
		}
		break;

		case 3://file(Target)
		Temp_Item=new MP3FileType;
		switch (this->CheckValueItemType(Value)) {
			case 0: //folder(Value)
			case 1: //file(Value)
			case 2: //file(Value)
			throw NameError(Value);
		}
		break;
	}

	//file part only
	//set the file info to update
	Temp_Item->SetName(Target); // Set SubFile Name
	Temp_Item->SetPath(this->m_fdCurPointer->GetPath()+"/"+Target); // Set SubFile Path
	if (!(this->m_fdCurPointer->RetrieveItemPtrByName(Temp_Item))) { //if not found
		throw ItemNotFound(Target);
	}
	Temp_Item->SetName(Value); // Update SubFile Name
	Temp_Item->SetPath(this->m_fdCurPointer->GetPath()+"/"+Value); // Update SubFile Path

	//set modifed time
	Temp_Item->GenerateTime(current_time);
	Temp_Item->SetModifiedTime(current_time);
	return 1; //Update file

}

// Run File.
int BaseApplication::RunFile(std::string Target){
	//already filter folder in Run()

	//for setting value;
	ItemType** Target_ItemPtr = nullptr ;
	std::string current_time;

	if(this->GetTargetItemPtrInPath(Target,Target_ItemPtr)){
		dynamic_cast<FileType*>(*Target_ItemPtr)->Run();

		// add recent item
		this->AddRecentItem(*Target_ItemPtr);

		//set access time
        (*Target_ItemPtr)->GenerateTime(current_time);
        (*Target_ItemPtr)->SetAccessTime(current_time);
		return 1;
	}
	return 0;
}

// Copy Item.
int BaseApplication::CopyItem(std::string Target){
	//already filter Target=="" in this->Run()
  ItemType** Target_ItemPtr = nullptr ;

	if (this->GetTargetItemPtrInPath(Target,Target_ItemPtr)) {
		// if Heap has another memory
		if (this->Heap!=nullptr) {
			delete this->Heap;
		}
		if ((*Target_ItemPtr)->WhatIs()=="Folder") {
			this->Heap = new FolderType;
			//copy
			*dynamic_cast<FolderType*>(this->Heap) = *dynamic_cast<FolderType*>(*Target_ItemPtr);
		} else if ((*Target_ItemPtr)->WhatIs()=="TextFile") {
			this->Heap = new TextFileType;
			//copy
			*dynamic_cast<TextFileType*>(this->Heap) = *dynamic_cast<TextFileType*>(*Target_ItemPtr);
		} else if ((*Target_ItemPtr)->WhatIs()=="JPGFile") {
			this->Heap = new JPGFileType;
			//copy
			*dynamic_cast<JPGFileType*>(this->Heap) = *dynamic_cast<JPGFileType*>(*Target_ItemPtr);
		} else if ((*Target_ItemPtr)->WhatIs()=="MP3File") {
			this->Heap = new MP3FileType;
			//copy
			*dynamic_cast<MP3FileType*>(this->Heap) = *dynamic_cast<MP3FileType*>(*Target_ItemPtr);
		}
		return 1;
	}

	return 0;
}

// Cut/move Item.
int BaseApplication::CutItem(std::string Target){
	//already filter Target=="" in this->Run()
    ItemType** Target_ItemPtr = nullptr ;
	FolderType* Temp_curFolderPtr =nullptr;

	if (this->GetTargetItemPtrInPath(Target,Target_ItemPtr,Temp_curFolderPtr)) {
		// if Heap has another memory
		if (this->Heap!=nullptr) {
			delete this->Heap;
		}
		if ((*Target_ItemPtr)->WhatIs()=="Folder") {
			this->Heap = new FolderType;
			//copy
			*dynamic_cast<FolderType*>(this->Heap) = *dynamic_cast<FolderType*>(*Target_ItemPtr);
		} else if ((*Target_ItemPtr)->WhatIs()=="TextFile") {
			this->Heap = new TextFileType;
			//copy
			*dynamic_cast<TextFileType*>(this->Heap) = *dynamic_cast<TextFileType*>(*Target_ItemPtr);
		} else if ((*Target_ItemPtr)->WhatIs()=="JPGFile") {
			this->Heap = new JPGFileType;
			//copy
			*dynamic_cast<JPGFileType*>(this->Heap) = *dynamic_cast<JPGFileType*>(*Target_ItemPtr);
		} else if ((*Target_ItemPtr)->WhatIs()=="MP3File") {
			this->Heap = new MP3FileType;
			//copy
			*dynamic_cast<MP3FileType*>(this->Heap) = *dynamic_cast<MP3FileType*>(*Target_ItemPtr);
		}

		//delete
		if (!Temp_curFolderPtr->DeleteItem(*Target_ItemPtr)) {
			throw ItemNotFound((*Target_ItemPtr)->GetName());
		}
		return 1;
	}
	return 0;
}

// Paste Item.
int BaseApplication::Paste(std::string Value){
	if (this->Heap==nullptr) { // if has no data in heap do nothing
		return 0;
	}

	if (Value.find('.')!=std::string::npos) { //filter file
		throw NameError(Value);
	}

	ItemType** Target_ItemPtr = nullptr;

	if (this->GetTargetItemPtrInPath(Value, Target_ItemPtr)) {
		//paste
		//set heap new path
		this->Heap->SetPath((*Target_ItemPtr)->GetPath()+"/"+this->Heap->GetName());
		dynamic_cast<FolderType*>(*Target_ItemPtr)->NewItem(this->Heap);
		return 1;
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
	ItemType* Temp_Item;
	FolderType Temp_Folder;
	switch (this->CheckValueItemType(Value)) {
		case 0://folder
		//set the folder info to find
		Temp_Item = new FolderType;
		break;

		case 1:// text file
		//set the folder info to find
		Temp_Item = new TextFileType;
		break;

		case 2:// jpg file
		//set the folder info to find
		Temp_Item = new JPGFileType;
		break;

		case 3:// mp3 file
		//set the folder info to find
		Temp_Item = new MP3FileType;
		break;
	}
	Temp_Item->SetName(Value); // Set SubFile Name
	Temp_Item->SetPath(this->m_fdCurPointer->GetPath()+"/"+Value); // Set SubFile Path
	if (this->m_fdCurPointer->RetrieveItemByName(Temp_Item)) {
		Temp_Item->DisplayInfoOnScreen();
		return ;
	}

}

// Display the Current Folder Information on Screen.
void BaseApplication::DisplayCurFolderInfo(){
	//display
	this->m_fdCurPointer->DisplayInfoOnScreen();
}

// Add Item record in Recently Folder.
int BaseApplication::AddRecentItem(ItemType * Temp_Item){
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
