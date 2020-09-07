#ifndef WDT_HUD_H
#define WDT_HUD_H

#include <QWidget>

namespace Ui {
class wdt_Hud;
}

class wdt_Hud : public QWidget
{
    Q_OBJECT

public:
    explicit wdt_Hud(QWidget *parent = nullptr);
    ~wdt_Hud();

private:
    Ui::wdt_Hud *ui;
};

#endif // WDT_HUD_H
