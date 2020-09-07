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

QCPF_Model::QCPF_Model(QObject* parent):_config(this)
{
    this->setParent(parent);

    slot_LoadConfigFile(_config);
}

QCPF_Model::QCPF_Model(QObject* parent, QString applicationDirPath, QString sysPluginDirPath, QString nSysPluginDirPath, QString configDirPath, QString configFileName, bool isEnableHotPlug):_config(this)
{
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

    I_IsEnableHotPlug = isEnableHotPlug;

    slot_LoadConfigFile(_config);
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

            if(fileInfo.fileName().endsWith(".dll", Qt::CaseInsensitive))
            {
                /// 进行文件copy
                if(!QFile::copy(fileInfo.filePath(),
                    targetDir.filePath(fileInfo.fileName()))){
                        return false;
                }
            }
    }
    return true;
}

int QCPF_Model::pluginsCollect(bool isCopyToTemp, QString pluginDirPath,  QList<PluginInfo*> selectedPluginInfoList, PluginType type)
{
    QDir dir(pluginDirPath);
    if(!dir.exists()) //判断文件夹是否存在
    {
        _outputInfo._type = InfoType::INFT_STATUS_INFO;
        _outputInfo._content = QString(tr("Can not find the plugin dir path \"%1\"")).arg(pluginDirPath);
        emit sig_OutputInfo(_outputInfo);
        return -1;
    }

    QString tempDirPath = pluginDirPath + "/Temp";
    QDir tempDir(tempDirPath);
    //清空临时文件夹
    foreach (QFileInfo fi, tempDir.entryInfoList()) {
        tempDir.remove(fi.fileName());
    }

    QFileInfoList fileList;
    //是否做热插拔处理
    if(isCopyToTemp)
    {
        if(!copyDirectoryDllFiles(pluginDirPath, tempDirPath,  true))
        {
            _outputInfo._type = InfoType::INFT_STATUS_INFO;
            _outputInfo._content = QString(tr("There is an error on copying plugin files."));
            emit sig_OutputInfo(_outputInfo);
            return -2;
        }

        tempDir.setFilter(QDir::Files);//设置dir的过滤模式,表示只遍历本文件夹内的文件
        fileList = tempDir.entryInfoList();//获取本文件夹内所有文件的信息
    }
    else
    {
        dir.setFilter(QDir::Files);//设置dir的过滤模式,表示只遍历本文件夹内的文件
        fileList = dir.entryInfoList();//获取本文件夹内所有文件的信息
    }

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
            pluginInstance(fileList[i], type);
    }
    return 0;
}

int QCPF_Model::pluginInstance(QFileInfo fi, PluginType type)
{
    QFileInfo fileInfo = fi; //获取每个文件信息
    QString suffix = fileInfo.suffix(); //获取文件后缀名
    //筛选出所有dll文件(如果要筛选其他格式的文件则根据需要修改tr("dll")中的字符串即可)
    if(QString::compare(suffix, QString("dll"), Qt::CaseInsensitive) == 0)
    {
        QString filePath = fileInfo.absoluteFilePath();//获取文件绝对路径即全路径
        QString fileName = fileInfo.baseName();//获取文件后名(不带后缀的文件名)

        PluginInterface *plugin = nullptr;
        QPluginLoader pluginLoader(filePath);

        QObject *tInstanse = nullptr;
        try {
                tInstanse = pluginLoader.instance();
        } catch(int){
            _outputInfo._type = InfoType::INFT_STATUS_INFO;
            _outputInfo._content = QString(tr("There is a Error when loading plugin \"%1\"")).arg(fileName);
            emit sig_OutputInfo(_outputInfo);
            return -254; //实例化组件时异常
        }

        if(tInstanse)
        {
            plugin = qobject_cast<PluginInterface*>(tInstanse);
            if(plugin)
            {
                //检查是否已经有同ID的组件，如果有就不添加，没有则添加
                QString tDestPluginID = plugin->I_PluginID;

                PluginInterface *tp = new PluginInterface();

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
                /*
                动态建立信号槽的连接
                */
                connect(this, SIGNAL(sig_Core(QVariant, QVariant&)), plugin, SLOT(PluginInterface::slot_Plugin(QVariant, QVariant&)));
                connect(plugin, SIGNAL(PluginInterface::sig_Plugin(QVariant, QVariant&)), this, SLOT(slot_Core(QVariant, QVariant&)));
                //发送组件信息信号，通过LoadingControllor连接到需要显示的view里去

                _outputInfo._type = InfoType::INFT_STATUS_INFO;

                if(type==PT_SYS)
                    _outputInfo._content = QString(tr("Collecting system plugin information:%1")).arg(plugin->I_PluginID);
                else
                    _outputInfo._content = QString(tr("Collecting non-system plugin information:%1")).arg(plugin->I_PluginID);

                emit sig_OutputInfo(_outputInfo);
            }
        }
    }
}

int QCPF_Model::slot_Initialize(QString user, QString pwd, QString extInfo)
{
    if(user!="tt" || pwd!="1")
    {
        _outputInfo._type = InfoType::INFT_MSG_INFO;
        _outputInfo._content = tr("Load failed，Please check your user name and password!") ;
        emit sig_OutputInfo(_outputInfo);
        return -1;
    }

    foreach (PluginInterface* pi, I_SysPlugins) {
        delete pi;
    }
    foreach (PluginInterface* pi, I_NSysOrigPlugins) {
        delete pi;
    }
    foreach (PluginInterface* pi, I_NSysClonePlugins) {
        delete pi;
    }
    foreach (PluginInterface* pi, I_NSysAllValidPlugins) {
        delete pi;
    }
    foreach (PluginInterface* pi, I_NSysOrigPlugins_Sel) {
        delete pi;
    }

    //收集系统组件信息
    pluginsCollect(I_IsEnableHotPlug, I_SystemPluginDirPath, _config._sysPlugins_Sel, PT_SYS);

    //收集非系统组件信息
    pluginsCollect(I_IsEnableHotPlug, I_NonSysPluginDirPath, _config._nSysPlugins_Sel, PT_NON_SYS);

    //安装配置信息
    installConfig(_config);

    //invoke plugin functions
    foreach (PluginInterface* tp, this->I_SysPlugins) {
        tp->OnViewModelInitialize();
    }
    foreach (PluginInterface* tp, this->I_NSysAllValidPlugins) {
        tp->OnViewModelInitialize();
    }

    return 0;
}

int QCPF_Model::slot_Core(QVariant arg_in, QVariant &arg_out)
{

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
        bool isExsit = false;

        QString tSelOrigPluginID = config._sysPlugins_Sel[i]->_pluginID;
        for(int j=0; j<this->I_SysPlugins.count(); j++)
        {
            QString tPluginID = ((PluginInterface*)this->I_SysPlugins[j])->I_PluginID;
            if(tSelOrigPluginID==tPluginID)
            {
                this->I_SysPlugins_Sel.append(this->I_SysPlugins[j]);
                isExsit = true;
                break;
            }
        }

        if(!isExsit)
        {
            _outputInfo._type = InfoType::INFT_STATUS_INFO;
            //_outputInfo._content = QStringLiteral("装载已选系统组件时，在系统组件集合中未找到ID为\"") + tSelOrigPluginID + QStringLiteral("\"的组件.");
            _outputInfo._content = QString(tr("Can't find the plugin which plugin id=%1,when loading the selected system plugins.")).arg(tSelOrigPluginID);
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
        bool isOrigExsit = false;

        QString tSelOrigPluginID = config._nSysPlugins_Sel[i]->_pluginID;
        for(int j=0; j<this->I_NSysOrigPlugins.count(); j++)
        {
            QString tPluginID = ((PluginInterface*)this->I_NSysOrigPlugins[j])->I_PluginID;
            if(tSelOrigPluginID==tPluginID)
            {
                this->I_NSysOrigPlugins_Sel.append(this->I_NSysOrigPlugins[j]);
                isOrigExsit = true;
                break;
            }
        }

        if(!isOrigExsit)
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

    foreach (PluginInterface* pi, this->I_NSysClonePlugins) {
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
        foreach (PluginInterface* pi, this->I_NSysClonePlugins) {
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
                QString tPluginID = ((PluginInterface*)this->I_NSysOrigPlugins_Sel[j])->I_PluginID;
                if(config._nSysClonePlugins[i]->_originalPluginID==tPluginID)
                {
                    PluginInterface* tClonePlugin = ((PluginInterface*)this->I_NSysOrigPlugins_Sel[j])->Clone(config._nSysClonePlugins[i]->_copyID, config._nSysClonePlugins[i]->_copyAliasName, config._nSysClonePlugins[i]->_copyComment);
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
        PluginInterface* tPlugin = nullptr;

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
    //_outputInfo._content = QStringLiteral("读取内核配置.");
    _outputInfo._content = tr("Reading the core config file.");
    emit sig_OutputInfo(_outputInfo);

    QFile file(I_ConfigFullFilePath);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    in >> config;
    file.close();

    //暂时的用户管理
    I_UserInfoLst.append(new UserInfo("Jamie", "19820901", AT_DEVELOPER1));
    I_CurrentUserInfo._userName = "Jamie";
    I_CurrentUserInfo._password = "19820901";
    I_CurrentUserInfo._authority = AT_DEVELOPER1;
    return 0;
}

int QCPF_Model::slot_SaveConfigFile()
{
    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    //_outputInfo._content = QStringLiteral("保存内核配置.");
    _outputInfo._content = tr("Saveing the core config file.");
    emit sig_OutputInfo(_outputInfo);

    return saveConfigFile(I_ConfigFullFilePath);
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


