/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "qcpf_model.h"
#include <QPluginLoader>
#include <QDataStream>
#include <QStringLiteral>
#include <QMap>

#define MASK_END_STR "_tp"
#define SYSTEM_VERSION "1.0.0.6"
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
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
        if(!targetDir.mkdir(targetDir.absolutePath()))
            return false;
    }

    QFileInfoList fileInfoList = sourceDir.entryInfoList();
    foreach(QFileInfo fileInfo, fileInfoList){
        if(fileInfo.fileName() == "." || fileInfo.fileName() == "..")
            continue;

        if(fileInfo.isDir()){    /**< 当为目录时，递归的进行copy */
            if(!copyDirectoryFiles(fileInfo.filePath(),
                targetDir.filePath(fileInfo.fileName()),
                coverFileIfExist))
                return false;
        }
        else{            /**< 当允许覆盖操作时，将旧文件进行删除操作 */
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

bool copyDirectoryDllFiles(const QString &fromDir, const QString &toDir, bool coverFileIfExist)
{
    QDir sourceDir(fromDir);
    QDir targetDir(toDir);
    if(!targetDir.exists()){    /**< 如果目标目录不存在，则进行创建 */
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
                /// 进行文件copy, 拷贝失败继续拷贝下一个文件。
                if(!QFile::copy(fileInfo.filePath(),
                    targetDir.filePath(fileInfo.fileName()))){
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
    //清空临时文件夹
    foreach (QFileInfo fi, tempDir.entryInfoList()) {
        tempDir.remove(fi.fileName());
    }

    QFileInfoList fileList;

    dir.setFilter(QDir::Files);
    fileList = dir.entryInfoList();

    int fileCount =fileList.count();

    for(int i=0; i<selectedPluginInfoList.count(); i++)
    {
        bool isExit = false;
        foreach (QFileInfo fi, fileList) {
            QString tFileName = fi.fileName();
            QString tFilePath = fi.filePath();
            if(tFileName==selectedPluginInfoList[i]->_pluginFileName)
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
                pluginLst = I_SysPlugins;
            else
                pluginLst = I_NSysOrigPlugins;


            bool isHasInstance = false;
            foreach(Plugin_Interface* pi, pluginLst)
            {
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

        } catch(int){
            _outputInfo._type = InfoType::INFT_STATUS_INFO;
            _outputInfo._content = QString(tr("There is a Error when loading plugin \"%1\"")).arg(fileName);
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
                    this->I_SysPlugins.append(plugin);

                if(plugin->I_PluginType == PT_NON_SYS && type == PT_NON_SYS)
                    this->I_NSysOrigPlugins.append(plugin);

                _outputInfo._type = InfoType::INFT_STATUS_INFO;

                if(type==PT_SYS)
                    _outputInfo._content = QString(tr("Collecting system plugin:%1")).arg(plugin->I_PluginID);
                else
                    _outputInfo._content = QString(tr("Collecting non-system plugin:%1")).arg(plugin->I_PluginID);

                emit sig_OutputInfo(_outputInfo);
            }
        }
    }
}

int QCPF_Model::collectPlutins()
{
    if(0!=pluginsCollect(I_SystemPluginDirPath, _config._sysPlugins_Sel, PT_SYS))
        return -1;

    if(0!=pluginsCollect(I_NonSysPluginDirPath, _config._nSysPlugins_Sel, PT_NON_SYS))
       return -2;

    tagOutputInfo info;
    info._type = INFT_PLUGIN_COLLECT_FINISHED;
    emit sig_OutputInfo(info);
    return 0;
}

int QCPF_Model::slot_Initialize()
{
    try
    {
        _config.resetData();
        slot_LoadConfigFile(_config);

        collectPlutins();

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

        foreach (Plugin_Interface* tp, this->I_SysPlugins) {
            tp->OnCoreInitialize();
        }
        foreach (Plugin_Interface* tp, this->I_NSysAllValidPlugins) {
            tp->OnCoreInitialize();
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
            collectPlutins();
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
            //_outputInfo._content = QStringLiteral("装载已选系统组件时，在系统组件集合中未找到ID为\"") + tSelOrigPluginID + QStringLiteral("\"的组件.");
            _outputInfo._content = QString(tr("Can't find the plugin which plugin id = %1,when loading the selected system plugins.")).arg(tSelOrigPluginID);
            emit sig_OutputInfo(_outputInfo);
        }
    }

    //---------------------------------------------------------------装载已选非系统组件
    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    //_outputInfo._content = QStringLiteral("装载非系统组件.");
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
            //_outputInfo._content = QStringLiteral("装载已选非系统组件时，在非系统原始组件集合中未找到ID为\"") + tSelOrigPluginID + QStringLiteral("\"的组件.");
            _outputInfo._content = QString(tr("Can't find the plugin which plugin id=%1,when loading the selected non-system plugins.")).arg(tSelOrigPluginID);
            emit sig_OutputInfo(_outputInfo);
        }
    }

    //---------------------------------------------------------------装/卸载克隆组件
    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    //_outputInfo._content = QStringLiteral("卸载禁用的克隆组件.");
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
    //_outputInfo._content = QStringLiteral("装载创建的克隆组件.");
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
                //_outputInfo._content = QStringLiteral("装载克隆组件时，在已选原始组件集合中未找到ID为\"") + config._nSysClonePlugins[i]->_originalPluginID + QStringLiteral("\"的已选原始组件.");
                _outputInfo._content = QString(tr("Can't find the original plugin which id=%1 from selected non-system collection, on installing the clone plugins.")).arg(config._nSysClonePlugins[i]->_originalPluginID);
                emit sig_OutputInfo(_outputInfo);
            }
        }
    }

    //---------------------------------------------------------------为I_nSysAllValidPlugins排序
    this->I_NSysAllValidPlugins.clear();

    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    //_outputInfo._content = QStringLiteral("配置组件运行时序.");
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
                //_outputInfo._content = QStringLiteral("配置组件运行时序时，在已选原始组件集合中未找到ID为\"") + tItem->_originalPluginID + QStringLiteral("\"的已选原始组件.");
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
                //_outputInfo._content = QStringLiteral("配置组件运行时序时，在克隆组件集合中未找到原始组件ID为\"") + tItem->_originalPluginID + QStringLiteral("\"，副本ID为") + tItem->_copyID + QStringLiteral("\"的克隆组件.");
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
    if ((pOne == NULL) || (pTwe == NULL))
    {
        fclose(pOne);
        fclose(pTwe);
        return 1;
    }

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
    //_outputInfo._content = QStringLiteral("保存内核配置.");
    _outputInfo._content = tr("Saveing the core config file.");
    emit sig_OutputInfo(_outputInfo);

    QFileInfo tFi(I_ConfigFullFilePath);
    if(!tFi.exists())
        return -1;

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

int QCPF_Model::Invoke_PluginFunction(PluginType pType, QString pluginID, QString copyID, QString pluginFunctionName, QVariant arg_in, QVariant& arg_out)
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

