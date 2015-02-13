#include <QMouseEvent>
#include "kylinlistwidget.h"
#include "kylinlistwidgetitem.h"
#include "mainwindow.h"
#include <QDebug>

KylinListWidget::KylinListWidget(QWidget *parent)
    :QListWidget(parent)
{
    connect(this, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(onItemClicked(QListWidgetItem*)));
}

KylinListWidget::~KylinListWidget()
{
}

void KylinListWidget::onItemClicked(QListWidgetItem *item)
{
    KylinListWidgetItem* listitem = static_cast<KylinListWidgetItem*>(item);
    mainwindow->changeSkin(listitem->getSkinName());
}

void  KylinListWidget::enterEvent (QEvent *event)
{

}
void  KylinListWidget::leaveEvent (QEvent *event)
{

}

void KylinListWidget::moveEvent (QMoveEvent *event)
{

}

void KylinListWidget::mouseMoveEvent(QMouseEvent *event)
{
    QPoint point = event->pos();
    KylinListWidgetItem *item = (KylinListWidgetItem*)itemAt(point);
    if (item)
    {
        item->painter();
    }
    event->ignore();
}
