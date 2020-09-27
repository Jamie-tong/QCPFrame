#include "sumwidgetfortoolbar.h"
#include "ui_sumwidgetfortoolbar.h"

SumWidgetForToolbar::SumWidgetForToolbar(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SumWidgetForToolbar)
{
    ui->setupUi(this);

    setSpinQss(ui->spinBox1, "#DCE4EC", "#34495E");
    setSpinQss(ui->spinBox2, "#DCE4EC", "#34495E");
    setSpinQss(ui->spinBoxEnd, "#DCE4EC", "#34495E");
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


void SumWidgetForToolbar::setSpinQss(QSpinBox *txt, QString normalColor, QString focusColor)
{
    QStringList qss;
    qss.append(QString("QSpinBox{border-style:none;padding:6px;border-radius:5px;border:2px solid %1;}").arg(normalColor));
    qss.append(QString("QSpinBox:focus{border:2px solid %1;}").arg(focusColor));
    txt->setStyleSheet(qss.join(""));
}
