/********************************************************************************
** Form generated from reading UI file 'wdt_viewversion.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WDT_VIEWVERSION_H
#define UI_WDT_VIEWVERSION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wdt_ViewVersion
{
public:
    QLabel *labViewVersion;
    QLabel *label;

    void setupUi(QWidget *wdt_ViewVersion)
    {
        if (wdt_ViewVersion->objectName().isEmpty())
            wdt_ViewVersion->setObjectName(QString::fromUtf8("wdt_ViewVersion"));
        wdt_ViewVersion->resize(96, 24);
        labViewVersion = new QLabel(wdt_ViewVersion);
        labViewVersion->setObjectName(QString::fromUtf8("labViewVersion"));
        labViewVersion->setGeometry(QRect(40, 4, 51, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("Agency FB"));
        labViewVersion->setFont(font);
        label = new QLabel(wdt_ViewVersion);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(5, 4, 31, 16));

        retranslateUi(wdt_ViewVersion);

        QMetaObject::connectSlotsByName(wdt_ViewVersion);
    } // setupUi

    void retranslateUi(QWidget *wdt_ViewVersion)
    {
        wdt_ViewVersion->setWindowTitle(QCoreApplication::translate("wdt_ViewVersion", "Form", nullptr));
        labViewVersion->setText(QCoreApplication::translate("wdt_ViewVersion", "1.0.0.3", nullptr));
        label->setText(QCoreApplication::translate("wdt_ViewVersion", "View:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wdt_ViewVersion: public Ui_wdt_ViewVersion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WDT_VIEWVERSION_H
