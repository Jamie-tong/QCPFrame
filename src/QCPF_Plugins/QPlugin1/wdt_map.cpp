#include "wdt_map.h"
#include "ui_wdt_map.h"

wdt_Map::wdt_Map(QCPF_Interface* core, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wdt_Map)
{
    ui->setupUi(this);
    _core = core;

    QPalette pal = this->palette();

    QString imgPath = _core->I_ApplicationDirPath + "/Images/hud.png";
    pal.setBrush(QPalette::Background, QBrush(QPixmap(imgPath)));
    setPalette(pal);
}

wdt_Map::~wdt_Map()
{
    delete ui;
}
