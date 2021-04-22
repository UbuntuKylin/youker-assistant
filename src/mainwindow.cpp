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

#include "mainwindow.h"
#include <QDebug>
#include <QApplication>
#include <QDesktopWidget>
#include <QGSettings/qgsettings.h>
#include <QGraphicsDropShadowEffect>
#include <QStackedLayout>
#include <X11/extensions/Xrandr.h>
#include <qx11info_x11.h>
#include <libudev.h>
#include "../component/utils.h"
#include "../component/threadpool.h"
#include "dataworker.h"
#include "../component/utils.h"
#include "monitorwidget.h"
#include "optimizedwidget.h"

#include "maintopwidget.h"
#include "middlewidget.h"
#include "mainbottomwidget.h"
#include "topbasewidget.h"
#include "listwidget.h"
#include "drivewidget.h"
#include <QtMath>

#include <QDBusInterface>

#include "xatom-helper.h"

#define KYLIN_USER_GUIDE_PATH "/"

#define KYLIN_USER_GUIDE_SERVICE "com.kylinUserGuide.hotel"

#define KYLIN_USER_GUIDE_INTERFACE "com.guide.hotel"

#include <unistd.h>

QString GlobalData::globalarch = ""; // add by hebing, just for transmit var

inline bool isRunningInstalled() {
    static bool installed = (QCoreApplication::applicationDirPath() ==
                             QDir(("/usr/bin")).canonicalPath());
    return installed;
}

inline QString getPluginsDirectory() {
    if (isRunningInstalled()) {
        return QString("/usr/lib/kylin-assistant/plugins/");
    } else {
        return QString(QCoreApplication::applicationDirPath() + "/plugins/");
    }
}

MainWindow::MainWindow(QString cur_arch, int d_count, QWidget* parent/*, Qt::WindowFlags flags*/)
    : QMainWindow(parent/*, flags*/)
    , m_mousePressed(false)
    , arch(cur_arch)
    , display_count(d_count)
{
    this->hide();
    qDebug() << Q_FUNC_INFO ;
    GlobalData::globalarch = this->arch;

    registerCustomDataMetaType();
    registerCustomDataListMetaType();

    //注册监听xrr事件
    XRRQueryExtension(QX11Info::display(), &rr_event_base, &rr_error_base);
    XRRSelectInput(QX11Info::display(), QX11Info::appRootWindow(), RRScreenChangeNotifyMask);
    qApp->installNativeEventFilter(this); //监听全局x事件，调用了这个才能收到nativeEventFilter 

//    this->setStyleSheet("background : red");

    this->osName = accessOSName();
//    char *dsk;
//    dsk = getenv("XDG_CURRENT_DESKTOP");
    this->desktop = qgetenv("XDG_CURRENT_DESKTOP");
    if(this->desktop.isEmpty())
        this->desktop = qgetenv("XDG_SESSION_DESKTOP");

    // 添加窗管协议
    MotifWmHints hints;
    hints.flags = MWM_HINTS_FUNCTIONS|MWM_HINTS_DECORATIONS;
    hints.functions = MWM_FUNC_ALL;
    hints.decorations = MWM_DECOR_BORDER;
    XAtomHelper::getInstance()->setWindowMotifHint(this->winId(), hints);

//    this->setWindowFlags(Qt::FramelessWindowHint);
    //For UKUI and Mate
//    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAutoFillBackground(true);
    this->setMouseTracking(true);
    this->setWindowTitle(tr("Kylin Assistant"));

    if(QIcon::hasThemeIcon("kylin-assistant"))
        this->setWindowIcon(QIcon::fromTheme("kylin-assistant"));
    else
        this->setWindowIcon(QIcon(":/res/kylin-assistant.png"));

    this->setWindowOpacity(1);
    this->setFixedSize(MAIN_WINDOW_WIDTH, MAIN_WINDOW_HEIGHT);

    status = "Cleanup";

    mSettings = new QSettings(KYLIN_COMPANY_SETTING, KYLIN_SETTING_FILE_NAME_SETTING);
    mSettings->setIniCodec("UTF-8");

    last_skin_path = ":/background/res/skin/1.png";

    main_skin_pixmap.load(last_skin_path);

    info_widget = NULL;
    cleaner_widget = NULL;
//    setting_widget = NULL;
    box_widget = NULL;
    aboutDlg = NULL;

    cleaner_action_widget = NULL;
    setting_action_widget = NULL;
    box_action_widget = NULL;

    toolKits = new Toolkits(0, this->width(), this->height());

//    main_menu = new KylinMenu(this);
//    main_menu->setParentWindow(this);
//    main_menu->initConnect();
    main_menu = new QMenu(this);
    main_menu->setMinimumWidth(160);
    main_menu->addAction(tr("Help"));
    main_menu->addAction(tr("About"));
    main_menu->addAction(tr("Exit"));

    connect(main_menu,&QMenu::triggered,this,[=](QAction *action){
        qDebug() << Q_FUNC_INFO << action->text();
        if(action->text() == tr("About")){
            if(!aboutDlg){
               createAboutDialog();
            }
            aboutDlg->move(this->geometry().left()+220,this->geometry().top()+25);
            aboutDlg->setModal(true);
            aboutDlg->show();
        }else if(action->text() == tr("Help")){
            QProcess *process = new QProcess(this);
            QString cmd = "kylin-user-guide";
            QStringList arg;
            qDebug() << Q_FUNC_INFO;
            arg << "-A" << "kylin-assistant";
            process->start(cmd,arg);
        }else if(action->text() == tr("Exit")){
            this->close();
        }
    });

    this->startDbusDaemon();
/*
    codes below moved to onInitDataFinished()
*/
//    this->initWidgets();
//
//    //边框阴影效果
//    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
//    shadow_effect->setBlurRadius(5);
//    shadow_effect->setColor(QColor(0, 0, 0, 0));
//    shadow_effect->setOffset(2, 4);
//    this->setGraphicsEffect(shadow_effect);
//
//    const QByteArray id("org.ukui.style");
//    if (QGSettings::isSchemaInstalled(id)){
//        QGSettings *Setting = new QGSettings(id);
//        connect(Setting,&QGSettings::changed,[=](QString key){
//            if("systemFont" == key || "systemFontSize" == key ){
//                QFont font = this->font();
////                int width = font.pointSize();
//                for (auto widget: qApp->allWidgets()) {
//                    widget->setFont(font);
//                }
//            }
//            if("iconThemeName" == key){
//                if(QIcon::hasThemeIcon("kylin-assistant"))
//                    this->setWindowIcon(QIcon::fromTheme("kylin-assistant"));
//                else
//                    this->setWindowIcon(QIcon(":/res/kylin-assistant.png"));
//            }
//        });
//    }

}

void MainWindow::paintEvent(QPaintEvent *event)
{
//    Q_UNUSED(event)
//    QPainterPath path;
//    path.setFillRule(Qt::WindingFill);
//    path.addRoundRect(10,10,this->width()-20,this->height()-20,2,2);
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing,true);
//    painter.fillPath(path,QBrush(Qt::white));
//    QColor color(0,0,0,50);
//    for(int i = 0 ; i < 10 ; ++i)
//    {
//        QPainterPath path;
//        path.setFillRule(Qt::WindingFill);
//        path.addRoundRect(10-i,10-i,this->width()-(10-i)*2,this->height()-(10-i)*2,2,2);
//        color.setAlpha(150 - qSqrt(i)*50);
//        painter.setPen(color);
//        painter.drawPath(path);
//    }

    QWidget::paintEvent(event);
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{

    qDebug() << Q_FUNC_INFO;
    if (event->key() == Qt::Key_F1){
        QString serviceName = KYLIN_USER_GUIDE_SERVICE + QString("%1%2").arg("_").arg(QString::number(getuid()));

        QDBusInterface *  iface = new QDBusInterface(serviceName,
                                                         KYLIN_USER_GUIDE_PATH,
                                                         KYLIN_USER_GUIDE_INTERFACE,
                                                         QDBusConnection::sessionBus(),
                                                         this);
        QDBusMessage msg = iface->call(QString("showGuide"), "kylin-assistant");

        delete iface;
    }
}

MainWindow::~MainWindow()
{
//    delete m_qSystemDbus;
    this->stopUDevHotPlugin();

    if (m_dataWorker) {
        m_dataWorker->deleteLater();
    }
    ThreadPool::Instance()->deleteLater();

    if (info_widget != NULL)
    {
        delete info_widget;
        info_widget = NULL;
    }
    if (cleaner_widget != NULL)
    {
        delete cleaner_widget;
        cleaner_widget = NULL;
    }
//    if (setting_widget != NULL)
//    {
//        delete setting_widget;
//        setting_widget = NULL;
//    }
    if (box_widget != NULL)
    {
        delete box_widget;
        box_widget = NULL;
    }
    if (aboutDlg != NULL)
    {
        delete aboutDlg;
        aboutDlg = NULL;
    }
    if (toolKits != NULL)
    {
        delete toolKits;
        toolKits = NULL;
    }
    if (mSettings != NULL)
    {
        mSettings->sync();
        delete mSettings;
        mSettings = NULL;
    }
    if (centralWidget != NULL) {
        delete centralWidget;
        centralWidget = nullptr;
    }
}

void MainWindow::initWidgets()
{
    QPalette palette_back;
    palette_back.setBrush(QPalette::Background, QBrush(QPixmap(last_skin_path)));

    m_topStack = new QStackedWidget(this);
    m_bottomStack = new QStackedWidget(this);

    //middle
    m_middleWidget = new MiddleWidget(this, this->arch, this->osName);
    if(!fan && !temperature && !cpufm)
        m_middleWidget->setHideMonitorWidget(true);
    m_middleWidget->setFixedSize(MAIN_WINDOW_WIDTH, 140);
    connect(m_middleWidget, SIGNAL(turnCurrentPage(QString)), this, SLOT(setCurrentPageIndex(QString)));
    connect(m_middleWidget, SIGNAL(middle_showMenu()), this, SLOT(showMainMenu()));
    connect(m_middleWidget, SIGNAL(middle_showMin()), this, SLOT(showMinimized()));
    connect(m_middleWidget, SIGNAL(middle_closeApp()), this, SLOT(closeYoukerAssistant()));

    //bottom
//    m_mainBottomWidget = new MainBottomWidget(this, this->arch, this->osName);
//    connect(m_mainBottomWidget, SIGNAL(sendSignal()), m_middleWidget, SLOT(showBoxTool()));
//    m_bottomStack->addWidget(m_mainBottomWidget);

    optimized_widget = new OptimizedWidget();
    m_bottomStack->addWidget(optimized_widget);

    cleaner_widget = new CleanerWidget();
    m_bottomStack->addWidget(cleaner_widget);
    cleaner_widget->setToolKits(toolKits);
    cleaner_widget->setParentWindow(this);
    cleaner_widget->initUI(last_skin_path);
//    connect(cleaner_action_widget, SIGNAL(showDetailData()),cleaner_widget, SLOT(displayDetailPage()));
//    connect(cleaner_action_widget, SIGNAL(showMainData()),cleaner_widget, SLOT(displayMainPage()));
//    connect(cleaner_action_widget, SIGNAL(sendCleanSignal()),cleaner_widget, SIGNAL(transCleanSignal()));

    info_widget = new InfoWidget(this->arch);

    // connect(m_dataWorker, &DataWorker::sendDevicePageNotExists, info_widget, &InfoWidget::resetInfoLeftListUI);

    m_bottomStack->addWidget(info_widget);
//    list_widget = new MListwidget();
//    m_bottomStack->addWidget(list_widget);

    drive_widget = new Drivewidget();
    m_bottomStack->addWidget(drive_widget);

//    setting_widget = new SettingWidget(this->desktop);
//    setting_widget->setParentWindow(this);
//    connect(setting_widget, SIGNAL(changeActionPage(QString)), setting_action_widget, SLOT(displayActionSubPage(QString)));
//    connect(setting_action_widget, SIGNAL(notifyContentPageToMain()), setting_widget, SLOT(displaySettingHomePage()));
//    m_bottomStack->addWidget(setting_widget);

    box_widget = new BoxWidget(this, this->arch, this->osName, getPluginsDirectory());
    connect(box_widget, SIGNAL(pluginModuleError(QString)), this, SLOT(onPluginModuleError(QString)));
    m_bottomStack->addWidget(box_widget);

    monitorwidget = new Monitorwidget();
    m_bottomStack->addWidget(monitorwidget);

    centralWidget = new QWidget;
//    centralWidget->setStyleSheet("background: transparent");
    QVBoxLayout *contentLayout = new QVBoxLayout(centralWidget);
    this->setCentralWidget(centralWidget);
//    this->setContentsMargins(SHADOW_LEFT_TOP_PADDING+8,SHADOW_LEFT_TOP_PADDING+7,SHADOW_RIGHT_BOTTOM_PADDING+6,SHADOW_RIGHT_BOTTOM_PADDING+6);
    this->setContentsMargins(0,0,0,0);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setMargin(0);
    contentLayout->setSpacing(0);

//    contentLayout->addWidget(m_topStack);
    contentLayout->addWidget(m_middleWidget);
    contentLayout->addWidget(m_bottomStack);
//    m_topStack->setCurrentWidget(m_mainTopWidget);
    m_bottomStack->setCurrentWidget(cleaner_widget);

    /* 初始化标题栏 */
    m_middleWidget->InitMiddlewidget();

    this->moveCenter();

}

void MainWindow::onInitDataFinished()
{
    qDebug() << Q_FUNC_INFO;
    //边框阴影效果
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setBlurRadius(5);
    shadow_effect->setColor(QColor(0, 0, 0, 0));
    shadow_effect->setOffset(2, 4);
    this->setGraphicsEffect(shadow_effect);

    const QByteArray id("org.ukui.style");
    if (QGSettings::isSchemaInstalled(id)){
        QGSettings *Setting = new QGSettings(id);
        connect(Setting,&QGSettings::changed,[=](QString key){
            if("systemFont" == key || "systemFontSize" == key ){
                QFont font = this->font();
//                int width = font.pointSize();
                for (auto widget: qApp->allWidgets()) {
                    widget->setFont(font);
                }
            }
            if("iconThemeName" == key){
                if(QIcon::hasThemeIcon("kylin-assistant"))
                    this->setWindowIcon(QIcon::fromTheme("kylin-assistant"));
                else
                    this->setWindowIcon(QIcon(":/res/kylin-assistant.png"));
            }
        });
    }
    this->battery = m_dataWorker->isBatteryExist();
    this->sensor = m_dataWorker->isSensorExist();
    this->temperature = m_dataWorker->hide_temperature_page();
    this->fan = m_dataWorker->hide_fan_page();
    this->cpufm = m_dataWorker->hide_cpufm_page();
//    this->info = m_dataWorker->onRequesetAllInfoIsHaveValue();
//    qDebug() << Q_FUNC_INFO << info;

    this->initWidgets();

    this->m_cpulist = m_dataWorker->cpuModeList();
    this->m_currentCpuMode = m_dataWorker->cpuCurrentMode();
    this->m_cpufreqlist = m_dataWorker->cpuFreqList();
    // this->m_cpuFreqRange = m_dataWorker->cpuFreqRange();
//    qDebug() << Q_FUNC_INFO <<this->m_cpulist << this->m_currentCpuMode;

    /*
    Qt::AutoConnection 自动连接：（默认值）如果信号在接收者所依附的线程内发射，则等同于直接连接。如果发射信号的线程和接受者所依附的线程不同，则等同于队列连接。
    Qt::DirectConnection 直接连接：当信号发射时，槽函数将直接被调用。无论槽函数所属对象在哪个线程，槽函数都在发射信号的线程内执行。
    Qt::QueuedConnection 队列连接：当控制权回到接受者所依附线程的事件循环时，槽函数被调用。槽函数在接收者所依附线程执行。也就是说：这种方式既可以在线程内传递消息，也可以跨线程传递消息
    Qt::BlockingQueuedConnection 与Qt::QueuedConnection类似，但是会阻塞等到关联的slot都被执行。这里出现了阻塞这个词，说明它是专门用来多线程间传递消息的。
    */
    //kobe: why does ui died ??????????????????????
//    connect(m_mainTopWidget, SIGNAL(startOneKeyScan(QStringList)), m_dataWorker, SLOT(onStartOneKeyScan(QStringList))/*, Qt::QueuedConnection*/);//Qt::QueuedConnection
//    connect(m_mainTopWidget, SIGNAL(startOneKeyClean()), m_dataWorker, SLOT(onStartOneKeyClean())/*, Qt::BlockingQueuedConnection*/);
//    connect(m_dataWorker, SIGNAL(isScanning(QString)), m_mainTopWidget, SLOT(getScanResult(QString)), Qt::BlockingQueuedConnection);//Qt::BlockingQueuedConnection
//    connect(m_dataWorker, SIGNAL(finishScanWork(QString)), m_mainTopWidget, SLOT(finishScanResult(QString)), Qt::BlockingQueuedConnection);
//    connect(m_dataWorker, SIGNAL(tellScanResult(QString,QString)) ,m_mainTopWidget, SLOT(getScanAllResult(QString,QString)), Qt::BlockingQueuedConnection);
//    connect(m_dataWorker, SIGNAL(finishCleanWorkMain(QString)), m_mainTopWidget, SLOT(getCleanResult(QString)), Qt::BlockingQueuedConnection);
//    connect(m_dataWorker, SIGNAL(finishCleanWorkMainError(QString)), m_mainTopWidget, SLOT(finishCleanError(QString)), Qt::BlockingQueuedConnection);
//    connect(m_dataWorker, SIGNAL(quickCleanProcess(QString,QString)), m_mainTopWidget, SLOT(getCleaningMessage(QString,QString)), Qt::BlockingQueuedConnection);

//    connect(cleaner_action_widget, SIGNAL(showDetailData()),cleaner_widget, SLOT(displayDetailPage()));
//    connect(cleaner_action_widget, SIGNAL(showMainData()),cleaner_widget, SLOT(displayMainPage()));
    //connect(cleaner_action_widget, SIGNAL(sendCleanSignal()),cleaner_widget, SIGNAL(transCleanSignal()));

    connect(m_dataWorker, SIGNAL(tellCleanerDetailData(QStringList)), cleaner_widget, SIGNAL(tellCleanerDetailData(QStringList)), Qt::BlockingQueuedConnection);
    connect(m_dataWorker, SIGNAL(tellCleanerDetailStatus(QString)), cleaner_widget, SIGNAL(tellCleanerDetailStatus(QString)), Qt::BlockingQueuedConnection);

//    connect(m_dataWorker, SIGNAL(tellCleanerDetailStatus(QString)), cleaner_action_widget, SLOT(showCleanReciveStatus(QString)), Qt::BlockingQueuedConnection);
//    connect(m_dataWorker, SIGNAL(tellCleanerDetailError(QString)), cleaner_action_widget, SLOT(showCleanReciveError(QString)), Qt::BlockingQueuedConnection);

//    connect(m_dataWorker, SIGNAL(sendCleanOverSignal()), cleaner_widget, SLOT(displayMainPage()));
//    connect(m_dataWorker, SIGNAL(sendCleanOverSignal()), cleaner_action_widget, SLOT(displayOrgPage()));
//    connect(m_dataWorker, SIGNAL(sendCleanOverSignal()), cleaner_action_widget, SLOT(showCleanOverStatus()));
//    connect(m_dataWorker, SIGNAL(policykitCleanSignal(bool)), cleaner_action_widget, SLOT(receivePolicyKitSignal(bool)));
//    connect(m_dataWorker, SIGNAL(tellCleanerMainData(QStringList)), cleaner_action_widget, SLOT(showCleanerData(QStringList)), Qt::BlockingQueuedConnection);
//    connect(m_dataWorker, SIGNAL(tellCleanerMainStatus(QString, QString)), cleaner_action_widget, SLOT(showCleanerStatus(QString, QString)), Qt::BlockingQueuedConnection);
//    connect(m_dataWorker, SIGNAL(sendCleanErrorSignal(QString)), cleaner_action_widget, SLOT(showCleanerError(QString)), Qt::BlockingQueuedConnection);

    connect(cleaner_widget, SIGNAL(startScanSystem(QMap<QString,QVariant>)), m_dataWorker, SLOT(onStartScanSystem(QMap<QString,QVariant>)));
    connect(cleaner_widget, SIGNAL(startCleanSystem(QMap<QString,QVariant>)), m_dataWorker, SLOT(onStartCleanSystem(QMap<QString,QVariant>)));

    //add by tangguang -------------------------------------------------------------
    connect(cleaner_widget, SIGNAL(startOneKeyScan(QStringList)),m_dataWorker,SLOT(onStartOneKeyScan(QStringList)));
    connect(m_dataWorker, SIGNAL(isScanning(QString)), cleaner_widget, SIGNAL(isScanning(QString)), Qt::BlockingQueuedConnection);//Qt::BlockingQueuedConnection
    connect(m_dataWorker, SIGNAL(finishScanWork(QString)), cleaner_widget, SIGNAL(finishScanWork(QString)), Qt::BlockingQueuedConnection);
    connect(m_dataWorker, SIGNAL(tellScanResult(QString,QString)) ,cleaner_widget, SIGNAL(tellScanResult(QString,QString)), Qt::BlockingQueuedConnection);

    connect(cleaner_widget, SIGNAL(startOneKeyClean()), m_dataWorker, SLOT(onStartOneKeyClean())/*, Qt::BlockingQueuedConnection*/);
    connect(m_dataWorker, SIGNAL(finishCleanWorkMain(QString)), cleaner_widget, SIGNAL(finishCleanWorkMain(QString)), Qt::BlockingQueuedConnection);

    connect(m_dataWorker, SIGNAL(tellCleanerMainData(QStringList)), cleaner_widget, SIGNAL(tellCleanerMainData(QStringList)), Qt::BlockingQueuedConnection);
    connect(m_dataWorker, SIGNAL(tellCleanerMainStatus(QString, QString)), cleaner_widget, SIGNAL(tellCleanerMainStatus(QString, QString)), Qt::BlockingQueuedConnection);
    connect(m_dataWorker, SIGNAL(sendCleanErrorSignal(QString)), cleaner_widget, SIGNAL(sendCleanErrorSignal(QString)), Qt::BlockingQueuedConnection);
    connect(m_dataWorker, SIGNAL(policykitCleanSignal(bool)), cleaner_widget, SIGNAL(policykitCleanSignal(bool)));
    connect(m_dataWorker, SIGNAL(sendCleanOverSignal()), cleaner_widget, SIGNAL(sendCleanOverSignal()));
    //------------------------------------------------------------------------------

    connect(info_widget, SIGNAL(requestRefreshSystemInfo()), m_dataWorker, SLOT(onRequestRefreshSystemInfo()));
    connect(m_dataWorker, SIGNAL(sendSystemInfo(QMap<QString,QVariant>)), info_widget, SLOT(onSendSystemInfo(QMap<QString,QVariant>)));

    //desktop info
    connect(info_widget, SIGNAL(requestDesktopInfo()), m_dataWorker, SLOT(onRequestDesktopInfo()));
    connect(m_dataWorker, SIGNAL(sendDesktopInfo(QMap<QString,QVariant>)), info_widget, SLOT(onSendDesktopInfo(QMap<QString,QVariant>)));

    //cpu info
    connect(info_widget, SIGNAL(requestCpuInfo()), m_dataWorker, SLOT(onRequestCpuInfo()));
    connect(m_dataWorker, SIGNAL(sendCpuInfo(QMap<QString,QVariant>)), info_widget, SLOT(onSendCpuInfo(QMap<QString,QVariant>)));

    //memory info
    connect(info_widget, SIGNAL(requestMemoryInfo()), m_dataWorker, SLOT(onRequestMemoryInfo()));
    connect(m_dataWorker, SIGNAL(sendMemoryInfo(QMap<QString,QVariant>)), info_widget, SLOT(onSendMemoryInfo(QMap<QString,QVariant>)));

    //board info
    connect(info_widget, SIGNAL(requestBoardInfo()), m_dataWorker, SLOT(onRequestBoardInfo()));
    connect(m_dataWorker, SIGNAL(sendBoardInfo(QMap<QString,QVariant>)), info_widget, SLOT(onSendBoardInfo(QMap<QString,QVariant>)));

    //hd info
    connect(info_widget, SIGNAL(requestHDInfo()), m_dataWorker, SLOT(onRequestHDInfo()));
    connect(m_dataWorker, SIGNAL(sendHDInfo(QMap<QString,QVariant>)), info_widget, SLOT(onSendHDInfo(QMap<QString,QVariant>)));

    //nic info
    connect(info_widget, SIGNAL(requestNicInfo()), m_dataWorker, SLOT(onRequestNicInfo()));
    connect(m_dataWorker, SIGNAL(sendNicInfo(QMap<QString,QVariant>)), info_widget, SLOT(onSendNicInfo(QMap<QString,QVariant>)));

    //monitor info
    connect(info_widget, SIGNAL(requestMonitorInfo()), m_dataWorker, SLOT(onRequestMonitorInfo()));
    connect(m_dataWorker, SIGNAL(sendMonitorInfo(QMap<QString,QVariant>)), info_widget, SLOT(onSendMonitorInfo(QMap<QString,QVariant>)));

    //audio info
    connect(info_widget, SIGNAL(requestAudioInfo()), m_dataWorker, SLOT(onRequestAudioInfo()));
    connect(m_dataWorker, SIGNAL(sendAudioInfo(QMap<QString,QVariant>)), info_widget, SLOT(onSendAudioInfo(QMap<QString,QVariant>)));

    //battery info
    connect(info_widget, SIGNAL(requestBatteryInfo()), m_dataWorker, SLOT(onRequestBatteryInfo()));
    connect(m_dataWorker, SIGNAL(sendBatteryInfo(QMap<QString,QVariant>)), info_widget, SLOT(onSendBatteryInfo(QMap<QString,QVariant>)));

    //sensor info
    connect(info_widget, SIGNAL(requestSensorInfo()), m_dataWorker, SLOT(onRequestSensorInfo()));
    connect(m_dataWorker, SIGNAL(sendSensorInfo(QMap<QString,QVariant>)), info_widget, SLOT(onSendSensorInfo(QMap<QString,QVariant>)));

    //CDROM info
    connect(info_widget, SIGNAL(requestCDROMInfo()), m_dataWorker, SLOT(onRequestCDROMInfo()));
    connect(m_dataWorker, SIGNAL(sendCDROMInfoValue(QMap<QString,QVariant>)), info_widget, SLOT(onSendCDROMInfo(QMap<QString,QVariant>)));

    //input info
    connect(info_widget, SIGNAL(requestInputInfo()), m_dataWorker, SLOT(onRequestInputInfo()));

    //communication info
    connect(info_widget, SIGNAL(requestCommunicationInfo()), m_dataWorker, SLOT(onRequestCommunicationInfo()));

    connect(monitorwidget,SIGNAL(requestcpuTemperature()),m_dataWorker, SLOT(onRequestCpuTemperature()));
    connect(m_dataWorker, SIGNAL(sendCpuTemperaturedata(QMap<QString, QVariant>)),monitorwidget,SLOT(onsendTemperaturedata(QMap<QString, QVariant>)));

    // connect(monitorwidget,SIGNAL(requestcpurange()),m_dataWorker,SLOT(onRequesetCpuRange()));
    // connect(m_dataWorker,SIGNAL(sendCpuRangedata(QMap<QString,QVariant>)),monitorwidget,SLOT(sendcpurangedata(QMap<QString,QVariant>)));
    connect(monitorwidget,SIGNAL(setCpuGoverner(QString)),m_dataWorker,SLOT(onSetCurrentCpuMode(QString)));

    connect(monitorwidget,SIGNAL(RequestCPUFrequencyData()),m_dataWorker,SLOT(onRequestCpuAverageFrequency()));
    connect(m_dataWorker,SIGNAL(sendCpuAverageFrequency(QMap<QString,QVariant>)),monitorwidget,SIGNAL(SendCPUFrequencyData(QMap<QString,QVariant>)));

    connect(monitorwidget,SIGNAL(RequestFanInfoData()),m_dataWorker,SLOT(onRequestFanInfo()));
    connect(m_dataWorker,SIGNAL(sendFanInfoValue(QMap<QString,QVariant>)),monitorwidget,SIGNAL(SendFanInfoData(QMap<QString,QVariant>)));

    //bind setting notify signal
//    connect(m_dataWorker, SIGNAL(string_value_notify(QString,QString)), setting_widget, SIGNAL(string_value_notify(QString,QString)));
//    connect(m_dataWorker, SIGNAL(bool_value_notify(QString,bool)), setting_widget, SIGNAL(bool_value_notify(QString,bool)));
//    connect(m_dataWorker, SIGNAL(int_value_notify(QString,int)), setting_widget, SIGNAL(int_value_notify(QString,int)));
//    connect(m_dataWorker, SIGNAL(double_value_notify(QString,double)), setting_widget, SIGNAL(double_value_notify(QString,double)));

    //TODO:WTF??????
    /*connect(m_dataWorker, SIGNAL(string_value_notify(QString,QString)), setting_widget, SLOT(on_string_value_notify(QString,QString)));
    connect(m_dataWorker, SIGNAL(bool_value_notify(QString,bool)), setting_widget, SLOT(on_bool_value_notify(QString,bool)));
    connect(m_dataWorker, SIGNAL(int_value_notify(QString,int)), setting_widget, SLOT(on_int_value_notify(QString,int)));
    connect(m_dataWorker, SIGNAL(double_value_notify(QString,double)), setting_widget, SLOT(on_double_value_notify(QString,double)));
*/

    //theme
//    connect(setting_widget, SIGNAL(changeSystemTheme(QString)), m_dataWorker, SLOT(onChangeSystemTheme(QString)));
//    connect(setting_widget, SIGNAL(requestThemeData()), m_dataWorker, SLOT(onRequestThemeData()));
//    connect(m_dataWorker, SIGNAL(sendThemeList(QString,QStringList)), setting_widget, SIGNAL(sendThemeList(QString,QStringList)));

    //icon
//    connect(setting_widget, SIGNAL(requestIconData()), m_dataWorker, SLOT(onRequestIconData()));
//    connect(m_dataWorker, SIGNAL(sendIconThemeList(QString,QStringList)), setting_widget, SIGNAL(sendIconThemeList(QString,QStringList)));
//    connect(m_dataWorker, SIGNAL(sendDisplayIconValue(bool,bool,bool,bool,bool)), setting_widget, SIGNAL(sendDisplayIconValue(bool,bool,bool,bool,bool)));
//    connect(setting_widget, SIGNAL(resetIconTheme(QString)), m_dataWorker, SLOT(onResetIconTheme(QString)));
//    connect(setting_widget, SIGNAL(displayComputerIcon(bool)), m_dataWorker, SLOT(onDisplayComputerIcon(bool)));
//    connect(setting_widget, SIGNAL(displayFolderIcon(bool)), m_dataWorker, SLOT(onDisplayFolderIcon(bool)));
//    connect(setting_widget, SIGNAL(displayNetworkIcon(bool)), m_dataWorker, SLOT(onDisplayNetworkIcon(bool)));
//    connect(setting_widget, SIGNAL(displayRecycleBinIcon(bool)), m_dataWorker, SLOT(onDisplayRecycleBinIcon(bool)));
//    connect(setting_widget, SIGNAL(displayDiskIcon(bool)), m_dataWorker, SLOT(onDisplayDiskIcon(bool)));

    //mouse
//    connect(setting_widget, SIGNAL(requestMouseData()), m_dataWorker, SLOT(onRequestMouseData()));
//    connect(m_dataWorker, SIGNAL(sendMouseThemeAndCusorSize(QString,QStringList,int)), setting_widget, SIGNAL(sendMouseThemeAndCusorSize(QString,QStringList,int)));
//    connect(setting_widget, SIGNAL(resetMouseCursorTheme(QString)), m_dataWorker, SLOT(onResetMouseCursorTheme(QString)));
//    connect(setting_widget, SIGNAL(resetMouseCursorSize(int)), m_dataWorker, SLOT(onResetMouseCursorSize(int)));

    //voice
//    connect(setting_widget, SIGNAL(requestSoundData()), m_dataWorker, SLOT(onRequestSoundData()));
//    connect(m_dataWorker, SIGNAL(sendSoundList(QString,QStringList)), setting_widget, SIGNAL(sendSoundList(QString,QStringList)));
//    connect(m_dataWorker, SIGNAL(sendEnableSoundValue(bool,bool,bool)), setting_widget, SIGNAL(sendEnableSoundValue(bool,bool,bool)));
//    connect(setting_widget, SIGNAL(resetVoiceTheme(QString)), m_dataWorker, SLOT(onResetVoiceTheme(QString)));
//    connect(setting_widget, SIGNAL(resetLoginTipVoice(bool)), m_dataWorker, SLOT(onResetLoginTipVoice(bool)));
//    connect(setting_widget, SIGNAL(resetEventVoice(bool)), m_dataWorker, SLOT(onResetEventVoice(bool)));
//    connect(setting_widget, SIGNAL(resetInputFeedbackVoice(bool)), m_dataWorker, SLOT(onResetInputFeedbackVoice(bool)));

    //panel
//    connect(setting_widget, SIGNAL(requestMateOrUnityPanelData(bool)), m_dataWorker, SLOT(onRequestMateOrUnityPanelData(bool)));
//    connect(m_dataWorker, SIGNAL(sendMatePanelValue(bool,bool,bool,bool)), setting_widget, SIGNAL(sendMatePanelValue(bool,bool,bool,bool)));
//    connect(m_dataWorker, SIGNAL(sendUnityBlurAndTransparencyValue(int,double)), setting_widget, SIGNAL(sendUnityBlurAndTransparencyValue(int,double)));
//    connect(m_dataWorker, SIGNAL(sendUnityTimeValue(QString,QStringList,bool,bool,bool)), setting_widget, SIGNAL(sendUnityTimeValue(QString,QStringList,bool,bool,bool)));
//    connect(m_dataWorker, SIGNAL(sendUnityPanelPowerValue(QString,QStringList,bool,bool)), setting_widget, SIGNAL(sendUnityPanelPowerValue(QString,QStringList,bool,bool)));
//    connect(setting_widget, SIGNAL(resetPanelTransparencyValue(double)), m_dataWorker, SLOT(onResetPanelTransparencyValue(double)));
//    connect(setting_widget, SIGNAL(resetDateFormat(QString)), m_dataWorker, SLOT(onResetDateFormat(QString)));
//    connect(setting_widget, SIGNAL(resetShowBatteryIcon(QString)), m_dataWorker, SLOT(onResetShowBatteryIcon(QString)));
//    connect(setting_widget, SIGNAL(resetDashBlurExperimental(int)), m_dataWorker, SLOT(onResetDashBlurExperimental(int)));
//    connect(setting_widget, SIGNAL(resetDisplaySeconds(bool)), m_dataWorker, SLOT(onResetDisplaySeconds(bool)));
//    connect(setting_widget, SIGNAL(resetDisplayWeek(bool)), m_dataWorker, SLOT(onResetDisplayWeek(bool)));
//    connect(setting_widget, SIGNAL(resetDisplayDate(bool)), m_dataWorker, SLOT(onResetDisplayDate(bool)));
//    connect(setting_widget, SIGNAL(resetDisplayBatteryPercentage(bool)), m_dataWorker, SLOT(onResetDisplayBatteryPercentage(bool)));
//    connect(setting_widget, SIGNAL(resetDisplayBatteryTime(bool)), m_dataWorker, SLOT(onResetDisplayBatteryTime(bool)));
//    connect(setting_widget, SIGNAL(resetShowApplications(bool)), m_dataWorker, SLOT(onResetShowApplications(bool)));
//    connect(setting_widget, SIGNAL(resetShowDesktop(bool)), m_dataWorker, SLOT(onResetShowDesktop(bool)));
//    connect(setting_widget, SIGNAL(resetShowIcon(bool)), m_dataWorker, SLOT(onResetShowIcon(bool)));
//    connect(setting_widget, SIGNAL(resetShowPlaces(bool)), m_dataWorker, SLOT(onResetShowPlaces(bool)));

    //launcher menu
//    connect(setting_widget, SIGNAL(requestMateOrUnityMenuData(bool)), m_dataWorker, SLOT(onRequestMateOrUnityMenuData(bool)));
//    connect(m_dataWorker, SIGNAL(sendMatePanelIconValue(int,int,bool,bool)), setting_widget, SIGNAL(sendMatePanelIconValue(int,int,bool,bool)));
//    connect(m_dataWorker, SIGNAL(sendUnityIconValue(int,bool,bool,double,int,QStringList)), setting_widget, SIGNAL(sendUnityIconValue(int,bool,bool,double,int,QStringList)));
//    connect(m_dataWorker, SIGNAL(sendUnityLauncherPosition(QString,QStringList)), setting_widget, SIGNAL(sendUnityLauncherPosition(QString,QStringList)));

//    connect(setting_widget, SIGNAL(resetIconSizeValue(int)), m_dataWorker, SLOT(onResetIconSizeValue(int)));
//    connect(setting_widget, SIGNAL(resetTransparencyValue(int)), m_dataWorker, SLOT(onResetTransparencyValue(int)));
//    connect(setting_widget, SIGNAL(resetIconColouring(int)), m_dataWorker, SLOT(onResetIconColouring(int)));
//    connect(setting_widget, SIGNAL(resetAutoHide(bool)), m_dataWorker, SLOT(onResetAutoHide(bool)));
//    connect(setting_widget, SIGNAL(resetDisplayDesktopIcon(bool)), m_dataWorker, SLOT(onResetDisplayDesktopIcon(bool)));
//    connect(setting_widget, SIGNAL(resetTopIconSizeValue(int)), m_dataWorker, SLOT(onResetTopIconSizeValue(int)));
//    connect(setting_widget, SIGNAL(resetBottomIconSizeValue(int)), m_dataWorker, SLOT(onResetBottomIconSizeValue(int)));
//    connect(setting_widget, SIGNAL(resetTopAutoHide(bool)), m_dataWorker, SLOT(onResetTopAutoHide(bool)));
//    connect(setting_widget, SIGNAL(resetBottomAutoHide(bool)), m_dataWorker, SLOT(onResetBottomAutoHide(bool)));
//    connect(setting_widget, SIGNAL(resetLauncherPosition(QString)), m_dataWorker, SLOT(onResetLauncherPosition(QString)));

    //window
//    connect(setting_widget, SIGNAL(requesetWindowButtonAlign()), m_dataWorker, SLOT(onRequesetWindowButtonAlign()));
//    connect(setting_widget, SIGNAL(requesetMenusHaveIcons()), m_dataWorker, SLOT(onRequesetMenusHaveIcons()));
//    connect(setting_widget, SIGNAL(requesetWindowTitileTags()), m_dataWorker, SLOT(onRequesetWindowTitileTags()));

//    connect(m_dataWorker, SIGNAL(sendWindowButtonAlign(QString)), setting_widget, SIGNAL(sendWindowButtonAlign(QString)));
//    connect(m_dataWorker, SIGNAL(sendMenusHaveIcons(bool)), setting_widget, SIGNAL(sendMenusHaveIcons(bool)));
//    connect(m_dataWorker, SIGNAL(sendWindowTitileTags(QString,QStringList,QStringList,QString,QString,QString)), setting_widget, SIGNAL(sendWindowTitileTags(QString,QStringList,QStringList,QString,QString,QString)));

//    connect(setting_widget, SIGNAL(resetMenusHaveIcon(bool)), m_dataWorker, SLOT(onResetMenusHaveIcon(bool)));
//    connect(setting_widget, SIGNAL(resetTitlebarWheel(QString)), m_dataWorker, SLOT(onResetTitlebarWheel(QString)));
//    connect(setting_widget, SIGNAL(resetTitlebarDoubleClick(QString)), m_dataWorker, SLOT(onResetTitlebarDoubleClick(QString)));
//    connect(setting_widget, SIGNAL(resetMouseMiddleClick(QString)), m_dataWorker, SLOT(onResetMouseMiddleClick(QString)));
//    connect(setting_widget, SIGNAL(resetMouseRightClick(QString)), m_dataWorker, SLOT(onResetMouseRightClick(QString)));
//    connect(setting_widget, SIGNAL(resetWindowButtonLeftOrRightAlign(bool)), m_dataWorker, SLOT(onResetWindowButtonLeftOrRightAlign(bool)));

    //font
//    connect(setting_widget, SIGNAL(requestFontData()), m_dataWorker, SLOT(onRequestFontData()));
//    connect(m_dataWorker, SIGNAL(sendFontValue(QString)), setting_widget, SIGNAL(sendFontValue(QString)));
//    connect(m_dataWorker, SIGNAL(sendDesktopFontValue(QString)), setting_widget, SIGNAL(sendDesktopFontValue(QString)));
//    connect(m_dataWorker, SIGNAL(sendMonospaceFontValue(QString)), setting_widget, SIGNAL(sendMonospaceFontValue(QString)));
//    connect(m_dataWorker, SIGNAL(sendDocumentFontValue(QString)), setting_widget, SIGNAL(sendDocumentFontValue(QString)));
//    connect(m_dataWorker, SIGNAL(sendTitlebarFontValue(QString)), setting_widget, SIGNAL(sendTitlebarFontValue(QString)));
//    connect(m_dataWorker, SIGNAL(sendFontSmoothAndAntialiasingValue(double,QString,QStringList,QString,QStringList)), setting_widget, SIGNAL(sendFontSmoothAndAntialiasingValue(double,QString,QStringList,QString,QStringList)));

//    connect(setting_widget, SIGNAL(setDefaultFontByName(QString)), m_dataWorker, SLOT(onSetDefaultFontByName(QString)));
//    connect(setting_widget, SIGNAL(setDesktopFontByName(QString)), m_dataWorker, SLOT(onSetDesktopFontByName(QString)));
//    connect(setting_widget, SIGNAL(setMonospaceFontByName(QString)), m_dataWorker, SLOT(onSetMonospaceFontByName(QString)));
//    connect(setting_widget, SIGNAL(setDocumentFontByName(QString)), m_dataWorker, SLOT(onSetDocumentFontByName(QString)));
//    connect(setting_widget, SIGNAL(setTitlebarFontByName(QString)), m_dataWorker, SLOT(onSetTitlebarFontByName(QString)));
//    connect(setting_widget, SIGNAL(resetFontZoomScalingValue(double)), m_dataWorker, SLOT(onResetFontZoomScalingValue(double)));
//    connect(setting_widget, SIGNAL(resetFontHinting(QString)), m_dataWorker, SLOT(onResetFontHinting(QString)));
//    connect(setting_widget, SIGNAL(resetFontAntialiasing(QString)), m_dataWorker, SLOT(onResetFontAntialiasing(QString)));
//    connect(setting_widget, SIGNAL(restoreDefaultFont(bool)), m_dataWorker, SLOT(onRestoreDefaultFont(bool)));
//    connect(setting_widget, SIGNAL(restoreDesktopDefaultFont(bool)), m_dataWorker, SLOT(onRestoreDesktopDefaultFont(bool)));
//    connect(setting_widget, SIGNAL(restoreMonospaceDefaultFont(bool)), m_dataWorker, SLOT(onRestoreMonospaceDefaultFont(bool)));
//    connect(setting_widget, SIGNAL(restoreDocumentDefaultFont(bool)), m_dataWorker, SLOT(onRestoreDocumentDefaultFont(bool)));
//    connect(setting_widget, SIGNAL(restoreTitlebarDefaultFont(bool)), m_dataWorker, SLOT(onRestoreTitlebarDefaultFont(bool)));

    //touchpad
//    connect(setting_widget, SIGNAL(requestMateOrUnityTouchpadData(bool)), m_dataWorker, SLOT(onRequestMateOrUnityTouchpadData(bool)));
//    connect(m_dataWorker, SIGNAL(sendTouchPadValue(bool,bool,QString,int,QString)), setting_widget, SIGNAL(sendTouchPadValue(bool,bool,QString,int,QString)));
//    connect(setting_widget, SIGNAL(resetTouchpad(bool)), m_dataWorker, SLOT(onResetTouchpad(bool)));
//    connect(setting_widget, SIGNAL(resetHorizontalScrolling(bool)), m_dataWorker, SLOT(onResetHorizontalScrolling(bool)));
//    connect(setting_widget, SIGNAL(setScrollbarOverlayOrLegacyMode(bool)), m_dataWorker, SLOT(onSetScrollbarOverlayOrLegacyMode(bool)));
//    connect(setting_widget, SIGNAL(setMateTouchscrollingMode(int)), m_dataWorker, SLOT(onSetMateTouchscrollingMode(int)));
//    connect(setting_widget, SIGNAL(setUnityTouchscrollingMode(int)), m_dataWorker, SLOT(onSetUnityTouchscrollingMode(int)));

    //ac and battery
//    connect(setting_widget, SIGNAL(requestPowerAndBatteryData()), m_dataWorker, SLOT(onRequestPowerAndBatteryData()));
//    connect(m_dataWorker, SIGNAL(sendIdleAndGammaData(double,QStringList,int,QString,QString,QString,QStringList)), setting_widget, SIGNAL(sendIdleAndGammaData(double,QStringList,int,QString,QString,QString,QStringList)));
//    connect(m_dataWorker, SIGNAL(sendLockAndSleepData(bool,QString,QStringList,QString,QString,QString,QString,QStringList,QString)), setting_widget, SIGNAL(sendLockAndSleepData(bool,QString,QStringList,QString,QString,QString,QString,QStringList,QString)));

//    connect(setting_widget, SIGNAL(resetScreenGammaValue(double)), m_dataWorker, SLOT(onResetScreenGammaValue(double)));
//    connect(setting_widget, SIGNAL(resetBrightnessValue(int)), m_dataWorker, SLOT(onResetBrightnessValue(int)));
//    connect(setting_widget, SIGNAL(resetIdleDelay(int,int)), m_dataWorker, SLOT(onResetIdleDelay(int,int)));
//    connect(setting_widget, SIGNAL(resetLockEnabled(bool)), m_dataWorker, SLOT(onResetLockEnabled(bool)));
//    connect(setting_widget, SIGNAL(resetLockDelay(int,int)), m_dataWorker, SLOT(onResetLockDelay(int,int)));
//    connect(setting_widget, SIGNAL(setCurrentCriticalLow(QString)), m_dataWorker, SLOT(onSetCurrentCriticalLow(QString)));
//    connect(setting_widget, SIGNAL(setCurrentLidBattery(QString)), m_dataWorker, SLOT(onSetCurrentLidBattery(QString)));
//    connect(setting_widget, SIGNAL(setCurrentLidAC(QString)), m_dataWorker, SLOT(onSetCurrentLidAC(QString)));
//    connect(setting_widget, SIGNAL(resetSleepTimeoutBattery(int,int)), m_dataWorker, SLOT(onResetSleepTimeoutBattery(int,int)));
//    connect(setting_widget, SIGNAL(resetSleepTimeoutAC(int,int)), m_dataWorker, SLOT(onResetSleepTimeoutAC(int,int)));
//    connect(setting_widget, SIGNAL(resetSleepTimeoutDisplayBattery(int,int)), m_dataWorker, SLOT(onResetSleepTimeoutDisplayBattery(int,int)));
//    connect(setting_widget, SIGNAL(resetSleepTimeoutDisplayAC(int,int)), m_dataWorker, SLOT(onResetSleepTimeoutDisplayAC(int,int)));
//    connect(setting_widget, SIGNAL(setCurrentCpuMode(QString)), m_dataWorker, SLOT(onSetCurrentCpuMode(QString)));

    //file manager
//    connect(setting_widget, SIGNAL(requestFileManagerData()), m_dataWorker, SLOT(onRequestFileManagerData()));
//    connect(m_dataWorker, SIGNAL(sendFileManagerData(bool,bool,bool,bool,int,int,int)), setting_widget, SIGNAL(sendFileManagerData(bool,bool,bool,bool,int,int,int)));

//    connect(setting_widget, SIGNAL(resetLocationReplacePathbar(bool)), m_dataWorker, SLOT(onResetLocationReplacePathbar(bool)));
//    connect(setting_widget, SIGNAL(resetAutoMountMedia(bool)), m_dataWorker, SLOT(onResetAutoMountMedia(bool)));
//    connect(setting_widget, SIGNAL(resetAutoOpenFolder(bool)), m_dataWorker, SLOT(onResetAutoOpenFolder(bool)));
//    connect(setting_widget, SIGNAL(resetPromptAutorunPrograms(bool)), m_dataWorker, SLOT(onResetPromptAutorunPrograms(bool)));
//    connect(setting_widget, SIGNAL(resetThumbnailIconSize(int)), m_dataWorker, SLOT(onResetThumbnailIconSize(int)));
//    connect(setting_widget, SIGNAL(resetThumbnailCacheTime(int)), m_dataWorker, SLOT(onResetThumbnailCacheTime(int)));
//    connect(setting_widget, SIGNAL(resetThumbnailCacheSize(int)), m_dataWorker, SLOT(onResetThumbnailCacheSize(int)));

    info_widget->initInfoUI(this->battery, this->sensor);
//    list_widget->setBatteryAndSensor(this->battery,this->sensor,this->info);
//    list_widget->InitInfowidgetUI();

    m_dataWorker->onRequestPartInfoAgain();
//    monitorwidget->InitUI();

    monitorwidget->set_governer_list(m_cpulist,m_cpufreqlist);
    monitorwidget->set_cur_governer(m_currentCpuMode);
    monitorwidget->set_temperature(this->temperature);
    monitorwidget->set_fan(this->fan);
    monitorwidget->set_cpuFm(this->cpufm);
    monitorwidget->set_cpuFreqRange(m_dataWorker->cpuFreqRange());
    monitorwidget->InitUI();

    this->startUDevHotPlugin();
    this->show();
    this->raise();
}

void MainWindow::moveCenter()
{
    QPoint pos = QCursor::pos();
    QRect primaryGeometry;
    for (QScreen *screen : qApp->screens()) {
        if (screen->geometry().contains(pos)) {
            primaryGeometry = screen->geometry();
        }
    }

    if (primaryGeometry.isEmpty()) {
        primaryGeometry = qApp->primaryScreen()->geometry();
    }

    this->move(primaryGeometry.x() + (primaryGeometry.width() - this->width())/2,
               primaryGeometry.y() + (primaryGeometry.height() - this->height())/2);
    // show after initialization
    // this->show();
    // this->raise();
}

void MainWindow::onPluginModuleError(const QString &info)
{
    toolKits->alertMSG(this->geometry().topLeft().x(), this->geometry().topLeft().y(), info);
}

QString MainWindow::accessOSName()
{

    QString osname = "";
    QString tmp = "";

    QFile osfile("/etc/os-release");
    if(osfile.exists()) {
        if(!osfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Can't open os-release!" << endl;
        }
        else {
            while(!osfile.atEnd()) {
                QByteArray line = osfile.readLine();
                QString str(line);
                if (str.startsWith("NAME")) {
                    tmp = str;
                    break;
                }
            }
            osfile.close();
        }
    }
    if(tmp.length() > 0 && tmp.contains("=")) {
        osname = QString(tmp.split("=").at(1)).replace("\"", "").replace("\n","").trimmed();
    }
    if(osname.length() > 0) {
        return osname;
    }

    osname = "";
    tmp = "";
    QFile ukfile("/etc/ubuntukylin-release");
    if(ukfile.exists()) {
        if(!ukfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Can't open ubuntukylin-release!" << endl;
        }
        else {
            while(!ukfile.atEnd()) {
                QByteArray line = ukfile.readLine();
                QString str(line);
                if (str.startsWith("DISTRIB_DESCRIPTION")) {
                    tmp = str;
                    break;
                }
            }
            ukfile.close();
        }
    }
    if(tmp.length() > 0 && tmp.contains("=")) {
        osname = QString(tmp.split("=").at(1)).replace("\"", "").replace("\n","").trimmed();
    }
    if(osname.length() > 0) {
        return osname;
    }

    osname = "";
    tmp = "";
    QFile lsbfile("/etc/lsb-release");
    if(lsbfile.exists()) {
        if(!lsbfile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            qDebug() << "Can't open lsb-release!" << endl;
        }
        else {
            while(!lsbfile.atEnd()) {
                QByteArray line = lsbfile.readLine();
                QString str(line);
                if (str.startsWith("DISTRIB_DESCRIPTION")) {
                    tmp = str;
                    break;
                }
            }
            lsbfile.close();
        }
    }
    if(tmp.length() > 0 && tmp.contains("=")) {
        osname = QString(tmp.split("=").at(1)).replace("\"", "").replace("\n","").trimmed();
    }
    if(osname.length() > 0) {
        return osname;
    }

    return "Ubuntu Kylin";
}

bool MainWindow::deleteFile(QString filename)
{
    return m_dataWorker->deleteAppointedFile(filename);
}

bool MainWindow::CopyFile(QString filename)
{
    return m_dataWorker->copyAppointedFile(filename);
}

QStringList MainWindow::filterSkin()
{
    QStringList skinlist;
    QString path = "/var/lib/kylin-assistant-daemon/default/";
    QString path2 = "/var/lib/kylin-assistant-daemon/custom/";
    QDir picdir(path);
    picdir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    picdir.setSorting(QDir::Size | QDir::Reversed);
    QDir picdir2(path2);
    picdir2.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    picdir2.setSorting(QDir::Size | QDir::Reversed);
    QStringList filters;
    filters << "*.jpg" << "*.png";
    picdir.setNameFilters(filters);
    picdir2.setNameFilters(filters);
    QFileInfoList list = picdir.entryInfoList();
    QFileInfoList list2 = picdir2.entryInfoList();
    if(list.size() < 1 && list2.size() < 1) {
        skinlist << ":/background/res/skin/1.png" << ":/background/res/skin/2.png" << ":/background/res/skin/3.png" << ":/background/res/skin/4.png";
//        return ":/background/res/skin/1.png";
    }
    else if(list.size() > 0 && list2.size() > 0) {
        for (int j = 0; j < list.size(); ++j) {
            QFileInfo fileInfo = list.at(j);
            skinlist << path + fileInfo.fileName();
        }
        for (int k = 0; k < list2.size(); ++k) {
            QFileInfo fileInfo = list2.at(k);
            skinlist << path2 + fileInfo.fileName();
        }
        skinlist << ":/background/res/skin/1.png" << ":/background/res/skin/2.png" << ":/background/res/skin/3.png" << ":/background/res/skin/4.png";
    }
    else {
        if(list.size() > 0) {
            for (int j = 0; j < list.size(); ++j) {
                QFileInfo fileInfo = list.at(j);
                skinlist << path + fileInfo.fileName();
            }
            skinlist << ":/background/res/skin/1.png" << ":/background/res/skin/2.png" << ":/background/res/skin/3.png" << ":/background/res/skin/4.png";
        }
        else if(list2.size() > 0) {
            for (int m = 0; m < list2.size(); ++m) {
                QFileInfo fileInfo = list2.at(m);
                skinlist << path2 + fileInfo.fileName();
            }
            skinlist << ":/background/res/skin/1.png" << ":/background/res/skin/2.png" << ":/background/res/skin/3.png" << ":/background/res/skin/4.png";
        }
//        QFileInfo fileInfo = list.at(0);
//        return path + fileInfo.fileName();
    }
    return skinlist;
}

void MainWindow::setTranslator(QTranslator* translator)
{
//    this->translator = translator;
}

void MainWindow::changeLanguage(LANGUAGE language)
{
    if(current_language == language)
    {
        return;
    }
    current_language = language;

    switch(language)
    {
    case YOUKER_EN:
        translator->load(QString(":/qmfile/res/qm/kylin-assistant_es.qm"));
        break;

    case YOUKER_ZH_CN:
        translator->load(QString(":/qmfile/res/qm/kylin-assistant_zh_CN.qm"));
        break;

    case YOUKER_ES:
        translator->load(QString(":/qmfile/res/qm/kylin-assistant_es.qm"));
        break;

    default:
        translator->load(QString(":/qmfile/res/qm/kylin-assistant_zh_CN.qm"));
    }

//	title_widget->translateLanguage();
//	kill_mummy_widget->translateLanguage();
//	main_menu->translateActions();
//	character_widget->translateLanguage();
//	login_dialog->translateLanguage();
//	register_widget->translateLanguage();
//	character_widget->translateLanguage();
//	about_us_dialog->translateLanguage();
//	setting_dialog->translateLanguage();
//	skin_widget->translateLanguage();
//	system_tray->translateLanguage();
}

void MainWindow::startDbusDaemon()
{
//    qDebug() << "mainwindow thread id=" << QThread::currentThreadId();
    m_dataWorker = new DataWorker(this->desktop);


    QThread *w_thread = ThreadPool::Instance()->createNewThread();
    m_dataWorker->moveToThread(w_thread);
//    connect(w_thread, SIGNAL(started()), m_dataWorker, SLOT(doWork()));
//    connect(m_dataWorker, SIGNAL(dataLoadFinished()), this, SLOT(onInitDataFinished()));
//    connect(w_thread, &QThread::finished, w_thread, &QThread::deleteLater, Qt::QueuedConnection);
    connect(w_thread, &QThread::started, m_dataWorker, &DataWorker::doWork/*, Qt::QueuedConnection*/);
    connect(m_dataWorker, &DataWorker::dataLoadFinished, this, &MainWindow::onInitDataFinished/*, Qt::BlockingQueuedConnection*/);
    connect(w_thread, &QThread::finished, this, [=] {
        w_thread->deleteLater();
        qDebug() << "DataWorker thread finished......";
    });
    w_thread->start();
}

void MainWindow::startUDevHotPlugin()
{
    m_udevHotPlugin = new UDevHotPlugin(this);
    connect(m_udevHotPlugin, &UDevHotPlugin::sendUdevAddNotify, info_widget, &InfoWidget::onUDevHotPluginAdd);
    connect(m_udevHotPlugin, &UDevHotPlugin::sendUdevRemoveNotify, info_widget, &InfoWidget::onUDevHotPluginRemove);
    m_udevHotPlugin->start();
    qDebug()<<"UdevHotPlugin started!!";
}

void MainWindow::stopUDevHotPlugin()
{
    if (m_udevHotPlugin) {
        m_udevHotPlugin->stopDevHotPlugin();
        m_udevHotPlugin->quit();
        m_udevHotPlugin->wait();
        qDebug()<<"UdevHotPlugin stoped!!";
    }
}

void MainWindow::handleMessage(const QString &msg)
{
    qDebug() << Q_FUNC_INFO;
    this->showNormal();
}

int MainWindow::getCurrentBackgroundIndex()
{
    int index = 1;
    /*mSettings->beginGroup("Background");
    QString cur_skin_path = mSettings->value("Path").toString();
    if(!cur_skin_path.isEmpty()) {
        int  start_pos = cur_skin_path.lastIndexOf("/") + 1;
        int end_pos = cur_skin_path.length();
        index = cur_skin_path.mid(start_pos, end_pos-start_pos).replace(".png", "").toInt();
    }
    mSettings->endGroup();
    mSettings->sync();*/
    return index;
}

QString MainWindow::getCurrentBackgroundName()
{
    QString cur_skin_path;
    /*mSettings->beginGroup("Background");
    cur_skin_path = mSettings->value("Path").toString();
    if(!cur_skin_path.isEmpty()) {
        int  start_pos = cur_skin_path.lastIndexOf("/") + 1;
        int end_pos = cur_skin_path.length();
        cur_skin_path = cur_skin_path.mid(start_pos, end_pos-start_pos);
    }
    mSettings->endGroup();
    mSettings->sync();*/
    return cur_skin_path;
}

QString MainWindow::getCurrentBackgroundAbsName()
{
    QString cur_skin_path;
    /*mSettings->beginGroup("Background");
    cur_skin_path = mSettings->value("Path").toString();
    mSettings->endGroup();
    mSettings->sync();*/
    return cur_skin_path;
}

void MainWindow::restoreSkin()
{
  /*if (main_skin_pixmap.isDetached())
  {
    main_skin_pixmap.detach();
  }
  main_skin_pixmap.load(last_skin_path);
  QPalette palette_back;
  palette_back.setBrush(QPalette::Background, main_skin_pixmap);*/
}


void MainWindow::changeSkin(QString pciture)
{
    /*if (main_skin_pixmap.isDetached())
    {
        main_skin_pixmap.detach();
    }
    last_skin_path = pciture;
    main_skin_pixmap.load(pciture);
    QPalette palette;
    palette.setBrush(QPalette::Background, main_skin_pixmap);

    mSettings->beginGroup("Background");
    mSettings->setValue("Path", pciture);
    mSettings->endGroup();
    mSettings->sync();

//    if(auto_start != NULL) {
//        auto_start->resetTitleSkin(last_skin_path);
//    }
//    if(camera_manager != NULL) {
//        camera_manager->resetTitleSkin(last_skin_path);
//    }
    if(setting_widget != NULL) {
        setting_widget->resetSkin(last_skin_path);
    }
    if(cleaner_widget != NULL) {
        cleaner_widget->resetSkin(last_skin_path);
    }
    if(aboutDlg != NULL) {
        aboutDlg->resetTitleSkin(last_skin_path);
    }*/
}

void MainWindow::reViewThePointSkin(QString pciture)
{
    if (review_skin_pixmap.isDetached())
    {
        review_skin_pixmap.detach();
    }
    review_skin_pixmap.load(pciture);
    QPalette palette_back;
    palette_back.setBrush(QPalette::Background, review_skin_pixmap);
}

void MainWindow::reViewTheOrgSkin()
{
    if (review_skin_pixmap.isDetached())
    {
        review_skin_pixmap.detach();
    }
    review_skin_pixmap.load(last_skin_path);
    QPalette palette_back;
    palette_back.setBrush(QPalette::Background, review_skin_pixmap);
}

void MainWindow::showMainMenu() {
//    if (this->arch == "aarch64" || this->osName == "Kylin" || this->osName == "YHKylin")
//    {
        QPoint p = rect().topRight();
        p.setX(p.x() - 100);
        p.setY(p.y() + 28);
        main_menu->exec(this->mapToGlobal(p));
//    }
//    else
//    {
//        QPoint p = rect().topLeft();
//        p.setX(p.x() + 107);//104
//        p.setY(p.y() + 22);
//        main_menu->exec(this->mapToGlobal(p));
//    }

//    //向上弹出menu
//    QPoint pos;
//    pos.setX(0);
//    pos.setY(-main_menu->sizeHint().height());
//    main_menu->exec(title_widget->mapToGlobal(pos));
}

void MainWindow::closeYoukerAssistant() {
//    qApp->exit();
    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
    animation->setDuration(500);
    animation->setStartValue(1);
    animation->setEndValue(0);
    animation->start();
    connect(animation, SIGNAL(finished()), this, SLOT(close()));
}

void MainWindow::closeEvent(QCloseEvent *)
{
//    QApplication::quit();
    qApp->exit();
}

void MainWindow::setCurrentPageIndex(QString index)
{
//    qDebug() << "==========index " << index;

    if (index == "Cleanup" && status != "Cleanup") {
        m_bottomStack->setCurrentWidget(cleaner_widget);
        m_bottomStack->setFixedSize(cleaner_widget->size());
        status = "Cleanup";
    }
    else if (index == "Optimize" && status != "Optimize") {
        m_bottomStack->setCurrentWidget(optimized_widget);
        m_bottomStack->setFixedSize(optimized_widget->size());
        status = "Monitoring";
    }
    else if (index == "Monitor" && status != "Monitor") {
        m_bottomStack->setCurrentWidget(monitorwidget);
        m_bottomStack->setFixedSize(monitorwidget->size());
        if(cpufm)
            monitorwidget->RefreshCPUFMCheckStatus();
        status = "Monitor";
    }
    else if (index == "Drive" && status != "Drive") {
        m_bottomStack->setCurrentWidget(drive_widget);
        m_bottomStack->setFixedSize(drive_widget->size());
        status = "Drive";
    }
    else if (index == "Sysinfo" && status != "Sysinfo") {
        m_bottomStack->setCurrentWidget(info_widget);
        m_bottomStack->setFixedSize(info_widget->size());
        status = "Sysinfo";
    }
    else if (index == "Toolkits" && status != "Toolkits") {
        m_bottomStack->setCurrentWidget(box_widget);
        m_bottomStack->setFixedSize(box_widget->size());
        status = "Toolkits";
    }
}

void MainWindow::openSkinCenter()
{
    /*if(skin_center == NULL) {
        skin_center = new SkinCenter(0, last_skin_path, this->arch, this->osName);//20161228
        skin_center->setParentWindow(this);
        skin_center->initSysBackgroundList();
        int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (442  / 2);
        int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (340  / 2);
        skin_center->move(w_x, w_y);
        skin_center->show();
        skin_center->raise();
    }
    else {
        int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (442  / 2);
        int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (326  / 2);
        skin_center->move(w_x, w_y);
        skin_center->show();
        skin_center->raise();
    }*/
}

void MainWindow::openUpgradePage(/*QStringList version_list*/)
{
    /*int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (334  / 2);
    int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (470  / 2);
    if(upgrade_dialog == NULL)
    {
//        upgrade_dialog = new UpgradeDialog(0, version_list.at(2), last_skin_path);
        upgrade_dialog = new UpgradeDialog(0, last_skin_path, this->arch, this->osName);//20161228
        upgrade_dialog->setSystemDbusProxy(systeminterface);
//        upgrade_dialog->setSessionDbusProxy(sessioninterface);
        connect(home_page, SIGNAL(sendOpenUpgrade()), this, SLOT(openUpgradePageAgain()));
        connect(upgrade_dialog, SIGNAL(showBackendBtnSignal(bool)), home_page, SLOT(displayBackedBtn(bool)));
        connect(upgrade_dialog,SIGNAL(close_signal()), this, SLOT(closeYoukerAssistant()));
        connect(systeminterface,SIGNAL(get_fetch_signal(QString, QStringList)),upgrade_dialog,SLOT(receiveFetchSignal(QString, QStringList)));
        connect(systeminterface,SIGNAL(get_apt_signal(QString, QStringList)),upgrade_dialog,SLOT(receiveAptSignal(QString, QStringList)));
//        connect(sessioninterface,SIGNAL(receive_source_list_signal(bool)),upgrade_dialog,SLOT(receiveCheckResultSignal(bool)));
        upgrade_dialog->move(w_x, w_y);
        upgrade_dialog->show();
        upgrade_dialog->raise();
        upgrade_dialog->startAccessData();
    }
    else {
//        upgrade_dialog->resetVersionNumber(version_list);
        upgrade_dialog->move(w_x, w_y);
        upgrade_dialog->show();
        upgrade_dialog->raise();
        home_page->hideBackedBtn();
//        upgrade_dialog->startAccessData();
    }*/
}

//void MainWindow::openUpgradePageAgain()
//{
//    int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (334  / 2);
//    int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (470  / 2);
//    upgrade_dialog->move(w_x, w_y);
//    upgrade_dialog->show();
//    upgrade_dialog->raise();
//}

void MainWindow::newFeatures()
{

}

void MainWindow::setupConfigure()
{

}

void MainWindow::createAboutDialog()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);
//    aboutDlg = new AboutDialog(0, last_skin_path, this->arch, this->osName);
//    aboutDlg->setModal(false);

    aboutDlg = new AboutWidget();
    aboutDlg->setAppIcon("kylin-assistant");
    aboutDlg->setAppName(tr("ToolKit"));
    aboutDlg->setAppVersion(qApp->applicationVersion());
    aboutDlg->setAppDescription(tr("<p>ToolKit is a powerful system supporting software which is developed by Kylin team. Mainly for the naive user, it can help users manage the system. At present, It provides system junk scanning and cleaning, viewing the system hardware and software information, task manager, and some other functions.</p>"));
//    aboutDlg->setAppDescription(tr("<p>The software is still under development. Please visit  kylin-assistant") + QString::fromLocal8Bit("<a style='color: #3f96e4;' href = https://github.com/UbuntuKylin/youker-assistant>Github</a>") + tr(" for more information. Welcome everyone to join with us.</p>"));
    aboutDlg->setAppDescription(tr("<p>Service & Support : <a style='color: black;' href='mailto://support@kylinos.cn'>support@kylinos.cn</a></p>"));

    QApplication::restoreOverrideCursor();
}

void MainWindow::aboutUs()
{
    /*int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (442  / 2);
    int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (326  / 2);
    if(aboutDlg == NULL)
    {
        aboutDlg = new AboutDialog(0, last_skin_path, this->arch, this->osName);
        aboutDlg->move(w_x, w_y);
        aboutDlg->show();
        aboutDlg->raise();
    }
    else {
        aboutDlg->move(w_x, w_y);
        aboutDlg->show();
        aboutDlg->raise();
    }*/
//    if (!aboutDlg) {
//        createAboutDialog();
//    }
//    int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (442  / 2);
//    int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (326  / 2);
//    aboutDlg->move(w_x, w_y);
//    aboutDlg->setModal(true);
//    aboutDlg->show();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    /*if(event->button() == Qt::LeftButton)
    {
        m_mousePressed = true;
        m_dragPosition = event->globalPos() - pos();
    }*/
//    if (event->button() == Qt::LeftButton) {
//        this->m_dragPosition = event->globalPos() - frameGeometry().topLeft();
//        this->m_mousePressed = true;
//        this->setCursor(Qt::OpenHandCursor);
//    }

    QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    /*m_mousePressed = false;
    setWindowOpacity(1);*/
//    this->m_mousePressed = false;
//    this->setCursor(Qt::ArrowCursor);
//    setWindowOpacity(1);

    QMainWindow::mouseReleaseEvent(event);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    /*if(m_mousePressed)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - m_dragPosition);
        setWindowOpacity(0.9);
//        event->accept();
    }*/
//    if (this->m_mousePressed) {
//        move(event->globalPos() - this->m_dragPosition);
//        setWindowOpacity(0.9);
//    }

    QMainWindow::mouseMoveEvent(event);
}

//void MainWindow::paintEvent(QPaintEvent *event)
//{
//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.setOpacity(0.05);

//    int penWidth = 1;
//    QPainterPath framePath;
//    framePath.addRoundedRect(QRect(rect().x() + penWidth, rect().y() + penWidth, rect().width() - penWidth * 2, rect().height() - penWidth * 2), 3, 3);//背景弧度
//    painter.setClipPath(framePath);

//    QPen framePen;
//    framePen.setColor(QColor("#fca71d"));
//    painter.setOpacity(0.2);
//    painter.drawPath(framePath);
//}

bool MainWindow::nativeEventFilter(const QByteArray &eventType, void *message, long *result) //监听全局x事件
{
    if (qstrcmp(eventType, "xcb_generic_event_t") != 0) {
        return false;
    }

    xcb_generic_event_t *event = reinterpret_cast<xcb_generic_event_t*>(message);
    const uint8_t responseType = event->response_type & ~0x80;
    if(responseType == rr_event_base + RRScreenChangeNotify){
        RRScreenChangeEvent();  //屏幕改变事件
    }
    return false;
}

void MainWindow::RRScreenChangeEvent()
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
        if(m_dataWorker) {
            m_dataWorker->onRequestMonitorInfo();
        }
    }
}
