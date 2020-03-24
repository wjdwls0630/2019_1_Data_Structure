#include "FolderType.h"
#pragma warning(disable:4996)//control error of localtime()

//get folder name
string FolderType::getName() {
	return name;
}

//get folder location
string FolderType::getLocation() {
	return location;
}

string FolderType::getLocationName()
{
	string ln = location + "\\" + name;
	if (ln.substr(0, 1) == "\\") {
		ln = ln.substr(1);
	}
	if (ln.length() > 3) {
		if (ln.substr(3, 1) == "\\" && ln.substr(2, 1) == "\\") {
			ln = ln.substr(0, 3) + ln.substr(4);
		}
	}
	return ln;
}

//get folder size
int FolderType::getSize() {
	return size;
}

//get date of when folder was created
string FolderType::getDate() {
	return date;
}

//get the number of folder inside current folder
int FolderType::getTheNumOfFolder() {
	return theNumOfFolder;
}

//get the number of file inside current folder
int FolderType::getTheNumOfFile() {
	return theNumOfFile;
}

AVLtree<FolderType>* FolderType::getSubFolderList()
{
	if (theNumOfFolder != 0) {
		return subFolderList;
	}
	return nullptr;
}

AVLtree<FileType>* FolderType::getSubFileList()
{
	if (theNumOfFile != 0) {
		return subFileList;
	}
	return nullptr;
}

//set folder name
void FolderType::setName(string inName) {
	name = inName;
}

//set location of current folder
void FolderType::setLocation(string inLocation) {
	location = inLocation;
}

//set size of current folder
void FolderType::setSize(int inSize) {
	size = inSize;
}

//set created date of current folder
void FolderType::setDate()
{
	time_t tt;

	time(&tt);

	struct tm* ti;

	ti = localtime(&tt);

	stringstream ss;
	ss << setw(4) << ti->tm_year + 1900 << "/ " << setfill('0') << setw(2)
		<< ti->tm_mon + 1 << "/ " << setfill('0') << setw(2) << ti->tm_mday << ", " << setfill('0') << setw(2) << ti->tm_hour << ":" << setfill('0') << setw(2)
		<< ti->tm_min << ":" << setfill('0') << setw(2) << ti->tm_sec <<"\0";

	//copy the stream buffer to name 
	date = ss.str();
}

//set data memeber upperFolder's address to input data's address
void FolderType::setUpperFolder(FolderType* upperFolder) {
	this->upperFolder = upperFolder;
}

//set name of folder obtained from user 
void FolderType::setNameFromKB() {
	string inName;
	cout << "\tEnter folder name: ";
	cin >> inName;
	setName(inName);
}

//set property of folder obtained from user
void FolderType::setPropertyFromKB() {
	setNameFromKB();
}

void FolderType::setSubFolderList(AVLtree<FolderType>* inItem)
{
	subFolderList = inItem;
}

void FolderType::setSubFileList(AVLtree<FileType>* inItem)
{
	subFileList = inItem;
}

//display current folder name
void FolderType::displayName() {
	cout << "\tFolder name : " << name << endl;
}

//display current folder location
void FolderType::displayLocation() {
	cout << "\tLocation : " << location << endl;
}

//display folder size
void FolderType::displaySize() {
	cout << "\tSize : " << size << endl;
}

//display created date of current folder
void FolderType::displayDate() {
	cout << "\tCreated date : " << date << endl;
}

//display property of current folder
void FolderType::displayProperty() {
	cout << "\t-----------------------------------------------" << endl;
	displayName();
	displayLocation();
	displaySize();
	displayDate();
	displayTheNumOfFolder();
	displayTheNumOfFile();
	if (theNumOfFolder != 0) {
		displaySubFolders();
	}
	else {
		cout << "\t-----------------------------------------------" << endl;
	}
	if (theNumOfFile != 0) {
		displaySubFiles();
	}
}

//display current folder's sublist and set input folder's address to certain folder
int FolderType::openFolderAtSFL(FolderType *& m_curFolder, const string& name)
{
	//do if subfolder list exist
	if (subFolderList != NULL) {

		FolderType* data = new FolderType();
		data->setName(name);
		//set input data's location to find
		data->setLocation((*m_curFolder).getLocationName());

		if (subFolderList->findT(data)) {
			m_curFolder = data;
			return 1;
		}
		else {
			return 0;
		}
	}
	return 0;
}

//set input data's address to upperFolder's address
int FolderType::openUpperFolder(FolderType*& m_curFolder) {
	if (this->location != "") {
		m_curFolder = upperFolder;
		return 1;
	}
	else {
		return 0;
	}
}

//add folder to subfolder list
int FolderType::addFolderToSFL(FolderType& inItem)
{
	//allocate memory to subFolderList if there is no folder inside current folder
	if (theNumOfFolder == 0) {
		subFolderList = new AVLtree<FolderType>();
	}

	//if adding processs is completed successfully, increase the number of folder by 1, else show message
	if (subFolderList->addT(inItem)) {
		theNumOfFolder++;
	}
	else {
		cout << endl << "\tCan't add folder(Folder already exists!)" << endl << endl;
		return 0;
	}
	return 1;
}

//get folder name from user and delete folder from subfolder list
int FolderType::deleteFolderFromSFL(FolderType& inItem)
{
	if (theNumOfFolder == 0) {
		return 0;
	}

	//if deleting processs is completed successfully, decrease the number of folder by 1, else show message
	if (subFolderList->deleteT(inItem)) {
		theNumOfFolder--;
		return 1;
	}
	else {
		return 0;
	}
}

int FolderType::deleteFolderFromSFLtemporarily(FolderType & inItem)
{
	if (theNumOfFolder == 0) {
		return 0;
	}
	TreeNode<FolderType>* result;
	if (subFolderList->deleteTtemporarily(inItem, result)) {
		theNumOfFolder--;
		return 1;
	}
	else {
		return 0;
	}
}

//rename a folder in current path
int FolderType::renameFolder(FolderType*& inItem, const string& newName) {

	//find folder if subfolder list is not empty
	if (subFolderList != NULL) {
		if (subFolderList->findT(inItem)) {
			TreeNode<FolderType>* temp;
			//delete found node and rebalance
			subFolderList->deleteTtemporarily((*inItem), temp);
			temp->left = NULL;
			temp->right = NULL;

			inItem->setName(newName);
			inItem->setLocation(this->getLocationName());

			//add node and rebalance
			subFolderList->addNode(temp);
			return 1;
		}
	}
	return 0;
}

//display names of folders inside subfolder list
void FolderType::displaySubFolders() {
	FolderType* data;
	if (theNumOfFolder != 0) {
		subFolderList->resetList();
		cout << "\t-----------------------------------------------" << endl;
		cout << "\tInside this folder" << endl;
		for (int i = 0; i < theNumOfFolder; i++) {
			subFolderList->getNextT(data);
			data->displayName();
		}
		cout << "\t-----------------------------------------------" << endl;
	}
	else {
		cout << endl << "\t0 folder(s) inside" << endl << endl;
	}
}

//display the number of folder inside current folder
void FolderType::displayTheNumOfFolder() {
	cout << '\t' << theNumOfFolder << " folder(s) inside" << endl;
}

//set the number of folders found and return Folders form of linked list
void FolderType::searchFolderName(FolderType& input, int& theNumOfFound, SortedLinkedList<FolderType*>& foundlist)
{
	//find the folders if subfolder list exists
	if (subFolderList != NULL) {
		subFolderList->resetList();
		FolderType* temp;
		for (int i = 0; i < theNumOfFolder; i++) {
			subFolderList->getNextT(temp);
			if (temp->getName().find(input.getName()) != string::npos) {
				foundlist.addT(temp);
				theNumOfFound++;
			}
			temp->searchFolderName(input, theNumOfFound, foundlist);
		}
	}
	return;
}

//search the folder which is exactly same with input
FolderType * FolderType::searchExactFolderName(FolderType & input)
{
	FolderType* temp;
	if (subFolderList != NULL) {
		subFolderList->resetList();
		for (int i = 0; i < theNumOfFolder; i++) {
			subFolderList->getNextT(temp);
			if (input == (*temp)) {
				return temp;
			}
		}
	}
	return NULL;
}

//get file name from user and add file to subfile list
int FolderType::addFileToSFL(FileType& inItem) {
	if (theNumOfFile == 0) {
		subFileList = new AVLtree<FileType>();
	}
	if (subFileList->addT(inItem)) {
		theNumOfFile++;
		return 1;
	}
	return 0;
}

//get file name from user and delete folder from subfile list
int FolderType::deleteFileFromSFL(FileType& inItem)
{
	if (theNumOfFile == 0) {
		return 0;
	}
	if (subFileList->deleteT(inItem)) {
		theNumOfFile--;
		return 1;
	}
	return 0;
}

int FolderType::deleteFileFromSFLtemporarily(FileType & inItem)
{
	if (theNumOfFile == 0) {
		return 0;
	}
	TreeNode<FileType>* result;
	if (subFileList->deleteTtemporarily(inItem, result)) {
		theNumOfFile--;
		return 1;
	}
	return 0;
}

//rename a file in current path
int FolderType::renameFile(FileType*& inItem, string& newName) {
	
	//find file if subfolder list is not empty
	if (subFileList != NULL) {

		if (subFileList->findT(inItem)) {
			TreeNode<FileType>* temp;
			//delete found node and rebalance
			subFileList->deleteTtemporarily((*inItem), temp);
			temp->left = NULL;
			temp->right = NULL;

			inItem->setName(newName);
			inItem->setLocation(this->getLocationName());
			int dotIndex = newName.find_last_of(".");
			if (dotIndex != string::npos) {
				inItem->setExtension(newName.substr(dotIndex));
			}

			//add node and rebalance
			subFileList->addNode(temp);
			return 1;
		}
	}
	return 0;
}

//display names of files inside current subfile list
void FolderType::displaySubFiles() {
	FileType* data;
	if (theNumOfFile != 0) {
		subFileList->resetList();
		cout << "\t-----------------------------------------------" << endl;
		cout << "\tInside this folder" << endl;
		for (int i = 0; i < theNumOfFile; i++) {
			subFileList->getNextT(data);
			data->displayName();
		}
		cout << "\t-----------------------------------------------" << endl;
	}
	else {
		cout << endl << "\t0 file(s) inside" << endl << endl;
	}
}

void FolderType::displayTheNumOfFile() {
	cout << '\t' << theNumOfFile << " file(s) inside" << endl;
}

//set the number of files found and return Folders form of linked list
void FolderType::searchFileName(FileType& input, int& theNumOfFound, SortedLinkedList<FileType*>& foundlist)
{

	//find the folders if subfolder list exists
	if (subFileList != NULL) {
		subFileList->resetList();
		FileType* temp;
		for (int i = 0; i < theNumOfFile; i++) {
			subFileList->getNextT(temp);
			if (temp->getName().find(input.getName()) != string::npos) {
				foundlist.addT(temp);
				theNumOfFound++;
			}
		}
	}

	//find the files in the subfolders if subFolder exist
	FolderType* tempFol;
	if (subFolderList != NULL) {
		subFolderList->resetList();
		for (int i = 0; i < theNumOfFolder; i++) {
			subFolderList->getNextT(tempFol);
			tempFol->searchFileName(input, theNumOfFound, foundlist);
		}
	}
	return;
}

//search a specific folder
FileType* FolderType::searchExactFileName(FileType & input)
{
	FileType* temp;
	if (subFileList != NULL) {
		subFileList->resetList();
		for (int i = 0; i < theNumOfFile; i++) {
			subFileList->getNextT(temp);
			if (input == (*temp)) {
				return temp;
			}
		}
	}
	return NULL;
}

//check two folders' name and location are same
bool FolderType::operator==(const FolderType& dataBeingCompared) const {
	bool isTrue = false;
	if ((this->name == dataBeingCompared.name) && (this->location == dataBeingCompared.location)) {
		isTrue = true;
	}
	return isTrue;
}

//check two folders' name compare by name
bool FolderType::operator>(const FolderType& dataBeingCompared) const {
	if (this->name > dataBeingCompared.name) {
		return true;
	}
	return false;
}

//check two folders' name compare by name
bool FolderType::operator<(const FolderType& dataBeingCompared) const {
	if (this->name < dataBeingCompared.name) {
		return true;
	}
	return false;
}
