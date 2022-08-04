/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef PLUGININTERFACE_H
#define PLUGININTERFACE_H

#include <QString>
#include <QObject>
#include <QVector>
#include <QVariant>
#include <QIcon>
#include <QPluginLoader>
#include <QTranslator>

class Plugin_Interface;

enum InfoType
{
    INFT_INITIALIZE_FINISHED,

    INFT_MSG_INFO,
    INFT_MSG_WARN,
    INFT_MSG_ERROR,
    INFT_MSG_QUESTION,

    INFT_STATUS_INFO,

    INFT_APPLICATION_CLOSE,
    INFT_APPLICATION_READ_SETTINGS,
    INFT_APPLICATION_WRITE_SETTINGS,
    INFT_APPLICATION_REFRESH,
    INFT_APPLICATION_ID_CHANGED,
    INFT_APPLICATION_TITLE_CHANGED,

    INFT_PLUGIN_COLLECT,
    INFT_PLUGIN_COLLECT_FINISHED,

    INFT_CORE_CONFIG_CHANGED,
    INFT_VIEW_CONFIG_CHANGED,

    INFT_PLUGIN_BROADCAST,
    INFT_PLUGIN_SPECIAL,

    INFT_STATUSBAR_TEMP,

    INFT_EXT_BASE,
};

enum AuthorityType
    {
        AT_ORIGINATOR,

        AT_DEVELOPER1,
        AT_DEVELOPER2,
        AT_DEVELOPER3,

        AT_MANAGER1,
        AT_MANAGER2,
        AT_MANAGER3,

        AT_USER1,
        AT_USER2,
        AT_USER3,

        AT_GUEST,
    };

enum PluginType
{
    PT_SYS,
    PT_NON_SYS,
};

enum WidgetShowType
{
        ST_NONE,
        ST_WIDGET,
        ST_POPUP,
        ST_DOCK,
};

struct tagOutputInfo
{
public:
    InfoType _type;
    QString _title;
    QString _content;
    int _timeout;
    tagOutputInfo(){}
    tagOutputInfo(InfoType type, QString title, QString content){ _type=type;_title=title;_content=content;}
    tagOutputInfo(InfoType type, QString title, QString content, int timeout){ _type=type;_title=title;_content=content; _timeout=timeout;}
};

typedef int (*FPTR_FUNC_NCLS)(QVariant arg_in, QVariant &arg_out);
typedef int (Plugin_Interface::*FPTR_FUNC_CLS)(QVariant arg_in, QVariant &arg_out);
typedef void (Plugin_Interface::*FPTR_ACTION)(bool);
typedef void (Plugin_Interface::*FPTR_TRANSLATE)(void);
struct PluginActionInfo
{
    public:
        QString _actionName;
        QString _actionDetail;
        QIcon _actionIcon;
        FPTR_ACTION _pAction;
};

struct PluginFunctionInfo
{
    public:
        QString _functionName;
        QString _functionDetail;

        FPTR_FUNC_CLS _pFunction;
};

struct PluginWidgetInfo
{
    public:
            WidgetShowType _showType = ST_DOCK;
            int _origWidth;
            int _origHeight;
            QWidget *_widget;
            QString _widgetDetail;
            PluginWidgetInfo(){}
};

class Plugin_Interface:public QObject
{
        Q_OBJECT
public:
    QString I_PluginID;
    PluginType I_PluginType;
    QString I_PluginAliasName;
    QString I_PluginVersion;
    QString I_PluginAuther;
    QString I_PluginComment;
    QString I_PluginFilePath;
    QVariant I_PluginTag;
    AuthorityType I_PluginAuthority;
    bool I_IsEnable;

    bool I_IsCopy;
    QString I_CopyID;
    QString I_CopyAliasName;
    QString I_CopyComment;

    QVariant I_PluginVar;
    QList<QVariant> I_PluginVarList;
    QList<PluginActionInfo*> I_ActionList;
    QList<PluginFunctionInfo*> I_FunctionList;
    QVector<PluginWidgetInfo*> I_WidgetList;
    QTranslator* I_Translator;

public:
    virtual Plugin_Interface* Clone(QString copyID, QString copyAliasName, QString copyComment) {return nullptr;}
    virtual bool ConnectCore(QObject* core) { return true; }
    virtual int PluginFunction(QVariant arg_in, QVariant &arg_out) { return 0; }
    virtual void InitActionList(Plugin_Interface* plugin){};
    virtual void InitFunctionList(Plugin_Interface* plugin){};
    virtual void InitWidgetList(Plugin_Interface* plugin){};

signals:
    int sig_OutputInfo(tagOutputInfo& info);
    int sig_Plugin(QVariant arg_in, QVariant &arg_out);

public slots:
    virtual int slot_InputInfo(tagOutputInfo& info) { return 0; }
    virtual int slot_Plugin(QVariant arg_in, QVariant &arg_out) { return 0; }
    virtual void slot_Action(bool checkState) { }

    virtual int OnCoreInitialize() { return 0; }

    virtual int OnViewCreated() { return 0; }

    virtual int OnViewLoaded() { return 0; }

    virtual int OnViewClosing() { return 0; }
};

#define Plugin_Interface_iid "io.qt.interface.plugin_interface"
Q_DECLARE_INTERFACE(Plugin_Interface, Plugin_Interface_iid)

#endif 
