#ifndef WDT_MAP_H
#define WDT_MAP_H

#include <QWidget>
#include "../../../interface/hostinterface.h"

namespace Ui {
class wdt_Map;
}

class wdt_Map : public QWidget
{
    Q_OBJECT

public:
    explicit wdt_Map(QCPF_Interface* core, QWidget *parent = nullptr);
    ~wdt_Map();

private:
    Ui::wdt_Map *ui;
    QCPF_Interface* _core;
};

#endif // WDT_MAP_H
