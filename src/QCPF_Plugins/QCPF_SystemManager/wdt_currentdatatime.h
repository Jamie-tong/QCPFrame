/*
Author : Jamie.Tong
QQ      : 260271262
Data    : 2020-09-07
License: GPL v3.0
*/

#ifndef STATUS_CURRENTDATATIME_H
#define STATUS_CURRENTDATATIME_H

#include <QWidget>

namespace Ui {
class wdt_CurrentDataTime;
}

class wdt_CurrentDataTime : public QWidget
{
    Q_OBJECT

public:
    explicit wdt_CurrentDataTime(QWidget *parent = nullptr);
    ~wdt_CurrentDataTime();

private slots:
    void slot_OnTimer();
protected:
    void showEvent(QShowEvent *event);
private:
    QTimer* _timer;
    Ui::wdt_CurrentDataTime *ui;
};

#endif // STATUS_CURRENTDATATIME_H
