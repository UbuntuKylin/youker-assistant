#include "systemdispatcher.h"
#include <QDebug>
#include <QVariant>
#include <QProcessEnvironment>
#include <QtDBus>
#include <QObject>
#include <QString>
SystemDispatcher::SystemDispatcher(QObject *parent) :
    QObject(parent)
{
    systemiface = new QDBusInterface("com.ubuntukylin.Ihu",
                               "/",
                               "com.ubuntukylin.Ihu",
                               QDBusConnection::systemBus());
    QObject::connect(systemiface,SIGNAL(clear_browser(QString)),this,SLOT(show_progress_clear_rubbish(QString)));
    QObject::connect(systemiface,SIGNAL(pc_msg(QString)),this,SLOT(show_signal(QString)));



//    QObject::connect(iface,SIGNAL(clear_rubbish(QString)),this,SLOT(show_progress_clear_rubbish(QString)));
    //呼叫远程的pc_message，参数为num
    //QDBusReply<int> reply = iface.call("pc_message", num);
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("pc_message");

    notify_str = "";
    if (reply.isValid()) {
        QMap<QString, QVariant> value = reply.value();
        myinfo = value;
        qDebug() << myinfo;
    }
    else {
        qDebug() << "get pc_message failed!";
    }


//    QDBusReply<QMap<QString, QVariant> > reply2 = systemiface->call("search_the_same", "/home/kobe/a/");
//    if (reply2.isValid()) {
//        qDebug() << "aaaaaaaaaaaaa";
//        qDebug() << reply2.value();
//    }
//    else {
//        qDebug() << "search_the_same failed!";
////        return "search_the_same has error";
//    }


//    QDBusReply<QStringList> reply3 = iface->call("search_the_large", "/home/kobe/a/");
//    if (reply3.isValid()) {
//        QStringList value = reply3.value();
//        qDebug() << value;
//    }
//    else {
//        qDebug() << "search_the_large failed!";
//    }
}


QString SystemDispatcher::get_value(QString key)
{
    QVariant tt = myinfo.value(key);
    return tt.toString();
}

int SystemDispatcher::get_add_value()
{
    QDBusReply<int> reply = systemiface->call("test_add", 3, 4);
    int tt = reply.value();
    return tt;
}

QString SystemDispatcher::show_progress_clear_rubbish(QString msg)
{
    qDebug() << "kobekoeb***********";
    qDebug() << msg;
//    emit myStringChanged("Kobe test for fastclear button and dbus communication");
    return msg;
}

QString SystemDispatcher::show_signal(QString msg) {
    qDebug() << "pspspspspps***********";
    qDebug() << msg;
    return msg;
}

void SystemDispatcher::send_btn_msg(QString str)
{
    QDBusReply<void> reply = systemiface->call("test_fastclear", str);
}

//QString SystemDispatcher::getMyString()
//{
//    m_string="Called from the Q_INVOKABLE function";
//    return m_string;
//}

//void SystemDispatcher::setmyString(QString aString)
//{
//    if(aString==m_string)
//    {
//        return;
//    }
//    m_string=aString;
//    emit myStringChanged();
//}

//QString SystemDispatcher::myString()
//{
//    m_string="Called from the PROPERTY";
//    return m_string;
//}


void SystemDispatcher::check_screen_break_point() {
    QDBusReply<void> reply = systemiface->call("check_screen");
}

void SystemDispatcher::custom_plymouth_bg(QString imagepath) {
    QDBusReply<void> reply = systemiface->call("custom_plymouth", imagepath);
}

//QMap<QString, QStringList> search_the_same_file(QString imagepath);

//QMap<QString, QStringList> SystemDispatcher::search_the_same_file(QString path) {
//    QDBusReply<QMap<QString, QStringList> > reply = iface->call("search_the_same", path);
////    if (reply.isValid()) {
////        QMap<QString, QStringList> value = reply.value();
//////        myinfo = value;
////        qDebug() << value;
////    }
////    else {
////        qDebug() << "get same file failed!";
////    }
//}

int SystemDispatcher::get_record_number(QString mode) {
    QDBusReply<int> reply = systemiface->call("get_the_record", mode);
    if (reply.isValid()) {
        int value = reply.value();
        qDebug() << "value start";
        qDebug() << value;
        qDebug() << "value end";
        return value;
    }
    else {
        qDebug() << "get record number failed!";
        return 0;
    }
}


void SystemDispatcher::clean_browser_record(QString mode) {
    QDBusReply<void> reply = systemiface->call("clean_the_browser", mode);
}

QMap<QString, QVariant> SystemDispatcher::search_same_files(QString path) {
    QDBusReply<QMap<QString, QVariant> > reply = systemiface->call("search_the_same", path);
    if (reply.isValid()) {
        qDebug() << "aaaaaaaaaaaaa";
        qDebug() << reply.value();
        return reply.value();
    }
    else {
        qDebug() << "search_the_same failed!";
//        return "search_the_same has error";
    }
}

QStringList SystemDispatcher::search_largest_file(QString path) {
    QDBusReply<QStringList> reply = systemiface->call("search_the_large", path);
    if (reply.isValid()) {
        QStringList value = reply.value();
        qDebug() << value;
        return reply.value();
    }
    else {
        qDebug() << "search_the_large failed!";
//        return "search_the_large has error";
    }
}

void SystemDispatcher::set_str(QString str)
{
    notify_str = str;
}
QString SystemDispatcher::get_str()
{
    return notify_str;
}


