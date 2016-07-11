/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "audiowidget.h"
#include "computerpage.h"

AudioWidget::AudioWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    this->setStyleSheet("QWidget{border: none;background-color: #ffffff;}");
    setFixedSize(750, 403/* - 10*/);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403/* - 10*/);
    dataOK = false;
}

bool AudioWidget::getStatus()
{
    return this->dataOK;
}

void AudioWidget::initData()
{
    audio_info_map.clear();
    audio_info_map = systemproxy->get_audiocard_info_qt();
    QMap<QString, QVariant>::iterator iter = audio_info_map.find("MulNum");
    int mulNum = 0;
    if (iter == audio_info_map.end())
    {
        mulNum = 0;
    }
    else{
        mulNum =  iter.value().toInt();
    }
    if(audio_info_map.count() == 1 && audio_info_map.contains("kylinkobe"))
    {
    }
    else {
        if(mulNum == 1)
        {
            ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("Audio Info"));
            audio_info_map.remove("MulNum");
            QMap<QString, QVariant> tmpMap;
            QMap<QString,QVariant>::iterator it;
            for ( it = audio_info_map.begin(); it != audio_info_map.end(); ++it ) {
                if (it.value().toString().length() > 0) {
                    tmpMap.insert(it.key(), it.value());
                }
            }
            page->setMap(tmpMap, audio_info_map.value("MulVendor").toString().toUpper());
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
                    if(itbegin.key() != "MulNum" && itbegin.value().toString().contains("<1_1>")) {
                        QString result = itbegin.value().toString().split("<1_1>").at(i);
                        if (result.length() > 0) {
                            tmp_info_map.insert(itbegin.key(), result);
                        }
                    }
                }
                page->setMap(tmp_info_map, tmp_info_map.value("MulVendor").toString().toUpper());
                page->initUI();
                scroll_widget->addScrollWidget(page);
            }
        }
    }
    dataOK = true;
}
