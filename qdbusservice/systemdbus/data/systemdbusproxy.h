#pragma once

#include "../customdata.h"

#include <QObject>
#include <QScopedPointer>

class SystemDbusHandler;

class SystemDbusProxy : public QObject
{
    Q_OBJECT
public:
    explicit SystemDbusProxy(QObject *parent = 0);
    ~SystemDbusProxy();

    QString demoInfo();
    bool userIsActive(const QString &user, bool active);
    CustomData getCustomData();
    void sendCustomData(const CustomData &message);
    void exitService();

signals:
    void reportAlert(int ret, const QString &description);

private:
    SystemDbusHandler *m_handler = nullptr;
};
