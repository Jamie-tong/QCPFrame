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
    QString sysPluginDirPath = appDirPath + "/Bin/Plugin/";
    QString nSyspluginDirPath = appDirPath + "/Plugin/";

    QString _coreConfigFileDirPath = appDirPath + "/Config/Core/";
    QString _coreConfigFileName = "CoreConfig.dat";

    QString _viewConfigFileDirPath = appDirPath + "/Config/View/";
    QString _viewConfigFileName = "ViewConfig.dat";

    //create core object
    _core = new QCPF_Model(RM_APPLICATION, this, appDirPath, sysPluginDirPath, nSyspluginDirPath, _coreConfigFileDirPath, _coreConfigFileName);
    _view = new QCPF_ViewModel(_core, this, _viewConfigFileDirPath, _viewConfigFileName);

    _core->_view = (QObject*)_view;
    //------------set ui from config model
    setWindowTitle(_core->_config._systemName);

    //用于在_core被构造后就马上与插件进行通讯，执行OnCoreInitialize
    //Load界面启动后，执行slot_Initialize才建立信号槽连接。
    _core->slot_PreInitialize();

    //------------load view
    formLoading *view_load = new formLoading(_view);

    connect(view_load, SIGNAL(sig_DoCoreInitialize(QString, QString, QString)), _core, SLOT(slot_Initialize(QString, QString, QString)));
    connect(view_load, SIGNAL(sig_DoViewModelInitialize(QString, QString, QString)), (QObject*)_view, SLOT(slot_Initialize(QString, QString, QString)));

    connect(_core, SIGNAL(sig_OutputInfo(tagOutputInfo&)), view_load, SLOT(slot_InputInfo(tagOutputInfo&)));
    connect((QObject*)_view, SIGNAL(sig_OutputInfo(tagOutputInfo&)), view_load, SLOT(slot_InputInfo(tagOutputInfo&)));

    connect(_core, SIGNAL(sig_OutputInfo(tagOutputInfo&)), (QObject*)_view, SLOT(slot_InputInfo(tagOutputInfo&)));
    connect((QObject*)_view, SIGNAL(sig_OutputInfo(tagOutputInfo&)), (QObject*)_view, SLOT(slot_InputInfo(tagOutputInfo&)));

    view_load->exec();

    disconnect(view_load, SIGNAL(sig_DoCoreInitialize(QString, QString, QString)), _core, SLOT(slot_Initialize(QString, QString, QString)));
    disconnect(view_load, SIGNAL(sig_DoViewModelInitialize(QString, QString, QString)), (QObject*)_view, SLOT(slot_Initialize(QString, QString, QString)));

    disconnect(_core, SIGNAL(sig_OutputInfo(tagOutputInfo&)), view_load, SLOT(slot_InputInfo(tagOutputInfo&)));
    disconnect((QObject*)_view, SIGNAL(sig_OutputInfo(tagOutputInfo&)), view_load, SLOT(slot_InputInfo(tagOutputInfo&)));

//Test Menu for 1 and release for 0
#if 0
    QMenuBar* tempMenuBar = new QMenuBar(this);
    QMenu* testMenu = new QMenu();
    testMenu->setTitle(tr("Test"));
    testMenu->setObjectName("menuTest");
    foreach (Plugin_Interface* pi, _core->I_SysPlugins) {
            foreach (PluginActionInfo* pfi, pi->I_ActionList) {
                QAction* tSysAction = new QAction(testMenu);
                tSysAction->setObjectName(pfi->_actionName);
                tSysAction->setText(pfi->_actionName);
                connect(tSysAction, &QAction::triggered, pi, &Plugin_Interface::slot_Action);
                testMenu->addAction(tSysAction);
            }
        }

    tempMenuBar->addMenu(testMenu);
    this->setMenuBar(tempMenuBar);
#else
    _view->initUIFromConfig(this);

    //invoke plugin functions one by one
    foreach (Plugin_Interface* pi, _core->I_NSysAllValidPlugins) {
        pi->OnViewCreated();
    }
#endif


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
    foreach (Plugin_Interface* pi, _core->I_NSysAllValidPlugins) {
        pi->OnViewClosing();
    }

    //保存界面布局到Layout.ini
    QString _layoutIniFilePath = _core->I_ApplicationDirPath + "/Config/View/.Layout.ini";
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
    foreach (Plugin_Interface* pi, _core->I_NSysAllValidPlugins) {
        pi->OnViewLoaded();
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

void MainWindow::on_MainWindow_destroyed()
{
    if(QMessageBox::Yes == QMessageBox::question(this, tr("information"), QStringLiteral("Are you sure to quit the application?")))
    {
        this->close();
    }
}
