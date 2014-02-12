/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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
#ifndef SUSPENSIONFRAME_H
#define SUSPENSIONFRAME_H

#include <QWidget>
#include <QtGui>
namespace Ui {
class SuspensionFrame;
}

class SuspensionFrame : public QWidget
{
    Q_OBJECT
    
public:
    explicit SuspensionFrame(QWidget *parent = 0);
    virtual QSize sizeHint()const;
    QString get_locale_version();
    ~SuspensionFrame();
    
private:
    Ui::SuspensionFrame *ui;
    QPoint dragPos;
    QSize initSize;
    QImage wheel;
    QPixmap blister;
    int ratio_sus;
    QString locale_Lan;
signals:
    void accelerate_memory();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *event);
private slots:
    void on_descBtn_clicked();
    void get_sysc_data(QString upspeed, QString downspeed, QString ratio, int used_memory, QString free_memory, QString cpu_ratio);
    void on_fastBtn_clicked();
};

#endif // SUSPENSIONFRAME_H
