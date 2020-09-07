#include "sumwidgetfortoolbar.h"
#include "ui_sumwidgetfortoolbar.h"

SumWidgetForToolbar::SumWidgetForToolbar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SumWidgetForToolbar)
{
    ui->setupUi(this);
}

SumWidgetForToolbar::~SumWidgetForToolbar()
{
    delete ui;
}

void SumWidgetForToolbar::on_spinBox1_valueChanged(int arg1)
{
    ui->spinBoxEnd->setValue(ui->spinBox1->value()+ui->spinBox2->value());
}

void SumWidgetForToolbar::on_spinBox2_valueChanged(int arg1)
{
    ui->spinBoxEnd->setValue(ui->spinBox1->value()+ui->spinBox2->value());
}
