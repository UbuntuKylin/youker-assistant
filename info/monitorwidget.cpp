#include "monitorwidget.h"

MonitorWidget::MonitorWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);

    vgaNum = this->initData();

    if(vgaNum == 1)
    {
        ComputerPage *page = new ComputerPage(scroll_widget->zone, "Monitor Info");
        monitor_info_map.remove("Vga_num");
        page->setMap(monitor_info_map, monitor_info_map.value("Vga_vendor").toString().toUpper());
        page->initUI();
        scroll_widget->addScrollWidget(page);
    }
    else if(vgaNum > 1)
    {
        for(int i=0;i<vgaNum;i++)
        {
            ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("Monitor Info %1").arg(i+1));
            tmp_info_map.clear();
            QMap<QString, QVariant>::iterator itbegin = monitor_info_map.begin();
            QMap<QString, QVariant>::iterator  itend = monitor_info_map.end();
            for (;itbegin != itend; ++itbegin)
            {
                if(itbegin.key() != "Vga_num")
                    tmp_info_map.insert(itbegin.key(), itbegin.value().toString().split("<1_1>").at(i));
            }
            page->setMap(tmp_info_map, tmp_info_map.value("Vga_vendor").toString().toUpper());
            page->initUI();
            scroll_widget->addScrollWidget(page);
        }
    }
}

int MonitorWidget::initData()
{
    monitor_info_map.clear();
    monitor_info_map = systemproxy->get_monitor_info_qt();
    QMap<QString, QVariant>::iterator iter = monitor_info_map.find("Vga_num");
    if (iter == monitor_info_map.end())
    {
        return 0;
    }
    else{
        return iter.value().toInt();
    }
}
