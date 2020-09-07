#include "wdt_parampanel.h"
#include "ui_wdt_parampanel.h"

wdt_ParamPanel::wdt_ParamPanel(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wdt_ParamPanel)
{
    ui->setupUi(this);
}

wdt_ParamPanel::~wdt_ParamPanel()
{
    delete ui;
}
