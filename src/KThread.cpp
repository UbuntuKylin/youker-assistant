#include <QDebug>
#include "KThread.h"
KThread::KThread(QDBusInterface *systemiface, Transmit *transmit):QThread()
{
    iface = systemiface;
    trans = transmit;

}
KThread::~KThread()
{
    stop();
}
void KThread::run()
{
    QDBusReply<QStringList> reply = iface->call("get_network_flow");
    trans->start_to_tansmit("kobe");
//    tansmit = new Transmit();
//    tansmit->start_to_tansmit("kobe");
//    emit this->sendToQml(reply.value());
//    iface->list = reply.value();
}
void KThread::stop()
{
    wait();
}
