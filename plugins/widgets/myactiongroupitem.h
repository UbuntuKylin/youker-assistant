#ifndef _MYACTIONGROUPITEM_H_
#define _MYACTIONGROUPITEM_H_

#include "myaction.h"

#include <QObject>

class MyActionGroup;

class MyActionGroupItem : public MyAction
{
public:
    MyActionGroupItem( QObject * parent, MyActionGroup *group,
                       const char * name, int data, bool autoadd = true );
};

#endif // _MYACTIONGROUPITEM_H_
