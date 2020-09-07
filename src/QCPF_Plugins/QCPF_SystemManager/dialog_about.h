/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef DIALOG_ABOUT_H
#define DIALOG_ABOUT_H

#include <QDialog>

namespace Ui {
class Dialog_About;
}

class Dialog_About : public QDialog
{
    Q_OBJECT

public:
    explicit Dialog_About(QWidget *parent = nullptr);
    ~Dialog_About();

private slots:
    void on_btnClose_clicked();

private:
    Ui::Dialog_About *ui;
};

#endif // DIALOG_ABOUT_H
