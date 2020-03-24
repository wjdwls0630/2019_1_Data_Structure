#include "project02.h"

project02::project02(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	this->setWindowTitle("Folder And File Management");
	QString address = QString::fromUtf8(m_curFolder->getLocationName().c_str());
	ui.lineEdit->setText(address);
	this->setWindowIcon(QIcon(":/project02/mainWindow"));

	m_RecentlyFolder.autoEnQueue(*m_curFolder);
	m_goBackForthFolder.autoPush(m_curFolder);

	QObject::connect(ui.actionCreate, SIGNAL(triggered()), this, SLOT(newFolder()));
	QObject::connect(ui.actionDelete, SIGNAL(triggered()), this, SLOT(deleteFolder()));
	QObject::connect(ui.actionRename, SIGNAL(triggered()), this, SLOT(renameFolder()));
	QObject::connect(ui.actionOpen_Folder_at_current_folder, SIGNAL(triggered()), this, SLOT(openFolderAtSFL()));
	QObject::connect(ui.actionGo_to_upper_Folder, SIGNAL(triggered()), this, SLOT(openUF()));
	QObject::connect(ui.actionGo_Back, SIGNAL(triggered()), this, SLOT(goBack()));
	QObject::connect(ui.actionShow_Back_History, SIGNAL(triggered()), this, SLOT(showBacks()));
	QObject::connect(ui.actionShow_Front_History, SIGNAL(triggered()), this, SLOT(showFronts()));
	QObject::connect(ui.actionCurrent_Folder_Property,SIGNAL(triggered()), this, SLOT(showFolderProperty()));
	QObject::connect(ui.actionClear_History, SIGNAL(triggered()), this, SLOT(clearHistory()));
	QObject::connect(ui.actionCreate_2, SIGNAL(triggered()), this, SLOT(newFile()));
	QObject::connect(ui.actionDelete_2, SIGNAL(triggered()), this, SLOT(deleteFile()));
	QObject::connect(ui.actionRename_2, SIGNAL(triggered()), this, SLOT(renameFile()));
	QObject::connect(ui.actionOpen_File_At_Current_Folder, SIGNAL(triggered()), this, SLOT(ReadWriteDataToFile()));
	QObject::connect(ui.actionShow_File_Property, SIGNAL(triggered()), this, SLOT(showFileProperty()));
	QObject::connect(ui.actionRetrieve_Folder_By_Name_2, SIGNAL(triggered()), this, SLOT(retrieveFolderByName()));
	QObject::connect(ui.actionRetrieve_File_By_Name_2, SIGNAL(triggered()), this, SLOT(retrieveFileByName()));
	QObject::connect(ui.actionRetrieve_Folder_And_File_By_Name_2, SIGNAL(triggered()), this, SLOT(retrieveFolderAndFileByName()));
	QObject::connect(ui.actionRetrieve_Folder_By_Name_3, SIGNAL(triggered()), this, SLOT(retrieveFolderByName_current()));
	QObject::connect(ui.actionRetrieve_File_By_Name_3, SIGNAL(triggered()), this, SLOT(retrieveFileByName_current()));
	QObject::connect(ui.actionRetrieve_Folder_And_File_By_Name_3, SIGNAL(triggered()), this, SLOT(retrieveFolderAndFileByName_current()));
	QObject::connect(ui.actionCopy, SIGNAL(triggered()), this, SLOT(copyFolder()));
	QObject::connect(ui.actionCut, SIGNAL(triggered()), this, SLOT(cutFolder()));
	QObject::connect(ui.actionCopy_2, SIGNAL(triggered()), this, SLOT(copyFile()));
	QObject::connect(ui.actionCut_2, SIGNAL(triggered()), this, SLOT(cutFile()));
	QObject::connect(ui.actionPaste, SIGNAL(triggered()), this, SLOT(paste()));
	QObject::connect(ui.actionPaste_2, SIGNAL(triggered()), this, SLOT(paste()));
}

void project02::newFolder()
{
	//create pushbutton and label
	QPushButton* button = new QPushButton();
	QLabel* label = new QLabel("Folder");

	//get folder name from user and set folder name and location
	bool ok;
	QString Qname = QInputDialog::getText(this, "New folder", "Enter folder name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
	string name = Qname.toUtf8().constData();
	FolderType data;
	data.setName(name);
	data.setLocation(m_curFolder->getLocationName());
	data.setUpperFolder(m_curFolder);

	//change window content if user click ok AND the folder is added
	if ((ok == true)&&(m_curFolder->addFolderToSFL(data))) {
		//clear contents
		row = 1;
		for (int i = 0; i < theNumOfItems ; i++) {
			ui.formLayout->removeRow(row);
		}

		//show folders in sorted way
		FolderType* data_show;
		if (m_curFolder->getTheNumOfFolder() != 0) {
			AVLtree<FolderType>* SFL = m_curFolder->getSubFolderList();
			SFL->resetList();
			for (int i = 0; i < m_curFolder->getTheNumOfFolder(); i++) {
				//create pushbutton for temporary saving and show
				QPushButton* button_temp = new QPushButton;
				QLabel* label_temp = new QLabel;
				label_temp->setText("Folder");
				SFL->getNextT(data_show);

				//string to QString conversion
				QString Qname_temp = QString::fromUtf8(data_show->getName().c_str());
				ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
				button_temp->setText(Qname_temp);
				ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

				QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));

				//set connect signal and slot
				signalmapper->setMapping(button_temp, Qname_temp);
				QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));
				row++;
			}
		}
		//show files in sorted way
		FileType* data_show_file;
		if (m_curFolder->getTheNumOfFile() != 0) {
			AVLtree<FileType>* SFL = m_curFolder->getSubFileList();
			SFL->resetList();
			for (int i = 0; i < m_curFolder->getTheNumOfFile(); i++) {
				//create pushbutton for temporary saving and show
				QPushButton* button_temp = new QPushButton;
				QLabel* label_temp = new QLabel;
				label_temp->setText("File");
				SFL->getNextT(data_show_file);

				//string to QString conversion
				QString Qname_temp = QString::fromUtf8(data_show_file->getName().c_str());
				ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
				button_temp->setText(Qname_temp);
				ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

				QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));

				//set connect signal and slot
				signalmapper->setMapping(button_temp, Qname_temp);
				QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));
				row++;
			}
		}
		theNumOfFolders++;
		theNumOfItems++;
	}
	else if((ok == true) && !(m_curFolder->addFolderToSFL(data))){
		QMessageBox::warning(this, tr("Error"), tr("Can't add folder \n (Folder already exists!)"));
	}
}

void project02::deleteFolder()
{
	//show message if there is no folders
	if (theNumOfFolders == 0) {
		QMessageBox::warning(this, tr("Error"), tr("Please add folder first..."));
		return;
	}

	//get folder name from user and set folder name and location
	bool ok;
	QString Qname = QInputDialog::getText(this, "Delete Folder", "Enter folder name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
	string name = Qname.toUtf8().constData();
	FolderType data;
	data.setName(name);
	data.setLocation(m_curFolder->getLocationName());

	//if deleting processs is completed successfully, decrease the number of folder by 1, else show message
	if ((ok == true) && (m_curFolder->deleteFolderFromSFL(data))) {
		//clear contents
		row = 1;
		for (int i = 0; i < theNumOfItems; i++) {
			ui.formLayout->removeRow(row);
		}

		//show folders in sorted way
		FolderType* data_show;
		if (m_curFolder->getTheNumOfFolder() != 0) {
			AVLtree<FolderType>* SFL = m_curFolder->getSubFolderList();
			SFL->resetList();
			for (int i = 0; i < m_curFolder->getTheNumOfFolder(); i++) {
				//create pushbutton for temporary saving and show
				QPushButton* button_temp = new QPushButton;
				QLabel* label_temp = new QLabel;
				label_temp->setText("Folder");
				SFL->getNextT(data_show);

				//string to QString conversion
				QString Qname_temp = QString::fromUtf8(data_show->getName().c_str());
				ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
				button_temp->setText(Qname_temp);
				ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

				QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));

				//set connect signal and slot
				signalmapper->setMapping(button_temp, Qname_temp);
				QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));
				row++;
			}
		}
		//show files in sorted way
		FileType* data_show_file;
		if (m_curFolder->getTheNumOfFile() != 0) {
			AVLtree<FileType>* SFL = m_curFolder->getSubFileList();
			SFL->resetList();
			for (int i = 0; i < m_curFolder->getTheNumOfFile(); i++) {
				//create pushbutton for temporary saving and show
				QPushButton* button_temp = new QPushButton;
				QLabel* label_temp = new QLabel;
				label_temp->setText("File");
				SFL->getNextT(data_show_file);

				//string to QString conversion
				QString Qname_temp = QString::fromUtf8(data_show_file->getName().c_str());
				ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
				button_temp->setText(Qname_temp);
				ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

				//set connect signal and slot
				signalmapper->setMapping(button_temp, Qname_temp);
				QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));
				row++;
			}
		}
		theNumOfFolders--;
		theNumOfItems--;
	}
	else if ((ok == true) && !(m_curFolder->deleteFolderFromSFL(data))) {
		QMessageBox::warning(this, tr("Error"), tr("Can't delete folder \n (Folder doesn't exist!)"));
	}
}

void project02::renameFolder()
{
	if (theNumOfFolders == 0) {
		QMessageBox::warning(this, tr("Error"), tr("Please add folder first..."));
		return;
	}

	//get folder name from user and set folder name and location
	bool ok;
	QString Qname = QInputDialog::getText(this, "Rename folder", "Enter folder name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
	string name = Qname.toUtf8().constData();
	FolderType* data = new FolderType;
	data->setName(name);
	data->setLocation(m_curFolder->getLocationName());

	if (ok == true) {
		//get new name from user
		bool ok_new;
		QString Qname_new = QInputDialog::getText(this, "Folder name input", "Enter new folder name : ", QLineEdit::Normal, QDir::home().dirName(), &ok_new);
		string name_new = Qname_new.toUtf8().constData();

		if (ok_new == true) {
			//do if folder exist
			if (m_curFolder->renameFolder(data, name_new)) {
				//clear contents
				row = 1;
				for (int i = 0; i < theNumOfItems; i++) {
					ui.formLayout->removeRow(row);
				}

				//show folders in sorted way
				FolderType* data_show;
				if (m_curFolder->getTheNumOfFolder() != 0) {
					AVLtree<FolderType>* SFL = m_curFolder->getSubFolderList();
					SFL->resetList();
					for (int i = 0; i < m_curFolder->getTheNumOfFolder(); i++) {
						//create pushbutton for temporary saving and show
						QPushButton* button_temp = new QPushButton;
						QLabel* label_temp = new QLabel;
						label_temp->setText("Folder");
						SFL->getNextT(data_show);

						//string to QString conversion
						QString Qname_temp = QString::fromUtf8(data_show->getName().c_str());
						ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
						button_temp->setText(Qname_temp);
						ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

						QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
						QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));

						//set connect signal and slot
						signalmapper->setMapping(button_temp, Qname_temp);
						QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
						QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));
						row++;
					}
				}

				//show files in sorted way
				FileType* data_show_file;
				if (m_curFolder->getTheNumOfFile() != 0) {
					AVLtree<FileType>* SFL = m_curFolder->getSubFileList();
					SFL->resetList();
					for (int i = 0; i < m_curFolder->getTheNumOfFile(); i++) {
						//create pushbutton for temporary saving and show
						QPushButton* button_temp = new QPushButton;
						QLabel* label_temp = new QLabel;
						label_temp->setText("File");
						SFL->getNextT(data_show_file);

						//string to QString conversion
						QString Qname_temp = QString::fromUtf8(data_show_file->getName().c_str());
						ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
						button_temp->setText(Qname_temp);
						ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

						QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
						QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));

						//set connect signal and slot
						signalmapper->setMapping(button_temp, Qname_temp);
						QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
						QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));
						row++;
					}
				}
			}
			else {
				QMessageBox::warning(this, tr("Error"), tr("Can't rename folder \n (Folder doesn't exist!)"));
			}
		}
	}
}

void project02::openUF()
{
	//change current folder's address to upper folder
	if (m_curFolder->openUpperFolder(m_curFolder)) {
		//clear contents
		row = 1;
		for (int i = 0; i < theNumOfItems; i++) {
			ui.formLayout->removeRow(row);
		}
		theNumOfItems = 0;

		//change current path
		QString QlocationName = QString::fromUtf8(m_curFolder->getLocationName().c_str());
		ui.lineEdit->setText(QlocationName);

		theNumOfItems = m_curFolder->getTheNumOfFolder() + m_curFolder->getTheNumOfFile();
		theNumOfFolders = m_curFolder->getTheNumOfFolder();
		theNumOfFiles = m_curFolder->getTheNumOfFile();

		//show folders in sorted way
		FolderType* data_show;
		if (m_curFolder->getTheNumOfFolder() != 0) {
			AVLtree<FolderType>* SFL = m_curFolder->getSubFolderList();
			SFL->resetList();
			for (int i = 0; i < m_curFolder->getTheNumOfFolder(); i++) {
				//create pushbutton for temporary saving and show
				QPushButton* button_temp = new QPushButton;
				QLabel* label_temp = new QLabel;
				label_temp->setText("Folder");
				SFL->getNextT(data_show);

				//string to QString conversion
				QString Qname_temp = QString::fromUtf8(data_show->getName().c_str());
				ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
				button_temp->setText(Qname_temp);
				ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

				QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));

				//set connect signal and slot
				signalmapper->setMapping(button_temp, Qname_temp);
				QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));
				row++;
			}
		}
		//show files in sorted way
		FileType* data_show_file;
		if (m_curFolder->getTheNumOfFile() != 0) {
			AVLtree<FileType>* SFL = m_curFolder->getSubFileList();
			SFL->resetList();
			for (int i = 0; i < m_curFolder->getTheNumOfFile(); i++) {
				//create pushbutton for temporary saving and show
				QPushButton* button_temp = new QPushButton;
				QLabel* label_temp = new QLabel;
				label_temp->setText("File");
				SFL->getNextT(data_show_file);

				//string to QString conversion
				QString Qname_temp = QString::fromUtf8(data_show_file->getName().c_str());
				ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
				button_temp->setText(Qname_temp);
				ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

				QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));

				//set connect signal and slot
				signalmapper->setMapping(button_temp, Qname_temp);
				QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));
				row++;
			}
		}
		m_RecentlyFolder.autoEnQueue(*m_curFolder);
		m_goBackForthFolder.autoPush(m_curFolder);
	}
	else {
		QMessageBox::warning(this, tr("Error"), tr("Can't go up. \n (This is root folder.)"));
	}
}

void project02::goBack()
{
	if (m_goBackForthFolder.goBackward(m_curFolder)) {
		//clear contents
		row = 1;
		for (int i = 0; i < theNumOfItems; i++) {
			ui.formLayout->removeRow(row);
		}
		theNumOfItems = 0;

		//change current path
		QString QlocationName = QString::fromUtf8(m_curFolder->getLocationName().c_str());
		ui.lineEdit->setText(QlocationName);

		theNumOfItems = m_curFolder->getTheNumOfFolder() + m_curFolder->getTheNumOfFile();
		theNumOfFolders = m_curFolder->getTheNumOfFolder();
		theNumOfFiles = m_curFolder->getTheNumOfFile();

		//show folders in sorted way
		FolderType* data_show;
		if (m_curFolder->getTheNumOfFolder() != 0) {
			AVLtree<FolderType>* SFL = m_curFolder->getSubFolderList();
			SFL->resetList();
			for (int i = 0; i < m_curFolder->getTheNumOfFolder(); i++) {
				//create pushbutton for temporary saving and show
				QPushButton* button_temp = new QPushButton;
				QLabel* label_temp = new QLabel;
				label_temp->setText("Folder");
				SFL->getNextT(data_show);

				//string to QString conversion
				QString Qname_temp = QString::fromUtf8(data_show->getName().c_str());
				ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
				button_temp->setText(Qname_temp);
				ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

				QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));

				//set connect signal and slot
				signalmapper->setMapping(button_temp, Qname_temp);
				QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));
				row++;
			}
		}
		//show files in sorted way
		FileType* data_show_file;
		if (m_curFolder->getTheNumOfFile() != 0) {
			AVLtree<FileType>* SFL = m_curFolder->getSubFileList();
			SFL->resetList();
			for (int i = 0; i < m_curFolder->getTheNumOfFile(); i++) {
				//create pushbutton for temporary saving and show
				QPushButton* button_temp = new QPushButton;
				QLabel* label_temp = new QLabel;
				label_temp->setText("File");
				SFL->getNextT(data_show_file);

				//string to QString conversion
				QString Qname_temp = QString::fromUtf8(data_show_file->getName().c_str());
				ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
				button_temp->setText(Qname_temp);
				ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

				QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));

				//set connect signal and slot
				signalmapper->setMapping(button_temp, Qname_temp);
				QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));
				row++;
			}
		}
	}
	else {
		QMessageBox::warning(this, tr("Error"), tr("Can't go back. \n (Back history doesn't exist.)"));
	}
}

void project02::showBacks()
{
	//create new window;
	SecondWindow secWindow;

	//get back history and put all in the new window
	SortedLinkedList<FolderType*> backFolders;
	backFolders = m_goBackForthFolder.getBackHistory();
	if (backFolders.getLength() != 0) {
		secWindow.addTitle_BackHistory();

		backFolders.resetList();
		FolderType** temp;
		for (int i = 0; i < backFolders.getLength(); i++) {
			backFolders.getNextT(temp);
			QString QlocationName = QString::fromUtf8((*temp)->getLocationName().c_str());
			QString Qint = QString::number(i+1);
			QLabel* label = new QLabel(QString(Qint + ". "));
			QPushButton* button = new QPushButton(QlocationName);
			secWindow.addRow((i + 1), label, button);

			//disconnecting signal and slots
			QObject::disconnect(button, SIGNAL(clicked()), signalmapper, SLOT(map()));
			QObject::disconnect(signalmapper, SIGNAL(mapped(const int&)), this, SLOT(openFrontResult(const int&)));
			QObject::disconnect(button, SIGNAL(clicked()), &secWindow, SLOT(close()));

			QObject::disconnect(button, SIGNAL(clicked()), signalmapper, SLOT(map()));
			QObject::disconnect(signalmapper, SIGNAL(mapped(const int&)), this, SLOT(openBackResult(const int&)));
			QObject::disconnect(button, SIGNAL(clicked()), &secWindow, SLOT(close()));

			//connecting signal and slots
			signalmapper->setMapping(button, i + 1);
			QObject::connect(button, SIGNAL(clicked()), signalmapper, SLOT(map()));
			QObject::connect(signalmapper, SIGNAL(mapped(const int&)), this, SLOT(openBackResult(const int&)));

			QObject::connect(button, SIGNAL(clicked()), &secWindow, SLOT(close()));
		}
		secWindow.setModal(true);
		secWindow.exec();
	}
	else {
		QMessageBox::warning(this, tr("Error"), tr("Can't go back. \n (Back history doesn't exist.)"));
	}
	//prevent memory leak
	backFolders.makeEmpty();
}

void project02::goFront()
{
	if (m_goBackForthFolder.goForward(m_curFolder)) {
		//clear contents
		row = 1;
		for (int i = 0; i < theNumOfItems; i++) {
			ui.formLayout->removeRow(row);
		}
		theNumOfItems = 0;

		//change current path
		QString QlocationName = QString::fromUtf8(m_curFolder->getLocationName().c_str());
		ui.lineEdit->setText(QlocationName);

		theNumOfItems = m_curFolder->getTheNumOfFolder() + m_curFolder->getTheNumOfFile();
		theNumOfFolders = m_curFolder->getTheNumOfFolder();
		theNumOfFiles = m_curFolder->getTheNumOfFile();

		//show folders in sorted way
		FolderType* data_show;
		if (m_curFolder->getTheNumOfFolder() != 0) {
			AVLtree<FolderType>* SFL = m_curFolder->getSubFolderList();
			SFL->resetList();
			for (int i = 0; i < m_curFolder->getTheNumOfFolder(); i++) {
				//create pushbutton for temporary saving and show
				QPushButton* button_temp = new QPushButton;
				QLabel* label_temp = new QLabel;
				label_temp->setText("Folder");
				SFL->getNextT(data_show);

				//string to QString conversion
				QString Qname_temp = QString::fromUtf8(data_show->getName().c_str());
				ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
				button_temp->setText(Qname_temp);
				ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

				QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));

				//set connect signal and slot
				signalmapper->setMapping(button_temp, Qname_temp);
				QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));
				row++;
			}
		}
		//show files in sorted way
		FileType* data_show_file;
		if (m_curFolder->getTheNumOfFile() != 0) {
			AVLtree<FileType>* SFL = m_curFolder->getSubFileList();
			SFL->resetList();
			for (int i = 0; i < m_curFolder->getTheNumOfFile(); i++) {
				//create pushbutton for temporary saving and show
				QPushButton* button_temp = new QPushButton;
				QLabel* label_temp = new QLabel;
				label_temp->setText("File");
				SFL->getNextT(data_show_file);

				//string to QString conversion
				QString Qname_temp = QString::fromUtf8(data_show_file->getName().c_str());
				ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
				button_temp->setText(Qname_temp);
				ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

				QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));

				//set connect signal and slot
				signalmapper->setMapping(button_temp, Qname_temp);
				QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));
				row++;
			}
		}
	}
	else {
		QMessageBox::warning(this, tr("Error"), tr("Can't go front. \n (Front history doesn't exist.)"));
	}
}

void project02::showFronts()
{
	//create new window;
	SecondWindow secWindow;

	//get front history and put all in the new window
	SortedLinkedList<FolderType*> frontFolders;
	frontFolders = m_goBackForthFolder.getFrontHistory();
	if (frontFolders.getLength() != 0) {
		secWindow.addTitle_FrontHistory();

		frontFolders.resetList();
		FolderType** temp;
		for (int i = 0; i < frontFolders.getLength(); i++) {
			frontFolders.getNextT(temp);
			QString QlocationName = QString::fromUtf8((*temp)->getLocationName().c_str());
			QString Qint = QString::number(i + 1);
			QLabel* label = new QLabel(QString(Qint + ". "));
			QPushButton* button = new QPushButton(QlocationName);
			secWindow.addRow((i + 1), label, button);

			//disconnecting signal and slots
			QObject::disconnect(button, SIGNAL(clicked()), signalmapper, SLOT(map()));
			QObject::disconnect(signalmapper, SIGNAL(mapped(const int&)), this, SLOT(openFrontResult(const int&)));
			QObject::disconnect(button, SIGNAL(clicked()), &secWindow, SLOT(close()));

			QObject::disconnect(button, SIGNAL(clicked()), signalmapper, SLOT(map()));
			QObject::disconnect(signalmapper, SIGNAL(mapped(const int&)), this, SLOT(openBackResult(const int&)));
			QObject::disconnect(button, SIGNAL(clicked()), &secWindow, SLOT(close()));

			//connecting signal and slots
			signalmapper->setMapping(button, i + 1);
			QObject::connect(button, SIGNAL(clicked()), signalmapper, SLOT(map()));
			QObject::connect(signalmapper, SIGNAL(mapped(const int&)), this, SLOT(openFrontResult(const int&)));

			QObject::connect(button, SIGNAL(clicked()), &secWindow, SLOT(close()));
		}
		secWindow.setModal(true);
		secWindow.exec();
	}
	else {
		QMessageBox::warning(this, tr("Error"), tr("Can't go front. \n (Front history doesn't exist.)"));
	}
	//prevent memory leak
	frontFolders.makeEmpty();
}

void project02::openBackResult(const int & n)
{
	for (int i = 0; i < n; i++) {
		goBack();
	}
}

void project02::openFrontResult(const int & n)
{
	for (int i = 0; i < n; i++) {
		goFront();
	}
}

void project02::showFolderProperty()
{
	SecondWindow secWindow;

	QLabel* nameLabel = new QLabel("Folder Name : ");
	QString Qname = QString::fromUtf8(m_curFolder->getName().c_str());
	QLabel* name = new QLabel(Qname);

	QLabel* locationLabel = new QLabel("Folder Location : ");
	QString Qlocation = QString::fromUtf8(m_curFolder->getLocation().c_str());
	QLabel* location = new QLabel(Qlocation);

	QLabel* sizeLabel = new QLabel("Folder Size : ");
	int size_int = m_curFolder->getSize();
	QString Qsize;
	if ((size_int >= 1024) && (size_int < 1024 * 1024)) {
		Qsize = QString::number((float)size_int / 1024);
		Qsize = Qsize + "KB";
	}
	else if ((size_int >= 1024 * 1024) && (size_int < pow(1024, 3))) {
		Qsize = QString::number((float)size_int / 1024 * 1024);
		Qsize = Qsize + "MB";
	}
	else if ((size_int >= pow(1024, 3) && (size_int < pow(1024, 4)))) {
		Qsize = QString::number((float)size_int / pow(1024, 3));
		Qsize = Qsize + "GB";
	}
	else {
		Qsize = QString::number(size_int);
		Qsize = Qsize + "Byte";
	}
	QLabel* size = new QLabel(Qsize);

	QLabel* dateLabel = new QLabel("Folder Created Date : ");
	QString Qdate = QString::fromUtf8(m_curFolder->getDate().c_str());
	QLabel* date = new QLabel(Qdate);

	QLabel* folderNumLabel = new QLabel("The number of folders inside : ");
	QString QfolderNum = QString::number(m_curFolder->getTheNumOfFolder());
	QLabel* folderNum = new QLabel(QfolderNum);

	QLabel* fileNumLabel = new QLabel("The number of files inside : ");
	QString QfileNum = QString::number(m_curFolder->getTheNumOfFile());
	QLabel* fileNum = new QLabel(QfileNum);

	secWindow.addTitle_FolderProperty();
	secWindow.addFolderProperty(2, nameLabel, name);
	secWindow.addFolderProperty(3, locationLabel, location);
	secWindow.addFolderProperty(5, sizeLabel, size);
	secWindow.addFolderProperty(6, dateLabel, date);
	secWindow.addFolderProperty(7, folderNumLabel, folderNum);
	secWindow.addFolderProperty(8, fileNumLabel, fileNum);

	secWindow.resize(300, 100);

	secWindow.setModal(true);
	secWindow.exec();
}

void project02::clearHistory()
{
	QMessageBox::StandardButton reply;
	reply = QMessageBox::question(this, "Clear History", "Do you really want to clear all history?", QMessageBox::Yes | QMessageBox::No);
	if (reply == QMessageBox::Yes) {
		m_RecentlyFolder.makeEmpty();
		m_goBackForthFolder.makeEmpty();
		QMessageBox::information(this, "Notice", "All History is cleared");
	}
}

int project02::checkType(string inString)
{
	if (inString == "class FolderType") {
		return FOLDERTYPE;
	}
	else if (inString == "class FileType") {
		return FILETYPE;
	}
	else {
		return UNKNOWN;
	}
}

int project02::copyFolderCommand(FolderType * copied, FolderType *& newFolder)
{
	//allocate memory for new folder and give original data
	newFolder = new FolderType;
	*newFolder = *copied;
	if (copied->getTheNumOfFolder() != 0) {
		copySubFolders(copied, newFolder);
		return 1;
	}
	return 0;
}

int project02::copySubFolders(FolderType * copied, FolderType *& newFolder)
{
	//allocate other memory to newFolderlist and add Folders
	AVLtree<FolderType>* newFolderList = new AVLtree<FolderType>;
	AVLtree<FolderType>* oldFolderList = copied->getSubFolderList();
	AVLtree<FileType>* newFileList = new AVLtree<FileType>;
	AVLtree<FileType>* oldFileList = copied->getSubFileList();
	FolderType* temp_folder;
	FolderType* data_folder;
	FileType* temp_file;
	FileType* data_file;

	if (copied->getTheNumOfFile() != 0) {
		oldFileList->resetList();
		for (int i = 0; i < copied->getTheNumOfFile(); i++) {
			data_file = new FileType;
			oldFileList->getNextT(temp_file);
			*data_file = *temp_file;
			newFileList->addT(*data_file);
		}
		newFolder->setSubFileList(newFileList);
	}

	if (copied->getTheNumOfFolder() != 0) {
		oldFolderList->resetList();
		for (int i = 0; i < copied->getTheNumOfFolder(); i++) {
			data_folder = new FolderType;
			oldFolderList->getNextT(temp_folder);
			*data_folder = *temp_folder;
			//copy subfolders reculsively
			copySubFolders(temp_folder, data_folder);
			newFolderList->addT(*data_folder);
		}
		newFolder->setSubFolderList(newFolderList);
		return 1;
	}
	return 0;
}

void project02::openFolder(QString Qname)
{
	//clear contents
	row = 1;
	for (int i = 0; i < theNumOfItems; i++) {
		ui.formLayout->removeRow(row);
	}
	theNumOfFolders = 0;
	theNumOfItems = 0;

	//change current folder's address to one folder of subfolder
	string name = Qname.toUtf8().constData();
	if (m_curFolder->openFolderAtSFL(m_curFolder, name)) {

		//change current path
		QString QlocationName = QString::fromUtf8(m_curFolder->getLocationName().c_str());
		ui.lineEdit->setText(QlocationName);

		theNumOfItems = m_curFolder->getTheNumOfFolder() + m_curFolder->getTheNumOfFile();
		theNumOfFolders = m_curFolder->getTheNumOfFolder();
		theNumOfFiles = m_curFolder->getTheNumOfFile();

		//show folders in sorted way
		FolderType* data_show;
		if (m_curFolder->getTheNumOfFolder() != 0) {
			AVLtree<FolderType>* SFL = m_curFolder->getSubFolderList();
			SFL->resetList();
			for (int i = 0; i < m_curFolder->getTheNumOfFolder(); i++) {
				//create pushbutton for temporary saving and show
				QPushButton* button_temp = new QPushButton;
				QLabel* label_temp = new QLabel;
				label_temp->setText("Folder");
				SFL->getNextT(data_show);

				//string to QString conversion
				QString Qname_temp = QString::fromUtf8(data_show->getName().c_str());
				ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
				button_temp->setText(Qname_temp);
				ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

				//set connect signal and slot
				signalmapper->setMapping(button_temp, Qname_temp);
				QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));
				row++;
			}
		}
		m_RecentlyFolder.autoEnQueue(*m_curFolder);
		m_goBackForthFolder.autoPush(m_curFolder);
	}
}

void project02::openFolderAtSFL()
{
	//get folder name from user and set folder name and location
	bool ok;
	QString Qname = QInputDialog::getText(this, "Folder name input", "Enter folder name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
	string name = Qname.toUtf8().constData();
	FolderType data;
	data.setName(name);
	data.setLocation(m_curFolder->getLocationName());
	if (ok == true) {
		if (m_curFolder->openFolderAtSFL(m_curFolder, name)) {
			//clear contents
			row = 1;
			for (int i = 0; i < theNumOfItems; i++) {
				ui.formLayout->removeRow(row);
			}
			theNumOfFolders = 0;
			theNumOfItems = 0;

			//change current path
			QString QlocationName = QString::fromUtf8(m_curFolder->getLocationName().c_str());
			ui.lineEdit->setText(QlocationName);

			theNumOfItems = m_curFolder->getTheNumOfFolder() + m_curFolder->getTheNumOfFile();
			theNumOfFolders = m_curFolder->getTheNumOfFolder();
			theNumOfFiles = m_curFolder->getTheNumOfFile();

			//show folders in sorted way
			FolderType* data_show;
			if (m_curFolder->getTheNumOfFolder() != 0) {
				AVLtree<FolderType>* SFL = m_curFolder->getSubFolderList();
				SFL->resetList();
				for (int i = 0; i < m_curFolder->getTheNumOfFolder(); i++) {
					//create pushbutton for temporary saving and show
					QPushButton* button_temp = new QPushButton;
					QLabel* label_temp = new QLabel;
					label_temp->setText("Folder");
					SFL->getNextT(data_show);

					//string to QString conversion
					QString Qname_temp = QString::fromUtf8(data_show->getName().c_str());
					ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
					button_temp->setText(Qname_temp);
					ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

					//set connect signal and slot
					signalmapper->setMapping(button_temp, Qname_temp);
					QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
					QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));
					row++;
				}
			}
			m_RecentlyFolder.autoEnQueue(*m_curFolder);
			m_goBackForthFolder.autoPush(m_curFolder);

		}
		else {
			QMessageBox::warning(this, tr("Error"), tr("Can't open folder \n (Folder doesn't exists!)"));
		}
	}
}

void project02::newFile()
{
	//create pushbutton and label
	QPushButton* button = new QPushButton();
	QLabel* label = new QLabel("File");

	//get folder name from user and set folder name and location
	bool ok;
	QString Qname = QInputDialog::getText(this, "File name input", "Enter file name with Extension : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
	string name = Qname.toUtf8().constData();
	FileType data;
	data.setName(name);
	data.setLocation(m_curFolder->getLocationName());
	string passName = data.getName();
	int dotIndex = passName.find_last_of(".");
	if (dotIndex != string::npos) {
		data.setExtension(passName.substr(dotIndex));
	}

	//change window content if user click ok AND the folder is added
	if ((ok == true) && (m_curFolder->addFileToSFL(data))) {
		//clear contents
		row = 1;
		for (int i = 0; i < theNumOfItems; i++) {
			ui.formLayout->removeRow(row);
		}

		//show folders in sorted way
		FolderType* data_show;
		if (m_curFolder->getTheNumOfFolder() != 0) {
			AVLtree<FolderType>* SFL = m_curFolder->getSubFolderList();
			SFL->resetList();
			for (int i = 0; i < m_curFolder->getTheNumOfFolder(); i++) {
				//create pushbutton for temporary saving and show
				QPushButton* button_temp = new QPushButton;
				QLabel* label_temp = new QLabel;
				label_temp->setText("Folder");
				SFL->getNextT(data_show);

				//string to QString conversion
				QString Qname_temp = QString::fromUtf8(data_show->getName().c_str());
				ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
				button_temp->setText(Qname_temp);
				ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);


				QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));

				//set connect signal and slot
				signalmapper->setMapping(button_temp, Qname_temp);
				QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));
				row++;
			}
		}
		//show files in sorted way
		FileType* data_show_file;
		if (m_curFolder->getTheNumOfFile() != 0) {
			AVLtree<FileType>* SFL = m_curFolder->getSubFileList();
			SFL->resetList();
			for (int i = 0; i < m_curFolder->getTheNumOfFile(); i++) {
				//create pushbutton for temporary saving and show
				QPushButton* button_temp = new QPushButton;
				QLabel* label_temp = new QLabel;
				label_temp->setText("File");
				SFL->getNextT(data_show_file);

				//string to QString conversion
				QString Qname_temp = QString::fromUtf8(data_show_file->getName().c_str());
				ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
				button_temp->setText(Qname_temp);
				ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

				QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));

				//set connect signal and slot
				signalmapper->setMapping(button_temp, Qname_temp);
				QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));
				row++;
			}
		}
		fsOutput.open(passName, ios::trunc);
		fsOutput.close();

		theNumOfFiles++;
		theNumOfItems++;
	}
	else if ((ok == true) && !(m_curFolder->addFileToSFL(data))) {
		QMessageBox::warning(this, tr("Error"), tr("Can't add file \n (File already exists!)"));
	}
}

void project02::deleteFile()
{
	//show message if there is no folders
	if (theNumOfFiles == 0) {
		QMessageBox::warning(this, tr("Error"), tr("Please add file first..."));
		return;
	}

	//get folder name from user and set folder name and location
	bool ok;
	QString Qname = QInputDialog::getText(this, "File name input", "Enter file name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
	string name = Qname.toUtf8().constData();
	FileType data;
	data.setName(name);
	data.setLocation(m_curFolder->getLocationName());

	//if deleting processs is completed successfully, decrease the number of folder by 1, else show message
	if ((ok == true) && (m_curFolder->deleteFileFromSFL(data))) {
		remove(name.c_str());
		//clear contents
		row = 1;
		for (int i = 0; i < theNumOfItems; i++) {
			ui.formLayout->removeRow(row);
		}

		//show folders in sorted way
		FolderType* data_show;
		if (m_curFolder->getTheNumOfFolder() != 0) {
			AVLtree<FolderType>* SFL = m_curFolder->getSubFolderList();
			SFL->resetList();
			for (int i = 0; i < m_curFolder->getTheNumOfFolder(); i++) {
				//create pushbutton for temporary saving and show
				QPushButton* button_temp = new QPushButton;
				QLabel* label_temp = new QLabel;
				label_temp->setText("Folder");
				SFL->getNextT(data_show);

				//string to QString conversion
				QString Qname_temp = QString::fromUtf8(data_show->getName().c_str());
				ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
				button_temp->setText(Qname_temp);
				ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

				//set connect signal and slot
				signalmapper->setMapping(button_temp, Qname_temp);
				QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));
				row++;
			}
		}
		//show files in sorted way
		FileType* data_show_file;
		if (m_curFolder->getTheNumOfFile() != 0) {
			AVLtree<FileType>* SFL = m_curFolder->getSubFileList();
			SFL->resetList();
			for (int i = 0; i < m_curFolder->getTheNumOfFile(); i++) {
				//create pushbutton for temporary saving and show
				QPushButton* button_temp = new QPushButton;
				QLabel* label_temp = new QLabel;
				label_temp->setText("File");
				SFL->getNextT(data_show_file);

				//string to QString conversion
				QString Qname_temp = QString::fromUtf8(data_show_file->getName().c_str());
				ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
				button_temp->setText(Qname_temp);
				ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

				//set connect signal and slot
				signalmapper->setMapping(button_temp, Qname_temp);
				QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
				QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));
				row++;
			}
		}
		theNumOfFiles--;
		theNumOfItems--;
	}
	else if ((ok == true) && !(m_curFolder->deleteFileFromSFL(data))) {
		QMessageBox::warning(this, tr("Error"), tr("Can't delete file \n (Folder doesn't exist!)"));
	}
}

void project02::renameFile()
{

	if (theNumOfFiles == 0) {
		QMessageBox::warning(this, tr("Error"), tr("Please add file first..."));
		return;
	}

	//get folder name from user and set folder name and location
	bool ok;
	QString Qname = QInputDialog::getText(this, "File name input", "Enter file name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
	string name = Qname.toUtf8().constData();
	FileType* data = new FileType;
	data->setName(name);
	data->setLocation(m_curFolder->getLocationName());

	if (ok == true) {
		//get new name from user
		bool ok_new;
		QString Qname_new = QInputDialog::getText(this, "File name input", "Enter new file name : ", QLineEdit::Normal, QDir::home().dirName(), &ok_new);
		string name_new = Qname_new.toUtf8().constData();

		if (ok_new == true) {
			//do if folder exist
			if (m_curFolder->renameFile(data, name_new)) {
				rename(name.c_str(),name_new.c_str());
				//clear contents
				row = 1;
				for (int i = 0; i < theNumOfItems; i++) {
					ui.formLayout->removeRow(row);
				}

				//show folders in sorted way
				FolderType* data_show;
				if (m_curFolder->getTheNumOfFolder() != 0) {
					AVLtree<FolderType>* SFL = m_curFolder->getSubFolderList();
					SFL->resetList();
					for (int i = 0; i < m_curFolder->getTheNumOfFolder(); i++) {
						//create pushbutton for temporary saving and show
						QPushButton* button_temp = new QPushButton;
						QLabel* label_temp = new QLabel;
						label_temp->setText("Folder");
						SFL->getNextT(data_show);

						//string to QString conversion
						QString Qname_temp = QString::fromUtf8(data_show->getName().c_str());
						ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
						button_temp->setText(Qname_temp);
						ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

						QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
						QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));

						//set connect signal and slot
						signalmapper->setMapping(button_temp, Qname_temp);
						QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
						QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));
						row++;
					}
				}

				//show files in sorted way
				FileType* data_show_file;
				if (m_curFolder->getTheNumOfFile() != 0) {
					AVLtree<FileType>* SFL = m_curFolder->getSubFileList();
					SFL->resetList();
					for (int i = 0; i < m_curFolder->getTheNumOfFile(); i++) {
						//create pushbutton for temporary saving and show
						QPushButton* button_temp = new QPushButton;
						QLabel* label_temp = new QLabel;
						label_temp->setText("File");
						SFL->getNextT(data_show_file);

						//string to QString conversion
						QString Qname_temp = QString::fromUtf8(data_show_file->getName().c_str());
						ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
						button_temp->setText(Qname_temp);
						ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

						QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
						QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));

						//set connect signal and slot
						signalmapper->setMapping(button_temp, Qname_temp);
						QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
						QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));
						row++;
					}
				}
			}
			else {
				QMessageBox::warning(this, tr("Error"), tr("Can't rename folder \n (Folder doesn't exist!)"));
			}
		}
	}
}

void project02::openFile(QString Qname)
{

	//set the data which will be searched
	FileType data;
	string name = Qname.toUtf8().constData();
	data.setName(name);
	data.setLocation(m_curFolder->getLocationName());
	string passName = data.getName();
	int dotIndex = passName.find_last_of(".");
	if (dotIndex != string::npos) {
		data.setExtension(passName.substr(dotIndex));
	}
	//set the pointer of found file
	FileType* found = m_curFolder->searchExactFileName(data);

	//create new window
	SecondWindow secWindow;
	secWindow.addTitle_FileContent(Qname);

	//if file is found, read data from that file
	if (found != NULL) {
		string foundFileName = found->getName();
		fsInput.open(foundFileName);
		if (fsInput.is_open()) {
			string line;

			textContent = new QTextEdit;
			while (getline(fsInput, line)) {
				textContent->append(line.c_str());
			}
			secWindow.addTextContent(2, textContent);
			fsInput.close();

			fsOutput.open(foundFileName, ios::in | ios::out);

			QPushButton* saveButton = new QPushButton("save and close");
			QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(saveFile()));
			QObject::connect(saveButton, SIGNAL(clicked()), &secWindow, SLOT(close()));

			secWindow.addPushButtonAtField(2, saveButton);

			secWindow.resize(400, 200);
			secWindow.setModal(true);
			secWindow.exec();

			QObject::disconnect(saveButton, SIGNAL(clicked()), this, SLOT(saveFile()));
			QObject::disconnect(saveButton, SIGNAL(clicked()), &secWindow, SLOT(close()));
			return;
		}
		else {
			QMessageBox::warning(this, tr("Error"), tr("Can't find file \n (File doesn't exists!)"));
			return;
		}
	}
	//else show message
	else {
		QMessageBox::warning(this, tr("Error"), tr("File doesn't exists!"));
	}
}

void project02::ReadWriteDataToFile()
{
	if (m_curFolder->getTheNumOfFile() != 0) {
		//get folder name from user and set folder name and location
		bool ok;
		QString Qname = QInputDialog::getText(this, "File name input", "Enter file name with Extension : ", QLineEdit::Normal, QDir::home().dirName(), &ok);

		//create new window
		SecondWindow secWindow;
		secWindow.addTitle_FileContent(Qname);

		if (ok == true) {
			string name = Qname.toUtf8().constData();
			FileType data;
			data.setName(name);
			data.setLocation(m_curFolder->getLocationName());
			string passName = data.getName();
			int dotIndex = passName.find_last_of(".");
			if (dotIndex != string::npos) {
				data.setExtension(passName.substr(dotIndex));
			}

			FileType* found = m_curFolder->searchExactFileName(data);

			//if file is found, read data from that file
			if (found != NULL) {
				string foundFileName = found->getName();
				fsInput.open(foundFileName);
				if (fsInput.is_open()) {
					string line;

					textContent = new QTextEdit;
					while (getline(fsInput, line)) {
						textContent->append(line.c_str());
					}
					secWindow.addTextContent(2, textContent);
					fsInput.close();

					fsOutput.open(foundFileName, ios::in|ios::out);


					QPushButton* saveButton = new QPushButton("save and close");
					QObject::connect(saveButton, SIGNAL(clicked()), this, SLOT(saveFile()));
					QObject::connect(saveButton, SIGNAL(clicked()), &secWindow, SLOT(close()));

					secWindow.addPushButtonAtField(2, saveButton);

					secWindow.resize(400, 200);
					secWindow.setModal(true);
					secWindow.exec();
				}
				else {
					QMessageBox::warning(this, tr("Error"), tr("Can't find file \n (File doesn't exists!)"));
					return;
				}
			}
			//else show message
			else {
				QMessageBox::warning(this, tr("Error"), tr("File doesn't exists!"));
			}
		}
	}
}

//pre : file is opened, textContent object initialized
void project02::saveFile()
{
	QString QdataContent = textContent->toPlainText();
	string dataContent = QdataContent.toUtf8().constData();

	//store original file's length
	fsOutput.seekp(0, ios::end);
	int oldLength = fsOutput.tellp();
	fsOutput.clear();

	fsOutput.seekp(0, ios::beg);
	int assure = fsOutput.tellp();
	while (assure != oldLength) {
		fsOutput << " ";
		assure = fsOutput.tellp();
	}
	fsOutput.clear();
	fsOutput.seekp(0, ios::beg);

	fsOutput << dataContent;
	fsOutput.close();
	return;
}

void project02::showFileProperty()
{
	//show message if there is no folders
	if (theNumOfFiles == 0) {
		QMessageBox::warning(this, tr("Error"), tr("Please add file first..."));
		return;
	}

	//get folder name from user and set folder name and location
	bool ok;
	QString Qname_file = QInputDialog::getText(this, "File name input", "Enter file name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
	string name_file = Qname_file.toUtf8().constData();
	FileType data;
	data.setName(name_file);
	data.setLocation(m_curFolder->getLocationName());

	//set the pointer of found file
	FileType* found = m_curFolder->searchExactFileName(data);
	if (found != NULL) {
		SecondWindow secWindow;

		QLabel* nameLabel = new QLabel("File Name : ");
		QString Qname = QString::fromUtf8(found->getName().c_str());
		QLabel* name = new QLabel(Qname);

		QLabel* extensionLabel = new QLabel("File extension : ");
		QString Qextension = QString::fromUtf8(found->getExtension().c_str());
		QLabel* extension = new QLabel(Qextension);

		QLabel* locationLabel = new QLabel("File Location : ");
		QString Qlocation = QString::fromUtf8(found->getLocation().c_str());
		QLabel* location = new QLabel(Qlocation);

		QLabel* sizeLabel = new QLabel("File Size : ");
		int size_int = found->getSize();
		QString Qsize;
		if ((size_int >= 1024) && (size_int < 1024 * 1024)) {
			Qsize = QString::number((float)size_int / 1024);
			Qsize = Qsize + "KB";
		}
		else if ((size_int >= 1024 * 1024) && (size_int < pow(1024, 3))) {
			Qsize = QString::number((float)size_int / 1024 * 1024);
			Qsize = Qsize + "MB";
		}
		else if ((size_int >= pow(1024, 3) && (size_int < pow(1024, 4)))) {
			Qsize = QString::number((float)size_int / pow(1024, 3));
			Qsize = Qsize + "GB";
		}
		else {
			Qsize = QString::number(size_int);
			Qsize = Qsize + "Byte";
		}
		QLabel* size = new QLabel(Qsize);

		QLabel* dateLabel = new QLabel("File Created Date : ");
		QString Qdate = QString::fromUtf8(found->getDate().c_str());
		QLabel* date = new QLabel(Qdate);

		secWindow.setWindowTitle(Qname.append(" Property"));
		secWindow.addTitle_FileProperty();
		secWindow.addFolderProperty(2, nameLabel, name);
		secWindow.addFolderProperty(3, extensionLabel, extension);
		secWindow.addFolderProperty(4, locationLabel, location);
		secWindow.addFolderProperty(6, sizeLabel, size);
		secWindow.addFolderProperty(7, dateLabel, date);

		secWindow.resize(300, 100);

		secWindow.setModal(true);
		secWindow.exec();
	}
	else {
		QMessageBox::warning(this, tr("Error"), tr("File doesn't exists!"));
	}
}

void project02::retrieveFolderByName()
{
	SortedLinkedList<FolderType*> foundList;
	int theNumOfFound = 0;

	//get folder name from user and set folder name and location
	bool ok;
	QString Qname = QInputDialog::getText(this, "Find Folders", "Enter folder name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
	string name = Qname.toUtf8().constData();
	if (ok == true) {
		FolderType input;
		input.setName(name);
		m_RootFolder.searchFolderName(input, theNumOfFound, foundList);
		foundList.resetList();

		/*Iterator of foundList. Why pointer of pointer?
		*	1.	the input of getNextT is the pointer of Item of SortedLinkedList of NodeType
		*	2.	foundrList store the pointer of FolderType
		*	3.	Iterator should point the pointer of FolderType(=>FolderType**)
		*/
		FolderType** tempptr;

		QString QtheNumOfFound = QString::number(theNumOfFound);
		QtheNumOfFound = QtheNumOfFound.append(" folder(s) found");
		QMessageBox::information(this, "Found Result", QtheNumOfFound);

		if (theNumOfFound != 0) {
			SecondWindow secWindow;
			secWindow.setWindowTitle("Folder Search result(of all folder)");
			secWindow.addSubLabel_FolderRetrieve(0);
			for (int i = 0; i < theNumOfFound; i++) {
				foundList.getNextT(tempptr);
				QString Qname_found = QString::fromUtf8((*tempptr)->getName().c_str());
				QString Qlocation_found = QString::fromUtf8((*tempptr)->getLocation().c_str());

				QLabel* label = new QLabel(Qlocation_found); 
				QPushButton* button = new QPushButton(Qname_found);
				secWindow.addButtonLabel((i + 2), button, label);
			}
			secWindow.setModal(true);
			secWindow.exec();
		}
	}
	foundList.makeEmpty();
}

void project02::retrieveFileByName()
{
	SortedLinkedList<FileType*> foundList;
	int theNumOfFound = 0;

	//get folder name from user and set folder name and location
	bool ok;
	QString Qname = QInputDialog::getText(this, "Find files", "Enter file name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
	string name = Qname.toUtf8().constData();
	if (ok == true) {
		FileType input;
		input.setName(name);
		m_RootFolder.searchFileName(input, theNumOfFound, foundList);
		foundList.resetList();

		/*Iterator of foundList. Why pointer of pointer?
		*	1.	the input of getNextT is the pointer of Item of SortedLinkedList of NodeType
		*	2.	foundrList store the pointer of FolderType
		*	3.	Iterator should point the pointer of FolderType(=>FolderType**)
		*/
		FileType** tempptr;

		QString QtheNumOfFound = QString::number(theNumOfFound);
		QtheNumOfFound = QtheNumOfFound.append(" files(s) found");
		QMessageBox::information(this, "Found Result", QtheNumOfFound);

		if (theNumOfFound != 0) {
			SecondWindow secWindow;
			secWindow.setWindowTitle("File Search result(of all folder)");
			secWindow.addSubLabel_FileRetrieve(0);
			for (int i = 0; i < theNumOfFound; i++) {
				foundList.getNextT(tempptr);
				QString Qname_found = QString::fromUtf8((*tempptr)->getName().c_str());
				QString Qlocation_found = QString::fromUtf8((*tempptr)->getLocation().c_str());

				QLabel* label = new QLabel(Qlocation_found);
				QPushButton* button = new QPushButton(Qname_found);
				secWindow.addButtonLabel((i + 2), button, label);
			}
			secWindow.setModal(true);
			secWindow.exec();
		}
	}
	foundList.makeEmpty();
}

void project02::retrieveFolderAndFileByName()
{
	SecondWindow secWindow;
	SortedLinkedList<FolderType*> foundFolderList;
	int theNumOfFoundFolder = 0;
	int row = 2;

	//get folder name from user and set folder name and location
	bool ok;
	QString Qname = QInputDialog::getText(this, "Find Folders and Files", "Enter Item name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
	string name = Qname.toUtf8().constData();
	if (ok == true) {
		/*Iterator of foundfolderList. Why pointer of pointer?
		*	1.	the input of getNextT is the pointer of Item of SortedLinkedList of NodeType
		*	2.	foundFolderList store the pointer of FolderType
		*	3.	Iterator should point the pointer of FolderType(FolderType**)
		*/
		FolderType** tempptrFolder;
		FolderType inputFolder;
		inputFolder.setName(name);
		m_RootFolder.searchFolderName(inputFolder, theNumOfFoundFolder, foundFolderList);
		foundFolderList.resetList();

		QString QtheNumOfFoundFolder = QString::number(theNumOfFoundFolder);
		QtheNumOfFoundFolder = QtheNumOfFoundFolder.append(" folder(s) found");

		

		SortedLinkedList<FileType*> foundFileList;
		int theNumOfFoundFile = 0;

		/*Iterator of foundFileList. Why pointer of pointer?
		*	1.	the input of getNextT is the pointer of Item of SortedLinkedList of NodeType
		*	2.	foundFileList store the pointer ofFileType
		*	3.	Iterator should point the pointer of FileType(FileType**)
		*/
		FileType** tempptrFile;
		FileType inputFile;
		inputFile.setName(name);
		m_RootFolder.searchFileName(inputFile, theNumOfFoundFile, foundFileList);
		foundFileList.resetList();
		
		QString QtheNumOfFoundFile = QString::number(theNumOfFoundFile);
		QtheNumOfFoundFile = QtheNumOfFoundFile.append(" file(s) found");
		QString QtheNumOfFound = QtheNumOfFoundFolder + "\n" + QtheNumOfFoundFile;
		QMessageBox::information(this, "Found Result", QtheNumOfFound);

		if ((theNumOfFoundFolder != 0)|| (theNumOfFoundFile != 0) ){
			secWindow.setWindowTitle("Folder And File Search result(of all folder)");
			if (theNumOfFoundFolder != 0) {
				secWindow.addSubLabel_FolderRetrieve(0);
				for (int i = 0; i < theNumOfFoundFolder; i++) {
					foundFolderList.getNextT(tempptrFolder);
					QString Qname_found = QString::fromUtf8((*tempptrFolder)->getName().c_str());
					QString Qlocation_found = QString::fromUtf8((*tempptrFolder)->getLocation().c_str());

					QLabel* label = new QLabel(Qlocation_found);
					QPushButton* button = new QPushButton(Qname_found);
					secWindow.addButtonLabel(row, button, label);
					row++;
				}
			}
			if (theNumOfFoundFile != 0) {
				secWindow.addSubLabel_FileRetrieve(row);
				row++;
				for (int i = 0; i < theNumOfFoundFile; i++) {
					foundFileList.getNextT(tempptrFile);
					QString Qname_found = QString::fromUtf8((*tempptrFile)->getName().c_str());
					QString Qlocation_found = QString::fromUtf8((*tempptrFile)->getLocation().c_str());

					QLabel* label = new QLabel(Qlocation_found);
					QPushButton* button = new QPushButton(Qname_found);
					secWindow.addButtonLabel(row, button, label);
					row++;
				}
			}
			secWindow.setModal(true);
			secWindow.exec();
		}
		//delete all node of found linked list when the function end
		foundFolderList.makeEmpty();
		foundFileList.makeEmpty();
	}
}


void project02::retrieveFolderByName_current()
{
	SortedLinkedList<FolderType*> foundList;
	int theNumOfFound = 0;

	//get folder name from user and set folder name and location
	bool ok;
	QString Qname = QInputDialog::getText(this, "Find Folder", "Enter folder name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
	string name = Qname.toUtf8().constData();
	if (ok == true) {
		FolderType input;
		input.setName(name);
		m_curFolder->searchFolderName(input, theNumOfFound, foundList);
		foundList.resetList();

		/*Iterator of foundList. Why pointer of pointer?
		*	1.	the input of getNextT is the pointer of Item of SortedLinkedList of NodeType
		*	2.	foundrList store the pointer of FolderType
		*	3.	Iterator should point the pointer of FolderType(=>FolderType**)
		*/
		FolderType** tempptr;

		QString QtheNumOfFound = QString::number(theNumOfFound);
		QtheNumOfFound = QtheNumOfFound.append(" folder(s) found");
		QMessageBox::information(this, "Found Result", QtheNumOfFound);

		if (theNumOfFound != 0) {
			SecondWindow secWindow;
			secWindow.setWindowTitle("Folder Search result(of all folder)");
			secWindow.addSubLabel_FolderRetrieve(0);
			for (int i = 0; i < theNumOfFound; i++) {
				foundList.getNextT(tempptr);
				QString Qname_found = QString::fromUtf8((*tempptr)->getName().c_str());
				QString Qlocation_found = QString::fromUtf8((*tempptr)->getLocation().c_str());

				QLabel* label = new QLabel(Qlocation_found);
				QPushButton* button = new QPushButton(Qname_found);
				secWindow.addButtonLabel((i + 2), button, label);
			}
			secWindow.setModal(true);
			secWindow.exec();
		}
	}
	foundList.makeEmpty();
}

void project02::retrieveFileByName_current()
{
	SortedLinkedList<FileType*> foundList;
	int theNumOfFound = 0;

	//get folder name from user and set folder name and location
	bool ok;
	QString Qname = QInputDialog::getText(this, "Find File", "Enter file name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
	string name = Qname.toUtf8().constData();
	if (ok == true) {
		FileType input;
		input.setName(name);
		m_curFolder->searchFileName(input, theNumOfFound, foundList);
		foundList.resetList();

		/*Iterator of foundList. Why pointer of pointer?
		*	1.	the input of getNextT is the pointer of Item of SortedLinkedList of NodeType
		*	2.	foundrList store the pointer of FolderType
		*	3.	Iterator should point the pointer of FolderType(=>FolderType**)
		*/
		FileType** tempptr;

		QString QtheNumOfFound = QString::number(theNumOfFound);
		QtheNumOfFound = QtheNumOfFound.append(" files(s) found");
		QMessageBox::information(this, "Found Result", QtheNumOfFound);

		if (theNumOfFound != 0) {
			SecondWindow secWindow;
			secWindow.setWindowTitle("File Search result(of all folder)");
			secWindow.addSubLabel_FileRetrieve(0);
			for (int i = 0; i < theNumOfFound; i++) {
				foundList.getNextT(tempptr);
				QString Qname_found = QString::fromUtf8((*tempptr)->getName().c_str());
				QString Qlocation_found = QString::fromUtf8((*tempptr)->getLocation().c_str());

				QLabel* label = new QLabel(Qlocation_found);
				QPushButton* button = new QPushButton(Qname_found);
				secWindow.addButtonLabel((i + 2), button, label);
			}
			secWindow.setModal(true);
			secWindow.exec();
		}
	}
	foundList.makeEmpty();
}

void project02::retrieveFolderAndFileByName_current()
{
	SecondWindow secWindow;
	SortedLinkedList<FolderType*> foundFolderList;
	int theNumOfFoundFolder = 0;
	int row = 2;

	//get folder name from user and set folder name and location
	bool ok;
	QString Qname = QInputDialog::getText(this, "Find Folder And File", "Enter Item name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
	string name = Qname.toUtf8().constData();
	if (ok == true) {
		/*Iterator of foundfolderList. Why pointer of pointer?
		*	1.	the input of getNextT is the pointer of Item of SortedLinkedList of NodeType
		*	2.	foundFolderList store the pointer of FolderType
		*	3.	Iterator should point the pointer of FolderType(FolderType**)
		*/
		FolderType** tempptrFolder;
		FolderType inputFolder;
		inputFolder.setName(name);
		m_curFolder->searchFolderName(inputFolder, theNumOfFoundFolder, foundFolderList);
		foundFolderList.resetList();

		QString QtheNumOfFoundFolder = QString::number(theNumOfFoundFolder);
		QtheNumOfFoundFolder = QtheNumOfFoundFolder.append(" folder(s) found");



		SortedLinkedList<FileType*> foundFileList;
		int theNumOfFoundFile = 0;

		/*Iterator of foundFileList. Why pointer of pointer?
		*	1.	the input of getNextT is the pointer of Item of SortedLinkedList of NodeType
		*	2.	foundFileList store the pointer ofFileType
		*	3.	Iterator should point the pointer of FileType(FileType**)
		*/
		FileType** tempptrFile;
		FileType inputFile;
		inputFile.setName(name);
		m_curFolder->searchFileName(inputFile, theNumOfFoundFile, foundFileList);
		foundFileList.resetList();

		QString QtheNumOfFoundFile = QString::number(theNumOfFoundFile);
		QtheNumOfFoundFile = QtheNumOfFoundFile.append(" file(s) found");
		QString QtheNumOfFound = QtheNumOfFoundFolder + "\n" + QtheNumOfFoundFile;
		QMessageBox::information(this, "Found Result", QtheNumOfFound);

		if ((theNumOfFoundFolder != 0) || (theNumOfFoundFile != 0)) {
			secWindow.setWindowTitle("Folder And File Search result(of all folder)");
			if (theNumOfFoundFolder != 0) {
				secWindow.addSubLabel_FolderRetrieve(0);
				for (int i = 0; i < theNumOfFoundFolder; i++) {
					foundFolderList.getNextT(tempptrFolder);
					QString Qname_found = QString::fromUtf8((*tempptrFolder)->getName().c_str());
					QString Qlocation_found = QString::fromUtf8((*tempptrFolder)->getLocation().c_str());

					QLabel* label = new QLabel(Qlocation_found);
					QPushButton* button = new QPushButton(Qname_found);
					secWindow.addButtonLabel(row, button, label);
					row++;
				}
			}
			if (theNumOfFoundFile != 0) {
				secWindow.addSubLabel_FileRetrieve(row);
				row++;
				for (int i = 0; i < theNumOfFoundFile; i++) {
					foundFileList.getNextT(tempptrFile);
					QString Qname_found = QString::fromUtf8((*tempptrFile)->getName().c_str());
					QString Qlocation_found = QString::fromUtf8((*tempptrFile)->getLocation().c_str());

					QLabel* label = new QLabel(Qlocation_found);
					QPushButton* button = new QPushButton(Qname_found);
					secWindow.addButtonLabel(row, button, label);
					row++;
				}
			}
			secWindow.setModal(true);
			secWindow.exec();
		}
		//delete all node of found linked list when the function end
		foundFolderList.makeEmpty();
		foundFileList.makeEmpty();
	}
}

void project02::copyFolder()
{
	if (m_curFolder->getTheNumOfFolder() != 0) {
		//get folder name from user and set folder name and location
		bool ok;
		QString Qname = QInputDialog::getText(this, "Copy Folder", "Enter folder name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
		string name = Qname.toUtf8().constData();
		FolderType data;
		data.setName(name);
		data.setLocation(m_curFolder->getLocationName());

		//set the pointer of found folder
		FolderType* found;
		found = m_curFolder->searchExactFolderName(data);
		if (found != NULL) {
			clipboard.autoEnQueue(found);
			QMessageBox::information(this, "Information", "Folder copied successfully.");
		}
		else {
			QMessageBox::warning(this, tr("Error"), tr("Can't copy folder \n(Folder doesn't exist.)"));
		}
	}
	else {
		QMessageBox::warning(this, tr("Error"), tr("Please add folder first..."));
	}
}

void project02::cutFolder()
{
	if (m_curFolder->getTheNumOfFolder() != 0) {
		//get folder name from user and set folder name and location
		bool ok;
		QString Qname = QInputDialog::getText(this, "Cut Folder", "Enter folder name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
		string name = Qname.toUtf8().constData();
		FolderType data;
		data.setName(name);
		data.setLocation(m_curFolder->getLocationName());

		//set the pointer of found folder
		FolderType* found;
		found = m_curFolder->searchExactFolderName(data);
		if (found != NULL) {
			clipboard.autoEnQueue(found);
			//update file size of all upper folders
			FolderType* uppertemp = m_curFolder;
			while (1) {
				uppertemp->setSize(uppertemp->getSize() - (*found).getSize());
				if (!(uppertemp->openUpperFolder(uppertemp))) {
					break;
				}
			}
			m_curFolder->deleteFolderFromSFLtemporarily(data);
			QMessageBox::information(this, "Information", "Folder cut successfully.");

			//clear contents
			row = 1;
			for (int i = 0; i < theNumOfItems; i++) {
				ui.formLayout->removeRow(row);
			}

			//show folders in sorted way
			FolderType* data_show;
			if (m_curFolder->getTheNumOfFolder() != 0) {
				AVLtree<FolderType>* SFL = m_curFolder->getSubFolderList();
				SFL->resetList();
				for (int i = 0; i < m_curFolder->getTheNumOfFolder(); i++) {
					//create pushbutton for temporary saving and show
					QPushButton* button_temp = new QPushButton;
					QLabel* label_temp = new QLabel;
					label_temp->setText("Folder");
					SFL->getNextT(data_show);

					//string to QString conversion
					QString Qname_temp = QString::fromUtf8(data_show->getName().c_str());
					ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
					button_temp->setText(Qname_temp);
					ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

					QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
					QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));

					//set connect signal and slot
					signalmapper->setMapping(button_temp, Qname_temp);
					QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
					QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));
					row++;
				}
			}
			//show files in sorted way
			FileType* data_show_file;
			if (m_curFolder->getTheNumOfFile() != 0) {
				AVLtree<FileType>* SFL = m_curFolder->getSubFileList();
				SFL->resetList();
				for (int i = 0; i < m_curFolder->getTheNumOfFile(); i++) {
					//create pushbutton for temporary saving and show
					QPushButton* button_temp = new QPushButton;
					QLabel* label_temp = new QLabel;
					label_temp->setText("File");
					SFL->getNextT(data_show_file);

					//string to QString conversion
					QString Qname_temp = QString::fromUtf8(data_show_file->getName().c_str());
					ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
					button_temp->setText(Qname_temp);
					ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

					//set connect signal and slot
					signalmapper->setMapping(button_temp, Qname_temp);
					QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
					QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));
					row++;
				}
			}
			theNumOfFolders--;
			theNumOfItems--;
		}
		else {
			QMessageBox::warning(this, tr("Error"), tr("Can't cut folder \n(Folder doesn't exist.)"));
		}
	}
	else {
		QMessageBox::warning(this, tr("Error"), tr("Please add folder first..."));
	}
}

void project02::paste()
{
	BaseType* data = clipboard.getRear();

	//check type and paste case by case
	int type = checkType(typeid(*data).name());
	if (type == FOLDERTYPE) {
		FolderType* newFolder;
		newFolder = new FolderType;
		copyFolderCommand((FolderType*)data, newFolder);
		m_curFolder->addFolderToSFL(*newFolder);
		//update file size of all upper folders
		FolderType* uppertemp = m_curFolder;
		while (1) {
			uppertemp->setSize(uppertemp->getSize() + (*data).getSize());
			if (!(uppertemp->openUpperFolder(uppertemp))) {
				break;
			}
		}
		theNumOfFolders++;
		theNumOfItems++;
	}
	else if (type == FILETYPE) {
		FileType* newFile;
		newFile = new FileType;
		(*newFile) = *((FileType*)data);
		m_curFolder->addFileToSFL(*newFile);
		//update file size of all upper folders
		FolderType* uppertemp = m_curFolder;
		while (1) {
			uppertemp->setSize(uppertemp->getSize() + (*data).getSize());
			if (!(uppertemp->openUpperFolder(uppertemp))) {
				break;
			}
		}
		theNumOfFiles++;
		theNumOfItems++;
	}
	//clear contents
	row = 1;
	for (int i = 0; i < theNumOfItems; i++) {
		ui.formLayout->removeRow(row);
	}

	//show folders in sorted way
	FolderType* data_show;
	if (m_curFolder->getTheNumOfFolder() != 0) {
		AVLtree<FolderType>* SFL = m_curFolder->getSubFolderList();
		SFL->resetList();
		for (int i = 0; i < m_curFolder->getTheNumOfFolder(); i++) {
			//create pushbutton for temporary saving and show
			QPushButton* button_temp = new QPushButton;
			QLabel* label_temp = new QLabel;
			label_temp->setText("Folder");
			SFL->getNextT(data_show);

			//string to QString conversion
			QString Qname_temp = QString::fromUtf8(data_show->getName().c_str());
			ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
			button_temp->setText(Qname_temp);
			ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

			QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
			QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));

			//set connect signal and slot
			signalmapper->setMapping(button_temp, Qname_temp);
			QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
			QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));
			row++;
		}
	}
	//show files in sorted way
	FileType* data_show_file;
	if (m_curFolder->getTheNumOfFile() != 0) {
		AVLtree<FileType>* SFL = m_curFolder->getSubFileList();
		SFL->resetList();
		for (int i = 0; i < m_curFolder->getTheNumOfFile(); i++) {
			//create pushbutton for temporary saving and show
			QPushButton* button_temp = new QPushButton;
			QLabel* label_temp = new QLabel;
			label_temp->setText("File");
			SFL->getNextT(data_show_file);

			//string to QString conversion
			QString Qname_temp = QString::fromUtf8(data_show_file->getName().c_str());
			ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
			button_temp->setText(Qname_temp);
			ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

			//set connect signal and slot
			signalmapper->setMapping(button_temp, Qname_temp);
			QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
			QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));
			row++;
		}
	}
}

void project02::copyFile()
{
	if (m_curFolder->getTheNumOfFile() != 0) {
		//get folder name from user and set folder name and location
		bool ok;
		QString Qname = QInputDialog::getText(this, "Copy File", "Enter file name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
		string name = Qname.toUtf8().constData();
		FileType data;
		data.setName(name);
		data.setLocation(m_curFolder->getLocationName());

		//set the pointer of found folder
		FileType* found;
		found = m_curFolder->searchExactFileName(data);
		if (found != NULL) {
			clipboard.autoEnQueue(found);
			QMessageBox::information(this, "Information", "File copied successfully.");
		}
		else {
			QMessageBox::warning(this, tr("Error"), tr("Can't copy file \n(File doesn't exist.)"));
		}
	}
	else {
		QMessageBox::warning(this, tr("Error"), tr("Please add file first..."));
	}
}

void project02::cutFile()
{
	if (m_curFolder->getTheNumOfFile() != 0) {
		//get folder name from user and set folder name and location
		bool ok;
		QString Qname = QInputDialog::getText(this, "Cut File", "Enter file name : ", QLineEdit::Normal, QDir::home().dirName(), &ok);
		string name = Qname.toUtf8().constData();
		FileType data;
		data.setName(name);
		data.setLocation(m_curFolder->getLocationName());

		//set the pointer of found folder
		FileType* found = m_curFolder->searchExactFileName(data);

		if (found != NULL) {
			clipboard.autoEnQueue(found);
			//update file size of all upper folders
			FolderType* uppertemp = m_curFolder;
			while (1) {
				uppertemp->setSize(uppertemp->getSize() - (*found).getSize());
				if (!(uppertemp->openUpperFolder(uppertemp))) {
					break;
				}
			}
			m_curFolder->deleteFileFromSFLtemporarily(*found);
			QMessageBox::information(this, "Information", "File cut successfully.");

			//clear contents
			row = 1;
			for (int i = 0; i < theNumOfItems; i++) {
				ui.formLayout->removeRow(row);
			}

			//show folders in sorted way
			FolderType* data_show;
			if (m_curFolder->getTheNumOfFolder() != 0) {
				AVLtree<FolderType>* SFL = m_curFolder->getSubFolderList();
				SFL->resetList();
				for (int i = 0; i < m_curFolder->getTheNumOfFolder(); i++) {
					//create pushbutton for temporary saving and show
					QPushButton* button_temp = new QPushButton;
					QLabel* label_temp = new QLabel;
					label_temp->setText("Folder");
					SFL->getNextT(data_show);

					//string to QString conversion
					QString Qname_temp = QString::fromUtf8(data_show->getName().c_str());
					ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
					button_temp->setText(Qname_temp);
					ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

					QObject::disconnect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
					QObject::disconnect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));

					//set connect signal and slot
					signalmapper->setMapping(button_temp, Qname_temp);
					QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
					QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFolder(const QString&)));
					row++;
				}
			}
			//show files in sorted way
			FileType* data_show_file;
			if (m_curFolder->getTheNumOfFile() != 0) {
				AVLtree<FileType>* SFL = m_curFolder->getSubFileList();
				SFL->resetList();
				for (int i = 0; i < m_curFolder->getTheNumOfFile(); i++) {
					//create pushbutton for temporary saving and show
					QPushButton* button_temp = new QPushButton;
					QLabel* label_temp = new QLabel;
					label_temp->setText("File");
					SFL->getNextT(data_show_file);

					//string to QString conversion
					QString Qname_temp = QString::fromUtf8(data_show_file->getName().c_str());
					ui.formLayout->setWidget(row, QFormLayout::LabelRole, label_temp);
					button_temp->setText(Qname_temp);
					ui.formLayout->setWidget(row, QFormLayout::FieldRole, button_temp);

					//set connect signal and slot
					signalmapper->setMapping(button_temp, Qname_temp);
					QObject::connect(button_temp, SIGNAL(clicked()), signalmapper, SLOT(map()));
					QObject::connect(signalmapper, SIGNAL(mapped(const QString&)), this, SLOT(openFile(const QString&)));
					row++;
				}
			}
			theNumOfFiles--;
			theNumOfItems--;
		}
		else {
			QMessageBox::warning(this, tr("Error"), tr("Can't cut file \n(Folder doesn't exist.)"));
		}
	}
	else {
		QMessageBox::warning(this, tr("Error"), tr("Please add file first..."));
	}
}






