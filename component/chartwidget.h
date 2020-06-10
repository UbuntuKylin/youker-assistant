#ifndef CHARTWIDGET_H
#define CHARTWIDGET_H

#include <QWidget>
#include <QtCharts/QChart>
#include <QtCore/QTimer>
#include <QQueue>


QT_CHARTS_BEGIN_NAMESPACE
class QSplineSeries;
class QLineSeries;
class QValueAxis;
class QCategoryAxis;
class QAreaSeries;
QT_CHARTS_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE

class Chart: public QChart
{
    Q_OBJECT
public:
    Chart(QGraphicsItem *parent = 0, Qt::WindowFlags wFlags = 0);
    virtual ~Chart();
    qreal getCpuTemperature();
signals:
    void requestCpuTemperature();
    void refreshlablesignals(qreal);

public slots:
    void handleTimeout();
    void receiverCpuTemperature(QMap<QString, QVariant> tmpMap);

private:
    QTimer m_timer;
    QLineSeries *m_series;
    QLineSeries *m_series1;
    QAreaSeries *series;
    QStringList m_titles;
//    QValueAxis *m_axisX;
    QCategoryAxis *m_axisX;
    QValueAxis *m_axisY;
    qreal min = 0;
    qreal m_step;
    qreal m_x;
    qreal m_y;
    QQueue<qreal> q;
};

#endif // CHARTWIDGET_H
