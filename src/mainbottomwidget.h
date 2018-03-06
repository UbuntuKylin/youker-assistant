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

#ifndef MAINBOTTOMWIDGET_H
#define MAINBOTTOMWIDGET_H

#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class ToolButton;

class MainBottomWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MainBottomWidget(QWidget *parent = 0, QString arch = "", QString os = ""/*, const QString &version = ""*/);
    ~MainBottomWidget();
    void setLanguage();
    void initBoxTool();
    void initConnect();
    void initUI();

public slots:
    void switchPageIndex(QString index);
    void displayBackedBtn(bool flag);
    void onCheckBtnClicked();
    void hideBackedBtn();

signals:
    void sendSubIndex(int index);
    void sendSignal();
    void sendOpenUpgrade();

private:
    QLabel *version_logo;
    QLabel *version_title;
    QLabel *version_tip;
    QPushButton *check_btn;
//    QLabel *version_label;
    QLabel *box_logo;
    QPushButton *box_title;
    QLabel *box_tip;
    QString current_version;
    QString osname;
    QString osarch;
//    QList<ToolButton *> item_list;
};

#endif // MAINBOTTOMWIDGET_H
