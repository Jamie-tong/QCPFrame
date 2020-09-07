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

class PluginInterface;

enum InfoType
{
    INFT_INITIALIZE_FINISHED,

    INFT_MSG_INFO,
    INFT_MSG_WARN,
    INFT_MSG_ERROR,
    INFT_MSG_QUESTION,

    INFT_STATUS_INFO,
    INFT_APPLICATION_CLOSE,

    INFT_WRITE_LOG,

    INFT_UI_UPDATE,

    INFT_PLUGIN_BROADCAST,//表示组件发起了事件广播，广播内容见参数
    INFT_PLUGIN_SPECIAL,//表示组件向另一个指定组件发送消息，消息内容见参数
};

enum AuthorityType
    {
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
    PT_SYS,//系统组件，用于升级框架本身
    PT_NON_SYS,//非系统组件，用于实现或升级业务模块
};

enum WidgetShowType
{
        ST_NONE,
        ST_POPUP,
        ST_DOCK
};

struct tagOutputInfo
{
public:
    InfoType _type;
    QString _title;
    QString _content;
    tagOutputInfo(){}
    tagOutputInfo(InfoType type, QString title, QString content){ _type=type;_title=title;_content=content;}
};

struct PluginFunctionInfo
{
    public:
        QString _functonName;
        QString _functionDetail;

        void (*pFunction)(bool);//函数指针指向组件函数
};

struct PluginWidgetInfo
{
    public:
            WidgetShowType _showType;
            int _origWidth;
            int _origHeight;
            QWidget *_widget;
            QString _widgetDetail;
            PluginWidgetInfo(){}
};

class PluginInterface:public QObject
{
        Q_OBJECT
public:
    QString I_PluginID;//组件ID，该属性是组件间唯一的
    PluginType I_PluginType;//组件类型，系统组件或非系统组件
    QString I_PluginAliasName;//组件别名
    QString I_PluginVersion;//组件版本
    QString I_PluginAuther;//组件开发者
    QString I_PluginComment;//组件功能说明
    QString I_PluginFilePath;//组件路径
    QVariant I_PluginTag;//组件类型,用于区别业务类型或者结构类型
    AuthorityType I_PluginAuthority;//组件的访问权限

    bool I_IsCopy;//我是谁？我是不是一个克隆体?
    QString I_CopyID;//副本ID，该属性是副本间唯一的
    QString I_CopyAliasName;//副本别名
    QString I_CopyComment;//副本功能说明

    QVariant I_PluginVar;//通用组件变量
    QVector<QVariant> I_PluginVarList;//通用组件变量集合
    QList<PluginFunctionInfo*> I_FunctionList;//通用组件Function集合
    QVector<PluginWidgetInfo*> I_WidgetList;//通用组件部件集合

public:
    virtual PluginInterface* Clone(QString copyID, QString copyAliasName, QString copyComment) {return nullptr;}
    virtual bool ConnectCore(QObject* core) { return true; }
    virtual bool ConnectViewModel(QObject* view) { return true; }
    virtual int PluginFunction(QVariant arg_in, QVariant &arg_out) { return 0; }
signals:
    int sig_Plugin(QVariant arg_in, QVariant &arg_out);
    int sig_OutputInfo(tagOutputInfo& info);
public slots:
    virtual int slot_Plugin(QVariant arg_in, QVariant &arg_out) { return 0; }
    virtual void slot_Action(bool checkState) { }
    //当core初始化时要执行的过程
    virtual int OnCoreInitialize() { return 0; }
    //当viewModel初始化时要执行的过程
    virtual int OnViewModelInitialize() { return 0; }
    //当view视图构造完成后，Load前要执行的过程
    virtual int OnViewCreated() { return 0; }
    //当view视图Load时要执行的过程
    virtual int OnViewLoaded() { return 0; }
    //当view视图Closeing时要执行的过程
    virtual int OnViewClosing() { return 0; }
};

//这个宏将一个给定的字符串标识符和ClassName所表示的接口相关联，其中Identifier必须唯一。
#define PluginInterface_iid "io.qt.interface.pluginInterface"
Q_DECLARE_INTERFACE(PluginInterface, PluginInterface_iid)

#endif // PLUGININTERFACE_H
