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

#include "mousewidget.h"
#include <QDebug>
#include <QLabel>
#include <QComboBox>
#include <QRadioButton>
#include "../dbusproxy/youkersessiondbus.h"
#include "../dbusproxy/youkersystemdbus.h"

MouseWidget::MouseWidget(QWidget *parent, SessionDispatcher *proxy , SystemDispatcher *sproxy, QString cur_desktop) :
    QWidget(parent),
    sessionproxy(proxy),
    systemproxy(sproxy),
    desktop(cur_desktop)
{
    dataOK = false;
    theme_label = new QLabel();
    size_label = new QLabel();
    theme_combo = new QComboBox();
    small_size = new QRadioButton();
    small_size->setFocusPolicy(Qt::NoFocus);
//    small_size->setChecked(true);
    small_size->setObjectName("smallradio");
    big_size = new QRadioButton();
    big_size->setFocusPolicy(Qt::NoFocus);
//    big_size->setChecked(false);
    big_size->setObjectName("bigradio");

    theme_label->setFixedWidth(150);
    size_label->setFixedWidth(150);

    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->setSpacing(10);
    layout1->addWidget(theme_label);
    layout1->addWidget(theme_combo);
    layout1->addStretch();
    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->setSpacing(10);
    layout2->addWidget(size_label);
    layout2->addWidget(small_size);
    layout2->addWidget(big_size);
    layout2->addStretch();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(layout1);
    layout->addLayout(layout2);
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

MouseWidget::~MouseWidget()
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

void MouseWidget::setLanguage() {
//    title_label->setText(tr("Mouse Settings"));
//    description_label->setText(tr("Replace the theme and size of the mouse pointer,  then click the 'OK' button to confirm. Also, theme change need to restart system."));
//    back_btn->setText(tr("Back"));
    theme_label->setText(tr("Mouse Pointer Theme") + ":");
    size_label->setText(tr("Cursor Pointer Size") + ":");
    small_size->setText(tr("Small Size"));
    big_size->setText(tr("Big Size"));
}

bool MouseWidget::getStatus()
{
    return this->dataOK;
}

void MouseWidget::initData()
{
    //在mate下，默认值为空
    QString current_cursor_theme = sessionproxy->get_cursor_theme_qt();
    /*QStringList */cursorlist = sessionproxy->get_cursor_themes_qt();
    theme_combo->clear();
    theme_combo->clearEditText();
    theme_combo->addItems(cursorlist);
    QList<QString>::Iterator it = cursorlist.begin(), itend = cursorlist.end();
    int initIndex = 0;
    for(;it != itend; it++,initIndex++)
    {
        if(*it == current_cursor_theme)
            break;
    }
    theme_combo->setCurrentIndex(initIndex);
    int default_value = sessionproxy->get_cursor_size_qt();
    if(default_value < 48) {
        small_size->setChecked(true);
        big_size->setChecked(false);
    }
    else {
        big_size->setChecked(true);
        small_size->setChecked(false);
    }
//    if (this->desktop == "mate")
//    {
//        if(default_value == 18 || default_value == 24) {
//            small_size->setChecked(true);
//            big_size->setChecked(false);
//        }
//        else if(default_value == 48) {
//            big_size->setChecked(true);
//            small_size->setChecked(false);
//        }
//    }
//    else
//    {
//        if(default_value == 24) {
//            small_size->setChecked(true);
//            big_size->setChecked(false);
//        }
//        else if(default_value == 48) {
//            big_size->setChecked(true);
//            small_size->setChecked(false);
//        }
//    }
    dataOK = true;
    this->initConnect();
}

void MouseWidget::initConnect() {
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
    connect(theme_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setMouseCursorTheme(QString)));
    connect(small_size, SIGNAL(clicked(/*bool*/)), this, SLOT(setRadioButtonRowStatus(/*bool*/)));
    connect(big_size, SIGNAL(clicked(/*bool*/)), this, SLOT(setRadioButtonRowStatus(/*bool*/)));

    connect(sessionproxy, SIGNAL(string_value_notify(QString, QString)), this, SLOT(mousewidget_notify_string(QString, QString)));
    connect(sessionproxy, SIGNAL(int_value_notify(QString, int)), this, SLOT(mousewidget_notify_int(QString, int)));
}

void MouseWidget::mousewidget_notify_string(QString key, QString value)
{
    if (key == "cursor-theme") {
        QList<QString>::Iterator it = cursorlist.begin(), itend = cursorlist.end();
        int index = -1;
        for(;it != itend; it++)
        {
            ++index;
            if(*it == value)
                break;
        }
        if (index > -1)
            theme_combo->setCurrentIndex(index);
    }
}

void MouseWidget::mousewidget_notify_int(QString key, int value)
{
    if (key == "cursor-size") {
        if(value < 48) {
            small_size->setChecked(true);
            big_size->setChecked(false);
        }
        else {
            big_size->setChecked(true);
            small_size->setChecked(false);
        }
    }
}

void MouseWidget::setMouseCursorTheme(QString selectTheme)
{
    sessionproxy->set_cursor_theme_qt(selectTheme);
    systemproxy->set_cursor_theme_with_root_qt(selectTheme);
}

void MouseWidget::setRadioButtonRowStatus(/*bool status*/)
{
    QObject *obj = sender(); //返回发出信号的对象，用QObject类型接收
    QRadioButton* pbtn = qobject_cast<QRadioButton*>(obj);
    QString obj_name = pbtn->objectName();
    if(obj_name == "smallradio")
    {
        if (this->desktop == "mate")
            sessionproxy->set_cursor_size_qt(18);
        else
            sessionproxy->set_cursor_size_qt(24);
    }
    else if(obj_name == "bigradio")
    {
        sessionproxy->set_cursor_size_qt(48);
    }
}
