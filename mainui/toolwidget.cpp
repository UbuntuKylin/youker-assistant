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

ToolWidget::ToolWidget(QWidget *parent)
	: QWidget(parent)
{
    this->setFixedSize(900, 47);
//    this->setGeometry(0, 227, 900, 47);
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(233,238,241));//#e9eef1
    this->setPalette(palette);

    QStringList icon_list;
    icon_list<<":/tool/res/menu/home"<<":/tool/res/menu/cleanup"<<":/tool/res/menu/sysinfo"<<":/tool/res/menu/feature"<<":/tool/res/menu/toolkits";

    QStringList text_list;
    text_list<< tr("Home") << tr("Cleanup") << tr("Sysinfo") << tr("Feature") << tr("Toolkits");

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
    this->switchPageIndex(0);
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(switchPageIndex(QString)));

	button_layout->addStretch();
	button_layout->setSpacing(8);
    button_layout->setMargin(0);
	button_layout->setContentsMargins(15, 0, 15, 0);

    setLayout(button_layout);
    is_move = false;
}

ToolWidget::~ToolWidget()
{
}

void ToolWidget::initConnect() {
    connect(this, SIGNAL(turnCurrentPage(int)), p_mainwindow, SLOT(setCurrentPageIndex(int)));
}

void ToolWidget::switchPageIndex(QString index)
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
    this->switchPageIndex("4");
}
