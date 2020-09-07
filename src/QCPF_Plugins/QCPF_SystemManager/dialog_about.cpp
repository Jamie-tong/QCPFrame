/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "dialog_about.h"
#include "ui_dialog_about.h"

Dialog_About::Dialog_About(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog_About)
{
    ui->setupUi(this);

    //去掉问号按钮
    setWindowFlags(Qt::Dialog
                   | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);

    //禁止调整大小
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(hasHeightForWidth());
    setSizePolicy(sizePolicy);
    setMinimumSize(QSize(560, 300));
    setMaximumSize(QSize(560, 300));
    setSizeGripEnabled(false);

}

Dialog_About::~Dialog_About()
{
    delete ui;
}

void Dialog_About::on_btnClose_clicked()
{
    this->close();
}
