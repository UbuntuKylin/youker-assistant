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

#include "agentlistitem.h"
#include <QHBoxLayout>
#include <QMouseEvent>

AgentListItem::AgentListItem(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    m_mousePressed = false;
    label = new QLabel();
    delede_button = new QPushButton();
    delede_button->setFocusPolicy(Qt::NoFocus);
    delede_button->setObjectName("transparentButton");

    QPixmap pixmap("://res/delete.png");
    delede_button->setIcon(pixmap);
    delede_button->setIconSize(pixmap.size());
    connect(delede_button, SIGNAL(clicked()), this, SLOT(onDeleteButtonClicked()));

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(label);
    layout->addStretch();
    layout->addWidget(delede_button);
//    layout->setContentsMargins(5, 5, 5, 5);
    layout->setSpacing(5);
    layout->setMargin(0);
    setLayout(layout);
}

AgentListItem::~AgentListItem()
{
    if(label != NULL)
    {
        delete label;
        label = NULL;
    }
    if(delede_button != NULL)
    {
        delete delede_button;
        delede_button = NULL;
    }
}

void AgentListItem::setCurrentItemName(QString name)
{
    label->setText(name);
}

QString AgentListItem::getCurrentItemName()
{
    QString name = label->text();
    return name;
}

void AgentListItem::onDeleteButtonClicked()
{
    QString name = label->text();
    emit removeItem(name);
}

void AgentListItem::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_mousePressed = true;
    }
}

void AgentListItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(m_mousePressed)
    {
        emit showItemName(label->text());
        m_mousePressed = false;
    }
}
