#include "nicwidget.h"

NicWidget::NicWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    this->initData();
    page = new ComputerPage(scroll_widget->zone, tr("NIC Info"));
    page->setMap(wire_info_map, wire_info_map.value("NetVendor").toString().toUpper());
    page->initUI();
    scroll_widget->addScrollWidget(page);
    page2 = new ComputerPage(scroll_widget->zone, tr("WireLess NIC Info"));
    page2->setMap(wireless_info_map, wireless_info_map.value("WlanVendor").toString().toUpper());
    page2->initUI();
    scroll_widget->addScrollWidget(page2);
}

void NicWidget::initData()
{
    QMap<QString, QVariant> tmpMap = systemproxy->get_networkcard_info_qt();
    QMap<QString,QVariant>::iterator it; //遍历map
    for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
        if(it.key().startsWith("Wlan"))
        {
            wireless_info_map.insert(it.key(), it.value());
        }
        else
        {
            wire_info_map.insert(it.key(), it.value());
        }
    }
}
