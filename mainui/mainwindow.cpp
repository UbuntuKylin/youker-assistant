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
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>
#include "shadowwidget.h"
#include "cameramanager.h"

MainWindow::MainWindow(QString cur_arch, QWidget *parent) :
    QDialog(parent), arch(cur_arch)/*skin_center(parent),*/
{
    this->osName = accessOSName();
//    char *dsk;
//    dsk = getenv("XDG_CURRENT_DESKTOP");


    this->desktop = qgetenv("XDG_CURRENT_DESKTOP");
    if(this->desktop.isEmpty())
        this->desktop = qgetenv("XDG_SESSION_DESKTOP");
//        qDebug() << this->desktop;
//    qDebug() << QString::compare(this->desktop, "mate", Qt::CaseInsensitive/*Qt::CaseInsensitive*/);

//    this->osName = "Kylin";
//    if (this->arch == "aarch64" || this->osName == "Kylin") {
    if (this->desktop == "MATE" || this->desktop == "mate") {
        this->isTopLevel();
        this->resize(900, 600);
        this->setAutoFillBackground(true);
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
        this->setWindowTitle(tr("Kylin Assistant"));
    }
    else {
        this->setFixedSize(900, 600);
        this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint);
        this->setWindowTitle(tr("Youker Assistant"));
    }

//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint | Qt::WindowSystemMenuHint);
////    this->setAttribute(Qt::WA_TranslucentBackground, true);

    this->setWindowIcon(QIcon(":/res/youker-assistant.png"));
    this->setWindowOpacity(1);
//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
//    this->setAttribute(Qt::WA_TranslucentBackground);
//    this->setStyleSheet("QMainWindow{border: 1px solid gray;border-radius:2px}");
    this->setStyleSheet("QDialog{border: 1px solid white;border-radius:1px;background-color: #ffffff;}");
    version = "V2.1.5";//20161228
    status = HOMEPAGE;
    statusFlag = false;



    mSettings = new QSettings(YOUKER_COMPANY_SETTING, YOUKER_SETTING_FILE_NAME_SETTING);
    mSettings->setIniCodec("UTF-8");


    //judge has skin or not in /var/lib/youker-assistant-daemon/default/
    mSettings->beginGroup("Background");
    last_skin_path = mSettings->value("Path").toString();
    if(last_skin_path.isEmpty()) {
        last_skin_path = ":/background/res/skin/1.png";
        mSettings->setValue("Path", last_skin_path);
    }
    else {
        QStringList skinlist = this->filterSkin();
        QList<QString>::Iterator it = skinlist.begin(), itend = skinlist.end();
        bool flag = false;
        for(;it != itend; it++)
        {
            if(*it == last_skin_path) {
                flag = true;
                break;
            }
        }
        if (flag == false) {
            last_skin_path = skinlist.at(0);
            mSettings->setValue("Path", last_skin_path);
        }
    }

    mSettings->endGroup();
    mSettings->sync();
    main_skin_pixmap.load(last_skin_path);

    skin_center = NULL;

    home_page = NULL;
    info_widget = NULL;
    cleaner_widget = NULL;
    setting_widget = NULL;
    box_widget = NULL;
    aboutDlg = NULL;

    auto_start = NULL;
    upgrade_dialog = NULL;
//    camera_manager = NULL;

    spreadGroup = NULL;
    gatherGroup = NULL;

    home_action_widget = NULL;
    info_action_widget = NULL;
    cleaner_action_widget = NULL;
    setting_action_widget = NULL;
    box_action_widget = NULL;

    toolKits = new Toolkits(0, this->width(), this->height());


    shadow_widget = new ShadowWidget(this);
    shadow_widget->setGeometry(rect());
//    shadow_widget->setColor(QColor(Qt::gray));
    shadow_widget->setColor(QColor("#e9eef0"));

    default_action_widget = new ActionWidget(this);
    default_action_widget->setGeometry(QRect(0, 0, 900, 227));
    default_action_widget->setFixedHeight(227);
    other_action_widget = new ActionWidget(this);
    other_action_widget->setGeometry(QRect(0, -150, 900, 150));
    other_action_widget->setFixedHeight(150);
    topStack = new QStackedWidget(other_action_widget);
    topStack->setGeometry(other_action_widget->rect());

    //设置在最底层，方便title_widget的显示
//    default_action_widget->lower();
    QPalette palette_back;
    palette_back.setBrush(QPalette::Background, QBrush(QPixmap(last_skin_path)));
    default_action_widget->setPalette(palette_back);
    other_action_widget->setPalette(palette_back);

    tool_widget = new ToolWidget(this, this->arch, this->osName);
    tool_widget->setGeometry(QRect(0, 227, 900, 47));
    tool_widget->setParentWindow(this);
    connect(this, SIGNAL(chanegBoxToolStatus()), tool_widget, SLOT(showBoxTool()));
    tool_widget->initConnect();

    title_widget = new TitleWidget(this, this->arch, this->osName);
    if (this->arch == "aarch64" || this->osName == "Kylin")
        title_widget->move(756, 0);
    else {
        title_widget->move(0, 0);
    }
    connect(title_widget, SIGNAL(closeApp()), this, SLOT(closeYoukerAssistant()));
    title_widget->setParentWindow(this);
    title_widget->initConnect();

//
    login_widget = new LoginWidget(this);
    if (this->arch == "aarch64" || this->osName == "Kylin")
        login_widget->hide();
    else {
        login_widget->move(585, 0);//900 - login_widget(220) - right_align(15) = 665
    }

    default_content_widget = new ContentWidget(this);
    default_content_widget->setGeometry(QRect(0, 274, 900, 326));
    default_content_widget->setFixedHeight(326);
    other_content_widget = new ContentWidget(this);
    other_content_widget->setGeometry(QRect(0, 600, 900, 403));
    other_content_widget->setFixedHeight(403);
    bottomStack = new QStackedWidget(other_content_widget);
    bottomStack->setGeometry(other_content_widget->rect());
//    top_grid_layout = NULL;
//    bottom_grid_layout = NULL;

    main_menu = new KylinMenu(this);
    main_menu->setParentWindow(this);
    main_menu->initConnect();

    this->initHomePage();
    this->initAnimation();
}

MainWindow::~MainWindow()
{
    if (home_page != NULL)
    {
        delete home_page;
        home_page = NULL;
    }
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
    if (setting_action_widget != NULL)
    {
        delete setting_action_widget;
        setting_action_widget = NULL;
    }
    if (sessioninterface != NULL)
    {
        delete sessioninterface;
        sessioninterface = NULL;
    }
    if (systeminterface != NULL)
    {
        delete systeminterface;
        systeminterface = NULL;
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

    if(auto_start != NULL)
    {
        delete auto_start;
        auto_start = NULL;
    }
//    if(camera_manager != NULL)
//    {
//        delete camera_manager;
//        camera_manager = NULL;
//    }
    if(skin_center != NULL)
    {
        delete skin_center;
        skin_center = NULL;
    }
    if(upgrade_dialog != NULL)
    {
        delete upgrade_dialog;
        upgrade_dialog = NULL;
    }
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
    bool result = systeminterface->delete_file_qt(filename);
    return result;
}

bool MainWindow::CopyFile(QString filename)
{
    bool result = systeminterface->copy_file_qt(filename);
    return result;
}

QStringList MainWindow::filterSkin()
{
    QStringList skinlist;
    QString path = "/var/lib/youker-assistant-daemon/default/";
    QString path2 = "/var/lib/youker-assistant-daemon/custom/";
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

void MainWindow::initAnimation()
{
    QPoint origPoint(0, 227);
    QPoint needPoint(0, 150);
    QPoint origPoint1(0, 0);
    QPoint needPoint1(0, -227);
    QPoint origPoint2(0, -150);
    QPoint needPoint2(0, 0);

    QPoint origPoint3(0, 274);
    QPoint needPoint3(0, 600);
    QPoint origPoint4(0, 600);
    QPoint needPoint4(0, 197);

    QPropertyAnimation *mainActionAnimation = new QPropertyAnimation(default_action_widget, "pos");
    mainActionAnimation->setDuration(500);
    mainActionAnimation->setStartValue(origPoint1);
    mainActionAnimation->setEndValue(needPoint1);

    QPropertyAnimation *mainActionAnimation2 = new QPropertyAnimation(other_action_widget, "pos");
    mainActionAnimation2->setDuration(500);
    mainActionAnimation2->setStartValue(origPoint2);
    mainActionAnimation2->setEndValue(needPoint2);

    QPropertyAnimation *mainToolAnimation = new QPropertyAnimation(tool_widget, "pos");
    mainToolAnimation->setDuration(500);
    mainToolAnimation->setStartValue(origPoint);
    mainToolAnimation->setEndValue(needPoint);

    QPropertyAnimation *mainContentAnimation = new QPropertyAnimation(default_content_widget, "pos");
    mainContentAnimation->setDuration(500);
    mainContentAnimation->setStartValue(origPoint3);
    mainContentAnimation->setEndValue(needPoint3);

    QPropertyAnimation *mainContentAnimation2 = new QPropertyAnimation(other_content_widget, "pos");
    mainContentAnimation2->setDuration(500);
    mainContentAnimation2->setStartValue(origPoint4);
    mainContentAnimation2->setEndValue(needPoint4);

    QPropertyAnimation  *m_toTrans = new QPropertyAnimation(shadow_widget, "opacity");
    m_toTrans->setDuration(200);
    m_toTrans->setStartValue(1);
    m_toTrans->setEndValue(0);

    spreadGroup = new QParallelAnimationGroup(this);
    spreadGroup->addAnimation(mainActionAnimation);
    spreadGroup->addAnimation(mainActionAnimation2);
    spreadGroup->addAnimation(mainToolAnimation);
    spreadGroup->addAnimation(mainContentAnimation);
    spreadGroup->addAnimation(mainContentAnimation2);
    spreadGroup->addAnimation(m_toTrans);

    QPropertyAnimation *mainActionBackAnimation2 = new QPropertyAnimation(other_action_widget, "pos");
    mainActionBackAnimation2->setDuration(500);
    mainActionBackAnimation2->setStartValue(needPoint2);
    mainActionBackAnimation2->setEndValue(origPoint2);

    QPropertyAnimation *mainActionBackAnimation = new QPropertyAnimation(default_action_widget, "pos");
    mainActionBackAnimation->setDuration(500);
    mainActionBackAnimation->setStartValue(needPoint1);
    mainActionBackAnimation->setEndValue(origPoint1);

    QPropertyAnimation *mainToolBackAnimation = new QPropertyAnimation(tool_widget, "pos");
    mainToolBackAnimation->setDuration(500);
    mainToolBackAnimation->setStartValue(needPoint);
    mainToolBackAnimation->setEndValue(origPoint);


    QPropertyAnimation *mainContentBackAnimation = new QPropertyAnimation(default_content_widget, "pos");
    mainContentBackAnimation->setDuration(500);
    mainContentBackAnimation->setStartValue(needPoint3);
    mainContentBackAnimation->setEndValue(origPoint3);

    QPropertyAnimation *mainContentBackAnimation2 = new QPropertyAnimation(other_content_widget, "pos");
    mainContentBackAnimation2->setDuration(500);
    mainContentBackAnimation2->setStartValue(needPoint4);
    mainContentBackAnimation2->setEndValue(origPoint4);

    QPropertyAnimation  *m_toGray = new QPropertyAnimation(shadow_widget, "opacity");
    m_toGray->setDuration(200);
    m_toGray->setStartValue(0);
    m_toGray->setEndValue(1);

    gatherGroup = new QParallelAnimationGroup(this);
    gatherGroup->addAnimation(mainActionBackAnimation);
    gatherGroup->addAnimation(mainActionBackAnimation2);
    gatherGroup->addAnimation(mainToolBackAnimation);
    gatherGroup->addAnimation(mainContentBackAnimation);
    gatherGroup->addAnimation(mainContentBackAnimation2);
    gatherGroup->addAnimation(m_toGray);

    connect(spreadGroup, SIGNAL(finished()), this, SLOT(upAnimFinished()));
    connect(gatherGroup, SIGNAL(finished()), this, SLOT(closeAnimFinished()));
}

void MainWindow::upAnimFinished()
{
    tool_widget->show();
    shadow_widget->hide();
    if(title_widget->isHidden())
        title_widget->show();
    if (this->arch != "aarch64" && this->osName != "Kylin")
    {
        if(status == BOXPAGE && login_widget->isHidden()) {
            login_widget->show();
        }
        else {
            login_widget->hide();
        }
    }
}

void MainWindow::closeAnimFinished()
{
    tool_widget->show();
    if(title_widget->isHidden())
        title_widget->show();
    if (this->arch != "aarch64" && this->osName != "Kylin" && login_widget->isHidden())
    {
        login_widget->show();
    }
    shadow_widget->hide();
}

void MainWindow::setTranslator(QTranslator* translator)
{
    this->translator = translator;
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
        translator->load(QString(":/qmfile/res/qm/youker-assistant_es.qm"));
        break;

    case YOUKER_ZH_CN:
        translator->load(QString(":/qmfile/res/qm/youker-assistant_zh_CN.qm"));
        break;

    case YOUKER_ES:
        translator->load(QString(":/qmfile/res/qm/youker-assistant_es.qm"));
        break;

    default:
        translator->load(QString(":/qmfile/res/qm/youker-assistant_zh_CN.qm"));
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

void MainWindow::display() {
    if (this->isHidden()) {
        int windowWidth = QApplication::desktop()->width();
        int windowHeight = QApplication::desktop()->height();
        this->move((windowWidth - this->width()) / 2,(windowHeight - this->height()) / 2);
        this->show();
        this->raise();
        QTimer::singleShot(100, this, SLOT(startDbusDaemon()));
    }
    else {
        this->hide();
    }
}

inline bool isRunningInstalled() {
    static bool installed = (QCoreApplication::applicationDirPath() ==
                             QDir(("/usr/bin")).canonicalPath());
    return installed;
}

inline QString getAppDirectory() {
    if (isRunningInstalled()) {
        return QString("/var/lib/youker-assistant-daemon/");
    } else {
        return QString(QCoreApplication::applicationDirPath());
    }
}

void MainWindow::startDbusDaemon()
{
    sessioninterface = new SessionDispatcher(this);
    systeminterface = new SystemDispatcher(this);
//    this->desktop = sessioninterface->access_current_desktop_qt();
//    this->osName = systeminterface->get_os_name_qt();
//    this->machine = sessioninterface->access_current_machine_qt();//x86_64
    this->battery = sessioninterface->judge_power_is_exists_qt();
    login_widget->setSessionDbusProxy(sessioninterface);
    if (this->arch != "aarch64" && this->osName != "Kylin")
        sessioninterface->check_user_qt();
    connect(sessioninterface, SIGNAL(ssoSuccessSignal(QString, QString)), login_widget, SLOT(showLoginInfo(QString,QString)));
    connect(sessioninterface, SIGNAL(ssoLoginLogoutSignal(bool)), login_widget, SLOT(showLoginAndLogoutStatus(bool)));
    home_action_widget->setSessionDbusProxy(sessioninterface);
    home_action_widget->setSystemDbusProxy(systeminterface);
    home_action_widget->enableSanButton();
    connect(sessioninterface, SIGNAL(isScanning(QString)), home_action_widget, SLOT(getScanResult(QString)));
    connect(sessioninterface, SIGNAL(finishScanWork(QString)), home_action_widget, SLOT(finishScanResult(QString)));
    connect(sessioninterface, SIGNAL(tellScanResult(QString,QString)) ,home_action_widget, SLOT(getScanAllResult(QString,QString)));
    connect(systeminterface, SIGNAL(finishCleanWorkMain(QString/*, QString*/)), home_action_widget, SLOT(getCleanResult(QString/*, QString*/)));
    connect(systeminterface, SIGNAL(finishCleanWorkMainError(QString)), home_action_widget, SLOT(finishCleanError(QString)));
    connect(systeminterface, SIGNAL(quickCleanProcess(QString,QString)), home_action_widget, SLOT(getCleaningMessage(QString,QString)));
    home_page->setSessionDbusProxy(sessioninterface);
    home_page->setSystemDbusProxy(systeminterface);
    this->initOtherPages();
}

void MainWindow::initOtherPages()
{
    if(cleaner_action_widget == NULL)
        cleaner_action_widget = new CleanerActionWidget(this);
    topStack->addWidget(cleaner_action_widget);
    if(info_action_widget == NULL)
        info_action_widget = new InfoActionWidget(this);
    topStack->addWidget(info_action_widget);
    if(setting_action_widget == NULL)
        setting_action_widget = new SettingActionWidget();
    topStack->addWidget(setting_action_widget);
    if(box_action_widget == NULL)
        box_action_widget = new BoxActionWidget(this);
    topStack->addWidget(box_action_widget);

    if(cleaner_widget == NULL)
        cleaner_widget = new CleanerWidget();
    cleaner_widget->setSessionDbusProxy(sessioninterface);
    cleaner_widget->setSystemDbusProxy(systeminterface);
    cleaner_widget->setToolKits(toolKits);
    cleaner_widget->setParentWindow(this);
    cleaner_widget->initUI(last_skin_path);
    connect(cleaner_action_widget, SIGNAL(showDetailData()),cleaner_widget, SLOT(displayDetailPage()));
    connect(cleaner_action_widget, SIGNAL(showMainData()),cleaner_widget, SLOT(displayMainPage()));
    connect(cleaner_action_widget, SIGNAL(sendCleanSignal()),cleaner_widget, SIGNAL(transCleanSignal()));
    connect(systeminterface, SIGNAL(sendCleanOverSignal()), cleaner_widget, SLOT(displayMainPage()));
    connect(systeminterface, SIGNAL(sendCleanOverSignal()), cleaner_action_widget, SLOT(displayOrgPage()));
    //kobe
    connect(systeminterface, SIGNAL(policykitCleanSignal(bool)), cleaner_action_widget, SLOT(receivePolicyKitSignal(bool)));
    connect(systeminterface, SIGNAL(sendCleanOverSignal()), cleaner_action_widget, SLOT(showCleanOverStatus()));
    connect(systeminterface, SIGNAL(tellCleanerMainData(QStringList)), cleaner_action_widget, SLOT(showCleanerData(QStringList)));
    connect(systeminterface, SIGNAL(tellCleanerMainStatus(QString, QString)), cleaner_action_widget, SLOT(showCleanerStatus(QString, QString)));
    connect(systeminterface, SIGNAL(sendCleanErrorSignal(QString)), cleaner_action_widget, SLOT(showCleanerError(QString)));
    connect(sessioninterface, SIGNAL(tellCleanerDetailStatus(QString)), cleaner_action_widget, SLOT(showCleanReciveStatus(QString)));
    connect(sessioninterface, SIGNAL(tellCleanerDetailError(QString)), cleaner_action_widget, SLOT(showCleanReciveError(QString)));


    connect(cleaner_action_widget, SIGNAL(sendScanSignal()),cleaner_widget, SIGNAL(transScanSignal()));
    connect(cleaner_widget, SIGNAL(tranActionAnimaitonSignal()),cleaner_action_widget, SLOT(displayAnimation()));
    connect(cleaner_widget, SIGNAL(tranScanOverSignal(bool)),cleaner_action_widget, SLOT(accordScanOverStatusToChange(bool)));
    bottomStack->addWidget(cleaner_widget);

    if(info_widget == NULL)
        info_widget = new InfoWidget(this->arch);
    info_widget->setSessionDbusProxy(sessioninterface);
    info_widget->setSystemDbusProxy(systeminterface);
    info_widget->initUI(this->battery);
    bottomStack->addWidget(info_widget);

    if(setting_widget == NULL)
        setting_widget = new SettingWidget(this->desktop, this->battery);
    setting_widget->setParentWindow(this);
    setting_widget->setSessionDbusProxy(sessioninterface);
    setting_widget->setSystemDbusProxy(systeminterface);
    setting_widget->initUI(last_skin_path);
    connect(setting_widget, SIGNAL(changeActionPage(int)), setting_action_widget, SLOT(displayActionSubPage(int)));
    connect(setting_action_widget, SIGNAL(notifyContentPageToMain()), setting_widget, SLOT(displaySettingHomePage()));
    bottomStack->addWidget(setting_widget);

    if(box_widget == NULL)
        box_widget = new BoxWidget(this, this->arch, this->osName, getAppDirectory());
    box_widget->setSessionDbusProxy(sessioninterface);
    connect(box_widget, SIGNAL(sendSubIndex(int)), this, SLOT(displaySubPage(int)));
    bottomStack->addWidget(box_widget);
}

int MainWindow::getCurrentBackgroundIndex()
{
    int index = 1;
    mSettings->beginGroup("Background");
    QString cur_skin_path = mSettings->value("Path").toString();
    if(!cur_skin_path.isEmpty()) {
        int  start_pos = cur_skin_path.lastIndexOf("/") + 1;
        int end_pos = cur_skin_path.length();
        index = cur_skin_path.mid(start_pos, end_pos-start_pos).replace(".png", "").toInt();
    }
    mSettings->endGroup();
    mSettings->sync();
    return index;
}

QString MainWindow::getCurrentBackgroundName()
{
    QString cur_skin_path;
    mSettings->beginGroup("Background");
    cur_skin_path = mSettings->value("Path").toString();
    if(!cur_skin_path.isEmpty()) {
        int  start_pos = cur_skin_path.lastIndexOf("/") + 1;
        int end_pos = cur_skin_path.length();
        cur_skin_path = cur_skin_path.mid(start_pos, end_pos-start_pos);
    }
    mSettings->endGroup();
    mSettings->sync();
    return cur_skin_path;
}

QString MainWindow::getCurrentBackgroundAbsName()
{
    QString cur_skin_path;
    mSettings->beginGroup("Background");
    cur_skin_path = mSettings->value("Path").toString();
    mSettings->endGroup();
    mSettings->sync();
    return cur_skin_path;
}

void MainWindow::restoreSkin()
{
  if (main_skin_pixmap.isDetached())
  {
    main_skin_pixmap.detach();
  }
  main_skin_pixmap.load(last_skin_path);
  QPalette palette_back;
  palette_back.setBrush(QPalette::Background, main_skin_pixmap);
  default_action_widget->setPalette(palette_back);
  other_action_widget->setPalette(palette_back);
}


void MainWindow::changeSkin(QString pciture)
{
    if (main_skin_pixmap.isDetached())
    {
        main_skin_pixmap.detach();
    }
    last_skin_path = pciture;
    main_skin_pixmap.load(pciture);
    QPalette palette;
    palette.setBrush(QPalette::Background, main_skin_pixmap);
    default_action_widget->setPalette(palette);
    other_action_widget->setPalette(palette);

    mSettings->beginGroup("Background");
    mSettings->setValue("Path", pciture);
    mSettings->endGroup();
    mSettings->sync();

    if(auto_start != NULL) {
        auto_start->resetTitleSkin(last_skin_path);
    }
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
    }
    if(upgrade_dialog != NULL) {
        upgrade_dialog->resetTitleSkin(last_skin_path);
    }
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
    default_action_widget->setPalette(palette_back);
    other_action_widget->setPalette(palette_back);
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
    default_action_widget->setPalette(palette_back);
    other_action_widget->setPalette(palette_back);
}

void MainWindow::showMainMenu() {
    if (this->arch == "aarch64" || this->osName == "Kylin")
    {
        QPoint p = rect().topRight();
        p.setX(p.x() - 180);
        p.setY(p.y() + 22);
        main_menu->exec(this->mapToGlobal(p));
    }
    else
    {
        QPoint p = rect().topLeft();
        p.setX(p.x() + 107);//104
        p.setY(p.y() + 22);
        main_menu->exec(this->mapToGlobal(p));
    }

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
    if(index == 0)
    {
        if (this->arch == "aarch64" || this->osName == "Kylin")
            login_widget->hide();
        if (status != HOMEPAGE) {
            statusFlag = true;
            shadow_widget->show();
            tool_widget->hide();
            if(title_widget->isVisible())
                title_widget->hide();
            if (this->arch != "aarch64" && this->osName == "Kylin" && login_widget->isVisible())
            {
                login_widget->hide();
            }
            gatherGroup->start();
            status = HOMEPAGE;
        }
        else
            statusFlag = false;
    }
    else if(index == 1)
    {
        if (this->arch == "aarch64" || this->osName == "Kylin")
            login_widget->hide();
        if (status == HOMEPAGE) {
            statusFlag = true;
        }
        else {
            statusFlag = false;
        }
        if (status != CLEANPAGE && statusFlag) {
            shadow_widget->show();
            tool_widget->hide();
            if(title_widget->isVisible())
                title_widget->hide();
            if (this->arch != "aarch64" && this->osName != "Kylin" && login_widget->isVisible()) {
                login_widget->hide();
            }
//            topStack->setCurrentIndex(0);
//            bottomStack->setCurrentIndex(0);
            topStack->setCurrentWidget(cleaner_action_widget);
            bottomStack->setCurrentWidget(cleaner_widget);
            spreadGroup->start();
            status = CLEANPAGE;
        }
        else {
            if (this->arch != "aarch64" && this->osName != "Kylin" && login_widget->isVisible()) {
                login_widget->hide();
            }
//            topStack->setCurrentIndex(0);
//            bottomStack->setCurrentIndex(0);
            topStack->setCurrentWidget(cleaner_action_widget);
            bottomStack->setCurrentWidget(cleaner_widget);
        }
    }
    else if(index == 2)
    {
        if (this->arch == "aarch64" || this->osName == "Kylin")
            login_widget->hide();
        if (status == HOMEPAGE) {
            statusFlag = true;
        }
        else {
            statusFlag = false;
        }
        if (status != INFOPAGE && statusFlag) {
            shadow_widget->show();
            tool_widget->hide();
            if(title_widget->isVisible())
                title_widget->hide();
            if (this->arch != "aarch64" && this->osName != "Kylin" && login_widget->isVisible()) {
                login_widget->hide();
            }
//            topStack->setCurrentIndex(1);
//            bottomStack->setCurrentIndex(1);
            topStack->setCurrentWidget(info_action_widget);
            bottomStack->setCurrentWidget(info_widget);
            spreadGroup->start();
            status = INFOPAGE;
        }
        else {
            if (this->arch != "aarch64" && this->osName != "Kylin" && login_widget->isVisible()) {
                login_widget->hide();
            }
//            topStack->setCurrentIndex(1);
//            bottomStack->setCurrentIndex(1);
            topStack->setCurrentWidget(info_action_widget);
            bottomStack->setCurrentWidget(info_widget);
        }
    }
    else if(index == 3)
    {
        if (status == HOMEPAGE)
            statusFlag = true;
        else
            statusFlag = false;
        if (this->arch == "aarch64" || this->osName == "Kylin")
        {
            login_widget->hide();
            if (status != BOXPAGE && statusFlag) {
                shadow_widget->show();
                tool_widget->hide();
                if(title_widget->isVisible())
                    title_widget->hide();
    //            topStack->setCurrentIndex(3);
    //            bottomStack->setCurrentIndex(3);
                topStack->setCurrentWidget(box_action_widget);
                bottomStack->setCurrentWidget(box_widget);
                spreadGroup->start();
                status = BOXPAGE;
            }
            else {
    //            topStack->setCurrentIndex(3);
    //            bottomStack->setCurrentIndex(3);
                topStack->setCurrentWidget(box_action_widget);
                bottomStack->setCurrentWidget(box_widget);
            }
        }
        else
        {
            if (status != SETTINGPAGE && statusFlag) {
                shadow_widget->show();
                tool_widget->hide();
                if(title_widget->isVisible())
                    title_widget->hide();
                if (this->arch != "aarch64" && this->osName != "Kylin" && login_widget->isVisible()) {
                    login_widget->hide();
                }
    //            topStack->setCurrentIndex(2);
    //            bottomStack->setCurrentIndex(2);
                topStack->setCurrentWidget(setting_action_widget);
                bottomStack->setCurrentWidget(setting_widget);
                spreadGroup->start();
                status = SETTINGPAGE;
            }
            else {
                if (this->arch != "aarch64" && this->osName != "Kylin" && login_widget->isVisible()) {
                    login_widget->hide();
                }
    //            topStack->setCurrentIndex(2);
    //            bottomStack->setCurrentIndex(2);
                topStack->setCurrentWidget(setting_action_widget);
                bottomStack->setCurrentWidget(setting_widget);
            }
        }
    }
    else if(index == 4)
    {
        if (this->arch != "aarch64" && this->osName != "Kylin")
        {
            if (status == HOMEPAGE)
                statusFlag = true;
            else
                statusFlag = false;
            if (status != BOXPAGE && statusFlag) {
                shadow_widget->show();
                tool_widget->hide();
                if(title_widget->isVisible())
                    title_widget->hide();
                if (login_widget->isVisible()) {
                    login_widget->hide();
                }
    //            topStack->setCurrentIndex(3);
    //            bottomStack->setCurrentIndex(3);
                topStack->setCurrentWidget(box_action_widget);
                bottomStack->setCurrentWidget(box_widget);
                spreadGroup->start();
                status = BOXPAGE;
            }
            else {
                if (login_widget->isHidden()) {
                    login_widget->show();
                }
    //            topStack->setCurrentIndex(3);
    //            bottomStack->setCurrentIndex(3);
                topStack->setCurrentWidget(box_action_widget);
                bottomStack->setCurrentWidget(box_widget);
            }
        }
    }
}

void MainWindow::initHomePage()
{
    if(home_action_widget == NULL)
    {
//        if(top_grid_layout == NULL )
        QGridLayout *home_top_grid_layout = new QGridLayout();
//        home_action_widget = new HomeActionWidget(this, mSettings);
        home_action_widget = new HomeActionWidget(0, mSettings);
        home_top_grid_layout->addWidget(home_action_widget,0,0);
        default_action_widget->setLayout(home_top_grid_layout);
        home_top_grid_layout->setSpacing(0);
        home_top_grid_layout->setContentsMargins(0, 0, 0, 0);
    }

    if(home_page == NULL)
    {
//        if( bottom_grid_layout == NULL )
        QGridLayout *home_bottom_grid_layout = new QGridLayout();
        home_page = new HomePage(0, version);
        connect(home_page, SIGNAL(sendSubIndex(int)), this, SLOT(displaySubPage(int)));
        home_page->setParentWindow(this);
        home_page->initUI();
        home_page->initConnect();

        home_bottom_grid_layout->addWidget(home_page,0,0);
        default_content_widget->setLayout(home_bottom_grid_layout);
        home_bottom_grid_layout->setSpacing(0);
        home_bottom_grid_layout->setContentsMargins(0, 0, 0, 0);
    }
}

void MainWindow::openSkinCenter() {
    if(skin_center == NULL) {
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
    }
}

void MainWindow::openUpgradePage(/*QStringList version_list*/)
{
    int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (334  / 2);
    int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (470  / 2);
    if(upgrade_dialog == NULL)
    {
//        upgrade_dialog = new UpgradeDialog(0, version_list.at(2), last_skin_path);
        upgrade_dialog = new UpgradeDialog(0, this->version, last_skin_path, this->arch, this->osName);//20161228
        upgrade_dialog->setSystemDbusProxy(systeminterface);
        upgrade_dialog->setSessionDbusProxy(sessioninterface);
        connect(home_page, SIGNAL(sendOpenUpgrade()), this, SLOT(openUpgradePageAgain()));
        connect(upgrade_dialog, SIGNAL(showBackendBtnSignal(bool)), home_page, SLOT(displayBackedBtn(bool)));
        connect(upgrade_dialog,SIGNAL(close_signal()), this, SLOT(closeYoukerAssistant()));
        connect(systeminterface,SIGNAL(get_fetch_signal(QString, QStringList)),upgrade_dialog,SLOT(receiveFetchSignal(QString, QStringList)));
        connect(systeminterface,SIGNAL(get_apt_signal(QString, QStringList)),upgrade_dialog,SLOT(receiveAptSignal(QString, QStringList)));
        connect(sessioninterface,SIGNAL(receive_source_list_signal(bool)),upgrade_dialog,SLOT(receiveCheckResultSignal(bool)));
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
    }
}

void MainWindow::openUpgradePageAgain()
{
    int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (334  / 2);
    int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (470  / 2);
    upgrade_dialog->move(w_x, w_y);
    upgrade_dialog->show();
    upgrade_dialog->raise();
}

void MainWindow::displaySubPage(int index)
{
    if(index == 0)
    {
        if(auto_start == NULL) {
            auto_start = new AutoStartWidget(0, sessioninterface, last_skin_path);
            connect(sessioninterface, SIGNAL(tellAutoModel(QStringList)), auto_start, SLOT(readyReciveData(QStringList)));
            connect(sessioninterface, SIGNAL(showAutoModel()), auto_start, SLOT(readyShowUI()));
            auto_start->initData();
            int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (560  / 2);
            int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (398  / 2);
            auto_start->move(w_x, w_y);
            auto_start->show();
            auto_start->raise();
        }
        else {
            int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (560  / 2);
            int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (398  / 2);
            auto_start->move(w_x, w_y);
            auto_start->show();
            auto_start->raise();
        }
    }

    else if(index == 1)
    {
        CameraManager *camera_manager = new CameraManager(0, sessioninterface, last_skin_path);
        int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (622  / 2);
        int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (480  / 2);
        camera_manager->move(w_x, w_y);
        camera_manager->exec();
//        if(camera_manager == NULL) {
//            camera_manager = new CameraManager(0, sessioninterface, last_skin_path);
//            int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (622  / 2);
//            int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (480  / 2);
//            camera_manager->move(w_x, w_y);
//            camera_manager->exec();
//        }
//        else {
//            int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (622  / 2);
//            int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (480  / 2);
//            camera_manager->move(w_x, w_y);
//            camera_manager->exec();
//        }
    }
}

void MainWindow::newFeatures()
{

}

void MainWindow::setupConfigure()
{

}

void MainWindow::aboutUs()
{
    int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (442  / 2);
    int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (326  / 2);
    if(aboutDlg == NULL)
    {
        aboutDlg = new AboutDialog(0, version, last_skin_path, this->arch, this->osName);
        aboutDlg->move(w_x, w_y);
        aboutDlg->show();
        aboutDlg->raise();
    }
    else {
        aboutDlg->move(w_x, w_y);
        aboutDlg->show();
        aboutDlg->raise();
    }
}


void MainWindow::mousePressEvent(QMouseEvent *event)
{
//    if(event->button() == Qt::LeftButton)
//    {
//        mouse_press = true;
//        drag_pos = event->globalPos() - this->frameGeometry().topLeft();
//        event->accept();
//    }
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
    }
    drag_pos = event->globalPos() - pos();
}

void MainWindow::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
    setWindowOpacity(1);
}

void MainWindow::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - drag_pos);
        setWindowOpacity(0.9);
//        event->accept();
    }
}

//void MainWindow::paintEvent(QPaintEvent *event)
//{
//    QPainterPath path;
//    path.setFillRule(Qt::WindingFill);
//    path.addRect(10, 10, this->width()-20, this->height()-20);

//    QPainter painter(this);
//    painter.setRenderHint(QPainter::Antialiasing, true);
//    painter.fillPath(path, QBrush(Qt::white));

//    QColor color(0, 0, 0, 50);
//    for(int i=0; i<10; i++)
//    {
//        QPainterPath path;
//        path.setFillRule(Qt::WindingFill);
//        path.addRect(10-i, 10-i, this->width()-(10-i)*2, this->height()-(10-i)*2);
//        color.setAlpha(150 - qSqrt(i)*50);
//        painter.setPen(color);
//        painter.drawPath(path);
//    }
//}
