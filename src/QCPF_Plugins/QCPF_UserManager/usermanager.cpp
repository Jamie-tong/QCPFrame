#include "usermanager.h"
#include "ui_usermanager.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QJsonValue>
#include <QDebug>
#include <QDateTime>
#include <QMessageBox>

UserManager::UserManager(QCPF_Model* core, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::UserManager)
{
    ui->setupUi(this);
    _core = core;

    //去掉问号按钮
    setWindowFlags(Qt::Dialog
                   | Qt::WindowCloseButtonHint | Qt::WindowMaximizeButtonHint);

    //禁止调整大小
    QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
    sizePolicy.setHorizontalStretch(0);
    sizePolicy.setVerticalStretch(0);
    sizePolicy.setHeightForWidth(hasHeightForWidth());
    setSizePolicy(sizePolicy);
    setMinimumSize(QSize(770, 500));
    setMaximumSize(QSize(770, 500));
    setSizeGripEnabled(false);

    //注册面板显示后的信号槽
    _timer = new QTimer(this);
    _timer->setSingleShot(true);
    connect(_timer, SIGNAL(timeout()), this, SLOT(slot_OnULoaded()));
}

UserManager::~UserManager()
{
    delete ui;
}

void UserManager::showEvent(QShowEvent *event)
{
    _timer->start(1);
}

void UserManager::slot_OnULoaded()
{
    //--------------------------
    //设置原始组件信息列表样式
    //--------------------------
    QStringList nHeadLst;
    ui->tableUserInfo->setColumnCount(5);
    ui->tableUserInfo->setRowCount(0);

    ui->tableUserInfo->clear();
    //如果下面出现乱码，就把环境设置为：
    //1.工具->选项->默认编码->UTF-8;
    //2.工具->选项->UTF-8 BOM->如果编码是UTF-8则添加
    nHeadLst<<tr("No.")<<tr("User Name")<<tr("Password")<<tr("Authority")<<tr("Datetime");

    ui->tableUserInfo->setHorizontalHeaderLabels(nHeadLst);

    ui->tableUserInfo->setColumnWidth(0, 30);
    ui->tableUserInfo->setColumnWidth(1, 100);
    ui->tableUserInfo->setColumnWidth(2, 100);
    ui->tableUserInfo->setColumnWidth(3, 100);
    ui->tableUserInfo->setColumnWidth(4, 100);

    setTableStyle(ui->tableUserInfo);

    foreach (UserInfo* uInfo, _core->I_UserInfoLst) {
        int tRowCount = ui->tableUserInfo->rowCount();
        ui->tableUserInfo->insertRow(tRowCount);

        ui->tableUserInfo->setItem(tRowCount, 0, new QTableWidgetItem(QString::number(tRowCount+1)));
        ui->tableUserInfo->setItem(tRowCount, 1, new QTableWidgetItem(uInfo->_userName));
        ui->tableUserInfo->setItem(tRowCount, 2, new QTableWidgetItem(uInfo->_password));
        ui->tableUserInfo->setItem(tRowCount, 3, new QTableWidgetItem(QString::number(uInfo->_authority)));
        ui->tableUserInfo->setItem(tRowCount, 4, new QTableWidgetItem(uInfo->_createDatetime));
    }
}

void UserManager::on_btnAddUserInfo_clicked()
{
    if(ui->txtUserName->text()=="" || ui->txtPassword->text()=="")
    {
        QMessageBox::information(this, "info", "User Name or Password can not be null!");
        return;
    }

    for(int i=0; i<ui->tableUserInfo->rowCount(); i++)
    {
        if(ui->tableUserInfo->item(i, 1)->text() == ui->txtUserName->text())
        {
            QMessageBox::information(this, "info", "There is a same user existed!");
            return;
        }
    }

    int tRowCount = ui->tableUserInfo->rowCount();
    ui->tableUserInfo->insertRow(tRowCount);

    ui->tableUserInfo->setItem(tRowCount, 0, new QTableWidgetItem(QString::number(tRowCount+1)));
    ui->tableUserInfo->setItem(tRowCount, 1, new QTableWidgetItem(ui->txtUserName->text()));
    ui->tableUserInfo->setItem(tRowCount, 2, new QTableWidgetItem(ui->txtPassword->text()));
    ui->tableUserInfo->setItem(tRowCount, 3, new QTableWidgetItem(QString::number(ui->cbAuthority->currentIndex())));
    ui->tableUserInfo->setItem(tRowCount, 4, new QTableWidgetItem(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss")));
}

void UserManager::setTableStyle(QTableWidget *table)
{
    //设置表头颜色
    table->horizontalHeader()->setStyleSheet("QHeaderView::section{color:black; border:1px gray;background-color:lightgray;font:9pt '微软雅黑';padding:5px;min-height:1em;}");
    table->horizontalHeader()->setDefaultAlignment (Qt::AlignLeft | Qt::AlignVCenter); //居左
   //设置相邻行颜色交替显示
    table->setAlternatingRowColors(true);
    //垂直表头不显示
    table->verticalHeader()->setVisible(false);
    //水平表头显示
    table->horizontalHeader()->setVisible(true);

    table->horizontalHeader()->setStretchLastSection(true);

    table->horizontalHeader()->setHighlightSections(false);//取消表头的在选中单元格时的高亮状态。
    table->setEditTriggers(QAbstractItemView::NoEditTriggers);//设为不可编辑
    table->setSelectionBehavior(QAbstractItemView::SelectRows);//设置选中模式为选中行
    table->setSelectionMode( QAbstractItemView::SingleSelection);//设置选中单个
    table->horizontalHeader()->setStretchLastSection(true);//最后一列自动调整列宽
    table->setStyleSheet("font:9pt '微软雅黑';");

    table->setSortingEnabled(false);
}

void UserManager::on_btnOk_clicked()
{
    QFile file(_core->I_ApplicationDirPath + "/Data/User/Users.json");
    if(!file.open(QIODevice::ReadWrite)) {
        qDebug() << "File open error";
    } else {
        qDebug() <<"File open!";
    }

    QJsonArray jsonArray;
    for(int i = 0; i< ui->tableUserInfo->rowCount();i++)
    {
        QJsonObject jsonObject;
        jsonObject.insert("Datetime", ui->tableUserInfo->item(i, 4)->text());
        jsonObject.insert("Authority", ui->tableUserInfo->item(i, 3)->text());
        jsonObject.insert("Password", ui->tableUserInfo->item(i, 2)->text());
        jsonObject.insert("UserName", ui->tableUserInfo->item(i, 1)->text());
        jsonArray.append(jsonObject);
    }

    QJsonObject jsonObject;
    jsonObject.insert("Users", jsonArray);
    jsonArray.append(jsonObject);
    QJsonDocument jsonDoc;
    jsonDoc.setObject(jsonObject);
    file.write(jsonDoc.toJson());
    file.close();

    this->close();
}

void UserManager::on_btnCancel_clicked()
{
    this->close();
}

void UserManager::on_btnReplaceUserInfo_clicked()
{
    int tRowIndex = ui->tableUserInfo->currentRow();
    if(tRowIndex<0)
        return;

    ui->tableUserInfo->item(tRowIndex, 1)->setText(ui->txtUserName->text());
    ui->tableUserInfo->item(tRowIndex, 2)->setText(ui->txtPassword->text());
    ui->tableUserInfo->item(tRowIndex, 3)->setText(QString::number(ui->cbAuthority->currentIndex()));
    ui->tableUserInfo->item(tRowIndex, 4)->setText(QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss"));
}

void UserManager::on_btnDeleteUserInfo_clicked()
{
    int tRowIndex = ui->tableUserInfo->currentRow();
    if(tRowIndex<0)
        return;

    ui->tableUserInfo->removeRow(tRowIndex);
}

void UserManager::on_tableUserInfo_itemClicked(QTableWidgetItem *item)
{
    if(item==nullptr)
        return;

    ui->txtUserName->setText(ui->tableUserInfo->item(item->row(), 1)->text());
    ui->txtPassword->setText(ui->tableUserInfo->item(item->row(), 2)->text());
    ui->cbAuthority->setCurrentIndex(ui->tableUserInfo->item(item->row(), 3)->text().toInt());
}
