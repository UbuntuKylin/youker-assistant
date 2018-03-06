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

#include "panelwidget.h"
#include <QLabel>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QRadioButton>
#include <QHBoxLayout>

PanelWidget::PanelWidget(QWidget *parent, QString cur_desktop, bool has_battery) :
    SettingModulePage(parent),desktop(cur_desktop)
{
    blur_label = new QLabel();
    transparency_label = new QLabel();
    date_format_label = new QLabel();
    second_label = new QLabel();
    week_label = new QLabel();
    date_label = new QLabel();
    battery_icon_label = new QLabel();
    battery_percentage_label = new QLabel();
    battery_time_label = new QLabel();
    show_app_label = new QLabel();
    show_desktop_label = new QLabel();
    show_icon_label = new QLabel();
    show_places_label = new QLabel();

    smart_radio = new QRadioButton();
    smart_radio->setFocusPolicy(Qt::NoFocus);
    smart_radio->setChecked(true);
    smart_radio->setObjectName("smart_radio");
    static_radio = new QRadioButton();
    static_radio->setFocusPolicy(Qt::NoFocus);
    static_radio->setChecked(false);
    static_radio->setObjectName("static_radio");
    clear_radio = new QRadioButton();
    clear_radio->setFocusPolicy(Qt::NoFocus);
    clear_radio->setChecked(false);
    clear_radio->setObjectName("clear_radio");
    QHBoxLayout *radio_layout = new QHBoxLayout();
    radio_layout->setSpacing(10);
    radio_layout->addWidget(smart_radio);
    radio_layout->addWidget(static_radio);
    radio_layout->addWidget(clear_radio);
    radio_layout->addStretch();

    transparency_slider = new QDoubleSpinBox();
    transparency_slider->setButtonSymbols(QAbstractSpinBox::PlusMinus);
    transparency_slider->setSingleStep(0.1);
    transparency_slider->setMinimum(0.2);
    transparency_slider->setMaximum(8.0);

    date_combo = new QComboBox();
    second_switcher = new KylinSwitcher();
    week_switcher = new KylinSwitcher();
    date_switcher = new KylinSwitcher();
    battery_combo = new QComboBox();
    battery_percentage_switcher = new KylinSwitcher();
    battery_time_switcher = new KylinSwitcher();
    app_switcher = new KylinSwitcher();
    desktop_switcher = new KylinSwitcher();
    icon_switcher = new KylinSwitcher();
    places_switcher = new KylinSwitcher();

    if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui") {
        blur_label->hide();
        transparency_label->hide();
        date_format_label->hide();
        second_label->hide();
        week_label->hide();
        date_label->hide();
        battery_icon_label->hide();
        battery_percentage_label->hide();
        battery_time_label->hide();
        smart_radio->hide();
        static_radio->hide();
        clear_radio->hide();
        transparency_slider->hide();
        date_combo->hide();
        second_switcher->hide();
        week_switcher->hide();
        date_switcher->hide();
        battery_combo->hide();
        battery_percentage_switcher->hide();
        battery_time_switcher->hide();
    }
    else {
        show_app_label->hide();
        show_desktop_label->hide();
        show_icon_label->hide();
        show_places_label->hide();
        app_switcher->hide();
        desktop_switcher->hide();
        icon_switcher->hide();
        places_switcher->hide();
    }

    blur_label->setFixedWidth(220);
    transparency_label->setFixedWidth(220);
    date_format_label->setFixedWidth(220);
    second_label->setFixedWidth(220);
    week_label->setFixedWidth(220);
    date_label->setFixedWidth(220);
    battery_icon_label->setFixedWidth(220);
    battery_percentage_label->setFixedWidth(220);
    battery_time_label->setFixedWidth(220);
    show_app_label->setFixedWidth(220);
    show_desktop_label->setFixedWidth(220);
    show_icon_label->setFixedWidth(220);
    show_places_label->setFixedWidth(220);

    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->setSpacing(10);
    layout1->addWidget(blur_label);
    layout1->addLayout(radio_layout);
    layout1->addStretch();
    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->setSpacing(10);
    layout2->addWidget(transparency_label);
    layout2->addWidget(transparency_slider);
    layout2->addStretch();
    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->setSpacing(10);
    layout3->addWidget(date_format_label);
    layout3->addWidget(date_combo);
    layout3->addStretch();
    QHBoxLayout *layout4 = new QHBoxLayout();
    layout4->setSpacing(10);
    layout4->addWidget(second_label);
    layout4->addWidget(second_switcher);
    layout4->addStretch();
    QHBoxLayout *layout5 = new QHBoxLayout();
    layout5->setSpacing(10);
    layout5->addWidget(week_label);
    layout5->addWidget(week_switcher);
    layout5->addStretch();
    QHBoxLayout *layout6 = new QHBoxLayout();
    layout6->setSpacing(10);
    layout6->addWidget(date_label);
    layout6->addWidget(date_switcher);
    layout6->addStretch();
    QHBoxLayout *layout7 = new QHBoxLayout();
    layout7->setSpacing(10);
    layout7->addWidget(battery_icon_label);
    layout7->addWidget(battery_combo);
    layout7->addStretch();
    QHBoxLayout *layout8 = new QHBoxLayout();
    layout8->setSpacing(10);
    layout8->addWidget(battery_percentage_label);
    layout8->addWidget(battery_percentage_switcher);
    layout8->addStretch();
    QHBoxLayout *layout9 = new QHBoxLayout();
    layout9->setSpacing(10);
    layout9->addWidget(battery_time_label);
    layout9->addWidget(battery_time_switcher);
    layout9->addStretch();
    QHBoxLayout *layout10 = new QHBoxLayout();
    layout10->setSpacing(10);
    layout10->addWidget(show_app_label);
    layout10->addWidget(app_switcher);
    layout10->addStretch();
    QHBoxLayout *layout11 = new QHBoxLayout();
    layout11->setSpacing(10);
    layout11->addWidget(show_desktop_label);
    layout11->addWidget(desktop_switcher);
    layout11->addStretch();
    QHBoxLayout *layout12 = new QHBoxLayout();
    layout12->setSpacing(10);
    layout12->addWidget(show_icon_label);
    layout12->addWidget(icon_switcher);
    layout12->addStretch();
    QHBoxLayout *layout13 = new QHBoxLayout();
    layout13->setSpacing(10);
    layout13->addWidget(show_places_label);
    layout13->addWidget(places_switcher);
    layout13->addStretch();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
    layout->addLayout(layout5);
    layout->addLayout(layout6);
//    if(sessionproxy->judge_power_is_exists_qt())
    if(has_battery)
    {
        layout->addLayout(layout7);
        layout->addLayout(layout8);
        layout->addLayout(layout9);
    }
    layout->addLayout(layout10);
    layout->addLayout(layout11);
    layout->addLayout(layout12);
    layout->addLayout(layout13);
    layout->addStretch();
    setLayout(layout);
    layout->setSpacing(10);
    layout->setContentsMargins(20, 20, 0, 0);

//    splitter->addWidget(top_widget);
//    splitter->addWidget(bottom_widget);

//    QHBoxLayout *main_layout = new QHBoxLayout;
//    main_layout->addStretch();
//    main_layout->addWidget(splitter);
//    main_layout->setSpacing(0);
//    main_layout->setContentsMargins(0, 0, 0, 0);
//    setLayout(main_layout);
//    this->initSettingData();
    this->setLanguage();
}

PanelWidget::~PanelWidget()
{
    if (blur_label != NULL) {
        delete blur_label;
        blur_label = NULL;
    }
    if (transparency_label != NULL) {
        delete transparency_label;
        transparency_label = NULL;
    }
    if (date_format_label != NULL) {
        delete date_format_label;
        date_format_label = NULL;
    }
    if (second_label != NULL) {
        delete second_label;
        second_label = NULL;
    }
    if (week_label != NULL) {
        delete week_label;
        week_label = NULL;
    }
    if (date_label != NULL) {
        delete date_label;
        date_label = NULL;
    }
    if (battery_icon_label != NULL) {
        delete battery_icon_label;
        battery_icon_label = NULL;
    }
    if (battery_percentage_label != NULL) {
        delete battery_percentage_label;
        battery_percentage_label = NULL;
    }
    if (battery_time_label != NULL) {
        delete battery_time_label;
        battery_time_label = NULL;
    }
    if (show_app_label != NULL) {
        delete show_app_label;
        show_app_label = NULL;
    }
    if (show_desktop_label != NULL) {
        delete show_desktop_label;
        show_desktop_label = NULL;
    }
    if (show_icon_label != NULL) {
        delete show_icon_label;
        show_icon_label = NULL;
    }
    if (show_places_label != NULL) {
        delete show_places_label;
        show_places_label = NULL;
    }
    if (smart_radio != NULL) {
        delete smart_radio;
        smart_radio = NULL;
    }
    if (static_radio != NULL) {
        delete static_radio;
        static_radio = NULL;
    }
    if (clear_radio != NULL) {
        delete clear_radio;
        clear_radio = NULL;
    }
    if (transparency_slider != NULL) {
        delete transparency_slider;
        transparency_slider = NULL;
    }
    if (date_combo != NULL) {
        delete date_combo;
        date_combo = NULL;
    }
    if (second_switcher != NULL) {
        delete second_switcher;
        second_switcher = NULL;
    }
    if (week_switcher != NULL) {
        delete week_switcher;
        week_switcher = NULL;
    }
    if (date_switcher != NULL) {
        delete date_switcher;
        date_switcher = NULL;
    }
    if (battery_combo != NULL) {
        delete battery_combo;
        battery_combo = NULL;
    }
    if (battery_percentage_switcher != NULL) {
        delete battery_percentage_switcher;
        battery_percentage_switcher = NULL;
    }
    if (battery_time_switcher != NULL) {
        delete battery_time_switcher;
        battery_time_switcher = NULL;
    }
    if (app_switcher != NULL) {
        delete app_switcher;
        app_switcher = NULL;
    }
    if (desktop_switcher != NULL) {
        delete desktop_switcher;
        desktop_switcher = NULL;
    }
    if (icon_switcher != NULL) {
        delete icon_switcher;
        icon_switcher = NULL;
    }
    if (places_switcher != NULL) {
        delete places_switcher;
        places_switcher = NULL;
    }
}

QString PanelWidget::settingModuleName()
{
    return "PanelPage";
}

void PanelWidget::setLanguage() {
//    title_label->setText(tr("Dash & Panel"));
//    description_label->setText(tr("Manage Dash and Panel menu settings."));
//    back_btn->setText(tr("Back"));
    blur_label->setText(tr("Dash background blur type") + ":");
    transparency_label->setText(tr("Panel Transparency") + ":");
    date_format_label->setText(tr("Date & time format") + ":");
    second_label->setText(tr("Display seconds") + ":");
    week_label->setText(tr("Display week") + ":");
    date_label->setText(tr("Display the date") + ":");
    battery_icon_label->setText(tr("Display battery icon") + ":");
    battery_percentage_label->setText(tr("Display battery percentage") + ":");
    battery_time_label->setText(tr("Display battery remaining time") + ":");

    smart_radio->setText(tr("Smart blur"));
    static_radio->setText(tr("Static blur"));
    clear_radio->setText(tr("Clear"));

    show_app_label->setText(tr("Show applications") + ":");
    show_desktop_label->setText(tr("Show system") + ":");//Show desktop
    show_icon_label->setText(tr("Show icon") + ":");
    show_places_label->setText(tr("Show places") + ":");
}

void PanelWidget::initSettingData()
{
    if(this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui") {
        emit this->requestMateOrUnityPanelData(true);

//        app_switcher->switchedOn = sessionproxy->get_show_apps_qt();
//        desktop_switcher->switchedOn = sessionproxy->get_show_desktop_qt();
//        icon_switcher->switchedOn = sessionproxy->get_show_icon_qt();
//        places_switcher->switchedOn = sessionproxy->get_show_places_qt();
    }
    else {//unity
        emit this->requestMateOrUnityPanelData(false);

        /*int default_value = sessionproxy->get_dash_blur_experimental_qt();
        if(default_value == 2) {
            smart_radio->setChecked(true);
            static_radio->setChecked(false);
            clear_radio->setChecked(false);
        }
        else if(default_value == 1) {
            static_radio->setChecked(true);
            smart_radio->setChecked(false);
            clear_radio->setChecked(false);
        }
        else if(default_value == 0) {
            clear_radio->setChecked(true);
            static_radio->setChecked(false);
            smart_radio->setChecked(false);
        }
        transparency_slider->setValue(sessionproxy->get_panel_transparency_qt());
        QString cur_format = sessionproxy->get_time_format_qt();
        QStringList timelist  = sessionproxy->get_all_time_format_qt();
        date_combo->clear();
        date_combo->clearEditText();
        date_combo->addItems(timelist);
        QList<QString>::Iterator it = timelist.begin(), itend = timelist.end();
        int initIndex = 0;
        for(;it != itend; it++,initIndex++)
        {
            if(*it == cur_format)
                break;
        }
        date_combo->setCurrentIndex(initIndex);

        second_switcher->switchedOn = sessionproxy->get_show_seconds_qt();
        week_switcher->switchedOn = sessionproxy->get_show_week_qt();
        date_switcher->switchedOn = sessionproxy->get_show_date_qt();

        QString cur_power = sessionproxy->get_power_icon_policy_qt();
        m_powerlist  = sessionproxy->get_all_power_icon_policy_qt();
        battery_combo->clear();
        battery_combo->clearEditText();
        battery_combo->addItems(m_powerlist);
        QList<QString>::Iterator ite = m_powerlist.begin(), iteend = m_powerlist.end();
        int index = 0;
        for(;ite != iteend; ite++,index++)
        {
            if(*ite == cur_power)
                break;
        }
        battery_combo->setCurrentIndex(index);

        battery_percentage_switcher->switchedOn = sessionproxy->get_show_power_percentage_qt();
        battery_time_switcher->switchedOn = sessionproxy->get_show_power_time_qt();*/
    }


    this->initConnect();
}

void PanelWidget::onSendMatePanelValue(bool app, bool desktop, bool icon, bool places)
{
    app_switcher->switchedOn = app;
    desktop_switcher->switchedOn = desktop;
    icon_switcher->switchedOn = icon;
    places_switcher->switchedOn = places;
}

void PanelWidget::onSendUnityBlurAndTransparencyValue(int blur, double transparent)
{
    if(blur == 2) {
        smart_radio->setChecked(true);
        static_radio->setChecked(false);
        clear_radio->setChecked(false);
    }
    else if(blur == 1) {
        static_radio->setChecked(true);
        smart_radio->setChecked(false);
        clear_radio->setChecked(false);
    }
    else if(blur == 0) {
        clear_radio->setChecked(true);
        static_radio->setChecked(false);
        smart_radio->setChecked(false);
    }
    transparency_slider->setValue(transparent);
}

void PanelWidget::onSendUnityTimeValue(const QString &time_format, const QStringList &timelist, bool showSecond, bool showWeek, bool showDate)
{
    QStringList m_timelist = timelist;
    date_combo->clear();
    date_combo->clearEditText();
    date_combo->addItems(m_timelist);
    QList<QString>::Iterator it = m_timelist.begin(), itend = m_timelist.end();
    int initIndex = 0;
    for(;it != itend; it++,initIndex++)
    {
        if(*it == time_format)
            break;
    }
    date_combo->setCurrentIndex(initIndex);

    second_switcher->switchedOn = showSecond;
    week_switcher->switchedOn = showWeek;
    date_switcher->switchedOn = showDate;
}

void PanelWidget::onSendUnityPanelPowerValue(const QString &cur_power, const QStringList &powerlist, bool showPower, bool showBatteryTime)
{
    m_powerlist.clear();
    m_powerlist = powerlist;
    battery_combo->clear();
    battery_combo->clearEditText();
    battery_combo->addItems(m_powerlist);
    QList<QString>::Iterator ite = m_powerlist.begin(), iteend = m_powerlist.end();
    int index = 0;
    for(;ite != iteend; ite++,index++)
    {
        if(*ite == cur_power)
            break;
    }
    battery_combo->setCurrentIndex(index);

    battery_percentage_switcher->switchedOn = showPower;
    battery_time_switcher->switchedOn = showBatteryTime;
}

void PanelWidget::initConnect() {
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
    connect(smart_radio, SIGNAL(clicked()), this, SLOT(setRadioButtonRowStatus()));
    connect(static_radio, SIGNAL(clicked()), this, SLOT(setRadioButtonRowStatus()));
    connect(clear_radio, SIGNAL(clicked()), this, SLOT(setRadioButtonRowStatus()));
    connect(transparency_slider, SIGNAL(valueChanged(double)), this, SLOT(setTransparencyValue(double)));
    connect(date_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setDateFormat(QString)));
    connect(second_switcher, SIGNAL(clicked()),  this, SLOT(setDisplaySeconds()));
    connect(week_switcher, SIGNAL(clicked()),  this, SLOT(setDisplayWeek()));
    connect(date_switcher, SIGNAL(clicked()),  this, SLOT(setDisplayDate()));
    connect(battery_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setShowBatteryIcon(QString)));
    connect(battery_percentage_switcher, SIGNAL(clicked()),  this, SLOT(setDisplayBatteryPercentage()));
    connect(battery_time_switcher, SIGNAL(clicked()),  this, SLOT(setDisplayBatteryTime()));
    connect(app_switcher, SIGNAL(clicked()),  this, SLOT(showApplications()));
    connect(desktop_switcher, SIGNAL(clicked()),  this, SLOT(showDesktop()));
    connect(icon_switcher, SIGNAL(clicked()),  this, SLOT(showIcon()));
    connect(places_switcher, SIGNAL(clicked()),  this, SLOT(showPlaces()));

//    connect(sessionproxy, SIGNAL(string_value_notify(QString, QString)), this, SLOT(panelwidget_notify_string(QString, QString)));
//    connect(sessionproxy, SIGNAL(bool_value_notify(QString, bool)), this, SLOT(panelwidget_notify_bool(QString, bool)));
}

void PanelWidget::panelwidget_notify_string(QString key, QString value)
{
    if (key == "icon-policy") {
        QList<QString>::Iterator it = m_powerlist.begin(), itend = m_powerlist.end();
        int index = -1;
        bool exist = false;
        for(;it != itend; it++)
        {
            ++index;
            if(*it == value) {
                exist = true;
                break;
            }
        }
        if (exist) {
            exist = false;
            battery_combo->setCurrentIndex(index);
        }
        else
            battery_combo->setCurrentIndex(-1);
    }
}

void PanelWidget::panelwidget_notify_bool(QString key, bool value)
{
    if (key == "show-seconds") {
        second_switcher->switchedOn = value;
    }
    else if (key == "show-day") {
        week_switcher->switchedOn = value;
    }
    else if (key == "show-date") {
        date_switcher->switchedOn = value;
    }
    else if (key == "show-time") {
        battery_time_switcher->switchedOn = value;
    }
    else if (key == "show-percentage") {
        battery_percentage_switcher->switchedOn = value;
    }
    else if (key == "show-applications") {
        app_switcher->switchedOn = value;
    }
    else if (key == "show-desktop") {
        desktop_switcher->switchedOn = value;
    }
    else if (key == "show-icon") {
        icon_switcher->switchedOn = value;
    }
    else if (key == "show-places") {
        places_switcher->switchedOn = value;
    }
}

void PanelWidget::setTransparencyValue(double value)
{
    emit resetPanelTransparencyValue(value);
//    sessionproxy->set_panel_transparency_qt(value);
}



void PanelWidget::setDateFormat(QString selected) {
    emit resetDateFormat(selected);
//    sessionproxy->set_time_format_qt(selected);
}

void PanelWidget::setShowBatteryIcon(QString selected) {
    emit resetShowBatteryIcon(selected);
//    sessionproxy->set_power_icon_policy_qt(selected);
}


//TODO: 设计一个枚举变量作为标记，用一个函数去调用dbus设置各个值
void PanelWidget::setRadioButtonRowStatus(/*bool status*/)
{
    QObject *obj = sender(); //返回发出信号的对象，用QObject类型接收
    QRadioButton* pbtn = qobject_cast<QRadioButton*>(obj);
    QString obj_name = pbtn->objectName();
    if(obj_name == "smart_radio")
    {
        emit resetDashBlurExperimental(2);
//        sessionproxy->set_dash_blur_experimental_qt(2);
    }
    else if(obj_name == "static_radio")
    {
        emit resetDashBlurExperimental(1);
//        sessionproxy->set_dash_blur_experimental_qt(1);
    }
    else if(obj_name == "clear_radio")
    {
        emit resetDashBlurExperimental(0);
//        sessionproxy->set_dash_blur_experimental_qt(0);
    }
}

void PanelWidget::setDisplaySeconds()
{
    emit resetDisplaySeconds(second_switcher->switchedOn);
//    sessionproxy->set_show_seconds_qt(second_switcher->switchedOn);
}

void PanelWidget::setDisplayWeek()
{
    emit resetDisplayWeek(week_switcher->switchedOn);
//    sessionproxy->set_show_week_qt(week_switcher->switchedOn);
}

void PanelWidget::setDisplayDate()
{
    emit resetDisplayDate(date_switcher->switchedOn);
//    sessionproxy->set_show_date_qt(date_switcher->switchedOn);
}

void PanelWidget::setDisplayBatteryPercentage()
{
    emit resetDisplayBatteryPercentage(battery_percentage_switcher->switchedOn);
//    sessionproxy->set_show_power_percentage_qt(battery_percentage_switcher->switchedOn);
}

void PanelWidget::setDisplayBatteryTime()
{
    emit resetDisplayBatteryTime(battery_time_switcher->switchedOn);
//    sessionproxy->set_show_power_time_qt(battery_time_switcher->switchedOn);
}

void PanelWidget::showApplications()
{
    emit resetShowApplications(app_switcher->switchedOn);
//    sessionproxy->set_show_apps_qt(app_switcher->switchedOn);
}

void PanelWidget::showDesktop()
{
    emit resetShowDesktop(desktop_switcher->switchedOn);
//    sessionproxy->set_show_desktop_qt(desktop_switcher->switchedOn);
}

void PanelWidget::showIcon()
{
    emit resetShowIcon(icon_switcher->switchedOn);
//    sessionproxy->set_show_icon_qt(icon_switcher->switchedOn);
}

void PanelWidget::showPlaces()
{
    emit resetShowPlaces(places_switcher->switchedOn);
//    sessionproxy->set_show_places_qt(places_switcher->switchedOn);
}
