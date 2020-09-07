#ifndef SUMWIDGETFORTOOLBAR_H
#define SUMWIDGETFORTOOLBAR_H

#include <QWidget>

namespace Ui {
class SumWidgetForToolbar;
}

class SumWidgetForToolbar : public QWidget
{
    Q_OBJECT

public:
    explicit SumWidgetForToolbar(QWidget *parent = nullptr);
    ~SumWidgetForToolbar();

private slots:
    void on_spinBox1_valueChanged(int arg1);

    void on_spinBox2_valueChanged(int arg1);

private:
    Ui::SumWidgetForToolbar *ui;
};

#endif // SUMWIDGETFORTOOLBAR_H
