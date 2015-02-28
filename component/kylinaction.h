#ifndef __KYLINACTION_H__
#define __KYLINACTION_H__

#include <QAction>
//#include "qimpanelagent.h"

//typedef enum SkinClass
//{
//    FCITX,
//    SOGOU
//} SkinClass;

class KylinAction : public QAction
{
    Q_OBJECT

public:
//    MyAction(const QString &text, QObject *parent);
    KylinAction(const QIcon &icon, const QString &text, QObject *parent);
    virtual ~KylinAction();

public:
//    void setProp(const KimpanelProperty &prop);
//    const KimpanelProperty& getProp();
    void setSkinPath(const QString skinPath);
    const QString getSkinPath();
//    void setSkinClass(const SkinClass skinClass);
//    SkinClass getSkinClass();
    void setRealName(const QString realName);
    const QString getRealName();
private:
//    KimpanelProperty mProp;
    QString mSkinPath;
//    SkinClass mSkinClass;
	QString mRealName;
public slots:
    void hover();
};

#endif // __KYLINACTION_H__
