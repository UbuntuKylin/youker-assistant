#ifndef SHREDQTHREAD_H
#define SHREDQTHREAD_H

#include "./filewipe.h"
#include <QThread>
#include <QObject>

class ShredQThread : public QObject
{
Q_OBJECT
public:
     ShredQThread(char *ch);
    ~ShredQThread();

public slots:
    void run();

signals:
    void success();
    void failed();

private:
    char *filename;
};

#endif // SHREDQTHREAD_H
