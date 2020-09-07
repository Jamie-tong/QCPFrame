#include "wdt_map.h"
#include "ui_wdt_map.h"

wdt_Map::wdt_Map(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wdt_Map)
{
    ui->setupUi(this);

    QPalette pal = this->palette();
    pal.setBrush(QPalette::Background, QBrush(QPixmap("G:/QCommonFrame/20200903/src/bin/debug/Images/hud.png")));
    setPalette(pal);
}

wdt_Map::~wdt_Map()
{
    delete ui;
}
