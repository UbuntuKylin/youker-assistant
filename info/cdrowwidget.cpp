#include "cdrowwidget.h"

CDRowWidget::CDRowWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    this->initData();
    page = new ComputerPage(scroll_widget->zone, "CDROM Info");
    page->setMap(cdrom_info_map, cdrom_info_map.value("DvdVendor").toString().toUpper());
    page->initUI();
    scroll_widget->addScrollWidget(page);
}

void CDRowWidget::initData()
{
    cdrom_info_map = systemproxy->get_cdrom_info_qt();
}
