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


//#pragma once

#ifndef AGENTLISTITEM_H
#define AGENTLISTITEM_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>

class AgentListItem : public QWidget
{
    Q_OBJECT
public:
    explicit AgentListItem(QWidget *parent = 0);
    ~AgentListItem();
    void setCurrentItemName(QString name);
    QString getCurrentItemName();

protected:
    void mouseReleaseEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);

signals:
    void showItemName(QString name);
    void removeItem(QString name);

public slots:
    void onDeleteButtonClicked();

private:
    bool m_mousePressed;
    QLabel *label;
    QPushButton *delede_button;

};


#endif // AGENTLISTITEM_H
