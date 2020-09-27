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
#define SYSTEM_VERSION "1.0.0.5"
#define ORGANIZATION_NAME "Jamie.T"

QCPF_Model::QCPF_Model(RunMode runMode, QObject* parent):_config(this)
{
    I_RunMode = runMode;
    I_SystemVersion = SYSTEM_VERSION;
    I_OrganizationName = ORGANIZATION_NAME;
    this->setParent(parent);

    slot_LoadConfigFile(_config);//由于系统起来便要显示系统名称，因此在构造的时候就读取一次配置文件。
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

    slot_LoadConfigFile(_config);//由于系统起来便要显示系统名称，因此在构造的时候就读取一次配置文件。
    I_SystemName = _config._systemName;
    I_SystemID = _config._systemID;
}

QCPF_Model::~QCPF_Model()
{

}

//拷贝文件：
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

//拷贝文件夹：
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

//只拷贝*.dll文件到temp文件夹，并且把文件名进行掩码，不递归：
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
    if(!dir.exists()) //判断文件夹是否存在
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
    //是否做热插拔处理
//    if(isCopyToTemp)
//    {
//        if(!copyDirectoryDllFiles(pluginDirPath, tempDirPath,  true))
//        {
//            _outputInfo._type = InfoType::INFT_STATUS_INFO;
//            _outputInfo._content = QString(tr("There is an error on copying plugin files."));
//            emit sig_OutputInfo(_outputInfo);
//            //return -2;
//        }

//        tempDir.setFilter(QDir::Files);//设置dir的过滤模式,表示只遍历本文件夹内的文件
//        fileList = tempDir.entryInfoList();//获取本文件夹内所有文件的信息
//    }
//    else
//    {
        dir.setFilter(QDir::Files);//设置dir的过滤模式,表示只遍历本文件夹内的文件
        fileList = dir.entryInfoList();//获取本文件夹内所有文件的信息


    int fileCount =fileList.count();//获取本文件夹内的文件个数

    //=========================================================================
    //按配置文件中原始组件顺序，查找指定组件文件,如果找到了就进行实例化，实现原始组件构造运行时可配
    //=========================================================================
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
                //如果已经实例化过，就不在实例化该plugin
                if(!isHasInstance)
                    pluginInstance(tFilePath, type);

                isExit = true;
                break;
            }
        }
        //如果按顺序没在指定文件夹找到目标文件，则提示，并继续查找下一个
        if(!isExit)
        {
            _outputInfo._type = InfoType::INFT_STATUS_INFO;
            _outputInfo._content = QString(tr("Can not find the file \"%1\", from dir path \"%2\"").arg(selectedPluginInfoList[i]->_pluginFileName).arg(pluginDirPath));
            emit sig_OutputInfo(_outputInfo);
        }
    }

    //=========================================================================
    //继续收集非配置文件的组件，如果上面已经按配置文件顺序构造过的组件，这里就不在构造了，反之则构造
    //=========================================================================
    for(int i=0;i<fileCount;i++)
    {
        bool isExit = false;
        for(int j=0; j<selectedPluginInfoList.count(); j++)
        {
            //如果上面已经按配置文件顺序构造过的组件，这里就不在构造了
            if(fileList[i].fileName() == selectedPluginInfoList[j]->_pluginFileName)
            {
                isExit = true;
                break;
            }
        }
        //如果上面没有构造过，则在这里按收集到的文件顺序依次构造
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
            //如果已经实例化过，就不在实例化该plugin
            if(!isHasInstance)
                pluginInstance(fileList[i], type);
        }
    }
    return 0;
}

int QCPF_Model::pluginInstance(QFileInfo fi, PluginType type)
{
    QFileInfo fileInfo = fi; //获取每个文件信息
    QString suffix = fileInfo.suffix(); //获取文件后缀名
    //筛选出所有dll文件(如果要筛选其他格式的文件则根据需要修改tr("dll")中的字符串即可)
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
        QString filePath = fileInfo.absoluteFilePath();//获取文件绝对路径即全路径
        QString fileName = fileInfo.baseName();//获取文件后名(不带后缀的文件名)

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
            return -254; //实例化组件时异常
        }

        if(tInstance)
        {
            plugin = qobject_cast<Plugin_Interface*>(tInstance);
            if(plugin)
            {
                //检查是否已经有同ID的组件，如果有就不添加，没有则添加
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
                    if(!plugin->ConnectCore(this))//使Plugin获得model和viewmodel对象实例,如果连接失败则不加载这个plugin
                        return -2;
                } catch (int) {
                    _outputInfo._type = InfoType::INFT_STATUS_INFO;
                    _outputInfo._content = QString(tr("There is a exception when connecting plugin:\"1%\"")).arg(fileName);
                    emit sig_OutputInfo(_outputInfo);
                    return -244;//连接组件时出现异常
                }

                if(plugin->I_PluginType == PT_SYS && type == PT_SYS)//两个条件的限制结果是，系统组件放到非系统组件目录不会被加载，反之非系统组件放到系统组件目录也不会被加载。
                    this->I_SysPlugins.append(plugin);

                if(plugin->I_PluginType == PT_NON_SYS && type == PT_NON_SYS)
                    this->I_NSysOrigPlugins.append(plugin);

                //发送组件信息信号，通过LoadingControllor连接到需要显示的view里去
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
    //收集系统组件信息
    if(0!=pluginsCollect(I_SystemPluginDirPath, _config._sysPlugins_Sel, PT_SYS))
        return -1;

    //收集非系统组件信息
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

        //收集组件信息
        collectPlutins();

        //安装配置信息
        installConfig(_config);

        //为所有组件建立公共信号槽连接
        foreach (Plugin_Interface* pi, I_SysPlugins_Sel) {
            /*
            动态建立信号槽的连接
            */
            connect(this, &QCPF_Model::sig_Core, pi, &Plugin_Interface::slot_Plugin);
            connect(pi, &Plugin_Interface::sig_Plugin, this, &QCPF_Model::slot_Core);
            connect(this, &QCPF_Model::sig_OutputInfo, pi, &Plugin_Interface::slot_InputInfo);
            connect(pi, &Plugin_Interface::sig_OutputInfo, this, &QCPF_Model::slot_InputInfo);
        }
        foreach (Plugin_Interface* npi, I_NSysAllValidPlugins) {
            /*
            动态建立信号槽的连接
            */
            connect(this, &QCPF_Model::sig_Core, npi, &Plugin_Interface::slot_Plugin);
            connect(npi, &Plugin_Interface::sig_Plugin, this, &QCPF_Model::slot_Core);
            connect(this, &QCPF_Model::sig_OutputInfo, npi, &Plugin_Interface::slot_InputInfo);
            connect(npi, &Plugin_Interface::sig_OutputInfo, this, &QCPF_Model::slot_InputInfo);
        }

        //invoke plugin functions
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
    //---------------------------------------------------------------装载已选系统组件
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
                //如果I_SysPlugins_Sel中已经有该对象，则不添加
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
//    //把没选中的系统组件卸载掉
//    foreach (Plugin_Interface* pi, this->I_SysPlugins) {
//        if(!pi->I_IsEnable)
//        {
//           QPluginLoader* pluginLoader = new QPluginLoader(pi->I_PluginFilePath);
//           if(pluginLoader!=nullptr)
//               pluginLoader->unload();
//        }
//    }
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
                //如果I_SysPlugins_Sel中已经有该对象，则不添加
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

//    //把没选中的非系统组件卸载掉
//    foreach (Plugin_Interface* pi, this->I_NSysOrigPlugins) {
//        if(!pi->I_IsEnable)
//        {
//           QPluginLoader* pluginLoader = new QPluginLoader(pi->I_PluginFilePath);

//           if(pluginLoader!=nullptr)
//           {
//                bool ret = pluginLoader->unload();
//                int i=0;
//           }
//        }
//    }
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

        //如果在配置文件里没找到该项，说明该项在配置时被干掉了，则卸载该项
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
        //如果I_NSysClonePlugins里面已经有该克隆体，则不再重新克隆它，这在初始化时没有意义，但是在保存信息时，可以使原有克隆体不被干掉
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
                    tClonePlugin->setParent(this->I_NSysOrigPlugins_Sel[j]);//与已选原始组件进行关联
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
        if(!tItem->_isCopy)//如果是原始组件
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
        else//如果是克隆组件
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
    //将2个消息各自读取到buffer中
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

    //写入
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

    //保存完配置文件，再重新读取并安装一次配置
    slot_LoadConfigFile(_config);
    installConfig(_config);
     return 0;
}

int QCPF_Model::slot_ApplyConfig()
{
    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    //_outputInfo._content = QStringLiteral("应用内核配置.");
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
    //_outputInfo._content = QStringLiteral("恢复内核配置.");
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

