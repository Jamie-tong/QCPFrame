/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QMessageBox>
#include <QDockWidget>
#include <QTextEdit>
#include <QStringLiteral>
#include <QSettings>

#include "../../interface/plugininterface.h"
#include "../QCPF_Model/qcpf_model.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //delete centry widget
    QWidget* p = takeCentralWidget();
    if(p)
        delete p;
    //allow dock
    setDockNestingEnabled(true);

    QString appDirPath = QCoreApplication::applicationDirPath();
    QString sysPluginDirPath = appDirPath + "/Bin/Plugins/";
    QString nSyspluginDirPath = appDirPath + "/Plugins/";

    QString _coreConfigFileDirPath = appDirPath + "/Config/Core/";
    QString _coreConfigFileName = "CoreConfig.dat";

    QString _viewConfigFileDirPath = appDirPath + "/Config/View/";
    QString _viewConfigFileName = "ViewConfig.dat";

    //create core object
    _view = new QCPF_ViewModel(this, _viewConfigFileDirPath, _viewConfigFileName);
    _core = new QCPF_Model(this, appDirPath, sysPluginDirPath, nSyspluginDirPath, _coreConfigFileDirPath, _coreConfigFileName);

    _view->_core = this->_core;
    //------------set ui from config model
    setWindowTitle(_core->_config._systemName);

    //------------load view
    formLoading *view_load = new formLoading(_core);

    connect(view_load, SIGNAL(sig_DoCoreInitialize(QString, QString, QString)), _core, SLOT(slot_Initialize(QString, QString, QString)));
    connect(view_load, SIGNAL(sig_DoViewModelInitialize(QString, QString, QString)), (QObject*)_view, SLOT(slot_Initialize(QString, QString, QString)));
    connect(_core, SIGNAL(sig_OutputInfo(tagOutputInfo&)), view_load, SLOT(slot_CoreInitializeInfo(tagOutputInfo&)));
    connect((QObject*)_view, SIGNAL(sig_OutputInfo(tagOutputInfo&)), view_load, SLOT(slot_CoreInitializeInfo(tagOutputInfo&)));
    connect(_core, SIGNAL(sig_OutputInfo(tagOutputInfo&)), this, SLOT(slot_CoreInfo(tagOutputInfo&)));
    connect((QObject*)_view, SIGNAL(sig_OutputInfo(tagOutputInfo&)), this, SLOT(slot_CoreInfo(tagOutputInfo&)));

    view_load->exec();

    foreach (PluginInterface* pi, _core->I_SysPlugins_Sel) {
        connect(pi, SIGNAL(sig_OutputInfo(tagOutputInfo&)), this, SLOT(slot_CoreInfo(tagOutputInfo&)));
    }
    foreach (PluginInterface* npi, _core->I_NSysOrigPlugins_Sel) {
        connect(npi, SIGNAL(sig_OutputInfo(tagOutputInfo&)), this, SLOT(slot_CoreInfo(tagOutputInfo&)));
    }

#if 0
    QMenuBar* tempMenuBar = new QMenuBar(this);
    QMenu* testMenu = new QMenu();
    testMenu->setTitle(tr("Test"));
    testMenu->setObjectName("menuTest");
    foreach (PluginInterface* pi, _core->I_SysPlugins) {
            foreach (PluginFunctionInfo* pfi, pi->I_FunctionList) {
                QAction* tSysAction = new QAction(testMenu);
                tSysAction->setObjectName(pfi->_functonName);
                tSysAction->setText(pfi->_functonName);
                connect(tSysAction, &QAction::triggered, pi, &PluginInterface::slot_Action);
                testMenu->addAction(tSysAction);
            }
        }

    tempMenuBar->addMenu(testMenu);
    this->setMenuBar(tempMenuBar);
#else
    //从视图配置文件导入UI配置
    _view->InitUIFromConfig(this);
#endif

    //invoke plugin functions one by one
    foreach (PluginInterface* pi, _core->I_NSysAllValidPlugins) {
        pi->OnViewCreated();
    }

    //设置docker分割线样式
    setStyleSheet("QMainWindow::separator{background:gray; width:1px; height:1px;}");

    //从Layout.ini恢复界面布局
    _layoutIniFilePath = appDirPath + "/Config/View/.Layout.ini";
    QFile file(_layoutIniFilePath);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray ba;
        QDataStream in(&file);
        in >> ba;
        file.close();
        this->restoreState(ba);
    }
}

void MainWindow::writeSettings()
{
QSettings settings("Software Inc.","Icon Editor");
settings.beginGroup("mainWindow");
settings.setValue("size", size());
settings.setValue("state", saveState());
settings.endGroup();
}

void MainWindow::readSettings()
{
QSettings settings("Software Inc.","Icon Editor");
settings.beginGroup("mainWindow");
resize(settings.value("size").toSize());
restoreState(settings.value("state").toByteArray());
settings.endGroup();
}

MainWindow::~MainWindow()
{
    //invoke plugin functions one by one
    foreach (PluginInterface* pi, _core->I_NSysAllValidPlugins) {
        pi->OnViewClosing();
    }

    //保存界面布局到Layout.ini
    QFile file(_layoutIniFilePath);
    if (file.open(QIODevice::WriteOnly))
    {
        QDataStream out(&file);
        out << this->saveState();
        file.close();
    }
    writeSettings();

    delete _core;
    delete ui;
}

void MainWindow::resizeEvent(QResizeEvent *event)
{
    //如果不是第一次显示
    if(!_isFirstResize)
        return;
    else
        _isFirstResize = false;

    //invoke plugin functions one by one
    foreach (PluginInterface* pi, _core->I_NSysAllValidPlugins) {
        pi->OnViewLoaded();
    }

    QFile file(_layoutIniFilePath);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray ba;
        QDataStream in(&file);
        in >> ba;
        file.close();
        this->restoreState(ba);

    }
}

void MainWindow::on_loading_cancel()
{
    this->close();
}

void MainWindow::closeEvent ( QCloseEvent * e )
{
    if( QMessageBox::question(this,
                             tr("Quit"),
                             tr("Are you sure to quit this application?"),
                              QMessageBox::Yes, QMessageBox::No )
                   == QMessageBox::Yes){
        e->accept();//不会将事件传递给组件的父组件
    }
    else
      e->ignore();
}

int MainWindow::slot_CoreInfo(tagOutputInfo& info)
{
    switch (info._type) {
        case InfoType::INFT_MSG_INFO:
                QMessageBox::information(this, info._title, info._content);
                break;
        case InfoType::INFT_MSG_WARN:
                QMessageBox::warning(this, info._title, info._content);
                break;
        case InfoType::INFT_MSG_ERROR:
                QMessageBox::critical(this, info._title, info._content);
                break;
        case InfoType::INFT_MSG_QUESTION:
                QMessageBox::question(this, info._title, info._content);
                break;
        case InfoType::INFT_APPLICATION_CLOSE:
                this->close();
                break;
        case InfoType::INFT_UI_UPDATE:
                _view->InitUIFromConfig(this);
            break;
    }
    return 0;
}

void MainWindow::on_MainWindow_destroyed()
{
    if(QMessageBox::Yes == QMessageBox::question(this, tr("information"), QStringLiteral("Are you sure to quit the application?")))
    {
        this->close();
    }
}
