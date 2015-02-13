#include "scrollwidget.h"
#include "../info/computerpage.h"
#include <QDebug>
#include "../component/utils.h"

ScrollWidget::ScrollWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    widget_count = 0;
    zone_height = 403;
    scroll_area = new QScrollArea();
    zone = new QWidget();

//    zone->setStyleSheet("border:1px solid black;");
//    zone->setAutoFillBackground(true);
//    QPalette palette;
////    palette.setColor(QPalette::Background, QColor(192,253,123));
//    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/background/res/bg/6.png")));
//    zone->setPalette(palette);

    //set white background color
    zone->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    zone->setPalette(palette);

    scroll_area->setGeometry(-1, -1, 750+2, 403);
    zone->setGeometry(0,0,750,403);
    zone->setWindowFlags(Qt::FramelessWindowHint);
    scroll_area->setWidget(zone);
    scroll_area->horizontalScrollBar()->hide();
//    scroll_area->setBackgroundRole(QPalette::Dark);
    scroll_area->setAlignment(Qt::AlignLeft);
    scroll_area->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    scroll_area->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
//    scroll_area->verticalScrollBar()->setStyleSheet("QScrollBar:vertical{margin:0px 0px 0px 0px;background-color:rgb(255,255,255,100);border:0px;width:6px;}"
//         "QScrollBar::sub-line:vertical{subcontrol-origin:margin;border:1px solid red;height:13px}"
//         "QScrollBar::up-arrow:vertical{subcontrol-origin:margin;background-color:blue;height:13px}"
//         "QScrollBar::sub-page:vertical{background-color:#EEEDF0;}"
//         "QScrollBar::handle:vertical{background-color:#D1D0D2;width:6px;} QScrollBar::handle:vertical:hover{background-color:#14ACF5;width:6px;}  QScrollBar::handle:vertical:pressed{background-color:#0B95D7;width:6px;}"
//         "QScrollBar::add-page:vertical{background-color:#EEEDF0;}"
//        "QScrollBar::down-arrow:vertical{background-color:yellow;}"
//         "QScrollBar::add-line:vertical{subcontrol-origin:margin;border:1px solid green;height:13px}");

   v_layout = new QVBoxLayout();
   v_layout->addWidget(scroll_area);
   v_layout->setSpacing(0);//设置间隔
   v_layout->setMargin(0);//设置总的外围边框
//   v_layout->setContentsMargins(5, 5, 5, 5);

   setLayout(v_layout);
}

void ScrollWidget::addScrollWidget(ComputerPage *widget)
{
//    if (widget_count == 0) {
//        widget->move(0,0);
////        zone_height = widget->page_height;
////        this->zone->resize(750, 403 + 30);
//        qDebug() << "scrooll->" << widget->page_height;
//        if(zone->height() + 10 > zone_height ) {
//            zone_height = widget->page_height;
//            this->zone->resize(750, zone_height + 20);
//        }
//    }
//    else {
//        int y = zone_height + PAGESPACE;
//        zone_height += widget->page_height + PAGESPACE;
//        if(zone_height > zone->height()) {
//            this->zone->resize(750, zone_height + 20);
//        }
//        widget->move(0, y);
//    }
//    widget_count ++;

    if (widget_count == 0) {
        widget->move(0,0);
//        qDebug() << "scrooll >" << widget->page_height;
//        qDebug() << zone_height;
//        qDebug() << zone->height();
        if(widget->page_height > zone->height()) {
            zone_height = widget->page_height;
            this->zone->resize(750, zone_height);
        }
        else {
            this->zone->resize(750, 403-3);
        }
    }
    else {
        int y = zone_height + PAGESPACE;
        zone_height += widget->page_height + PAGESPACE;
        if(zone_height > zone->height()) {
            this->zone->resize(750, zone_height);
        }
        widget->move(0, y);
    }
    widget_count ++;
}
