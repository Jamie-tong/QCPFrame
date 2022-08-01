/********************************************************************************
** Form generated from reading UI file 'wdt_search.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WDT_SEARCH_H
#define UI_WDT_SEARCH_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wdt_search
{
public:
    QLineEdit *lineEdit;

    void setupUi(QWidget *wdt_search)
    {
        if (wdt_search->objectName().isEmpty())
            wdt_search->setObjectName(QString::fromUtf8("wdt_search"));
        wdt_search->resize(223, 39);
        lineEdit = new QLineEdit(wdt_search);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(4, 4, 211, 31));

        retranslateUi(wdt_search);

        QMetaObject::connectSlotsByName(wdt_search);
    } // setupUi

    void retranslateUi(QWidget *wdt_search)
    {
        wdt_search->setWindowTitle(QCoreApplication::translate("wdt_search", "Form", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("wdt_search", "Search", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wdt_search: public Ui_wdt_search {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WDT_SEARCH_H
