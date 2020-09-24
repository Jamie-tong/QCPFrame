#ifndef WDT_VIEWVERSION_H
#define WDT_VIEWVERSION_H

#include <QWidget>

namespace Ui {
class wdt_ViewVersion;
}

class wdt_ViewVersion : public QWidget
{
    Q_OBJECT

public:
    explicit wdt_ViewVersion(QWidget *parent = nullptr);
    ~wdt_ViewVersion();

private:
    Ui::wdt_ViewVersion *ui;
};

#endif // WDT_VIEWVERSION_H
