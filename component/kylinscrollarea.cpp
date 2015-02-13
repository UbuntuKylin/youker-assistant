#include "kylinscrollarea.h"
#include <QDebug>
#include "autogroup.h"


KylinScrollArea::KylinScrollArea(QWidget *parent/*, int width, int height, int spacing*/) :
    QWidget(parent)
{
    cardcount = 0;
    number_per_row = -1;
    this->setWindowFlags(Qt::FramelessWindowHint);
    itemwidth = 400;//width;
    itemheight = 50;//height;
    cardspacing = 6;//spacing;
    scroll_area = new QScrollArea(this);
    cardPanel = new QWidget();
    scroll_area->setWidget(cardPanel);
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
}

void KylinScrollArea::calculate_data()
{
   scroll_area->setGeometry(-1, -1, this->width() + 2, this->height() + 2);
   cardPanel->setGeometry(0, 0, this->width(), this->height());
   number_per_row = (this->width() + this->cardspacing) / (this->itemwidth + this->cardspacing);
}

void KylinScrollArea::add_card(AutoGroup *card)
{
    int x = int(cardcount % number_per_row) * (itemwidth + cardspacing);
    int y = int(cardcount / number_per_row) * (itemheight + cardspacing);

    int nowHeight = y + itemheight;
    if(nowHeight >= cardPanel->height())
        cardPanel->resize(cardPanel->width(), nowHeight);

    card->move(x, y);
    cardcount = cardcount + 1;
}
