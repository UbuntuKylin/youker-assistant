#ifndef KTHREAD_H
#define KTHREAD_H
#include <QThread>
#include "transmit.h"
#include <QObject>
#include <QApplication>
#include <QString>

#include <QtDBus>
#include <QDBusInterface>
#include <QDBusConnection>
class KThread : public QThread
{
public:
    KThread(QDBusInterface *systemiface=0, Transmit *transmit=0);
    ~KThread();
    void stop();
    QDBusInterface *iface;
    Transmit *trans;
protected:
    void run();
signals:
//    void sendToQml(QString list);
//    void finished();
};
#endif // KTHREAD_H
