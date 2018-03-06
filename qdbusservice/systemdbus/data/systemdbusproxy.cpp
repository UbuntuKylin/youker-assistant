#include "systemdbusproxy.h"
#include "systemdbushandler.h"

#include <QDebug>
#include <QThread>

SystemDbusProxy::SystemDbusProxy(QObject *parent) :
    QObject(parent)
{
    m_handler = new SystemDbusHandler;

    QThread *handlerwork = new QThread;
    m_handler->moveToThread(handlerwork);
    handlerwork->start();

    connect(m_handler, &SystemDbusHandler::reportAlert, this, &SystemDbusProxy::reportAlert);
}

SystemDbusProxy::~SystemDbusProxy()
{
    this->exitService();
    m_handler->deleteLater();
}

QString SystemDbusProxy::demoInfo()
{
    return m_handler->demoInfo();
}

bool SystemDbusProxy::userIsActive(const QString &user, bool active)
{
    return m_handler->userIsActive(user, active);
}

CustomData SystemDbusProxy::getCustomData()
{
    return m_handler->getCustomData();
}

void SystemDbusProxy::sendCustomData(const CustomData &message)
{
    m_handler->sendCustomData(message);
}

void SystemDbusProxy::exitService()
{
    m_handler->exitService();
}
