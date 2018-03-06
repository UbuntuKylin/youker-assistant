#include "signalmanager.h"

SignalManager * SignalManager::m_signalManager = NULL;

SignalManager *SignalManager::Instance()
{
    if (m_signalManager == NULL) {
        m_signalManager = new SignalManager;
    }

    return m_signalManager;
}

SignalManager::SignalManager(QObject *parent) : QObject(parent)
{

}
