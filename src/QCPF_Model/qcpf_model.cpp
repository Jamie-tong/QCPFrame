/*
Author       : Jamie.Tong
QQ           : 260271262
Data From    : 2020-09-07
License      : GPL v3.0
*/

#include "qcpf_model.h"

#include <QDataStream>
#include <QStringLiteral>
#include <QMap>
#include <QWidget>
#include <QCoreApplication>
#include <QString>

#define MASK_END_STR "_tp"
#define SYSTEM_VERSION "2.0.0.4"
#define ORGANIZATION_NAME "Jamie.T"

QCPF_Model::QCPF_Model(RunMode runMode, QObject* parent):_config(this)
{
    I_RunMode = runMode;
    I_SystemVersion = SYSTEM_VERSION;
    I_OrganizationName = ORGANIZATION_NAME;
    this->setParent(parent);

    slot_LoadConfigFile(_config);
    I_SystemName = _config._systemName;
    I_SystemID = _config._systemID;
    I_EnableLogin = _config._enableLogin;

    if(!I_EnableLogin)
    {
        I_CurrentUserInfo._userName = "defaultUser";
        I_CurrentUserInfo._password = "";
        I_CurrentUserInfo._detail = "Non-login user.";
        I_CurrentUserInfo._authority = AT_MANAGER1;
        I_CurrentUserInfo._createDatetime = "";
    }
}

QCPF_Model::QCPF_Model(RunMode runMode, QObject* parent, QString applicationDirPath, QString sysPluginDirPath, QString nSysPluginDirPath, QString configDirPath, QString configFileName):_config(this)
{
    I_RunMode = runMode;
    I_SystemVersion = SYSTEM_VERSION;
    I_OrganizationName = ORGANIZATION_NAME;
    this->setParent(parent);

    I_ApplicationDirPath = applicationDirPath;
    I_SystemPluginDirPath = sysPluginDirPath;
    I_NonSysPluginDirPath = nSysPluginDirPath;
    I_ConfigDirPath = configDirPath;
    I_ConfigFileName = configFileName;

    if(I_ConfigDirPath.endsWith(QStringLiteral("/")))
        I_ConfigFullFilePath = I_ConfigDirPath + I_ConfigFileName;
    else
        I_ConfigFullFilePath = I_ConfigDirPath + QStringLiteral("/") + I_ConfigFileName;

    slot_LoadConfigFile(_config);
    I_SystemName = _config._systemName;
    I_SystemID = _config._systemID;
    I_EnableLogin = _config._enableLogin;

    if(!I_EnableLogin)
    {
        I_CurrentUserInfo._userName = "defaultUser";
        I_CurrentUserInfo._password = "";
        I_CurrentUserInfo._detail = "Non-login user.";
        I_CurrentUserInfo._authority = AT_MANAGER1;
        I_CurrentUserInfo._createDatetime = "";
    }
}

QCPF_Model::~QCPF_Model()
{

}

bool copyFileToPath(QString sourceDir ,QString toDir, bool coverFileIfExist)
{
    toDir.replace("\\","/");
    if (sourceDir == toDir){
        return true;
    }
    if (!QFile::exists(sourceDir)){
        return false;
    }
    QDir *createfile     = new QDir;
    bool exist = createfile->exists(toDir);
    if (exist){
        if(coverFileIfExist){
            createfile->remove(toDir);
        }
    }//end if

    if(!QFile::copy(sourceDir, toDir))
    {
        return false;
    }
    return true;
}

bool copyDirectoryFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){
            if(!copyDirectoryFiles(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()),
                coverFileIfExist))
                return false;
        }
        else{
            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            /// 进行文件copy
            if(!QFile::copy(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()))){
                    return false;
            }
        }
    }
    return true;
}

bool copyDirectoryLibraryFiles(const QString &fromDir, const QString &toDir, QStringList& copyFileLst, bool coverFileIfExist)
{
    copyFileLst.clear();
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

            if(coverFileIfExist && targetDir.exists(fileInfo.fileName())){
                targetDir.remove(fileInfo.fileName());
            }

            bool isValidFile = false;
#ifdef Q_OS_LINUX
            if(fileInfo.fileName().endsWith(".so", Qt::CaseInsensitive))
                isValidFile = true;
#endif

#ifdef Q_OS_WIN32
            if(fileInfo.fileName().endsWith(".dll", Qt::CaseInsensitive))
                isValidFile = true;
#endif
            if(isValidFile)
            {
                if(QFile::copy(fileInfo.filePath(),
                    targetDir.filePath(fileInfo.fileName()))){
                    copyFileLst.append(targetDir.filePath(fileInfo.fileName()));
                }
                else
                {
                    if(targetDir.exists(fileInfo.fileName()))
                        copyFileLst.append(targetDir.filePath(fileInfo.fileName()));
                    continue;
                }
            }
    }
    return true;
}

int QCPF_Model::pluginsCollect(QString pluginDirPath,  QList<PluginInfo*> selectedPluginInfoList, PluginType type)
{
    QDir dir(pluginDirPath);
    if(!dir.exists())
    {
        _outputInfo._type = InfoType::INFT_STATUS_INFO;
        _outputInfo._content = QString(tr("Can not find the plugin dir path \"%1\"")).arg(pluginDirPath);
        emit sig_OutputInfo(_outputInfo);
        return -1;
    }

    QString tempDirPath = pluginDirPath + "Temp";
    QDir tempDir(tempDirPath);

    foreach (QFileInfo fi, tempDir.entryInfoList()) {
        tempDir.remove(fi.fileName());
    }

    QFileInfoList fileList;
    QStringList copyFileLst;

    if(_config._enableHotPlug)
    {
        if(!copyDirectoryLibraryFiles(pluginDirPath, tempDirPath, copyFileLst, true))
        {
            _outputInfo._type = InfoType::INFT_STATUS_INFO;
            _outputInfo._content = QString(tr("There is an error on copying plugin files."));
            emit sig_OutputInfo(_outputInfo);
            return -3;
        }

        tempDir.setFilter(QDir::Files);
        fileList = tempDir.entryInfoList();
    }
    else
    {
        dir.setFilter(QDir::Files);
        fileList = dir.entryInfoList();
    }

    int fileCount =fileList.count();

    for(int i=0; i<selectedPluginInfoList.count(); i++)
    {
        bool isExit = false;
        foreach (QFileInfo fi, fileList) {
            QCoreApplication::processEvents();

            QString tFileName = fi.fileName();
            QString tFilePath = fi.filePath();
            QString tPluginFileName = selectedPluginInfoList[i]->_pluginFileName;

            if(tFileName==tPluginFileName)
            {
                QList<Plugin_Interface*> pluginLst;
                if(type == PT_SYS)
                    pluginLst = I_SysPlugins;
                else
                    pluginLst = I_NSysOrigPlugins;


                bool isHasInstance = false;
                foreach(Plugin_Interface* pi, pluginLst)
                {
                    if(pi->I_PluginFilePath == tFilePath)
                    {
                        isHasInstance = true;
                        break;
                    }
                }

                if(!isHasInstance)
                    pluginInstance(tFilePath, type);

                isExit = true;
                break;
            }
        }

        if(!isExit)
        {
            _outputInfo._type = InfoType::INFT_STATUS_INFO;
            _outputInfo._content = QString(tr("Can not find the file \"%1\", from dir path \"%2\"").arg(selectedPluginInfoList[i]->_pluginFileName).arg(pluginDirPath));
            emit sig_OutputInfo(_outputInfo);
        }
    }

    for(int i=0;i<fileCount;i++)
    {
        bool isExit = false;
        for(int j=0; j<selectedPluginInfoList.count(); j++)
        {
            QCoreApplication::processEvents();

            if(fileList[i].fileName() == selectedPluginInfoList[j]->_pluginFileName)
            {
                isExit = true;
                break;
            }
        }

        if(!isExit)
        {
            QList<Plugin_Interface*> pluginLst;
            if(type == PT_SYS)
            {
                pluginLst = I_SysPlugins;
            }
            else
            {
                pluginLst = I_NSysOrigPlugins;
            }


            bool isHasInstance = false;
            foreach(Plugin_Interface* pi, pluginLst)
            {
                QCoreApplication::processEvents();

                if(pi->I_PluginFilePath == fileList[i].filePath())
                {
                    isHasInstance = true;
                    break;
                }
            }

            if(!isHasInstance)
                pluginInstance(fileList[i], type);  
        }
    }

    if(_config._enableHotPlug)
    {
        QList<Plugin_Interface*> pluginLst;
        QList<Plugin_Interface*> discardedPluginLst;
        if(type == PT_SYS)
        {
            pluginLst = I_SysPlugins;
            discardedPluginLst = I_SysDiscardedPlugins;
        }
        else
        {
            pluginLst = I_NSysOrigPlugins;
            discardedPluginLst = I_NSysDiscardedPlugins;
        }

        foreach(Plugin_Interface* pi, pluginLst)
        {
            if(0>copyFileLst.indexOf(pi->I_PluginFilePath))
            {
                if(type == PT_SYS)
                {
                    I_SysPlugins.removeOne(pi);

                    if(0<=I_SysPlugins_Sel.indexOf(pi))
                        I_SysPlugins_Sel.removeOne(pi);

                     //-----------
                    I_SysDiscardedPlugins.append(pi);

                    //------------
                    for(int i=0; i<_config._sysPlugins_Sel.count(); i++)
                    {
                        if(_config._sysPlugins_Sel[i]->_pluginID == pi->I_PluginID && _config._sysPlugins_Sel[i]->_pluginFileName == pi->I_PluginFilePath)
                        {
                            _config._sysPlugins_Sel.removeAt(i);
                            _config._count_sysPlugins_Sel -=1;
                            break;
                        }
                    }
                }
                else
                {
                    if(0<=I_NSysOrigPlugins.indexOf(pi))
                        I_NSysOrigPlugins.removeOne(pi);

                    if(0<=I_NSysOrigPlugins_Sel.indexOf(pi))
                        I_NSysOrigPlugins_Sel.removeOne(pi);

                    if(0<=I_NSysClonePlugins.indexOf(pi))
                        I_NSysClonePlugins.removeOne(pi);

                    if(0<=I_NSysAllValidPlugins.indexOf(pi))
                        I_NSysAllValidPlugins.removeOne(pi);

                    //-----------
                   I_NSysDiscardedPlugins.append(pi);

                   //------------
                   for(int i=0; i<_config._nSysPlugins_Sel.count(); i++)
                   {
                       if(_config._nSysPlugins_Sel[i]->_pluginID == pi->I_PluginID && _config._nSysPlugins_Sel[i]->_pluginFileName == pi->I_PluginFilePath)
                       {
                           _config._nSysPlugins_Sel.removeAt(i);
                           _config._count_nSysPlugins_Sel -=1;
                           break;
                       }
                   }
                }
            }
            else
            {
                if(type == PT_SYS)
                {
                    if(0<=I_SysDiscardedPlugins.indexOf(pi))
                        I_SysDiscardedPlugins.removeOne(pi);
                }
                else
                {
                    if(0<=I_NSysDiscardedPlugins.indexOf(pi))
                        I_NSysDiscardedPlugins.removeOne(pi);
                }
            }
        }
    }

    return 0;
}

int QCPF_Model::pluginInstance(QFileInfo fi, PluginType type)
{
    QFileInfo fileInfo = fi;
    QString suffix = fileInfo.suffix();

    bool isValidFile = false;
#ifdef Q_OS_LINUX
    if(QString::compare(suffix, QString("so"), Qt::CaseInsensitive) == 0)
        isValidFile = true;
#endif

#ifdef Q_OS_WIN32
    if(QString::compare(suffix, QString("dll"), Qt::CaseInsensitive) == 0)
        isValidFile = true;
#endif
    if(isValidFile)
    {
        QString filePath = fileInfo.absoluteFilePath();
        QString fileName = fileInfo.baseName();

        Plugin_Interface *plugin = nullptr;
        QObject *tInstance = nullptr;
        QPluginLoader* pluginLoader = nullptr;
        try {
                pluginLoader = new QPluginLoader(filePath);
                tInstance = pluginLoader->instance();

                if(!pluginLoader->isLoaded())
                {
                    _outputInfo._type = InfoType::INFT_STATUS_INFO;
                    _outputInfo._content = QString(tr("There is an Error when loading plugin : \"%1\"")).arg( pluginLoader->errorString());
                    emit sig_OutputInfo(_outputInfo);
                }
        } catch(int){
            _outputInfo._type = InfoType::INFT_MSG_WARN;
            _outputInfo._content = QString(tr("There is an Error when loading plugin : \"%1\"")).arg(fileName);
            emit sig_OutputInfo(_outputInfo);
            return -254;
        }

        if(tInstance)
        {
            plugin = qobject_cast<Plugin_Interface*>(tInstance);
            if(plugin)
            {
                QString tDestPluginID = plugin->I_PluginID;

                Plugin_Interface *tp = new Plugin_Interface();

                if(type==PT_SYS)
                {
                    foreach (tp, this->I_SysPlugins) {
                        if(tp->I_PluginID == tDestPluginID)
                        {
                            _outputInfo._type = InfoType::INFT_STATUS_INFO;
                            _outputInfo._content = QString(tr("There is a same pluginID in system module:\"%1\"")).arg(filePath);
                            emit sig_OutputInfo(_outputInfo);
                            return -1;
                        }
                    }
                }
                else
                {
                    foreach (tp, this->I_NSysOrigPlugins) {
                        if(tp->I_PluginID == tDestPluginID)
                        {
                            _outputInfo._type = InfoType::INFT_STATUS_INFO;
                            _outputInfo._content = QString(tr("There is a same pluginID in non-system module:\"%1\"")).arg(filePath);
                            emit sig_OutputInfo(_outputInfo);
                            return -1;
                        }
                    }
                }

                plugin->I_PluginFilePath = filePath;

                try {
                    if(!plugin->ConnectCore(this))
                        return -2;

                } catch (int) {
                    _outputInfo._type = InfoType::INFT_STATUS_INFO;
                    _outputInfo._content = QString(tr("There is a exception when connecting plugin:\"1%\"")).arg(fileName);
                    emit sig_OutputInfo(_outputInfo);
                    return -244;
                }

                if(plugin->I_PluginType == PT_SYS && type == PT_SYS)
                {
                    this->I_SysPlugins.append(plugin);

                    I_PluginLoaderLst_Sys.append(pluginLoader);
                }

                if(plugin->I_PluginType == PT_NON_SYS && type == PT_NON_SYS)
                {
                    this->I_NSysOrigPlugins.append(plugin);
                    this->I_NSysAllValidPlugins.append(plugin);

                    I_PluginLoaderLst_NSys.append(pluginLoader);
                }

                _outputInfo._type = InfoType::INFT_STATUS_INFO;

                if(type==PT_SYS)
                    _outputInfo._content = QString(tr("Collecting system plugin:%1")).arg(plugin->I_PluginID);
                else
                    _outputInfo._content = QString(tr("Collecting non-system plugin:%1")).arg(plugin->I_PluginID);

                emit sig_OutputInfo(_outputInfo);
            }
        }
    }
    return 0;
}

int QCPF_Model::collectPlugins(PluginType type)
{
    if(type == PT_SYS)
    {
        if(0!=pluginsCollect(I_SystemPluginDirPath, _config._sysPlugins_Sel, PT_SYS))
            return -1;
    }
    else
    {
        if(0!=pluginsCollect(I_NonSysPluginDirPath, _config._nSysPlugins_Sel, PT_NON_SYS))
           return -2;
    }

    tagOutputInfo info;
    info._type = INFT_PLUGIN_COLLECT_FINISHED;
    emit sig_OutputInfo(info);
    return 0;
}

int QCPF_Model::collectPlugins()
{
    if(0!=pluginsCollect(I_SystemPluginDirPath, _config._sysPlugins_Sel, PT_SYS))
        return -1;

    if(0!=pluginsCollect(I_NonSysPluginDirPath, _config._nSysPlugins_Sel, PT_NON_SYS))
       return -2;

    tagOutputInfo info;
    info._type = INFT_PLUGIN_COLLECT_FINISHED;
    info._content = "Plugins collection finished!";
    emit sig_OutputInfo(info);
    return 0;
}

int QCPF_Model::slot_PreInitialize()
{
    _config.resetData();
    slot_LoadConfigFile(_config);

    collectPlugins();

    installConfig(_config);

    foreach (Plugin_Interface* tp, this->I_SysPlugins) {
        QString pid = tp->I_PluginID;
        tp->OnCoreInitialize();
    }
    foreach (Plugin_Interface* tp, this->I_NSysAllValidPlugins) {
        QString pid = tp->I_PluginID;
        tp->OnCoreInitialize();
    }

    return 0;
}

int QCPF_Model::slot_Initialize()
{
    try
    {
        _config.resetData();
        slot_LoadConfigFile(_config);

        collectPlugins();

        installConfig(_config);

        foreach (Plugin_Interface* pi, I_SysPlugins_Sel) {

            connect(this, &QCPF_Model::sig_Core, pi, &Plugin_Interface::slot_Plugin);
            connect(pi, &Plugin_Interface::sig_Plugin, this, &QCPF_Model::slot_Core);
            connect(this, &QCPF_Model::sig_OutputInfo, pi, &Plugin_Interface::slot_InputInfo);
            connect(pi, &Plugin_Interface::sig_OutputInfo, this, &QCPF_Model::slot_InputInfo);
        }
        foreach (Plugin_Interface* npi, I_NSysAllValidPlugins) {

            connect(this, &QCPF_Model::sig_Core, npi, &Plugin_Interface::slot_Plugin);
            connect(npi, &Plugin_Interface::sig_Plugin, this, &QCPF_Model::slot_Core);
            connect(this, &QCPF_Model::sig_OutputInfo, npi, &Plugin_Interface::slot_InputInfo);
            connect(npi, &Plugin_Interface::sig_OutputInfo, this, &QCPF_Model::slot_InputInfo);
        }
    }
    catch(int)
    {
        _outputInfo._type = InfoType::INFT_MSG_INFO;
        _outputInfo._content = tr("Core Initialize failed!") ;
        emit sig_OutputInfo(_outputInfo);
        return -255;
    }

    return 0;
}

int QCPF_Model::slot_Core(QVariant arg_in, QVariant &arg_out)
{

    return 0;
}

int QCPF_Model::slot_InputInfo(tagOutputInfo& info)
{
    switch (info._type) {
        case INFT_PLUGIN_COLLECT:
            if(info._title == "NonSys")
                collectPlugins(PT_NON_SYS);
            else if(info._title == "Sys")
                collectPlugins(PT_SYS);
            else
                collectPlugins();
        break;
    default:
        emit sig_OutputInfo(info);
    }

    return 0;
}

int QCPF_Model::installConfig(ConfigModel &config)
{
    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    _outputInfo._content = tr("Loading selected system plugins.");
    emit sig_OutputInfo(_outputInfo);

    this->I_SysPlugins_Sel.clear();
    for(int i=0; i<config._sysPlugins_Sel.count(); i++)
    {
        bool isExsitInSysPlugins = false;

        QString tSelOrigPluginID = config._sysPlugins_Sel[i]->_pluginID;
        for(int j=0; j<this->I_SysPlugins.count(); j++)
        {
            QString tPluginID = ((Plugin_Interface*)this->I_SysPlugins[j])->I_PluginID;
            if(tSelOrigPluginID==tPluginID)
            {
                bool isHasOne = false;
                foreach (Plugin_Interface*pi, this->I_SysPlugins_Sel) {
                    if(pi->I_PluginID == tSelOrigPluginID)
                    {
                        isHasOne = true;
                        break;
                    }
                }
                if(!isHasOne)
                {
                    this->I_SysPlugins[j]->I_IsEnable = true;
                    this->I_SysPlugins_Sel.append(this->I_SysPlugins[j]);
                }
                isExsitInSysPlugins = true;
                break;
            }
        }

        if(!isExsitInSysPlugins)
        {
            _outputInfo._type = InfoType::INFT_STATUS_INFO;
            _outputInfo._content = QString(tr("Can't find the plugin which plugin id = %1,when loading the selected system plugins.")).arg(tSelOrigPluginID);
            emit sig_OutputInfo(_outputInfo);
        }
    }

    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    _outputInfo._content = tr("Loading selected non-system plugins.");
    emit sig_OutputInfo(_outputInfo);

    this->I_NSysOrigPlugins_Sel.clear();
    for(int i=0; i<config._nSysPlugins_Sel.count(); i++)
    {
        bool isExsitInNSysOrigPlugins = false;

        QString tSelOrigPluginID = config._nSysPlugins_Sel[i]->_pluginID;
        for(int j=0; j<this->I_NSysOrigPlugins.count(); j++)
        {
            QString tPluginID = ((Plugin_Interface*)this->I_NSysOrigPlugins[j])->I_PluginID;
            if(tSelOrigPluginID==tPluginID)
            {
                bool isHasOne = false;
                foreach (Plugin_Interface*pi, this->I_NSysOrigPlugins_Sel) {
                    if(pi->I_PluginID == tSelOrigPluginID)
                    {
                        isHasOne = true;
                        break;
                    }
                }
                if(!isHasOne)
                {
                    this->I_NSysOrigPlugins[j]->I_IsEnable = true;
                    this->I_NSysOrigPlugins_Sel.append(this->I_NSysOrigPlugins[j]);
                }
                isExsitInNSysOrigPlugins = true;
                break;
            }
        }

        if(!isExsitInNSysOrigPlugins)
        {
            _outputInfo._type = InfoType::INFT_STATUS_INFO;
            _outputInfo._content = QString(tr("Can't find the plugin which plugin id=%1,when loading the selected non-system plugins.")).arg(tSelOrigPluginID);
            emit sig_OutputInfo(_outputInfo);
        }
    }

    foreach (Plugin_Interface* pi, this->I_NSysOrigPlugins) {
        if(!pi->I_IsEnable)
        {
           QPluginLoader* pluginLoader = new QPluginLoader(pi->I_PluginFilePath);

           if(pluginLoader!=nullptr)
           {
                bool ret = pluginLoader->unload();
                int i=0;
           }
        }
    }
    //---------------------------------------------------------------装/卸载克隆组件
    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    _outputInfo._content = tr("Uninstalling clone plugins.");
    emit sig_OutputInfo(_outputInfo);

    foreach (Plugin_Interface* pi, this->I_NSysClonePlugins) {
        bool isExsit = false;
        foreach (ClonePluginInfo* cpi, config._nSysClonePlugins) {
            if(cpi->_originalPluginID==pi->I_PluginID && cpi->_copyID==pi->I_CopyID)
            {
                isExsit = true;
                break;
            }
        }

        if(!isExsit)
        {
            this->I_NSysClonePlugins.removeOne(pi);
            delete pi;
        }
    }

    _outputInfo._type = InfoType::INFT_STATUS_INFO;
   _outputInfo._content = tr("Installing clone plugins.");
    emit sig_OutputInfo(_outputInfo);

    for(int i=0; i<config._nSysClonePlugins.count(); i++)
    {
        bool isCloneExsit = false;

        foreach (Plugin_Interface* pi, this->I_NSysClonePlugins) {
            if(pi->I_PluginID == config._nSysClonePlugins[i]->_originalPluginID &&
               pi->I_CopyID == config._nSysClonePlugins[i]->_copyID)
            {
                isCloneExsit = true;
                break;
            }
        }

        if(!isCloneExsit)
        {
            //---------------------------------------
            bool isOrigSelExsit = false;
            for(int j=0; j<this->I_NSysOrigPlugins_Sel.count(); j++)
            {
                QString tPluginID = ((Plugin_Interface*)this->I_NSysOrigPlugins_Sel[j])->I_PluginID;
                if(config._nSysClonePlugins[i]->_originalPluginID==tPluginID)
                {
                    Plugin_Interface* tClonePlugin = ((Plugin_Interface*)this->I_NSysOrigPlugins_Sel[j])->Clone(config._nSysClonePlugins[i]->_copyID, config._nSysClonePlugins[i]->_copyAliasName, config._nSysClonePlugins[i]->_copyComment);
                    tClonePlugin->setParent(this->I_NSysOrigPlugins_Sel[j]);
                    this->I_NSysClonePlugins.append(tClonePlugin);
                    isOrigSelExsit = true;
                    break;
                }
            }

            if(!isOrigSelExsit)
            {
                _outputInfo._type = InfoType::INFT_STATUS_INFO;

                _outputInfo._content = QString(tr("Can't find the original plugin which id=%1 from selected non-system collection, on installing the clone plugins.")).arg(config._nSysClonePlugins[i]->_originalPluginID);
                emit sig_OutputInfo(_outputInfo);
            }
        }
    }

    this->I_NSysAllValidPlugins.clear();

    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    _outputInfo._content = tr("Install the operation sequence.");
    emit sig_OutputInfo(_outputInfo);

    for(int i=0; i<config._nSysAllValidPlugins.count(); i++)
    {
        ValidPluginInfo* tItem = config._nSysAllValidPlugins[i];
        Plugin_Interface* tPlugin = nullptr;

        bool isExsit = false;
        if(!tItem->_isCopy)
        {
            for(int j=0; j<this->I_NSysOrigPlugins_Sel.count(); j++)
            {
                tPlugin = this->I_NSysOrigPlugins_Sel[j];
                if(tPlugin->I_PluginID == tItem->_originalPluginID && tPlugin->I_CopyID == tItem->_copyID)
                {
                    this->I_NSysAllValidPlugins.append(tPlugin);
                    isExsit = true;
                    break;
                }
            }

            if(!isExsit)
            {
                _outputInfo._type = InfoType::INFT_STATUS_INFO;
                _outputInfo._content = QString(tr("Can't find the original plugin which id=%1 from selected non-system collection, on installing the operation sequence.")).arg(tItem->_originalPluginID);
                emit sig_OutputInfo(_outputInfo);
            }
        }
        else
        {
            for(int j=0; j<this->I_NSysClonePlugins.count(); j++)
            {
                tPlugin = this->I_NSysClonePlugins[j];
                if(tPlugin->I_PluginID == tItem->_originalPluginID && tPlugin->I_CopyID == tItem->_copyID)
                {
                    this->I_NSysAllValidPlugins.append(tPlugin);
                    isExsit = true;
                    break;
                }
            }

            if(!isExsit)
            {
                _outputInfo._type = InfoType::INFT_STATUS_INFO;
                _outputInfo._content = QString(tr("Can't find the original plugin which id=%1 copyid=%2 from clone plugin collection, on installing the operation sequence.")).arg(tItem->_originalPluginID).arg(tItem->_copyID);
                emit sig_OutputInfo(_outputInfo);
            }
        }
    }
    return 0;
}

int CompareMsg(char* msg1, char* msg2)
{
    FILE *pOne, *pTwe;
    long lsize1, lsize2;
    char* buffer1 = NULL;
    char* buffer2 = NULL;
    size_t result1, result2;

    pOne = fopen(msg1, "rb");
    pTwe = fopen(msg2, "rb");
    if ((pOne == nullptr) || (pTwe == nullptr))
        return 1;

    fseek(pOne, 0, SEEK_END);
    lsize1 = ftell(pOne);
    //rewind(pOne);
    fseek(pOne, 0, SEEK_SET);
    fseek(pTwe, 0, SEEK_END);
    lsize2 = ftell(pTwe);
    rewind(pTwe);

    if (lsize1 != lsize2)
    {
        fclose(pOne);
        fclose(pTwe);
        return 1;
    }

    buffer1 = new char[lsize1];
    buffer2 = new char[lsize2];
    if ((buffer1 == NULL) || (buffer2 == NULL))
    {
        fclose(pOne);
        fclose(pTwe);
        delete[]buffer1;
        delete[]buffer2;
        return 1;
    }

    result1 = fread(buffer1, 1, lsize1, pOne);
    result2 = fread(buffer2, 1, lsize2, pTwe);
    if ((result1 != lsize1) || (result2 != lsize2))
    {
        fclose(pOne);
        fclose(pTwe);
        delete[]buffer1;
        delete[]buffer2;
        return 1;
    }


    int result = memcmp(buffer1, buffer2, lsize1);

    fclose(pOne);
    fclose(pTwe);
    delete[]buffer1;
    delete[]buffer2;

    return result;
}

int QCPF_Model::compareFiles(QString filePath1, QString filePath2)
{
    QByteArray tbFile1 = filePath1.toLatin1();
    QByteArray tbFile2 = filePath2.toLatin1();

    return CompareMsg(tbFile1.data(), tbFile2.data());
}

int QCPF_Model::saveConfigFile(QString filePath)
{
    if(!filePath.endsWith(QStringLiteral(".dat")))
        filePath += QStringLiteral(".dat");

    QFile file(filePath);

    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    out << _config;
    file.close();
    return 0;
}

int QCPF_Model::slot_LoadConfigFile(ConfigModel &config)
{
    config.resetData();

    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    _outputInfo._content = tr("Trying to read the core config file.");
    emit sig_OutputInfo(_outputInfo);

    if(!QFile::exists(I_ConfigFullFilePath))
    {
        _outputInfo._type = InfoType::INFT_STATUS_INFO;
        _outputInfo._content = tr("The core config file lost!");
        emit sig_OutputInfo(_outputInfo);
        return -1;
    }

    QFile file(I_ConfigFullFilePath);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    in >> config;
    file.close();

    return 0;
}

int QCPF_Model::slot_SaveConfigFile()
{
    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    _outputInfo._content = tr("Saveing the core config file.");
    emit sig_OutputInfo(_outputInfo);

    QFileInfo tFi(I_ConfigFullFilePath);
    if(!tFi.exists())
    {
        QFile fp;
        fp.setFileName(I_ConfigFullFilePath);
        fp.open(QIODevice::ReadWrite|QIODevice::Text);
    }

    QString tempConfigFullFilePath = I_ConfigDirPath + QStringLiteral("temp_") + I_ConfigFileName;
    if(0!=saveConfigFile(tempConfigFullFilePath))
            return -2;

    if(0!=compareFiles(tempConfigFullFilePath, I_ConfigFullFilePath))
    {
        saveConfigFile(I_ConfigFullFilePath);
        _outputInfo._type = INFT_CORE_CONFIG_CHANGED;
        emit sig_OutputInfo(_outputInfo);
    }

    slot_LoadConfigFile(_config);
    installConfig(_config);
     return 0;
}

int QCPF_Model::slot_ApplyConfig()
{
    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    _outputInfo._content = tr("Applying the core config file.");
    emit sig_OutputInfo(_outputInfo);

    QFileInfo tFi(I_ConfigFullFilePath);
    if(!tFi.exists())
        return -1;

    QString tempConfigFullFilePath = I_ConfigDirPath + QStringLiteral("temp_") + I_ConfigFileName;
    if(0!=saveConfigFile(tempConfigFullFilePath))
            return -1;

    if(0!=compareFiles(tempConfigFullFilePath, I_ConfigFullFilePath))
        installConfig(_config);
    return 0;
}

int QCPF_Model::slot_CancelConfig()
{
    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    _outputInfo._content = tr("Recovering the core config file.");
    emit sig_OutputInfo(_outputInfo);

    QFileInfo tFi(I_ConfigFullFilePath);
    if(!tFi.exists())
        return -1;

    QString tempConfigFullFilePath = I_ConfigDirPath + QStringLiteral("temp_") + I_ConfigFileName;
    if(0!=saveConfigFile(tempConfigFullFilePath))
            return -1;

    if(0!=compareFiles(tempConfigFullFilePath, I_ConfigFullFilePath))
    {
        _config.resetData();
        slot_LoadConfigFile(_config);
        installConfig(_config);
    }
    return 0;
}

Plugin_Interface* QCPF_Model::GetPlugin(PluginType pType, QString pluginID)
{
    QList<Plugin_Interface*> pluginLst;
    if (pType == PT_SYS)
        pluginLst = I_SysPlugins_Sel;
    else
        pluginLst = I_NSysOrigPlugins_Sel;

    foreach(Plugin_Interface* pi, pluginLst)
    {
        if(pi->I_PluginID == pluginID)
        {
            return pi;
        }
    }
    return nullptr;
}

PluginActionInfo* QCPF_Model::GetActionInfo(PluginType pType, QString pluginID, QString actionName)
{
    Plugin_Interface* dstPi = GetPlugin(pType, pluginID);

    if (dstPi == nullptr)
        return nullptr;

    foreach(PluginActionInfo* pai, dstPi->I_ActionList)
    {
        if(pai->_actionName == actionName)
        {
            return pai;
        }
    }

    return nullptr;
}

PluginWidgetInfo* QCPF_Model::GetWidgetInfo(PluginType pType, QString pluginID, QString widgetName)
{
    Plugin_Interface* dstPi = GetPlugin(pType, pluginID);

    if (dstPi == nullptr)
        return nullptr;

    foreach(PluginWidgetInfo* pwi, dstPi->I_WidgetList)
    {
        if(pwi->_widget->objectName() == widgetName)
            return pwi;
    }

    return nullptr;
}

PluginFunctionInfo* QCPF_Model::GetFunctionInfo(PluginType pType, QString pluginID, QString functionName)
{
    Plugin_Interface* dstPi = GetPlugin(pType, pluginID);

    if (dstPi == nullptr)
        return nullptr;

    foreach(PluginFunctionInfo* pfi, dstPi->I_FunctionList)
    {
        if(pfi->_functionName == functionName)
            return pfi;
    }

    return nullptr;
}


Plugin_Interface* QCPF_Model::GetPlugin_Copy(PluginType pType, QString pluginID, QString copyID)
{
    QList<Plugin_Interface*> pluginLst;
    if (pType == PT_SYS)
        pluginLst = I_SysPlugins_Sel;
    else
        pluginLst = I_NSysOrigPlugins_Sel;

    foreach(Plugin_Interface* pi, pluginLst)
    {
        if(pi->I_PluginID == pluginID && pi->I_CopyID == copyID)
        {
            return pi;
        }
    }
    return nullptr;
}

PluginActionInfo* QCPF_Model::GetActionInfo_Copy(PluginType pType, QString pluginID, QString copyID, QString actionName)
{
    Plugin_Interface* dstPi = GetPlugin_Copy(pType, pluginID, copyID);

    if (dstPi == nullptr)
        return nullptr;

    foreach(PluginActionInfo* pai, dstPi->I_ActionList)
    {
        if(pai->_actionName == actionName)
        {
            return pai;
        }
    }

    return nullptr;
}

PluginWidgetInfo* QCPF_Model::GetWidgetInfo_Copy(PluginType pType, QString pluginID, QString copyID, QString widgetName)
{
    Plugin_Interface* dstPi = GetPlugin_Copy(pType, pluginID, copyID);

    if (dstPi == nullptr)
        return nullptr;

    foreach(PluginWidgetInfo* pwi, dstPi->I_WidgetList)
    {
        if(pwi->_widget->objectName() == widgetName)
            return pwi;
    }

    return nullptr;
}

PluginFunctionInfo* QCPF_Model::GetFunctionInfo_Copy(PluginType pType, QString pluginID, QString copyID, QString functionName)
{
    Plugin_Interface* dstPi = GetPlugin_Copy(pType, pluginID, copyID);

    if (dstPi == nullptr)
        return nullptr;

    foreach(PluginFunctionInfo* pfi, dstPi->I_FunctionList)
    {
        if(pfi->_functionName == functionName)
            return pfi;
    }

    return nullptr;
}

int QCPF_Model::Invoke_PluginFunction(PluginType pType, QString pluginID, QString pluginFunctionName)
{
    QVariant tv;
    return Invoke_PluginFunction(pType, pluginID, pluginFunctionName, tv, tv);
}

int QCPF_Model::Invoke_PluginFunction(PluginType pType, QString pluginID, QString pluginFunctionName, QVariant arg_in)
{
    QVariant tv;
    return Invoke_PluginFunction(pType, pluginID, pluginFunctionName, arg_in, tv);
}

int QCPF_Model::Invoke_PluginFunction(PluginType pType, QString pluginID, QString pluginFunctionName, QVariant arg_in, QVariant& arg_out)
{
    QList<Plugin_Interface*> pluginLst;
    if(pType == PT_SYS)
        pluginLst = I_SysPlugins_Sel;
    else
        pluginLst = I_NSysOrigPlugins_Sel;

    bool isPluginExist = false;
    bool isFunctionExist = false;

    foreach (Plugin_Interface* pi, pluginLst) {
        if(pi->I_PluginID == pluginID)
        {
            isPluginExist = true;
            foreach(PluginFunctionInfo* pfi,  pi->I_FunctionList)
            {
                if(pfi->_functionName == pluginFunctionName)
                {
                    isFunctionExist = true;
                    int ret = (pi->*pfi->_pFunction)(arg_in, arg_out);
                }
            }
        }
    }

    if(!isPluginExist)
        return -1;

    if(!isFunctionExist)
        return -2;

    return 0;
}

int QCPF_Model::Invoke_PluginFunction_Copy(PluginType pType, QString pluginID, QString copyID, QString pluginFunctionName)
{
    QVariant tv;
    return Invoke_PluginFunction_Copy(pType, pluginID, copyID, pluginFunctionName, tv, tv);
}

int QCPF_Model::Invoke_PluginFunction_Copy(PluginType pType, QString pluginID, QString copyID, QString pluginFunctionName, QVariant arg_in)
{
    QVariant tv;
    return Invoke_PluginFunction_Copy(pType, pluginID, copyID, pluginFunctionName, arg_in, tv);
}

int QCPF_Model::Invoke_PluginFunction_Copy(PluginType pType, QString pluginID, QString copyID, QString pluginFunctionName, QVariant arg_in, QVariant& arg_out)
{
    QList<Plugin_Interface*> pluginLst;
    if(pType == PT_SYS)
        pluginLst = I_SysPlugins_Sel;
    else
        pluginLst = I_NSysAllValidPlugins;

    bool isPluginExist = false;
    bool isFunctionExist = false;

    foreach (Plugin_Interface* pi, pluginLst) {
        if(pi->I_PluginID == pluginID && pi->I_CopyID == copyID)
        {
            isPluginExist = true;
            foreach(PluginFunctionInfo* pfi,  pi->I_FunctionList)
            {
                if(pfi->_functionName == pluginFunctionName)
                {
                    isFunctionExist = true;
                    int ret = (pi->*pfi->_pFunction)(arg_in, arg_out);
                }
            }
        }
    }

    if(!isPluginExist)
        return -1;

    if(!isFunctionExist)
        return -2;

    return 0;
}

