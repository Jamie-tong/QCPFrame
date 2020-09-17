/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "formloading.h"
#include "ui_formloading.h"
#include <QDialog>
#include <QStringLiteral>
#include <QMessageBox>
#include <QTimer>
#include <QString>

#include <windows.h>//在Linux和Mac下要换成 unistd.h 头文件
#include <QProcess>
#include <QStringLiteral>

#include "mainwindow.h"

formLoading::formLoading(QCPF_ViewModel* view, QDialog *parent) :
    QDialog(parent),
    ui(new Ui::formLoading)
{
    ui->setupUi(this);
    _view = view;
    _core = view->_core;

    setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowStaysOnTopHint|Qt::Tool|Qt::X11BypassWindowManagerHint);

    //this->setWindowOpacity(0.9);

    setTxtQss(ui->txtUser, "#DCE4EC", "#34495E");
    setTxtQss(ui->txtPwd, "#DCE4EC", "#34495E");
    setBtnQss(ui->btnOk, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");
    setBtnQss(ui->btnCancel, "#34495E", "#FFFFFF", "#4E6D8C", "#F0F0F0", "#2D3E50", "#B8C6D1");

     //------------set ui from config model
    QString tSysName = _core->_config._systemName;
    ui->laSystemName->setText(tSysName);
    ui->labCoreVersion->setText(QString(tr("Core Version : %1")).arg(_core->I_SystemVersion));
    ui->labViewVersion->setText(QString(tr("View Version : %1")).arg(_view->_version));
}

formLoading::~formLoading()
{
    delete ui;
}

void formLoading::timerUpdate()
{
    QString tUser = ui->txtUser->text();
    QString tPwd = ui->txtPwd->text();
    QString tExtInfo = "";
    //先初始化core，再初始化viewmodel
    if(0!=_core->slot_Initialize(tUser, tPwd, tExtInfo))
    {
        timer->stop();
        timer->deleteLater();
        return;
    }

    _view->slot_Initialize();

    timer->stop();
    timer->deleteLater();
}

void formLoading::on_btnCancel_clicked()
{
    QString cmd;

    #ifndef WIN32
        int pidLinux = 0;
        cmd = QString("kill -9 %1").arg(pidLinux);
        system(cmd.toLocal8Bit().data());
    #else
        DWORD pidwin = GetCurrentProcessId(); // 当前进程ID
        cmd = QString("TASKKILL /PID %1 /T /F").arg(pidwin);
        system(cmd.toLocal8Bit().data());
    #endif
    emit sig_Cancel();
}

void formLoading::setBtnQss(QPushButton *btn,
                        QString normalColor, QString normalTextColor,
                        QString hoverColor, QString hoverTextColor,
                        QString pressedColor, QString pressedTextColor)
{
    QStringList qss;
    qss.append(QString("QPushButton{border-style:none;padding:10px;border-radius:5px;color:%1;background:%2;}").arg(normalTextColor).arg(normalColor));
    qss.append(QString("QPushButton:hover{color:%1;background:%2;}").arg(hoverTextColor).arg(hoverColor));
    qss.append(QString("QPushButton:pressed{color:%1;background:%2;}").arg(pressedTextColor).arg(pressedColor));
    btn->setStyleSheet(qss.join(""));
}

void formLoading::setTxtQss(QLineEdit *txt, QString normalColor, QString focusColor)
{
    QStringList qss;
    qss.append(QString("QLineEdit{border-style:none;padding:6px;border-radius:5px;border:2px solid %1;}").arg(normalColor));
    qss.append(QString("QLineEdit:focus{border:2px solid %1;}").arg(focusColor));
    txt->setStyleSheet(qss.join(""));
}

//拖拽操作
void formLoading::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = true;
        //获得鼠标的初始位置
        mouseStartPoint = event->globalPos();
        //mouseStartPoint = event->pos();
        //获得窗口的初始位置
        windowTopLeftPoint = this->frameGeometry().topLeft();
    }
}

void formLoading::mouseMoveEvent(QMouseEvent *event)
{
    if(m_bDrag)
    {
        //获得鼠标移动的距离
        QPoint distance = event->globalPos() - mouseStartPoint;
        //QPoint distance = event->pos() - mouseStartPoint;
        //改变窗口的位置
        this->move(windowTopLeftPoint + distance);
    }
}

void formLoading::mouseReleaseEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_bDrag = false;
    }
}

int formLoading::slot_CoreInitializeInfo(tagOutputInfo& info)
{
    switch (info._type) {

        case InfoType::INFT_MSG_INFO:
                QMessageBox::information(this, info._title, info._content);
                return -1;
        break;
        case InfoType::INFT_STATUS_INFO:
                ui->lb_LoadingInfo->setText(info._content);
                ui->lb_LoadingInfo->repaint();
                QThread::msleep(300);
        break;
        case InfoType::INFT_INITIALIZE_FINISHED:
            QThread::sleep(1);
            this->close();
            break;
    }

   return 0;
}

void formLoading::on_btnOk_clicked()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(timerUpdate()));

    timer->start(100);
}
