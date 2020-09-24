#ifndef WDT_COREVERSION_H
#define WDT_COREVERSION_H

#include <QWidget>

namespace Ui {
class wdt_CoreVersion;
}

class wdt_CoreVersion : public QWidget
{
    Q_OBJECT

public:
    explicit wdt_CoreVersion(QWidget *parent = nullptr);
    ~wdt_CoreVersion();

private:
    Ui::wdt_CoreVersion *ui;
};

#endif // WDT_COREVERSION_H
