/********************************************************************************
** Form generated from reading UI file 'formloading.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FORMLOADING_H
#define UI_FORMLOADING_H

#include <QtCore/QLocale>
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
    QFrame *frameLoad;
    QLabel *laSystemName;
    QFrame *frameLogin;
    QPushButton *btnCancel;
    QLabel *labPwd;
    QPushButton *btnOk;
    QLineEdit *txtUser;
    QLineEdit *txtPwd;
    QLabel *labUsr;
    QLabel *labInfoPrefix_2;
    QLabel *labCoreVersion;
    QLabel *labViewVersion;
    QLabel *labelBackgroud;
    QLabel *lb_LoadingInfo;

    void setupUi(QDialog *formLoading)
    {
        if (formLoading->objectName().isEmpty())
            formLoading->setObjectName(QString::fromUtf8("formLoading"));
        formLoading->setWindowModality(Qt::WindowModal);
        formLoading->setEnabled(true);
        formLoading->resize(610, 450);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(formLoading->sizePolicy().hasHeightForWidth());
        formLoading->setSizePolicy(sizePolicy);
        formLoading->setLayoutDirection(Qt::LeftToRight);
        formLoading->setAutoFillBackground(false);
        formLoading->setStyleSheet(QString::fromUtf8(""));
        formLoading->setLocale(QLocale(QLocale::Chinese, QLocale::China));
        frameLoad = new QFrame(formLoading);
        frameLoad->setObjectName(QString::fromUtf8("frameLoad"));
        frameLoad->setGeometry(QRect(190, 99, 411, 271));
        frameLoad->setStyleSheet(QString::fromUtf8("#frame { background-color: rgb(231, 231, 231);}"));
        frameLoad->setFrameShape(QFrame::StyledPanel);
        frameLoad->setFrameShadow(QFrame::Raised);
        laSystemName = new QLabel(frameLoad);
        laSystemName->setObjectName(QString::fromUtf8("laSystemName"));
        laSystemName->setGeometry(QRect(0, 0, 431, 81));
        QFont font;
        font.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font.setPointSize(28);
        font.setBold(false);
        font.setItalic(false);
        font.setWeight(9);
        font.setStrikeOut(false);
        laSystemName->setFont(font);
        laSystemName->setStyleSheet(QString::fromUtf8("font: 75 28pt \"\345\276\256\350\275\257\351\233\205\351\273\221\";"));
        laSystemName->setAlignment(Qt::AlignCenter);
        laSystemName->setWordWrap(true);
        laSystemName->setMargin(5);
        frameLogin = new QFrame(frameLoad);
        frameLogin->setObjectName(QString::fromUtf8("frameLogin"));
        frameLogin->setGeometry(QRect(5, 110, 401, 161));
        frameLogin->setFrameShape(QFrame::StyledPanel);
        frameLogin->setFrameShadow(QFrame::Raised);
        btnCancel = new QPushButton(frameLogin);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));
        btnCancel->setGeometry(QRect(215, 110, 110, 34));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Microsoft YaHei UI"));
        font1.setPointSize(9);
        font1.setBold(false);
        font1.setItalic(false);
        font1.setWeight(50);
        btnCancel->setFont(font1);
        btnCancel->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";"));
        labPwd = new QLabel(frameLogin);
        labPwd->setObjectName(QString::fromUtf8("labPwd"));
        labPwd->setGeometry(QRect(26, 70, 61, 16));
        QFont font2;
        font2.setFamily(QString::fromUtf8("\345\276\256\350\275\257\351\233\205\351\273\221"));
        font2.setBold(false);
        font2.setWeight(50);
        labPwd->setFont(font2);
        labPwd->setStyleSheet(QString::fromUtf8(""));
        btnOk = new QPushButton(frameLogin);
        btnOk->setObjectName(QString::fromUtf8("btnOk"));
        btnOk->setGeometry(QRect(92, 110, 110, 34));
        btnOk->setFont(font1);
        btnOk->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";"));
        txtUser = new QLineEdit(frameLogin);
        txtUser->setObjectName(QString::fromUtf8("txtUser"));
        txtUser->setGeometry(QRect(93, 14, 231, 31));
        txtUser->setFont(font1);
        txtUser->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";"));
        txtPwd = new QLineEdit(frameLogin);
        txtPwd->setObjectName(QString::fromUtf8("txtPwd"));
        txtPwd->setGeometry(QRect(93, 63, 231, 31));
        txtPwd->setFont(font1);
        txtPwd->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";"));
        labUsr = new QLabel(frameLogin);
        labUsr->setObjectName(QString::fromUtf8("labUsr"));
        labUsr->setGeometry(QRect(26, 20, 61, 16));
        labUsr->setFont(font2);
        labUsr->setStyleSheet(QString::fromUtf8(""));
        labInfoPrefix_2 = new QLabel(formLoading);
        labInfoPrefix_2->setObjectName(QString::fromUtf8("labInfoPrefix_2"));
        labInfoPrefix_2->setEnabled(true);
        labInfoPrefix_2->setGeometry(QRect(50, 424, 201, 20));
        labInfoPrefix_2->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";\n"
"color: rgb(104, 104, 104);"));
        labCoreVersion = new QLabel(formLoading);
        labCoreVersion->setObjectName(QString::fromUtf8("labCoreVersion"));
        labCoreVersion->setEnabled(true);
        labCoreVersion->setGeometry(QRect(50, 4, 150, 20));
        labCoreVersion->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";\n"
"color: rgb(104, 104, 104);"));
        labViewVersion = new QLabel(formLoading);
        labViewVersion->setObjectName(QString::fromUtf8("labViewVersion"));
        labViewVersion->setEnabled(true);
        labViewVersion->setGeometry(QRect(450, 425, 150, 20));
        labViewVersion->setStyleSheet(QString::fromUtf8("font: 9pt \"Microsoft YaHei UI\";\n"
"color: rgb(104, 104, 104);"));
        labelBackgroud = new QLabel(formLoading);
        labelBackgroud->setObjectName(QString::fromUtf8("labelBackgroud"));
        labelBackgroud->setGeometry(QRect(0, 0, 611, 451));
        labelBackgroud->setStyleSheet(QString::fromUtf8("border-image: url(:/bin/Image/gbLoad.jpg);"));
        lb_LoadingInfo = new QLabel(formLoading);
        lb_LoadingInfo->setObjectName(QString::fromUtf8("lb_LoadingInfo"));
        lb_LoadingInfo->setGeometry(QRect(173, 375, 430, 51));
        lb_LoadingInfo->setAlignment(Qt::AlignCenter);
        lb_LoadingInfo->setWordWrap(true);
        labelBackgroud->raise();
        frameLoad->raise();
        labInfoPrefix_2->raise();
        labCoreVersion->raise();
        labViewVersion->raise();
        lb_LoadingInfo->raise();

        retranslateUi(formLoading);

        QMetaObject::connectSlotsByName(formLoading);
    } // setupUi

    void retranslateUi(QDialog *formLoading)
    {
        formLoading->setWindowTitle(QCoreApplication::translate("formLoading", "\347\231\273\345\275\225", nullptr));
        laSystemName->setText(QCoreApplication::translate("formLoading", "QCPF Framework", nullptr));
        btnCancel->setText(QCoreApplication::translate("formLoading", "Cancel", nullptr));
        labPwd->setText(QCoreApplication::translate("formLoading", "Password:", nullptr));
        btnOk->setText(QCoreApplication::translate("formLoading", "Load", nullptr));
        txtUser->setText(QString());
        txtPwd->setText(QString());
        labUsr->setText(QCoreApplication::translate("formLoading", "User:", nullptr));
        labInfoPrefix_2->setText(QCoreApplication::translate("formLoading", "Copyright \302\251 Jamie.T", nullptr));
        labCoreVersion->setText(QCoreApplication::translate("formLoading", "Core Verson:", nullptr));
        labViewVersion->setText(QCoreApplication::translate("formLoading", "View Verson:", nullptr));
        labelBackgroud->setText(QString());
        lb_LoadingInfo->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class formLoading: public Ui_formLoading {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FORMLOADING_H
