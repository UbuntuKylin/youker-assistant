/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
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

#ifndef RESTARTDIALOG_H
#define RESTARTDIALOG_H

#include <QDialog>
//#include <qfiledialog.h>
namespace Ui {
class RestartDialog;
}

class RestartDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit RestartDialog(QWidget *parent = 0);
    ~RestartDialog();
    
private:
    Ui::RestartDialog *ui;
    QPoint dragPos;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
public slots:
    void exit_youker();
};

#endif // RESTARTDIALOG_H
