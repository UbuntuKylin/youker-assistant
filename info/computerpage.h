/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef COMPUTERPAGE_H
#define COMPUTERPAGE_H

#include <QWidget>
#include <QMap>
#include <QVariant>
#include "../dbusproxy/youkersessiondbus.h"
#include "../dbusproxy/youkersystemdbus.h"

class QLabel;
class QComboBox;
class QRadioButton;
class QGroupBox;
class QFormLayout;
class QHBoxLayout;

class ComputerPage : public QWidget
{
    Q_OBJECT
public:
    explicit ComputerPage(QWidget *parent = 0, QString title = "computer"/*, QString manufacturer = "UbuntuKylin"*/);
    ~ComputerPage();
    void setLanguage();
    int page_height;
    void initUI(bool cpu);
    void setMap(QMap<QString ,QVariant> tmp, const QString &manufacturer) {
        info_map = tmp;
        vendor = manufacturer;
    }
    void setsensor(bool flag) {
        sensor = flag;
    }
    void setSystemDbusProxy(SystemDispatcher* dispatcher) { systemProxy = dispatcher;}
    QString translatorSwitch(QString orgStr);
    void resetTimeValue(QString value);
    void resetSensor(QMap<QString, QVariant> sensormap);

public slots:
    void setRadioButtonRowStatus();

private:
    QString title_context;
    QLabel *title_label;
    QString vendor;
//    void resizeEvent(QResizeEvent *);
    QMap<QString ,QVariant> info_map;
    QLabel *logo_label;
    QLabel *time_label;
    QGroupBox *group_box;
    QFormLayout *form_layout;
    bool sensor;
    QRadioButton *ondemand_radio;
    QRadioButton *powersave_radio;
    QRadioButton *performance_radio;
    SystemDispatcher *systemProxy;
    QHBoxLayout *layout;

    QLabel *in0_label;
    QLabel *in2_label;
    QLabel *in3_label;
    QLabel *in5_label;
    QLabel *in6_label;
    QLabel *tr1_label;
    QLabel *tr2_label;
    QLabel *tr3_label;
    QLabel *tr4_label;
    QLabel *tr5_label;
    QLabel *tr6_label;
    QLabel *fanin1_label;
    QList<QLabel *> label_list;
 /*
    else if(orgStr == "IN0")//内存参考电压
        return tr("Memory reference voltage");
    else if(orgStr == "IN2")//SATA控制器电压
        return tr("SATA controller voltage");
    else if(orgStr == "IN3")//内存电压
        return tr("Memory voltage");
    else if(orgStr == "IN5")//CPU管脚电压
        return tr("CPU pin voltage");
    else if(orgStr == "IN6")//桥片电压
        return tr("Bridge voltage");
    else if(orgStr == "TR4")//CPU核电压
        return tr("CPU core voltage");
    else if(orgStr == "TR5")//CPU温度
        return tr("CPU temperature");
    else if(orgStr == "TR6")//主板温度
        return tr("Motherboard temperature");
    else if(orgStr == "FANIN1")//CPU风扇转速
        return tr("CPU fan speed");
//    ATX_3V3    TR1
//    ATX_5V    TR2
//    ATX_12V   TR3*/
};

#endif // COMPUTERPAGE_H
