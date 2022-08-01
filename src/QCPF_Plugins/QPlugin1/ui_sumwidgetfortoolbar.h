/********************************************************************************
** Form generated from reading UI file 'sumwidgetfortoolbar.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUMWIDGETFORTOOLBAR_H
#define UI_SUMWIDGETFORTOOLBAR_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SumWidgetForToolbar
{
public:
    QSpinBox *spinBoxEnd;
    QSpinBox *spinBox1;
    QLabel *label_2;
    QSpinBox *spinBox2;
    QLabel *label;

    void setupUi(QWidget *SumWidgetForToolbar)
    {
        if (SumWidgetForToolbar->objectName().isEmpty())
            SumWidgetForToolbar->setObjectName(QString::fromUtf8("SumWidgetForToolbar"));
        SumWidgetForToolbar->resize(223, 28);
        spinBoxEnd = new QSpinBox(SumWidgetForToolbar);
        spinBoxEnd->setObjectName(QString::fromUtf8("spinBoxEnd"));
        spinBoxEnd->setGeometry(QRect(158, 3, 61, 22));
        spinBox1 = new QSpinBox(SumWidgetForToolbar);
        spinBox1->setObjectName(QString::fromUtf8("spinBox1"));
        spinBox1->setGeometry(QRect(4, 3, 61, 22));
        label_2 = new QLabel(SumWidgetForToolbar);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(146, 6, 16, 16));
        spinBox2 = new QSpinBox(SumWidgetForToolbar);
        spinBox2->setObjectName(QString::fromUtf8("spinBox2"));
        spinBox2->setGeometry(QRect(80, 3, 61, 22));
        label = new QLabel(SumWidgetForToolbar);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(69, 4, 16, 16));

        retranslateUi(SumWidgetForToolbar);

        QMetaObject::connectSlotsByName(SumWidgetForToolbar);
    } // setupUi

    void retranslateUi(QWidget *SumWidgetForToolbar)
    {
        SumWidgetForToolbar->setWindowTitle(QCoreApplication::translate("SumWidgetForToolbar", "Form", nullptr));
        label_2->setText(QCoreApplication::translate("SumWidgetForToolbar", "=", nullptr));
        label->setText(QCoreApplication::translate("SumWidgetForToolbar", "+", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SumWidgetForToolbar: public Ui_SumWidgetForToolbar {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUMWIDGETFORTOOLBAR_H
