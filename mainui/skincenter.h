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

#ifndef SKINCENTER_H
#define SKINCENTER_H

#include <QDialog>
//#include <QTimer>

#include "../component/kylinlistwidget.h"
#include "../component/kylintitlebar.h"
#include "../component/kylinlistwidgetitem.h"

class MainWindow;

class SkinCenter :public QDialog
{
  Q_OBJECT
public:
    SkinCenter(QWidget *parent = 0/*, Qt::WindowFlags f = 0*/);
    ~SkinCenter();
    void setParentWindow(MainWindow *From) { mainwindow = From;}
    void initBackgroundList();
    void setLanguage();
    void initConnect();
    void initTitleBar(const QString &path);
    void initUsingLogo(QListWidgetItem *init_item);
    void setLogo();

public slots:
    void onCloseButtonClicked();
    void changeSkinCenterBackground(QString pciture);

protected:
//    virtual void	enterEvent (QEvent  *);
//    virtual void	leaveEvent (QEvent *);
    void closeEvent(QCloseEvent *event);

private:
    MainWindow *mainwindow;
    KylinTitleBar *title_bar;
    KylinListWidget *list_widget;
    QString last_skin_path;
    QLabel *using_label;
//    QTimer *delayTimer;
//    QString titlebar_pic;
};

#endif // SKINCENTER_H
