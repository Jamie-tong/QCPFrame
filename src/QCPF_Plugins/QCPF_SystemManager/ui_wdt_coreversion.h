/********************************************************************************
** Form generated from reading UI file 'wdt_coreversion.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WDT_COREVERSION_H
#define UI_WDT_COREVERSION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wdt_CoreVersion
{
public:
    QLabel *label;
    QLabel *labCoreVersion;

    void setupUi(QWidget *wdt_CoreVersion)
    {
        if (wdt_CoreVersion->objectName().isEmpty())
            wdt_CoreVersion->setObjectName(QString::fromUtf8("wdt_CoreVersion"));
        wdt_CoreVersion->resize(96, 24);
        label = new QLabel(wdt_CoreVersion);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(6, 3, 31, 16));
        labCoreVersion = new QLabel(wdt_CoreVersion);
        labCoreVersion->setObjectName(QString::fromUtf8("labCoreVersion"));
        labCoreVersion->setGeometry(QRect(40, 3, 51, 16));

        retranslateUi(wdt_CoreVersion);

        QMetaObject::connectSlotsByName(wdt_CoreVersion);
    } // setupUi

    void retranslateUi(QWidget *wdt_CoreVersion)
    {
        wdt_CoreVersion->setWindowTitle(QCoreApplication::translate("wdt_CoreVersion", "Form", nullptr));
        label->setText(QCoreApplication::translate("wdt_CoreVersion", "Core:", nullptr));
        labCoreVersion->setText(QCoreApplication::translate("wdt_CoreVersion", "1.0.0.3", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wdt_CoreVersion: public Ui_wdt_CoreVersion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WDT_COREVERSION_H
