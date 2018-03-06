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
#include <QGraphicsDropShadowEffect>
#include <QStackedLayout>
#include "../component/utils.h"
#include "../component/threadpool.h"
#include "dataworker.h"
#include "../component/utils.h"

#include "maintopwidget.h"
#include "middlewidget.h"
#include "mainbottomwidget.h"
#include "topbasewidget.h"
#include <QtMath>

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
    GlobalData::globalarch = this->arch;

    registerCustomDataMetaType();
    registerCustomDataListMetaType();

    this->osName = accessOSName();
//    char *dsk;
//    dsk = getenv("XDG_CURRENT_DESKTOP");
    this->desktop = qgetenv("XDG_CURRENT_DESKTOP");
    if(this->desktop.isEmpty())
        this->desktop = qgetenv("XDG_SESSION_DESKTOP");

    //For Unity
//    this->setWindowFlags(/*Qt::Window | */Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);//Attention: Qt::WindowCloseButtonHint make showMinimized() valid

    //For UKUI and Mate
    this->setWindowFlags(Qt::FramelessWindowHint  | Qt::WindowCloseButtonHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setAutoFillBackground(true);
    this->setMouseTracking(true);
    this->setWindowTitle(tr("Kylin Assistant"));
    this->setWindowIcon(QIcon(":/res/kylin-assistant.png"));
    this->setWindowOpacity(1);
    this->setFixedSize(MAIN_WINDOW_WIDTH+SHADOW_LEFT_TOP_PADDING+SHADOW_LEFT_TOP_PADDING, MAIN_WINDOW_HEIGHT+SHADOW_RIGHT_BOTTOM_PADDING+SHADOW_RIGHT_BOTTOM_PADDING);

    status = HOMEPAGE;

    mSettings = new QSettings(KYLIN_COMPANY_SETTING, KYLIN_SETTING_FILE_NAME_SETTING);
    mSettings->setIniCodec("UTF-8");

    last_skin_path = ":/background/res/skin/1.png";

    main_skin_pixmap.load(last_skin_path);

    info_widget = NULL;
    cleaner_widget = NULL;
    setting_widget = NULL;
    box_widget = NULL;
    aboutDlg = NULL;

    cleaner_action_widget = NULL;
    setting_action_widget = NULL;
    box_action_widget = NULL;

    toolKits = new Toolkits(0, this->width(), this->height());

    main_menu = new KylinMenu(this);
    main_menu->setParentWindow(this);
    main_menu->initConnect();

    this->initWidgets();

    //边框阴影效果
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setBlurRadius(5);
    shadow_effect->setColor(QColor(0, 0, 0, 127));
    shadow_effect->setOffset(2, 4);
    this->setGraphicsEffect(shadow_effect);

    this->hide();

    this->startDbusDaemon();
}

MainWindow::~MainWindow()
{
//    delete m_qSystemDbus;

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
    if (setting_widget != NULL)
    {
        delete setting_widget;
        setting_widget = NULL;
    }
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

    //top
    m_mainTopWidget = new MainTopWidget(true, mSettings, this);
//    m_mainTopWidget->setParentWindow(this);
    connect(m_mainTopWidget, SIGNAL(showMenu()), this, SLOT(showMainMenu()));
//    connect(m_mainTopWidget, SIGNAL(showMin()), this, SLOT(showMinimized()));
    connect(m_mainTopWidget, &MainTopWidget::showMin, this, [=] {
        this->showMinimized();
    });
    connect(m_mainTopWidget, SIGNAL(closeApp()), this, SLOT(closeYoukerAssistant()));
    m_mainTopWidget->setPalette(palette_back);
    m_topStack->addWidget(m_mainTopWidget);

    cleaner_action_widget = new MainTopWidget(false, mSettings, this);
    connect(cleaner_action_widget, SIGNAL(showMenu()), this, SLOT(showMainMenu()));
    connect(cleaner_action_widget, SIGNAL(showMin()), this, SLOT(showMinimized()));
    connect(cleaner_action_widget, SIGNAL(closeApp()), this, SLOT(closeYoukerAssistant()));
    cleaner_action_widget->setPalette(palette_back);
    m_topStack->addWidget(cleaner_action_widget);

    info_action_widget = new TopBaseWidget(this);
    connect(info_action_widget, SIGNAL(showMenu()), this, SLOT(showMainMenu()));
    connect(info_action_widget, SIGNAL(showMin()), this, SLOT(showMinimized()));
    connect(info_action_widget, SIGNAL(closeApp()), this, SLOT(closeYoukerAssistant()));
    info_action_widget->setPalette(palette_back);
    info_action_widget->setImage("://res/systeminfo.png");
    info_action_widget->setTipMessage(tr("Understand hardware information, provide more convenient channel to obtain hardware information"));
    m_topStack->addWidget(info_action_widget);

    setting_action_widget = new TopBaseWidget(this);
    connect(setting_action_widget, SIGNAL(showMenu()), this, SLOT(showMainMenu()));
    connect(setting_action_widget, SIGNAL(showMin()), this, SLOT(showMinimized()));
    connect(setting_action_widget, SIGNAL(closeApp()), this, SLOT(closeYoukerAssistant()));
    setting_action_widget->setPalette(palette_back);
    setting_action_widget->setImage("://res/systemset.png");
    setting_action_widget->setTipMessage(tr("You can perform a full range of customized systems based on personal preferences"));
    m_topStack->addWidget(setting_action_widget);

    box_action_widget = new TopBaseWidget(this);
    connect(box_action_widget, SIGNAL(showMenu()), this, SLOT(showMainMenu()));
    connect(box_action_widget, SIGNAL(showMin()), this, SLOT(showMinimized()));
    connect(box_action_widget, SIGNAL(closeApp()), this, SLOT(closeYoukerAssistant()));
    box_action_widget->setPalette(palette_back);
    box_action_widget->setImage("://res/toolkits.png");
    box_action_widget->setTipMessage(tr("Provide a practical and lightweight tool, create fast and convenient experience for you"));
    m_topStack->addWidget(box_action_widget);

    //middle
    m_middleWidget = new MiddleWidget(this, this->arch, this->osName);
    m_middleWidget->setFixedSize(MAIN_WINDOW_WIDTH, 47);
    connect(m_middleWidget, SIGNAL(turnCurrentPage(int)), this, SLOT(setCurrentPageIndex(int)));

    //bottom
    m_mainBottomWidget = new MainBottomWidget(this, this->arch, this->osName);
    connect(m_mainBottomWidget, SIGNAL(sendSignal()), m_middleWidget, SLOT(showBoxTool()));
    m_bottomStack->addWidget(m_mainBottomWidget);

    cleaner_widget = new CleanerWidget();
    m_bottomStack->addWidget(cleaner_widget);
    cleaner_widget->setToolKits(toolKits);
    cleaner_widget->setParentWindow(this);
    cleaner_widget->initUI(last_skin_path);
    connect(cleaner_action_widget, SIGNAL(showDetailData()),cleaner_widget, SLOT(displayDetailPage()));
    connect(cleaner_action_widget, SIGNAL(showMainData()),cleaner_widget, SLOT(displayMainPage()));
    connect(cleaner_action_widget, SIGNAL(sendCleanSignal()),cleaner_widget, SIGNAL(transCleanSignal()));

    info_widget = new InfoWidget(this->arch);
    m_bottomStack->addWidget(info_widget);

    setting_widget = new SettingWidget(this->desktop);
    setting_widget->setParentWindow(this);
    connect(setting_widget, SIGNAL(changeActionPage(QString)), setting_action_widget, SLOT(displayActionSubPage(QString)));
    connect(setting_action_widget, SIGNAL(notifyContentPageToMain()), setting_widget, SLOT(displaySettingHomePage()));
    m_bottomStack->addWidget(setting_widget);

    box_widget = new BoxWidget(this, this->arch, this->osName, getPluginsDirectory());
    connect(box_widget, SIGNAL(pluginModuleError(QString)), this, SLOT(onPluginModuleError(QString)));
    m_bottomStack->addWidget(box_widget);

    centralWidget = new QWidget;
    QVBoxLayout *contentLayout = new QVBoxLayout(centralWidget);
    this->setCentralWidget(centralWidget);
    this->setContentsMargins(SHADOW_LEFT_TOP_PADDING,SHADOW_LEFT_TOP_PADDING,SHADOW_RIGHT_BOTTOM_PADDING,SHADOW_RIGHT_BOTTOM_PADDING);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setMargin(0);
    contentLayout->setSpacing(0);

    contentLayout->addWidget(m_topStack);
    contentLayout->addWidget(m_middleWidget);
    contentLayout->addWidget(m_bottomStack);
    m_topStack->setCurrentWidget(m_mainTopWidget);
    m_bottomStack->setCurrentWidget(m_mainBottomWidget);
}

void MainWindow::onInitDataFinished()
{
    this->battery = m_dataWorker->isBatteryExist();
    this->sensor = m_dataWorker->isSensorExist();
    this->m_cpulist = m_dataWorker->cpuModeList();
    this->m_currentCpuMode = m_dataWorker->cpuCurrentMode();

    /*
    Qt::AutoConnection 自动连接：（默认值）如果信号在接收者所依附的线程内发射，则等同于直接连接。如果发射信号的线程和接受者所依附的线程不同，则等同于队列连接。
    Qt::DirectConnection 直接连接：当信号发射时，槽函数将直接被调用。无论槽函数所属对象在哪个线程，槽函数都在发射信号的线程内执行。
    Qt::QueuedConnection 队列连接：当控制权回到接受者所依附线程的事件循环时，槽函数被调用。槽函数在接收者所依附线程执行。也就是说：这种方式既可以在线程内传递消息，也可以跨线程传递消息
    Qt::BlockingQueuedConnection 与Qt::QueuedConnection类似，但是会阻塞等到关联的slot都被执行。这里出现了阻塞这个词，说明它是专门用来多线程间传递消息的。
    */
    //kobe: why does ui died ??????????????????????
    connect(m_mainTopWidget, SIGNAL(startOneKeyScan(QStringList)), m_dataWorker, SLOT(onStartOneKeyScan(QStringList))/*, Qt::QueuedConnection*/);//Qt::QueuedConnection
    connect(m_mainTopWidget, SIGNAL(startOneKeyClean()), m_dataWorker, SLOT(onStartOneKeyClean())/*, Qt::BlockingQueuedConnection*/);
    connect(m_dataWorker, SIGNAL(isScanning(QString)), m_mainTopWidget, SLOT(getScanResult(QString)), Qt::BlockingQueuedConnection);//Qt::BlockingQueuedConnection
    connect(m_dataWorker, SIGNAL(finishScanWork(QString)), m_mainTopWidget, SLOT(finishScanResult(QString)), Qt::BlockingQueuedConnection);
    connect(m_dataWorker, SIGNAL(tellScanResult(QString,QString)) ,m_mainTopWidget, SLOT(getScanAllResult(QString,QString)), Qt::BlockingQueuedConnection);
    connect(m_dataWorker, SIGNAL(finishCleanWorkMain(QString)), m_mainTopWidget, SLOT(getCleanResult(QString)), Qt::BlockingQueuedConnection);
    connect(m_dataWorker, SIGNAL(finishCleanWorkMainError(QString)), m_mainTopWidget, SLOT(finishCleanError(QString)), Qt::BlockingQueuedConnection);
    connect(m_dataWorker, SIGNAL(quickCleanProcess(QString,QString)), m_mainTopWidget, SLOT(getCleaningMessage(QString,QString)), Qt::BlockingQueuedConnection);

    connect(cleaner_action_widget, SIGNAL(showDetailData()),cleaner_widget, SLOT(displayDetailPage()));
    connect(cleaner_action_widget, SIGNAL(showMainData()),cleaner_widget, SLOT(displayMainPage()));
    connect(cleaner_action_widget, SIGNAL(sendCleanSignal()),cleaner_widget, SIGNAL(transCleanSignal()));

    connect(m_dataWorker, SIGNAL(tellCleanerDetailData(QStringList)), cleaner_widget, SIGNAL(tellCleanerDetailData(QStringList)), Qt::BlockingQueuedConnection);
    connect(m_dataWorker, SIGNAL(tellCleanerDetailStatus(QString)), cleaner_widget, SIGNAL(tellCleanerDetailStatus(QString)), Qt::BlockingQueuedConnection);

    connect(m_dataWorker, SIGNAL(tellCleanerDetailStatus(QString)), cleaner_action_widget, SLOT(showCleanReciveStatus(QString)), Qt::BlockingQueuedConnection);
    connect(m_dataWorker, SIGNAL(tellCleanerDetailError(QString)), cleaner_action_widget, SLOT(showCleanReciveError(QString)), Qt::BlockingQueuedConnection);

    connect(m_dataWorker, SIGNAL(sendCleanOverSignal()), cleaner_widget, SLOT(displayMainPage()));
    connect(m_dataWorker, SIGNAL(sendCleanOverSignal()), cleaner_action_widget, SLOT(displayOrgPage()));
    connect(m_dataWorker, SIGNAL(sendCleanOverSignal()), cleaner_action_widget, SLOT(showCleanOverStatus()));
    connect(m_dataWorker, SIGNAL(policykitCleanSignal(bool)), cleaner_action_widget, SLOT(receivePolicyKitSignal(bool)));
    connect(m_dataWorker, SIGNAL(tellCleanerMainData(QStringList)), cleaner_action_widget, SLOT(showCleanerData(QStringList)), Qt::BlockingQueuedConnection);
    connect(m_dataWorker, SIGNAL(tellCleanerMainStatus(QString, QString)), cleaner_action_widget, SLOT(showCleanerStatus(QString, QString)), Qt::BlockingQueuedConnection);
    connect(m_dataWorker, SIGNAL(sendCleanErrorSignal(QString)), cleaner_action_widget, SLOT(showCleanerError(QString)), Qt::BlockingQueuedConnection);

    connect(cleaner_widget, SIGNAL(startScanSystem(QMap<QString,QVariant>)), m_dataWorker, SLOT(onStartScanSystem(QMap<QString,QVariant>)));
    connect(cleaner_widget, SIGNAL(startCleanSystem(QMap<QString,QVariant>)), m_dataWorker, SLOT(onStartCleanSystem(QMap<QString,QVariant>)));

    connect(cleaner_action_widget, SIGNAL(sendScanSignal()),cleaner_widget, SIGNAL(transScanSignal()));
    connect(cleaner_widget, SIGNAL(tranActionAnimaitonSignal()),cleaner_action_widget, SLOT(displayAnimation()));
    connect(cleaner_widget, SIGNAL(tranScanOverSignal(bool)),cleaner_action_widget, SLOT(accordScanOverStatusToChange(bool)));

    connect(info_widget, SIGNAL(requestupdateSystemRunnedTime()), m_dataWorker, SLOT(onUpdateSystemRunnedTime()));
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
    connect(setting_widget, SIGNAL(changeSystemTheme(QString)), m_dataWorker, SLOT(onChangeSystemTheme(QString)));
    connect(setting_widget, SIGNAL(requestThemeData()), m_dataWorker, SLOT(onRequestThemeData()));
    connect(m_dataWorker, SIGNAL(sendThemeList(QString,QStringList)), setting_widget, SIGNAL(sendThemeList(QString,QStringList)));

    //icon
    connect(setting_widget, SIGNAL(requestIconData()), m_dataWorker, SLOT(onRequestIconData()));
    connect(m_dataWorker, SIGNAL(sendIconThemeList(QString,QStringList)), setting_widget, SIGNAL(sendIconThemeList(QString,QStringList)));
    connect(m_dataWorker, SIGNAL(sendDisplayIconValue(bool,bool,bool,bool,bool)), setting_widget, SIGNAL(sendDisplayIconValue(bool,bool,bool,bool,bool)));
    connect(setting_widget, SIGNAL(resetIconTheme(QString)), m_dataWorker, SLOT(onResetIconTheme(QString)));
    connect(setting_widget, SIGNAL(displayComputerIcon(bool)), m_dataWorker, SLOT(onDisplayComputerIcon(bool)));
    connect(setting_widget, SIGNAL(displayFolderIcon(bool)), m_dataWorker, SLOT(onDisplayFolderIcon(bool)));
    connect(setting_widget, SIGNAL(displayNetworkIcon(bool)), m_dataWorker, SLOT(onDisplayNetworkIcon(bool)));
    connect(setting_widget, SIGNAL(displayRecycleBinIcon(bool)), m_dataWorker, SLOT(onDisplayRecycleBinIcon(bool)));
    connect(setting_widget, SIGNAL(displayDiskIcon(bool)), m_dataWorker, SLOT(onDisplayDiskIcon(bool)));

    //mouse
    connect(setting_widget, SIGNAL(requestMouseData()), m_dataWorker, SLOT(onRequestMouseData()));
    connect(m_dataWorker, SIGNAL(sendMouseThemeAndCusorSize(QString,QStringList,int)), setting_widget, SIGNAL(sendMouseThemeAndCusorSize(QString,QStringList,int)));
    connect(setting_widget, SIGNAL(resetMouseCursorTheme(QString)), m_dataWorker, SLOT(onResetMouseCursorTheme(QString)));
    connect(setting_widget, SIGNAL(resetMouseCursorSize(int)), m_dataWorker, SLOT(onResetMouseCursorSize(int)));

    //voice
    connect(setting_widget, SIGNAL(requestSoundData()), m_dataWorker, SLOT(onRequestSoundData()));
    connect(m_dataWorker, SIGNAL(sendSoundList(QString,QStringList)), setting_widget, SIGNAL(sendSoundList(QString,QStringList)));
    connect(m_dataWorker, SIGNAL(sendEnableSoundValue(bool,bool,bool)), setting_widget, SIGNAL(sendEnableSoundValue(bool,bool,bool)));
    connect(setting_widget, SIGNAL(resetVoiceTheme(QString)), m_dataWorker, SLOT(onResetVoiceTheme(QString)));
    connect(setting_widget, SIGNAL(resetLoginTipVoice(bool)), m_dataWorker, SLOT(onResetLoginTipVoice(bool)));
    connect(setting_widget, SIGNAL(resetEventVoice(bool)), m_dataWorker, SLOT(onResetEventVoice(bool)));
    connect(setting_widget, SIGNAL(resetInputFeedbackVoice(bool)), m_dataWorker, SLOT(onResetInputFeedbackVoice(bool)));

    //panel
    connect(setting_widget, SIGNAL(requestMateOrUnityPanelData(bool)), m_dataWorker, SLOT(onRequestMateOrUnityPanelData(bool)));
    connect(m_dataWorker, SIGNAL(sendMatePanelValue(bool,bool,bool,bool)), setting_widget, SIGNAL(sendMatePanelValue(bool,bool,bool,bool)));
    connect(m_dataWorker, SIGNAL(sendUnityBlurAndTransparencyValue(int,double)), setting_widget, SIGNAL(sendUnityBlurAndTransparencyValue(int,double)));
    connect(m_dataWorker, SIGNAL(sendUnityTimeValue(QString,QStringList,bool,bool,bool)), setting_widget, SIGNAL(sendUnityTimeValue(QString,QStringList,bool,bool,bool)));
    connect(m_dataWorker, SIGNAL(sendUnityPanelPowerValue(QString,QStringList,bool,bool)), setting_widget, SIGNAL(sendUnityPanelPowerValue(QString,QStringList,bool,bool)));
    connect(setting_widget, SIGNAL(resetPanelTransparencyValue(double)), m_dataWorker, SLOT(onResetPanelTransparencyValue(double)));
    connect(setting_widget, SIGNAL(resetDateFormat(QString)), m_dataWorker, SLOT(onResetDateFormat(QString)));
    connect(setting_widget, SIGNAL(resetShowBatteryIcon(QString)), m_dataWorker, SLOT(onResetShowBatteryIcon(QString)));
    connect(setting_widget, SIGNAL(resetDashBlurExperimental(int)), m_dataWorker, SLOT(onResetDashBlurExperimental(int)));
    connect(setting_widget, SIGNAL(resetDisplaySeconds(bool)), m_dataWorker, SLOT(onResetDisplaySeconds(bool)));
    connect(setting_widget, SIGNAL(resetDisplayWeek(bool)), m_dataWorker, SLOT(onResetDisplayWeek(bool)));
    connect(setting_widget, SIGNAL(resetDisplayDate(bool)), m_dataWorker, SLOT(onResetDisplayDate(bool)));
    connect(setting_widget, SIGNAL(resetDisplayBatteryPercentage(bool)), m_dataWorker, SLOT(onResetDisplayBatteryPercentage(bool)));
    connect(setting_widget, SIGNAL(resetDisplayBatteryTime(bool)), m_dataWorker, SLOT(onResetDisplayBatteryTime(bool)));
    connect(setting_widget, SIGNAL(resetShowApplications(bool)), m_dataWorker, SLOT(onResetShowApplications(bool)));
    connect(setting_widget, SIGNAL(resetShowDesktop(bool)), m_dataWorker, SLOT(onResetShowDesktop(bool)));
    connect(setting_widget, SIGNAL(resetShowIcon(bool)), m_dataWorker, SLOT(onResetShowIcon(bool)));
    connect(setting_widget, SIGNAL(resetShowPlaces(bool)), m_dataWorker, SLOT(onResetShowPlaces(bool)));

    //launcher menu
    connect(setting_widget, SIGNAL(requestMateOrUnityMenuData(bool)), m_dataWorker, SLOT(onRequestMateOrUnityMenuData(bool)));
    connect(m_dataWorker, SIGNAL(sendMatePanelIconValue(int,int,bool,bool)), setting_widget, SIGNAL(sendMatePanelIconValue(int,int,bool,bool)));
    connect(m_dataWorker, SIGNAL(sendUnityIconValue(int,bool,bool,double,int,QStringList)), setting_widget, SIGNAL(sendUnityIconValue(int,bool,bool,double,int,QStringList)));
    connect(m_dataWorker, SIGNAL(sendUnityLauncherPosition(QString,QStringList)), setting_widget, SIGNAL(sendUnityLauncherPosition(QString,QStringList)));

    connect(setting_widget, SIGNAL(resetIconSizeValue(int)), m_dataWorker, SLOT(onResetIconSizeValue(int)));
    connect(setting_widget, SIGNAL(resetTransparencyValue(int)), m_dataWorker, SLOT(onResetTransparencyValue(int)));
    connect(setting_widget, SIGNAL(resetIconColouring(int)), m_dataWorker, SLOT(onResetIconColouring(int)));
    connect(setting_widget, SIGNAL(resetAutoHide(bool)), m_dataWorker, SLOT(onResetAutoHide(bool)));
    connect(setting_widget, SIGNAL(resetDisplayDesktopIcon(bool)), m_dataWorker, SLOT(onResetDisplayDesktopIcon(bool)));
    connect(setting_widget, SIGNAL(resetTopIconSizeValue(int)), m_dataWorker, SLOT(onResetTopIconSizeValue(int)));
    connect(setting_widget, SIGNAL(resetBottomIconSizeValue(int)), m_dataWorker, SLOT(onResetBottomIconSizeValue(int)));
    connect(setting_widget, SIGNAL(resetTopAutoHide(bool)), m_dataWorker, SLOT(onResetTopAutoHide(bool)));
    connect(setting_widget, SIGNAL(resetBottomAutoHide(bool)), m_dataWorker, SLOT(onResetBottomAutoHide(bool)));
    connect(setting_widget, SIGNAL(resetLauncherPosition(QString)), m_dataWorker, SLOT(onResetLauncherPosition(QString)));

    //window
    connect(setting_widget, SIGNAL(requesetWindowButtonAlign()), m_dataWorker, SLOT(onRequesetWindowButtonAlign()));
    connect(setting_widget, SIGNAL(requesetMenusHaveIcons()), m_dataWorker, SLOT(onRequesetMenusHaveIcons()));
    connect(setting_widget, SIGNAL(requesetWindowTitileTags()), m_dataWorker, SLOT(onRequesetWindowTitileTags()));

    connect(m_dataWorker, SIGNAL(sendWindowButtonAlign(QString)), setting_widget, SIGNAL(sendWindowButtonAlign(QString)));
    connect(m_dataWorker, SIGNAL(sendMenusHaveIcons(bool)), setting_widget, SIGNAL(sendMenusHaveIcons(bool)));
    connect(m_dataWorker, SIGNAL(sendWindowTitileTags(QString,QStringList,QStringList,QString,QString,QString)), setting_widget, SIGNAL(sendWindowTitileTags(QString,QStringList,QStringList,QString,QString,QString)));

    connect(setting_widget, SIGNAL(resetMenusHaveIcon(bool)), m_dataWorker, SLOT(onResetMenusHaveIcon(bool)));
    connect(setting_widget, SIGNAL(resetTitlebarWheel(QString)), m_dataWorker, SLOT(onResetTitlebarWheel(QString)));
    connect(setting_widget, SIGNAL(resetTitlebarDoubleClick(QString)), m_dataWorker, SLOT(onResetTitlebarDoubleClick(QString)));
    connect(setting_widget, SIGNAL(resetMouseMiddleClick(QString)), m_dataWorker, SLOT(onResetMouseMiddleClick(QString)));
    connect(setting_widget, SIGNAL(resetMouseRightClick(QString)), m_dataWorker, SLOT(onResetMouseRightClick(QString)));
    connect(setting_widget, SIGNAL(resetWindowButtonLeftOrRightAlign(bool)), m_dataWorker, SLOT(onResetWindowButtonLeftOrRightAlign(bool)));

    //font
    connect(setting_widget, SIGNAL(requestFontData()), m_dataWorker, SLOT(onRequestFontData()));
    connect(m_dataWorker, SIGNAL(sendFontValue(QString)), setting_widget, SIGNAL(sendFontValue(QString)));
    connect(m_dataWorker, SIGNAL(sendDesktopFontValue(QString)), setting_widget, SIGNAL(sendDesktopFontValue(QString)));
    connect(m_dataWorker, SIGNAL(sendMonospaceFontValue(QString)), setting_widget, SIGNAL(sendMonospaceFontValue(QString)));
    connect(m_dataWorker, SIGNAL(sendDocumentFontValue(QString)), setting_widget, SIGNAL(sendDocumentFontValue(QString)));
    connect(m_dataWorker, SIGNAL(sendTitlebarFontValue(QString)), setting_widget, SIGNAL(sendTitlebarFontValue(QString)));
    connect(m_dataWorker, SIGNAL(sendFontSmoothAndAntialiasingValue(double,QString,QStringList,QString,QStringList)), setting_widget, SIGNAL(sendFontSmoothAndAntialiasingValue(double,QString,QStringList,QString,QStringList)));

    connect(setting_widget, SIGNAL(setDefaultFontByName(QString)), m_dataWorker, SLOT(onSetDefaultFontByName(QString)));
    connect(setting_widget, SIGNAL(setDesktopFontByName(QString)), m_dataWorker, SLOT(onSetDesktopFontByName(QString)));
    connect(setting_widget, SIGNAL(setMonospaceFontByName(QString)), m_dataWorker, SLOT(onSetMonospaceFontByName(QString)));
    connect(setting_widget, SIGNAL(setDocumentFontByName(QString)), m_dataWorker, SLOT(onSetDocumentFontByName(QString)));
    connect(setting_widget, SIGNAL(setTitlebarFontByName(QString)), m_dataWorker, SLOT(onSetTitlebarFontByName(QString)));
    connect(setting_widget, SIGNAL(resetFontZoomScalingValue(double)), m_dataWorker, SLOT(onResetFontZoomScalingValue(double)));
    connect(setting_widget, SIGNAL(resetFontHinting(QString)), m_dataWorker, SLOT(onResetFontHinting(QString)));
    connect(setting_widget, SIGNAL(resetFontAntialiasing(QString)), m_dataWorker, SLOT(onResetFontAntialiasing(QString)));
    connect(setting_widget, SIGNAL(restoreDefaultFont(bool)), m_dataWorker, SLOT(onRestoreDefaultFont(bool)));
    connect(setting_widget, SIGNAL(restoreDesktopDefaultFont(bool)), m_dataWorker, SLOT(onRestoreDesktopDefaultFont(bool)));
    connect(setting_widget, SIGNAL(restoreMonospaceDefaultFont(bool)), m_dataWorker, SLOT(onRestoreMonospaceDefaultFont(bool)));
    connect(setting_widget, SIGNAL(restoreDocumentDefaultFont(bool)), m_dataWorker, SLOT(onRestoreDocumentDefaultFont(bool)));
    connect(setting_widget, SIGNAL(restoreTitlebarDefaultFont(bool)), m_dataWorker, SLOT(onRestoreTitlebarDefaultFont(bool)));

    //touchpad
    connect(setting_widget, SIGNAL(requestMateOrUnityTouchpadData(bool)), m_dataWorker, SLOT(onRequestMateOrUnityTouchpadData(bool)));
    connect(m_dataWorker, SIGNAL(sendTouchPadValue(bool,bool,QString,int,QString)), setting_widget, SIGNAL(sendTouchPadValue(bool,bool,QString,int,QString)));
    connect(setting_widget, SIGNAL(resetTouchpad(bool)), m_dataWorker, SLOT(onResetTouchpad(bool)));
    connect(setting_widget, SIGNAL(resetHorizontalScrolling(bool)), m_dataWorker, SLOT(onResetHorizontalScrolling(bool)));
    connect(setting_widget, SIGNAL(setScrollbarOverlayOrLegacyMode(bool)), m_dataWorker, SLOT(onSetScrollbarOverlayOrLegacyMode(bool)));
    connect(setting_widget, SIGNAL(setMateTouchscrollingMode(int)), m_dataWorker, SLOT(onSetMateTouchscrollingMode(int)));
    connect(setting_widget, SIGNAL(setUnityTouchscrollingMode(int)), m_dataWorker, SLOT(onSetUnityTouchscrollingMode(int)));

    //ac and battery
    connect(setting_widget, SIGNAL(requestPowerAndBatteryData()), m_dataWorker, SLOT(onRequestPowerAndBatteryData()));
    connect(m_dataWorker, SIGNAL(sendIdleAndGammaData(double,QStringList,int,QString,QString,QString,QStringList)), setting_widget, SIGNAL(sendIdleAndGammaData(double,QStringList,int,QString,QString,QString,QStringList)));
    connect(m_dataWorker, SIGNAL(sendLockAndSleepData(bool,QString,QStringList,QString,QString,QString,QString,QStringList,QString)), setting_widget, SIGNAL(sendLockAndSleepData(bool,QString,QStringList,QString,QString,QString,QString,QStringList,QString)));

    connect(setting_widget, SIGNAL(resetScreenGammaValue(double)), m_dataWorker, SLOT(onResetScreenGammaValue(double)));
    connect(setting_widget, SIGNAL(resetBrightnessValue(int)), m_dataWorker, SLOT(onResetBrightnessValue(int)));
    connect(setting_widget, SIGNAL(resetIdleDelay(int,int)), m_dataWorker, SLOT(onResetIdleDelay(int,int)));
    connect(setting_widget, SIGNAL(resetLockEnabled(bool)), m_dataWorker, SLOT(onResetLockEnabled(bool)));
    connect(setting_widget, SIGNAL(resetLockDelay(int,int)), m_dataWorker, SLOT(onResetLockDelay(int,int)));
    connect(setting_widget, SIGNAL(setCurrentCriticalLow(QString)), m_dataWorker, SLOT(onSetCurrentCriticalLow(QString)));
    connect(setting_widget, SIGNAL(setCurrentLidBattery(QString)), m_dataWorker, SLOT(onSetCurrentLidBattery(QString)));
    connect(setting_widget, SIGNAL(setCurrentLidAC(QString)), m_dataWorker, SLOT(onSetCurrentLidAC(QString)));
    connect(setting_widget, SIGNAL(resetSleepTimeoutBattery(int,int)), m_dataWorker, SLOT(onResetSleepTimeoutBattery(int,int)));
    connect(setting_widget, SIGNAL(resetSleepTimeoutAC(int,int)), m_dataWorker, SLOT(onResetSleepTimeoutAC(int,int)));
    connect(setting_widget, SIGNAL(resetSleepTimeoutDisplayBattery(int,int)), m_dataWorker, SLOT(onResetSleepTimeoutDisplayBattery(int,int)));
    connect(setting_widget, SIGNAL(resetSleepTimeoutDisplayAC(int,int)), m_dataWorker, SLOT(onResetSleepTimeoutDisplayAC(int,int)));
    connect(setting_widget, SIGNAL(setCurrentCpuMode(QString)), m_dataWorker, SLOT(onSetCurrentCpuMode(QString)));

    //file manager
    connect(setting_widget, SIGNAL(requestFileManagerData()), m_dataWorker, SLOT(onRequestFileManagerData()));
    connect(m_dataWorker, SIGNAL(sendFileManagerData(bool,bool,bool,bool,int,int,int)), setting_widget, SIGNAL(sendFileManagerData(bool,bool,bool,bool,int,int,int)));

    connect(setting_widget, SIGNAL(resetLocationReplacePathbar(bool)), m_dataWorker, SLOT(onResetLocationReplacePathbar(bool)));
    connect(setting_widget, SIGNAL(resetAutoMountMedia(bool)), m_dataWorker, SLOT(onResetAutoMountMedia(bool)));
    connect(setting_widget, SIGNAL(resetAutoOpenFolder(bool)), m_dataWorker, SLOT(onResetAutoOpenFolder(bool)));
    connect(setting_widget, SIGNAL(resetPromptAutorunPrograms(bool)), m_dataWorker, SLOT(onResetPromptAutorunPrograms(bool)));
    connect(setting_widget, SIGNAL(resetThumbnailIconSize(int)), m_dataWorker, SLOT(onResetThumbnailIconSize(int)));
    connect(setting_widget, SIGNAL(resetThumbnailCacheTime(int)), m_dataWorker, SLOT(onResetThumbnailCacheTime(int)));
    connect(setting_widget, SIGNAL(resetThumbnailCacheSize(int)), m_dataWorker, SLOT(onResetThumbnailCacheSize(int)));

    info_widget->initInfoUI(this->battery, this->sensor);
    setting_widget->initSettingsUI(this->m_cpulist, this->m_currentCpuMode, this->battery/*, last_skin_path*/);
    this->moveCenter();
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
    this->show();
    this->raise();
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
        p.setX(p.x() - 180);
        p.setY(p.y() + 22);
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

void MainWindow::setCurrentPageIndex(int index)
{
    if (index == 0 && status != HOMEPAGE) {
        m_topStack->setCurrentWidget(m_mainTopWidget);
        m_bottomStack->setCurrentWidget(m_mainBottomWidget);
        m_topStack->setFixedSize(m_mainTopWidget->size());
        m_bottomStack->setFixedSize(m_mainBottomWidget->size());
        status = HOMEPAGE;
    }
    else if (index == 1 && status != CLEANPAGE) {
        m_topStack->setCurrentWidget(cleaner_action_widget);
        m_bottomStack->setCurrentWidget(cleaner_widget);
        m_topStack->setFixedSize(cleaner_action_widget->size());
        m_bottomStack->setFixedSize(cleaner_widget->size());
        status = CLEANPAGE;
    }
    else if (index == 2 && status != INFOPAGE) {
        m_topStack->setCurrentWidget(info_action_widget);
        m_bottomStack->setCurrentWidget(info_widget);
        m_topStack->setFixedSize(info_action_widget->size());
        m_bottomStack->setFixedSize(info_widget->size());
        status = INFOPAGE;
    }
    else if (index == 3 && status != SETTINGPAGE) {
        m_topStack->setCurrentWidget(setting_action_widget);
        m_bottomStack->setCurrentWidget(setting_widget);
        m_topStack->setFixedSize(setting_action_widget->size());
        m_bottomStack->setFixedSize(setting_widget->size());
        status = SETTINGPAGE;
    }
    else if (index == 4 && status != BOXPAGE) {
        m_topStack->setCurrentWidget(box_action_widget);
        m_bottomStack->setCurrentWidget(box_widget);
        m_topStack->setFixedSize(box_action_widget->size());
        m_bottomStack->setFixedSize(box_widget->size());
        status = BOXPAGE;
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
    aboutDlg = new AboutDialog(0, last_skin_path, this->arch, this->osName);
    aboutDlg->setModal(false);
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
    if (!aboutDlg) {
        createAboutDialog();
    }
    int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (442  / 2);
    int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (326  / 2);
    aboutDlg->move(w_x, w_y);
    aboutDlg->show();
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    /*if(event->button() == Qt::LeftButton)
    {
        m_mousePressed = true;
        m_dragPosition = event->globalPos() - pos();
    }*/
    if (event->button() == Qt::LeftButton) {
        this->m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->m_mousePressed = true;
    }

    QMainWindow::mousePressEvent(event);
}

void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    /*m_mousePressed = false;
    setWindowOpacity(1);*/
    this->m_mousePressed = false;
    setWindowOpacity(1);

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
    if (this->m_mousePressed) {
        move(event->globalPos() - this->m_dragPosition);
        setWindowOpacity(0.9);
    }

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
