﻿/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "formloading.h"
#include "qcpf_model.h"
#include "qcpf_viewmodel.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    QCPF_Model *_core;
    QCPF_ViewModel* _view;

private slots:
    void on_loading_cancel();
    void on_MainWindow_destroyed();

protected:
    void resizeEvent(QResizeEvent *event);
    void closeEvent ( QCloseEvent * e );
private:
    Ui::MainWindow *ui;
    QList<QDockWidget*> m_docks;
    bool _isFirstResize;
    void writeSettings();
    void readSettings();
    InitThread* initTd;
};

#endif // MAINWINDOW_H
