#ifndef YPROCESS_H
#define YPROCESS_H

#include <QObject>

class YProcess
{
public:
    YProcess();
    QString user;
    QString pid;
    QString pcpu;
    QString pmem;
    QString started;
    QString cmd;
    QString command;
    QString memo;
};

#endif // YPROCESS_H
