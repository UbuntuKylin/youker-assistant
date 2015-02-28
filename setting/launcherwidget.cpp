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
#include "../dbusproxy/youkersessiondbus.h"

LauncherWidget::LauncherWidget(QWidget *parent, SessionDispatcher *proxy) :
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

    size_label = new QLabel();
    size_value_label = new QLabel();
    hide_label = new QLabel();
    icon_label = new QLabel();
    transparency_label = new QLabel();
    background_label = new QLabel();
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

    size_label->setFixedWidth(180);
    hide_label->setFixedWidth(180);
    icon_label->setFixedWidth(180);
    transparency_label->setFixedWidth(180);
    background_label->setFixedWidth(180);

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
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
    layout->addLayout(layout5);
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

LauncherWidget::~LauncherWidget()
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

void LauncherWidget::setLanguage() {
//    title_label->setText(tr("Launcher settings"));
//    description_label->setText(tr("Setting the Launcher display mode, Icon size."));
//    back_btn->setText(tr("Back"));
    size_label->setText(tr("Launcher icon size") + ":");
    hide_label->setText(tr("Launcher hide mode") + ":");
    icon_label->setText(tr("Display desktop icon") + ":");
    transparency_label->setText(tr("Launcher Transparency") + ":");
    background_label->setText(tr("Icon Background") + ":");

}

void LauncherWidget::initData()
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
    QStringList colourlist  = sessionproxy->get_all_launcher_icon_colourings_qt();
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

}

void LauncherWidget::initConnect() {
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
    connect(size_slider, SIGNAL(valueChanged(int)), this, SLOT(setIconSizeValue(int)));
    connect(hide_switcher, SIGNAL(clicked()),  this, SLOT(setAutoHide()));
    connect(icon_switcher, SIGNAL(clicked()),  this, SLOT(setDisplayDesktopIcon()));
    connect(transparency_slider, SIGNAL(valueChanged(double)), this, SLOT(setTransparencyValue(double)));
    connect(backgound_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setIconColouring(QString)));
}

void LauncherWidget::setIconSizeValue(int value){
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
