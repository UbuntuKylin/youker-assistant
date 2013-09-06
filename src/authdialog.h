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

#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>

#include <qfiledialog.h>
namespace Ui {
class AuthDialog;
}

class AuthDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AuthDialog(QString msg = "", QWidget *parent = 0);
    ~AuthDialog();
    bool trans_password(QString flagstr, QString pwd);

private slots:
    void on_closeButton_clicked();
    void on_okButton_clicked();

private:
    Ui::AuthDialog *ui;

//    void setView();
    QPoint dragPos;
    QString passwd;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
};

#endif // AUTHDIALOG_H
