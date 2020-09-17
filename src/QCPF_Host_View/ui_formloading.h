/********************************************************************************
** Form generated from reading UI file 'formloading.ui'
**
** Created by: Qt User Interface Compiler version 5.13.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMLOADING_H
#define UI_FORMLOADING_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_formLoading
{
public:
    QFrame *frame;
    QLabel *labUsr;
    QLineEdit *txtUser;
    QLabel *labPwd;
    QLineEdit *txtPwd;
    QPushButton *btnOk;
    QPushButton *btnCancel;
    QLabel *laSystemName;
    QLabel *lb_LoadingInfo;
    QLabel *labInfoPrefix_2;
    QLabel *labCoreVersion;
    QLabel *labViewVersion;

    void setupUi(QDialog *formLoading)
    {
        if (formLoading->objectName().isEmpty())
            formLoading->setObjectName(QString::fromUtf8("formLoading"));
        formLoading->setWindowModality(Qt::WindowModal);
        formLoading->resize(614, 456);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(formLoading->sizePolicy().hasHeightForWidth());
        formLoading->setSizePolicy(sizePolicy);
        formLoading->setAutoFillBackground(false);
        formLoading->setStyleSheet(QString::fromUtf8("#formLoading {border-image: url(:/Images/BackgroundImage6.jpg);}"));
        frame = new QFrame(formLoading);
        frame->setObjectName(QString::fromUtf8("frame"));
        frame->setGeometry(QRect(210, 50, 351, 301));
        frame->setStyleSheet(QString::fromUtf8("#frame { background-color: rgb(231, 231, 231);}"));
        frame->setFrameShape(QFrame::StyledPanel);
        frame->setFrameShadow(QFrame::Raised);
        labUsr = new QLabel(frame);
        labUsr->setObjectName(QString::fromUtf8("labUsr"));
        labUsr->setGeometry(QRect(13, 136, 61, 16));
        labUsr->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";"));
        txtUser = new QLineEdit(frame);
        txtUser->setObjectName(QString::fromUtf8("txtUser"));
        txtUser->setGeometry(QRect(80, 130, 211, 31));
        txtUser->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";"));
        labPwd = new QLabel(frame);
        labPwd->setObjectName(QString::fromUtf8("labPwd"));
        labPwd->setGeometry(QRect(13, 197, 61, 16));
        labPwd->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";"));
        txtPwd = new QLineEdit(frame);
        txtPwd->setObjectName(QString::fromUtf8("txtPwd"));
        txtPwd->setGeometry(QRect(80, 190, 211, 31));
        txtPwd->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";"));
        btnOk = new QPushButton(frame);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setGeometry(QRect(80, 250, 91, 34));
        btnOk->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";"));
        btnCancel = new QPushButton(frame);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(200, 250, 91, 34));
        btnCancel->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";"));
        laSystemName = new QLabel(frame);
        laSystemName->setObjectName(QString::fromUtf8("laSystemName"));
        laSystemName->setGeometry(QRect(0, 30, 351, 81));
        QFont font;
        font.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font.setPointSize(20);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        laSystemName->setFont(font);
        laSystemName->setStyleSheet(QString::fromUtf8("font: 75 20pt \"Microsoft YaHei UI\";"));
        laSystemName->setAlignment(Qt::AlignCenter);
        laSystemName->setWordWrap(true);
        laSystemName->setMargin(5);
        lb_LoadingInfo = new QLabel(formLoading);
        lb_LoadingInfo->setObjectName(QString::fromUtf8("lb_LoadingInfo"));
        lb_LoadingInfo->setGeometry(QRect(210, 360, 351, 61));
        lb_LoadingInfo->setWordWrap(true);
        labInfoPrefix_2 = new QLabel(formLoading);
        labInfoPrefix_2->setObjectName(QString::fromUtf8("labInfoPrefix_2"));
        labInfoPrefix_2->setEnabled(true);
        labInfoPrefix_2->setGeometry(QRect(30, 430, 131, 20));
        labInfoPrefix_2->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";\n"
"color: rgb(104, 104, 104);"));
        labCoreVersion = new QLabel(formLoading);
        labCoreVersion->setObjectName(QString::fromUtf8("labCoreVersion"));
        labCoreVersion->setEnabled(true);
        labCoreVersion->setGeometry(QRect(210, 430, 131, 20));
        labCoreVersion->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";\n"
"color: rgb(104, 104, 104);"));
        labViewVersion = new QLabel(formLoading);
        labViewVersion->setObjectName(QString::fromUtf8("labViewVersion"));
        labViewVersion->setEnabled(true);
        labViewVersion->setGeometry(QRect(470, 430, 131, 20));
        labViewVersion->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";\n"
"color: rgb(104, 104, 104);"));

        retranslateUi(formLoading);

        QMetaObject::connectSlotsByName(formLoading);
    } // setupUi

    void retranslateUi(QDialog *formLoading)
    {
        formLoading->setWindowTitle(QCoreApplication::translate("formLoading", "\347\231\273\345\275\225", nullptr));
        labUsr->setText(QCoreApplication::translate("formLoading", "User:", nullptr));
        txtUser->setText(QCoreApplication::translate("formLoading", "tt", nullptr));
        labPwd->setText(QCoreApplication::translate("formLoading", "Password:", nullptr));
        txtPwd->setText(QCoreApplication::translate("formLoading", "1", nullptr));
        btnOk->setText(QCoreApplication::translate("formLoading", "Load", nullptr));
        btnCancel->setText(QCoreApplication::translate("formLoading", "Cancel", nullptr));
        laSystemName->setText(QCoreApplication::translate("formLoading", "QCPF Framework", nullptr));
        lb_LoadingInfo->setText(QString());
        labInfoPrefix_2->setText(QCoreApplication::translate("formLoading", "Copyright \302\251 Jamie.T", nullptr));
        labCoreVersion->setText(QCoreApplication::translate("formLoading", "Core Verson:", nullptr));
        labViewVersion->setText(QCoreApplication::translate("formLoading", "View Verson:", nullptr));
    } // retranslateUi

};

namespace Ui {
    class formLoading: public Ui_formLoading {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMLOADING_H
