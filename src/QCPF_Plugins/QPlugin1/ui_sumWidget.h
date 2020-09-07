/********************************************************************************
** Form generated from reading UI file 'sumWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SUMWIDGET_H
#define UI_SUMWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Sum
{
public:
    QSpinBox *spinBox1;
    QSpinBox *spinBox2;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBoxEnd;

    void setupUi(QWidget *Sum)
    {
        if (Sum->objectName().isEmpty())
            Sum->setObjectName(QString::fromUtf8("Sum"));
        Sum->resize(230, 32);
        spinBox1 = new QSpinBox(Sum);
        spinBox1->setObjectName(QString::fromUtf8("spinBox1"));
        spinBox1->setGeometry(QRect(8, 6, 61, 22));
        spinBox2 = new QSpinBox(Sum);
        spinBox2->setObjectName(QString::fromUtf8("spinBox2"));
        spinBox2->setGeometry(QRect(84, 6, 61, 22));
        label = new QLabel(Sum);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(73, 10, 16, 16));
        label_2 = new QLabel(Sum);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(150, 9, 16, 16));
        spinBoxEnd = new QSpinBox(Sum);
        spinBoxEnd->setObjectName(QString::fromUtf8("spinBoxEnd"));
        spinBoxEnd->setGeometry(QRect(162, 6, 61, 22));

        retranslateUi(Sum);

        QMetaObject::connectSlotsByName(Sum);
    } // setupUi

    void retranslateUi(QWidget *Sum)
    {
        Sum->setWindowTitle(QCoreApplication::translate("Sum", "Form", nullptr));
        label->setText(QCoreApplication::translate("Sum", "+", nullptr));
        label_2->setText(QCoreApplication::translate("Sum", "=", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Sum: public Ui_Sum {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SUMWIDGET_H
