/********************************************************************************
** Form generated from reading UI file 'pluginform2.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLUGINFORM2_H
#define UI_PLUGINFORM2_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_pluginform2
{
public:
    QTableWidget *tableWidget;

    void setupUi(QWidget *pluginform2)
    {
        if (pluginform2->objectName().isEmpty())
            pluginform2->setObjectName(QString::fromUtf8("pluginform2"));
        pluginform2->resize(282, 739);
        tableWidget = new QTableWidget(pluginform2);
        if (tableWidget->columnCount() < 12)
            tableWidget->setColumnCount(12);
        if (tableWidget->rowCount() < 60)
            tableWidget->setRowCount(60);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setGeometry(QRect(0, 0, 401, 1111));
        QFont font;
        font.setPointSize(9);
        tableWidget->setFont(font);
        tableWidget->setFrameShape(QFrame::Panel);
        tableWidget->setAlternatingRowColors(true);
        tableWidget->setRowCount(60);
        tableWidget->setColumnCount(12);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setMinimumSectionSize(18);
        tableWidget->horizontalHeader()->setDefaultSectionSize(100);
        tableWidget->horizontalHeader()->setHighlightSections(true);
        tableWidget->verticalHeader()->setVisible(false);
        tableWidget->verticalHeader()->setMinimumSectionSize(18);
        tableWidget->verticalHeader()->setDefaultSectionSize(18);

        retranslateUi(pluginform2);

        QMetaObject::connectSlotsByName(pluginform2);
    } // setupUi

    void retranslateUi(QWidget *pluginform2)
    {
        pluginform2->setWindowTitle(QCoreApplication::translate("pluginform2", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class pluginform2: public Ui_pluginform2 {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLUGINFORM2_H
