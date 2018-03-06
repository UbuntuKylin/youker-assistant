#ifndef _MYACTIONGROUP_H_
#define _MYACTIONGROUP_H_

#include <QActionGroup>
#include <QWidget>
#include "myaction.h"

class MyActionGroup : public QActionGroup
{
    Q_OBJECT

public:
    MyActionGroup ( QObject * parent );
    void setChecked(int ID);

    int checked();
    void clear(bool remove);
    void setActionsEnabled(bool);
    void addTo(QWidget *);
    void removeFrom(QWidget *);
    void uncheckAll();

signals:
    void activated(int);

protected slots:
    void itemTriggered(QAction *);
};

#endif
