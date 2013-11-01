#include "processmanager.h"

ProcessManager::ProcessManager(QObject *parent) :
    QObject(parent)
{
}

QList<YProcess> ProcessManager::getProcess(){
    QProcess *p = new QProcess();
    p->start("ps -u shine -o user,pid,%cpu,%mem,start,command");
    p->waitForFinished();

    QList<YProcess> *yplist = new QList<YProcess>();
    p->readLine();  //throw the first line
    while(p->canReadLine()){
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
    }
    return *yplist;
}

void ProcessManager::killProcess(QString pid){
    QProcess *p = new QProcess();
    p->start("kill -9 " + pid);
    p->waitForFinished();
}
