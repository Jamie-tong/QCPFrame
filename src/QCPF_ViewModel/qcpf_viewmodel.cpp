/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "qcpf_viewmodel.h"
#include <QDataStream>
#include <QDir>
#include "../QCPF_Model/qcpf_model.h"
#include <QtWidgets/QMainWindow>
#include <QDockWidget>

QCPF_Model* _instCore;
QCPF_ViewModel::QCPF_ViewModel(QObject* parent):_config(this)
{
    this->setParent(parent);
    slot_LoadConfigFile(_config);
}

QCPF_ViewModel::QCPF_ViewModel(QObject* parent, QString configDirPath, QString configFileName):_config(this)
{
    this->setParent(parent);

    _configDirPath = configDirPath;
    _configFileName = configFileName;

    if(_configDirPath.endsWith(QStringLiteral("/")))
        _configFullFilePath = _configDirPath + _configFileName;
    else
        _configFullFilePath = _configDirPath + QStringLiteral("/") + _configFileName;

    slot_LoadConfigFile(_config);
}

//*******************************************
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

int QCPF_ViewModel::compareFiles(QString filePath1, QString filePath2)
{
    QByteArray tbFile1 = filePath1.toLatin1();
    QByteArray tbFile2 = filePath2.toLatin1();

    return CompareMsg(tbFile1.data(), tbFile2.data());
}

int QCPF_ViewModel::saveConfigFile(QString filePath)
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

int QCPF_ViewModel::slot_LoadConfigFile(viewConfigModel &config)
{
    config.resetData();

    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    _outputInfo._content = tr("trying to read view config file...");
    emit sig_OutputInfo(_outputInfo);

    if(!QFile::exists(_configFullFilePath))
    {
        _outputInfo._type = InfoType::INFT_MSG_ERROR;
        _outputInfo._content = tr("view config file lost!");
        emit sig_OutputInfo(_outputInfo);
        return -1;
    }

    QFile file(_configFullFilePath);
    file.open(QIODevice::ReadOnly);
    QDataStream in(&file);
    in >> config;
    file.close();
    return 0;
}

int QCPF_ViewModel::slot_SaveConfigFile()
{
    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    _outputInfo._content = tr("trying to save config file.");
    emit sig_OutputInfo(_outputInfo);

    return saveConfigFile(_configFullFilePath);
}

int QCPF_ViewModel::slot_ApplyConfig()
{
    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    _outputInfo._content = tr("apply view config.");
    emit sig_OutputInfo(_outputInfo);

    QFileInfo tFi(_configFullFilePath);
    if(!tFi.exists())
        return -1;

    QString tempConfigFullFilePath = _configDirPath + QStringLiteral("temp_") + _configFileName;
    if(0!=saveConfigFile(tempConfigFullFilePath))
            return -1;

    if(0!=compareFiles(tempConfigFullFilePath, _configFullFilePath))
    {
        _outputInfo._type = InfoType::INFT_UI_UPDATE;
        _outputInfo._content = tr("trying to save config file.");
        emit sig_OutputInfo(_outputInfo);
    }
    return 0;
}

int QCPF_ViewModel::slot_CancelConfig()
{
    _outputInfo._type = InfoType::INFT_STATUS_INFO;
    _outputInfo._content = QStringLiteral("recover view config.");
    emit sig_OutputInfo(_outputInfo);

    QFileInfo tFi(_configFullFilePath);
    if(!tFi.exists())
        return -1;

    QString tempConfigFullFilePath = _configDirPath + QStringLiteral("temp_") + _configFileName;
    if(0!=saveConfigFile(tempConfigFullFilePath))
            return -1;

    if(0!=compareFiles(tempConfigFullFilePath, _configFullFilePath))
    {
        _config.resetData();
        slot_LoadConfigFile(_config);
    }
    return 0;
}

int QCPF_ViewModel::slot_Initialize(QString user, QString pwd, QString extInfo)
{
    _instCore = (QCPF_Model*)_core;
    if(user!="tt" || pwd!="1")
    {
        _outputInfo._type = InfoType::INFT_MSG_INFO;
        _outputInfo._content = tr("Please input the correct user name and password!") ;
        emit sig_OutputInfo(_outputInfo);
        return -1;
    }


    //invoke plugin functions
    foreach (PluginInterface* tp, _instCore->I_SysPlugins) {
        tp->ConnectViewModel(this);
        tp->OnViewModelInitialize();
    }
    foreach (PluginInterface* tp, _instCore->I_NSysAllValidPlugins) {
        tp->ConnectViewModel(this);
        tp->OnViewModelInitialize();
    }
    _outputInfo._type = InfoType::INFT_INITIALIZE_FINISHED;
    emit sig_OutputInfo(_outputInfo);

    return 0;
}

void QCPF_ViewModel::parseMenu(QMenu* nMenu, JMenuNode* nNode)
{
    if(nNode->_children.count()==0)
    {
        if(nNode->_menuIsSeprator)//判断是否为分隔符
        {
            nMenu->addSeparator();
        }
        else
        {
            QAction* tChildAction = new QAction();
            tChildAction->setObjectName(nNode->_functionName);

            tChildAction->setText(nNode->_menuTitle);
            tChildAction->setProperty("ItemActionName", nNode->_functionName);

            QKeySequence key(nNode->_menuShortCut);
            tChildAction->setShortcut(key);

            if(_instCore->I_CurrentUserInfo._authority <= nNode->_menuAuthority)
                tChildAction->setEnabled(true);
            else
                tChildAction->setEnabled(false);

            tChildAction->setCheckable(nNode->_menuCheckable);
            tChildAction->setIcon(QIcon(nNode->_menuIconPath));

            if(nNode->_pluginType == PT_SYS)//系统组件
            {
                foreach (PluginInterface* pi, _instCore->I_SysPlugins_Sel)
                {
                    if(pi->I_PluginID == nNode->_pluginID)
                    {
                        connect(tChildAction, &QAction::triggered, pi, &PluginInterface::slot_Action);
                        break;
                    }
                }
            }
            else
            {
                foreach (PluginInterface* pi, _instCore->I_NSysOrigPlugins_Sel)
                {
                    if(pi->I_PluginID == nNode->_pluginID)
                    {
                        connect(tChildAction, &QAction::triggered, pi, &PluginInterface::slot_Action);
                        break;
                    }
                }
            }

            _actionList.append(tChildAction);
            nMenu->addAction(tChildAction);
        }
    }
    else
    {
        QMenu* childMenu = new QMenu(nNode->_menuShortCut, nMenu);
        childMenu->setTitle(nNode->_menuTitle);
        childMenu->setIcon(QIcon(nNode->_menuIconPath));
        nMenu->addMenu(childMenu);

        if(_instCore->I_CurrentUserInfo._authority == nNode->_menuAuthority)
            childMenu->setEnabled(true);
        else
            childMenu->setEnabled(false);

        for(int i=0; i<nNode->_children.count(); i++)
        {
            JMenuNode* childNode = nNode->_children[i];
            //递归
            parseMenu(childMenu, childNode);
        }
    }
}

void QCPF_ViewModel::InitUIFromConfig(QMainWindow* viewHost)
{
    _mainMenubar = new QMenuBar(viewHost);
    _mainMenubar->setObjectName(QString::fromUtf8("menuMain"));
    _mainMenubar->setGeometry(QRect(0, 0, 1024, 23));
    viewHost->setMenuBar(_mainMenubar);

    for(int i=0; i<_config._toolBarLst.count(); i++)
    {
        QToolBar* _tToolbar = new QToolBar((QWidget*)viewHost);
        _tToolbar->setObjectName(QString(tr("Bar%1")).arg(i+1));
        _tToolbar->setMinimumSize(QSize(0, 0));
        _tToolbar->setIconSize(QSize(32, 32));

        _mainToolbarLst.append(_tToolbar);
        viewHost->addToolBar(Qt::TopToolBarArea, _tToolbar);
    }

    _mainStatusbar = new QStatusBar(viewHost);
    _mainStatusbar->setObjectName(QString::fromUtf8("statusBarMain"));
    _mainStatusbar->setStyleSheet(QString::fromUtf8(""));
    _mainStatusbar->setSizeGripEnabled(true);
    viewHost->setStatusBar(_mainStatusbar);

    _mainMenubar->clear();
    removeWidgetsFromStatusBar(_mainStatusbar);

    //======================
    drawMenuFromConfig(_mainMenubar);
    drawToolBarFromConfig(_mainToolbarLst);
    drawStatusBarFromConfig(_mainStatusbar);
    drawDockWidgetFromConfig(viewHost);
}

void QCPF_ViewModel::drawMenuFromConfig(QMenuBar* mainMenu)
{
    for(int i=0; i<_config._menuTopItemLst.count(); i++)
    {
        QAction* tAction = new QAction();

        tAction->setText(_config._menuTopItemLst[i]->_menuTitle);

        //一级菜单一定是QMenu,二级菜单及以上，如果是最后一级，则直接是QAction，如果还有子菜单，则该项必须是QMenu容器，然后下面才是QAction
        QMenu* tTopMenu = new QMenu(mainMenu);
        tTopMenu->setTitle(_config._menuTopItemLst[i]->_menuTitle);

        if(_instCore->I_CurrentUserInfo._authority <= _config._menuTopItemLst[i]->_menuAuthority)
            tTopMenu->setEnabled(true);
        else
            tTopMenu->setEnabled(false);

        tTopMenu->setIcon(QIcon(_config._menuTopItemLst[i]->_menuIconPath));

        mainMenu->addMenu(tTopMenu);

        for(int j=0; j<_config._menuTopItemLst[i]->_children.count(); j++)
        {
            parseMenu(tTopMenu, _config._menuTopItemLst[i]->_children[j]);
        }
    }
}

void QCPF_ViewModel::drawToolBarFromConfig(QList<QToolBar*> mainToolbarLst)
{
    for(int i=0; i<_config._toolBarLst.count(); i++)
    {
        mainToolbarLst[i]->clear();

        for(int j=0; j<_config._toolBarLst[i]->_toolBarItemList.count(); j++)
        {
            if(_config._toolBarLst[i]->_toolBarItemList[j]->_type == TP_SEPERATOR)//Seperator
            {
                mainToolbarLst[i]->addSeparator();
            }
            else if(_config._toolBarLst[i]->_toolBarItemList[j]->_type == TP_WIDGET)//"Widget"
            {
                QString pluginType = _config._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_pluginType==0?tr("System"):tr("NonSystem");
                QString pluginID = _config._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_pluginID;
                QString copyID = _config._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_copyID;
                QString widgetObjectName = _config._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_widgetObjectName;

                QList<PluginInterface*> tPluginLst;
                if(pluginType == "System")
                    tPluginLst = ((QCPF_Model*)_core)->I_SysPlugins_Sel;
                else
                    tPluginLst = ((QCPF_Model*)_core)->I_NSysAllValidPlugins;

                foreach (PluginInterface* pi, tPluginLst) {
                    if(pi->I_PluginID == pluginID && pi->I_CopyID == copyID)
                    {
                        foreach (PluginWidgetInfo* pwi, pi->I_WidgetList) {
                            if(pwi->_widget->objectName() == widgetObjectName)
                            {
                                pwi->_widget->setFixedSize(QSize(pwi->_origWidth,pwi->_origHeight));
                                mainToolbarLst[i]->addWidget(pwi->_widget);
                                mainToolbarLst[i]->repaint();
                                break;
                            }
                        }
                        break;
                    }
                }
            }
            else if(_config._toolBarLst[i]->_toolBarItemList[j]->_type == TP_ACTION)//"Action"
            {
                foreach (QAction* act, _actionList) {
                    if(act->objectName() ==_config._toolBarLst[i]->_toolBarItemList[j]->_actionItem->_actionObjectName)
                    {
                        mainToolbarLst[i]->addAction(act);
                        break;
                    }
                }
            }
        }
    }
}

void QCPF_ViewModel::drawStatusBarFromConfig(QStatusBar* mainStatusbar)
{
    for(int i=0; i<_config._statusBarItemLst.count(); i++)
    {
            QString pluginType = _config._statusBarItemLst[i]->_pluginType==0?tr("System"):tr("NonSystem");
            QString pluginID = _config._statusBarItemLst[i]->_pluginID;
            QString copyID = _config._statusBarItemLst[i]->_copyID;
            QString widgetObjectName = _config._statusBarItemLst[i]->_widgetObjectName;

            QList<PluginInterface*> tPluginLst;
            if(pluginType == "System")
                tPluginLst = ((QCPF_Model*)_core)->I_SysPlugins_Sel;
            else
                tPluginLst = ((QCPF_Model*)_core)->I_NSysAllValidPlugins;

            foreach (PluginInterface* pi, tPluginLst) {
                if(pi->I_PluginID == pluginID && pi->I_CopyID == copyID)
                {
                    foreach (PluginWidgetInfo* pwi, pi->I_WidgetList) {
                        if(pwi->_widget->objectName() == widgetObjectName)
                        {
                            pwi->_widget->setFixedSize(QSize(pwi->_origWidth,pwi->_origHeight));
                            mainStatusbar->addWidget(pwi->_widget);
                            _widgetLst_Statusbar.append(pwi->_widget);
                            mainStatusbar->repaint();
                            break;
                        }
                    }
                    break;
                }
            }
    }
}

void QCPF_ViewModel::removeWidgetsFromStatusBar(QStatusBar* mainStatusbar)
{
    foreach(QWidget* wid, _widgetLst_Statusbar)
    {
        mainStatusbar->removeWidget(wid);
    }
}

void QCPF_ViewModel::drawDockWidgetFromConfig(QMainWindow* viewHost)
{
    foreach (WidgetItem* wi, _config._workspaceWidgetLst) {

        if(!wi->_isVisible)
            continue;

        QList<PluginInterface*> tPluginLst;
        if(wi->_pluginType == PT_SYS)
            tPluginLst = ((QCPF_Interface*)_core)->I_SysPlugins;
        else
            tPluginLst = ((QCPF_Interface*)_core)->I_NSysAllValidPlugins;

        foreach (PluginInterface* pi, tPluginLst) {
            if(pi->I_PluginType == wi->_pluginType &&
               pi->I_PluginID == wi->_pluginID &&
               pi->I_CopyID == wi->_copyID)
                foreach (PluginWidgetInfo* pwi, pi->I_WidgetList) {
                    if(pwi->_widget->objectName() == wi->_widgetObjectName)
                    {
                        QString tDockWidgetObjectName = wi->_pluginID + "_" + wi->_copyID + "_" + wi->_widgetObjectName;
                        QDockWidget *tDw = new QDockWidget(pwi->_widget->windowTitle());

                        tDw->setObjectName(tDockWidgetObjectName);//要想存储布局，每个dock必须有唯一的objectName
                        tDw->setFeatures(QDockWidget::DockWidgetMovable|QDockWidget::DockWidgetFloatable); //具有全部特性
                        tDw->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
                        tDw->setStyleSheet("border:1px solid #ccc;");

                        tDw->setWidget(pwi->_widget);
                        tDw->setVisible(true);
                        viewHost->addDockWidget(Qt::RightDockWidgetArea,tDw);
                    }
                }
        }

    }
}

