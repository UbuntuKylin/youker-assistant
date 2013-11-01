#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QObject>
#include <QDebug>
#include <QProcess>
#include "yprocess.h"

class ProcessManager : public QObject
{
    Q_OBJECT
public:
    explicit ProcessManager(QObject *parent = 0);
    
    QList<YProcess> getProcess();
    void killProcess(QString pid);
signals:
    
public slots:
    
};

#endif // PROCESSMANAGER_H
