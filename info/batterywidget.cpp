#include "batterywidget.h"
//#include <QDebug>

BatteryWidget::BatteryWidget(QWidget *parent, SessionDispatcher *proxy) :
    QWidget(parent),
    sessionproxy(proxy)
{
    setFixedSize(750, 403);

    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    this->initData();
    page = new ComputerPage(scroll_widget->zone, tr("Battery Info"));
    page->setMap(battery_info_map, battery_info_map.value("POWER_SUPPLY_MANUFACTURER").toString().toUpper());
    page->initUI();
    scroll_widget->addScrollWidget(page);
}

void BatteryWidget::initData()
{
//    battery_info_map = sessionproxy->read_battery_info_qt();
//    qDebug() << battery_info_map;
    QMap<QString, QVariant> tmpMap = sessionproxy->read_battery_info_qt();
    QMap<QString,QVariant>::iterator it; //遍历map
    for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
        if(it.key() != "POWER_SUPPLY_CAPACITY" && it.key() != "POWER_SUPPLY_CYCLE_COUNT" && it.key() != "POWER_SUPPLY_POWER_NOW" && it.key() != "POWER_SUPPLY_PRESENT" && it.key() != "POWER_SUPPLY_STATUS" && it.key() != "POWER_SUPPLY_VOLTAGE_MIN_DESIGN" )
        {
            battery_info_map.insert(it.key(), it.value());
        }
    }
}

