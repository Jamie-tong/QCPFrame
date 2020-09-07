/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef QCPF_VIEWMODEL_H
#define QCPF_VIEWMODEL_H

#include <QObject>
#include "viewConfigModel.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>

#if defined(QCPF_VIEWMODEL_LIBRARY)
#  define QCPF_VIEWMODEL_EXPORT Q_DECL_EXPORT
#else
#  define QCPF_VIEWMODEL_EXPORT Q_DECL_IMPORT
#endif

class QCPF_VIEWMODEL_EXPORT QCPF_ViewModel : QObject
{
    Q_OBJECT
    public:
        QCPF_ViewModel(QObject* parent);
        QCPF_ViewModel(QObject* parent, QString configDirPath, QString configFileName);

        QString _configDirPath;
        QString _configFileName;
        QString _configFullFilePath;

        QObject *_core;
        tagOutputInfo _outputInfo;
        viewConfigModel _config;
        QList<QAction*> _actionList;

    signals:
        int sig_OutputInfo(tagOutputInfo& info);//向槽函数发送初始化信息
    public slots:
        int slot_Initialize(QString user, QString pwd, QString extInfo);
        int slot_LoadConfigFile(viewConfigModel &config);
        int slot_SaveConfigFile();
        int slot_ApplyConfig();
        int slot_CancelConfig();

    public:
        void InitUIFromConfig(QMainWindow* viewHost);

    private:
        int compareFiles(QString filePath1, QString filePath2);
        int saveConfigFile(QString filePath);
        void parseMenu(QMenu* nMenu, JMenuNode* nNode);

        void drawMenuFromConfig(QMenuBar* mainMenu);
        void drawToolBarFromConfig(QList<QToolBar*> mainToolbarLst);
        void drawStatusBarFromConfig(QStatusBar* mainStatusbar);
        void removeWidgetsFromStatusBar(QStatusBar* mainStatusbar);
        void drawDockWidgetFromConfig(QMainWindow* viewHost);
        QList<QWidget*> _widgetLst_Statusbar;
        bool isFirst = true;

        QMenuBar* _mainMenubar;
        QList<QToolBar*> _mainToolbarLst;
        QStatusBar* _mainStatusbar;
};

#endif // QCPF_VIEWMODEL_H
