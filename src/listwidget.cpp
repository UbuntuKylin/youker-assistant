#include "listwidget.h"
#include "infowidget.h"
#include "../info/infogui.h"

#include <QDBusConnection>

MListwidget::MListwidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(860,460);
    this->setAutoFillBackground(true);
    this->setStyleSheet("QWidget{background:#ffffff;border: none;\
                         border-bottom-right-radius:10px;\
                         border-bottom-left-radius:6px;}");

    splitter = new QSplitter(this);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->setOrientation(Qt::Horizontal);
    splitter->setChildrenCollapsible(false);
    splitter->setHandleWidth(1);

    listview = new QListWidget(this);
    listview->setFixedSize(160,this->height());
    listview->setFocusPolicy(Qt::NoFocus);
    listview->setObjectName("listview");
    listview->setMovement(QListView::Static);
    listview->setStyleSheet("QListWidget{background: rgb(237,237,237);line-height:10px;color:rgb(0,0,0,185);\
                            border-bottom-right-radius:0px}\
                            QListWidget::item:selected{background:white;color:black;}");

    stackedwidget = new QStackedWidget(this);
    stackedwidget->setFocusPolicy(Qt::NoFocus);
    stackedwidget->setAutoFillBackground(true);

    info_widget = new InfoWidget();

//    InitListUI();
    connect(listview,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(changeListwidgetpage(QListWidgetItem*)));

    //input info
    QDBusConnection::systemBus().connect("", \
                      "", \
                      "com.kylin.assistant.systemdaemon", \
                      "inputdev_info_signal", \
                      info_widget, SLOT(onSendInputInfo(QDBusMessage)));

    //multimedia info
    QDBusConnection::systemBus().connect("", \
                      "", \
                      "com.kylin.assistant.systemdaemon", \
                      "multimediadev_info_signal", \
                      info_widget, SLOT(onSendMultimediaInfo(QDBusMessage)));

    //communication info
    QDBusConnection::systemBus().connect("", \
                      "", \
                      "com.kylin.assistant.systemdaemon", \
                      "communicationdev_info_signal", \
                      info_widget, SLOT(onSendCommunicationInfo(QDBusMessage)));

    qDebug()<<Q_FUNC_INFO;
}

void MListwidget::InitListUI()
{
//    InitInfowidgetUI();
}

void MListwidget::InitInfowidgetUI()
{
    stringlist.clear();


    stringlist << tr("Local \nSystem");
    system_widget = new InfoGui(this);
    system_widget->setInfoGuiName("computer");
    stackedwidget->addWidget(system_widget);
    stackedwidget->setCurrentWidget(system_widget);
    emit this->m_requestRefreshSystemInfo();

    stringlist << tr("Hardware \nInformation");
//    info_widget = new InfoWidget();
//    info_widget->setInfoGuiName("info_widget");
    stackedwidget->addWidget(info_widget);
//    stackedwidget->setCurrentWidget(info_widget);
//    emit this->List_requestDesktopInfo();

    connect(info_widget,SIGNAL(requestDesktopInfo()),this,SLOT(onSendDesktopInfo_signal()));
    connect(this,SIGNAL(requestDesktopInfo_send(QMap<QString,QVariant>)),info_widget,SLOT(onSendDesktopInfo(QMap<QString, QVariant>)));
    connect(info_widget,SIGNAL(requestCpuInfo()),this,SLOT(onSendCpuInfo_signal()));
    connect(this,SIGNAL(requestCpuInfo_send(QMap<QString,QVariant>)),info_widget,SLOT(onSendCpuInfo(QMap<QString, QVariant>)));
    connect(info_widget,SIGNAL(requestMemoryInfo()),this,SLOT(onSendMemoryInfo_signal()));
    connect(this,SIGNAL(requestMemoryInfo_send(QMap<QString,QVariant>)),info_widget,SLOT(onSendMemoryInfo(QMap<QString, QVariant>)));
    connect(info_widget,SIGNAL(requestBoardInfo()),this,SLOT(onSendBoardInfo_signal()));
    connect(this,SIGNAL(requestBoardInfo_send(QMap<QString,QVariant>)),info_widget,SLOT(onSendBoardInfo(QMap<QString, QVariant>)));
    connect(info_widget,SIGNAL(requestHDInfo()),this,SLOT(onSendHDInfo_signal()));
    connect(this,SIGNAL(requestHDInfo_send(QMap<QString,QVariant>)),info_widget,SLOT(onSendHDInfo(QMap<QString, QVariant>)));
    connect(info_widget,SIGNAL(requestNicInfo()),this,SLOT(onSendNicInfo_signal()));
    connect(this,SIGNAL(requestNicInfo_send(QMap<QString,QVariant>)),info_widget,SLOT(onSendNicInfo(QMap<QString, QVariant>)));
    connect(info_widget,SIGNAL(requestMonitorInfo()),this,SLOT(onSendMonitorInfo_signal()));
    connect(this,SIGNAL(requestMonitorInfo_send(QMap<QString,QVariant>)),info_widget,SLOT(onSendMonitorInfo(QMap<QString, QVariant>)));
    connect(info_widget,SIGNAL(requestAudioInfo()),this,SLOT(onSendAudioInfo_signal()));
    connect(this,SIGNAL(requestAudioInfo_send(QMap<QString,QVariant>)),info_widget,SLOT(onSendAudioInfo(QMap<QString, QVariant>)));
    connect(info_widget,SIGNAL(requestBatteryInfo()),this,SLOT(onSendBatteryInfo_signal()));
    connect(this,SIGNAL(requestBatteryInfo_send(QMap<QString,QVariant>)),info_widget,SLOT(onSendBatteryInfo(QMap<QString, QVariant>)));
    connect(info_widget,SIGNAL(requestSensorInfo()),this,SLOT(onSendSensorInfo_signal()));
    connect(this,SIGNAL(requestSensorInfo_send(QMap<QString,QVariant>)),info_widget,SLOT(onSendSensorInfo(QMap<QString, QVariant>)));

    for(int i = 0; i < stringlist.length(); i++) {
        QListWidgetItem *item = new QListWidgetItem(stringlist.at(i),listview);
        item->setSizeHint(QSize(160,60));
        item->setStatusTip(stringlist.at(i));
        item->setToolTip(stringlist.at(i));
        item->setTextAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    }

    listview->setCurrentRow(0);

    stackedwidget->setFixedSize(750,this->height());
    stackedwidget->setAttribute(Qt::WA_TranslucentBackground);
    QHBoxLayout *main_layout = new QHBoxLayout(this);
    QVBoxLayout *right_layout = new QVBoxLayout();
    right_layout->addWidget(stackedwidget);
    right_layout->setSpacing(0);
    right_layout->setMargin(0);
    right_layout->setContentsMargins(0,0,0,0);
    splitter->addWidget(listview);
    splitter->addWidget(stackedwidget);

    main_layout->addWidget(splitter);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0,0,0,0);

    this->setLayout(main_layout);
    info_widget->initInfoUI(this->has_Battery,this->has_Sensor,this->all_info);
}


void MListwidget::setBatteryAndSensor(bool battery, bool sensor, QMap<QString,bool> info){
//    qDebug() << Q_FUNC_INFO << battery << sensor;
    this->has_Battery=battery;
    this->has_Sensor =sensor;
    this->all_info = info;
}

void MListwidget::changeListwidgetpage(QListWidgetItem *item)
{
//    qDebug() << "item======" << item;
    if(!item)
        return;
    QString page_Name = item->statusTip();
    if (page_Name.isEmpty() || page_Name.isNull())
        return;
//     qDebug() << "InfoWidget changeInfoPage" << page_Name;
    if(page_Name == tr("Hardware \nInformation") )
    {
        stackedwidget->setCurrentWidget(info_widget);
    }
    if(page_Name == tr("Local \nSystem") )
    {
        stackedwidget->setCurrentWidget(system_widget);
    }
}

void MListwidget::onSendSystemInfo(QMap<QString, QVariant> tmpMap)
{
    if (!tmpMap.isEmpty()) {
        QMap<QString, QVariant> sys_info_map;
        QMap<QString,QVariant>::iterator it;
        for (it = tmpMap.begin(); it != tmpMap.end(); ++it) {
                if (it.key() != "uptime" && it.value().toString().length() > 0) {
                    sys_info_map.insert(it.key(), it.value());
                }
            }
            if(sys_info_map.isEmpty() || sys_info_map.count() <= 0) {
                return;
            }
            else {
                for (int i = 0; i < stackedwidget->count(); i++) {
                    if (InfoGui *page = static_cast<InfoGui *>(stackedwidget->widget(i))) {
                        if (page->infoGuiName().isEmpty() || page->infoGuiName().isNull())
                            continue;
                        if (page->infoGuiName() == "computer") {
                            page->clearWidget();
                            page->loadOnePage(0, tr("Computer Info"), sys_info_map);
                            break;
                        }
                    }
                }
                sys_info_map.clear();
    //            if (system_widget) {
    //                system_widget->clearWidget();
    //                system_widget->loadOnePage(0, "Computer Info", sys_info_map);
    //            }
            }
    }
}

void MListwidget::onSendDesktopInfo_next(QMap<QString, QVariant> tmpMap)
{
//    qDebug() << Q_FUNC_INFO;
    emit this->requestDesktopInfo_send(tmpMap);
}

void MListwidget::onSendDesktopInfo_signal()
{
//    qDebug() << Q_FUNC_INFO;
    emit this->List_requestDesktopInfo();
}

void MListwidget::onSendCpuInfo_next(QMap<QString, QVariant> tmpMap)
{
//    qDebug() << Q_FUNC_INFO;
    emit this->requestCpuInfo_send(tmpMap);
}

void MListwidget::onSendCpuInfo_signal()
{
//    qDebug() << Q_FUNC_INFO;
    emit this->List_requestCpuInfo();
}

void MListwidget::onSendMemoryInfo_next(QMap<QString, QVariant> tmpMap)
{
    emit this->requestMemoryInfo_send(tmpMap);
}

void MListwidget::onSendMemoryInfo_signal()
{
    emit this->List_requestMemoryInfo();
}

void MListwidget::onSendBoardInfo_next(QMap<QString, QVariant> tmpMap)
{
    emit this->requestBoardInfo_send(tmpMap);
}

void MListwidget::onSendBoardInfo_signal()
{
    emit this->List_requestBoardInfo();
}

void MListwidget::onSendHDInfo_next(QMap<QString, QVariant> tmpMap)
{
    emit this->requestHDInfo_send(tmpMap);
}

void MListwidget::onSendHDInfo_signal()
{
    emit this->List_requestHDInfo();
}

void MListwidget::onSendNicInfo_next(QMap<QString, QVariant> tmpMap)
{
    emit this->requestNicInfo_send(tmpMap);
}

void MListwidget::onSendNicInfo_signal()
{
    emit this->List_requestNicInfo();
}

void MListwidget::onSendMonitorInfo_next(QMap<QString, QVariant> tmpMap)
{
    emit this->requestMonitorInfo_send(tmpMap);
}

void MListwidget::onSendMonitorInfo_signal()
{
    emit this->List_requestMonitorInfo();
}

void MListwidget::onSendAudioInfo_next(QMap<QString, QVariant> tmpMap)
{
    emit this->requestAudioInfo_send(tmpMap);
}

void MListwidget::onSendAudioInfo_signal()
{
    emit this->List_requestAudioInfo();
}

void MListwidget::onSendBatteryInfo_next(QMap<QString, QVariant> tmpMap)
{
    emit this->requestBatteryInfo_send(tmpMap);
}

void MListwidget::onSendBatteryInfo_signal()
{
    emit this->List_requestBatteryInfo();
}

void MListwidget::onSendSensorInfo_next(QMap<QString, QVariant> tmpMap)
{
    emit this->requestSensorInfo_send(tmpMap);
}

void MListwidget::onSendSensorInfo_signal()
{
    emit this->List_requestSensorInfo();
}
