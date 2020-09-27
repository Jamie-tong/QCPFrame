#ifndef WDT_SEARCH_H
#define WDT_SEARCH_H

#include <QWidget>
#include <QSpinBox>

namespace Ui {
class wdt_search;
}

class wdt_search : public QWidget
{
    Q_OBJECT

public:
    explicit wdt_search(QWidget *parent = nullptr);
    ~wdt_search();

private:
    Ui::wdt_search *ui;
    void setTextQss(QLineEdit *txt, QString normalColor, QString focusColor);
};

#endif // WDT_SEARCH_H
