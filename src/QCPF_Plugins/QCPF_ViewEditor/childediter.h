#ifndef CHILDEDITER_H
#define CHILDEDITER_H

#include <QDialog>
#include "PluginIO.h"
#include "model/viewmodel.h"

namespace Ui {
class ChildEditer;
}

class ChildEditer : public QDialog
{
    Q_OBJECT

public:
    explicit ChildEditer(QCFModel* model, QWidget *parent = nullptr);
    ~ChildEditer();

private slots:
    void slot_OnULoaded();

private:
    Ui::ChildEditer *ui;
    QTimer* _timer;
    QCFModel* _core;
};

#endif // CHILDEDITER_H
