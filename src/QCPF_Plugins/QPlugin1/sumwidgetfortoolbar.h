#ifndef SUMWIDGETFORTOOLBAR_H
#define SUMWIDGETFORTOOLBAR_H

#include <QWidget>
#include <QSpinBox>

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
    void setSpinQss(QSpinBox *txt, QString normalColor, QString focusColor);
};

#endif // SUMWIDGETFORTOOLBAR_H
