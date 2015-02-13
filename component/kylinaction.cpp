#include "kylinaction.h"

//KylinAction::KylinAction(const QString &text, QObject *parent) : QAction(text, parent)
//{

//}

KylinAction::KylinAction(const QIcon &icon, const QString &text, QObject *parent)
    : QAction(icon, text, parent)
{

}

KylinAction::~KylinAction()
{

}

void KylinAction::setSkinPath(const QString skinPath)
{
    this->mSkinPath = skinPath;
}

const QString KylinAction::getSkinPath()
{
    return this->mSkinPath;
}

void KylinAction::setRealName(const QString realName)
{
    this->mRealName = realName;
}

const QString KylinAction::getRealName()
{
    return this->mRealName;
}


void KylinAction::hover()
{

}
