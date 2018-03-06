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

#include "toolwidget.h"
#include "../component/kylintoolbutton.h"
#include "mainwindow.h"
//#include <QPropertyAnimation>
#include <QDebug>
//#include <QParallelAnimationGroup>

ToolWidget::ToolWidget(QWidget *parent, QString arch, QString os)
    : QWidget(parent), cur_arch(arch), osname(os)
{
    this->setFixedSize(900, 47);
//    this->setGeometry(0, 227, 900, 47);
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(233,238,241));//#e9eef1
    this->setPalette(palette);

    QStringList icon_list;
    QStringList text_list;
    if(this->cur_arch == "aarch64" || this->osname == "Kylin" || this->osname == "YHKylin")
    {
        icon_list<<":/tool/res/menu/home"<<":/tool/res/menu/cleanup"<<":/tool/res/menu/sysinfo"<<":/tool/res/menu/toolkits";
        text_list<< tr("KylinHome") << tr("Cleanup") << tr("Sysinfo") << tr("Toolkits");
    }
    else {
        icon_list<<":/tool/res/menu/home"<<":/tool/res/menu/cleanup"<<":/tool/res/menu/sysinfo"<<":/tool/res/menu/feature"<<":/tool/res/menu/toolkits";
        text_list<< tr("Home") << tr("Cleanup") << tr("Sysinfo") << tr("Feature") << tr("Toolkits");
    }

	QHBoxLayout *button_layout = new QHBoxLayout();

    QSignalMapper *signal_mapper = new QSignalMapper(this);
    for(int i=0; i<icon_list.size(); i++)
	{
        KylinToolButton *tool_button = new KylinToolButton(icon_list.at(i), text_list.at(i));
        tool_button->setFixedSize(180, 47);
		button_list.append(tool_button);
        connect(tool_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(tool_button, QString::number(i, 10));
		button_layout->addWidget(tool_button, 0, Qt::AlignBottom);
	}
    this->switchSelectedPageIndex(0);
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(switchSelectedPageIndex(QString)));

	button_layout->addStretch();
	button_layout->setSpacing(8);
    button_layout->setMargin(0);
	button_layout->setContentsMargins(15, 0, 15, 0);

    setLayout(button_layout);
    is_move = false;
//    this->initAnimation();
}

ToolWidget::~ToolWidget()
{
    for(int i=0; i<button_list.count(); i++)
    {
        KylinToolButton *btn = button_list.at(i);
        delete btn;
        btn = NULL;
    }
    button_list.clear();
}

void ToolWidget::initConnect() {
    connect(this, SIGNAL(turnCurrentPage(int)), p_mainwindow, SLOT(setCurrentPageIndex(int)));
}

void ToolWidget::switchSelectedPageIndex(QString index)
{
	bool ok;  
    int current_index = index.toInt(&ok, 10);

	for(int i=0; i<button_list.count(); i++)
	{
        KylinToolButton *tool_button = button_list.at(i);
		if(current_index == i)
		{
            tool_button->setMousePress(true);
		}
		else
		{
            tool_button->setMousePress(false);
		}
	}
    emit turnCurrentPage(current_index);
}

void ToolWidget::showBoxTool()
{
    if(this->cur_arch == "aarch64" || this->osname == "Kylin" || this->osname == "YHKylin")
    {
        this->switchSelectedPageIndex("3");
    }
    else
    {
        this->switchSelectedPageIndex("4");
    }
}


//void ToolWidget::initAnimation()
//{
//    QPoint home_origPoint(0, 227);
//    QPoint home_needPoint(0, 274);
//    QPoint clean_origPoint(180, 197);
//    QPoint clean_needPoint(180, 150);
//    QPoint info_origPoint(360, 197);
//    QPoint info_needPoint(360, 150);
//    QPoint setting_origPoint(480, 197);
//    QPoint setting_needPoint(480, 150);
//    QPoint box_origPoint(720, 197);
//    QPoint box_needPoint(720, 150);

//    QPropertyAnimation *homeToolAnimation = new QPropertyAnimation(button_list.at(0), "pos");
//    homeToolAnimation->setDuration(200);
//    homeToolAnimation->setStartValue(home_origPoint);
//    homeToolAnimation->setEndValue(home_needPoint);

//    QPropertyAnimation *cleanToolAnimation = new QPropertyAnimation(button_list.at(1), "pos");
//    cleanToolAnimation->setDuration(200);
//    cleanToolAnimation->setStartValue(clean_origPoint);
//    cleanToolAnimation->setEndValue(clean_needPoint);

//    QPropertyAnimation *infoToolAnimation = new QPropertyAnimation(button_list.at(2), "pos");
//    infoToolAnimation->setDuration(200);
//    infoToolAnimation->setStartValue(info_origPoint);
//    infoToolAnimation->setEndValue(info_needPoint);

//    QPropertyAnimation *settingToolAnimation = new QPropertyAnimation(button_list.at(3), "pos");
//    settingToolAnimation->setDuration(200);
//    settingToolAnimation->setStartValue(setting_needPoint);
//    settingToolAnimation->setEndValue(setting_origPoint);

//    QPropertyAnimation *boxToolAnimation = new QPropertyAnimation(button_list.at(4), "pos");
//    boxToolAnimation->setDuration(200);
//    boxToolAnimation->setStartValue(box_origPoint);
//    boxToolAnimation->setEndValue(box_needPoint);

//    openGroup = new QParallelAnimationGroup(this);
//    openGroup->addAnimation(setting_origPoint);
//    openGroup->addAnimation(boxToolAnimation);

//    QPropertyAnimation *settingbackToolAnimation = new QPropertyAnimation(button_list.at(3), "pos");
//    settingbackToolAnimation->setDuration(200);
//    settingbackToolAnimation->setStartValue(setting_origPoint);
//    settingbackToolAnimation->setEndValue(setting_needPoint);

//    QPropertyAnimation *boxbackToolAnimation = new QPropertyAnimation(button_list.at(4), "pos");
//    boxbackToolAnimation->setDuration(200);
//    boxbackToolAnimation->setStartValue(box_needPoint);
//    boxbackToolAnimation->setEndValue(box_origPoint);

//    closeGroup = new QParallelAnimationGroup(this);
//    closeGroup->addAnimation(settingbackToolAnimation);
//    closeGroup->addAnimation(boxbackToolAnimation);
//}
