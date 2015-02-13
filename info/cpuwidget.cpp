#include "cpuwidget.h"

CpuWidget::CpuWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403 - 3);
    this->initData();
    page = new ComputerPage(scroll_widget->zone, "CPU Info");
    page->setMap(cpu_info_map, cpu_info_map.value("CpuVendor").toString().toUpper());
    page->initUI();
    scroll_widget->addScrollWidget(page);
}

void CpuWidget::initData()
{
    cpu_info_map = systemproxy->get_cpu_info_qt();
}
