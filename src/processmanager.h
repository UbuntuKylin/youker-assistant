#ifndef PROCESSMANAGER_H
#define PROCESSMANAGER_H

#include <QObject>
#include <QDebug>
#include <QProcess>
#include "yprocess.h"

class QSettings;
class ProcessManager : public QObject
{
    Q_OBJECT
public:
    explicit ProcessManager(QObject *parent = 0);
    ~ProcessManager();
    
    Q_INVOKABLE QList<YProcess> getProcess();
    Q_INVOKABLE void killProcess(QString pid);
signals:
    
public slots:
private:
    QSettings * mSettings;
    
};

#endif // PROCESSMANAGER_H
