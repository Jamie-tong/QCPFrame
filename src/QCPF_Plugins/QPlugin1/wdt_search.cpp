#include "wdt_search.h"
#include "ui_wdt_search.h"

wdt_search::wdt_search(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wdt_search)
{
    ui->setupUi(this);

    setTextQss(ui->lineEdit, "#DCE4EC", "#34495E");
}

wdt_search::~wdt_search()
{
    delete ui;
}

void wdt_search::setTextQss(QLineEdit *txt, QString normalColor, QString focusColor)
{
    QStringList qss;
    qss.append(QString("QLineEdit{border-style:none;padding:6px;border-radius:5px;border:2px solid %1;}").arg(normalColor));
    qss.append(QString("QLineEdit:focus{border:2px solid %1;}").arg(focusColor));
    txt->setStyleSheet(qss.join(""));
}
