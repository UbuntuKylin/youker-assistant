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

#include "maininfopage.h"
#include "dataworker.h"
#include "kabaseinfopage.h"

#include <QPainter>
#include <QPainterPath>
#include <QDebug>
#include <QJsonValue>
#include <QJsonObject>
#include <QJsonDocument>
#include <QTimer>

MainInfoPage::MainInfoPage(QWidget *parent)
    : QWidget(parent)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    initUI();
    initConnections();
}

void MainInfoPage::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainterPath path;

    QPainter painter(this);
    painter.setOpacity(1);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    painter.setClipping(true);
    painter.setPen(Qt::transparent);

    path.addRoundedRect(this->rect(), 6.0, 6.0);
    path.setFillRule(Qt::WindingFill);
    painter.setBrush(this->palette().base());
    painter.setPen(Qt::transparent);

    painter.drawPath(path);
}

MainInfoPage::~MainInfoPage()
{
    this->stopUDevHotPlugin();
}

void MainInfoPage::initUI()
{
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->setContentsMargins(32,0,0,0);
    m_mainLayout->setSpacing(8);
    m_tabbarLayout = new QHBoxLayout();
    m_tabbarLayout->setContentsMargins(0,0,0,0);
    m_tabbarLayout->setSpacing(8);

    m_tabbar = new KATabBar();
    m_tabbarLayout->addWidget(m_tabbar);
    m_tabbarLayout->addSpacing(32);
    m_mainLayout->addLayout(m_tabbarLayout);
    m_stackedInfoPage = new QStackedWidget();
    m_stackedInfoPage->setObjectName(QLatin1String("qt_tabwidget_stackedwidget"));
    m_stackedInfoPage->setLineWidth(0);
    m_mainLayout->addWidget(m_stackedInfoPage);

    this->setLayout(m_mainLayout);
}

void MainInfoPage::initConnections()
{
    connect(m_tabbar, &KATabBar::changeTabIndex, this, &MainInfoPage::onChangeInfoPage);
    connect(DataWorker::getInstance(), SIGNAL(updateHardwareInfo(unsigned, QString)), this, SLOT(onUpdateInfo(unsigned, QString)));
    connect(DataWorker::getInstance(), SIGNAL(updateLshwFinished()), this, SLOT(onLshwInfoUpdateFinished()));
    DataWorker::getInstance()->connectHardwareInfoSignal(true);
    DataWorker::getInstance()->connectLshwInfoSignal(true);
    this->startUDevHotPlugin();
}

void MainInfoPage::refreshInfo()
{
    Q_EMIT updateInfo(0);
    DataWorker::getInstance()->getHardwareInfo();
}

void MainInfoPage::onUpdateInfo(unsigned uStatus, QString strAllInfo)
{
    if (uStatus == 0 || strAllInfo.isEmpty()) {
        return;
    }
    onUpdateInfo(strAllInfo);
    if (m_tabbar)
        m_tabbar->onChangeTabIndex(0);
    QTimer::singleShot(0, this, [&,this,uStatus](){
        Q_EMIT this->updateInfo(uStatus);
    });
}

void MainInfoPage::onUpdateInfo(QString strAllInfo)
{
    // parse json string and init tabbar & stacked widget
#if 0
    strAllInfo = "{\"processor\":{\"processor\":\"processor111\",\"cores_num\":\"4\",\"threads_num\":\"8\","
                 "\"slot\":\"1\",\"fref\":\"2059Hz\",\"L1_cache\":\"L1_cache1\",\"L2_cache\":\"L2_cache1\","
                 "\"L3_cache\":\"L3_cache1\",\"instruction_set\":\"x86_64\",\"used\":\"10.2%\"}"

                 ",\"memory\":{\"list\":[{\"slot\":\"slot\",\"name\":\"name\",\"freq\":\"freq\",\"bus_width\":\"bus_width\","
                 "\"total_capacity\":\"total_capacity\",\"used_capacity\":\"used_capacity\",\"serail_num\":\"serail_num\","
                 "\"manufacturer\":\"manufacturer\"},"
                 "{\"slot\":\"slot\",\"name\":\"name1\",\"freq\":\"freq\",\"bus_width\":\"bus_width\",\"total_capacity\":\"total_capacity\","
                 "\"used_capacity\":\"used_capacity\",\"serail_num\":\"serail_num\",\"manufacturer\":\"manufacturer\"}]}"

                 ",\"graphics_card\":{\"list\":[{\"manufacturer\":\"manufacturer\",\"name\":\"name\",\"is_discrete\":\"1\","
                 "\"memory\":\"memory\"},{\"manufacturer\":\"manufacturer\",\"name\":\"name1\",\"is_discrete\":\"1\",\"memory\":\"memory\"}]}"

                 ",\"mother_board\":{\"name\":\"name\",\"chipset\":\"chipset\",\"serial_num\":\"serial_num\",\"publish_date\":\"publish_date\","
                 "\"bios_manufacturer\":\"bios_manufacturer\",\"bios_version\":\"bios_version\"}"

                 ",\"network_card\":{\"list\":[{\"name\":\"name\",\"is_wifi\":\"1\",\"mac_addr\":\"mac_addr\","
                 "\"connect_speed\":\"connect_speed\",\"mtu\":\"mtu\",\"ip_addr\":\"ip_addr\",\"subnet_mask\":\"subnet_mask\","
                 "\"gateway\":\"gateway\",\"dns_server\":\"dns_server\",\"recv_bytes\":\"recv_bytes\",\"send_bytes\":\"send_bytes\"},"
                 "{\"name\":\"name1\",\"is_wifi\":\"0\",\"mac_addr\":\"mac_addr\",\"connect_speed\":\"connect_speed\",\"mtu\":\"mtu\","
                 "\"ip_addr\":\"ip_addr\",\"subnet_mask\":\"subnet_mask\",\"gateway\":\"gateway\",\"dns_server\":\"dns_server\","
                 "\"recv_bytes\":\"recv_bytes\",\"send_bytes\":\"send_bytes\"}]}"

                 ",\"harddisk\":{\"list\":[{\"manufacturer\":\"manufacturer\",\"name\":\"name\",\"capacity\":\"capacity\","
                 "\"used_times\":\"used_times\",\"interface\":\"interface\",\"is_maindisk\":\"1\",\"is_ssd\":\"0\","
                 "\"serial_num\":\"serial_num\",\"model\":\"model\",\"trans_rate\":\"trans_rate\",\"read_speed\":\"read_speed\","
                 "\"write_speed\":\"write_speed\"},"
                 "{\"manufacturer\":\"manufacturerA\",\"name\":\"name1\",\"capacity\":\"capacity\",\"used_times\":\"used_times\","
                 "\"interface\":\"interface\",\"is_maindisk\":\"1\",\"is_ssd\":\"0\",\"serial_num\":\"serial_num\",\"model\":\"model\","
                 "\"trans_rate\":\"trans_rate\",\"read_speed\":\"read_speed\",\"write_speed\":\"write_speed\"}]}"

                 ",\"monitor\":{\"list\":[{\"manufacturer\":\"manufacturer\",\"name\":\"name\",\"size\":\"size\",\"ratio\":\"ratio\","
                 "\"resolution\":\"resolution\",\"max_available_resolution\":\"max_available_resolution\",\"is_main\":\"1\","
                 "\"gamma\":\"gamma\"},"
                 "{\"manufacturer\":\"manufacturer\",\"name\":\"name1\",\"size\":\"size\",\"ratio\":\"ratio\",\"resolution\":\"resolution\","
                 "\"max_available_resolution\":\"max_available_resolution\",\"is_main\":\"0\",\"gamma\":\"gamma\"}]}"

                 ",\"voice_card\":{\"list\":[{\"bus_addr\":\"bus_addr\",\"drive\":\"drive\",\"model\":\"model\",\"manufacturer\":\"manufacturer\"},"
                 "{\"bus_addr\":\"bus_addr\",\"drive\":\"driveAB\",\"model\":\"model\",\"manufacturer\":\"manufacturer\"}]}"

                 ",\"key_board\":{\"list\":[{\"dev_type\":\"dev_type\",\"name\":\"name\",\"dev_model\":\"dev_model\","
                 "\"manufacturer\":\"manufacturer\",\"dev_addr\":\"dev_addr\"}]}"

                 ",\"mouse\":{\"list\":[{\"dev_type\":\"dev_type1\",\"name\":\"name\",\"dev_model\":\"dev_model\","
                 "\"manufacturer\":\"manufacturer\",\"dev_addr\":\"dev_addr\"}]}"

                 ",\"battery\":{\"bat_model\":\"bat_model\",\"soc\":\"soc\",\"estimated_service_time\":\"estimated_service_time\","
                 "\"used_times\":\"used_times\"}"

                 ",\"camera\":{\"list\":[{\"name\":\"name\",\"resolution\":\"resolution\"}]}"

                 ",\"cddrive\":{\"list\":[{\"name\":\"name\"}]}"

                 ",\"bluetooth\":{\"list\":[{\"bus_addr\":\"bus_addr\",\"function\":\"function\",\"freq\":\"freq\","
                 "\"configuration\":\"configuration\",\"dev_type\":\"dev_type\",\"id\":\"123\",\"dev_model\":\"dev_model\","
                 "\"resource\":\"resource\",\"manufacturer\":\"manufacturer\",\"dev_version\":\"dev_version\",\"data_width\":\"data_width\"},"
                 "{\"bus_addr\":\"bus_addr1\",\"function\":\"function\",\"freq\":\"freq\",\"configuration\":\"configuration\","
                 "\"dev_type\":\"dev_type\",\"id\":\"123\",\"dev_model\":\"dev_model\",\"resource\":\"resource\",\"manufacturer\":\"manufacturer\","
                 "\"dev_version\":\"dev_version\",\"data_width\":\"data_width\"}]}"

                 ",\"fan\":{\"list\":[{\"speed\":\"1000hz\"},{\"speed\":\"600Hz\"}]}"
                 "}";
#endif
    qDebug()<<"Json:"<<strAllInfo;
    QJsonParseError jsonParseErr;
    QJsonDocument  rootDoc = QJsonDocument::fromJson(strAllInfo.toUtf8(), &jsonParseErr);//字符串格式化为JSON
    if (jsonParseErr.error != QJsonParseError::NoError) {
        qWarning() << "JSON格式错误:"<<jsonParseErr.errorString();
        return;
    } else {
         QJsonObject rootObj = rootDoc.object();
         if (rootObj.isEmpty()) {
             qWarning() << "JSON串为空";
             return;
         }
         // 处理器
         QJsonValue valJson = rootObj.value(PSI_ROOT);
         if (valJson.isObject()) {
             QJsonObject jsonObj = valJson.toObject();
             QString strInfo = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
             if (m_mapWidget.contains(HWINFO_PROCESSOR)) {
                 ProcessorInfo* processorInfo = qobject_cast<ProcessorInfo*>(m_mapWidget[HWINFO_PROCESSOR]);
                 if (processorInfo)
                    processorInfo->onUpdateInfo(strInfo);
             } else {
                 KATabButton *btnProcessor = new KATabButton();
                 btnProcessor->setText(tr("Processor"));
                 m_tabbar->addTabButton(btnProcessor);
                 m_processorInfo = new ProcessorInfo();
                 m_stackedInfoPage->addWidget(m_processorInfo);
                 m_mapWidget[HWINFO_PROCESSOR] = m_processorInfo;
                 m_processorInfo->onUpdateInfo(strInfo);
             }
         }
         // 内存
         valJson = rootObj.value(MMI_ROOT);
         if (valJson.isObject()) {
             QJsonObject jsonObj = valJson.toObject();
             QString strInfo = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
             if (m_mapWidget.contains(HWINFO_MEMORY)) {
                 MemoryInfo* memoryInfo = qobject_cast<MemoryInfo*>(m_mapWidget[HWINFO_MEMORY]);
                 if (memoryInfo) {
                     memoryInfo->onUpdateInfo(strInfo);
                 }
             } else {
                 KATabButton *btnMemory = new KATabButton();
                 btnMemory->setText(tr("Memory"));
                 m_tabbar->addTabButton(btnMemory);
                 m_memoryInfo = new MemoryInfo();
                 m_stackedInfoPage->addWidget(m_memoryInfo);
                 m_mapWidget[HWINFO_MEMORY] = m_memoryInfo;
                 m_memoryInfo->onUpdateInfo(strInfo);
             }
         }
         // 显卡
         valJson = rootObj.value(GSI_ROOT);
         if (valJson.isObject()) {
             QJsonObject jsonObj = valJson.toObject();
             QString strInfo = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
             if (m_mapWidget.contains(HWINFO_GRAPHICSCARD)) {
                 GraphicsCardInfo* graphicsCardInfo = qobject_cast<GraphicsCardInfo*>(m_mapWidget[HWINFO_GRAPHICSCARD]);
                 if (graphicsCardInfo) {
                     graphicsCardInfo->onUpdateInfo(strInfo);
                 }
             } else {
                 KATabButton *btnGraphicsCard = new KATabButton();
                 btnGraphicsCard->setText(tr("Graphics Card"));
                 m_tabbar->addTabButton(btnGraphicsCard);
                 m_graphicsCardInfo = new GraphicsCardInfo();
                 m_stackedInfoPage->addWidget(m_graphicsCardInfo);
                 m_mapWidget[HWINFO_GRAPHICSCARD] = m_graphicsCardInfo;
                 m_graphicsCardInfo->onUpdateInfo(strInfo);
             }
         }
         // 主板
         valJson = rootObj.value(MBI_ROOT);
         if (valJson.isObject()) {
             QJsonObject jsonObj = valJson.toObject();
             QString strInfo = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
             if (m_mapWidget.contains(HWINFO_MOTHERBOARD)) {
                 MotherBoardInfo* motherBoardInfo = qobject_cast<MotherBoardInfo*>(m_mapWidget[HWINFO_MOTHERBOARD]);
                 if (motherBoardInfo) {
                     motherBoardInfo->onUpdateInfo(strInfo);
                 }
             } else {
                 KATabButton *btnMotherBoard = new KATabButton();
                 btnMotherBoard->setText(tr("Motherboard"));
                 m_tabbar->addTabButton(btnMotherBoard);
                 m_motherBoardInfo = new MotherBoardInfo();
                 m_stackedInfoPage->addWidget(m_motherBoardInfo);
                 m_mapWidget[HWINFO_MOTHERBOARD] = m_motherBoardInfo;
                 m_motherBoardInfo->onUpdateInfo(strInfo);
             }
         }
         // 网卡
         valJson = rootObj.value(NWI_ROOT);
         if (valJson.isObject()) {
             QJsonObject jsonObj = valJson.toObject();
             QString strInfo = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
             if (m_mapWidget.contains(HWINFO_NETCARD)) {
                 NetCardInfo* netCardInfo = qobject_cast<NetCardInfo*>(m_mapWidget[HWINFO_NETCARD]);
                 if (netCardInfo) {
                     netCardInfo->onUpdateInfo(strInfo);
                 }
             } else {
                 KATabButton *btnNetCard = new KATabButton();
                 btnNetCard->setText(tr("Network Card"));
                 m_tabbar->addTabButton(btnNetCard);
                 m_netcardInfo = new NetCardInfo();
                 m_stackedInfoPage->addWidget(m_netcardInfo);
                 m_mapWidget[HWINFO_NETCARD] = m_netcardInfo;
                 m_netcardInfo->onUpdateInfo(strInfo);
             }
         }
         // 硬盘
         valJson = rootObj.value(HDI_ROOT);
         if (valJson.isObject()) {
             QJsonObject jsonObj = valJson.toObject();
             QString strInfo = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
             if (m_mapWidget.contains(HWINFO_HARDDISK)) {
                 HardDiskInfo* hardDiskInfo = qobject_cast<HardDiskInfo*>(m_mapWidget[HWINFO_HARDDISK]);
                 if (hardDiskInfo) {
                     hardDiskInfo->onUpdateInfo(strInfo);
                 }
             } else {
                 KATabButton *hardDiskCard = new KATabButton();
                 hardDiskCard->setText(tr("Hard Disk"));
                 m_tabbar->addTabButton(hardDiskCard);
                 m_harddiskInfo = new HardDiskInfo();
                 m_stackedInfoPage->addWidget(m_harddiskInfo);
                 m_mapWidget[HWINFO_HARDDISK] = m_harddiskInfo;
                 m_harddiskInfo->onUpdateInfo(strInfo);
             }
         }
         // 显示器
         valJson = rootObj.value(MNI_ROOT);
         qInfo()<<"MNI_ROOT isObject:"<<valJson.isObject();
         if (valJson.isObject()) {
             QJsonObject jsonObj = valJson.toObject();
             QString strInfo = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
             if (m_mapWidget.contains(HWINFO_MONITOR)) {
                 MonitorInfo* monitorInfo = qobject_cast<MonitorInfo*>(m_mapWidget[HWINFO_MONITOR]);
                 if (monitorInfo) {
                     monitorInfo->onUpdateInfo(strInfo);
                 }
             } else {
                 KATabButton *monitorInfo = new KATabButton();
                 monitorInfo->setText(tr("Monitor"));
                 m_tabbar->addTabButton(monitorInfo);
                 m_monitorInfo = new MonitorInfo();
                 m_stackedInfoPage->addWidget(m_monitorInfo);
                 m_mapWidget[HWINFO_MONITOR] = m_monitorInfo;
                 m_monitorInfo->onUpdateInfo(strInfo);
             }
         }
         // 声卡
         valJson = rootObj.value(VCI_ROOT);
         if (valJson.isObject()) {
             QJsonObject jsonObj = valJson.toObject();
             QString strInfo = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
             if (m_mapWidget.contains(HWINFO_VOICECARD)) {
                 VoiceCardInfo* voiceCardInfo = qobject_cast<VoiceCardInfo*>(m_mapWidget[HWINFO_VOICECARD]);
                 if (voiceCardInfo) {
                     voiceCardInfo->onUpdateInfo(strInfo);
                 }
             } else {
                 KATabButton *voiceCardInfo = new KATabButton();
                 voiceCardInfo->setText(tr("Sound Card"));
                 m_tabbar->addTabButton(voiceCardInfo);
                 m_voicecardInfo = new VoiceCardInfo();
                 m_stackedInfoPage->addWidget(m_voicecardInfo);
                 m_mapWidget[HWINFO_VOICECARD] = m_voicecardInfo;
                 m_voicecardInfo->onUpdateInfo(strInfo);
             }
         }
         // 键盘
         valJson = rootObj.value(KBI_ROOT);
         if (valJson.isObject()) {
             QJsonObject jsonObj = valJson.toObject();
             QString strInfo = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
             if (m_mapWidget.contains(HWINFO_KEYBOARD)) {
                 KeyboardInfo* keyboardInfo = qobject_cast<KeyboardInfo*>(m_mapWidget[HWINFO_KEYBOARD]);
                 if (keyboardInfo) {
                     keyboardInfo->onUpdateInfo(strInfo);
                 }
             } else {
                 KATabButton *keyboardInfo = new KATabButton();
                 keyboardInfo->setText(tr("Keyboard"));
                 m_tabbar->addTabButton(keyboardInfo);
                 m_keyboardInfo = new KeyboardInfo();
                 m_stackedInfoPage->addWidget(m_keyboardInfo);
                 m_mapWidget[HWINFO_KEYBOARD] = m_keyboardInfo;
                 m_keyboardInfo->onUpdateInfo(strInfo);
             }
         }
         // 鼠标
         valJson = rootObj.value(MSI_ROOT);
         if (valJson.isObject()) {
             QJsonObject jsonObj = valJson.toObject();
             QString strInfo = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
             if (m_mapWidget.contains(HWINFO_MOUSE)) {
                 MouseInfo* mouseInfo = qobject_cast<MouseInfo*>(m_mapWidget[HWINFO_MOUSE]);
                 if (mouseInfo) {
                     mouseInfo->onUpdateInfo(strInfo);
                 }
             } else {
                 KATabButton *mouseInfo = new KATabButton();
                 mouseInfo->setText(tr("Mouse"));
                 m_tabbar->addTabButton(mouseInfo);
                 m_mouseInfo = new MouseInfo();
                 m_stackedInfoPage->addWidget(m_mouseInfo);
                 m_mapWidget[HWINFO_MOUSE] = m_mouseInfo;
                 m_mouseInfo->onUpdateInfo(strInfo);
             }
         }
         // 电池
         valJson = rootObj.value(BTI_ROOT);
         if (valJson.isObject()) {
             QJsonObject jsonObj = valJson.toObject();
             QString strInfo = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
             if (m_mapWidget.contains(HWINFO_BATTERY)) {
                 BatteryInfo* batteryInfo = qobject_cast<BatteryInfo*>(m_mapWidget[HWINFO_BATTERY]);
                 if (batteryInfo) {
                     batteryInfo->onUpdateInfo(strInfo);
                 }
             } else {
                 KATabButton *batteryInfo = new KATabButton();
                 batteryInfo->setText(tr("Battery"));
                 m_tabbar->addTabButton(batteryInfo);
                 m_batteryInfo = new BatteryInfo();
                 m_stackedInfoPage->addWidget(m_batteryInfo);
                 m_mapWidget[HWINFO_BATTERY] = m_batteryInfo;
                 m_batteryInfo->onUpdateInfo(strInfo);
             }
         }
         // 光驱
         valJson = rootObj.value(CDI_ROOT);
         if (valJson.isObject()) {
             QJsonObject jsonObj = valJson.toObject();
             QString strInfo = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
             if (m_mapWidget.contains(HWINFO_CDROM)) {
                 CDRomInfo* cdromInfo = qobject_cast<CDRomInfo*>(m_mapWidget[HWINFO_CDROM]);
                 if (cdromInfo) {
                     cdromInfo->onUpdateInfo(strInfo);
                 }
             } else {
                 KATabButton *cdromInfo = new KATabButton();
                 cdromInfo->setText(tr("CD-ROM"));
                 m_tabbar->addTabButton(cdromInfo);
                 m_cdromInfo = new CDRomInfo();
                 m_stackedInfoPage->addWidget(m_cdromInfo);
                 m_mapWidget[HWINFO_CDROM] = m_cdromInfo;
                 m_cdromInfo->onUpdateInfo(strInfo);
             }
         }
         // 摄像头
         valJson = rootObj.value(CAI_ROOT);
         if (valJson.isObject()) {
             QJsonObject jsonObj = valJson.toObject();
             QString strInfo = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
             if (m_mapWidget.contains(HWINFO_CAMERA)) {
                 CameraInfo* cameraInfo = qobject_cast<CameraInfo*>(m_mapWidget[HWINFO_CAMERA]);
                 if (cameraInfo) {
                     cameraInfo->onUpdateInfo(strInfo);
                 }
             } else {
                 KATabButton *cameraInfo = new KATabButton();
                 cameraInfo->setText(tr("Camera"));
                 m_tabbar->addTabButton(cameraInfo);
                 m_cameraInfo = new CameraInfo();
                 m_stackedInfoPage->addWidget(m_cameraInfo);
                 m_mapWidget[HWINFO_CAMERA] = m_cameraInfo;
                 m_cameraInfo->onUpdateInfo(strInfo);
             }
         }
         // 蓝牙
         valJson = rootObj.value(BLI_ROOT);
         if (valJson.isObject()) {
             QJsonObject jsonObj = valJson.toObject();
             QString strInfo = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
             if (m_mapWidget.contains(HWINFO_BLUETOOTH)) {
                 BluetoothInfo* bluetoothInfo = qobject_cast<BluetoothInfo*>(m_mapWidget[HWINFO_BLUETOOTH]);
                 if (bluetoothInfo) {
                     bluetoothInfo->onUpdateInfo(strInfo);
                 }
             } else {
                 KATabButton *bluetoothInfo = new KATabButton();
                 bluetoothInfo->setText(tr("Bluetooth"));
                 m_tabbar->addTabButton(bluetoothInfo);
                 m_bluetoothInfo = new BluetoothInfo();
                 m_stackedInfoPage->addWidget(m_bluetoothInfo);
                 m_mapWidget[HWINFO_BLUETOOTH] = m_bluetoothInfo;
                 m_bluetoothInfo->onUpdateInfo(strInfo);
             }
         }
         // 风扇
         valJson = rootObj.value(FAI_ROOT);
         if (valJson.isObject() && DataWorker::getInstance()->getCpuFanEnable()) {
             QJsonObject jsonObj = valJson.toObject();
             QString strInfo = QJsonDocument(jsonObj).toJson(QJsonDocument::Compact);
             if (m_mapWidget.contains(HWINFO_FAN)) {
                 FanInfo* fanInfo = qobject_cast<FanInfo*>(m_mapWidget[HWINFO_FAN]);
                 if (fanInfo) {
                     fanInfo->onUpdateInfo(strInfo);
                 }
             } else {
                 KATabButton *fanInfo = new KATabButton();
                 fanInfo->setText(tr("Fan"));
                 m_tabbar->addTabButton(fanInfo);
                 m_fanInfo = new FanInfo();
                 m_stackedInfoPage->addWidget(m_fanInfo);
                 m_mapWidget[HWINFO_FAN] = m_fanInfo;
                 m_fanInfo->onUpdateInfo(strInfo);
             }
         }
    }
}

void MainInfoPage::onChangeInfoPage(int nPage)
{
    qInfo()<<"change Page:"<<nPage;
    switchWidgetAnimation(m_stackedInfoPage->currentIndex(), nPage);
}

void MainInfoPage::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
}

void MainInfoPage::switchWidgetAnimation(int nOldIndex, int nNewIndex)
{
#if 1
    m_stackedInfoPage->setCurrentIndex(nNewIndex);
    if (nOldIndex != nNewIndex) {
        KABaseInfoPage* subWidget = qobject_cast<KABaseInfoPage*>(m_stackedInfoPage->currentWidget());
        subWidget->onRefreshInfo();
    }
#else
    QWidget *oldWidget = m_stackedInfoPage->widget(nOldIndex);
    QWidget *newWidget = m_stackedInfoPage->widget(nNewIndex);
    if (!oldWidget || !newWidget) {
        return;
    }
    if (m_anmgWidget) {
        if (m_anmgWidget->state() == QAbstractAnimation::Running) {
            m_anmgWidget->stop();
        }
        delete m_anmgWidget;
        m_anmgWidget = nullptr;
    }
    if (nOldIndex < nNewIndex) {
        m_anmWidgetLeft = new QPropertyAnimation(oldWidget,"geometry");
        m_anmWidgetRight = new QPropertyAnimation(newWidget,"geometry");
        QRect leftRect = oldWidget->geometry();
        QRect rightRect = leftRect;
        m_anmWidgetLeft->setStartValue(leftRect);
        leftRect.setLeft(leftRect.left()-leftRect.width());
        leftRect.setRight(leftRect.right()-leftRect.width());
        m_anmWidgetLeft->setEndValue(leftRect);
        m_anmWidgetLeft->setDuration(500);
        m_anmWidgetLeft->setEasingCurve(QEasingCurve::Linear);

        m_anmWidgetRight->setEndValue(rightRect);
        rightRect.setLeft(rightRect.left()+rightRect.width());
        rightRect.setRight(rightRect.right()+rightRect.width());
        m_anmWidgetRight->setStartValue(rightRect);
        m_anmWidgetRight->setDuration(500);
        m_anmWidgetRight->setEasingCurve(QEasingCurve::Linear);
    } else {
        m_anmWidgetLeft = new QPropertyAnimation(newWidget,"geometry");
        m_anmWidgetRight = new QPropertyAnimation(oldWidget,"geometry");
        QRect leftRect = oldWidget->geometry();
        QRect rightRect = leftRect;
        m_anmWidgetLeft->setStartValue(leftRect);
        leftRect.setLeft(leftRect.left()+leftRect.width());
        leftRect.setRight(leftRect.right()+leftRect.width());
        m_anmWidgetLeft->setEndValue(leftRect);
        m_anmWidgetLeft->setDuration(500);
        m_anmWidgetLeft->setEasingCurve(QEasingCurve::Linear);

        m_anmWidgetRight->setEndValue(rightRect);
        rightRect.setLeft(rightRect.left()-rightRect.width());
        rightRect.setRight(rightRect.right()-rightRect.width());
        m_anmWidgetRight->setStartValue(rightRect);
        m_anmWidgetRight->setDuration(500);
        m_anmWidgetRight->setEasingCurve(QEasingCurve::Linear);
    }
    m_anmgWidget = new QParallelAnimationGroup(this);
    m_anmgWidget->addAnimation(m_anmWidgetLeft);
    m_anmgWidget->addAnimation(m_anmWidgetRight);
    m_anmgWidget->start();
    connect(m_anmgWidget, &QParallelAnimationGroup::finished, this, [&,this](){
        this->m_stackedInfoPage->setCurrentIndex(nNewIndex);
    });
#endif
}

void MainInfoPage::startUDevHotPlugin()
{
    m_udevHotPlugin = new UDevHotPlugin(this);
    connect(m_udevHotPlugin, &UDevHotPlugin::sendUdevAddNotify, this, &MainInfoPage::onUDevHotPluginAdd);
    connect(m_udevHotPlugin, &UDevHotPlugin::sendUdevRemoveNotify, this, &MainInfoPage::onUDevHotPluginRemove);
    m_udevHotPlugin->start();
    qDebug()<<"UdevHotPlugin started!!";
}

void MainInfoPage::stopUDevHotPlugin()
{
    if (m_udevHotPlugin) {
        m_udevHotPlugin->stopDevHotPlugin();
        m_udevHotPlugin->quit();
        m_udevHotPlugin->wait();
        qDebug()<<"UdevHotPlugin stoped!!";
    }
}

void MainInfoPage::onUDevHotPluginAdd(QString strUdevSubName, QString strUdevType)
{
    qDebug()<<"UDev Added:"<<strUdevSubName<<"|"<<strUdevType;
    if (strUdevSubName == "usb" && strUdevType == "usb_device") {
        QTimer::singleShot(500, this, [&,this](){
            DataWorker::getInstance()->updateLshwInfo();
            // update input info
            if (m_mapWidget.find(HWINFO_KEYBOARD) != m_mapWidget.end()) {
                KABaseInfoPage* subWidget = qobject_cast<KABaseInfoPage*>(m_mapWidget[HWINFO_KEYBOARD]);
                subWidget->onRefreshInfo();
            }
            if (m_mapWidget.find(HWINFO_MOUSE) != m_mapWidget.end()) {
                KABaseInfoPage* subWidget = qobject_cast<KABaseInfoPage*>(m_mapWidget[HWINFO_MOUSE]);
                subWidget->onRefreshInfo();
            }
        });
    }
    else if (strUdevSubName != "usb") {
    }
}

void MainInfoPage::onUDevHotPluginRemove(QString strUdevSubName, QString strUdevType)
{
    qDebug()<<"UDev Removed:"<<strUdevSubName<<"|"<<strUdevType;
    if (strUdevSubName == "usb" && strUdevType == "usb_device") {
        QTimer::singleShot(500, this, [&,this](){
            DataWorker::getInstance()->updateLshwInfo();
            // update input info
            if (m_mapWidget.find(HWINFO_KEYBOARD) != m_mapWidget.end()) {
                KABaseInfoPage* subWidget = qobject_cast<KABaseInfoPage*>(m_mapWidget[HWINFO_KEYBOARD]);
                subWidget->onRefreshInfo();
            }
            if (m_mapWidget.find(HWINFO_MOUSE) != m_mapWidget.end()) {
                KABaseInfoPage* subWidget = qobject_cast<KABaseInfoPage*>(m_mapWidget[HWINFO_MOUSE]);
                subWidget->onRefreshInfo();
            }
        });
    }
    else if (strUdevSubName != "usb") {
    }
}

void MainInfoPage::onLshwInfoUpdateFinished()
{
    qInfo()<<"onLshwInfoUpdateFinished";
    // update communication info
    if (m_mapWidget.find(HWINFO_BLUETOOTH) != m_mapWidget.end()) {
        KABaseInfoPage* subWidget = qobject_cast<KABaseInfoPage*>(m_mapWidget[HWINFO_BLUETOOTH]);
        subWidget->onRefreshInfo();
    }
    if (m_mapWidget.find(HWINFO_CDROM) != m_mapWidget.end()) {
        KABaseInfoPage* subWidget = qobject_cast<KABaseInfoPage*>(m_mapWidget[HWINFO_CDROM]);
        subWidget->onRefreshInfo();
    }
    // update HD info(invalid)
    if (m_mapWidget.find(HWINFO_HARDDISK) != m_mapWidget.end()) {
        KABaseInfoPage* subWidget = qobject_cast<KABaseInfoPage*>(m_mapWidget[HWINFO_HARDDISK]);
        subWidget->onRefreshInfo();
    }
    // update NIC info
    if (m_mapWidget.find(HWINFO_NETCARD) != m_mapWidget.end()) {
        KABaseInfoPage* subWidget = qobject_cast<KABaseInfoPage*>(m_mapWidget[HWINFO_NETCARD]);
        subWidget->onRefreshInfo();
    }
}
