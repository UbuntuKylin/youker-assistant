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

#ifndef UPGRADEDIALOG_H
#define UPGRADEDIALOG_H

#include <QDialog>
#include "../component/kylintitlebar.h"
#include <QTextEdit>
#include <QProgressBar>
#include "../dbusproxy/youkersystemdbus.h"
#include "../dbusproxy/youkersessiondbus.h"

//class QMovie;
//class QTimer;
class LoadingLabel;

class UpgradeDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit UpgradeDialog(QWidget *parent = 0, /*const QString &version="", */QString skin = ":/background/res/skin/1.png", QString arch = "", QString os = "");//20161228
    ~UpgradeDialog();
    void initConnect();
    void resetTitleSkin(QString skin);
    void switchPage(bool flag);
    void setSystemDbusProxy(SystemDispatcher *dispatcher) { systemProxy = dispatcher;}
    void setSessionDbusProxy(SessionDispatcher *dispatcher) { sessionProxy = dispatcher;}
    void resetVersionNumber(QStringList version_list);
    void startAccessData();
    void showErrorComponents();
    void showUpdateSourceComponents();
    
public slots:
    void onCloseBtnClicked();
    void onUpgradeBtnClicked();
    void receiveFetchSignal(QString msg_type, QStringList msg);
    void receiveAptSignal(QString msg_type, QStringList msg);
    void checkLastestVersion();
    void receiveCheckResultSignal(bool result);
    void onRetryBtnClicked();
//    void slotDisappearTip();
    void openUrl(QString url);

signals:
    void close_signal();
    void showBackendBtnSignal(bool flag);

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);

private:
    QPoint m_dragPosition; //移动的距离
    bool m_mousePressed; //按下鼠标左键
    QWidget *baseWidget;
    SystemButton *close_btn;
    QProgressBar *progressbar;
    QLabel *visit_label;
    QLabel *net_icon_label;
    QLabel *normal_icon_label;
    QLabel *ok_icon_label;
    LoadingLabel *work_loading_label;
    LoadingLabel *upgrade_loading_label;
    QLabel *m_appNameLabel;
    QLabel *doing_label;
    QLabel *error_label;
    QLabel *tip_label;
    QLabel *splitlabel;
    QLabel *version_label;
    QWidget *new_widget;
    QLabel *hook_label;
    QLabel *official_label;
    QLabel *vline;
    QLabel *new_label;
    QLabel *new_num_label;
    QPushButton *retryBtn;
    QPushButton *upgradeBtn;
    QPushButton *okBtn;
    SystemDispatcher *systemProxy;
    SessionDispatcher *sessionProxy;
    bool isBusy;
    bool upgradeOver;
//    QMovie *movie;
//    QLabel *movie_label;
//    QTimer *timer;
//    QLabel *msg_label;
    QString cur_version;
};

#endif // UPGRADEDIALOG_H
