/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef FORMLOADING_H
#define FORMLOADING_H

#include <QDialog>
#include <QMouseEvent>

#include "qcpf_model.h"
#include "qcpf_viewmodel.h"
#include "initthread.h"

class QPushButton;
class QLineEdit;

namespace Ui {
class formLoading;
}

class formLoading : public QDialog
{
    Q_OBJECT
public:
    explicit formLoading(QCPF_ViewModel* view, QDialog *parent = nullptr);
    ~formLoading();

protected:
    //拖拽窗口
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void showEvent(QShowEvent *);
    bool eventFilter(QObject *target, QEvent *event);

signals:
    int sig_DoCoreInitialize(QString user, QString pwd, QString extInfo);
    int sig_DoViewModelInitialize(QString user, QString pwd, QString extInfo);
    void  sig_Cancel();

private slots:
    void slot_OnULoaded();
    void on_btnOk_clicked();
    void on_btnCancel_clicked();

    void setBtnQss(QPushButton *btn,
                   QString normalColor, QString normalTextColor,
                   QString hoverColor, QString hoverTextColor,
                   QString pressedColor, QString pressedTextColor);
    void setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor);

    int slot_InputInfo(tagOutputInfo& info);


    void on_txtUser_textChanged(const QString &arg1);

    void on_txtPwd_textChanged(const QString &arg1);

private:
    Ui::formLoading *ui;
    QCPF_Model* _core;
    QCPF_ViewModel* _view;

    bool        m_bDrag;
    QPoint      mouseStartPoint;
    QPoint      windowTopLeftPoint;
    QTimer *_timer;
};

#endif // FORMLOADING_H
