#include <QDebug>
#include "KThread.h"
//QStringList speedlist;
KThread::KThread(QDBusInterface *systemiface, Transmit *transmit , QString method, QStringList arglist, QString flag):QThread()
{
    iface = systemiface;
    trans = transmit;
    method_name = method;
    list = arglist;
    file_flag = flag;
}
KThread::~KThread()
{
    stop();
}
void KThread::run()
{
    if(method_name == "get_network_flow") {
        QDBusReply<QStringList> reply = iface->call(method_name);
        trans->start_to_tansmit(reply.value());
    }
    else if(method_name == "clean_by_main_one_key") {
        iface->call("clean_by_main_one_key", list);
    }

    else if(method_name == "clean_by_second_one_key") {
        iface->call("clean_by_second_one_key", list);
    }
    else if(method_name == "clean_history_records") {
        iface->call("clean_history_records");
    }
    else if(method_name == "clean_cookies_records") {
        iface->call("clean_cookies_records", list);
    }
    else if(method_name == "clean_package_cruft") {
        iface->call("clean_package_cruft", list);
    }
    else if(method_name == "clean_file_cruft") {
        iface->call("clean_file_cruft", list, file_flag);
    }
}
void KThread::stop()
{
    wait();
}
