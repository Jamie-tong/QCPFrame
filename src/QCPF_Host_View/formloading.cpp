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

#include <QKeyEvent>


#ifdef Q_OS_LINUX
    #include <unistd.h>
#endif
 
#ifdef Q_OS_WIN32
    #include <windows.h>
#endif

#include <QProcess>
#include <QStringLiteral>

#include "mainwindow.h"

struct tagUserInfo{
    QString userName;
    QString password;
};
Q_DECLARE_METATYPE(tagUserInfo)

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

    //注册面板显示后的信号槽
    _timer = new QTimer(this);
    _timer->setSingleShot(true);
    connect(_timer, SIGNAL(timeout()), this, SLOT(slot_OnULoaded()));

    ui->txtUser->installEventFilter(this);//设置完后自动调用其eventFilter函数
    ui->txtPwd->installEventFilter(this);//设置完后自动调用其eventFilter函数
}

formLoading::~formLoading()
{
    delete ui;
}

void formLoading::slot_OnULoaded()
{
    QRect rct_frame = ui->frameLoad->geometry();
    QRect rct_lbLoadingInfo = ui->lb_LoadingInfo->geometry();

    QCoreApplication::processEvents();
    ui->frameLogin->setVisible(false);
    ui->lb_LoadingInfo->setGeometry(rct_frame.x(), rct_frame.y()+rct_frame.height()-rct_lbLoadingInfo.height() - 70, rct_lbLoadingInfo.width(), rct_lbLoadingInfo.height());
    _core->slot_Initialize();

    ui->lb_LoadingInfo->setGeometry(rct_frame.x(), rct_frame.y()+rct_frame.height(), rct_lbLoadingInfo.width(), rct_lbLoadingInfo.height());
    ui->lb_LoadingInfo->clear();
    ui->frameLogin->setVisible(true);
    ui->btnOk->setFocus();
    ui->btnOk->setDefault(true);
    _timer->deleteLater();
}

bool formLoading::eventFilter(QObject *target, QEvent *event)
{
    if(target == ui->txtUser || target ==ui->txtPwd)
        {
            if(event->type() == QEvent::KeyPress)
            {
                 QKeyEvent *k = static_cast<QKeyEvent *>(event);

                 if(k->key() == Qt::Key_Return)//回车键
                 {
                     on_btnOk_clicked();
                     return true;
                 }
            }
        }
        return QWidget::eventFilter(target,event);
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

int formLoading::slot_InputInfo(tagOutputInfo& info)
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

void formLoading::showEvent(QShowEvent *event)
{
    _timer->start(1);
}

void formLoading::on_btnOk_clicked()
{
    if(ui->txtUser->text()=="" || ui->txtPwd->text()=="")
    {
        QMessageBox::information(this, "info", "User Name or Password can not be null!");
        return;
    }

    //通过函数指针调用用户管理组件的验证功能，旨在将用户管理与框架解耦，即有一天用户管理的密码验证要升级为加密形式，只需要更新用户管理模块。
    bool isVerifyLoginInfoExisted = false;
    bool isLegal = false;

    QVariant var_In;
    QVariant var_Out;
    tagUserInfo uInfo;
    uInfo.userName = ui->txtUser->text();
    uInfo.password = ui->txtPwd->text();
    var_In = QVariant::fromValue(uInfo);

    int ret =_core->Invoke_PluginFunction(PT_SYS,  "QCPF_UserManager", "VerifyLoginInfo", var_In, var_Out);

    //-1表示没找到组件, -2表示没找到函数指针对象
    if(ret==-1 || ret ==-2)
    {
        this->close();
    }
    bool verityEnd = var_Out.value<bool>();
    if(!verityEnd)
    {
        ui->lb_LoadingInfo->setText("Invalid username and password!");
    }
    else
        this->close();
}

void formLoading::on_txtUser_textChanged(const QString &arg1)
{
    ui->lb_LoadingInfo->setText("");
}

void formLoading::on_txtPwd_textChanged(const QString &arg1)
{
    ui->lb_LoadingInfo->setText("");
}
