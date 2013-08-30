#ifndef KTHREAD_H
#define KTHREAD_H
#include <QThread>
class KThread : public QThread
{
public:
    KThread();
    ~KThread();
    void stop();
protected:
    void run();
};
#endif // KTHREAD_H
