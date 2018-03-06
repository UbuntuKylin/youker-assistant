/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
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

#ifndef SELECTWIDGET_H
#define SELECTWIDGET_H

#include <QDialog>
#include <QVBoxLayout>
#include <QMouseEvent>

class QLabel;
class QSlider;
class QPushButton;

#include "../../component/mytitlebar.h"

class ReniceDialog : public QDialog
{
    Q_OBJECT
public:
    ReniceDialog(const QString &title = "", QWidget *parent = 0);
    ~ReniceDialog();

    void loadData(int nice);
    void moveCenter();

public slots:
    void onClose();

signals:
    void resetReniceValue(int value);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QVBoxLayout *m_mainLayout = nullptr;
    MyTitleBar *m_titleBar = nullptr;

    QHBoxLayout *h_layout = nullptr;
    QHBoxLayout *tip_layout = nullptr;
    QHBoxLayout *btn_layout = nullptr;
    QLabel *m_titleLabel = nullptr;
    QSlider *m_slider = nullptr;
    QLabel *m_valueLabel = nullptr;
    QLabel *m_valueStrLabel = nullptr;
    QLabel *m_tipTitle = nullptr;
    QLabel *m_tipLabel = nullptr;

    QPushButton *m_cancelbtn = nullptr;
    QPushButton *m_changeBtn = nullptr;

    QPoint m_dragPosition; //移动的距离
    bool m_mousePressed; //按下鼠标左键
};

#endif // SELECTWIDGET_H
