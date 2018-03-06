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

#include "windowwidget.h"
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>
#include <QRadioButton>
#include <QDebug>

WindowWidget::WindowWidget(QWidget *parent, QString cur_desktop) :
    SettingModulePage(parent),desktop(cur_desktop)
{
    icon_label = new QLabel();
    wheel_label = new QLabel();
    double_click_label = new QLabel();
    middle_click_label = new QLabel();
    right_click_label = new QLabel();
    icon_switcher = new KylinSwitcher();
    wheel_combo = new QComboBox();
    double_click_combo = new QComboBox();
    middle_click_combo = new QComboBox();
    right_click_combo = new QComboBox();
    position_label = new QLabel();
    left_radio = new QRadioButton();
    right_radio = new QRadioButton();
    left_radio->setFocusPolicy(Qt::NoFocus);
    left_radio->setObjectName("leftradio");
    right_radio->setFocusPolicy(Qt::NoFocus);
    right_radio->setObjectName("rightradio");

    if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui") {
        icon_label->hide();
        icon_switcher->hide();
    }
    else {
        position_label->hide();
        left_radio->hide();
        right_radio->hide();
    }

    position_label->setFixedWidth(220);
    icon_label->setFixedWidth(220);
    wheel_label->setFixedWidth(220);
    double_click_label->setFixedWidth(220);
    middle_click_label->setFixedWidth(220);
    right_click_label->setFixedWidth(220);

    QHBoxLayout *layout0 = new QHBoxLayout();
    layout0->setSpacing(10);
    layout0->addWidget(position_label);
    layout0->addWidget(left_radio);
    layout0->addWidget(right_radio);
    layout0->addStretch();
    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->setSpacing(10);
    layout1->addWidget(icon_label);
    layout1->addWidget(icon_switcher);
    layout1->addStretch();
    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->setSpacing(10);
    layout2->addWidget(wheel_label);
    layout2->addWidget(wheel_combo);
    layout2->addStretch();
    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->setSpacing(10);
    layout3->addWidget(double_click_label);
    layout3->addWidget(double_click_combo);
    layout3->addStretch();
    QHBoxLayout *layout4 = new QHBoxLayout();
    layout4->setSpacing(10);
    layout4->addWidget(middle_click_label);
    layout4->addWidget(middle_click_combo);
    layout4->addStretch();
    QHBoxLayout *layout5 = new QHBoxLayout();
    layout5->setSpacing(10);
    layout5->addWidget(right_click_label);
    layout5->addWidget(right_click_combo);
    layout5->addStretch();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(layout0);
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
//    this->initSettingData();
    this->setLanguage();
}

WindowWidget::~WindowWidget()
{
    if (icon_label != NULL) {
        delete icon_label;
        icon_label = NULL;
    }
    if (wheel_label != NULL) {
        delete wheel_label;
        wheel_label = NULL;
    }
    if (double_click_label != NULL) {
        delete double_click_label;
        double_click_label = NULL;
    }
    if (middle_click_label != NULL) {
        delete middle_click_label;
        middle_click_label = NULL;
    }
    if (right_click_label != NULL) {
        delete right_click_label;
        right_click_label = NULL;
    }
    if (icon_switcher != NULL) {
        delete icon_switcher;
        icon_switcher = NULL;
    }
    if (wheel_combo != NULL) {
        delete wheel_combo;
        wheel_combo = NULL;
    }
    if (double_click_combo != NULL) {
        delete double_click_combo;
        double_click_combo = NULL;
    }
    if (middle_click_combo != NULL) {
        delete middle_click_combo;
        middle_click_combo = NULL;
    }
    if (right_click_combo != NULL) {
        delete right_click_combo;
        right_click_combo = NULL;
    }
    if (position_label != NULL) {
        delete position_label;
        position_label = NULL;
    }
    if (left_radio != NULL) {
        delete left_radio;
        left_radio = NULL;
    }
    if (right_radio != NULL) {
        delete right_radio;
        right_radio = NULL;
    }
}

QString WindowWidget::settingModuleName()
{
    return "WindowPage";
}

void WindowWidget::setLanguage() {
//    title_label->setText(tr("Window"));
//    description_label->setText(tr("Window Manager settings."));
//    back_btn->setText(tr("Back"));
    position_label->setText(tr("Arrangement of buttons on the titlebar") + ":");//标题栏按钮布局
    icon_label->setText(tr("Menu with icons") + ":");
    wheel_label->setText(tr("Titlebar mouse wheel action") + ":");
    double_click_label->setText(tr("Titlebar double-click action") + ":");
    middle_click_label->setText(tr("Titlebar middle-click action") + ":");
    right_click_label->setText(tr("Titlebar right-click action") + ":");
    left_radio->setText(tr("Left"));
    right_radio->setText(tr("Right"));
}

void WindowWidget::initSettingData()
{
    if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui") {

        emit this->requesetWindowButtonAlign();
//        QString current_value = sessionproxy->get_window_button_align_qt();
//        if(current_value == "left") {
//            left_radio->setChecked(true);
//            right_radio->setChecked(false);
//        }
//        else if(current_value == "right") {
//            right_radio->setChecked(true);
//            left_radio->setChecked(false);
//        }
    }
    else {
        emit this->requesetMenusHaveIcons();
//        icon_switcher->switchedOn = sessionproxy->get_menus_have_icons_qt();
    }
    emit this->requesetWindowTitileTags();

//    QString current_wheel_type = sessionproxy->get_current_titlebar_wheel_qt();
//    //FT arm has no org.compiz.gwd.mouse-wheel-action, so is empty
//    if (current_wheel_type.isEmpty())
//    {
//        wheel_label->hide();
//        wheel_combo->hide();
//    }

//    m_wheellist = sessionproxy->get_titlebar_wheel_qt();
//    wheel_combo->clear();
//    wheel_combo->clearEditText();
//    wheel_combo->addItems(m_wheellist);
//    QList<QString>::Iterator it1 = m_wheellist.begin(), itend1 = m_wheellist.end();
//    int initIndex1 = 0;
//    for(;it1 != itend1; it1++,initIndex1++)
//    {
//        if(*it1 == current_wheel_type)
//            break;
//    }
//    wheel_combo->setCurrentIndex(initIndex1);

//    QString current_double_type = sessionproxy->get_current_titlebar_double_qt();
//    m_titlebarOptions  = sessionproxy->get_titlebar_options_qt();
//    double_click_combo->clear();
//    double_click_combo->clearEditText();
//    double_click_combo->addItems(m_titlebarOptions);
//    QList<QString>::Iterator it2 = m_titlebarOptions.begin(), itend2 = m_titlebarOptions.end();
//    int initIndex2 = 0;
//    for(;it2 != itend2; it2++,initIndex2++)
//    {
//        if(*it2 == current_double_type)
//            break;
//    }
//    double_click_combo->setCurrentIndex(initIndex2);

//    QString current_middle_type = sessionproxy->get_current_titlebar_middle_qt();
////    QStringList middlelist  = sessionproxy->get_titlebar_middle_qt();
//    middle_click_combo->clear();
//    middle_click_combo->clearEditText();
//    middle_click_combo->addItems(m_titlebarOptions);
//    QList<QString>::Iterator it3 = m_titlebarOptions.begin(), itend3 = m_titlebarOptions.end();
//    int initIndex3 = 0;
//    for(;it3 != itend3; it3++,initIndex3++)
//    {
//        if(*it3 == current_middle_type)
//            break;
//    }
//    middle_click_combo->setCurrentIndex(initIndex3);

//    QString current_right_type = sessionproxy->get_current_titlebar_right_qt();
////    QStringList rightlist  = sessionproxy->get_titlebar_right_qt();
//    right_click_combo->clear();
//    right_click_combo->clearEditText();
//    right_click_combo->addItems(m_titlebarOptions);
//    QList<QString>::Iterator it4 = m_titlebarOptions.begin(), itend4 = m_titlebarOptions.end();
//    int initIndex4 = 0;
//    for(;it4 != itend4; it4++,initIndex4++)
//    {
//        if(*it4 == current_right_type)
//            break;
//    }
//    right_click_combo->setCurrentIndex(initIndex4);

    this->initConnect();
}

void WindowWidget::onSendWindowButtonAlign(const QString &current_value)
{
    if(current_value == "left") {
        left_radio->setChecked(true);
        right_radio->setChecked(false);
    }
    else if(current_value == "right") {
        right_radio->setChecked(true);
        left_radio->setChecked(false);
    }
}

void WindowWidget::onSendMenusHaveIcons(bool menuHaveIcons)
{
    icon_switcher->switchedOn = menuHaveIcons;
}

void WindowWidget::onSendWindowTitileTags(const QString &current_wheel_type, const QStringList &wheellist, const QStringList &titlebarOptions, const QString &current_double_type, const QString &current_middle_type, const QString &current_right_type)
{
    //FT arm has no org.compiz.gwd.mouse-wheel-action, so is empty
    if (current_wheel_type.isEmpty())
    {
        wheel_label->hide();
        wheel_combo->hide();
    }

    m_wheellist.clear();
    m_wheellist = wheellist;
    wheel_combo->clear();
    wheel_combo->clearEditText();
    wheel_combo->addItems(m_wheellist);
    QList<QString>::Iterator it1 = m_wheellist.begin(), itend1 = m_wheellist.end();
    int initIndex1 = 0;
    for(;it1 != itend1; it1++,initIndex1++)
    {
        if(*it1 == current_wheel_type)
            break;
    }
    wheel_combo->setCurrentIndex(initIndex1);

    m_titlebarOptions.clear();
    m_titlebarOptions = titlebarOptions;
    double_click_combo->clear();
    double_click_combo->clearEditText();
    double_click_combo->addItems(m_titlebarOptions);
    QList<QString>::Iterator it2 = m_titlebarOptions.begin(), itend2 = m_titlebarOptions.end();
    int initIndex2 = 0;
    for(;it2 != itend2; it2++,initIndex2++)
    {
        if(*it2 == current_double_type)
            break;
    }
    double_click_combo->setCurrentIndex(initIndex2);

    middle_click_combo->clear();
    middle_click_combo->clearEditText();
    middle_click_combo->addItems(m_titlebarOptions);
    QList<QString>::Iterator it3 = m_titlebarOptions.begin(), itend3 = m_titlebarOptions.end();
    int initIndex3 = 0;
    for(;it3 != itend3; it3++,initIndex3++)
    {
        if(*it3 == current_middle_type)
            break;
    }
    middle_click_combo->setCurrentIndex(initIndex3);

    right_click_combo->clear();
    right_click_combo->clearEditText();
    right_click_combo->addItems(m_titlebarOptions);
    QList<QString>::Iterator it4 = m_titlebarOptions.begin(), itend4 = m_titlebarOptions.end();
    int initIndex4 = 0;
    for(;it4 != itend4; it4++,initIndex4++)
    {
        if(*it4 == current_right_type)
            break;
    }
    right_click_combo->setCurrentIndex(initIndex4);
}


void WindowWidget::initConnect() {
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
    connect(left_radio, SIGNAL(clicked()), this, SLOT(setRadioButtonRowStatus()));
    connect(right_radio, SIGNAL(clicked()), this, SLOT(setRadioButtonRowStatus()));
    connect(icon_switcher, SIGNAL(clicked()), this, SLOT(setMenuIcon()));
    connect(wheel_combo, SIGNAL(currentIndexChanged(QString)), this, SLOT(setMouseWheel(QString)));
    connect(double_click_combo, SIGNAL(currentIndexChanged(QString)), this, SLOT(setMouseDoubleClick(QString)));
    connect(middle_click_combo, SIGNAL(currentIndexChanged(QString)), this, SLOT(setMouseMiddleClick(QString)));
    connect(right_click_combo, SIGNAL(currentIndexChanged(QString)), this, SLOT(setMouseRightClick(QString)));

//    connect(sessionproxy, SIGNAL(string_value_notify(QString, QString)), this, SLOT(windowwidget_notify_string(QString, QString)));
//    connect(sessionproxy, SIGNAL(bool_value_notify(QString, bool)), this, SLOT(windowwidget_notify_bool(QString, bool)));
}

void WindowWidget::windowwidget_notify_string(QString key, QString value)
{
    if (key == "button-layout") {
        if (value == "close,maximize,minimize:menu" || value == "close,minimize,maximize:menu" || value == "close,minimize,maximize:" || value == "close,maximize,minimize:")
        {
            left_radio->setChecked(true);
            right_radio->setChecked(false);
        }
        else if (value == "menu:minimize,maximize,close" || value == "menu:maximize,minimize,close" || value == ":minimize,maximize,close" || value == ":maximize,minimize,close")
        {
            right_radio->setChecked(true);
            left_radio->setChecked(false);
        }
    }
    else if (key == "mouse-wheel-action") {
        QList<QString>::Iterator it = m_wheellist.begin(), itend = m_wheellist.end();
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
            wheel_combo->setCurrentIndex(index);
        }
        else
            wheel_combo->setCurrentIndex(-1);
    }
    else if (key == "action-double-click-titlebar") {
        QList<QString>::Iterator it = m_titlebarOptions.begin(), itend = m_titlebarOptions.end();
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
            double_click_combo->setCurrentIndex(index);
        }
        else
            double_click_combo->setCurrentIndex(-1);
    }
    else if (key == "action-middle-click-titlebar") {
        QList<QString>::Iterator it = m_titlebarOptions.begin(), itend = m_titlebarOptions.end();
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
            middle_click_combo->setCurrentIndex(index);
        }
        else
            middle_click_combo->setCurrentIndex(-1);
    }
    else if (key == "action-right-click-titlebar") {
        QList<QString>::Iterator it = m_titlebarOptions.begin(), itend = m_titlebarOptions.end();
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
            right_click_combo->setCurrentIndex(index);
        }
        else
            right_click_combo->setCurrentIndex(-1);
    }
}

void WindowWidget::windowwidget_notify_bool(QString key, bool value)
{
    if (key == "menus-have-icons") {
        icon_switcher->switchedOn = value;
    }
}

void WindowWidget::setMenuIcon()
{
    emit this->resetMenusHaveIcon(icon_switcher->switchedOn);
//    sessionproxy->set_menus_have_icons_qt(icon_switcher->switchedOn);

}

void WindowWidget::setMouseWheel(QString selected)
{
    emit this->resetTitlebarWheel(selected);
//    sessionproxy->set_titlebar_wheel_qt(selected);
}

void WindowWidget::setMouseDoubleClick(QString selected)
{
    emit this->resetTitlebarDoubleClick(selected);
//    sessionproxy->set_titlebar_double_qt(selected);
}

void WindowWidget::setMouseMiddleClick(QString selected)
{
    emit this->resetMouseMiddleClick(selected);
//    sessionproxy->set_titlebar_middle_qt(selected);
}

void WindowWidget::setMouseRightClick(QString selected)
{
    emit this->resetMouseRightClick(selected);
//    sessionproxy->set_titlebar_right_qt(selected);
}

void WindowWidget::setRadioButtonRowStatus()
{
    QObject *obj = sender(); //返回发出信号的对象，用QObject类型接收
    QRadioButton* pbtn = qobject_cast<QRadioButton*>(obj);
    QString obj_name = pbtn->objectName();
    if(obj_name == "leftradio")
    {
        emit this->resetWindowButtonLeftOrRightAlign(true);
//        sessionproxy->set_window_button_align_left_qt();
    }
    else if(obj_name == "rightradio")
    {
        emit this->resetWindowButtonLeftOrRightAlign(false);
//        sessionproxy->set_window_button_align_right_qt();
    }
}
