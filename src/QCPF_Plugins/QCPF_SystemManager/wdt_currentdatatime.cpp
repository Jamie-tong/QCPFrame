/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#include "wdt_currentdatatime.h"
#include "ui_wdt_currentdatatime.h"
#include <QTimer>
#include <QDateTime>

wdt_CurrentDataTime::wdt_CurrentDataTime(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wdt_CurrentDataTime)
{
    ui->setupUi(this);

    _timer = new QTimer(this);
    _timer->setInterval(1000);
    _timer->setSingleShot(false);
    connect(_timer, SIGNAL(timeout()), this, SLOT(slot_OnTimer()));
}

wdt_CurrentDataTime::~wdt_CurrentDataTime()
{
    delete ui;
}

void wdt_CurrentDataTime::showEvent(QShowEvent *event)
{
    _timer->start(1);
}

void wdt_CurrentDataTime::slot_OnTimer()
{
    QDateTime dt;
    ui->labDateTime->setText(dt.currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}
