#include "wdt_zoomchart.h"
#include "ui_wdt_zoomchart.h"

#include "chart.h"
#include "chartview.h"
#include <QtCore/QtMath>
#include <QtCore/QRandomGenerator>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

QT_CHARTS_USE_NAMESPACE

wdt_ZoomChart::wdt_ZoomChart(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::wdt_ZoomChart)
{
    ui->setupUi(this);

    //![1]
        QLineSeries *series = new QLineSeries();
        for (int i = 0; i < 500; i++) {
            QPointF p((qreal) i, qSin(M_PI / 50 * i) * 100);
            p.ry() += QRandomGenerator::global()->bounded(20);
            *series << p;
        }
    //![1]

        Chart *chart = new Chart();
        chart->addSeries(series);
        chart->setTitle("Zoom in/out example");
        chart->setAnimationOptions(QChart::SeriesAnimations);
        chart->legend()->hide();
        chart->createDefaultAxes();

        ChartView *chartView = new ChartView(chart);
        chartView->setRenderHint(QPainter::Antialiasing);

    ui->gridLayout->addWidget(chartView);
    this->grabGesture(Qt::PanGesture);
    this->grabGesture(Qt::PinchGesture);
}

wdt_ZoomChart::~wdt_ZoomChart()
{
    delete ui;
}
