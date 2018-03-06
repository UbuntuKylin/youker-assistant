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

#include "menuwidget.h"
#include <QDebug>
#include <QLabel>
#include <QSlider>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QVBoxLayout>
#include <QHBoxLayout>

MenuWidget::MenuWidget(QWidget *parent, QString cur_desktop) :
    SettingModulePage(parent),desktop(cur_desktop)
{
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

    size_slider = new QSlider(Qt::Horizontal);
    size_slider->setFocusPolicy(Qt::NoFocus);
    size_slider->setRange(32, 64);
    size_slider->setSingleStep(1);

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
        transparency_slider->hide();
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

    this->setLanguage();
}

MenuWidget::~MenuWidget()
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

QString MenuWidget::settingModuleName()
{
    return "MenuPage";
}

void MenuWidget::setLanguage() {
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

void MenuWidget::initSettingData()
{
    if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui") {
        emit this->requestMateOrUnityMenuData(true);
    }
    else {
        emit this->requestMateOrUnityMenuData(false);
    }

    this->initConnect();
}

void MenuWidget::onSendMatePanelIconValue(int topIconSize, int bottomIconSize, bool topIconHide, bool bottomIconHide)
{
    size_top_slider->setValue(topIconSize);
    size_top_value_label->setText(QString::number(topIconSize));
    size_bottom_slider->setValue(bottomIconSize);
    size_bottom_value_label->setText(QString::number(bottomIconSize));
    hide_top_switcher->switchedOn = topIconHide;
    hide_bottom_switcher->switchedOn = bottomIconHide;
}

void MenuWidget::onSendUnityIconValue(int iconSize, bool iconHide, bool desktopIconShowed, double launcherTransparency, int iconColourIndex, const QStringList &colourlist)
{
    size_slider->setValue(iconSize);
    size_value_label->setText(QString::number(iconSize));
    hide_switcher->switchedOn = iconHide;
    icon_switcher->switchedOn = desktopIconShowed;
    transparency_slider->setValue(launcherTransparency);

    QString current_icon_colouring = "";
    if (iconColourIndex == 0) {
        current_icon_colouring = "all programs";
    }
    else if (iconColourIndex == 1) {
        current_icon_colouring = "only run app";
    }
    else if (iconColourIndex == 2) {
        current_icon_colouring = "no coloring";
    }
    else if (iconColourIndex == 3) {
        current_icon_colouring = "edge coloring";
    }
    else if (iconColourIndex == 4) {
        current_icon_colouring = "each workspace alternating coloring";
    }

    m_colourlist.clear();
    m_colourlist = colourlist;
    backgound_combo->clearEditText();
    backgound_combo->addItems(m_colourlist);
    QList<QString>::Iterator it = m_colourlist.begin(), itend = m_colourlist.end();
    int initIndex = 0;
    for(;it != itend; it++,initIndex++)
    {
        if(*it == current_icon_colouring)
            break;
    }
    backgound_combo->setCurrentIndex(initIndex);
}

void MenuWidget::onSendUnityLauncherPosition(const QString &current_position, const QStringList &positionlist)
{
    m_positionlist.clear();
    m_positionlist = positionlist;
    position_combo->clear();
    position_combo->clearEditText();
    position_combo->addItems(m_positionlist);
    QList<QString>::Iterator it2 = m_positionlist.begin(), itend2 = m_positionlist.end();
    int initIndex = 0;
    for(;it2 != itend2; it2++,initIndex++)
    {
        if(*it2 == current_position)
            break;
    }
    position_combo->setCurrentIndex(initIndex);
}

void MenuWidget::initConnect() {
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

//    connect(sessionproxy, SIGNAL(bool_value_notify(QString, bool)), this, SLOT(launcherwidget_notify_bool(QString, bool)));
//    connect(sessionproxy, SIGNAL(double_value_notify(QString, double)), this, SLOT(launcherwidget_notify_double(QString, double)));
//    connect(sessionproxy, SIGNAL(int_value_notify(QString, int)), this, SLOT(launcherwidget_notify_int(QString, int)));
//    connect(sessionproxy, SIGNAL(string_value_notify(QString, QString)), this, SLOT(launcherwidget_notify_string(QString, QString)));
}

void MenuWidget::launcherwidget_notify_double(QString key, double value)
{
    if (key == "launcher-opacity") {
        transparency_slider->setValue(value);
    }
}

void MenuWidget::launcherwidget_notify_bool(QString key, bool value)
{
    if (key == "auto-hide-top") {
        hide_top_switcher->switchedOn = value;
    }
    else if (key == "auto-hide-bottom") {
        hide_bottom_switcher->switchedOn = value;
    }
}

void MenuWidget::launcherwidget_notify_int(QString key, int value)
{
    if (key == "icon-size") {
        size_slider->setValue(value);
        size_value_label->setText(QString::number(value));
    }
    if (key == "launcher-hide-mode") {
        if (value == 0)
            hide_switcher->switchedOn = false;
        else if (value == 1)
            hide_switcher->switchedOn = true;
    }
    if (key == "backlight-mode") {
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
        QList<QString>::Iterator it = m_colourlist.begin(), itend = m_colourlist.end();
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
    if (key == "size-top") {
        size_top_slider->setValue(value);
        size_top_value_label->setText(QString::number(value));
    }
    else if (key == "size-bottom") {
        size_bottom_slider->setValue(value);
        size_bottom_value_label->setText(QString::number(value));
    }
}

void MenuWidget::launcherwidget_notify_string(QString key, QString value)
{
    if (key == "launcher-position") {
        QList<QString>::Iterator it = m_positionlist.begin(), itend = m_positionlist.end();
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

void MenuWidget::setIconSizeValue(int value) {
    size_value_label->setText(QString::number(value));
    emit resetIconSizeValue(value);
}

void MenuWidget::setTransparencyValue(double value)
{
    emit resetTransparencyValue(value);
}

void MenuWidget::setIconColouring(QString selectColour) {
    if (selectColour == "all programs") {
        emit this->resetIconColouring(0);
    }
    else if (selectColour == "only run app") {
        emit this->resetIconColouring(1);
    }
    else if (selectColour == "no coloring") {
        emit this->resetIconColouring(2);
    }
    else if (selectColour == "edge coloring") {
        emit this->resetIconColouring(3);
    }
    else if (selectColour == "each workspace alternating coloring") {
        emit this->resetIconColouring(4);
    }
}

void MenuWidget::setAutoHide() {
    emit this->resetAutoHide(hide_switcher->switchedOn);
}

void MenuWidget::setDisplayDesktopIcon() {
    emit this->resetDisplayDesktopIcon(icon_switcher->switchedOn);
}

void MenuWidget::setTopIconSizeValue(int value){
    size_top_value_label->setText(QString::number(value));
    emit this->resetTopIconSizeValue(value);
}

void MenuWidget::setBottomIconSizeValue(int value){
    size_bottom_value_label->setText(QString::number(value));
    emit this->resetBottomIconSizeValue(value);
}

void MenuWidget::setTopAutoHide() {
    emit this->resetTopAutoHide(hide_top_switcher->switchedOn);
}

void MenuWidget::setBottomAutoHide() {
    emit this->resetBottomAutoHide(hide_bottom_switcher->switchedOn);
}

void MenuWidget::setLauncherPosition(QString position) {
    emit this->resetLauncherPosition(position);
}
