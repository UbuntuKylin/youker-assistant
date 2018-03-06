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

#include "touchpadwidget.h"
#include <QDebug>
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include <QButtonGroup>
#include <QHBoxLayout>
#include <QVBoxLayout>

TouchpadWidget::TouchpadWidget(QWidget *parent, QString cur_desktop) :
    SettingModulePage(parent),
    desktop(cur_desktop)
{
    touchpad_label = new QLabel();
    horizontal_scrolling_label = new QLabel();
    scrollbar_type_label = new QLabel();
    scrolling_mode_label = new QLabel();
    touchpad_switcher  = new KylinSwitcher();
    horizontal_scrolling_switcher  = new KylinSwitcher();
    features_radio = new QRadioButton();
    features_radio->setFocusPolicy(Qt::NoFocus);
//    features_radio->setChecked(true);
    features_radio->setObjectName("features_radio");
    standard_radio = new QRadioButton();
    standard_radio->setFocusPolicy(Qt::NoFocus);
//    standard_radio->setChecked(false);
    standard_radio->setObjectName("standard_radio");
    QButtonGroup *btnGroup1 = new QButtonGroup();
    btnGroup1->addButton(features_radio);
    btnGroup1->addButton(standard_radio);

    disable_radio = new QRadioButton();
    disable_radio->setFocusPolicy(Qt::NoFocus);
    disable_radio->setObjectName("disable_radio");
    edge_radio = new QRadioButton();
    edge_radio->setFocusPolicy(Qt::NoFocus);
//    edge_radio->setChecked(true);
    edge_radio->setObjectName("edge_radio");
    two_finger_radio = new QRadioButton();
    two_finger_radio->setFocusPolicy(Qt::NoFocus);
//    two_finger_radio->setChecked(false);
    two_finger_radio->setObjectName("two_finger_radio");
    QButtonGroup *btnGroup2 = new QButtonGroup();
    btnGroup2->addButton(disable_radio);
    btnGroup2->addButton(edge_radio);
    btnGroup2->addButton(two_finger_radio);

    if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui") {
        scrollbar_type_label->hide();
        features_radio->hide();
        standard_radio->hide();
    }

    touchpad_label->setFixedWidth(180);
    horizontal_scrolling_label->setFixedWidth(180);
    scrollbar_type_label->setFixedWidth(180);
    scrolling_mode_label->setFixedWidth(180);

    //20180101
    //kobe1510
    /*this->release = sessionproxy->get_os_release_qt();
    if(this->release.endsWith("15.10-wily")) {
        touchpad_label->hide();
        touchpad_switcher->hide();
        horizontal_scrolling_label->hide();
        horizontal_scrolling_switcher->hide();
        scrollbar_type_label->hide();
        features_radio->hide();
        standard_radio->hide();
    }*/

    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->setSpacing(10);
    layout1->addWidget(touchpad_label);
    layout1->addWidget(touchpad_switcher);
    layout1->addStretch();
    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->setSpacing(10);
    layout2->addWidget(horizontal_scrolling_label);
    layout2->addWidget(horizontal_scrolling_switcher);
    layout2->addStretch();
    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->setSpacing(10);
    layout3->addWidget(scrollbar_type_label);
    layout3->addWidget(features_radio);
    layout3->addWidget(standard_radio);
    layout3->addStretch();
    QHBoxLayout *layout4 = new QHBoxLayout();
    layout4->setSpacing(10);
    layout4->addWidget(scrolling_mode_label);
    layout4->addWidget(disable_radio);
    layout4->addWidget(edge_radio);
    layout4->addWidget(two_finger_radio);
    layout4->addStretch();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
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

TouchpadWidget::~TouchpadWidget()
{
    if (touchpad_label != NULL) {
        delete touchpad_label;
        touchpad_label = NULL;
    }
    if (horizontal_scrolling_label != NULL) {
        delete horizontal_scrolling_label;
        horizontal_scrolling_label = NULL;
    }
    if (scrollbar_type_label != NULL) {
        delete scrollbar_type_label;
        scrollbar_type_label = NULL;
    }
    if (scrolling_mode_label != NULL) {
        delete scrolling_mode_label;
        scrolling_mode_label = NULL;
    }
    if (touchpad_switcher != NULL) {
        delete touchpad_switcher;
        touchpad_switcher = NULL;
    }
    if (horizontal_scrolling_switcher != NULL) {
        delete horizontal_scrolling_switcher;
        horizontal_scrolling_switcher = NULL;
    }
    if (features_radio != NULL) {
        delete features_radio;
        features_radio = NULL;
    }
    if (standard_radio != NULL) {
        delete standard_radio;
        standard_radio = NULL;
    }
    if (disable_radio != NULL) {
        delete disable_radio;
        disable_radio = NULL;
    }
    if (edge_radio != NULL) {
        delete edge_radio;
        edge_radio = NULL;
    }
    if (two_finger_radio != NULL) {
        delete two_finger_radio;
        two_finger_radio = NULL;
    }
}

QString TouchpadWidget::settingModuleName()
{
    return "TouchPadPage";
}

void TouchpadWidget::setLanguage() {
//    title_label->setText(tr("Touchpad settings"));
//    description_label->setText(tr("Setting the relevant properties of your touchpad,make the operation more convenient."));
//    back_btn->setText(tr("Back"));
    touchpad_label->setText(tr("Enable touchpad") + ":");
    horizontal_scrolling_label->setText(tr("Enable horizontal scrolling") + ":");
    scrollbar_type_label->setText(tr("Scrollbar type") + ":");
    scrolling_mode_label->setText(tr("Touchpad scrolling mode") + ":");//触摸板滚动模式
    features_radio->setText(tr("Features Type"));
    standard_radio->setText(tr("Standard Type"));
    disable_radio->setText(tr("Disabled"));//禁用
    edge_radio->setText(tr("Edge Scrolling"));//边界滚动
    two_finger_radio->setText(tr("Two-finger Scrolling"));//双指滚动
}

void TouchpadWidget::initSettingData()
{
    if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui")
    {
        emit requestMateOrUnityTouchpadData(true);
    }
    else {
        emit requestMateOrUnityTouchpadData(false);
    }


    //kobe1510
    /*if(!this->release.endsWith("15.10-wily")) {
        touchpad_switcher->switchedOn = sessionproxy->get_touchpad_enable_qt();
        horizontal_scrolling_switcher->switchedOn = sessionproxy->get_touchscrolling_use_horizontal_qt();
        QString mode_value = sessionproxy->get_scrollbars_mode_qt();
        if(mode_value == "overlay-auto") {
            features_radio->setChecked(true);
            standard_radio->setChecked(false);
        }
        else if(mode_value == "normal") {
            standard_radio->setChecked(true);
            features_radio->setChecked(false);
        }
    }
    if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui")
    {
        int scroll_value = sessionproxy->get_mate_touchscrolling_mode_qt();
        if(scroll_value == 0) {
            disable_radio->setChecked(true);
            edge_radio->setChecked(false);
            two_finger_radio->setChecked(false);
        }
        else if(scroll_value == 1) {
            edge_radio->setChecked(true);
            disable_radio->setChecked(false);
            two_finger_radio->setChecked(false);
        }
        else if(scroll_value == 2) {
            two_finger_radio->setChecked(true);
            disable_radio->setChecked(false);
            edge_radio->setChecked(false);
        }
    }
    else
    {
        QString scroll_value = sessionproxy->get_touchscrolling_mode_qt();
        if(scroll_value == "disabled") {
            disable_radio->setChecked(true);
            edge_radio->setChecked(false);
            two_finger_radio->setChecked(false);
        }
        else if(scroll_value == "edge-scrolling") {
            edge_radio->setChecked(true);
            disable_radio->setChecked(false);
            two_finger_radio->setChecked(false);
        }
        else if(scroll_value == "two-finger-scrolling") {
            two_finger_radio->setChecked(true);
            disable_radio->setChecked(false);
            edge_radio->setChecked(false);
        }
    }*/

    this->initConnect();
}

void TouchpadWidget::onSendTouchPadValue(bool touchpadEnable, bool touchscrollingHorizontal, const QString &mode_value, int scroll_int_value, const QString &scroll_string_value)
{
    touchpad_switcher->switchedOn = touchpadEnable;
    horizontal_scrolling_switcher->switchedOn = touchscrollingHorizontal;
    if(mode_value == "overlay-auto") {
        features_radio->setChecked(true);
        standard_radio->setChecked(false);
    }
    else if(mode_value == "normal") {
        standard_radio->setChecked(true);
        features_radio->setChecked(false);
    }

    if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui")
    {
        if(scroll_int_value == 0) {
            disable_radio->setChecked(true);
            edge_radio->setChecked(false);
            two_finger_radio->setChecked(false);
        }
        else if(scroll_int_value == 1) {
            edge_radio->setChecked(true);
            disable_radio->setChecked(false);
            two_finger_radio->setChecked(false);
        }
        else if(scroll_int_value == 2) {
            two_finger_radio->setChecked(true);
            disable_radio->setChecked(false);
            edge_radio->setChecked(false);
        }
    }
    else
    {
        if(scroll_string_value == "disabled") {
            disable_radio->setChecked(true);
            edge_radio->setChecked(false);
            two_finger_radio->setChecked(false);
        }
        else if(scroll_string_value == "edge-scrolling") {
            edge_radio->setChecked(true);
            disable_radio->setChecked(false);
            two_finger_radio->setChecked(false);
        }
        else if(scroll_string_value == "two-finger-scrolling") {
            two_finger_radio->setChecked(true);
            disable_radio->setChecked(false);
            edge_radio->setChecked(false);
        }
    }
}

void TouchpadWidget::initConnect() {
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
    connect(touchpad_switcher, SIGNAL(clicked()),  this, SLOT(setTouchpad()));
    connect(horizontal_scrolling_switcher, SIGNAL(clicked()),  this, SLOT(setHorizontalScrolling()));
    connect(features_radio, SIGNAL(clicked(/*bool*/)), this, SLOT(setRadioButtonRowStatus(/*bool*/)));
    connect(standard_radio, SIGNAL(clicked(/*bool*/)), this, SLOT(setRadioButtonRowStatus(/*bool*/)));
    connect(disable_radio, SIGNAL(clicked(/*bool*/)), this, SLOT(setRadioButtonRowStatus(/*bool*/)));
    connect(edge_radio, SIGNAL(clicked(/*bool*/)), this, SLOT(setRadioButtonRowStatus(/*bool*/)));
    connect(two_finger_radio, SIGNAL(clicked(/*bool*/)), this, SLOT(setRadioButtonRowStatus(/*bool*/)));

//    connect(sessionproxy, SIGNAL(string_value_notify(QString, QString)), this, SLOT(touchpadwidget_notify_string(QString, QString)));
//    connect(sessionproxy, SIGNAL(bool_value_notify(QString, bool)), this, SLOT(touchpadwidget_notify_bool(QString, bool)));
//    connect(sessionproxy, SIGNAL(int_value_notify(QString, int)), this, SLOT(touchpadwidget_notify_int(QString, int)));
}

void TouchpadWidget::touchpadwidget_notify_string(QString key, QString value)
{
    if (key == "scroll-method") {
        if(value == "disabled") {
            disable_radio->setChecked(true);
            edge_radio->setChecked(false);
            two_finger_radio->setChecked(false);
        }
        else if(value == "edge-scrolling") {
            edge_radio->setChecked(true);
            disable_radio->setChecked(false);
            two_finger_radio->setChecked(false);
        }
        else if(value == "two-finger-scrolling") {
            two_finger_radio->setChecked(true);
            disable_radio->setChecked(false);
            edge_radio->setChecked(false);
        }
    }
    else if (key == "scrollbar-mode") {
        if(value == "overlay-auto") {
            features_radio->setChecked(true);
            standard_radio->setChecked(false);
        }
        else if(value == "normal") {
            standard_radio->setChecked(true);
            features_radio->setChecked(false);
        }
    }
}

void TouchpadWidget::touchpadwidget_notify_bool(QString key, bool value)
{
    if (key == "touchpad-enabled") {
        touchpad_switcher->switchedOn = value;
    }
    else if (key == "horiz-scroll-enabled") {
        horizontal_scrolling_switcher->switchedOn = value;
    }
}

void TouchpadWidget::touchpadwidget_notify_int(QString key, int value)
{
    if (key == "scroll-method") {
        if(value == 0) {
            disable_radio->setChecked(true);
            edge_radio->setChecked(false);
            two_finger_radio->setChecked(false);
        }
        else if(value == 1) {
            edge_radio->setChecked(true);
            disable_radio->setChecked(false);
            two_finger_radio->setChecked(false);
        }
        else if(value == 2) {
            two_finger_radio->setChecked(true);
            disable_radio->setChecked(false);
            edge_radio->setChecked(false);
        }
    }
}

void TouchpadWidget::setTouchpad()
{
    emit resetTouchpad(touchpad_switcher->switchedOn);
//    sessionproxy->set_touchpad_enable_qt(touchpad_switcher->switchedOn);
}

void TouchpadWidget::setHorizontalScrolling()
{
    emit resetHorizontalScrolling(horizontal_scrolling_switcher->switchedOn);
//    sessionproxy->set_touchscrolling_use_horizontal_qt(horizontal_scrolling_switcher->switchedOn);
}

void TouchpadWidget::setRadioButtonRowStatus(/*bool status*/)
{
    QObject *obj = sender(); //返回发出信号的对象，用QObject类型接收
    QRadioButton* pbtn = qobject_cast<QRadioButton*>(obj);
    QString obj_name = pbtn->objectName();
    if(obj_name == "features_radio")
    {
        emit setScrollbarOverlayOrLegacyMode(true);
//        sessionproxy->set_scrollbars_mode_overlay_qt();
    }
    else if(obj_name == "standard_radio")
    {
        emit setScrollbarOverlayOrLegacyMode(false);
//        sessionproxy->set_scrollbars_mode_legacy_qt();
    }
    else if(obj_name == "disable_radio")
    {
        if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui")
            emit setMateTouchscrollingMode(0);
//            sessionproxy->set_mate_touchscrolling_mode_qt(0);
        else {
            emit setUnityTouchscrollingMode(0);
//            sessionproxy->set_touchscrolling_mode_disabled_qt();
        }
    }
    else if(obj_name == "edge_radio")
    {
        if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui")
            emit setMateTouchscrollingMode(1);
//            sessionproxy->set_mate_touchscrolling_mode_qt(1);
        else {
            emit setUnityTouchscrollingMode(1);
//            sessionproxy->set_touchscrolling_mode_edge_qt();
        }
    }
    else if(obj_name == "two_finger_radio")
    {
        if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui")
            emit setMateTouchscrollingMode(2);
//            sessionproxy->set_mate_touchscrolling_mode_qt(2);
        else {
            emit setUnityTouchscrollingMode(2);
//            sessionproxy->set_touchscrolling_mode_twofinger_qt();
        }
    }
}
