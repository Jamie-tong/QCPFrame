#include "pluginform2.h"
#include "ui_pluginform2.h"

pluginform2::pluginform2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::pluginform2)
{
    ui->setupUi(this);
}

pluginform2::~pluginform2()
{
    delete ui;
}
