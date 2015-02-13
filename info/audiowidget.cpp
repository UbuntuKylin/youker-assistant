#include "audiowidget.h"
#include <QPalette>
#include <QtGui/QApplication>

AudioWidget::AudioWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    setFixedSize(750, 403/* - 10*/);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403/* - 10*/);

    mulNum = this->initData();

    if(mulNum == 1)
    {
        ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("Audio Info"));
        audio_info_map.remove("MulNum");
        page->setMap(audio_info_map, audio_info_map.value("MulVendor").toString().toUpper());
        page->initUI();
        scroll_widget->addScrollWidget(page);
    }
    else if(mulNum > 1)
    {
        for(int i=0;i<mulNum;i++)
        {
            ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("Audio Info %1").arg(i+1));
            tmp_info_map.clear();
            QMap<QString, QVariant>::iterator itbegin = audio_info_map.begin();
            QMap<QString, QVariant>::iterator  itend = audio_info_map.end();
            for (;itbegin != itend; ++itbegin)
            {
                if(itbegin.key() != "MulNum")
                    tmp_info_map.insert(itbegin.key(), itbegin.value().toString().split("<1_1>").at(i));
            }
            page->setMap(tmp_info_map, tmp_info_map.value("MulVendor").toString().toUpper());
            page->initUI();
            scroll_widget->addScrollWidget(page);
        }
    }
}

int AudioWidget::initData()
{
    audio_info_map.clear();
    audio_info_map = systemproxy->get_audiocard_info_qt();
    QMap<QString, QVariant>::iterator iter = audio_info_map.find("MulNum");
    if (iter == audio_info_map.end())
    {
        return 0;
    }
    else{
        return iter.value().toInt();
    }
}
