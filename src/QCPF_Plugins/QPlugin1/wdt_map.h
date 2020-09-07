#ifndef WDT_MAP_H
#define WDT_MAP_H

#include <QWidget>

namespace Ui {
class wdt_Map;
}

class wdt_Map : public QWidget
{
    Q_OBJECT

public:
    explicit wdt_Map(QWidget *parent = nullptr);
    ~wdt_Map();

private:
    Ui::wdt_Map *ui;
};

#endif // WDT_MAP_H
