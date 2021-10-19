/*
 * Copyright (C) 2021 KylinSoft Co., Ltd.
 *
 * Authors:
 *  Yang Min yangmin@kylinos.cn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "monitorinfo.h"
#include "dataworker.h"

#include <QDebug>
#include <QTimer>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>
#include <qx11info_x11.h>
#include <QApplication>
#include <X11/extensions/Xrandr.h>

MonitorInfo::MonitorInfo(QWidget *parent)
    : KABaseInfoPage(parent)
{
    m_strInfoJson = "";
    initUI();
    initConnections();
}

void MonitorInfo::initUI()
{
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(0);
    m_listLayout = new QVBoxLayout();
    m_listLayout->setContentsMargins(0,0,0,0);
    m_listLayout->setSpacing(0);
    m_listLayout->setAlignment(Qt::AlignTop);
    m_listFrame = new QFrame();
    m_listFrame->setLayout(m_listLayout);
    m_scrollFrame = new QScrollArea();
    m_scrollFrame->setContentsMargins(0, 0, 0, 0);
    m_scrollFrame->setBackgroundRole(QPalette::Base);
    m_scrollFrame->setAutoFillBackground(true);
    m_scrollFrame->setFrameStyle(0);
    m_scrollFrame->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollFrame->setWidgetResizable(true);
    m_scrollFrame->setWidget(m_listFrame);

    m_mainLayout->addWidget(m_scrollFrame);
    this->setLayout(m_mainLayout);
}

void MonitorInfo::onUpdateInfo(QString strInfoJson)
{
    m_strInfoJson = strInfoJson;
    qInfo()<<"Monitor Info:"<<m_strInfoJson;
    QTimer::singleShot(0, this, [&, this, strInfoJson](){
        this->updateInfoItems(strInfoJson);
        this->chkNoDevice();
    });
}

void MonitorInfo::initConnections()
{
    //注册监听xrr事件
    XRRQueryExtension(QX11Info::display(), &m_xrrEventBase, &m_xrrErrorBase);
    XRRSelectInput(QX11Info::display(), QX11Info::appRootWindow(), RRScreenChangeNotifyMask);
    qApp->installNativeEventFilter(this); //监听全局x事件，调用了这个才能收到nativeEventFilter

    connect(DataWorker::getInstance(), SIGNAL(updateMonitorInfo(uint,QString)), this, SLOT(onUpdateInfo(uint,QString)));
}

bool MonitorInfo::nativeEventFilter(const QByteArray &eventType, void *message, long *result) //监听全局x事件
{
    if (qstrcmp(eventType, "xcb_generic_event_t") != 0) {
        return false;
    }

    xcb_generic_event_t *event = reinterpret_cast<xcb_generic_event_t*>(message);
    const uint8_t responseType = event->response_type & ~0x80;
    if(responseType == m_xrrEventBase + RRScreenChangeNotify){
        RRScreenChangeEvent();  //屏幕改变事件
    }
    return false;
}

void MonitorInfo::RRScreenChangeEvent()
{
    XRRScreenResources *screen;
    screen = XRRGetScreenResources(QX11Info::display(), QX11Info::appRootWindow());
    XRROutputInfo *info;
    int nCurCount = 0;
    static int nLastCount = -1;

    //这里只是屏幕改变事件，通过屏幕改变事件遍历所有
    for (int i = 0; i < screen->noutput; i++) {
        info = XRRGetOutputInfo(QX11Info::display(), screen, screen->outputs[i]);
        if (info->connection == RR_Connected) {
            nCurCount++;
        }
        XRRFreeOutputInfo(info);
    }
    /*
        count为当前连接的显示器个数，每次记录并比较就可以得到显示器的热插拔事件
    */
    XRRFreeScreenResources(screen);

    // 屏幕数发生变化，获取最新屏幕信息
    if (nCurCount != nLastCount) {
        nLastCount = nCurCount;
        DataWorker::getInstance()->getMonitorInfo(true);
    }
}

void MonitorInfo::clearInfoItems()
{
    QMap<unsigned,QMap<unsigned, QWidget*>>::iterator itMapInfoItems = m_mapInfoItems.begin();
    for (;itMapInfoItems != m_mapInfoItems.end(); itMapInfoItems++) {
        QMap<unsigned, QWidget*>::iterator itInfoItems = itMapInfoItems.value().begin();
        for (;itInfoItems != itMapInfoItems.value().end(); itInfoItems++) {
            if (itInfoItems.value()) {
                delete itInfoItems.value();
            }
        }
        itMapInfoItems.value().clear();
    }
    m_mapInfoItems.clear();
}

void MonitorInfo::addInfoItems(unsigned uGroup, unsigned uId, QString strTitle, QString strContent, bool bMulti)
{
    if (strContent.isEmpty())
        return ;
    if (m_mapInfoItems.contains(uGroup)) {
        QMap<unsigned,QMap<unsigned, QWidget*>>::iterator itMapInfoItems = m_mapInfoItems.find(uGroup);
        if (itMapInfoItems != m_mapInfoItems.end()) {
            if (itMapInfoItems.value().contains(uId)) {
                KInfoListItem *listItem = qobject_cast<KInfoListItem *>(itMapInfoItems.value()[uId]);
                if (listItem) {
                    listItem->updateDetailInfo(strContent);
                }
            } else {
                bool isSigleLine = true;
                if (bMulti) {
                    isSigleLine = (itMapInfoItems.value().size()-1)%2;
                } else {
                    isSigleLine = itMapInfoItems.value().size()%2;
                }
                KInfoListItem *listItem = new KInfoListItem(strTitle, "", strContent, isSigleLine);
                listItem->setMinimumHeight(40);
                listItem->setFixedWidth(666);
                m_listLayout->addWidget(listItem);
                itMapInfoItems.value()[uId] = listItem;
            }
        }
    } else {
        QMap<unsigned, QWidget*> mapItems;
        if (bMulti) {
            KAInfoTitle *infoTitle = new KAInfoTitle(QString("%1%2").arg(tr("Monitor")).arg(m_mapInfoItems.size()+1));
            infoTitle->setMinimumHeight(40);
            infoTitle->setFixedWidth(666);
            m_listLayout->addWidget(infoTitle);
            mapItems[MONITORINFO_TITLE] = infoTitle;
        }
        KInfoListItem *listItem = new KInfoListItem(strTitle, "", strContent, 0);
        listItem->setMinimumHeight(40);
        listItem->setFixedWidth(666);
        m_listLayout->addWidget(listItem);
        mapItems[uId] = listItem;
        m_mapInfoItems[uGroup] = mapItems;
    }
}

void MonitorInfo::updateInfoItems(QString strInfoJson)
{
    if (strInfoJson.isEmpty())
        return;
    qInfo()<<"Cur info:"<<strInfoJson;
    QJsonParseError jsonParseErr;
    QJsonDocument  rootDoc = QJsonDocument::fromJson(strInfoJson.toUtf8(), &jsonParseErr);//字符串格式化为JSON
    if (jsonParseErr.error != QJsonParseError::NoError) {
        qWarning() << "JSON格式错误";
        return;
    } else {
         QJsonObject rootObj = rootDoc.object();
         if (rootObj.isEmpty()) {
             qWarning() << "JSON串为空";
             return;
         }
         QJsonValue valJson = rootObj.value("list");
         if (valJson.isArray()) {
            QJsonArray arrayJson = valJson.toArray();
            clearInfoItems();
            bool bMulti = false;
            if (arrayJson.size() > 1) {
                bMulti = true;
            }
            for (int n = 0; n < arrayJson.size(); n++) {
                if (arrayJson.at(n).isObject()) {
                    QJsonObject subItemObj = arrayJson.at(n).toObject();
                    QJsonValue subItemValue = subItemObj.value(MNI_MANUFACTURER);
                    if (subItemValue.isString()) {
                        addInfoItems(n, MONITORINFO_MANUFACTURER, tr("Manufacturer"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(MNI_NAME);
                    if (subItemValue.isString()) {
                        addInfoItems(n, MONITORINFO_NAME, tr("Name"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(MNI_SIZE);
                    if (subItemValue.isString()) {
                        addInfoItems(n, MONITORINFO_SIZE, tr("Size"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(MNI_RATIO);
                    if (subItemValue.isString()) {
                        addInfoItems(n, MONITORINFO_RATIO, tr("Ratio"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(MNI_RESOLUTION);
                    if (subItemValue.isString()) {
                        addInfoItems(n, MONITORINFO_RESOLUTION, tr("Resolution"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(MNI_MAXAVARES);
                    if (subItemValue.isString()) {
                        addInfoItems(n, MONITORINFO_MAXAVARES, tr("MAX Resolution"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(MNI_ISMAIN);
                    if (subItemValue.isString()) {
                        QString strYesOrNo = "";
                        if (subItemValue.toString() == "1") {
                            strYesOrNo = tr("Yes");
                        } else {
                            strYesOrNo = tr("No");
                        }
                        addInfoItems(n, MONITORINFO_ISMAIN, tr("Main Screen"), strYesOrNo, bMulti);
                    }
                    subItemValue = subItemObj.value(MNI_INTERFACE);
                    if (subItemValue.isString()) {
                        addInfoItems(n, MONITORINFO_INTERFACE, tr("Interface"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(MNI_VISIBLEAREA);
                    if (subItemValue.isString()) {
                        addInfoItems(n, MONITORINFO_VISIBLEAREA, tr("Visible Area"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(MNI_WEEK);
                    if (subItemValue.isString()) {
                        addInfoItems(n, MONITORINFO_WEEK, tr("Product Week"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(MNI_YEAR);
                    if (subItemValue.isString()) {
                        addInfoItems(n, MONITORINFO_YEAR, tr("Product Year"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(MNI_GAMMA);
                    if (subItemValue.isString()) {
                        addInfoItems(n, MONITORINFO_GAMMA, tr("Gamma"), subItemValue.toString(), bMulti);
                    }
                }
            }
         }
    }
}

void MonitorInfo::onRefreshInfo()
{
    DataWorker::getInstance()->getMonitorInfo(false);
}

void MonitorInfo::chkNoDevice()
{
    unsigned infoSize = 0;
    QMap<unsigned,QMap<unsigned, QWidget*>>::iterator itMapInfoItems = m_mapInfoItems.begin();
    for (;itMapInfoItems != m_mapInfoItems.end(); itMapInfoItems++) {
        infoSize += itMapInfoItems.value().size();
    }
    if (infoSize == 0) {
        addInfoItems(0, MONITORINFO_INVALID, "", tr("Device not exitst or Get Device is Empty"), false);
    }
}
