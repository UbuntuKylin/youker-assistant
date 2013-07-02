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

#ifndef CONTROL_H
#define CONTROL_H

//#include <QObject>
//#include <QQmlParserStatus>
//#include <QQmlListProperty>
//#include <QDBusInterface>
//#include <QDBusConnection>
//#include <QtQuick/QQuickView>
//#include <QGuiApplication>
//#include <QString>

#include <QObject>
#include <QDBusInterface>
#include <QDBusConnection>
#include <QApplication>
#include <QString>
#include <QDeclarativeView>

class DispatcherQml : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QNOTIFY myStringChanged)
//    Q_PROPERTY(QString myString READ myString WRITE setmyString NOTIFY myStringChanged)
public:
    explicit DispatcherQml(QObject *parent = 0);
    Q_INVOKABLE QString get_value(QString);
    Q_INVOKABLE int get_add_value();
    Q_INVOKABLE void send_btn_msg(QString);
    Q_INVOKABLE bool set_launcher(bool);
    Q_INVOKABLE QStringList get_themes();
    Q_INVOKABLE void set_theme(QString theme);
    Q_INVOKABLE void check_screen_break_point();
    Q_INVOKABLE void custom_plymouth_bg(QString imagepath);
    //custom_plymouth
    QMap<QString, QVariant> myinfo;
    QDBusInterface *iface;
    QDBusInterface *iface1;
    Q_INVOKABLE void set_str(QString str);
    Q_INVOKABLE QString get_str();
    QString notify_str;
//    Q_INVOKABLE QString get_str(QString str);

//    Q_INVOKABLE QMap <int, QString> data;

//    Q_INVOKABLE QString getMyString();

signals:
    void myStringChanged(QString str);//绑定到QML的Handler：onMyStringChanged

public slots:
    QString show_progress_clear_rubbish(QString);
//    void setmyString(QString aString);
//    QString myString();
private:
//    QString m_string;
};

#endif // CONTROL_H


/*
a 	ARRAY 数组
b 	BOOLEAN 布尔值
d 	DOUBLE IEEE 754双精度浮点数
g 	SIGNATURE 类型签名
i 	INT32 32位有符号整数
n 	INT16 16位有符号整数
o 	OBJECT_PATH 对象路径
q 	UINT16 16位无符号整数
s 	STRING 零结尾的UTF-8字符串
t 	UINT64 64位无符号整数
u 	UINT32 32位无符号整数
v 	VARIANT 可以放任意数据类型的容器，数据中包含类型信息。例如glib中的GValue。
x 	INT64 64位有符号整数
y 	BYTE 8位无符号整数
() 	定义结构时使用。例如"(i(ii))"
{} 	定义键－值对时使用。例如"a{us}"

a表示数组，数组元素的类型由a后面的标记决定。例如：
    "as"是字符串数组。
    数组"a(i(ii))"的元素是一个结构。用括号将成员的类型括起来就表示结构了，结构可以嵌套。
    数组"a{sv}"的元素是一个键－值对。"{sv}"表示键类型是字符串，值类型是VARIANT。
*/
