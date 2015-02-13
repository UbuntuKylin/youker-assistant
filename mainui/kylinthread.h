#ifndef KYLINTHREAD_H
#define KYLINTHREAD_H

#include <QThread>
class CleanerWidget;

class KylinThread : public QThread
{
    Q_OBJECT
public:
    KylinThread();
    ~KylinThread();
    virtual void run();
    void setCleanerWidget(CleanerWidget* widget) { parent_widget = widget; }

private:
    CleanerWidget *parent_widget;
};

#endif // KYLINTHREAD_H
