/********************************************************************************
** Form generated from reading UI file 'pluginwidgetviewer.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGINWIDGETVIEWER_H
#define UI_PLUGINWIDGETVIEWER_H

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

class Ui_PluginWidgetViewer
{
public:
    QDialogButtonBox *buttonBox;
    QGroupBox *groupBox_2;
    QLabel *label_5;
    QLineEdit *txtWidgetObjectName;
    QTextBrowser *txtWidgetDetail;
    QLabel *label_8;
    QLineEdit *txtWidgetOrigSize;
    QLabel *label_9;
    QTabWidget *tabWidget;
    QWidget *tab;
    QWidget *tab_2;
    QGroupBox *groupBox;
    QComboBox *cbPluginWidget;
    QLabel *label;
    QComboBox *cbPluginID;
    QLabel *label_2;
    QLabel *label_3;
    QComboBox *cbCopyID;
    QLabel *label_4;
    QComboBox *cbStatusbarItemType;

    void setupUi(QDialog *PluginWidgetViewer)
    {
        if (PluginWidgetViewer->objectName().isEmpty())
            PluginWidgetViewer->setObjectName(QString::fromUtf8("PluginWidgetViewer"));
        PluginWidgetViewer->resize(360, 446);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../bin/debug/Images/viewedit.png"), QSize(), QIcon::Normal, QIcon::Off);
        PluginWidgetViewer->setWindowIcon(icon);
        buttonBox = new QDialogButtonBox(PluginWidgetViewer);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setGeometry(QRect(-10, 410, 362, 32));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        groupBox_2 = new QGroupBox(PluginWidgetViewer);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 200, 341, 201));
        label_5 = new QLabel(groupBox_2);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(16, 20, 71, 20));
        txtWidgetObjectName = new QLineEdit(groupBox_2);
        txtWidgetObjectName->setObjectName(QString::fromUtf8("txtWidgetObjectName"));
        txtWidgetObjectName->setEnabled(true);
        txtWidgetObjectName->setGeometry(QRect(90, 20, 241, 20));
        txtWidgetObjectName->setReadOnly(true);
        txtWidgetDetail = new QTextBrowser(groupBox_2);
        txtWidgetDetail->setObjectName(QString::fromUtf8("txtWidgetDetail"));
        txtWidgetDetail->setEnabled(true);
        txtWidgetDetail->setGeometry(QRect(90, 80, 241, 111));
        label_8 = new QLabel(groupBox_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(16, 80, 71, 20));
        txtWidgetOrigSize = new QLineEdit(groupBox_2);
        txtWidgetOrigSize->setObjectName(QString::fromUtf8("txtWidgetOrigSize"));
        txtWidgetOrigSize->setEnabled(true);
        txtWidgetOrigSize->setGeometry(QRect(90, 50, 241, 20));
        txtWidgetOrigSize->setReadOnly(true);
        label_9 = new QLabel(groupBox_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(16, 50, 71, 20));
        tabWidget = new QTabWidget(PluginWidgetViewer);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(10, 0, 351, 21));
        tab = new QWidget();
        tab->setObjectName(QString::fromUtf8("tab"));
        tabWidget->addTab(tab, QString());
        tab_2 = new QWidget();
        tab_2->setObjectName(QString::fromUtf8("tab_2"));
        tabWidget->addTab(tab_2, QString());
        groupBox = new QGroupBox(PluginWidgetViewer);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(10, 30, 341, 161));
        cbPluginWidget = new QComboBox(groupBox);
        cbPluginWidget->setObjectName(QString::fromUtf8("cbPluginWidget"));
        cbPluginWidget->setGeometry(QRect(90, 60, 241, 22));
        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(16, 33, 71, 16));
        cbPluginID = new QComboBox(groupBox);
        cbPluginID->setObjectName(QString::fromUtf8("cbPluginID"));
        cbPluginID->setGeometry(QRect(90, 30, 241, 22));
        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(16, 63, 71, 16));
        label_3 = new QLabel(groupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(16, 93, 71, 16));
        cbCopyID = new QComboBox(groupBox);
        cbCopyID->setObjectName(QString::fromUtf8("cbCopyID"));
        cbCopyID->setGeometry(QRect(90, 90, 241, 22));
        label_4 = new QLabel(groupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(16, 123, 71, 16));
        cbStatusbarItemType = new QComboBox(groupBox);
        cbStatusbarItemType->addItem(QString());
        cbStatusbarItemType->addItem(QString());
        cbStatusbarItemType->setObjectName(QString::fromUtf8("cbStatusbarItemType"));
        cbStatusbarItemType->setGeometry(QRect(90, 120, 241, 22));
        label_2->raise();
        cbPluginWidget->raise();
        label->raise();
        cbPluginID->raise();
        label_3->raise();
        cbCopyID->raise();
        label_4->raise();
        cbStatusbarItemType->raise();

        retranslateUi(PluginWidgetViewer);
        QObject::connect(buttonBox, SIGNAL(accepted()), PluginWidgetViewer, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), PluginWidgetViewer, SLOT(reject()));

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(PluginWidgetViewer);
    } // setupUi

    void retranslateUi(QDialog *PluginWidgetViewer)
    {
        PluginWidgetViewer->setWindowTitle(QCoreApplication::translate("PluginWidgetViewer", "Widget Viewer", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("PluginWidgetViewer", "Widget info", nullptr));
        label_5->setText(QCoreApplication::translate("PluginWidgetViewer", "Widget:", nullptr));
        label_8->setText(QCoreApplication::translate("PluginWidgetViewer", "Detail:", nullptr));
        label_9->setText(QCoreApplication::translate("PluginWidgetViewer", "Size:", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab), QCoreApplication::translate("PluginWidgetViewer", "System Plugins", nullptr));
        tabWidget->setTabText(tabWidget->indexOf(tab_2), QCoreApplication::translate("PluginWidgetViewer", "Non-System Plugins", nullptr));
        groupBox->setTitle(QCoreApplication::translate("PluginWidgetViewer", "Plugin info", nullptr));
        label->setText(QCoreApplication::translate("PluginWidgetViewer", "Plugin ID:", nullptr));
        label_2->setText(QCoreApplication::translate("PluginWidgetViewer", "Widget:", nullptr));
        label_3->setText(QCoreApplication::translate("PluginWidgetViewer", "Copy ID:", nullptr));
        label_4->setText(QCoreApplication::translate("PluginWidgetViewer", "Type:", nullptr));
        cbStatusbarItemType->setItemText(0, QCoreApplication::translate("PluginWidgetViewer", "Common", nullptr));
        cbStatusbarItemType->setItemText(1, QCoreApplication::translate("PluginWidgetViewer", "Permanent", nullptr));

        cbStatusbarItemType->setCurrentText(QCoreApplication::translate("PluginWidgetViewer", "Common", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PluginWidgetViewer: public Ui_PluginWidgetViewer {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGINWIDGETVIEWER_H
