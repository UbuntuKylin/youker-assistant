#ifndef MYTEST_H
#define MYTEST_H

#include <QDBusInterface>
#include <QDeclarativeItem>
class mytest : public QDBusInterface
{
    Q_OBJECT
public:
    explicit mytest(const QString & service, const QString & path, const QString & interface = QString(), const QDBusConnection & connection = QDBusConnection::systemBus(), QDeclarativeItem *parent = 0);
    QDBusInterface * iface;
signals:

public slots:
//private:
//    QStringList list;
    
};

#endif // MYTEST_H
