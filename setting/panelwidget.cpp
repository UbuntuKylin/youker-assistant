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
#include "../dbusproxy/youkersessiondbus.h"

PanelWidget::PanelWidget(QWidget *parent, SessionDispatcher *proxy) :
    QWidget(parent),
    sessionproxy(proxy)
{
//    splitter = new QSplitter();
//    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    splitter->setOrientation(Qt::Vertical);
//    splitter->setHandleWidth(1);

//    top_widget = new QWidget();
//    bottom_widget = new QWidget();

//    title_label = new QLabel();
//    title_label->setFixedHeight(20);
//    description_label = new QLabel();
//    description_label->setFixedHeight(20);
//    back_btn = new QPushButton();

//    QVBoxLayout *v_layout = new QVBoxLayout();
//    v_layout->addWidget(title_label);
//    v_layout->addWidget(description_label);
//    v_layout->setMargin(0);
//    v_layout->setSpacing(1);

//    QHBoxLayout *h_layout = new QHBoxLayout();
//    h_layout->addWidget(back_btn);
//    h_layout->addLayout(v_layout);
//    h_layout->addStretch();
//    top_widget->setLayout(h_layout);
//    top_widget->setFixedSize(900,60);
//    h_layout->setSpacing(20);
//    h_layout->setContentsMargins(20, 0, 0, 0);

    blur_label = new QLabel();
    transparency_label = new QLabel();
    date_format_label = new QLabel();
    second_label = new QLabel();
    week_label = new QLabel();
    date_label = new QLabel();
    battery_icon_label = new QLabel();
    battery_percentage_label = new QLabel();
    battery_time_label = new QLabel();

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

    blur_label->setFixedWidth(220);
    transparency_label->setFixedWidth(220);
    date_format_label->setFixedWidth(220);
    second_label->setFixedWidth(220);
    week_label->setFixedWidth(220);
    date_label->setFixedWidth(220);
    battery_icon_label->setFixedWidth(220);
    battery_percentage_label->setFixedWidth(220);
    battery_time_label->setFixedWidth(220);

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
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
    layout->addLayout(layout5);
    layout->addLayout(layout6);
    if(sessionproxy->judge_power_is_exists_qt())
    {
        layout->addLayout(layout7);
        layout->addLayout(layout8);
        layout->addLayout(layout9);
    }

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
    this->initData();
    this->setLanguage();
    this->initConnect();
}

PanelWidget::~PanelWidget()
{
//    if(label != NULL)
//    {
//        delete label;
//        label = NULL;
//    }
//    if(back_btn != NULL)
//    {
//        delete back_btn;
//        back_btn = NULL;
//    }
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

}

void PanelWidget::initData()
{
    int default_value = sessionproxy->get_dash_blur_experimental_qt();
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
    QStringList powerlist  = sessionproxy->get_all_power_icon_policy_qt();
    battery_combo->clear();
    battery_combo->clearEditText();
    battery_combo->addItems(powerlist);
    QList<QString>::Iterator ite = powerlist.begin(), iteend = powerlist.end();
    int index = 0;
    for(;ite != iteend; ite++,index++)
    {
        if(*ite == cur_power)
            break;
    }
    battery_combo->setCurrentIndex(index);

    battery_percentage_switcher->switchedOn = sessionproxy->get_show_power_percentage_qt();
    battery_time_switcher->switchedOn = sessionproxy->get_show_power_time_qt();
}

void PanelWidget::initConnect() {
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
    connect(smart_radio, SIGNAL(clicked(/*bool*/)), this, SLOT(setRadioButtonRowStatus(/*bool*/)));
    connect(static_radio, SIGNAL(clicked(/*bool*/)), this, SLOT(setRadioButtonRowStatus(/*bool*/)));
    connect(clear_radio, SIGNAL(clicked(/*bool*/)), this, SLOT(setRadioButtonRowStatus(/*bool*/)));
    connect(transparency_slider, SIGNAL(valueChanged(double)), this, SLOT(setTransparencyValue(double)));
    connect(date_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setDateFormat(QString)));
    connect(second_switcher, SIGNAL(clicked()),  this, SLOT(setDisplaySeconds()));
    connect(week_switcher, SIGNAL(clicked()),  this, SLOT(setDisplayWeek()));
    connect(date_switcher, SIGNAL(clicked()),  this, SLOT(setDisplayDate()));
    connect(battery_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setShowBatteryIcon(QString)));
    connect(battery_percentage_switcher, SIGNAL(clicked()),  this, SLOT(setDisplayBatteryPercentage()));
    connect(battery_time_switcher, SIGNAL(clicked()),  this, SLOT(setDisplayBatteryTime()));
}

void PanelWidget::setTransparencyValue(double value)
{
    sessionproxy->set_panel_transparency_qt(value);
}

void PanelWidget::setDateFormat(QString selected) {
    sessionproxy->set_time_format_qt(selected);
}

void PanelWidget::setShowBatteryIcon(QString selected) {
    sessionproxy->set_power_icon_policy_qt(selected);
}

void PanelWidget::setRadioButtonRowStatus(/*bool status*/)
{
    QObject *obj = sender(); //返回发出信号的对象，用QObject类型接收
    QRadioButton* pbtn = qobject_cast<QRadioButton*>(obj);
    QString obj_name = pbtn->objectName();
    if(obj_name == "smart_radio")
    {
        sessionproxy->set_cursor_size_qt(24);
//        qDebug() << "small radio clicked";
    }
    else if(obj_name == "static_radio")
    {
        sessionproxy->set_cursor_size_qt(48);
//        qDebug() << "big radio clicked";
    }
    else if(obj_name == "clear_radio")
    {
        sessionproxy->set_cursor_size_qt(48);
//        qDebug() << "big radio clicked";
    }
}

void PanelWidget::setDisplaySeconds()
{
    sessionproxy->set_show_seconds_qt(second_switcher->switchedOn);
}

void PanelWidget::setDisplayWeek()
{
    sessionproxy->set_show_week_qt(week_switcher->switchedOn);
}

void PanelWidget::setDisplayDate()
{
    sessionproxy->set_show_date_qt(date_switcher->switchedOn);
}

void PanelWidget::setDisplayBatteryPercentage()
{
    sessionproxy->set_show_power_percentage_qt(battery_percentage_switcher->switchedOn);
}

void PanelWidget::setDisplayBatteryTime()
{
    sessionproxy->set_show_power_time_qt(battery_time_switcher->switchedOn);
}
