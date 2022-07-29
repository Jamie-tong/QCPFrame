#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <QObject>
#include "qcpf_model.h"
class QCPF_Controllor: public QObject
{
    Q_OBJECT
public:
    QCPF_Controllor();

private:
    QCPF_Model* _core;
public:
    void GetCoreInfo(QString& systemName, QString& systemID, QString& systemVersion, QString& organizetionName);
    void PluginCollect();
    void GetPluginIDList();
    void GetFunctionListFromPlugin(QString pluginID);
    void PerformFunction(QString pluginID, QString copyID, QString functionName);
public slots:
    int slot_CoreInfo(tagOutputInfo& info);
};

#endif // COMMANDHANDLER_H
