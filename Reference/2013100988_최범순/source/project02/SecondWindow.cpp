#include "SecondWindow.h"

SecondWindow::SecondWindow(QWidget *parent)
	: QDialog(parent)
{
	ui.setupUi(this);
}

SecondWindow::~SecondWindow()
{
}

void SecondWindow::addTitle_BackHistory()
{
	QLabel* label = new QLabel;
	label->setText("Back History");
	ui.formLayout->setWidget(0, QFormLayout::LabelRole, label);
}

void SecondWindow::addTitle_FrontHistory()
{
	QLabel* label = new QLabel;
	label->setText("Front History");
	ui.formLayout->setWidget(0, QFormLayout::LabelRole, label);
}

void SecondWindow::addTitle_FolderProperty()
{
	QLabel* label = new QLabel;
	label->setText("Folder Property");
	ui.formLayout->setWidget(0, QFormLayout::LabelRole, label);
}

void SecondWindow::addTitle_FileProperty()
{
	QLabel* label = new QLabel;
	label->setText("File Property");
	ui.formLayout->setWidget(0, QFormLayout::LabelRole, label);
}

void SecondWindow::addTitle_FileContent(QString fileName)
{
	QLabel* label = new QLabel;
	label->setText("File Content");
	this->setWindowTitle(fileName);
	ui.formLayout->setWidget(0, QFormLayout::LabelRole, label);
}

void SecondWindow::addTitle_FolderRetrieveResult()
{
	QLabel* label = new QLabel;
	label->setText("Folder Search result");
	ui.formLayout->setWidget(0, QFormLayout::LabelRole, label);
}

void SecondWindow::addTitle_FileRetrieveResult()
{
	QLabel* label = new QLabel;
	label->setText("File Search result");
	ui.formLayout->setWidget(0, QFormLayout::LabelRole, label);
}

void SecondWindow::addTitle_FolderAndFileRetrieveResult()
{
	QLabel* label = new QLabel;
	label->setText("Folder and File Search result");
	ui.formLayout->setWidget(0, QFormLayout::LabelRole, label);
}

void SecondWindow::addSubLabel_FolderRetrieve(const int & row)
{
	QLabel* label1 = new QLabel;
	label1->setText("Folder name");
	ui.formLayout->setWidget(row, QFormLayout::LabelRole, label1);

	QLabel* label2 = new QLabel;
	label2->setText("Folder Location");
	ui.formLayout->setWidget(row, QFormLayout::FieldRole, label2);
}

void SecondWindow::addSubLabel_FileRetrieve(const int & row)
{
	QLabel* label1 = new QLabel;
	label1->setText("File name");
	ui.formLayout->setWidget(row, QFormLayout::LabelRole, label1);

	QLabel* label2 = new QLabel;
	label2->setText("File Location");
	ui.formLayout->setWidget(row, QFormLayout::FieldRole, label2);
}

void SecondWindow::addFolderProperty(const int & row, QLabel * Label, QLabel * Content)
{
	ui.formLayout->setWidget(row, QFormLayout::LabelRole, Label);

	ui.formLayout->setWidget(row, QFormLayout::FieldRole, Content);
}

void SecondWindow::addButtonLabel(const int & row, QPushButton * button, QLabel * label)
{
	ui.formLayout->setWidget(row, QFormLayout::LabelRole, button);

	ui.formLayout->setWidget(row, QFormLayout::FieldRole, label); 
}

void SecondWindow::addTextContent(const int & row, QTextEdit * textedit)
{
	ui.formLayout->setWidget(row, QFormLayout::LabelRole, textedit);
}

void SecondWindow::addPushButtonAtField(const int & row, QPushButton * inButton)
{
	ui.formLayout->setWidget(row, QFormLayout::FieldRole, inButton);
}

void SecondWindow::addRow(const int & row, QLabel* inLabel, QPushButton* inButton)
{
	
	ui.formLayout->setWidget(row, QFormLayout::LabelRole, inLabel);

	ui.formLayout->setWidget(row, QFormLayout::FieldRole, inButton);

}
