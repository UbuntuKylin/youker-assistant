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

#include "launcherwidget.h"
#include <QDebug>
#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include "../dbusproxy/youkersessiondbus.h"

LauncherWidget::LauncherWidget(QWidget *parent, SessionDispatcher *proxy, QString cur_desktop) :
    QWidget(parent),desktop(cur_desktop),
    sessionproxy(proxy)
{
    dataOK = false;
    size_label = new QLabel();
    size_value_label = new QLabel();
    hide_label = new QLabel();
    icon_label = new QLabel();
    transparency_label = new QLabel();
    background_label = new QLabel();
    size_top_label = new QLabel();
    hide_top_label = new QLabel();
    size_top_value_label = new QLabel();
    size_bottom_label = new QLabel();
    hide_bottom_label = new QLabel();
    size_bottom_value_label = new QLabel();
    position_label = new QLabel();

//    QLabel *size_top_label;
//    QLabel *hide_top_label;
//    QLabel *size_bottom_label;
//    QLabel *hide_bottom_label;

    size_slider = new QSlider(Qt::Horizontal);
//    size_slider->setTickPosition(QSlider::TicksRight);
    size_slider->setFocusPolicy(Qt::NoFocus);
    size_slider->setRange(32, 64);
    size_slider->setSingleStep(1);
//    size_slider->setMinimum(1);
//    size_slider->setMaximum(10);

    hide_switcher = new KylinSwitcher();
    icon_switcher = new KylinSwitcher();
    transparency_slider = new QDoubleSpinBox();
    transparency_slider->setButtonSymbols(QAbstractSpinBox::PlusMinus);
    transparency_slider->setSingleStep(0.1);
    transparency_slider->setMinimum(0.0);
    transparency_slider->setMaximum(1.0);
    backgound_combo = new QComboBox();

    size_top_slider = new QSlider(Qt::Horizontal);
    size_top_slider->setFocusPolicy(Qt::NoFocus);
    size_top_slider->setRange(24, 180);
    size_top_slider->setSingleStep(1);
    size_bottom_slider = new QSlider(Qt::Horizontal);
    size_bottom_slider->setFocusPolicy(Qt::NoFocus);
    size_bottom_slider->setRange(24, 180);
    size_bottom_slider->setSingleStep(1);
    hide_top_switcher = new KylinSwitcher();
    hide_bottom_switcher = new KylinSwitcher();

    position_combo = new QComboBox();

//    QSlider *size_top_slider;
//    QSlider *size_bottom_slider;
//    KylinSwitcher *hide_top_switcher;
//    KylinSwitcher *icon_bottom_switcher;

    if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui") {
        size_label->hide();
        size_value_label->hide();
        hide_label->hide();
        icon_label->hide();
        transparency_label->hide();
        background_label->hide();
        position_label->hide();
        size_slider->hide();
        hide_switcher->hide();
        icon_switcher->hide();
        transparency_slider->hide();;
        backgound_combo->hide();
        position_combo->hide();
    }
    else
    {
        size_top_label->hide();
        hide_top_label->hide();
        size_top_value_label->hide();
        size_bottom_label->hide();
        hide_bottom_label->hide();
        size_bottom_value_label->hide();
        size_top_slider->hide();
        size_bottom_slider->hide();
        hide_top_switcher->hide();
        hide_bottom_switcher->hide();
    }

    size_label->setFixedWidth(180);
    hide_label->setFixedWidth(180);
    icon_label->setFixedWidth(180);
    transparency_label->setFixedWidth(180);
    background_label->setFixedWidth(180);
    size_top_label->setFixedWidth(180);
    hide_top_label->setFixedWidth(180);
    size_bottom_label->setFixedWidth(180);
    hide_bottom_label->setFixedWidth(180);
    position_label->setFixedWidth(180);

    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->setSpacing(10);
    layout1->addWidget(size_label);
    layout1->addWidget(size_slider);
    layout1->addWidget(size_value_label);
    layout1->addStretch();
    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->setSpacing(10);
    layout2->addWidget(hide_label);
    layout2->addWidget(hide_switcher);
    layout2->addStretch();
    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->setSpacing(10);
    layout3->addWidget(icon_label);
    layout3->addWidget(icon_switcher);
    layout3->addStretch();
    QHBoxLayout *layout4 = new QHBoxLayout();
    layout4->setSpacing(10);
    layout4->addWidget(transparency_label);
    layout4->addWidget(transparency_slider);
    layout4->addStretch();
    QHBoxLayout *layout5 = new QHBoxLayout();
    layout5->setSpacing(10);
    layout5->addWidget(background_label);
    layout5->addWidget(backgound_combo);
    layout5->addStretch();

    QHBoxLayout *layout6 = new QHBoxLayout();
    layout6->setSpacing(10);
    layout6->addWidget(size_top_label);
    layout6->addWidget(size_top_slider);
    layout6->addWidget(size_top_value_label);
    layout6->addStretch();
    QHBoxLayout *layout7 = new QHBoxLayout();
    layout7->setSpacing(10);
    layout7->addWidget(hide_top_label);
    layout7->addWidget(hide_top_switcher);
    layout7->addStretch();
    QHBoxLayout *layout8 = new QHBoxLayout();
    layout8->setSpacing(10);
    layout8->addWidget(size_bottom_label);
    layout8->addWidget(size_bottom_slider);
    layout8->addWidget(size_bottom_value_label);
    layout8->addStretch();
    QHBoxLayout *layout9 = new QHBoxLayout();
    layout9->setSpacing(10);
    layout9->addWidget(hide_bottom_label);
    layout9->addWidget(hide_bottom_switcher);
    layout9->addStretch();
    QHBoxLayout *layout10 = new QHBoxLayout();
    layout10->setSpacing(10);
    layout10->addWidget(position_label);
    layout10->addWidget(position_combo);
    layout10->addStretch();

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout10);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
    layout->addLayout(layout5);
    layout->addLayout(layout6);
    layout->addLayout(layout7);
    layout->addLayout(layout8);
    layout->addLayout(layout9);
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
//    this->initData();
    this->setLanguage();
}

LauncherWidget::~LauncherWidget()
{
    if (size_label != NULL) {
        delete size_label;
        size_label = NULL;
    }
    if (size_value_label != NULL) {
        delete size_value_label;
        size_value_label = NULL;
    }
    if (hide_label != NULL) {
        delete hide_label;
        hide_label = NULL;
    }
    if (icon_label != NULL) {
        delete icon_label;
        icon_label = NULL;
    }
    if (transparency_label != NULL) {
        delete transparency_label;
        transparency_label = NULL;
    }
    if (background_label != NULL) {
        delete background_label;
        background_label = NULL;
    }
    if (size_top_label != NULL) {
        delete size_top_label;
        size_top_label = NULL;
    }
    if (hide_top_label != NULL) {
        delete hide_top_label;
        hide_top_label = NULL;
    }
    if (position_label != NULL) {
        delete position_label;
        position_label = NULL;
    }
    if (size_top_value_label != NULL) {
        delete size_top_value_label;
        size_top_value_label = NULL;
    }
    if (size_bottom_label != NULL) {
        delete size_bottom_label;
        size_bottom_label = NULL;
    }
    if (hide_bottom_label != NULL) {
        delete hide_bottom_label;
        hide_bottom_label = NULL;
    }
    if (size_bottom_value_label != NULL) {
        delete size_bottom_value_label;
        size_bottom_value_label = NULL;
    }
    if (size_slider != NULL) {
        delete size_slider;
        size_slider = NULL;
    }
    if (hide_switcher != NULL) {
        delete hide_switcher;
        hide_switcher = NULL;
    }
    if (icon_switcher != NULL) {
        delete icon_switcher;
        icon_switcher = NULL;
    }
    if (transparency_slider != NULL) {
        delete transparency_slider;
        transparency_slider = NULL;
    }
    if (backgound_combo != NULL) {
        delete backgound_combo;
        backgound_combo = NULL;
    }
    if (size_top_slider != NULL) {
        delete size_top_slider;
        size_top_slider = NULL;
    }
    if (size_bottom_slider != NULL) {
        delete size_bottom_slider;
        size_bottom_slider = NULL;
    }
    if (hide_top_switcher != NULL) {
        delete hide_top_switcher;
        hide_top_switcher = NULL;
    }
    if (hide_bottom_switcher != NULL) {
        delete hide_bottom_switcher;
        hide_bottom_switcher = NULL;
    }
    if (position_combo != NULL) {
        delete position_combo;
        position_combo = NULL;
    }

}

void LauncherWidget::setLanguage() {
//    title_label->setText(tr("Launcher settings"));
//    description_label->setText(tr("Setting the Launcher display mode, Icon size."));
//    back_btn->setText(tr("Back"));
    size_label->setText(tr("Launcher icon size") + ":");
    hide_label->setText(tr("Launcher hide mode") + ":");
    icon_label->setText(tr("Display desktop icon") + ":");
    transparency_label->setText(tr("Launcher Transparency") + ":");
    background_label->setText(tr("Icon Background") + ":");
    size_top_label->setText(tr("Top panel icon size") + ":");
    hide_top_label->setText(tr("Top panel auto hide") + ":");
    size_bottom_label->setText(tr("Bottom panel icon size") + ":");
    hide_bottom_label->setText(tr("Bottom panel auto hide") + ":");
    position_label->setText(tr("Launcher position") + ":");
}

bool LauncherWidget::getStatus()
{
    return this->dataOK;
}

void LauncherWidget::initData()
{
    if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui") {
        size_top_slider->setValue(sessionproxy->get_mate_panel_icon_size_qt("top"));
        size_top_value_label->setText(QString::number(size_top_slider->value()));
        size_bottom_slider->setValue(sessionproxy->get_mate_panel_icon_size_qt("bottom"));
        size_bottom_value_label->setText(QString::number(size_bottom_slider->value()));
        hide_top_switcher->switchedOn = sessionproxy->get_mate_panel_autohide_qt("top");
        hide_bottom_switcher->switchedOn = sessionproxy->get_mate_panel_autohide_qt("bottom");
    }
    else
    {
        size_slider->setValue(sessionproxy->get_launcher_icon_size_qt());
        size_value_label->setText(QString::number(size_slider->value()));
        hide_switcher->switchedOn = sessionproxy->get_launcher_autohide_qt();
        icon_switcher->switchedOn = sessionproxy->get_launcher_have_showdesktopicon_qt();
        transparency_slider->setValue(sessionproxy->get_launcher_transparency_qt());
        int cur_index = sessionproxy->get_launcher_icon_colouring_qt();
        QString current_icon_colouring = "";
        if (cur_index == 0) {
            current_icon_colouring = "all programs";
        }
        else if (cur_index == 1) {
            current_icon_colouring = "only run app";
        }
        else if (cur_index == 2) {
            current_icon_colouring = "no coloring";
        }
        else if (cur_index == 3) {
            current_icon_colouring = "edge coloring";
        }
        else if (cur_index == 4) {
            current_icon_colouring = "each workspace alternating coloring";
        }
        /*QStringList */colourlist  = sessionproxy->get_all_launcher_icon_colourings_qt();
        backgound_combo->clear();
        backgound_combo->clearEditText();
        backgound_combo->addItems(colourlist);
        QList<QString>::Iterator it = colourlist.begin(), itend = colourlist.end();
        int initIndex = 0;
        for(;it != itend; it++,initIndex++)
        {
            if(*it == current_icon_colouring)
                break;
        }
        backgound_combo->setCurrentIndex(initIndex);

        QString current_position = sessionproxy->get_current_launcher_position_qt();
        positionlist  = sessionproxy->get_all_launcher_position_qt();
        position_combo->clear();
        position_combo->clearEditText();
        position_combo->addItems(positionlist);
        QList<QString>::Iterator it2 = positionlist.begin(), itend2 = positionlist.end();
        initIndex = 0;
        for(;it2 != itend2; it2++,initIndex++)
        {
            if(*it2 == current_position)
                break;
        }
        position_combo->setCurrentIndex(initIndex);
    }

    dataOK = true;
    this->initConnect();
}

void LauncherWidget::initConnect() {
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
    connect(size_slider, SIGNAL(valueChanged(int)), this, SLOT(setIconSizeValue(int)));
    connect(hide_switcher, SIGNAL(clicked()),  this, SLOT(setAutoHide()));
    connect(icon_switcher, SIGNAL(clicked()),  this, SLOT(setDisplayDesktopIcon()));
    connect(transparency_slider, SIGNAL(valueChanged(double)), this, SLOT(setTransparencyValue(double)));
    connect(backgound_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setIconColouring(QString)));
    connect(position_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setLauncherPosition(QString)));

    connect(size_top_slider, SIGNAL(valueChanged(int)), this, SLOT(setTopIconSizeValue(int)));
    connect(size_bottom_slider, SIGNAL(valueChanged(int)), this, SLOT(setBottomIconSizeValue(int)));
    connect(hide_top_switcher, SIGNAL(clicked()),  this, SLOT(setTopAutoHide()));
    connect(hide_bottom_switcher, SIGNAL(clicked()),  this, SLOT(setBottomAutoHide()));

    connect(sessionproxy, SIGNAL(bool_value_notify(QString, bool)), this, SLOT(launcherwidget_notify_bool(QString, bool)));
    connect(sessionproxy, SIGNAL(double_value_notify(QString, double)), this, SLOT(launcherwidget_notify_double(QString, double)));
    connect(sessionproxy, SIGNAL(int_value_notify(QString, int)), this, SLOT(launcherwidget_notify_int(QString, int)));
    connect(sessionproxy, SIGNAL(string_value_notify(QString, QString)), this, SLOT(launcherwidget_notify_string(QString, QString)));
}

void LauncherWidget::launcherwidget_notify_double(QString key, double value)
{
    if (key == "launcher-opacity") {
        transparency_slider->setValue(value);
    }
}

void LauncherWidget::launcherwidget_notify_bool(QString key, bool value)
{
    if (key == "auto-hide-top") {
        hide_top_switcher->switchedOn = value;
    }
    else if (key == "auto-hide-bottom") {
        hide_bottom_switcher->switchedOn = value;
    }
}

void LauncherWidget::launcherwidget_notify_int(QString key, int value)
{
    if (key == "icon-size") {
        size_slider->setValue(value);
        size_value_label->setText(QString::number(value));
    }
    else if (key == "launcher-hide-mode") {
        if (value == 0)
            hide_switcher->switchedOn = false;
        else if (value == 1)
            hide_switcher->switchedOn = true;
    }
    else if (key == "backlight-mode") {
        QString current_icon_colouring = "";
        if (value == 0) {
            current_icon_colouring = "all programs";
        }
        else if (value == 1) {
            current_icon_colouring = "only run app";
        }
        else if (value == 2) {
            current_icon_colouring = "no coloring";
        }
        else if (value == 3) {
            current_icon_colouring = "edge coloring";
        }
        else if (value == 4) {
            current_icon_colouring = "each workspace alternating coloring";
        }
        QList<QString>::Iterator it = colourlist.begin(), itend = colourlist.end();
        int index = -1;
        bool exist = false;
        for(;it != itend; it++)
        {
            ++index;
            if(*it == current_icon_colouring) {
                exist = true;
                break;
            }
        }
        if (exist) {
            exist = false;
            backgound_combo->setCurrentIndex(index);
        }
        else
            backgound_combo->setCurrentIndex(-1);
    }
    else if (key == "size-top") {
        size_top_slider->setValue(value);
        size_top_value_label->setText(QString::number(value));
    }
    else if (key == "size-bottom") {
        size_bottom_slider->setValue(value);
        size_bottom_value_label->setText(QString::number(value));
    }
}

void LauncherWidget::launcherwidget_notify_string(QString key, QString value)
{
    if (key == "launcher-position") {
        QList<QString>::Iterator it = positionlist.begin(), itend = positionlist.end();
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
            position_combo->setCurrentIndex(index);
        }
        else
            position_combo->setCurrentIndex(-1);
    }
}

void LauncherWidget::setIconSizeValue(int value) {
    size_value_label->setText(QString::number(value));
    sessionproxy->set_launcher_icon_size_qt(value);
}

void LauncherWidget::setTransparencyValue(double value)
{
    sessionproxy->set_launcher_transparency_qt(value);
}

void LauncherWidget::setIconColouring(QString selectColour) {
    if (selectColour == "all programs") {
        sessionproxy->set_launcher_icon_colouring_qt(0);
    }
    else if (selectColour == "only run app") {
        sessionproxy->set_launcher_icon_colouring_qt(1);
    }
    else if (selectColour == "no coloring") {
        sessionproxy->set_launcher_icon_colouring_qt(2);
    }
    else if (selectColour == "edge coloring") {
        sessionproxy->set_launcher_icon_colouring_qt(3);
    }
    else if (selectColour == "each workspace alternating coloring") {
        sessionproxy->set_launcher_icon_colouring_qt(4);
    }
}

void LauncherWidget::setAutoHide() {
    sessionproxy->set_launcher_autohide_qt(hide_switcher->switchedOn);
}

void LauncherWidget::setDisplayDesktopIcon() {
    sessionproxy->set_launcher_have_showdesktopicon_qt(icon_switcher->switchedOn);
}

void LauncherWidget::setTopIconSizeValue(int value){
    size_top_value_label->setText(QString::number(value));
    sessionproxy->set_mate_panel_icon_size_qt("top", value);
}

void LauncherWidget::setBottomIconSizeValue(int value){
    size_bottom_value_label->setText(QString::number(value));
    sessionproxy->set_mate_panel_icon_size_qt("bottom", value);
}

void LauncherWidget::setTopAutoHide() {
    sessionproxy->set_mate_panel_autohide_qt("top", hide_top_switcher->switchedOn);
}

void LauncherWidget::setBottomAutoHide() {
    sessionproxy->set_mate_panel_autohide_qt("bottom", hide_bottom_switcher->switchedOn);
}

void LauncherWidget::setLauncherPosition(QString position) {
    sessionproxy->set_launcher_position_qt(position);
}
