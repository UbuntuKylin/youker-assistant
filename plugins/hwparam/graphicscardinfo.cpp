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

#include "graphicscardinfo.h"
#include "dataworker.h"

#include <QDebug>
#include <QTimer>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QJsonArray>

GraphicsCardInfo::GraphicsCardInfo(QWidget *parent)
    : KABaseInfoPage(parent)
{
    m_strInfoJson = "";
    initUI();
    initConnections();
}

void GraphicsCardInfo::initUI()
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

void GraphicsCardInfo::onUpdateInfo(QString strInfoJson)
{
    m_strInfoJson = strInfoJson;
    qInfo()<<"GraphicsCardInfo Info:"<<m_strInfoJson;
    QTimer::singleShot(0, this, [&, this, strInfoJson](){
        this->updateInfoItems(strInfoJson);
        this->chkNoDevice();
    });
}

void GraphicsCardInfo::initConnections()
{
    connect(DataWorker::getInstance(), SIGNAL(updateGraphicsCardInfo(uint,QString)), this, SLOT(onUpdateInfo(uint,QString)));
}

void GraphicsCardInfo::clearInfoItems()
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

void GraphicsCardInfo::addInfoItems(unsigned uGroup, unsigned uId, QString strTitle, QString strContent, bool bMulti)
{
    if (strContent.isEmpty())
        return;
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
            KAInfoTitle *infoTitle = new KAInfoTitle(QString("%1%2").arg(tr("Graphics Card")).arg(m_mapInfoItems.size()+1));
            infoTitle->setMinimumHeight(40);
            infoTitle->setFixedWidth(666);
            m_listLayout->addWidget(infoTitle);
            mapItems[GRAPHICSCARDINFO_TITLE] = infoTitle;
        }
        KInfoListItem *listItem = new KInfoListItem(strTitle, "", strContent, 0);
        listItem->setMinimumHeight(40);
        listItem->setFixedWidth(666);
        m_listLayout->addWidget(listItem);
        mapItems[uId] = listItem;
        m_mapInfoItems[uGroup] = mapItems;
    }
}

void GraphicsCardInfo::updateInfoItems(QString strInfoJson)
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
                    QJsonValue subItemValue = subItemObj.value(GSI_MANUFACTURER);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_MANUFACTURER, tr("Manufacturer"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_SUBSYSTEM);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_SUBSYSTEM, tr("SubSystem"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_NAME);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_NAME, tr("Name"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_ISDISCRETE);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_ISDISCRETE, tr("IsDiscrete"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_MEMORY);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_MEMORY, tr("Memory"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_CAPCITY);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_CAPCITY, tr("Video Memory"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_MEMTYPE);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_MEMTYPE, tr("Memory Type"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_MODEL);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_MODEL, tr("Model"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_VERSION);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_VERSION, tr("Version"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_BITWIDTH);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_BITWIDTH, tr("Bit Width"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_FUNCTION);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_FUNCTION, tr("Funtion"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_CLOCK);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_CLOCK, tr("Clock"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_DRIVER);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_DRIVER, tr("Driver"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_DBUSINFO);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_DBUSINFO, tr("Dbus Info"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_PHYSICSID);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_PHYSICSID, tr("ID"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_DEVICE);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_DEVICE, tr("Device"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_GDDRCAPACITY);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_GDDRCAPACITY, tr("GDDR Capacity"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_EGLVERSION);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_EGLVERSION, tr("EGL Version"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_EGLAPIS);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_EGLAPIS, tr("EGL Client APIs"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_GLVERSION);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_GLVERSION, tr("GL Version"), subItemValue.toString(), bMulti);
                    }
                    subItemValue = subItemObj.value(GSI_GLSLVERSION);
                    if (subItemValue.isString()) {
                        addInfoItems(n, GRAPHICSCARDINFO_GLSLVERSION, tr("GLSL Version"), subItemValue.toString(), bMulti);
                    }
                }
            }
         }
    }
}

void GraphicsCardInfo::onRefreshInfo()
{
    DataWorker::getInstance()->getGraphicsCardInfo();
}

void GraphicsCardInfo::chkNoDevice()
{
    unsigned infoSize = 0;
    QMap<unsigned,QMap<unsigned, QWidget*>>::iterator itMapInfoItems = m_mapInfoItems.begin();
    for (;itMapInfoItems != m_mapInfoItems.end(); itMapInfoItems++) {
        infoSize += itMapInfoItems.value().size();
    }
    if (infoSize == 0) {
        addInfoItems(0, GRAPHICSCARDINFO_INVALID, "", tr("Device not exitst or Get Device is Empty"), false);
    }
}
