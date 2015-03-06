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

#ifndef TIPDIALOG_H
#define TIPDIALOG_H

#include <QDialog>

#include "../component/kylinlistwidget.h"
#include "../component/kylintitlebar.h"

class SessionDispatcher;
class MainWindow;

class TipDialog :public QDialog
{
  Q_OBJECT
public:
    TipDialog(QWidget *parent = 0, QString msg = "");
    ~TipDialog();
    void setParentWindow(MainWindow *From) { mainwindow = From;}
    void setLanguage();
    void initConnect();

public slots:
    void onCloseButtonClicked();
    void onOKButtonClicked();

private:
    void initTitleBar();

private:
    MainWindow *mainwindow;
    KylinTitleBar *title_bar;
    QLabel *msg_label;
    QPushButton *okBtn;
    QString message;
};

#endif // TIPDIALOG_H
