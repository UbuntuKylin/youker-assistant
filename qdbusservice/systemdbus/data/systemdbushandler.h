#pragma once

#include "systemdbusproxy.h"
#include "systeminterface.h"
#include "../customdata.h"

#include <QObject>
#include <QDebug>
#include <QDBusConnection>

class SystemDbusHandler : public QObject
{
    Q_OBJECT

public:
    explicit SystemDbusHandler(QObject *parent = 0)
        : QObject(parent)
    {
        m_sysDbus = new SystemInterface("com.kylin.assistant.qsystemdbus",
                                     "/com/kylin/assistant/qsystemdbus",
                                     QDBusConnection::systemBus(),
                                     this);
        connect(m_sysDbus, &SystemInterface::reportAlert, this, &SystemDbusHandler::reportAlert);
    }

    QString demoInfo()
    {
        return m_sysDbus->demoInfo();
    }

    bool userIsActive(const QString &user, bool active)
    {
        return m_sysDbus->userIsActive(user, active);
    }

    CustomData getCustomData()
    {
        return m_sysDbus->getCustomData();
    }

    void sendCustomData(const CustomData &message)
    {
        m_sysDbus->sendCustomData(message);
    }

    void exitService()
    {
        m_sysDbus->exitService();
    }

signals:
    void reportAlert(int ret, const QString &description);

private:
    SystemInterface *m_sysDbus = nullptr;
};
