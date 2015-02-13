#include "kylinlistwidgetitem.h"
#include <QPen>
#include <QLinearGradient>
#include "mainwindow.h"
#include <QDebug>

KylinListWidgetItem::KylinListWidgetItem(const QIcon &icon, const QString &text, QListWidget *view, int type)
    :QListWidgetItem(icon,text,view,type)
{
    mainwindow = NULL;
}

KylinListWidgetItem::~KylinListWidgetItem()
{
}

void KylinListWidgetItem::setOver(bool flag)
{
    if(flag != is_over)
    {
        is_over = flag;
        listWidget()->update();
    }
}

void KylinListWidgetItem::setPress(bool flag)
{
    if(flag != is_press)
    {
        is_press = flag;
        listWidget()->update();
    }
}

void KylinListWidgetItem::painter()
{
    mainwindow->reViewThePointSkin(point_skin);
}
