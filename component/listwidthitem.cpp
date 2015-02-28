#include "listwidthitem.h"
#include <QPen>
#include <QLinearGradient>
#include "../mainui/mainwindow.h"
#include <QDebug>

ListWidthItem::ListWidthItem(const QIcon &icon, const QString &text,
                             QListWidget *view, int type)
                             :QListWidgetItem(icon,text,view,type)
{
    m_MainFrom = NULL;
}

ListWidthItem::~ListWidthItem()
{
}


void ListWidthItem::SetOver(bool bEnable)
{
    if(bEnable!=m_bOver)
    {
        //设置m_bOver标志位
        m_bOver = bEnable;
        //更新
        listWidget()->update();
    }
}

void ListWidthItem::SetPress(bool bEnable)
{
    if(bEnable!=m_bPress)
    {
        //设置m_bOver标志位
        m_bPress = bEnable;
        //更新
        listWidget()->update();
    }
}

void ListWidthItem::painter()
{
    qDebug() << "kaaaaaaaaaaaaa";
    m_MainFrom->ReViewChangeBackSkin(m_sPicture);
}
