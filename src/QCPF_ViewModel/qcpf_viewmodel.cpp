/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "qcpf_viewmodel.h"
#include <QDataStream>
#include <QDir>
#include <QtWidgets/QMainWindow>
#include <QDockWidget>
#include <QMessageBox>


#define MASK_END_STR "_tp"
#define SYSTEM_VERSION "1.0.0.6"
#define ORGANIZATION_NAME "Jamie.T"

QCPF_ViewModel::QCPF_ViewModel(QCPF_Model* model, QObject* parent):_config(this)
{
    _version = SYSTEM_VERSION;
    _organization = ORGANIZATION_NAME;

    this->setParent(parent);
    _core = model;

    slot_LoadConfigFile(_config);
}

QCPF_ViewModel::QCPF_ViewModel(QCPF_Model* model, QObject* parent, QString configDirPath, QString configFileName):_config(this)
{
    _version = SYSTEM_VERSION;
    _organization = ORGANIZATION_NAME;

    this->setParent(parent);
    _core = model;

    _configDirPath = configDirPath;
    _configFileName = configFileName;

    if(_configDirPath.endsWith(QStringLiteral("/")))
        _configFullFilePath = _configDirPath + _configFileName;
    else
        _configFullFilePath = _configDirPath + QStringLiteral("/") + _configFileName;

    slot_LoadConfigFile(_config);
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
    _outputInfo._content = tr("Trying to read view config file...");
    emit sig_OutputInfo(_outputInfo);

    if(!QFile::exists(_configFullFilePath))
    {
        _outputInfo._type = InfoType::INFT_STATUS_INFO;
        _outputInfo._content = tr("The View config file lost!");
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

    QFileInfo tFi(_configFullFilePath);
    if(!tFi.exists())
        return -1;

    QString tempConfigFullFilePath = _configDirPath + QStringLiteral("temp_") + _configFileName;
    if(0!=saveConfigFile(tempConfigFullFilePath))
            return -2;

    if(0!=compareFiles(tempConfigFullFilePath, _configFullFilePath))
    {
        saveConfigFile(_configFullFilePath);
        _outputInfo._type = INFT_VIEW_CONFIG_CHANGED;
        emit sig_OutputInfo(_outputInfo);

        return 1;
    }
    return 0;
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
        _outputInfo._type = InfoType::INFT_VIEW_CONFIG_CHANGED;
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
        slot_LoadConfigFile(_config);
    }
    return 0;
}

int QCPF_ViewModel::slot_Initialize()
{
    try {
        slot_LoadConfigFile(_config);

        _outputInfo._type = InfoType::INFT_INITIALIZE_FINISHED;
        emit sig_OutputInfo(_outputInfo);
    } catch (int) {
        _outputInfo._type = InfoType::INFT_MSG_INFO;
        _outputInfo._content = tr("ViewModel Initialize failed!") ;
        emit sig_OutputInfo(_outputInfo);
        return -255;
    }

    return 0;
}

int QCPF_ViewModel::slot_InputInfo(tagOutputInfo& info)
{
    switch (info._type) {
        case InfoType::INFT_MSG_INFO:
                QMessageBox::information(_viewHost, info._title, info._content);
                break;
        case InfoType::INFT_MSG_WARN:
                QMessageBox::warning(_viewHost, info._title, info._content);
                break;
        case InfoType::INFT_MSG_ERROR:
                QMessageBox::critical(_viewHost, info._title, info._content);
                break;
        case InfoType::INFT_MSG_QUESTION:
                QMessageBox::question(_viewHost, info._title, info._content);
                break;
        case InfoType::INFT_APPLICATION_CLOSE:
                _viewHost->close();
                break;
        case InfoType::INFT_PLUGIN_COLLECT:
                _core->slot_Initialize();
            break;
        case InfoType::INFT_VIEW_CONFIG_CHANGED:
                //initUIFromConfig(_viewHost);
            break;
        case InfoType::INFT_STATUSBAR_TEMP:
                _mainStatusbar->showMessage(info._content, info._timeout);
            break;
    }

    return 0;
}

void QCPF_ViewModel::parseMenu(QMenu* nMenu, JMenuNode* nNode)
{
    if(nNode->_children.count()==0)
    {
        if(nNode->_menuIsSeprator)
        {
            nMenu->addSeparator();
        }
        else
        {
            QAction* tChildAction = new QAction();
            addActionToViewActionList(tChildAction, nNode->_actionName, nNode->_actionName, nNode->_menuShortCut, (AuthorityType)nNode->_menuAuthority, nNode->_menuCheckable, nNode->_menuIconPath, (PluginType)nNode->_pluginType, nNode->_pluginID);
            nMenu->addAction(tChildAction);
        }
    }
    else
    {
        QMenu* childMenu = new QMenu(nNode->_menuShortCut, nMenu);
        childMenu->setTitle(nNode->_menuTitle);

        QString finalIconPath;
        if(QFile::exists(nNode->_menuIconPath))
            finalIconPath = nNode->_menuIconPath;
        else
        {
            QFileInfo fInfo(nNode->_menuIconPath);
            QString tFileName = fInfo.fileName();
            if(QFile::exists(_core->I_ApplicationDirPath + "/Images/" + tFileName))
                finalIconPath = _core->I_ApplicationDirPath + "/Images/" + tFileName;
        }
        //--------------------------
        childMenu->setIcon(QIcon(finalIconPath));
        nMenu->addMenu(childMenu);

        if(_core->I_CurrentUserInfo._authority <= nNode->_menuAuthority)
            childMenu->setEnabled(true);
        else
            childMenu->setEnabled(false);

        for(int i=0; i<nNode->_children.count(); i++)
        {
            JMenuNode* childNode = nNode->_children[i];

            parseMenu(childMenu, childNode);
        }
    }
}

void QCPF_ViewModel::addActionToViewActionList(QAction* action, QString actionObjectName, QString actionText, QString shortcut, AuthorityType aType, bool isCheckable, QString iconPath, PluginType pType, QString pluginID)
{
    action->setObjectName(actionObjectName);

    action->setText(actionText);
    action->setProperty("ItemActionName", actionObjectName);

    QKeySequence key(shortcut);
    action->setShortcut(key);

    if(_core->I_CurrentUserInfo._authority <= aType)
        action->setEnabled(true);
    else
        action->setEnabled(false);

    action->setCheckable(isCheckable);

    QString finalIconPath;
    if(QFile::exists(iconPath))
        finalIconPath = iconPath;
    else
    {
        QFileInfo fInfo(iconPath);
        QString tFileName = fInfo.fileName();
        if(QFile::exists(_core->I_ApplicationDirPath + "/Images/" + tFileName))
            finalIconPath = _core->I_ApplicationDirPath + "/Images/" + tFileName;
    }
    //===========
    action->setIcon(QIcon(finalIconPath));

    if(pType == PT_SYS)
    {
        foreach (Plugin_Interface* pi, _core->I_SysPlugins_Sel)
        {
            if(pi->I_PluginID == pluginID)
            {
                connect(action, &QAction::triggered, pi, &Plugin_Interface::slot_Action);
                break;
            }
        }
    }
    else
    {
        foreach (Plugin_Interface* pi, _core->I_NSysOrigPlugins_Sel)
        {
            if(pi->I_PluginID == pluginID)
            {
                connect(action, &QAction::triggered, pi, &Plugin_Interface::slot_Action);
                break;
            }
        }
    }

    _actionList.append(action);
}

void QCPF_ViewModel::initUIFromConfig(QMainWindow* viewHost)
{
    _viewHost = viewHost;
    _mainMenubar = new QMenuBar(viewHost);
    _mainMenubar->setObjectName(QString::fromUtf8("menuMain"));
    _mainMenubar->setGeometry(QRect(0, 0, 1024, 23));
    viewHost->setMenuBar(_mainMenubar);

    for(int i=0; i<_config._toolBarLst.count(); i++)
    {
        QToolBar* _tToolbar = new QToolBar((QWidget*)viewHost);
        _tToolbar->setObjectName(QString(tr("Bar%1")).arg(i+1));
        _tToolbar->setWindowTitle(_config._toolBarLst[i]->_toolBarTitle);
        _tToolbar->setMinimumSize(_config._toolBarLst[i]->_IconSize);
        _tToolbar->setIconSize(_config._toolBarLst[i]->_IconSize);

        if(_config._toolBarLst[i]->_textStyle == BarItemSytle::BS_TEXT_BESIDE_ICON)
            _tToolbar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        else if(_config._toolBarLst[i]->_textStyle == BarItemSytle::BS_TEXT_UNDER_ICON)
            _tToolbar->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);

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

    viewHost->setStyleSheet("QMainWindow::separator{background:gray; width:1px; height:1px;}");

    QString _layoutIniFilePath = _core->I_ApplicationDirPath + "/Config/View/.Layout.ini";
    QFile file(_layoutIniFilePath);
    if (file.open(QIODevice::ReadOnly))
    {
        QByteArray ba;
        QDataStream in(&file);
        in >> ba;
        file.close();
        viewHost->restoreState(ba);
    }

    _mainMenubar->setVisible(_config._isEnable_ShowMenu);
    for(int i=0; i<_mainToolbarLst.count(); i++)
        _mainToolbarLst[i]->setVisible(_config._isEnable_ShowToolbar);
    _mainStatusbar->setVisible(_config._isEnable_ShowStatusbar);
}

void QCPF_ViewModel::drawMenuFromConfig(QMenuBar* mainMenu)
{
    for(int i=0; i<_config._menuTopItemLst.count(); i++)
    {
        QAction* tAction = new QAction();

        tAction->setText(_config._menuTopItemLst[i]->_menuTitle);

        QMenu* tTopMenu = new QMenu(mainMenu);
        tTopMenu->setTitle(_config._menuTopItemLst[i]->_menuTitle);

        if(_core->I_CurrentUserInfo._authority <= _config._menuTopItemLst[i]->_menuAuthority)
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
            if(_config._toolBarLst[i]->_toolBarItemList[j]->_type == BT_ACTION)//"Action"
            {
                foreach (QAction* act, _actionList) {
                    if(act->objectName() ==_config._toolBarLst[i]->_toolBarItemList[j]->_actionItem->_actionObjectName)
                    {
                        mainToolbarLst[i]->addAction(act);
                        break;
                    }
                }
            }
            else if(_config._toolBarLst[i]->_toolBarItemList[j]->_type == BT_WIDGET)//"Widget"
            {
                QString pluginType = _config._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_pluginType==0?tr("System"):tr("NonSystem");
                QString pluginID = _config._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_pluginID;
                QString copyID = _config._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_copyID;
                QString widgetObjectName = _config._toolBarLst[i]->_toolBarItemList[j]->_widgetItem->_widgetObjectName;

                QList<Plugin_Interface*> tPluginLst;
                if(pluginType == "System")
                    tPluginLst = _core->I_SysPlugins_Sel;
                else
                    tPluginLst = _core->I_NSysAllValidPlugins;

                foreach (Plugin_Interface* pi, tPluginLst) {
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
            else if(_config._toolBarLst[i]->_toolBarItemList[j]->_type == BT_SEPARATOR)//Separator
            {
                mainToolbarLst[i]->addSeparator();
            }
            else if(_config._toolBarLst[i]->_toolBarItemList[j]->_type == BT_SPACER)//Spacer
            {
                QWidget* spacer = new QWidget(_viewHost);
                spacer->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
                mainToolbarLst[i]->addWidget(spacer);
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

            QList<Plugin_Interface*> tPluginLst;
            if(pluginType == "System")
                tPluginLst = _core->I_SysPlugins_Sel;
            else
                tPluginLst = _core->I_NSysAllValidPlugins;

            foreach (Plugin_Interface* pi, tPluginLst) {
                if(pi->I_PluginID == pluginID && pi->I_CopyID == copyID)
                {
                    foreach (PluginWidgetInfo* pwi, pi->I_WidgetList) {
                        if(pwi->_widget->objectName() == widgetObjectName)
                        {
                            pwi->_widget->setFixedSize(QSize(pwi->_origWidth,pwi->_origHeight));

                            if(_config._statusBarItemLst[i]->_statusbarItemType == SBT_COMMON)
                                mainStatusbar->addWidget(pwi->_widget);
                            else if(_config._statusBarItemLst[i]->_statusbarItemType == SBT_PERMANENT)
                                mainStatusbar->addPermanentWidget(pwi->_widget);

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

        QList<Plugin_Interface*> tPluginLst;
        if(wi->_pluginType == PT_SYS)
            tPluginLst = _core->I_SysPlugins;
        else
            tPluginLst = _core->I_NSysAllValidPlugins;

        foreach (Plugin_Interface* pi, tPluginLst) {
            if(pi->I_PluginType == wi->_pluginType &&
               pi->I_PluginID == wi->_pluginID &&
               pi->I_CopyID == wi->_copyID)
                foreach (PluginWidgetInfo* pwi, pi->I_WidgetList) {
                    if(pwi->_widget->objectName() == wi->_widgetObjectName)
                    {
                        QString tDockWidgetObjectName = wi->_pluginID + "_" + wi->_copyID + "_" + wi->_widgetObjectName;
                        QDockWidget *tDw = new QDockWidget(pwi->_widget->windowTitle());

                        tDw->setObjectName(tDockWidgetObjectName);

                        QDockWidget::DockWidgetFeatures tFeatures = QDockWidget::NoDockWidgetFeatures;
                        if(_config._dock_Floatable)
                            tFeatures |= QDockWidget::DockWidgetFloatable;
                        if(_config._dock_Moveable)
                            tFeatures |= QDockWidget::DockWidgetMovable;
                        if(_config._dock_Closeable)
                            tFeatures |= QDockWidget::DockWidgetClosable;

                        tDw->setFeatures(tFeatures);
                        tDw->setAllowedAreas(Qt::AllDockWidgetAreas);
                        tDw->setStyleSheet("border:1px solid #ccc;");

                        tDw->setWidget(pwi->_widget);
                        viewHost->addDockWidget(Qt::RightDockWidgetArea,tDw);
                    }
                }
        }

    }
}

