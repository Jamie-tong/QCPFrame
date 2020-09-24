/********************************************************************************
** Form generated from reading UI file 'wdt_map.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WDT_MAP_H
#define UI_WDT_MAP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wdt_Map
{
public:
    QFrame *frame;

    void setupUi(QWidget *wdt_Map)
    {
        if (wdt_Map->objectName().isEmpty())
            wdt_Map->setObjectName(QString::fromUtf8("wdt_Map"));
        wdt_Map->resize(1648, 1079);
        wdt_Map->setStyleSheet(QString::fromUtf8(""));
        frame = new QFrame(wdt_Map);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 1651, 1081));
        frame->setStyleSheet(QString::fromUtf8("border-image: url(:/bin/Images/map.png);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        retranslateUi(wdt_Map);

        QMetaObject::connectSlotsByName(wdt_Map);
    } // setupUi

    void retranslateUi(QWidget *wdt_Map)
    {
        wdt_Map->setWindowTitle(QCoreApplication::translate("wdt_Map", "Map", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wdt_Map: public Ui_wdt_Map {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WDT_MAP_H
