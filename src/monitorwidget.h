#ifndef MONITORWIDGET_H
#define MONITORWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QListWidget>
#include <QListWidgetItem>
#include <QStringList>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QString>
#include <QStackedWidget>

#include "../component/cpufmwidget.h"
#include "../component/fanwidget.h"
#include "../component/temperature.h"

class Temperature;
class CpuFmwidget;
class Fanwidget;

class Monitorwidget : public QWidget
{
    Q_OBJECT
public:
    explicit Monitorwidget(QWidget *parent = nullptr);
    ~Monitorwidget();
    void InitUI();

    void set_governer_list(QStringList list);
    void set_cur_governer(QString string);

    void set_temperature(bool f);
    void set_fan(bool f);
    void set_cpuFm(bool f);
    void RefreshCPUFMCheckStatus();
    void set_cpuFreqRange(QMap<QString, QVariant> cpuFreqRange);
signals:
    void requestcpuTemperature();
    void sendTemperaturedata(QMap<QString, QVariant> tmpMap);

    void requestcpurange();
    void onsendcpurangedata(QMap<QString, QVariant> tmpMap);

    void setCpuGoverner(QString);
    void RequestCPUFrequencyData();
    void SendCPUFrequencyData(QMap<QString, QVariant> tmpMap);

    void RequestFanInfoData();
    void SendFanInfoData(QMap<QString, QVariant> tmpMap);
private slots:
    void sendTemperaturesigle();
    void onsendTemperaturedata(QMap<QString, QVariant> tmpMap);

    void changewidgetpage(QListWidgetItem*);
    // void sendcpurangedata(QMap<QString, QVariant> tmpMap);
    // void gotCpuRange(QMap<QString,QVariant> tmpMap);

private:
    QSplitter *splitter;
    QHBoxLayout *main_layout;
    QListWidget *list_widget;
    QStringList string_list;
    QStringList status_list;
    QStackedWidget *stackedwidget;
    Temperature *temperature;
    Fanwidget *fan_widget;
    CpuFmwidget *cpu_fm;

    QStringList governer_list;
    QString cur_governer;
    QMap<QString, QVariant> m_cpuFreqRange;

    bool m_temperature = true;
    bool m_fan = true;
    bool m_cpufm = true;
};

#endif // MONITORWIDGET_H
