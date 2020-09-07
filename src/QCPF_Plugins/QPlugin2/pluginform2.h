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

protected:
    void resizeEvent(QResizeEvent *event);
    void showEvent(QShowEvent *event);

public slots:
    void slot_OnULoaded();

private:
    Ui::pluginform2 *ui;
    bool _isFirstResize = true;
    QTimer* _timer;
};

#endif // PLUGINFORM2_H
