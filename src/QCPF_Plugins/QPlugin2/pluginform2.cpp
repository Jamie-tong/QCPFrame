#include "pluginform2.h"
#include "ui_pluginform2.h"

#include <QTimer>

pluginform2::pluginform2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pluginform2)
{
    ui->setupUi(this);

    //设置表头颜色
    ui->tableWidget->horizontalHeader()->setStyleSheet("QHeaderView::section{color:black; border:1px gray;background-color:lightgray;font:9pt '微软雅黑';padding:5px;min-height:1em;}");
    ui->tableWidget->horizontalHeader()->setDefaultAlignment (Qt::AlignLeft | Qt::AlignVCenter); //居左
   //设置相邻行颜色交替显示
    ui->tableWidget->setAlternatingRowColors(true);
    //垂直表头不显示
    ui->tableWidget->verticalHeader()->setVisible(false);

    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);

    ui->tableWidget->horizontalHeader()->setHighlightSections(false);//取消表头的在选中单元格时的高亮状态。
    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);//设为不可编辑
    ui->tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    ui->tableWidget->setSelectionMode( QAbstractItemView::SingleSelection);//设置选中单个
    ui->tableWidget->horizontalHeader()->setStretchLastSection(true);//最后一列自动调整列宽
    ui->tableWidget->setStyleSheet("font:9pt '微软雅黑';");

    ui->tableWidget->setSortingEnabled(false);

    //注册面板显示后的信号槽
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
    //如果不是第一次显示
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
