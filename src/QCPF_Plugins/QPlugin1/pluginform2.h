#ifndef PLUGINFORM2_H
#define PLUGINFORM2_H

#include <QWidget>

namespace Ui {
class pluginform2;
}

class pluginform2 : public QWidget
{
    Q_OBJECT

public:
    explicit pluginform2(QWidget *parent = nullptr);
    ~pluginform2();

private:
    Ui::pluginform2 *ui;
};

#endif // PLUGINFORM2_H
