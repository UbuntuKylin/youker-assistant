#include "chartwidget.h"
#include <QtCharts/QAbstractAxis>
#include <QtCharts/QSplineSeries>
#include <QtCharts/QValueAxis>
#include <QtCore/QRandomGenerator>
#include <QtCore/QDebug>
#include <QCategoryAxis>
#include <QAreaSeries>

Chart::Chart(QGraphicsItem *parent, Qt::WindowFlags wFlags):
    QChart(QChart::ChartTypeCartesian, parent, wFlags),
    m_series(0),
    m_axisX(new QCategoryAxis()),
    m_axisY(new QValueAxis()),
    m_step(0),
    m_x(0),
    m_y(0)
{
    QObject::connect(&m_timer, &QTimer::timeout, this, &Chart::handleTimeout);
    m_timer.setInterval(1000);

    q.clear();
    m_series = new QLineSeries(this);
    QPen green(Qt::red);
    green.setWidth(1);
    m_series->setPen(green);
    m_series->append(m_x, m_y);

    m_series1 = new QLineSeries(this);
    QPen green1(Qt::red);
    green1.setWidth(1);
    m_series1->setPen(green1);
    m_series1->append(m_x, m_y);

    series = new QAreaSeries();
    series->setName("Batman");
    QPen pen(0x059605);
    pen.setWidth(1);
    series->setPen(pen);
    series->setBrush(QBrush(Qt::blue));

    series->setUpperSeries(m_series);
    series->setLowerSeries(m_series1);

    addSeries(series);
//    addSeries(m_series1);

    m_axisX = new QCategoryAxis();
    m_axisX->setMin(0);
    m_axisX->setMax(120);
    m_axisX->append(tr("two minute"), 60);
    m_axisX->append(tr("one minute"), 120);
    addAxis(m_axisX,Qt::AlignBottom);
    addAxis(m_axisY,Qt::AlignLeft);
    m_series->attachAxis(m_axisX);
    m_series->attachAxis(m_axisY);
    m_series1->attachAxis(m_axisX);
    m_series1->attachAxis(m_axisY);
    series->attachAxis(m_axisX);
    series->attachAxis(m_axisY);
    m_axisY->setRange(30, 90);
    m_axisY->setTickCount(7);

    setPlotAreaBackgroundPen(QPen(0x059605));
    setPlotAreaBackgroundBrush(QBrush(Qt::white));

    m_timer.start();
}

Chart::~Chart()
{
    while (!q.isEmpty())
        q.dequeue();
}

qreal Chart::getCpuTemperature()
{
    return this->m_y;
}

void Chart::handleTimeout()
{
    emit this->requestCpuTemperature();
    emit this->refreshlablesignals(this->m_y);

    QList<QPointF> list;
    QList<QPointF> list1;
    QQueue<qreal> tag;
    tag.clear();
    tag=q;
    if(!tag.isEmpty())
    {
        for (int i = 0; i < tag.size(); ++i) {
            QPointF pointf;
            QPointF pointf1;
            pointf.setX(i);
            pointf.setY(tag.dequeue());

            pointf1.setX(i);
            pointf1.setY(30);
            list.append(pointf);
            list1.append(pointf1);
//            qDebug() << list1;
        }
    }

//    if(tag.size() < 60)
//    {
//        m_series->append(min, m_y);
//        min += 1;
//    }
//    if(tag.size() == 60)
//    {
        m_series->clear();
        m_series->replace(list);

        m_series1->clear();
        m_series1->replace(list1);


        series->setUpperSeries(m_series);
        series->setLowerSeries(m_series1);
//        m_series1->append(min, 35);
//               min += 1;

//    }

}

void Chart::receiverCpuTemperature(QMap<QString, QVariant> tmpMap)
{
//    qDebug() << Q_FUNC_INFO << tmpMap;
    QMap<QString, QVariant> cpu_info_map = tmpMap;
    if (!cpu_info_map.isEmpty()) {
        QMap<QString,QVariant>::iterator it;
        float m = 0;
        for ( it = cpu_info_map.begin(); it != cpu_info_map.end(); ++it ) {
            if (it.value().toString().length() > 0)
            {
                m += it.value().toString().toFloat();
//                qDebug()<< it.value().toString().toFloat() << cpu_info_map.count() << m;
            }
        }
        m = m/cpu_info_map.count();
        m_y = m;

        if(q.size() <= 240 )
        {
            q.enqueue(m);
        }
        else
        {
            q.dequeue();
            q.enqueue(m);
        }

//        qDebug()<< m <<q;
     }
}
