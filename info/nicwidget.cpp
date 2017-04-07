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

#include "nicwidget.h"
#include <QDebug>

NicWidget::NicWidget(QWidget *parent, SystemDispatcher *proxy) :
    QWidget(parent),
    systemproxy(proxy)
{
    this->setStyleSheet("QWidget{border: none;background-color: #ffffff;}");
    setFixedSize(750, 403);
    scroll_widget = new ScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 403);
    dataOK = false;
}

NicWidget::~NicWidget()
{
    this->clear_page_list();
    if (scroll_widget != NULL) {
        delete scroll_widget;
        scroll_widget = NULL;
    }
}

void NicWidget::clear_page_list()
{
    for(int i=0; i<page_list.count(); i++)
    {
        ComputerPage *page = page_list.at(i);
        delete page;
        page = NULL;
    }
    page_list.clear();
    if (scroll_widget)
        scroll_widget->resetWidget();
}

bool NicWidget::getStatus()
{
    return this->dataOK;
}

void NicWidget::slot_network_info(QMap<QString, QVariant> info)
{
//    qDebug() << "slot_network_info=" << info;
    this->clear_page_list();
    wire_info_map.clear();
    wire_info_map = info;
    if (wire_info_map.isEmpty() || wire_info_map.count() <= 1) {//may be wire_info_map only contains NetNum

    }
    else {
        QMap<QString, QVariant>::iterator iter = wire_info_map.find("NetNum");
        int netNum = 0;
        if (iter == wire_info_map.end()) {
            netNum = 0;
        }
        else{
            netNum = iter.value().toInt();
        }
        wire_info_map.remove("NetNum");
//        qDebug() << netNum;
        if(netNum == 0) {
        }
        else {
            if(netNum == 1) {
                if (wire_info_map.contains("NetLogicalname")) {
                    QMap<QString,QVariant>::iterator iter = wire_info_map.find("NetLogicalname");
                    QString netcard = iter.value().toString();
                    if (netcard.startsWith("veth") || netcard.startsWith("virbr")) {
                        wire_info_map["NetType"] = "VNIC";
                    }
                }
                ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("NIC Info"));
                page_list.append(page);
                QMap<QString, QVariant> tmpMap;
                QMap<QString,QVariant>::iterator it;
                for ( it = wire_info_map.begin(); it != wire_info_map.end(); ++it ) {
                    if (it.value().toString().length() > 0) {
                        tmpMap.insert(it.key(), it.value());
                    }
                }
                if (wire_info_map.value("NetVendor").toString().toUpper().contains("INTEL")) {
                    page->setMap(tmpMap, "INTEL");
                }
                else if (wire_info_map.value("NetVendor").toString().toUpper().contains("REALTEK")) {
                    page->setMap(tmpMap, "REALTEK");
                }
                else {
                    page->setMap(tmpMap, "");
                }
                page->initUI(false);
                scroll_widget->addScrollWidget(page);
                page->show();
            }
            else if(netNum > 1) {
                for(int i=0;i<netNum;i++) {
                    ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("NIC Info %1").arg(i+1));
                    page_list.append(page);
                    tmp_info_map.clear();
                    QMap<QString, QVariant>::iterator itbegin = wire_info_map.begin();
                    QMap<QString, QVariant>::iterator  itend = wire_info_map.end();
                    for (;itbegin != itend; ++itbegin) {
                        if(itbegin.value().toString().contains("<1_1>")) {
                            QStringList tmplist = itbegin.value().toString().split("<1_1>");
                            if (tmplist.length() >= i) {
                                QString result = tmplist.at(i);
                                if (result.length() > 0)
                                    tmp_info_map.insert(itbegin.key(), result);
                            }
                        }
                    }
                    if (tmp_info_map.contains("NetLogicalname")) {
                        if (tmp_info_map.value("NetLogicalname").toString().startsWith("veth") || tmp_info_map.value("NetLogicalname").toString().startsWith("virbr")) {
                            tmp_info_map["NetType"] = QVariant("VNIC");
                        }
                    }
//                    qDebug() << "tmp_info_map=" << tmp_info_map;
                    if (tmp_info_map.value("NetVendor").toString().toUpper().contains("INTEL")) {
                        page->setMap(tmp_info_map, "INTEL");
                    }
                    else if (tmp_info_map.value("NetVendor").toString().toUpper().contains("REALTEK")) {
                        page->setMap(tmp_info_map, "REALTEK");
                    }
                    else {
                        page->setMap(tmp_info_map, "");
                    }
                    page->initUI(false);
                    scroll_widget->addScrollWidget(page);
                    page->show();
                }
            }
        }
    }
//    dataOK = true;
}

void NicWidget::initData()
{
    /*wire_info_map.clear();
    wire_info_map = systemproxy->get_networkcard_info_qt();
    if (wire_info_map.isEmpty() || wire_info_map.count() <= 1) {//may be wire_info_map only contains NetNum

    }
    else {
        QMap<QString, QVariant>::iterator iter = wire_info_map.find("NetNum");
        int netNum = 0;
        if (iter == wire_info_map.end()) {
            netNum = 0;
        }
        else{
            netNum = iter.value().toInt();
        }
        wire_info_map.remove("NetNum");
        if(netNum == 0) {
        }
        else {
            if(netNum == 1) {
                if (wire_info_map.contains("NetLogicalname")) {
                    QMap<QString,QVariant>::iterator iter = wire_info_map.find("NetLogicalname");
                    QString netcard = iter.value().toString();
                    if (netcard.startsWith("veth") || netcard.startsWith("virbr")) {
                        wire_info_map["NetType"] = "VNIC";
                    }
                }
                ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("NIC Info"));
                QMap<QString, QVariant> tmpMap;
                QMap<QString,QVariant>::iterator it;
                for ( it = wire_info_map.begin(); it != wire_info_map.end(); ++it ) {
                    if (it.value().toString().length() > 0) {
                        tmpMap.insert(it.key(), it.value());
                    }
                }
                if (wire_info_map.value("NetVendor").toString().toUpper().contains("INTEL")) {
                    page->setMap(tmpMap, "INTEL");
                }
                else if (wire_info_map.value("NetVendor").toString().toUpper().contains("REALTEK")) {
                    page->setMap(tmpMap, "REALTEK");
                }
                else {
                    page->setMap(tmpMap, "");
                }
                page->initUI(false);
                scroll_widget->addScrollWidget(page);
            }
            else if(netNum > 1) {
                for(int i=0;i<netNum;i++) {
                    ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("NIC Info %1").arg(i+1));
                    tmp_info_map.clear();
                    QMap<QString, QVariant>::iterator itbegin = wire_info_map.begin();
                    QMap<QString, QVariant>::iterator  itend = wire_info_map.end();
                    for (;itbegin != itend; ++itbegin) {
                        if(itbegin.value().toString().contains("<1_1>")) {
                            QStringList tmplist = itbegin.value().toString().split("<1_1>");
                            if (tmplist.length() >= i) {
                                QString result = tmplist.at(i);
                                if (result.length() > 0)
                                    tmp_info_map.insert(itbegin.key(), result);
                            }
                        }
                    }
                    if (tmp_info_map.contains("NetLogicalname")) {
                        if (tmp_info_map.value("NetLogicalname").toString().startsWith("veth") || tmp_info_map.value("NetLogicalname").toString().startsWith("virbr")) {
                            tmp_info_map["NetType"] = QVariant("VNIC");
                        }
                    }
                    if (tmp_info_map.value("NetVendor").toString().toUpper().contains("INTEL")) {
                        page->setMap(tmp_info_map, "INTEL");
                    }
                    else if (tmp_info_map.value("NetVendor").toString().toUpper().contains("REALTEK")) {
                        page->setMap(tmp_info_map, "REALTEK");
                    }
                    else {
                        page->setMap(tmp_info_map, "");
                    }
                    page->initUI(false);
                    scroll_widget->addScrollWidget(page);
                }
            }
        }
    }
    dataOK = true;*/





    /*QMap<QString, QVariant> tmpMap = systemproxy->get_networkcard_info_qt();
    if (tmpMap.isEmpty() || tmpMap.count() <= 0) {
        page2 = NULL;
    }
    else {
        QMap<QString,QVariant>::iterator it;//遍历map
        for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
            if(it.key().startsWith("Wlan")) {
                if (it.value().toString().length() > 0) {
                    wireless_info_map.insert(it.key(), it.value());
                }
            }
            else {
                if (it.value().toString().length() > 0) {
                    wire_info_map.insert(it.key(), it.value());
                }
            }
        }
        QMap<QString, QVariant>::iterator iter = tmpMap.find("NetNum");
        int netNum = 0;
        if (iter == tmpMap.end()) {
            netNum = 0;
        }
        else {
            netNum = iter.value().toInt();
        }
        if(wire_info_map.isEmpty() || wire_info_map.count() <= 0) {
        }
        else {
            if(netNum == 1) {
                ComputerPage *page = NULL;
                if (wire_info_map.contains("NetLogicalname")) {
                    QMap<QString,QVariant>::iterator iter = wire_info_map.find("NetLogicalname");
                    QString netcard = iter.value().toString();
                    if (netcard.startsWith("veth") || netcard.startsWith("virbr")) {
                        page = new ComputerPage(scroll_widget->zone, tr("Vir NIC Info"));
                    }
                    else {
                        page = new ComputerPage(scroll_widget->zone, tr("NIC Info"));
                    }
                }
                else {
                    page = new ComputerPage(scroll_widget->zone, tr("NIC Info"));
                }
//                ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("NIC Info"));
                wire_info_map.remove("NetNum");
                QMap<QString, QVariant> tmpMap;
                QMap<QString,QVariant>::iterator it;
                for ( it = wire_info_map.begin(); it != wire_info_map.end(); ++it ) {
                    if (it.value().toString().length() > 0) {
                        if (QString::compare(it.value().toString(), "$", Qt::CaseInsensitive) != 0)//20161228
                            tmpMap.insert(it.key(), it.value());
                    }
                }
                page->setMap(wire_info_map, wire_info_map.value("NetVendor").toString().toUpper());
                page->initUI();
                scroll_widget->addScrollWidget(page);
            }
            else if(netNum > 1) {
                int vir = 0;
                int nic = 0;
                bool pageInit = false;
                for(int i=0;i<netNum;i++) {
                    ComputerPage *page = NULL;
                    tmp_info_map.clear();
                    pageInit = false;
                    QMap<QString, QVariant>::iterator itbegin = wire_info_map.begin();
                    QMap<QString, QVariant>::iterator  itend = wire_info_map.end();
                    for (;itbegin != itend; ++itbegin) {
                        if(itbegin.key() != "NetNum" && itbegin.value().toString().contains("<1_1>")) {
                            int len = itbegin.value().toString().split("<1_1>").length();
                            if (len > i) {
                                QString result = itbegin.value().toString().split("<1_1>").at(i);
                                if (result.length() > 0) {
                                    if (QString::compare(result, "$", Qt::CaseInsensitive) != 0) {
                                        tmp_info_map.insert(itbegin.key(), result);
                                        if (itbegin.key() == "NetLogicalname") {
                                            if (result.startsWith("veth") || result.startsWith("virbr")) {
                                                if (!pageInit) {
                                                    vir ++;
                                                    page = new ComputerPage(scroll_widget->zone, tr("Vir NIC Info %1").arg(vir));
                                                }
                                            }
                                            else {
                                                if (!pageInit) {
                                                    nic ++;
                                                    page = new ComputerPage(scroll_widget->zone, tr("NIC Info %1").arg(nic));
                                                }
                                            }
                                            pageInit = true;
                                        }
                                    }
                                }
                            }
                            else {
                                tmp_info_map.insert(itbegin.key(), "unknown");
                            }
                        }
                    }
//                    ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("NIC Info %1").arg(i+1));
                    page->setMap(tmp_info_map, tmp_info_map.value("NetVendor").toString().toUpper());
                    page->initUI();
                    scroll_widget->addScrollWidget(page);
                }
            }
        }

        if (wireless_info_map.isEmpty() || wireless_info_map.count() == 0) {
            page2 = NULL;
        }
        else {
            page2 = new ComputerPage(scroll_widget->zone, tr("WireLess NIC Info"));
            page2->setMap(wireless_info_map, wireless_info_map.value("WlanVendor").toString().toUpper());
            page2->initUI();
            scroll_widget->addScrollWidget(page2);
        }
    }*/
//    QMap<QString,QVariant>::iterator it;//遍历map
//    for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
//        if(it.key().startsWith("Wlan"))
//        {
//            if (it.value().toString().length() > 0) {
//                wireless_info_map.insert(it.key(), it.value());
//            }
//        }
//        else
//        {
//            if (it.value().toString().length() > 0) {
//                wire_info_map.insert(it.key(), it.value());
//            }
//        }
//    }

//    QMap<QString, QVariant>::iterator iter = tmpMap.find("NetNum");
//    int netNum = 0;
//    if (iter == tmpMap.end())
//    {
//        netNum = 0;
//    }
//    else {
//        netNum = iter.value().toInt();
//    }
//    if(wire_info_map.count() == 1 && wire_info_map.contains("kylinkobe"))
//    {
//    }
//    else {
//        if(netNum == 1)
//        {
//            ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("NIC Info"));
//            wire_info_map.remove("NetNum");
//            QMap<QString, QVariant> tmpMap;
//            QMap<QString,QVariant>::iterator it;
//            for ( it = wire_info_map.begin(); it != wire_info_map.end(); ++it ) {
//                if (it.value().toString().length() > 0) {
//                    if (QString::compare(it.value().toString(), "$", Qt::CaseInsensitive) != 0)//20161228
//                        tmpMap.insert(it.key(), it.value());
//                }
//            }
//            page->setMap(wire_info_map, wire_info_map.value("NetVendor").toString().toUpper());
//            page->initUI();
//            scroll_widget->addScrollWidget(page);
//        }
//        else if(netNum > 1)
//        {
//            for(int i=0;i<netNum;i++)
//            {
//                ComputerPage *page = new ComputerPage(scroll_widget->zone, tr("NIC Info %1").arg(i+1));
//                tmp_info_map.clear();
//                QMap<QString, QVariant>::iterator itbegin = wire_info_map.begin();
//                QMap<QString, QVariant>::iterator  itend = wire_info_map.end();
//                for (;itbegin != itend; ++itbegin)
//                {
//                    if(itbegin.key() != "NetNum" && itbegin.value().toString().contains("<1_1>")) {
//                        int len = itbegin.value().toString().split("<1_1>").length();
//                        if (len > i) {
//                            QString result = itbegin.value().toString().split("<1_1>").at(i);
//                            if (result.length() > 0) {
//                                if (QString::compare(result, "$", Qt::CaseInsensitive) != 0)//20161228
//                                    tmp_info_map.insert(itbegin.key(), result);
//                            }
//                        }
//                        else {
//                            tmp_info_map.insert(itbegin.key(), "unknown");
//                        }
//                    }
//                }
//                page->setMap(tmp_info_map, tmp_info_map.value("NetVendor").toString().toUpper());
//                page->initUI();
//                scroll_widget->addScrollWidget(page);
//            }
//        }
//    }

//    if((wireless_info_map.count() == 0) || (wireless_info_map.count() == 1 && wireless_info_map.contains("kylinkobe")))
//    {
//        page2 = NULL;
//    }
//    else {
//        page2 = new ComputerPage(scroll_widget->zone, tr("WireLess NIC Info"));
//        page2->setMap(wireless_info_map, wireless_info_map.value("WlanVendor").toString().toUpper());
//        page2->initUI();
//        scroll_widget->addScrollWidget(page2);
//    }
//    dataOK = true;



















//    QMap<QString,QVariant>::iterator it; //遍历map
//    for ( it = tmpMap.begin(); it != tmpMap.end(); ++it ) {
//        if(it.key().startsWith("Wlan"))
//        {
//            if (it.value().toString().length() > 0) {
//                wireless_info_map.insert(it.key(), it.value());
//            }
//        }
//        else
//        {
//            if (it.value().toString().length() > 0) {
//                wire_info_map.insert(it.key(), it.value());
//            }
//        }
//    }
//    if((wire_info_map.count() == 0) || (wire_info_map.count() == 1 && wire_info_map.contains("kylinkobe")))
//    {
//        page = NULL;
//    }
//    else {
//        page = new ComputerPage(scroll_widget->zone, tr("NIC Info"));
//        page->setMap(wire_info_map, wire_info_map.value("NetVendor").toString().toUpper());
//        page->initUI();
//        scroll_widget->addScrollWidget(page);
//    }
//    if((wireless_info_map.count() == 0) || (wireless_info_map.count() == 1 && wireless_info_map.contains("kylinkobe")))
//    {
//        page2 = NULL;
//    }
//    else {
//        page2 = new ComputerPage(scroll_widget->zone, tr("WireLess NIC Info"));
//        page2->setMap(wireless_info_map, wireless_info_map.value("WlanVendor").toString().toUpper());
//        page2->initUI();
//        scroll_widget->addScrollWidget(page2);
//    }
//    dataOK = true;
}
