#include "boardwidget.h"
BoardWidget::BoardWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    this->initData();
    page = new ComputerPage(scroll_widget->zone, "Board Info");
    page->setMap(board_info_map, board_info_map.value("BoaVendor").toString().toUpper());
    page->initUI();
    scroll_widget->addScrollWidget(page);
}

void BoardWidget::initData()
{
    board_info_map = systemproxy->get_board_info_qt();
}
