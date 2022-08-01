/********************************************************************************
** Form generated from reading UI file 'wdt_hud.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WDT_HUD_H
#define UI_WDT_HUD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wdt_Hud
{
public:
    QFrame *frame;

    void setupUi(QWidget *wdt_Hud)
    {
        if (wdt_Hud->objectName().isEmpty())
            wdt_Hud->setObjectName(QString::fromUtf8("wdt_Hud"));
        wdt_Hud->resize(450, 330);
        wdt_Hud->setStyleSheet(QString::fromUtf8(""));
        frame = new QFrame(wdt_Hud);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 451, 331));
        frame->setStyleSheet(QString::fromUtf8("border-image: url(:/bin/Image/hud.png);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        retranslateUi(wdt_Hud);

        QMetaObject::connectSlotsByName(wdt_Hud);
    } // setupUi

    void retranslateUi(QWidget *wdt_Hud)
    {
        wdt_Hud->setWindowTitle(QCoreApplication::translate("wdt_Hud", "Hud", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wdt_Hud: public Ui_wdt_Hud {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WDT_HUD_H
