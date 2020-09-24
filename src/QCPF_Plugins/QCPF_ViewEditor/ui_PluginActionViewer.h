/********************************************************************************
** Form generated from reading UI file 'PluginActionViewer.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGINACTIONVIEWER_H
#define UI_PLUGINACTIONVIEWER_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PluginActionViewer
{
public:
    QDialogButtonBox *buttonBox;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QGroupBox *groupBox_2;
    QLabel *label_5;
    QLineEdit *txtActionName;
    QTextBrowser *txtActionDetail;
    QLabel *label_8;
    QGroupBox *groupBox;
    QComboBox *cbPluginAction;
    QLabel *label;
    QComboBox *cbPluginID;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *cbCopyID;

    void setupUi(QDialog *PluginActionViewer)
    {
        if (PluginActionViewer->objectName().isEmpty())
            PluginActionViewer->setObjectName(QString::fromUtf8("PluginActionViewer"));
        PluginActionViewer->resize(362, 413);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../bin/debug/Images/viewedit.png"), QSize(), QIcon::Normal, QIcon::Off);
        PluginActionViewer->setWindowIcon(icon);
        buttonBox = new QDialogButtonBox(PluginActionViewer);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(10, 370, 341, 41));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        tabWidget = new QTabWidget(PluginActionViewer);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 0, 351, 21));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        groupBox_2 = new QGroupBox(PluginActionViewer);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 170, 341, 201));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(16, 20, 71, 20));
        txtActionName = new QLineEdit(groupBox_2);
        txtActionName->setObjectName(QString::fromUtf8("txtActionName"));
        txtActionName->setEnabled(true);
        txtActionName->setGeometry(QRect(90, 20, 241, 20));
        txtActionName->setReadOnly(true);
        txtActionDetail = new QTextBrowser(groupBox_2);
        txtActionDetail->setObjectName(QString::fromUtf8("txtActionDetail"));
        txtActionDetail->setEnabled(true);
        txtActionDetail->setGeometry(QRect(90, 50, 241, 141));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(17, 50, 71, 20));
        groupBox = new QGroupBox(PluginActionViewer);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 30, 341, 131));
        cbPluginAction = new QComboBox(groupBox);
        cbPluginAction->setObjectName(QString::fromUtf8("cbPluginAction"));
        cbPluginAction->setGeometry(QRect(90, 60, 241, 22));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(16, 30, 71, 16));
        cbPluginID = new QComboBox(groupBox);
        cbPluginID->setObjectName(QString::fromUtf8("cbPluginID"));
        cbPluginID->setGeometry(QRect(90, 30, 241, 22));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(16, 62, 71, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(16, 90, 71, 16));
        cbCopyID = new QComboBox(groupBox);
        cbCopyID->setObjectName(QString::fromUtf8("cbCopyID"));
        cbCopyID->setGeometry(QRect(90, 90, 241, 22));
        label_2->raise();
        cbPluginAction->raise();
        label->raise();
        cbPluginID->raise();
        label_3->raise();
        cbCopyID->raise();

        retranslateUi(PluginActionViewer);
        QObject::connect(buttonBox, SIGNAL(accepted()), PluginActionViewer, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PluginActionViewer, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PluginActionViewer);
    } // setupUi

    void retranslateUi(QDialog *PluginActionViewer)
    {
        PluginActionViewer->setWindowTitle(QCoreApplication::translate("PluginActionViewer", "Function Viewer", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("PluginActionViewer", "System Plugins", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("PluginActionViewer", "Non-System Plugins", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PluginActionViewer", "Action info", nullptr));
        label_5->setText(QCoreApplication::translate("PluginActionViewer", "Name", nullptr));
        label_8->setText(QCoreApplication::translate("PluginActionViewer", "Detail:", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PluginActionViewer", "Plugin info", nullptr));
        label->setText(QCoreApplication::translate("PluginActionViewer", "Plugin ID:", nullptr));
        label_2->setText(QCoreApplication::translate("PluginActionViewer", "Action:", nullptr));
        label_3->setText(QCoreApplication::translate("PluginActionViewer", "Copy ID:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PluginActionViewer: public Ui_PluginActionViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGINACTIONVIEWER_H
