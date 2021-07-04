/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef QCPF_VIEWMODEL_H
#define QCPF_VIEWMODEL_H

#include <QObject>
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>

#include "viewConfigModel.h"
#include "../QCPF_Model/qcpf_model.h"

#if defined(QCPF_VIEWMODEL_LIBRARY)
#  define QCPF_VIEWMODEL_EXPORT Q_DECL_EXPORT
#else
#  define QCPF_VIEWMODEL_EXPORT Q_DECL_IMPORT
#endif

class QCPF_VIEWMODEL_EXPORT QCPF_ViewModel : QObject
{
    Q_OBJECT
    public:
        QCPF_ViewModel(QCPF_Model* Model, QObject* parent);
        QCPF_ViewModel(QCPF_Model* Model, QObject* parent, QString configDirPath, QString configFileName);

        QCPF_Model *_core;
        QString _configDirPath;
        QString _configFileName;
        QString _configFullFilePath;

        tagOutputInfo _outputInfo;
        viewConfigModel _config;
        QList<QAction*> _actionList;
        QString _version;
        QString _organization;

    signals:
        int sig_OutputInfo(tagOutputInfo& info);
    public slots:
        int slot_Initialize();
        int slot_InputInfo(tagOutputInfo& info);
        int slot_LoadConfigFile(viewConfigModel &config);
        int slot_SaveConfigFile();
        int slot_ApplyConfig();
        int slot_CancelConfig();

    public:
        void initUIFromConfig(QMainWindow* viewHost);
        void addActionToViewActionList(QAction* action, QString actionObjectName, QString actionText, QString shortcut, AuthorityType aType, bool isCheckable, QString iconPath, PluginType pType, QString pluginID);
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
        QMainWindow* _viewHost;
};

#endif // QCPF_VIEWMODEL_H
