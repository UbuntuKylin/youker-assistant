#include "processmanager.h"
#include "util.h"
#include <QDebug>

ProcessManager::ProcessManager(QObject *parent) :
    QObject(parent)
{
    mSettings = new QSettings(YOUKER_COMPANY_SETTING, YOUKER_SETTING_FILE_NAME_SETTING);
    mSettings->setIniCodec("UTF-8");
}

ProcessManager::~ProcessManager() {
    mSettings->sync();
    if (mSettings != NULL)
        delete mSettings;
}

QList<YProcess> ProcessManager::getProcess(){


    mSettings->beginGroup("user");
    QString currrentName = mSettings->value("currentName").toString();
    if(currrentName.isEmpty()) {
        currrentName = QString("root");
    }
    mSettings->endGroup();
    mSettings->sync();

    QString cmd = tr("ps -u %1 -o user,pid,%cpu,%mem,start,command").arg(currrentName);

    QProcess *p = new QProcess();
//    p->start("ps -u lixiang -o user,pid,%cpu,%mem,start,command");
    p->start(cmd);
    p->waitForFinished();

    QList<YProcess> *yplist = new QList<YProcess>();
    p->readLine();  //throw the first line
    qDebug() << "-----------------access process list-------------------";

    while(p->canReadLine()){
        qDebug() << "111";
        YProcess *yp = new YProcess();
        QString tmps = p->readLine();

        int spaceIndex = tmps.indexOf(" ");
        yp->user = tmps.mid(0, spaceIndex);
        tmps.remove(0, spaceIndex);
        tmps = tmps.trimmed();

        spaceIndex = tmps.indexOf(" ");
        yp->pid = tmps.mid(0, spaceIndex);
        tmps.remove(0, spaceIndex);
        tmps = tmps.trimmed();

        spaceIndex = tmps.indexOf(" ");
        yp->pcpu = tmps.mid(0, spaceIndex);
        tmps.remove(0, spaceIndex);
        tmps = tmps.trimmed();

        spaceIndex = tmps.indexOf(" ");
        yp->pmem = tmps.mid(0, spaceIndex);
        tmps.remove(0, spaceIndex);
        tmps = tmps.trimmed();

        spaceIndex = tmps.indexOf(" ");
        yp->started = tmps.mid(0, spaceIndex);
        tmps.remove(0, spaceIndex);
        tmps = tmps.trimmed();

        yp->command = tmps;

        yplist->append(*yp);
        qDebug() << yp->user;
        qDebug() << yp->pid;
        qDebug() << yp->pcpu;
        qDebug() << yp->pmem;
        qDebug() << yp->started;
        qDebug() << yp->command;
    }

    return *yplist;
}

void ProcessManager::killProcess(QString pid){
    qDebug() << "-----------------the pid is-------------------";
    qDebug() << pid;
    QProcess *p = new QProcess();
    p->start("kill -9 " + pid);
    p->waitForFinished();
}
