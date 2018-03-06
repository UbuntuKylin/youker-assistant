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

#include "energywidget.h"
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QSlider>
#include <QButtonGroup>

EnergyWidget::EnergyWidget(QStringList cpulist, QString cpu, QString cur_desktop, bool has_battery, QWidget *parent) :
    SettingModulePage(parent),desktop(cur_desktop)
{
    gamma_label = new QLabel();
    gamma_slider = new QDoubleSpinBox();
    gamma_slider->setButtonSymbols(QAbstractSpinBox::PlusMinus);
    gamma_slider->setSingleStep(0.1);
    gamma_slider->setMinimum(0.1);
    gamma_slider->setMaximum(1.0);

    brightness_label = new QLabel();
    brightness_value_label = new QLabel();
    brightness_slider = new QSlider(Qt::Horizontal);
    brightness_slider->setFocusPolicy(Qt::NoFocus);
    brightness_slider->setRange(1, 100);
    brightness_slider->setSingleStep(1);

    idle_delay_label = new QLabel();
    idle_delay_combo = new QComboBox();
    lock_enabled_label = new QLabel();
    lock_enabled_switch = new KylinSwitcher();
    lock_delay_label = new QLabel();
    lock_delay_combo = new QComboBox();

    critical_low_label = new QLabel();
    suspend_low_radio = new QRadioButton();
    shutdown_radio = new QRadioButton();
    QButtonGroup *btnGroup1 = new QButtonGroup();
    btnGroup1->addButton(suspend_low_radio);
    btnGroup1->addButton(shutdown_radio);
    suspend_low_radio->setFocusPolicy(Qt::NoFocus);
    suspend_low_radio->setObjectName("suspend_low_radio");
    shutdown_radio->setFocusPolicy(Qt::NoFocus);
    shutdown_radio->setObjectName("shutdown_radio");
    laptop_lid_battery_label = new QLabel();
    suspend_lid_battery_radio = new QRadioButton();
    nothing_battery_radio = new QRadioButton();
    QButtonGroup *btnGroup2 = new QButtonGroup();
    btnGroup2->addButton(suspend_lid_battery_radio);
    btnGroup2->addButton(nothing_battery_radio);
    suspend_lid_battery_radio->setFocusPolicy(Qt::NoFocus);
    suspend_lid_battery_radio->setObjectName("suspend_lid_battery_radio");
    nothing_battery_radio->setFocusPolicy(Qt::NoFocus);
    nothing_battery_radio->setObjectName("nothing_battery_radio");
    laptop_lid_ac_label = new QLabel();
    suspend_lid_ac_radio = new QRadioButton();
    nothing_ac_radio = new QRadioButton();
    QButtonGroup *btnGroup3 = new QButtonGroup();
    btnGroup3->addButton(suspend_lid_ac_radio);
    btnGroup3->addButton(nothing_ac_radio);
    suspend_lid_ac_radio->setFocusPolicy(Qt::NoFocus);
    suspend_lid_ac_radio->setObjectName("suspend_lid_ac_radio");
    nothing_ac_radio->setFocusPolicy(Qt::NoFocus);
    nothing_ac_radio->setObjectName("nothing_ac_radio");
    sleep_battery_label = new QLabel();
    sleep_battery_combo = new QComboBox();
    sleep_ac_label = new QLabel();
    sleep_ac_combo = new QComboBox();
    sleep_battery_display_label = new QLabel();
    sleep_battery_display_combo = new QComboBox();
    sleep_ac_display_label = new QLabel();
    sleep_ac_display_combo = new QComboBox();

    if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui") {
        brightness_label->hide();
        brightness_value_label->hide();
        brightness_slider->hide();
    }
    else {
        sleep_battery_display_label->hide();
        sleep_battery_display_combo->hide();
        sleep_ac_display_label->hide();
        sleep_ac_display_combo->hide();
    }

//    if(!sessionproxy->judge_power_is_exists_qt())
    if(has_battery == false)
    {
        critical_low_label->hide();
        suspend_low_radio->hide();
        shutdown_radio->hide();
        laptop_lid_battery_label->hide();
        suspend_lid_battery_radio->hide();
        nothing_battery_radio->hide();
        sleep_battery_label->hide();
        sleep_battery_combo->hide();
        laptop_lid_ac_label->hide();
        suspend_lid_ac_radio->hide();
        nothing_ac_radio->hide();
        sleep_battery_display_label->hide();
        sleep_battery_display_combo->hide();
    }

    gamma_label->setFixedWidth(260);
    brightness_label->setFixedWidth(260);
    idle_delay_label->setFixedWidth(260);
    lock_enabled_label->setFixedWidth(260);
    lock_delay_label->setFixedWidth(260);
    critical_low_label->setFixedWidth(260);
    laptop_lid_battery_label->setFixedWidth(260);
    laptop_lid_ac_label->setFixedWidth(260);
    sleep_battery_label->setFixedWidth(260);
    sleep_ac_label->setFixedWidth(260);
    sleep_battery_display_label->setFixedWidth(260);
    sleep_ac_display_label->setFixedWidth(260);



    QHBoxLayout *layout0 = new QHBoxLayout();
    layout0->setSpacing(10);
    layout0->addWidget(gamma_label);
    layout0->addWidget(gamma_slider);
    layout0->addStretch();
    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->setSpacing(10);
    layout1->addWidget(brightness_label);
    layout1->addWidget(brightness_slider);
    layout1->addWidget(brightness_value_label);
    layout1->addStretch();
    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->setSpacing(10);
    layout2->addWidget(idle_delay_label);
    layout2->addWidget(idle_delay_combo);
    layout2->addStretch();
    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->setSpacing(10);
    layout3->addWidget(lock_enabled_label);
    layout3->addWidget(lock_enabled_switch);
    layout3->addStretch();
    QHBoxLayout *layout4 = new QHBoxLayout();
    layout4->setSpacing(10);
    layout4->addWidget(lock_delay_label);
    layout4->addWidget(lock_delay_combo);
    layout4->addStretch();
    QHBoxLayout *layout5 = new QHBoxLayout();
    layout5->setSpacing(10);
    layout5->addWidget(critical_low_label);
    layout5->addWidget(suspend_low_radio);
    layout5->addWidget(shutdown_radio);
//    layout5->addWidget(btnGroup);
    layout5->addStretch();
    QHBoxLayout *layout6 = new QHBoxLayout();
    layout6->setSpacing(10);
    layout6->addWidget(laptop_lid_battery_label);
    layout6->addWidget(suspend_lid_battery_radio);
    layout6->addWidget(nothing_battery_radio);
    layout6->addStretch();
    QHBoxLayout *layout7 = new QHBoxLayout();
    layout7->setSpacing(10);
    layout7->addWidget(laptop_lid_ac_label);
    layout7->addWidget(suspend_lid_ac_radio);
    layout7->addWidget(nothing_ac_radio);
    layout7->addStretch();
    QHBoxLayout *layout8 = new QHBoxLayout();
    layout8->setSpacing(10);
    layout8->addWidget(sleep_battery_label);
    layout8->addWidget(sleep_battery_combo);
    layout8->addStretch();
    QHBoxLayout *layout9 = new QHBoxLayout();
    layout9->setSpacing(10);
    layout9->addWidget(sleep_ac_label);
    layout9->addWidget(sleep_ac_combo);
    layout9->addStretch();
    QHBoxLayout *layout10 = new QHBoxLayout();
    layout10->setSpacing(10);
    layout10->addWidget(sleep_battery_display_label);
    layout10->addWidget(sleep_battery_display_combo);
    layout10->addStretch();
    QHBoxLayout *layout11 = new QHBoxLayout();
    layout11->setSpacing(10);
    layout11->addWidget(sleep_ac_display_label);
    layout11->addWidget(sleep_ac_display_combo);
    layout11->addStretch();

    m_layout = new QVBoxLayout(this);
    m_layout->setSpacing(10);
    m_layout->setContentsMargins(20, 20, 0, 0);

    m_layout->addLayout(layout0);
    m_layout->addLayout(layout1);
    m_layout->addLayout(layout2);
    m_layout->addLayout(layout3);
    m_layout->addLayout(layout4);
    m_layout->addLayout(layout5);
    m_layout->addLayout(layout6);
    m_layout->addLayout(layout7);
    m_layout->addLayout(layout8);
    m_layout->addLayout(layout9);
    m_layout->addLayout(layout10);
    m_layout->addLayout(layout11);

    //kobe reset cpu mode
    if (!cpulist.isEmpty()) {
//        qDebug() << cpulist;
//        qDebug() << cpu;
        QLabel *cpu_label = new QLabel();
        cpu_label->setText(tr("CPU FM mode:"));
        QHBoxLayout *cpu_layout = new QHBoxLayout();
        cpu_layout->setSpacing(10);
        cpu_layout->addWidget(cpu_label);
        QButtonGroup *cpuGroup = new QButtonGroup();

        QList<QString>::Iterator it = cpulist.begin(), itend = cpulist.end();
        for(;it != itend; it++) {
            if(*it == "ondemand") {
                QRadioButton *ondemand_radio = new QRadioButton();
                ondemand_radio->setFocusPolicy(Qt::NoFocus);
                ondemand_radio->setText(tr("Ondemand"));
                ondemand_radio->setObjectName("ondemandradio");
                ondemand_radio->setChecked(false);
                cpuGroup->addButton(ondemand_radio);
                cpu_layout->addWidget(ondemand_radio);
                connect(ondemand_radio, SIGNAL(clicked()), this, SLOT(onCpuRadioButtonClicked()));
            }
            else if(*it == "powersave") {
                QRadioButton *powersave_radio = new QRadioButton();
                powersave_radio->setFocusPolicy(Qt::NoFocus);
                powersave_radio->setText(tr("Powersave"));
                powersave_radio->setObjectName("powersaveradio");
                powersave_radio->setChecked(false);
                cpuGroup->addButton(powersave_radio);
                cpu_layout->addWidget(powersave_radio);
                connect(powersave_radio, SIGNAL(clicked()), this, SLOT(onCpuRadioButtonClicked()));
            }
            else if(*it == "performance") {
                QRadioButton *performance_radio = new QRadioButton();
                performance_radio->setFocusPolicy(Qt::NoFocus);
                performance_radio->setText(tr("Performance"));
                performance_radio->setObjectName("performanceradio");
                performance_radio->setChecked(false);
                cpuGroup->addButton(performance_radio);
                cpu_layout->addWidget(performance_radio);
                connect(performance_radio, SIGNAL(clicked()), this, SLOT(onCpuRadioButtonClicked()));
            }
        }
        cpu_layout->addStretch();
        m_layout->addLayout(cpu_layout);

//        for (auto cpuMode : cpulist)
        foreach (QAbstractButton *absbutton, cpuGroup->buttons()) {
            QRadioButton *radio = qobject_cast<QRadioButton*>(absbutton);
            if (radio) {
                QString obj_name = radio->objectName();
                if(obj_name == "ondemandradio") {
                    if(cpu == "ondemand") {
                        radio->setChecked(true);
                    }
                    else {
                        radio->setChecked(false);
                    }
                }
                else if(obj_name == "powersaveradio") {
                    if(cpu == "powersave") {
                        radio->setChecked(true);
                    }
                    else {
                        radio->setChecked(false);
                    }
                }
                else if(obj_name == "performanceradio") {
                    if(cpu == "performance") {
                        radio->setChecked(true);
                    }
                    else {
                        radio->setChecked(false);
                    }
                }
            }
        }

    }
    m_layout->addStretch();

//    this->initSettingData();
    this->setLanguage();

//    iface = new QDBusInterface("org.gnome.SettingsDaemon",
//                               "/org/gnome/SettingsDaemon/Power",
//                               "org.gnome.SettingsDaemon.Power.Screen",
//                               QDBusConnection::sessionBus());
}

EnergyWidget::~EnergyWidget()
{
//    if (iface != NULL) {
//        delete iface;
//        iface = NULL;
//    }
    if (gamma_label != NULL) {
        delete gamma_label;
        gamma_label = NULL;
    }
    if (gamma_slider != NULL) {
        delete gamma_slider;
        gamma_slider = NULL;
    }
    if (brightness_label != NULL) {
        delete brightness_label;
        brightness_label = NULL;
    }
    if (brightness_value_label != NULL) {
        delete brightness_value_label;
        brightness_value_label = NULL;
    }
    if (brightness_slider != NULL) {
        delete brightness_slider;
        brightness_slider = NULL;
    }
    if (idle_delay_label != NULL) {
        delete idle_delay_label;
        idle_delay_label = NULL;
    }
    if (idle_delay_combo != NULL) {
        delete idle_delay_combo;
        idle_delay_combo = NULL;
    }
    if (lock_enabled_label != NULL) {
        delete lock_enabled_label;
        lock_enabled_label = NULL;
    }
    if (lock_enabled_switch != NULL) {
        delete lock_enabled_switch;
        lock_enabled_switch = NULL;
    }
    if (lock_delay_label != NULL) {
        delete lock_delay_label;
        lock_delay_label = NULL;
    }
    if (lock_delay_combo != NULL) {
        delete lock_delay_combo;
        lock_delay_combo = NULL;
    }
    if (critical_low_label != NULL) {
        delete critical_low_label;
        critical_low_label = NULL;
    }
    if (suspend_low_radio != NULL) {
        delete suspend_low_radio;
        suspend_low_radio = NULL;
    }
    if (shutdown_radio != NULL) {
        delete shutdown_radio;
        shutdown_radio = NULL;
    }
    if (laptop_lid_battery_label != NULL) {
        delete laptop_lid_battery_label;
        laptop_lid_battery_label = NULL;
    }
    if (suspend_lid_battery_radio != NULL) {
        delete suspend_lid_battery_radio;
        suspend_lid_battery_radio = NULL;
    }
    if (nothing_battery_radio != NULL) {
        delete nothing_battery_radio;
        nothing_battery_radio = NULL;
    }
    if (laptop_lid_ac_label != NULL) {
        delete laptop_lid_ac_label;
        laptop_lid_ac_label = NULL;
    }
    if (suspend_lid_ac_radio != NULL) {
        delete suspend_lid_ac_radio;
        suspend_lid_ac_radio = NULL;
    }
    if (nothing_ac_radio != NULL) {
        delete nothing_ac_radio;
        nothing_ac_radio = NULL;
    }
    if (sleep_battery_label != NULL) {
        delete sleep_battery_label;
        sleep_battery_label = NULL;
    }
    if (sleep_battery_combo != NULL) {
        delete sleep_battery_combo;
        sleep_battery_combo = NULL;
    }
    if (sleep_ac_label != NULL) {
        delete sleep_ac_label;
        sleep_ac_label = NULL;
    }
    if (sleep_ac_combo != NULL) {
        delete sleep_ac_combo;
        sleep_ac_combo = NULL;
    }
    if (sleep_battery_display_label != NULL) {
        delete sleep_battery_display_label;
        sleep_battery_display_label = NULL;
    }
    if (sleep_battery_display_combo != NULL) {
        delete sleep_battery_display_combo;
        sleep_battery_display_combo = NULL;
    }
    if (sleep_ac_display_label != NULL) {
        delete sleep_ac_display_label;
        sleep_ac_display_label = NULL;
    }
    if (sleep_ac_display_combo != NULL) {
        delete sleep_ac_display_combo;
        sleep_ac_display_combo = NULL;
    }

    QLayoutItem *child;
    while ((child = m_layout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
}

QString EnergyWidget::settingModuleName()
{
    return "EnergyPage";
}

void EnergyWidget::setLanguage() {
    gamma_label->setText(tr("Adjust gamma") + ":");
    brightness_label->setText(tr("Adjust brightness") + ":");
    idle_delay_label->setText(tr("Time before session is considered idle") + ":");//在一定时间范围内无操作则关闭屏幕
    lock_enabled_label->setText(tr("Lock screen") + ":");//锁定屏幕
    lock_delay_label->setText(tr("Lock delay") + ":");//锁屏延时
    critical_low_label->setText(tr("Battery critical low action") + ":");//电池严重不足时
    laptop_lid_battery_label->setText(tr("Laptop lid close action on battery") + ":");//合上盖子时
    laptop_lid_ac_label->setText(tr("Laptop lid close action on AC") + ":");//合上盖子时
    sleep_battery_label->setText(tr("Sleep timeout PC when on battery") + ":");//使用电池，空闲此时间后电脑转入睡眠
    sleep_ac_label->setText(tr("Sleep timeout PC when on AC") + ":");//使用电源，空闲此时间后电脑转入睡眠
    sleep_battery_display_label->setText(tr("Sleep timeout display when on battery") + ":");//使用电池，空闲此时间后屏幕转入睡眠
    sleep_ac_display_label->setText(tr("Sleep timeout display when on AC") + ":");//使用电源，空闲此时间后屏幕转入睡眠
    suspend_low_radio->setText(tr("suspend"));//休眠
    shutdown_radio->setText(tr("shutdown"));//电源关闭
    suspend_lid_battery_radio->setText(tr("suspend"));//挂起
    nothing_battery_radio->setText(tr("nothing"));//不处理
    suspend_lid_ac_radio->setText(tr("suspend"));//挂起
    nothing_ac_radio->setText(tr("nothing"));//不处理
}

void EnergyWidget::initSettingData()
{
    emit requestPowerAndBatteryData();

    /*iface = new QDBusInterface("org.gnome.SettingsDaemon",
                               "/org/gnome/SettingsDaemon/Power",
                               "org.gnome.SettingsDaemon.Power.Screen",
                               QDBusConnection::sessionBus());
    gamma_slider->setValue(sessionproxy->get_screen_gamma_qt());

    QStringList aclist  = sessionproxy->get_sleep_timeout_list_qt();
    bool inHere = false;
    if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui") {
        sleep_timeout_display_battery = sessionproxy->get_current_sleep_timeout_display_battery_qt();
        QStringList huname_display_battery_list;
        huname_display_battery_list << tr("5 minutes") << tr("10 minutes") << tr("20 minutes") << tr("Half an hour") << tr("1 hour") << tr("2 hours") << tr("never");
        QList<QString>::Iterator it5 = aclist.begin(), itend5 = aclist.end();
        int initIndex5 = 0;
        inHere = false;
        for(;it5 != itend5; it5++,initIndex5++)
        {
            if(*it5 == sleep_timeout_display_battery) {
                inHere = true;
                break;
            }
        }
        if (inHere == false) {
            huname_display_battery_list << sleep_timeout_display_battery;
            initIndex5 = huname_display_battery_list.length() - 1;
        }
        sleep_battery_display_combo->clear();
        sleep_battery_display_combo->clearEditText();
        sleep_battery_display_combo->addItems(huname_display_battery_list);
        sleep_battery_display_combo->setCurrentIndex(initIndex5);

        sleep_timeout_display_ac = sessionproxy->get_current_sleep_timeout_display_ac_qt();
        QStringList huname_display_ac_list;
        huname_display_ac_list << tr("5 minutes") << tr("10 minutes") << tr("20 minutes") << tr("Half an hour") << tr("1 hour") << tr("2 hours") << tr("never");
        QList<QString>::Iterator it6 = aclist.begin(), itend6 = aclist.end();
        int initIndex6 = 0;
        inHere = false;
        for(;it6 != itend6; it6++,initIndex6++)
        {
            if(*it6 == sleep_timeout_display_ac) {
                inHere = true;
                break;
            }
        }
        if (inHere == false) {
            huname_display_ac_list << sleep_timeout_display_ac;
            initIndex6 = huname_display_ac_list.length() - 1;
        }
        sleep_ac_display_combo->clear();
        sleep_ac_display_combo->clearEditText();
        sleep_ac_display_combo->addItems(huname_display_ac_list);
        sleep_ac_display_combo->setCurrentIndex(initIndex6);
    }
    else {
        QDBusReply<int> reply = iface->call("GetPercentage");
        if (reply.isValid()) {
            brightness_slider->setValue(reply.value());
            brightness_value_label->setText(QString::number(brightness_slider->value()));
        }
        else
        {
            brightness_label->hide();
            brightness_value_label->hide();
            brightness_slider->hide();
        }
    }

    current_idle_delay = sessionproxy->get_current_idle_delay_qt();
    QStringList idledelaylist  = sessionproxy->get_idle_delay_list_qt();
    QStringList huname_idle_list;
    huname_idle_list << tr("1 minute") << tr("2 minutes") << tr("3 minutes") << tr("5 minutes") << tr("10 minutes") << tr("Half an hour") << tr("1 hour") << tr("never");
    QList<QString>::Iterator it1 = idledelaylist.begin(), itend1 = idledelaylist.end();
    int initIndex1 = 0;

    for(;it1 != itend1; it1++,initIndex1++)
    {
        if(*it1 == current_idle_delay) {
            inHere = true;
            break;
        }
    }
    if (inHere == false) {
        huname_idle_list << current_idle_delay;
        initIndex1 = huname_idle_list.length() - 1;
    }
    idle_delay_combo->clear();
    idle_delay_combo->clearEditText();
    idle_delay_combo->addItems(huname_idle_list);
    idle_delay_combo->setCurrentIndex(initIndex1);

    lock_enabled_switch->switchedOn = sessionproxy->get_lock_enabled_qt();
    if(lock_enabled_switch->switchedOn)
    {
        lock_delay_combo->setDisabled(false);
    }
    else {
        lock_delay_combo->setDisabled(true);
    }

    current_lock_delay = sessionproxy->get_current_lock_delay_qt();
    QStringList lockdelaylist = sessionproxy->get_lock_delay_list_qt();
    QStringList huname_lock_list;
    huname_lock_list << tr("30 seconds") << tr("1 minute") << tr("2 minutes") << tr("3 minutes") << tr("5 minutes") << tr("10 minutes") << tr("Half an hour") << tr("1 hour") << tr("Turn off the screen");
    QList<QString>::Iterator it2 = lockdelaylist.begin(), itend2 = lockdelaylist.end();
    int initIndex2 = 0;
    inHere = false;
    for(;it2 != itend2; it2++,initIndex2++)
    {
        if(*it2 == current_lock_delay) {
            inHere = true;
            break;
        }
    }
    if (inHere == false) {
        huname_lock_list << current_lock_delay;
        initIndex2 = huname_lock_list.length() - 1;
    }
    lock_delay_combo->clear();
    lock_delay_combo->clearEditText();
    lock_delay_combo->addItems(huname_lock_list);
    lock_delay_combo->setCurrentIndex(initIndex2);

    QString critical_low = sessionproxy->get_current_critical_low_qt();
    if(critical_low == "suspend" ) {
        suspend_low_radio->setChecked(true);
        shutdown_radio->setChecked(false);
    }
    else if(critical_low == "shutdown") {
        shutdown_radio->setChecked(true);
        suspend_low_radio->setChecked(false);
    }
    QString laptop_battery = sessionproxy->get_current_lid_battery_qt();
    if(laptop_battery == "suspend") {
        suspend_lid_battery_radio->setChecked(true);
        nothing_battery_radio->setChecked(false);
    }
    else if(laptop_battery == "nothing") {
        nothing_battery_radio->setChecked(true);
        suspend_lid_battery_radio->setChecked(false);
    }
    QString laptop_ac = sessionproxy->get_current_lid_ac_qt();
    if(laptop_ac == "suspend") {
        suspend_lid_ac_radio->setChecked(true);
        nothing_ac_radio->setChecked(false);
    }
    else if(laptop_ac == "nothing") {
        nothing_ac_radio->setChecked(true);
        suspend_lid_ac_radio->setChecked(false);
    }

    sleep_timeout_battery = sessionproxy->get_current_sleep_timeout_battery_qt();
    QStringList batterylist  = sessionproxy->get_sleep_timeout_list_qt();
    QStringList huname_battery_list;
    huname_battery_list << tr("5 minutes") << tr("10 minutes") << tr("20 minutes") << tr("Half an hour") << tr("1 hour") << tr("2 hours") << tr("never");
    QList<QString>::Iterator it3 = batterylist.begin(), itend3 = batterylist.end();
    int initIndex3 = 0;
    inHere = false;
    for(;it3 != itend3; it3++,initIndex3++)
    {
        if(*it3 == sleep_timeout_battery) {
            inHere = true;
            break;
        }
    }
    if (inHere == false) {
        huname_battery_list << sleep_timeout_battery;
        initIndex3 = huname_battery_list.length() - 1;
    }
    sleep_battery_combo->clear();
    sleep_battery_combo->clearEditText();
    sleep_battery_combo->addItems(huname_battery_list);
    sleep_battery_combo->setCurrentIndex(initIndex3);

    sleep_timeout_ac = sessionproxy->get_current_sleep_timeout_ac_qt();
    QStringList huname_ac_list;
    huname_ac_list << tr("5 minutes") << tr("10 minutes") << tr("20 minutes") << tr("Half an hour") << tr("1 hour") << tr("2 hours") << tr("never");
    QList<QString>::Iterator it4 = aclist.begin(), itend4 = aclist.end();
    int initIndex4 = 0;
    inHere = false;
    for(;it4 != itend4; it4++,initIndex4++)
    {
        if(*it4 == sleep_timeout_ac) {
            inHere = true;
            break;
        }
    }
    if (inHere == false) {
        huname_ac_list << sleep_timeout_ac;
        initIndex4 = huname_ac_list.length() - 1;
    }
    sleep_ac_combo->clear();
    sleep_ac_combo->clearEditText();
    sleep_ac_combo->addItems(huname_ac_list);
    sleep_ac_combo->setCurrentIndex(initIndex4);*/


    this->initConnect();
}

void EnergyWidget::onSendIdleAndGammaData(double gamma, const QStringList &aclist, int brightnessValue, const QString &sleepTimeoutDisplayBattery, const QString &sleepTimeoutFisplayAC, const QString &idle_delay, const QStringList &idledelaylist)
{
    gamma_slider->setValue(gamma);

    m_aclist.clear();
    m_aclist  = aclist;
    bool inHere = false;
    if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui") {
        sleep_timeout_display_battery = sleepTimeoutDisplayBattery;
        QStringList huname_display_battery_list;
        huname_display_battery_list << tr("5 minutes") << tr("10 minutes") << tr("20 minutes") << tr("Half an hour") << tr("1 hour") << tr("2 hours") << tr("never");
        QList<QString>::Iterator it5 = m_aclist.begin(), itend5 = m_aclist.end();
        int initIndex5 = 0;
        inHere = false;
        for(;it5 != itend5; it5++,initIndex5++)
        {
            if(*it5 == sleep_timeout_display_battery) {
                inHere = true;
                break;
            }
        }
        if (inHere == false) {
            huname_display_battery_list << sleep_timeout_display_battery;
            initIndex5 = huname_display_battery_list.length() - 1;
        }
        sleep_battery_display_combo->clear();
        sleep_battery_display_combo->clearEditText();
        sleep_battery_display_combo->addItems(huname_display_battery_list);
        sleep_battery_display_combo->setCurrentIndex(initIndex5);

        sleep_timeout_display_ac = sleepTimeoutFisplayAC;
        QStringList huname_display_ac_list;
        huname_display_ac_list << tr("5 minutes") << tr("10 minutes") << tr("20 minutes") << tr("Half an hour") << tr("1 hour") << tr("2 hours") << tr("never");
        QList<QString>::Iterator it6 = m_aclist.begin(), itend6 = m_aclist.end();
        int initIndex6 = 0;
        inHere = false;
        for(;it6 != itend6; it6++,initIndex6++)
        {
            if(*it6 == sleep_timeout_display_ac) {
                inHere = true;
                break;
            }
        }
        if (inHere == false) {
            huname_display_ac_list << sleep_timeout_display_ac;
            initIndex6 = huname_display_ac_list.length() - 1;
        }
        sleep_ac_display_combo->clear();
        sleep_ac_display_combo->clearEditText();
        sleep_ac_display_combo->addItems(huname_display_ac_list);
        sleep_ac_display_combo->setCurrentIndex(initIndex6);
    }
    else {
        if (brightnessValue < 0) {
            brightness_label->hide();
            brightness_value_label->hide();
            brightness_slider->hide();
        }
        else {
            brightness_label->show();
            brightness_value_label->show();
            brightness_slider->show();
            brightness_slider->setValue(brightnessValue);
            brightness_value_label->setText(QString::number(brightnessValue));
        }
    }

    current_idle_delay = idle_delay;
    QStringList m_idledelaylist  = idledelaylist;
    QStringList huname_idle_list;
    huname_idle_list << tr("1 minute") << tr("2 minutes") << tr("3 minutes") << tr("5 minutes") << tr("10 minutes") << tr("Half an hour") << tr("1 hour") << tr("never");
    QList<QString>::Iterator it1 = m_idledelaylist.begin(), itend1 = m_idledelaylist.end();
    int initIndex1 = 0;

    for(;it1 != itend1; it1++,initIndex1++)
    {
        if(*it1 == current_idle_delay) {
            inHere = true;
            break;
        }
    }
    if (inHere == false) {
        huname_idle_list << current_idle_delay;
        initIndex1 = huname_idle_list.length() - 1;
    }
    idle_delay_combo->clear();
    idle_delay_combo->clearEditText();
    idle_delay_combo->addItems(huname_idle_list);
    idle_delay_combo->setCurrentIndex(initIndex1);
}

void EnergyWidget::onSendLockAndSleepData(bool lockEnabled, const QString &lock_delay, const QStringList &lockdelaylist, const QString &critical_low, const QString &laptop_battery, const QString &laptop_ac, const QString &sleepTimeoutBattery, const QStringList &batterylist, const QString &sleepTimeoutAc)
{
    lock_enabled_switch->switchedOn = lockEnabled;
    if(lock_enabled_switch->switchedOn)
    {
        lock_delay_combo->setDisabled(false);
    }
    else {
        lock_delay_combo->setDisabled(true);
    }

    current_lock_delay = lock_delay;
    QStringList m_lockdelaylist = lockdelaylist;
    QStringList huname_lock_list;
    huname_lock_list << tr("30 seconds") << tr("1 minute") << tr("2 minutes") << tr("3 minutes") << tr("5 minutes") << tr("10 minutes") << tr("Half an hour") << tr("1 hour") << tr("Turn off the screen");
    QList<QString>::Iterator it2 = m_lockdelaylist.begin(), itend2 = m_lockdelaylist.end();
    int initIndex2 = 0;
    bool inHere = false;
    for(;it2 != itend2; it2++,initIndex2++)
    {
        if(*it2 == current_lock_delay) {
            inHere = true;
            break;
        }
    }
    if (inHere == false) {
        huname_lock_list << current_lock_delay;
        initIndex2 = huname_lock_list.length() - 1;
    }
    lock_delay_combo->clear();
    lock_delay_combo->clearEditText();
    lock_delay_combo->addItems(huname_lock_list);
    lock_delay_combo->setCurrentIndex(initIndex2);

    if(critical_low == "suspend" ) {
        suspend_low_radio->setChecked(true);
        shutdown_radio->setChecked(false);
    }
    else if(critical_low == "shutdown") {
        shutdown_radio->setChecked(true);
        suspend_low_radio->setChecked(false);
    }

    if(laptop_battery == "suspend") {
        suspend_lid_battery_radio->setChecked(true);
        nothing_battery_radio->setChecked(false);
    }
    else if(laptop_battery == "nothing") {
        nothing_battery_radio->setChecked(true);
        suspend_lid_battery_radio->setChecked(false);
    }

    if(laptop_ac == "suspend") {
        suspend_lid_ac_radio->setChecked(true);
        nothing_ac_radio->setChecked(false);
    }
    else if(laptop_ac == "nothing") {
        nothing_ac_radio->setChecked(true);
        suspend_lid_ac_radio->setChecked(false);
    }

    sleep_timeout_battery = sleepTimeoutBattery;
    QStringList m_batterylist  = batterylist;
    QStringList huname_battery_list;
    huname_battery_list << tr("5 minutes") << tr("10 minutes") << tr("20 minutes") << tr("Half an hour") << tr("1 hour") << tr("2 hours") << tr("never");
    QList<QString>::Iterator it3 = m_batterylist.begin(), itend3 = m_batterylist.end();
    int initIndex3 = 0;
    inHere = false;
    for(;it3 != itend3; it3++,initIndex3++)
    {
        if(*it3 == sleep_timeout_battery) {
            inHere = true;
            break;
        }
    }
    if (inHere == false) {
        huname_battery_list << sleep_timeout_battery;
        initIndex3 = huname_battery_list.length() - 1;
    }
    sleep_battery_combo->clear();
    sleep_battery_combo->clearEditText();
    sleep_battery_combo->addItems(huname_battery_list);
    sleep_battery_combo->setCurrentIndex(initIndex3);

    sleep_timeout_ac = sleepTimeoutAc;
    QStringList huname_ac_list;
    huname_ac_list << tr("5 minutes") << tr("10 minutes") << tr("20 minutes") << tr("Half an hour") << tr("1 hour") << tr("2 hours") << tr("never");
    QList<QString>::Iterator it4 = m_aclist.begin(), itend4 = m_aclist.end();
    int initIndex4 = 0;
    inHere = false;
    for(;it4 != itend4; it4++,initIndex4++)
    {
        if(*it4 == sleep_timeout_ac) {
            inHere = true;
            break;
        }
    }
    if (inHere == false) {
        huname_ac_list << sleep_timeout_ac;
        initIndex4 = huname_ac_list.length() - 1;
    }
    sleep_ac_combo->clear();
    sleep_ac_combo->clearEditText();
    sleep_ac_combo->addItems(huname_ac_list);
    sleep_ac_combo->setCurrentIndex(initIndex4);
}

void EnergyWidget::initConnect()
{
    connect(gamma_slider, SIGNAL(valueChanged(double)), this, SLOT(setScreenGammaValue(double)));
    connect(brightness_slider, SIGNAL(valueChanged(int)), this, SLOT(setBrightnessValue(int)));
//    connect(idle_delay_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setIdleDelay(QString)));
    connect(idle_delay_combo, SIGNAL(currentIndexChanged(int)),  this, SLOT(setIdleDelay(int)));
    connect(lock_enabled_switch, SIGNAL(clicked()),  this, SLOT(setLockEnabled()));
//    connect(lock_delay_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setLockDelay(QString)));
    connect(lock_delay_combo, SIGNAL(currentIndexChanged(int)),  this, SLOT(setLockDelay(int)));
    connect(suspend_low_radio, SIGNAL(clicked()), this, SLOT(setRadioButtonRowStatus()));
    connect(shutdown_radio, SIGNAL(clicked()), this, SLOT(setRadioButtonRowStatus()));
    connect(suspend_lid_battery_radio, SIGNAL(clicked()), this, SLOT(setRadioButtonRowStatus()));
    connect(nothing_battery_radio, SIGNAL(clicked()), this, SLOT(setRadioButtonRowStatus()));
    connect(suspend_lid_ac_radio, SIGNAL(clicked()), this, SLOT(setRadioButtonRowStatus()));
    connect(nothing_ac_radio, SIGNAL(clicked()), this, SLOT(setRadioButtonRowStatus()));
    connect(sleep_battery_combo, SIGNAL(currentIndexChanged(int)),  this, SLOT(setSleepTimeoutBattery(int)));
    connect(sleep_ac_combo, SIGNAL(currentIndexChanged(int)),  this, SLOT(setSleepTimeoutAC(int)));
    connect(sleep_battery_display_combo, SIGNAL(currentIndexChanged(int)),  this, SLOT(setSleepTimeoutDisplayBattery(int)));
    connect(sleep_ac_display_combo, SIGNAL(currentIndexChanged(int)),  this, SLOT(setSleepTimeoutDisplayAC(int)));
}

void EnergyWidget::setScreenGammaValue(double value)
{
    emit resetScreenGammaValue(value);
//    sessionproxy->adjust_screen_gamma_qt(value);
}

void EnergyWidget::setBrightnessValue(int value)
{
    brightness_value_label->setText(QString::number(value));
    emit resetBrightnessValue(value);
//    iface->call("setPercentage", value);
}

//void EnergyWidget::setIdleDelay(QString value)
void EnergyWidget::setIdleDelay(int index)
{
    emit resetIdleDelay(index, current_idle_delay.toInt());
//    if (index == 0)
//    {
//        sessionproxy->set_current_idle_delay_qt(60);
//    }
//    else if (index == 1)
//    {
//        sessionproxy->set_current_idle_delay_qt(120);
//    }
//    else if (index == 2)
//    {
//        sessionproxy->set_current_idle_delay_qt(180);
//    }
//    else if (index == 3)
//    {
//        sessionproxy->set_current_idle_delay_qt(300);
//    }
//    else if (index == 4)
//    {
//        sessionproxy->set_current_idle_delay_qt(600);
//    }
//    else if (index == 5)
//    {
//        sessionproxy->set_current_idle_delay_qt(1800);
//    }
//    else if (index == 6)
//    {
//        sessionproxy->set_current_idle_delay_qt(3600);
//    }
//    else if (index == 7)
//    {
//        sessionproxy->set_current_idle_delay_qt(0);
//    }
//    else if (index == 8)
//    {
//        sessionproxy->set_current_idle_delay_qt(current_idle_delay.toInt());
//    }
////    sessionproxy->set_current_idle_delay_qt(value.toInt());
}

void EnergyWidget::setLockEnabled()
{
    emit resetLockEnabled(lock_enabled_switch->switchedOn);
//    sessionproxy->set_lock_enabled_qt(lock_enabled_switch->switchedOn);
    if (lock_enabled_switch->switchedOn) {
        lock_delay_combo->setDisabled(false);
    }
    else {
        lock_delay_combo->setDisabled(true);
    }
}

//void EnergyWidget::setLockDelay(QString value)
void EnergyWidget::setLockDelay(int index)
{
    emit resetLockDelay(index, current_lock_delay.toInt());
//    if (index == 0)
//    {
//        sessionproxy->set_current_lock_delay_qt(30);
//    }
//    else if (index == 1)
//    {
//        sessionproxy->set_current_lock_delay_qt(60);
//    }
//    else if (index == 2)
//    {
//        sessionproxy->set_current_lock_delay_qt(120);
//    }
//    else if (index == 3)
//    {
//        sessionproxy->set_current_lock_delay_qt(180);
//    }
//    else if (index == 4)
//    {
//        sessionproxy->set_current_lock_delay_qt(300);
//    }
//    else if (index == 5)
//    {
//        sessionproxy->set_current_lock_delay_qt(600);
//    }
//    else if (index == 6)
//    {
//        sessionproxy->set_current_lock_delay_qt(1800);
//    }
//    else if (index == 7)
//    {
//        sessionproxy->set_current_lock_delay_qt(3600);
//    }
//    else if (index == 8)
//    {
//        sessionproxy->set_current_lock_delay_qt(0);
//    }
//    else if (index == 9)
//    {
//        sessionproxy->set_current_lock_delay_qt(current_lock_delay.toInt());
//    }
////    sessionproxy->set_current_lock_delay_qt(value.toInt());
}

void EnergyWidget::onCpuRadioButtonClicked()
{
    QRadioButton *button = qobject_cast<QRadioButton*>(this->sender());
    if (button) {
        QString obj_name = button->objectName();
        emit setCurrentCpuMode(obj_name);
    }
}

void EnergyWidget::setRadioButtonRowStatus()
{
    QObject *obj = sender(); //返回发出信号的对象，用QObject类型接收
    QRadioButton* pbtn = qobject_cast<QRadioButton*>(obj);
    QString obj_name = pbtn->objectName();
    if(obj_name == "suspend_low_radio")
    {
        emit setCurrentCriticalLow("suspend");
//        sessionproxy->set_current_critical_low_qt("suspend");
    }
    else if(obj_name == "shutdown_radio")
    {
        emit setCurrentCriticalLow("shutdown");
//        sessionproxy->set_current_critical_low_qt("shutdown");
    }
    else if(obj_name == "suspend_lid_battery_radio")
    {
        emit setCurrentLidBattery("suspend");
//        sessionproxy->set_current_lid_battery_qt("suspend");
    }
    else if(obj_name == "nothing_battery_radio")
    {
        emit setCurrentLidBattery("nothing");
//        sessionproxy->set_current_lid_battery_qt("nothing");
    }
    else if(obj_name == "suspend_lid_ac_radio")
    {
        emit setCurrentLidAC("suspend");
//        sessionproxy->set_current_lid_ac_qt("suspend");
    }
    else if(obj_name == "nothing_ac_radio")
    {
        emit setCurrentLidAC("nothing");
//        sessionproxy->set_current_lid_ac_qt("nothing");
    }
}

void EnergyWidget::setSleepTimeoutBattery(int index)
{
    emit resetSleepTimeoutBattery(index, sleep_timeout_battery.toInt());
//    if (index == 0)
//    {
//        sessionproxy->set_current_sleep_timeout_battery_qt(300);
//    }
//    else if (index == 1)
//    {
//        sessionproxy->set_current_sleep_timeout_battery_qt(600);
//    }
//    else if (index == 2)
//    {
//        sessionproxy->set_current_sleep_timeout_battery_qt(1200);
//    }
//    else if (index == 3)
//    {
//        sessionproxy->set_current_sleep_timeout_battery_qt(1800);
//    }
//    else if (index == 4)
//    {
//        sessionproxy->set_current_sleep_timeout_battery_qt(3600);
//    }
//    else if (index == 5)
//    {
//        sessionproxy->set_current_sleep_timeout_battery_qt(7200);
//    }
//    else if (index == 6)
//    {
//        sessionproxy->set_current_sleep_timeout_battery_qt(0);
//    }
//    else if (index == 7)
//    {
//        sessionproxy->set_current_sleep_timeout_battery_qt(sleep_timeout_battery.toInt());
//    }
}

void EnergyWidget::setSleepTimeoutAC(int index)
{
    emit resetSleepTimeoutAC(index, sleep_timeout_ac.toInt());
//    if (index == 0)
//    {
//        sessionproxy->set_current_sleep_timeout_ac_qt(300);
//    }
//    else if (index == 1)
//    {
//        sessionproxy->set_current_sleep_timeout_ac_qt(600);
//    }
//    else if (index == 2)
//    {
//        sessionproxy->set_current_sleep_timeout_ac_qt(1200);
//    }
//    else if (index == 3)
//    {
//        sessionproxy->set_current_sleep_timeout_ac_qt(1800);
//    }
//    else if (index == 4)
//    {
//        sessionproxy->set_current_sleep_timeout_ac_qt(3600);
//    }
//    else if (index == 5)
//    {
//        sessionproxy->set_current_sleep_timeout_ac_qt(7200);
//    }
//    else if (index == 6)
//    {
//        sessionproxy->set_current_sleep_timeout_ac_qt(0);
//    }
//    else if (index == 7)
//    {
//        sessionproxy->set_current_sleep_timeout_ac_qt(sleep_timeout_ac.toInt());
//    }
}

void EnergyWidget::setSleepTimeoutDisplayBattery(int index)
{
    emit resetSleepTimeoutDisplayBattery(index, sleep_timeout_battery.toInt());
//    if (index == 0)
//    {
//        sessionproxy->set_current_sleep_timeout_display_battery_qt(300);
//    }
//    else if (index == 1)
//    {
//        sessionproxy->set_current_sleep_timeout_display_battery_qt(600);
//    }
//    else if (index == 2)
//    {
//        sessionproxy->set_current_sleep_timeout_display_battery_qt(1200);
//    }
//    else if (index == 3)
//    {
//        sessionproxy->set_current_sleep_timeout_display_battery_qt(1800);
//    }
//    else if (index == 4)
//    {
//        sessionproxy->set_current_sleep_timeout_display_battery_qt(3600);
//    }
//    else if (index == 5)
//    {
//        sessionproxy->set_current_sleep_timeout_display_battery_qt(7200);
//    }
//    else if (index == 6)
//    {
//        sessionproxy->set_current_sleep_timeout_display_battery_qt(0);
//    }
//    else if (index == 7)
//    {
//        sessionproxy->set_current_sleep_timeout_display_battery_qt(sleep_timeout_battery.toInt());
//    }
}

void EnergyWidget::setSleepTimeoutDisplayAC(int index)
{
    emit resetSleepTimeoutDisplayAC(index, sleep_timeout_battery.toInt());
//    if (index == 0)
//    {
//        sessionproxy->set_current_sleep_timeout_display_ac_qt(300);
//    }
//    else if (index == 1)
//    {
//        sessionproxy->set_current_sleep_timeout_display_ac_qt(600);
//    }
//    else if (index == 2)
//    {
//        sessionproxy->set_current_sleep_timeout_display_ac_qt(1200);
//    }
//    else if (index == 3)
//    {
//        sessionproxy->set_current_sleep_timeout_display_ac_qt(1800);
//    }
//    else if (index == 4)
//    {
//        sessionproxy->set_current_sleep_timeout_display_ac_qt(3600);
//    }
//    else if (index == 5)
//    {
//        sessionproxy->set_current_sleep_timeout_display_ac_qt(7200);
//    }
//    else if (index == 6)
//    {
//        sessionproxy->set_current_sleep_timeout_display_ac_qt(0);
//    }
//    else if (index == 7)
//    {
//        sessionproxy->set_current_sleep_timeout_display_ac_qt(sleep_timeout_battery.toInt());
//    }
}
