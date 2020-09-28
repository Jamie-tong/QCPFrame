#ifndef WDT_AREACHART_H
#define WDT_AREACHART_H

#include <QWidget>

namespace Ui {
class wdt_AreaChart;
}

class wdt_AreaChart : public QWidget
{
    Q_OBJECT

public:
    explicit wdt_AreaChart(QWidget *parent = nullptr);
    ~wdt_AreaChart();

private:
    Ui::wdt_AreaChart *ui;
};

#endif // WDT_AREACHART_H
