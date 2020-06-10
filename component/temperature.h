#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QFrame>
#include <QStackedWidget>
#include <QPixmap>
#include <QLabel>
#include <QListWidget>
#include <QStringList>
#include <QLabel>
#include <QSplitter>
#include <QStackedWidget>
#include <QListWidget>
#include <QtCharts/QChartView>

#include "../component/chartwidget.h"

class Chart;

class Temperature : public QWidget
{
    Q_OBJECT
public:
    explicit Temperature(QWidget *parent = nullptr);
    ~Temperature();

    void InitUI();
    void InitTopUI();
    void InitBottomUI();
signals:
    void requestTemperature();
    void sendTemperature(QMap<QString, QVariant> tmpMap);

private slots:
    void onsendTemperature(QMap<QString, QVariant> tmpMap);
    void sendrequest();
    void refreshlable(qreal);
private:
    QVBoxLayout *main_layout;
    QHBoxLayout *top_layout;
    QVBoxLayout *bottom_layout;
    QLabel *temperature_icon;
    QLabel *top_tip;
    QLabel *temperature_lable;
    QChartView *chartview;
    Chart *chart;
    qreal CpuTemperature;
};

#endif // TEMPERATURE_H
