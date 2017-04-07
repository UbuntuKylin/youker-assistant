#include <QThread>
#include <QDebug>
#include "../dbusproxy/youkersystemdbus.h"

class WorkerThread : public QThread
{
    Q_OBJECT

public:
    explicit WorkerThread(QObject *parent = 0)
        : QThread(parent)
    {
//        qDebug() << "Worker Thread : " << QThread::currentThreadId();
    }
    void initInterface(SystemDispatcher *systemiface) {
        iface = systemiface;
    }

protected:
//    virtual void run() Q_DECL_OVERRIDE {
        void run()
        {
//            qDebug() << "Worker Run Thread : " << QThread::currentThreadId();
            QMap<QString, QVariant> wire_info_map;
            wire_info_map = iface->get_networkcard_info_qt();
            emit resultReady(wire_info_map);
    }
signals:
    void resultReady(QMap<QString, QVariant> value);

private:
    SystemDispatcher *iface;
};
