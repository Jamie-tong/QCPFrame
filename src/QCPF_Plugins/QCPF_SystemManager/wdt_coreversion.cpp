#include "wdt_coreversion.h"
#include "ui_wdt_coreversion.h"
#include "PluginIO.h"

wdt_CoreVersion::wdt_CoreVersion(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wdt_CoreVersion)
{
    ui->setupUi(this);

    PluginIO* plugin = PluginIO::getInstance();

    ui->labCoreVersion->setText(plugin->_core->I_SystemVersion);
}

wdt_CoreVersion::~wdt_CoreVersion()
{
    delete ui;
}
