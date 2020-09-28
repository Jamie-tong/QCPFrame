#ifndef WDT_CUSTOMCHART_H
#define WDT_CUSTOMCHART_H

#include <QWidget>

namespace Ui {
class wdt_ZoomChart;
}

class wdt_ZoomChart : public QWidget
{
    Q_OBJECT

public:
    explicit wdt_ZoomChart(QWidget *parent = nullptr);
    ~wdt_ZoomChart();

private:
    Ui::wdt_ZoomChart *ui;
};

#endif // WDT_CUSTOMCHART_H
