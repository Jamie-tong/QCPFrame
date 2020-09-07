#include "wdt_hud.h"
#include "ui_wdt_hud.h"

wdt_Hud::wdt_Hud(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wdt_Hud)
{
    ui->setupUi(this);
}

wdt_Hud::~wdt_Hud()
{
    delete ui;
}
