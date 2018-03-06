#include "myactiongroupitem.h"
#include "myactiongroup.h"


MyActionGroupItem::MyActionGroupItem(QObject * parent, MyActionGroup *group,
                                     const char * name,
                                     int data, bool autoadd)
    : MyAction(parent, name, autoadd)
{
    setData(data);
    setCheckable(true);
    if (group) group->addAction(this);
}
