#pragma once

#include <QDialog>
#include "ui_SecondWindow.h"
#include <QtCore/QVariant>
#include <QtWidgets/QMainWindow>
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
#include <QtWidgets/QTextEdit>
#include <QSignalMapper>
#include <QDir>
#include <QMessageBox>

#include "project02.h"

/**
*	@brief	A class that control second window
*/
class SecondWindow : public QDialog
{
	Q_OBJECT

public:
	SecondWindow(QWidget *parent = Q_NULLPTR);
	~SecondWindow();
	/**
	*	@brief	add title of back history
	*/
	void addTitle_BackHistory();

	/**
	*	@brief	add title of front history
	*/
	void addTitle_FrontHistory();

	/**
	*	@brief	add title of folder property
	*/
	void addTitle_FolderProperty();

	/**
	*	@brief	add title of file property
	*/
	void addTitle_FileProperty();

	/**
	*	@brief	add title of file content
	*/
	void addTitle_FileContent(QString fileName);

	/**
	*	@brief	add title of folder search result
	*/
	void addTitle_FolderRetrieveResult();

	/**
	*	@brief	add title of file search result
	*/
	void addTitle_FileRetrieveResult();

	/**
	*	@brief	add title of folder and file search result
	*/
	void addTitle_FolderAndFileRetrieveResult();

	/**
	*	@brief	add sublabel of folder search
	*/
	void addSubLabel_FolderRetrieve(const int& row);

	/**
	*	@brief	add sublabel of file search
	*/
	void addSubLabel_FileRetrieve(const int& row);

	/**
	*	@brief	add a row in second window, add label and label
	*/
	void addFolderProperty(const int& row, QLabel* Label, QLabel* Content);

	/**
	*	@brief	add a row in second window, add button and label
	*/
	void addButtonLabel(const int& row, QPushButton* button, QLabel* label);

	/**
	*	@brief	add a row in second window, add text edit
	*/
	void addTextContent(const int& row, QTextEdit * textedit);

	/**
	*	@brief	add a row in second window, add button
	*/
	void addPushButtonAtField(const int& row, QPushButton* inButton);

	/**
	*	@brief	add a row in second window, add label and button
	*/
	void addRow(const int& row, QLabel* inLabel, QPushButton* inButton);

public slots:

private:
	Ui::SecondWindow ui;
	QSignalMapper* signalmapper = new QSignalMapper(this);
};
