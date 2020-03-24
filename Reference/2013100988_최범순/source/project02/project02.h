#pragma once

#include <QtCore/QVariant>
#include <QtWidgets/QMainWindow>
#include "ui_project02.h"
#include <QtWidgets/QInputDialog>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>
#include <QSignalMapper>
#include <QtWidgets/QTextEdit>
#include <QDir>
#include <QMessageBox>

#include <fstream>
#include <string>

#include "FolderType.h"
#include "CircularQueue.h"
#include "Stack.h"
#include "SecondWindow.h"

#define FOLDERTYPE 1
#define FILETYPE 2
#define UNKNOWN -1

/**
*	@brief	A class that control main window
*/
class project02 : public QMainWindow
{
	Q_OBJECT

public:
	project02(QWidget *parent = Q_NULLPTR);

	/**
	*	@brief	check type and return type in int type
	*	@pre	object should be initialized
	*	@return	return integer that means type
	*/
	int checkType(string inString);

	/**
	*	@brief	copy a folder to another temporary folder
	*	@pre	object should be initialized
	*	@return	return 1 if this function works well, otherwise 0
	*	@param	FolderType* copied	a folder which will be copied
	*	@param	FolderType* newFolder	a folder which will be created
	*/
	int copyFolderCommand(FolderType* copied, FolderType*& newFolder);

	/**
	*	@brief	copy all folders in subfolder list
	*	@pre	object should be initialized
	*	@pre	folders exist in subfolder
	*	@param	FolderType* copied	a folder which will be copied
	*	@param	FolderType* newFolderList	a folder which will be created
	*/
	int copySubFolders(FolderType* copied, FolderType*& newFolderList);

private slots:
	/**
	*	@brief	create new folder in current folder
	*/
	void newFolder();

	/**
	*	@brief	open Folder which name is Qname
	*/
	void openFolder(QString Qname);

	/**
	*	@brief	open Folder with name of user input
	*/
	void openFolderAtSFL();

	/**
	*	@brief	delete Folder with name of user input
	*/
	void deleteFolder();

	/**
	*	@brief	rename Folder with name of user input
	*/
	void renameFolder();

	/**
	*	@brief	open upper folder of current folder
	*/
	void openUF();

	/**
	*	@brief	go back folder
	*/
	void goBack();

	/**
	*	@brief	show back and access any of that
	*/
	void showBacks();

	/**
	*	@brief	go front folder
	*/
	void goFront();

	/**
	*	@brief	show front and access any of that
	*/
	void showFronts();

	/**
	*	@brief	go back n times
	*/
	void openBackResult(const int& n);

	/**
	*	@brief	go front n times
	*/
	void openFrontResult(const int& n);

	/**
	*	@brief	show current folder property
	*/
	void showFolderProperty();

	/**
	*	@brief	clear all history
	*/
	void clearHistory();

	/**
	*	@brief	create a new file in current folder
	*/
	void newFile();

	/**
	*	@brief	delete a file in current folder
	*/
	void deleteFile();

	/**
	*	@brief	rename a file in current folder
	*/
	void renameFile();

	/**
	*	@brief	open File which name is Qname
	*/
	void openFile(QString Qname);

	/**
	*	@brief	read data from a file
	*/
	void ReadWriteDataToFile();

	/**
	*	@brief clear all content of text file and write content which is in QTextEdit object
	*/
	void saveFile();

	/**
	*	@brief	show file property in current folder
	*/
	void showFileProperty();

	/**
	*	@brief	find folder by name of all system
	*/
	void retrieveFolderByName();

	/**
	*	@brief	find file by name of all system
	*/
	void retrieveFileByName();

	/**
	*	@brief	find folder and file by name of all system
	*/
	void retrieveFolderAndFileByName();

	/**
	*	@brief	find folder by name from current folder(include subfolders)
	*/
	void retrieveFolderByName_current();

	/**
	*	@brief	find file by name from current folder(include subfolders)
	*/
	void retrieveFileByName_current();

	/**
	*	@brief	find folder and file by name from current folder(include subfolders)
	*/
	void retrieveFolderAndFileByName_current();

	/**
	*	@brief	copy a folder
	*/
	void copyFolder();

	/**
	*	@brief	cut a folder
	*/
	void cutFolder();

	/**
	*	@brief	paste folder or file
	*/
	void paste();

	/**
	*	@brief	copy file
	*/
	void copyFile();

	/**
	*	@brief	cut file
	*/
	void cutFile();

private:
	Ui::project02Class ui;
	int row = 1;
	int theNumOfFolders = 0;
	int theNumOfFiles = 0;
	int theNumOfItems = 0;
	QSignalMapper* signalmapper = new QSignalMapper(this);	///<signal mapper to connect signal with slots which has input parameter
	QTextEdit* textContent;									///<text content to get input from user

	ifstream fsInput;										///<input file descriptor
	ofstream fsOutput;										///<output file descriptor

	FolderType m_RootFolder;								///<root folder
	FolderType* m_curFolder = &m_RootFolder;				///<pointer of current folder
	CircularQueue<FolderType> m_RecentlyFolder;				///<circular queue recording history
	CircularQueue<BaseType*> clipboard;						///<clipboard that manage the temporary items
	Stack<FolderType> m_goBackForthFolder;					///<Stack recording history

};
