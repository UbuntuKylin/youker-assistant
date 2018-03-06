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

#ifndef CLEANERITEMS_H
#define CLEANERITEMS_H

#include <QWidget>
#include <QDialog>
#include <QCheckBox>
#include <QGroupBox>
#include "../component/kylintitlebar.h"

class MainWindow;
class QCheckBox;
class QGroupBox;

//class CleanerItems : public QWidget
class CleanerItems : public QDialog
{
    Q_OBJECT
public:
//    explicit CleanerItems(QStringList &arglist, QStringList &statuslist, int height = 0, const QString title_text = "UbuntuKylin", QWidget *parent = 0);
    explicit CleanerItems(QStringList &arglist, QStringList &statuslist, QString skin = ":/background/res/skin/1.png", int height = 0, const QString title_text = "UbuntuKylin", QDialog *parent = 0);
    ~CleanerItems();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void setLanguage();
    void initConnect();
    int getItemCount();
    QStringList getSelectedItems();
    void resetTitleSkin(QString skin);

public slots:
    void resetSubCheckbox(int status);
    void scanAllSubCheckbox();
    void onCloseButtonClicked();

private:
    void initTitleBar(QString skin);

signals:
    void notifyMainCheckBox(int status);

private:
    QList<QCheckBox *> checkbox_list;
    MainWindow *p_mainwindow;
    KylinTitleBar *title_bar;
    QString titleName;
    QPushButton *okBtn;
    QGroupBox *group_box;
};

#endif // CLEANERITEMS_H




