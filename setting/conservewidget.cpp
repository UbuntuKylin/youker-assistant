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

#include "conservewidget.h"
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
//#include <QRadioButton>
#include <QDoubleSpinBox>
#include <QSlider>
#include "../dbusproxy/youkersessiondbus.h"
#include <QDebug>

ConserveWidget::ConserveWidget(QWidget *parent, SessionDispatcher *proxy, QString cur_desktop) :
    QWidget(parent),
    sessionproxy(proxy)
{
    iface = NULL;
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

    if (cur_desktop == "mate") {
        brightness_label->hide();
        brightness_value_label->hide();
        brightness_slider->hide();
    }

    gamma_label->setFixedWidth(260);
    brightness_label->setFixedWidth(260);
    idle_delay_label->setFixedWidth(260);
    lock_enabled_label->setFixedWidth(260);
    lock_delay_label->setFixedWidth(260);

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
//    QHBoxLayout *layout5 = new QHBoxLayout();
//    layout5->setSpacing(10);
//    layout5->addWidget(right_click_label);
//    layout5->addWidget(right_click_combo);
//    layout5->addStretch();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(layout0);
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
//    layout->addLayout(layout5);
    layout->addStretch();
    setLayout(layout);
    layout->setSpacing(10);
    layout->setContentsMargins(20, 20, 0, 0);

    this->initData();
    this->setLanguage();
    this->initConnect();
}

ConserveWidget::~ConserveWidget()
{
    if (iface != NULL) {
        delete iface;
        iface = NULL;
    }
}

void ConserveWidget::setLanguage() {
    gamma_label->setText(tr("Adjust gamma") + ":");
    brightness_label->setText(tr("Adjust brightness") + ":");
    idle_delay_label->setText(tr("Time before session is considered idle") + ":");//在一定时间范围内无操作则关闭屏幕
    lock_enabled_label->setText(tr("Lock screen") + ":");//锁定屏幕
    lock_delay_label->setText(tr("Lock delay") + ":");//锁屏延时
}

void ConserveWidget::initData()
{
    iface = new QDBusInterface("org.gnome.SettingsDaemon",
                               "/org/gnome/SettingsDaemon/Power",
                               "org.gnome.SettingsDaemon.Power.Screen",
                               QDBusConnection::sessionBus());
    gamma_slider->setValue(sessionproxy->get_screen_gamma_qt());

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

    current_idle_delay = sessionproxy->get_current_idle_delay_qt();
    QStringList idledelaylist  = sessionproxy->get_idle_delay_list_qt();
    QStringList huname_idle_list;
    huname_idle_list << tr("1 minute") << tr("2 minutes") << tr("3 minutes") << tr("5 minutes") << tr("10 minutes") << tr("Half an hour") << tr("1 hour") << tr("never");
    QList<QString>::Iterator it1 = idledelaylist.begin(), itend1 = idledelaylist.end();
    int initIndex1 = 0;
    bool inHere = false;
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
}

void ConserveWidget::initConnect() {
    connect(gamma_slider, SIGNAL(valueChanged(double)), this, SLOT(setScreenGammaValue(double)));
    connect(brightness_slider, SIGNAL(valueChanged(int)), this, SLOT(setBrightnessValue(int)));
//    connect(idle_delay_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setIdleDelay(QString)));
    connect(idle_delay_combo, SIGNAL(currentIndexChanged(int)),  this, SLOT(setIdleDelay(int)));
    connect(lock_enabled_switch, SIGNAL(clicked()),  this, SLOT(setLockEnabled()));
//    connect(lock_delay_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setLockDelay(QString)));
    connect(lock_delay_combo, SIGNAL(currentIndexChanged(int)),  this, SLOT(setLockDelay(int)));
}

void ConserveWidget::setScreenGammaValue(double value)
{
    sessionproxy->adjust_screen_gamma_qt(value);
}

void ConserveWidget::setBrightnessValue(int value)
{
    brightness_value_label->setText(QString::number(value));
    iface->call("setPercentage", value);
}

//void ConserveWidget::setIdleDelay(QString value)
void ConserveWidget::setIdleDelay(int index)
{
    if (index == 0)
    {
        sessionproxy->set_current_idle_delay_qt(60);
    }
    else if (index == 1)
    {
        sessionproxy->set_current_idle_delay_qt(120);
    }
    else if (index == 2)
    {
        sessionproxy->set_current_idle_delay_qt(180);
    }
    else if (index == 3)
    {
        sessionproxy->set_current_idle_delay_qt(300);
    }
    else if (index == 4)
    {
        sessionproxy->set_current_idle_delay_qt(600);
    }
    else if (index == 5)
    {
        sessionproxy->set_current_idle_delay_qt(1800);
    }
    else if (index == 6)
    {
        sessionproxy->set_current_idle_delay_qt(3600);
    }
    else if (index == 7)
    {
        sessionproxy->set_current_idle_delay_qt(0);
    }
    else if (index == 8)
    {
        sessionproxy->set_current_idle_delay_qt(current_idle_delay.toInt());
    }
//    sessionproxy->set_current_idle_delay_qt(value.toInt());
}

void ConserveWidget::setLockEnabled()
{
    sessionproxy->set_lock_enabled_qt(lock_enabled_switch->switchedOn);
    if (lock_enabled_switch->switchedOn) {
        lock_delay_combo->setDisabled(false);
    }
    else {
        lock_delay_combo->setDisabled(true);
    }
}

//void ConserveWidget::setLockDelay(QString value)
void ConserveWidget::setLockDelay(int index)
{
    if (index == 0)
    {
        sessionproxy->set_current_lock_delay_qt(30);
    }
    else if (index == 1)
    {
        sessionproxy->set_current_lock_delay_qt(60);
    }
    else if (index == 2)
    {
        sessionproxy->set_current_lock_delay_qt(120);
    }
    else if (index == 3)
    {
        sessionproxy->set_current_lock_delay_qt(180);
    }
    else if (index == 4)
    {
        sessionproxy->set_current_lock_delay_qt(300);
    }
    else if (index == 5)
    {
        sessionproxy->set_current_lock_delay_qt(600);
    }
    else if (index == 6)
    {
        sessionproxy->set_current_lock_delay_qt(1800);
    }
    else if (index == 7)
    {
        sessionproxy->set_current_lock_delay_qt(3600);
    }
    else if (index == 8)
    {
        sessionproxy->set_current_lock_delay_qt(0);
    }
    else if (index == 9)
    {
        sessionproxy->set_current_lock_delay_qt(current_lock_delay.toInt());
    }
//    sessionproxy->set_current_lock_delay_qt(value.toInt());
}
