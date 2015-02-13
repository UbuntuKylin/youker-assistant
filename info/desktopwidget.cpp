#include "desktopwidget.h"

DesktopWidget::DesktopWidget(QWidget *parent, SessionDispatcher *proxy) :
    QWidget(parent),
    sessionProxy(proxy)
{
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    this->initData();
    page = new ComputerPage(scroll_widget->zone, "Desktop Info");
    page->setMap(desktop_info_map, "UBUNTUKYLIN");
    page->initUI();
    scroll_widget->addScrollWidget(page);
}

void DesktopWidget::initData()
{
    desktop_info_map = sessionProxy->get_system_message_qt();
}
