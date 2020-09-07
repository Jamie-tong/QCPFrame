#ifndef QCFVIEWMODEL_H
#define QCFVIEWMODEL_H

#include <QObject>

#if defined(QCFVIEWMODEL_LIBRARY)
#  define QCFVIEWMODEL_EXPORT Q_DECL_EXPORT
#else
#  define QCFVIEWMODEL_EXPORT Q_DECL_IMPORT
#endif

#include "viewConfigModel.h"
#include <QMenuBar>
#include <QToolBar>
#include <QStatusBar>
#include <QAction>

class QCFModel;
class QCFVIEWMODEL_EXPORT QCFViewModel:public QObject
{
    Q_OBJECT
public:
    QCFViewModel(QObject* parent);
    QCFViewModel(QObject* parent, QString configDirPath, QString configFileName);

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

#endif // QCFVIEWMODEL_H
