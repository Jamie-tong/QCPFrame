#include "wdt_viewversion.h"
#include "ui_wdt_viewversion.h"
#include "PluginIO.h"
#include <QTimer>

wdt_ViewVersion::wdt_ViewVersion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wdt_ViewVersion)
{
    ui->setupUi(this);

    PluginIO* plugin = PluginIO::getInstance();
    QCPF_ViewModel* _view = (QCPF_ViewModel*)plugin->_core->_view;
    ui->labViewVersion->setText(_view->_version);
}

wdt_ViewVersion::~wdt_ViewVersion()
{
    delete ui;
}
