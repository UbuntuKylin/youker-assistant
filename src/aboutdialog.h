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

#ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

#include <QDialog>
#include <QTextEdit>
#include <QLabel>
#include <QTextBrowser>
#include "../component/systembutton.h"

class QParallelAnimationGroup;

class AboutDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AboutDialog(QWidget *parent = 0, /*const QString &version="", */QString skin = ":/background/res/skin/1.png", QString arch = "", QString os = "");
    ~AboutDialog();
    void initConnect();
    void resetTitleSkin(QString skin);
    void initAnimation();
    
public slots:
    void onCloseBtnClicked();
    void openUrl(QString url);
    void onAboutBtnClicked();
    void onContributorBtnClicked();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QPoint m_dragPosition; //移动的距离
    bool m_mousePressed; //按下鼠标左键
    QWidget *baseWidget;
    SystemButton *close_btn;
    QPushButton *aboutBtn;
    QPushButton *contributorBtn;
    QLabel *indicator;
//    QLabel *aboutIndicator;
//    QLabel *contributorIndicator;
//    QTextEdit *aboutEdit;
    QTextBrowser *aboutEdit;
    QTextEdit *contributorEdit;
    QLabel *iconLabel;
    QLabel *m_appNameLabel;
    QPushButton *okBtn;
//    QLabel *versionLabel;
//    QLabel *linkLabel;
    QParallelAnimationGroup *aboutGroup;
    QParallelAnimationGroup *contributorGroup;
};

#endif // ABOUTDIALOG_H
