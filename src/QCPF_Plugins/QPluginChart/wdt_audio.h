#ifndef WDT_AUDIO_H
#define WDT_AUDIO_H

#include <QWidget>

namespace Ui {
class wdt_Audio;
}

class wdt_Audio : public QWidget
{
    Q_OBJECT

public:
    explicit wdt_Audio(QWidget *parent = nullptr);
    ~wdt_Audio();

private:
    Ui::wdt_Audio *ui;
};

#endif // WDT_AUDIO_H
