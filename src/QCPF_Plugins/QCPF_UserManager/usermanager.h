#ifndef USERMANAGER_H
#define USERMANAGER_H

#include <QDialog>
#include <QTableWidget>
#include "../../QCPF_Model/qcpf_model.h"
#include <QTimer>

namespace Ui {
class UserManager;
}

class UserManager : public QDialog
{
    Q_OBJECT

public:
    explicit UserManager(QCPF_Model* core, QWidget *parent = nullptr);
    ~UserManager();

private slots:
    void slot_OnULoaded();

    void on_btnAddUserInfo_clicked();

    void on_btnOk_clicked();

    void on_btnCancel_clicked();

    void on_btnReplaceUserInfo_clicked();

    void on_btnDeleteUserInfo_clicked();

    void on_tableUserInfo_itemClicked(QTableWidgetItem *item);

protected:
    void showEvent(QShowEvent *);

private:
    Ui::UserManager *ui;
    QCPF_Model *_core;
    QTimer* _timer;
    void setTableStyle(QTableWidget *table);


};

#endif // USERMANAGER_H
