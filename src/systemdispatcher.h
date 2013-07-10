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
#ifndef SYSTEMDISPATCHER_H
#define SYSTEMDISPATCHER_H

#include <QObject>
#include <QObject>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QApplication>
#include <QString>
#include <QDeclarativeView>

class SystemDispatcher : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QNOTIFY myStringChanged)
    Q_PROPERTY(QNOTIFY finishCleanWork)
//    Q_PROPERTY(QString myString READ myString WRITE setmyString NOTIFY myStringChanged)
public:
    explicit SystemDispatcher(QObject *parent = 0);
    Q_INVOKABLE QString get_value(QString);
    Q_INVOKABLE int get_add_value();
    Q_INVOKABLE void send_btn_msg(QString);

    Q_INVOKABLE void check_screen_break_point();
    Q_INVOKABLE void custom_plymouth_bg(QString imagepath);

//    Q_INVOKABLE QMap<QString, QStringList> search_the_same_file(QString path);
    Q_INVOKABLE int get_the_record_qt(QString mode);
    Q_INVOKABLE void clean_the_browser_qt(QString mode);
    Q_INVOKABLE QMap<QString, QVariant> search_same_files(QString path);
    Q_INVOKABLE QStringList search_largest_file(QString path);

    //custom_plymouth
    QMap<QString, QVariant> myinfo;
    QDBusInterface *systemiface;
    Q_INVOKABLE void set_str(QString str);
    Q_INVOKABLE QString get_str();
    QString notify_str;
//    Q_INVOKABLE QString get_str(QString str);
//    Q_INVOKABLE QMap <int, QString> data;
//    Q_INVOKABLE QString getMyString();

signals:
    void myStringChanged(QString str);//绑定到QML的Handler：onMyStringChanged
    void finishCleanWork(QString msg);//绑定到QML的Handler：onFinishCleanWork

public slots:
    void handler_clear_rubbish(QString msg);
    QString show_signal(QString msg);
//    void setmyString(QString aString);
//    QString myString();
private:
    
};

#endif // SYSTEMDISPATCHER_H
