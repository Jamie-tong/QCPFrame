/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "mainwindow.h"
#include <QApplication>

#include <QDesktopWidget>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    w.setWindowState(Qt::WindowState::WindowMaximized);

    w.show();

    return a.exec();
}
