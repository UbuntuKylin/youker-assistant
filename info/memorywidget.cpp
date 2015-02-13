#include "memorywidget.h"
#include "../dbusproxy/youkersystemdbus.h"
#include <QDebug>

MemoryWidget::MemoryWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    memoryNum = this->initData();

    if(memoryNum == 1)
    {
        ComputerPage *page = new ComputerPage(scroll_widget->zone, "Memory Info");
        memory_info_map.remove("Memnum");
        page->setMap(memory_info_map, "INTEL");
        page->initUI();
        scroll_widget->addScrollWidget(page);
    }
    else if(memoryNum > 1)
    {
        for(int i=0;i<memoryNum;i++)
        {
            ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("Memory Info %1").arg(i+1));
            tmp_info_map.clear();
            QMap<QString, QVariant>::iterator itbegin = memory_info_map.begin();
            QMap<QString, QVariant>::iterator  itend = memory_info_map.end();
            for (;itbegin != itend; ++itbegin)
            {
                if(itbegin.key() != "Memnum")
                    tmp_info_map.insert(itbegin.key(), itbegin.value().toString().split("<1_1>").at(i));
            }
            page->setMap(tmp_info_map, tmp_info_map.value("MemVendor").toString().toUpper());
            page->initUI();
            scroll_widget->addScrollWidget(page);
        }
    }
}

int MemoryWidget::initData()
{
    memory_info_map.clear();
    memory_info_map = systemproxy->get_memory_info_qt();
    QMap<QString, QVariant>::iterator iter = memory_info_map.find("Memnum");
    if (iter == memory_info_map.end())
    {
        return 0;
    }
    else{
        return iter.value().toInt();
    }
}
