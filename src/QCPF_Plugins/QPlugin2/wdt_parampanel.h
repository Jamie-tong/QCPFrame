#ifndef WDT_PARAMPANEL_H
#define WDT_PARAMPANEL_H

#include <QWidget>

namespace Ui {
class wdt_ParamPanel;
}

class wdt_ParamPanel : public QWidget
{
    Q_OBJECT

public:
    explicit wdt_ParamPanel(QWidget *parent = nullptr);
    ~wdt_ParamPanel();

private:
    Ui::wdt_ParamPanel *ui;
};

#endif // WDT_PARAMPANEL_H
