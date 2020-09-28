#include <QCoreApplication>
#include <QCommandLineOption>
#include <QCommandLineParser>

#include "QCPF_Controllor.h"
#include <QDebug>

#include <iostream>
#include "QTextStream"
using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication app(argc, argv);

    cout<<"Welcome to QCPFrame，it's a Qt-based plugin framework which complies with the GPL3.0 protocol.\n"<<endl;

    QCPF_Controllor* _controllor = new QCPF_Controllor();

    QString sysName;
    QString sysID;
    QString sysVersion;
    QString organizationName;
    _controllor->GetCoreInfo(sysName, sysID, sysVersion, organizationName);

    QCoreApplication::setApplicationName(sysName);
    QCoreApplication::setOrganizationName(organizationName);
    QCoreApplication::setApplicationVersion(sysVersion);

    QCommandLineOption op_PSysInfo("PSysInfo", "get system info");// 长名称，无参数
    QCommandLineOption op_PLst("PLst", "get plugins form plugin dir");// 长名称，无参数
    QCommandLineOption op_PFuncLst("PFLst", "get the function list of plugin.", "Plugin ID");// 长名称，无参数
    QCommandLineOption op_PFunc("PFunc", "Run the function from plugin function list.", "Plugin ID, Copy ID, Function Name");// 长名称，无参数

    QCommandLineParser parser;

    parser.addOption(op_PSysInfo);
    parser.addOption(op_PLst);
    parser.addOption(op_PFuncLst);
    parser.addOption(op_PFunc);

    parser.process(app);

    qDebug() <<  parser.helpText()<<endl;

    if(parser.isSet(op_PSysInfo))
    {
        _controllor->GetCoreInfo(sysName, sysID, sysVersion, organizationName);
    }

    if(parser.isSet(op_PLst))
    {
        _controllor->GetPluginIDList();
    }

    if(parser.isSet(op_PFuncLst))
    {
        _controllor->GetFunctionListFromPlugin(parser.value(op_PFuncLst));
    }

    if(parser.isSet(op_PFunc))
    {
        QStringList paramLst =  parser.values(op_PFunc);
        if(paramLst.length()>=2)
        {
            if(paramLst.length()==2)
                _controllor->PerformFunction(paramLst[0], "", paramLst[1]);
            if(paramLst.length()==3)
                _controllor->PerformFunction(paramLst[0], paramLst[1], paramLst[2]);
        }
    }

    return app.exec();
}
