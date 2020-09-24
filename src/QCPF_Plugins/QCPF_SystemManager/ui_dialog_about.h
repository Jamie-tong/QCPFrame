/********************************************************************************
** Form generated from reading UI file 'dialog_about.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DIALOG_ABOUT_H
#define UI_DIALOG_ABOUT_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_Dialog_About
{
public:
    QLabel *label;
    QLabel *label_2;
    QLabel *labCoreVersion;
    QLabel *label_4;
    QPushButton *btnClose;
    QLabel *labViewVersion;
    QLabel *labSystemName;
    QLabel *labSystemID;

    void setupUi(QDialog *Dialog_About)
    {
        if (Dialog_About->objectName().isEmpty())
            Dialog_About->setObjectName(QString::fromUtf8("Dialog_About"));
        Dialog_About->resize(560, 356);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../bin/debug/Images/about.png"), QSize(), QIcon::Normal, QIcon::Off);
        Dialog_About->setWindowIcon(icon);
        label = new QLabel(Dialog_About);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(30, 3, 181, 41));
        label->setStyleSheet(QString::fromUtf8("font: 87 10pt \"Arial Black\";"));
        label_2 = new QLabel(Dialog_About);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(400, 270, 141, 31));
        label_2->setStyleSheet(QString::fromUtf8("font: 85 9.3pt \"Arial Black\";"));
        labCoreVersion = new QLabel(Dialog_About);
        labCoreVersion->setObjectName(QString::fromUtf8("labCoreVersion"));
        labCoreVersion->setGeometry(QRect(40, 240, 151, 21));
        labCoreVersion->setStyleSheet(QString::fromUtf8("font: 9pt \"Arial\";"));
        label_4 = new QLabel(Dialog_About);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(40, 55, 491, 171));
        label_4->setStyleSheet(QString::fromUtf8("font: 9pt \"Courier New\";"));
        label_4->setTextFormat(Qt::AutoText);
        label_4->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        label_4->setWordWrap(true);
        btnClose = new QPushButton(Dialog_About);
        btnClose->setObjectName(QString::fromUtf8("btnClose"));
        btnClose->setGeometry(QRect(397, 300, 141, 41));
        labViewVersion = new QLabel(Dialog_About);
        labViewVersion->setObjectName(QString::fromUtf8("labViewVersion"));
        labViewVersion->setGeometry(QRect(40, 260, 141, 21));
        labViewVersion->setStyleSheet(QString::fromUtf8("font: 9pt \"Arial\";"));
        labSystemName = new QLabel(Dialog_About);
        labSystemName->setObjectName(QString::fromUtf8("labSystemName"));
        labSystemName->setGeometry(QRect(40, 300, 331, 21));
        labSystemName->setStyleSheet(QString::fromUtf8("font: 9pt \"Arial\";"));
        labSystemID = new QLabel(Dialog_About);
        labSystemID->setObjectName(QString::fromUtf8("labSystemID"));
        labSystemID->setGeometry(QRect(40, 320, 331, 21));
        labSystemID->setStyleSheet(QString::fromUtf8("font: 9pt \"Arial\";"));
        label->raise();
        labCoreVersion->raise();
        label_4->raise();
        btnClose->raise();
        label_2->raise();
        labViewVersion->raise();
        labSystemName->raise();
        labSystemID->raise();

        retranslateUi(Dialog_About);

        QMetaObject::connectSlotsByName(Dialog_About);
    } // setupUi

    void retranslateUi(QDialog *Dialog_About)
    {
        Dialog_About->setWindowTitle(QCoreApplication::translate("Dialog_About", "About", nullptr));
        label->setText(QCoreApplication::translate("Dialog_About", "GPL . QCPFrame", nullptr));
        label_2->setText(QCoreApplication::translate("Dialog_About", "Powered by Jamie.T", nullptr));
        labCoreVersion->setText(QCoreApplication::translate("Dialog_About", "Core Version:", nullptr));
        label_4->setText(QCoreApplication::translate("Dialog_About", "  QCPFrame is a plugin framework that base on Qt. it can help you and your team develop agilely. for QCPFrame family, any element of your program such as function, menu-bar item, tool-bar item, status-bar item, docks of workspace can be a plugin or widget, it can be loaded, unloaded, edited by the \"View Editor\" who also is a plugin.  the core of the QCPFrame can make you run a console with base plugin system, the View Model can run them with UI, it's a multi-layered plugin system that can run in Linux and Windows. in the end, QCPFrame is a open-source project for you. any questions or suggestions, please let me know, you can also submit your code, let's make it better together, thanks!", nullptr));
        btnClose->setText(QCoreApplication::translate("Dialog_About", "Close", nullptr));
        labViewVersion->setText(QCoreApplication::translate("Dialog_About", "View Version:", nullptr));
        labSystemName->setText(QCoreApplication::translate("Dialog_About", "System Name:", nullptr));
        labSystemID->setText(QCoreApplication::translate("Dialog_About", "System ID:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Dialog_About: public Ui_Dialog_About {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DIALOG_ABOUT_H
