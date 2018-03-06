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

#ifndef LOGINWIDGET_H
#define LOGINWIDGET_H

#include <QWidget>

#include "../component/kylinbutton.h"
#include "../component/systembutton.h"

class SessionDispatcher;
class QLabel;

class LoginWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LoginWidget(QWidget *parent = 0);
    ~LoginWidget();
    void setSessionDbusProxy(SessionDispatcher* dispatcher) { sessionProxy = dispatcher;}
    void setLauguage();
    void initConnect();

public slots:
    void onLoginButtonClicked();
    void onLogoutButtonClicked();
    void showLoginInfo(QString name, QString email);
    void showLoginAndLogoutStatus(bool status);

private:
    QPoint press_point;//鼠标按下去的点
    bool is_move;
    QPushButton *login_button;
    QPushButton *logo_label;
    QLabel *user_label;
    QPushButton *logout_btn;
    SessionDispatcher *sessionProxy;
};

#endif // LOGINWIDGET_H
