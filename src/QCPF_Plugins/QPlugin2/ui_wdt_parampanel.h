/********************************************************************************
** Form generated from reading UI file 'wdt_parampanel.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WDT_PARAMPANEL_H
#define UI_WDT_PARAMPANEL_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_wdt_ParamPanel
{
public:
    QFrame *frame;

    void setupUi(QWidget *wdt_ParamPanel)
    {
        if (wdt_ParamPanel->objectName().isEmpty())
            wdt_ParamPanel->setObjectName(QString::fromUtf8("wdt_ParamPanel"));
        wdt_ParamPanel->resize(450, 539);
        wdt_ParamPanel->setStyleSheet(QString::fromUtf8(""));
        frame = new QFrame(wdt_ParamPanel);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(0, 0, 452, 771));
        frame->setStyleSheet(QString::fromUtf8("background-image: url(:/bin/Image/status.png);"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);

        retranslateUi(wdt_ParamPanel);

        QMetaObject::connectSlotsByName(wdt_ParamPanel);
    } // setupUi

    void retranslateUi(QWidget *wdt_ParamPanel)
    {
        wdt_ParamPanel->setWindowTitle(QCoreApplication::translate("wdt_ParamPanel", "Params panel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class wdt_ParamPanel: public Ui_wdt_ParamPanel {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WDT_PARAMPANEL_H
