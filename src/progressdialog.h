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
#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>
#include <QtGui>
namespace Ui {
class ProgressDialog;
}

class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(QWidget *parent = 0);
    virtual QSize sizeHint()const;
    ~ProgressDialog();
public slots:
    //将得到的软件操作的进度和状态动态的显示在进度条上面
    void setDynamicSoftwareProgress(QString type, QString msg);
    void reset_status();
private:
    Ui::ProgressDialog *ui;
    QPoint dragPos;
    int ratio_sus;
    QSize initSize;

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void paintEvent(QPaintEvent *);
    void resizeEvent(QResizeEvent *);

signals:
    //将进度条上的软件更新状态实时通知给SudoDispather
    void softwareSourceUpdateProgressToSudoDispather(QString cur_status);
};

#endif // PROGRESSDIALOG_H
