#include "pluginform2.h"
#include "ui_pluginform2.h"

#include <QTimer>

pluginform2::pluginform2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pluginform2)
{
    ui->setupUi(this);

    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{color:black; border:1px gray;background-color:lightgray;font:9pt '微软雅黑';padding:5px;min-height:1em;}");
    ui->tableWidget->horizontalHeader()->setDefaultAlignment (Qt::AlignLeft | Qt::AlignVCenter);

    ui->tableWidget->setAlternatingRowColors(true);

    ui->tableWidget->verticalHeader()->setVisible(false);

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->tableWidget->horizontalHeader()->setHighlightSections(false);
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableWidget->setSelectionMode( QAbstractItemView::SingleSelection);
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);
    ui->tableWidget->setStyleSheet("font:9pt '微软雅黑';");

    ui->tableWidget->setSortingEnabled(false);

    _timer = new QTimer(this);
    _timer->setSingleShot(true);
    connect(_timer, SIGNAL(timeout()), this, SLOT(slot_OnULoaded()));
}

pluginform2::~pluginform2()
{
    delete ui;
}

void pluginform2::resizeEvent(QResizeEvent *event)
{
    if(!_isFirstResize)
        return;
    else
        _isFirstResize = false;
}

void pluginform2::showEvent(QShowEvent *event)
{
    _timer->start(1);
}

void pluginform2::slot_OnULoaded()
{

}
