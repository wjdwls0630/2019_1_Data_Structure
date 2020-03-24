/********************************************************************************
** Form generated from reading UI file 'project02.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROJECT02_H
#define UI_PROJECT02_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_project02Class
{
public:
    QAction *actionCreate;
    QAction *actionDelete;
    QAction *actionCreate_2;
    QAction *actionDelete_2;
    QAction *actionGo_to_upper_Folder;
    QAction *actionRename;
    QAction *actionOpen_Folder_at_current_folder;
    QAction *actionGo_Back;
    QAction *actionGo_Front;
    QAction *actionShow_Back_History;
    QAction *actionShow_Front_History;
    QAction *actionCurrent_Folder_Property;
    QAction *actionClear_History;
    QAction *actionRead_File_At_Current_Folder;
    QAction *actionRename_2;
    QAction *actionShow_File_Property;
    QAction *actionOpen_File_At_Current_Folder;
    QAction *actionRetrieve_Folder_By_Name;
    QAction *actionRetrieve_File_By_Name;
    QAction *actionRetrieve_Folder_And_File_By_Name;
    QAction *actionRetrieve_Folder_By_Name_2;
    QAction *actionRetrieve_File_By_Name_2;
    QAction *actionRetrieve_Folder_And_File_By_Name_2;
    QAction *actionRetrieve_Folder_And_File_By_Name_3;
    QAction *actionRetrieve_Folder_By_Name_3;
    QAction *actionRetrieve_File_By_Name_3;
    QAction *actionCopy;
    QAction *actionCut;
    QAction *actionPaste;
    QAction *actionCopy_2;
    QAction *actionCut_2;
    QAction *actionPaste_2;
    QWidget *centralWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLineEdit *lineEdit;
    QMenuBar *menuBar;
    QMenu *menuFolder;
    QMenu *menuFile;
    QMenu *menuFind;
    QMenu *menuOf_all_Folder;
    QMenu *menuOf_current_Folder;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *project02Class)
    {
        if (project02Class->objectName().isEmpty())
            project02Class->setObjectName(QString::fromUtf8("project02Class"));
        project02Class->resize(731, 468);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(project02Class->sizePolicy().hasHeightForWidth());
        project02Class->setSizePolicy(sizePolicy);
        actionCreate = new QAction(project02Class);
        actionCreate->setObjectName(QString::fromUtf8("actionCreate"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/project02/Resources/add.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate->setIcon(icon);
        actionDelete = new QAction(project02Class);
        actionDelete->setObjectName(QString::fromUtf8("actionDelete"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/project02/Resources/delete folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete->setIcon(icon1);
        actionCreate_2 = new QAction(project02Class);
        actionCreate_2->setObjectName(QString::fromUtf8("actionCreate_2"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/project02/Resources/add-file.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCreate_2->setIcon(icon2);
        actionDelete_2 = new QAction(project02Class);
        actionDelete_2->setObjectName(QString::fromUtf8("actionDelete_2"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/project02/Resources/deleted.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionDelete_2->setIcon(icon3);
        actionGo_to_upper_Folder = new QAction(project02Class);
        actionGo_to_upper_Folder->setObjectName(QString::fromUtf8("actionGo_to_upper_Folder"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/project02/Resources/up-arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGo_to_upper_Folder->setIcon(icon4);
        actionRename = new QAction(project02Class);
        actionRename->setObjectName(QString::fromUtf8("actionRename"));
        actionOpen_Folder_at_current_folder = new QAction(project02Class);
        actionOpen_Folder_at_current_folder->setObjectName(QString::fromUtf8("actionOpen_Folder_at_current_folder"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/project02/Resources/folder.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_Folder_at_current_folder->setIcon(icon5);
        actionGo_Back = new QAction(project02Class);
        actionGo_Back->setObjectName(QString::fromUtf8("actionGo_Back"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/project02/Resources/left-arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGo_Back->setIcon(icon6);
        actionGo_Front = new QAction(project02Class);
        actionGo_Front->setObjectName(QString::fromUtf8("actionGo_Front"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/project02/Resources/right-arrow.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionGo_Front->setIcon(icon7);
        actionShow_Back_History = new QAction(project02Class);
        actionShow_Back_History->setObjectName(QString::fromUtf8("actionShow_Back_History"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/project02/Resources/double-left-chevron.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShow_Back_History->setIcon(icon8);
        actionShow_Front_History = new QAction(project02Class);
        actionShow_Front_History->setObjectName(QString::fromUtf8("actionShow_Front_History"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/project02/Resources/double-angle-pointing-to-right.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionShow_Front_History->setIcon(icon9);
        actionCurrent_Folder_Property = new QAction(project02Class);
        actionCurrent_Folder_Property->setObjectName(QString::fromUtf8("actionCurrent_Folder_Property"));
        actionClear_History = new QAction(project02Class);
        actionClear_History->setObjectName(QString::fromUtf8("actionClear_History"));
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/project02/Resources/eraser.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionClear_History->setIcon(icon10);
        actionRead_File_At_Current_Folder = new QAction(project02Class);
        actionRead_File_At_Current_Folder->setObjectName(QString::fromUtf8("actionRead_File_At_Current_Folder"));
        actionRename_2 = new QAction(project02Class);
        actionRename_2->setObjectName(QString::fromUtf8("actionRename_2"));
        actionShow_File_Property = new QAction(project02Class);
        actionShow_File_Property->setObjectName(QString::fromUtf8("actionShow_File_Property"));
        actionOpen_File_At_Current_Folder = new QAction(project02Class);
        actionOpen_File_At_Current_Folder->setObjectName(QString::fromUtf8("actionOpen_File_At_Current_Folder"));
        actionRetrieve_Folder_By_Name = new QAction(project02Class);
        actionRetrieve_Folder_By_Name->setObjectName(QString::fromUtf8("actionRetrieve_Folder_By_Name"));
        actionRetrieve_File_By_Name = new QAction(project02Class);
        actionRetrieve_File_By_Name->setObjectName(QString::fromUtf8("actionRetrieve_File_By_Name"));
        actionRetrieve_Folder_And_File_By_Name = new QAction(project02Class);
        actionRetrieve_Folder_And_File_By_Name->setObjectName(QString::fromUtf8("actionRetrieve_Folder_And_File_By_Name"));
        actionRetrieve_Folder_By_Name_2 = new QAction(project02Class);
        actionRetrieve_Folder_By_Name_2->setObjectName(QString::fromUtf8("actionRetrieve_Folder_By_Name_2"));
        actionRetrieve_File_By_Name_2 = new QAction(project02Class);
        actionRetrieve_File_By_Name_2->setObjectName(QString::fromUtf8("actionRetrieve_File_By_Name_2"));
        actionRetrieve_Folder_And_File_By_Name_2 = new QAction(project02Class);
        actionRetrieve_Folder_And_File_By_Name_2->setObjectName(QString::fromUtf8("actionRetrieve_Folder_And_File_By_Name_2"));
        actionRetrieve_Folder_And_File_By_Name_3 = new QAction(project02Class);
        actionRetrieve_Folder_And_File_By_Name_3->setObjectName(QString::fromUtf8("actionRetrieve_Folder_And_File_By_Name_3"));
        QIcon icon11;
        icon11.addFile(QString::fromUtf8(":/project02/Resources/find.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionRetrieve_Folder_And_File_By_Name_3->setIcon(icon11);
        actionRetrieve_Folder_By_Name_3 = new QAction(project02Class);
        actionRetrieve_Folder_By_Name_3->setObjectName(QString::fromUtf8("actionRetrieve_Folder_By_Name_3"));
        actionRetrieve_File_By_Name_3 = new QAction(project02Class);
        actionRetrieve_File_By_Name_3->setObjectName(QString::fromUtf8("actionRetrieve_File_By_Name_3"));
        actionCopy = new QAction(project02Class);
        actionCopy->setObjectName(QString::fromUtf8("actionCopy"));
        actionCut = new QAction(project02Class);
        actionCut->setObjectName(QString::fromUtf8("actionCut"));
        actionPaste = new QAction(project02Class);
        actionPaste->setObjectName(QString::fromUtf8("actionPaste"));
        actionCopy_2 = new QAction(project02Class);
        actionCopy_2->setObjectName(QString::fromUtf8("actionCopy_2"));
        actionCut_2 = new QAction(project02Class);
        actionCut_2->setObjectName(QString::fromUtf8("actionCut_2"));
        actionPaste_2 = new QAction(project02Class);
        actionPaste_2->setObjectName(QString::fromUtf8("actionPaste_2"));
        centralWidget = new QWidget(project02Class);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        formLayout = new QFormLayout(centralWidget);
        formLayout->setSpacing(6);
        formLayout->setContentsMargins(11, 11, 11, 11);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        lineEdit = new QLineEdit(centralWidget);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));

        formLayout->setWidget(0, QFormLayout::FieldRole, lineEdit);

        project02Class->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(project02Class);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 731, 21));
        menuFolder = new QMenu(menuBar);
        menuFolder->setObjectName(QString::fromUtf8("menuFolder"));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuFind = new QMenu(menuBar);
        menuFind->setObjectName(QString::fromUtf8("menuFind"));
        menuOf_all_Folder = new QMenu(menuFind);
        menuOf_all_Folder->setObjectName(QString::fromUtf8("menuOf_all_Folder"));
        menuOf_current_Folder = new QMenu(menuFind);
        menuOf_current_Folder->setObjectName(QString::fromUtf8("menuOf_current_Folder"));
        project02Class->setMenuBar(menuBar);
        mainToolBar = new QToolBar(project02Class);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        project02Class->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(project02Class);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        project02Class->setStatusBar(statusBar);

        menuBar->addAction(menuFolder->menuAction());
        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuFind->menuAction());
        menuFolder->addAction(actionCreate);
        menuFolder->addAction(actionDelete);
        menuFolder->addAction(actionRename);
        menuFolder->addSeparator();
        menuFolder->addAction(actionCopy);
        menuFolder->addAction(actionCut);
        menuFolder->addAction(actionPaste);
        menuFolder->addSeparator();
        menuFolder->addAction(actionOpen_Folder_at_current_folder);
        menuFolder->addAction(actionGo_to_upper_Folder);
        menuFolder->addSeparator();
        menuFolder->addAction(actionGo_Back);
        menuFolder->addAction(actionShow_Back_History);
        menuFolder->addAction(actionGo_Front);
        menuFolder->addAction(actionShow_Front_History);
        menuFolder->addSeparator();
        menuFolder->addAction(actionClear_History);
        menuFolder->addSeparator();
        menuFolder->addAction(actionCurrent_Folder_Property);
        menuFile->addAction(actionCreate_2);
        menuFile->addAction(actionDelete_2);
        menuFile->addAction(actionRename_2);
        menuFile->addSeparator();
        menuFile->addAction(actionCopy_2);
        menuFile->addAction(actionCut_2);
        menuFile->addAction(actionPaste_2);
        menuFile->addSeparator();
        menuFile->addAction(actionOpen_File_At_Current_Folder);
        menuFile->addSeparator();
        menuFile->addAction(actionShow_File_Property);
        menuFind->addAction(menuOf_all_Folder->menuAction());
        menuFind->addAction(menuOf_current_Folder->menuAction());
        menuOf_all_Folder->addAction(actionRetrieve_Folder_By_Name_2);
        menuOf_all_Folder->addAction(actionRetrieve_File_By_Name_2);
        menuOf_all_Folder->addAction(actionRetrieve_Folder_And_File_By_Name_2);
        menuOf_current_Folder->addAction(actionRetrieve_Folder_By_Name_3);
        menuOf_current_Folder->addAction(actionRetrieve_File_By_Name_3);
        menuOf_current_Folder->addAction(actionRetrieve_Folder_And_File_By_Name_3);
        mainToolBar->addSeparator();
        mainToolBar->addAction(actionGo_Back);
        mainToolBar->addAction(actionGo_Front);
        mainToolBar->addAction(actionGo_to_upper_Folder);
        mainToolBar->addAction(actionCreate);
        mainToolBar->addAction(actionDelete);
        mainToolBar->addAction(actionOpen_Folder_at_current_folder);
        mainToolBar->addAction(actionCreate_2);
        mainToolBar->addAction(actionDelete_2);
        mainToolBar->addAction(actionRetrieve_Folder_And_File_By_Name_3);

        retranslateUi(project02Class);

        QMetaObject::connectSlotsByName(project02Class);
    } // setupUi

    void retranslateUi(QMainWindow *project02Class)
    {
        project02Class->setWindowTitle(QApplication::translate("project02Class", "project02", nullptr));
        actionCreate->setText(QApplication::translate("project02Class", "Create", nullptr));
        actionDelete->setText(QApplication::translate("project02Class", "Delete", nullptr));
        actionCreate_2->setText(QApplication::translate("project02Class", "Create", nullptr));
        actionDelete_2->setText(QApplication::translate("project02Class", "Delete", nullptr));
        actionGo_to_upper_Folder->setText(QApplication::translate("project02Class", "Go to Upper Folder", nullptr));
        actionRename->setText(QApplication::translate("project02Class", "Rename", nullptr));
        actionOpen_Folder_at_current_folder->setText(QApplication::translate("project02Class", "Open Folder At Current Folder", nullptr));
        actionGo_Back->setText(QApplication::translate("project02Class", "Go Back", nullptr));
        actionGo_Front->setText(QApplication::translate("project02Class", "Go Front", nullptr));
        actionShow_Back_History->setText(QApplication::translate("project02Class", "Show Back History", nullptr));
        actionShow_Front_History->setText(QApplication::translate("project02Class", "Show Front History", nullptr));
        actionCurrent_Folder_Property->setText(QApplication::translate("project02Class", "Current Folder Property", nullptr));
        actionClear_History->setText(QApplication::translate("project02Class", "Clear History", nullptr));
        actionRead_File_At_Current_Folder->setText(QApplication::translate("project02Class", "Read File At Current Folder", nullptr));
        actionRename_2->setText(QApplication::translate("project02Class", "Rename", nullptr));
        actionShow_File_Property->setText(QApplication::translate("project02Class", "Show File Property", nullptr));
        actionOpen_File_At_Current_Folder->setText(QApplication::translate("project02Class", "Open File At Current Folder", nullptr));
        actionRetrieve_Folder_By_Name->setText(QApplication::translate("project02Class", "Retrieve Folder By Name", nullptr));
        actionRetrieve_File_By_Name->setText(QApplication::translate("project02Class", "Retrieve File By Name", nullptr));
        actionRetrieve_Folder_And_File_By_Name->setText(QApplication::translate("project02Class", "Retrieve Folder And File By Name", nullptr));
        actionRetrieve_Folder_By_Name_2->setText(QApplication::translate("project02Class", "Retrieve Folder By Name", nullptr));
        actionRetrieve_File_By_Name_2->setText(QApplication::translate("project02Class", "Retrieve File By Name", nullptr));
        actionRetrieve_Folder_And_File_By_Name_2->setText(QApplication::translate("project02Class", "Retrieve Folder And File By Name", nullptr));
        actionRetrieve_Folder_And_File_By_Name_3->setText(QApplication::translate("project02Class", "Retrieve Folder And File By Name", nullptr));
        actionRetrieve_Folder_By_Name_3->setText(QApplication::translate("project02Class", "Retrieve Folder By Name", nullptr));
        actionRetrieve_File_By_Name_3->setText(QApplication::translate("project02Class", "Retrieve File By Name", nullptr));
        actionCopy->setText(QApplication::translate("project02Class", "Copy", nullptr));
        actionCut->setText(QApplication::translate("project02Class", "Cut", nullptr));
        actionPaste->setText(QApplication::translate("project02Class", "Paste", nullptr));
        actionCopy_2->setText(QApplication::translate("project02Class", "Copy", nullptr));
        actionCut_2->setText(QApplication::translate("project02Class", "Cut", nullptr));
        actionPaste_2->setText(QApplication::translate("project02Class", "Paste", nullptr));
        label->setText(QApplication::translate("project02Class", "Current Path :", nullptr));
        menuFolder->setTitle(QApplication::translate("project02Class", "Folder", nullptr));
        menuFile->setTitle(QApplication::translate("project02Class", "File", nullptr));
        menuFind->setTitle(QApplication::translate("project02Class", "Retrieve", nullptr));
        menuOf_all_Folder->setTitle(QApplication::translate("project02Class", "Of all Folder", nullptr));
        menuOf_current_Folder->setTitle(QApplication::translate("project02Class", "Of current Folder", nullptr));
    } // retranslateUi

};

namespace Ui {
    class project02Class: public Ui_project02Class {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROJECT02_H
