/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    kobe24_lixiang@126.com
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
#ifndef MODALDIALOG_H
#define MODALDIALOG_H

#include <QDialog>
#include "quibo.h"
namespace Ui {
class ModalDialog;
}

class ModalDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ModalDialog(QWidget *parent = 0);
    ~ModalDialog();
    void monitor_check();
    
private:
    Ui::ModalDialog *ui;
    QPoint dragPos;
    QUIBO *qtui;

private slots:
    void on_closeButton_clicked();
    void on_okButton_clicked();
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // MODALDIALOG_H
