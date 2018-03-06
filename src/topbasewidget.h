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

#ifndef TOPBASEWIDGET_H
#define TOPBASEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include "../component/kylinbutton.h"
#include "../component/systembutton.h"

class TopBaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TopBaseWidget(QWidget *parent = 0);
    ~TopBaseWidget();

    void setTipMessage(const QString &message);
    void setImage(const QString &pic);

    void initTitlebarLeftContent();
    void initTitlebarRightContent();
    void initContentLeftContent();
    void initActionRightContent();
    void initWidgets();


//    QString getModuleName() const;
//    void setModuleName(const QString &name);
    QString getModuleName();
//    void setModuleName(QString name);

//    SettingModuleID getModuleNameID() const;
//    void setModuleNameID(const SettingModuleID &id);

public slots:
    void displayActionSubPage(QString moduleName);

signals:
    void notifyContentPageToMain();
    void showMenu();
    void showSkinCenter();
    void showMin();
    void closeApp();

private:
    QLabel *img_label = nullptr;
    QLabel *suggest_label = nullptr;
    QPushButton *back_button = nullptr;

    QString desktop;
//    QString m_moduleName;
//    SettingModuleID m_id;
    QString m_titileMessage;

    QVBoxLayout *m_layout = nullptr;
    QHBoxLayout *m_topLayout = nullptr;
    QHBoxLayout *m_titleRightLayout = nullptr;
    QHBoxLayout *m_bottomLayout = nullptr;
    QHBoxLayout *m_titleLeftLayout = nullptr;
    QHBoxLayout *m_toolLeftLayout = nullptr;
    QHBoxLayout *m_toolRightLayout = nullptr;
};

#endif // TOPBASEWIDGET_H
