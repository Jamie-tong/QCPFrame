/********************************************************************************
** Form generated from reading UI file 'wdt_currentdatatime.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WDT_CURRENTDATATIME_H
#define UI_WDT_CURRENTDATATIME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wdt_CurrentDataTime
{
public:
    QLabel *label;
    QLabel *labDateTime;

    void setupUi(QWidget *wdt_CurrentDataTime)
    {
        if (wdt_CurrentDataTime->objectName().isEmpty())
            wdt_CurrentDataTime->setObjectName(QString::fromUtf8("wdt_CurrentDataTime"));
        wdt_CurrentDataTime->resize(181, 24);
        label = new QLabel(wdt_CurrentDataTime);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(4, 4, 41, 16));
        labDateTime = new QLabel(wdt_CurrentDataTime);
        labDateTime->setObjectName(QString::fromUtf8("labDateTime"));
        labDateTime->setGeometry(QRect(39, 5, 131, 16));
        labDateTime->setFrameShape(QFrame::StyledPanel);
        labDateTime->setFrameShadow(QFrame::Plain);

        retranslateUi(wdt_CurrentDataTime);

        QMetaObject::connectSlotsByName(wdt_CurrentDataTime);
    } // setupUi

    void retranslateUi(QWidget *wdt_CurrentDataTime)
    {
        wdt_CurrentDataTime->setWindowTitle(QCoreApplication::translate("wdt_CurrentDataTime", "Form", nullptr));
        label->setText(QCoreApplication::translate("wdt_CurrentDataTime", "Time:", nullptr));
        labDateTime->setText(QCoreApplication::translate("wdt_CurrentDataTime", "2020-08-26", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wdt_CurrentDataTime: public Ui_wdt_CurrentDataTime {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WDT_CURRENTDATATIME_H
