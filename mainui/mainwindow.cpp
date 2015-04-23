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
#include "ui_mainwindow.h"
#include <QDebug>
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), skin_center(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(900, 600);
    this->setWindowTitle(tr("Youker Assistant"));
    this->setWindowIcon(QIcon(":/res/youker-assistant.png"));
    this->setWindowOpacity(1);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
    this->setStyleSheet("QMainWindow{border: 1px solid gray;border-radius:2px}");

    version = "V2.0.3";

    mSettings = new QSettings(YOUKER_COMPANY_SETTING, YOUKER_SETTING_FILE_NAME_SETTING);
    mSettings->setIniCodec("UTF-8");

    mSettings->beginGroup("Background");
    last_skin_path = mSettings->value("Path").toString();
    if(last_skin_path.isEmpty()) {
        last_skin_path = ":/background/res/skin/1.png";
        mSettings->setValue("Path", last_skin_path);
    }
    mSettings->endGroup();
    mSettings->sync();
    main_skin_pixmap.load(last_skin_path);

    initSkinCenter();

    home_page = NULL;
    info_widget = NULL;
    cleaner_widget = NULL;
    setting_widget = NULL;
    box_widget = NULL;
    aboutDlg = NULL;

    home_action_widget = NULL;
    info_action_widget = NULL;
    cleaner_action_widget = NULL;
    setting_action_widget = NULL;
    box_action_widget = NULL;

    toolKits = new Toolkits(0, this->width(), this->height());

    title_widget = new TitleWidget(this);
    connect(title_widget, SIGNAL(closeApp()), this, SLOT(closeYoukerAssistant()));
    title_widget->setParentWindow(this);
    title_widget->initConnect();

    action_widget = new ActionWidget(this);
    //设置在最底层，方便title_widget的显示
//    action_widget->lower();
    QPalette palette_back;
    palette_back.setBrush(QPalette::Background, QBrush(QPixmap(last_skin_path)));
    action_widget->setPalette(palette_back);

    tool_widget = new ToolWidget(this);
    tool_widget->setParentWindow(this);
    connect(this, SIGNAL(chanegBoxToolStatus()), tool_widget, SLOT(showBoxTool()));
    tool_widget->initConnect();
    login_widget = new LoginWidget(this);

    content_widget = new ContentWidget(this);
    top_grid_layout = NULL;
    bottom_grid_layout = NULL;

    main_menu = new KylinMenu(this);

    main_menu->setParentWindow(this);
    main_menu->initConnect();

    this->showHomePage();
//    this->initAnimation();
}

MainWindow::~MainWindow()
{
    if (main_layout != NULL)
    {
        delete main_layout;
        main_layout = NULL;
    }
    if (top_grid_layout != NULL)
    {
        delete top_grid_layout;
        top_grid_layout = NULL;
    }
    if (bottom_grid_layout != NULL)
    {
        delete bottom_grid_layout;
        bottom_grid_layout = NULL;
    }
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
    if (main_menu != NULL)
    {
        delete main_menu;
        main_menu = NULL;
    }
    if (home_action_widget != NULL)
    {
        delete home_action_widget;
        home_action_widget = NULL;
    }
    if (info_action_widget != NULL)
    {
        delete info_action_widget;
        info_action_widget = NULL;
    }
    if (cleaner_action_widget != NULL)
    {
        delete cleaner_action_widget;
        cleaner_action_widget = NULL;
    }
    if (setting_action_widget != NULL)
    {
        delete setting_action_widget;
        setting_action_widget = NULL;
    }
    if (box_action_widget != NULL)
    {
        delete box_action_widget;
        box_action_widget = NULL;
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
    mSettings->sync();
    if (mSettings != NULL)
    {
        delete mSettings;
        mSettings = NULL;
    }
    delete ui;
}


//void MainWindow::initAnimation()
//{
//    QRect mainAcitonRect(0, 0, 900, 150);
//    QRect origAcitonRect(0, 0, 900, 227);
//    QPoint origPoint(0, 227);
//    QPoint needPoint(0, 150);
//    QRect mainContentRect(0, 197, 900, 403);
//    QRect origContentRect(0, 274, 900, 326);

//    QPropertyAnimation *mainActionAnimation = new QPropertyAnimation(action_widget, "geometry");
//    mainActionAnimation->setDuration(1000);
//    mainActionAnimation->setStartValue(origAcitonRect);
//    mainActionAnimation->setEndValue(mainAcitonRect);

//    QPropertyAnimation *mainToolAnimation = new QPropertyAnimation(tool_widget, "pos");
//    mainToolAnimation->setDuration(200);
//    mainToolAnimation->setStartValue(origPoint);
//    mainToolAnimation->setEndValue(needPoint);

//    QPropertyAnimation *mainContentAnimation = new QPropertyAnimation(content_widget, "geometry");
//    mainContentAnimation->setDuration(500);
//    mainContentAnimation->setStartValue(origContentRect);
//    mainContentAnimation->setEndValue(mainContentRect);

//    openGroup = new QParallelAnimationGroup(this);
//    openGroup->addAnimation(mainActionAnimation);
//    openGroup->addAnimation(mainToolAnimation);
//    openGroup->addAnimation(mainContentAnimation);

//    QPropertyAnimation *mainActionBackAnimation = new QPropertyAnimation(action_widget, "geometry");
//    mainActionBackAnimation->setDuration(1000);
//    mainActionBackAnimation->setStartValue(mainAcitonRect);
//    mainActionBackAnimation->setEndValue(origAcitonRect);

//    QPropertyAnimation *mainToolBackAnimation = new QPropertyAnimation(tool_widget, "pos");
//    mainToolBackAnimation->setDuration(200);
//    mainToolBackAnimation->setStartValue(needPoint);
//    mainToolBackAnimation->setEndValue(origPoint);

//    QPropertyAnimation *mainContentBackAnimation = new QPropertyAnimation(content_widget, "geometry");
//    mainContentBackAnimation->setDuration(500);
//    mainContentBackAnimation->setStartValue(mainContentRect);
//    mainContentBackAnimation->setEndValue(origContentRect);

//    closeGroup = new QParallelAnimationGroup(this);
//    closeGroup->addAnimation(mainActionBackAnimation);
//    closeGroup->addAnimation(mainToolBackAnimation);
//    closeGroup->addAnimation(mainContentBackAnimation);
//}

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
//	content_widget->translateLanguage();
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

void MainWindow::setMainWindowLayout() {
//    main_layout = NULL;
    main_layout = new QBoxLayout(QBoxLayout::TopToBottom);
    main_layout->addWidget(action_widget/*, 0, Qt::AlignTop*/);
    main_layout->addWidget(tool_widget);
    main_layout->addWidget(content_widget/*, 0, Qt::AlignBottom*/);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    title_widget->move(0, 0);
//    title_widget->show();
    login_widget->move(585, 0);//900 - login_widget(220) - right_align(15) = 665
    this->centralWidget()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->centralWidget()->setLayout(main_layout);
}

void MainWindow::display() {
    this->setMainWindowLayout();

//    QPropertyAnimation *animation = new QPropertyAnimation(this, "windowOpacity");
//    animation->setDuration(500);
//    animation->setStartValue(0);
//    animation->setEndValue(1);
//    animation->start();

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

void MainWindow::startDbusDaemon()
{
    sessioninterface = new SessionDispatcher(this);
    systeminterface = new SystemDispatcher(this);
    this->desktop = sessioninterface->access_current_desktop_qt();
    login_widget->setSessionDbusProxy(sessioninterface);
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
}

void MainWindow::initSkinCenter() {
    skin_center.initTitleBar(last_skin_path);
    skin_center.setParentWindow(this);
    skin_center.initBackgroundList();
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
  action_widget->setPalette(palette_back);
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
    action_widget->setPalette(palette);

    mSettings->beginGroup("Background");
    mSettings->setValue("Path", pciture);
    mSettings->endGroup();
    mSettings->sync();
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
  action_widget->setPalette(palette_back);
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
  action_widget->setPalette(palette_back);
}

void MainWindow::showMainMenu() {
    QPoint p = rect().topLeft();
    p.setX(p.x() + 104);
    p.setY(p.y() + 22);
    main_menu->exec(this->mapToGlobal(p));
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
//        closeGroup->start();
        this->showHomePage();
    }
    else if(index == 1)
    {
//        openGroup->start();
        this->showClearWidget();
    }
    else if(index == 2)
    {
//        openGroup->start();
        this->showInfoWidget();
    }
    else if(index == 3)
    {
//        openGroup->start();
        this->showSettingWidget();
    }
    else if(index == 4)
    {
//        openGroup->start();
        this->showBoxWidget();
    }
}

void MainWindow::showHomePage()
{
    if(login_widget->isHidden())
        login_widget->show();
    if(home_action_widget == NULL)
    {
        if(top_grid_layout == NULL )
            top_grid_layout = new QGridLayout();
        home_action_widget = new HomeActionWidget(this, mSettings);
        top_grid_layout->addWidget(home_action_widget,0,0);
        action_widget->setLayout(top_grid_layout);
        top_grid_layout->setSpacing(0);
        top_grid_layout->setContentsMargins(0, 0, 0, 0);
    }
    else
    {
        home_action_widget->show();
    }
    if(info_action_widget != NULL)
    {
        info_action_widget->hide();
    }
    if(cleaner_action_widget != NULL)
    {
        cleaner_action_widget->hide();
    }
    if(setting_action_widget != NULL)
    {
        setting_action_widget->hide();
    }
    if(box_action_widget != NULL)
    {
        box_action_widget->hide();
    }

    if(home_page == NULL)
    {
        if( bottom_grid_layout == NULL )
            bottom_grid_layout = new QGridLayout();
        home_page = new HomePage(0, version);
        home_page->setParentWindow(this);
        home_page->initUI();
        home_page->initConnect();

        bottom_grid_layout->addWidget(home_page,0,0);
        content_widget->setLayout(bottom_grid_layout);
        bottom_grid_layout->setSpacing(0);
        bottom_grid_layout->setContentsMargins(0, 0, 0, 0);
    }
    else
    {
        home_page->show();
    }
    action_widget->setFixedSize(900, 227);
    content_widget->setFixedSize(900, 326);
    if (info_widget != NULL)
    {
        info_widget->hide();
    }
    if (cleaner_widget != NULL)
    {
        cleaner_widget->hide();
    }
    if (setting_widget != NULL)
    {
        setting_widget->hide();
    }
    if (box_widget != NULL)
    {
        box_widget->hide();
    }
}

void MainWindow::showInfoWidget()
{
    if(login_widget->isVisible())
        login_widget->hide();
    if(info_action_widget == NULL)
    {
        if(top_grid_layout == NULL )
            top_grid_layout = new QGridLayout();
        info_action_widget = new InfoActionWidget();
        top_grid_layout->addWidget(info_action_widget,0,0);
        action_widget->setLayout(top_grid_layout);
        top_grid_layout->setSpacing(0);
        top_grid_layout->setContentsMargins(0, 0, 0, 0);
    }
    else
    {
        info_action_widget->show();
    }
    if(home_action_widget != NULL)
    {
        home_action_widget->hide();
    }
    if(cleaner_action_widget != NULL)
    {
        cleaner_action_widget->hide();
    }
    if(setting_action_widget != NULL)
    {
        setting_action_widget->hide();
    }
    if(box_action_widget != NULL)
    {
        box_action_widget->hide();
    }


    if(info_widget == NULL)
    {
        if( bottom_grid_layout == NULL )
            bottom_grid_layout = new QGridLayout();
        info_widget = new InfoWidget();
        info_widget->setSessionDbusProxy(sessioninterface);
        info_widget->setSystemDbusProxy(systeminterface);
        info_widget->initUI();
        bottom_grid_layout->addWidget(info_widget,0,0);
        content_widget->setLayout(bottom_grid_layout);
        bottom_grid_layout->setSpacing(0);
        bottom_grid_layout->setContentsMargins(0, 0, 0, 0);
    }
    else
    {
        info_widget->show();
    }
    action_widget->setFixedSize(900, 150);
    content_widget->setFixedSize(900, 403);
    if (home_page != NULL)
    {
        home_page->hide();
    }
    if (cleaner_widget != NULL)
    {
        cleaner_widget->hide();
    }
    if (setting_widget != NULL)
    {
        setting_widget->hide();
    }
    if (box_widget != NULL)
    {
        box_widget->hide();
    }
}


void MainWindow::showClearWidget()
{
    if(login_widget->isVisible())
        login_widget->hide();
    if(cleaner_action_widget == NULL)
    {
        if(top_grid_layout == NULL )
            top_grid_layout = new QGridLayout();
        cleaner_action_widget = new CleanerActionWidget();
        cleaner_action_widget->setSessionDbusProxy(sessioninterface);
        cleaner_action_widget->setSystemDbusProxy(systeminterface);

        connect(systeminterface, SIGNAL(policykitCleanSignal(bool)), cleaner_action_widget, SLOT(receivePolicyKitSignal(bool)));
        connect(systeminterface, SIGNAL(sendCleanOverSignal()), cleaner_action_widget, SLOT(showCleanOverStatus()));
        connect(systeminterface, SIGNAL(tellCleanerMainData(QStringList)), cleaner_action_widget, SLOT(showCleanerData(QStringList)));
        connect(systeminterface, SIGNAL(tellCleanerMainStatus(QString, QString)), cleaner_action_widget, SLOT(showCleanerStatus(QString, QString)));
        connect(systeminterface, SIGNAL(sendCleanErrorSignal(QString)), cleaner_action_widget, SLOT(showCleanerError(QString)));
        connect(sessioninterface, SIGNAL(tellCleanerDetailStatus(QString)), cleaner_action_widget, SLOT(showReciveStatus(QString)));
        connect(sessioninterface, SIGNAL(tellCleanerDetailError(QString)), cleaner_action_widget, SLOT(showReciveError(QString)));
        top_grid_layout->addWidget(cleaner_action_widget,0,0);
        action_widget->setLayout(top_grid_layout);
        top_grid_layout->setSpacing(0);
        top_grid_layout->setContentsMargins(0, 0, 0, 0);
    }
    else
    {
        cleaner_action_widget->show();
    }
    if(home_action_widget != NULL)
    {
        home_action_widget->hide();
    }
    if(info_action_widget != NULL)
    {
        info_action_widget->hide();
    }
    if(setting_action_widget != NULL)
    {
        setting_action_widget->hide();
    }
    if(box_action_widget != NULL)
    {
        box_action_widget->hide();
    }

    if(cleaner_widget == NULL)
    {
        if( bottom_grid_layout == NULL )
            bottom_grid_layout = new QGridLayout();
        cleaner_widget = new CleanerWidget();
        cleaner_widget->setSessionDbusProxy(sessioninterface);
        cleaner_widget->setSystemDbusProxy(systeminterface);
        cleaner_widget->setToolKits(toolKits);
        cleaner_widget->setParentWindow(this);
        cleaner_widget->initUI();
        connect(cleaner_action_widget, SIGNAL(showDetailData()),cleaner_widget, SLOT(displayDetailPage()));
        connect(cleaner_action_widget, SIGNAL(showMainData()),cleaner_widget, SLOT(displayMainPage()));
        connect(cleaner_action_widget, SIGNAL(sendCleanSignal()),cleaner_widget, SIGNAL(transCleanSignal()));
        connect(systeminterface, SIGNAL(sendCleanOverSignal()), cleaner_widget, SLOT(displayMainPage()));
//        connect(systeminterface, SIGNAL(policykitCleanSignal(bool)), cleaner_widget, SLOT(displayMainPage()));


        connect(cleaner_action_widget, SIGNAL(sendScanSignal()),cleaner_widget, SIGNAL(transScanSignal()));
        connect(cleaner_widget, SIGNAL(tranActionAnimaitonSignal()),cleaner_action_widget, SLOT(displayAnimation()));
//        connect(cleaner_widget, SIGNAL(tranCleanActionAnimaitonSignal()),cleaner_action_widget, SLOT(displayCleanAnimation()));

        bottom_grid_layout->addWidget(cleaner_widget,0,0);
        content_widget->setLayout(bottom_grid_layout);
        bottom_grid_layout->setSpacing(0);
        bottom_grid_layout->setContentsMargins(0, 0, 0, 0);
    }
    else
    {
        cleaner_widget->show();
    }
    action_widget->setFixedSize(900, 150);
    content_widget->setFixedSize(900, 403);
    if (home_page != NULL)
    {
        home_page->hide();
    }
    if (info_widget != NULL)
    {
        info_widget->hide();
    }
    if (setting_widget != NULL)
    {
        setting_widget->hide();
    }
    if (box_widget != NULL)
    {
        box_widget->hide();
    }
}


void MainWindow::showSettingWidget()
{
    if(login_widget->isVisible())
        login_widget->hide();
    if(setting_action_widget == NULL)
    {
        if(top_grid_layout == NULL )
            top_grid_layout = new QGridLayout();
        setting_action_widget = new SettingActionWidget(this->desktop);
        top_grid_layout->addWidget(setting_action_widget,0,0);
        action_widget->setLayout(top_grid_layout);
        top_grid_layout->setSpacing(0);
        top_grid_layout->setContentsMargins(0, 0, 0, 0);
    }
    else
    {
        setting_action_widget->show();
    }
    if(home_action_widget != NULL)
    {
        home_action_widget->hide();
    }
    if(info_action_widget != NULL)
    {
        info_action_widget->hide();
    }
    if(cleaner_action_widget != NULL)
    {
        cleaner_action_widget->hide();
    }
    if(box_action_widget != NULL)
    {
        box_action_widget->hide();
    }

    if(setting_widget == NULL)
    {
        if( bottom_grid_layout == NULL )
            bottom_grid_layout = new QGridLayout();
        setting_widget = new SettingWidget(this->desktop);
        setting_widget->setParentWindow(this);
        setting_widget->setSessionDbusProxy(sessioninterface);
        setting_widget->setSystemDbusProxy(systeminterface);
        setting_widget->initUI();
        connect(setting_widget, SIGNAL(changeActionPage(int)), setting_action_widget, SLOT(displayActionSubPage(int)));
        connect(setting_action_widget, SIGNAL(notifyContentPageToMain()), setting_widget, SLOT(displaySettingHomePage()));
        bottom_grid_layout->addWidget(setting_widget,0,0);
        content_widget->setLayout(bottom_grid_layout);
        bottom_grid_layout->setSpacing(0);
        bottom_grid_layout->setContentsMargins(0, 0, 0, 0);
    }
    else
    {
        setting_widget->show();
    }
    action_widget->setFixedSize(900, 150);
    content_widget->setFixedSize(900, 403);
    if (home_page != NULL)
    {
        home_page->hide();
    }
    if (info_widget != NULL)
    {
        info_widget->hide();
    }
    if (cleaner_widget != NULL)
    {
        cleaner_widget->hide();
    }
    if (box_widget != NULL)
    {
        box_widget->hide();
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

void MainWindow::showBoxWidget()
{
    if(login_widget->isHidden())
        login_widget->show();
    if(box_action_widget == NULL)
    {
        if(top_grid_layout == NULL )
            top_grid_layout = new QGridLayout();
        box_action_widget = new BoxActionWidget();
        top_grid_layout->addWidget(box_action_widget,0,0);
        action_widget->setLayout(top_grid_layout);
        top_grid_layout->setSpacing(0);
        top_grid_layout->setContentsMargins(0, 0, 0, 0);
    }
    else
    {
        box_action_widget->show();
    }
    if(home_action_widget != NULL)
    {
        home_action_widget->hide();
    }
    if(info_action_widget != NULL)
    {
        info_action_widget->hide();
    }
    if(cleaner_action_widget != NULL)
    {
        cleaner_action_widget->hide();
    }
    if(setting_action_widget != NULL)
    {
        setting_action_widget->hide();
    }


    if(box_widget == NULL)
    {
        if( bottom_grid_layout == NULL )
            bottom_grid_layout = new QGridLayout();
        box_widget = new BoxWidget(this, getAppDirectory());
        box_widget->setSessionDbusProxy(sessioninterface);
//        box_widget = new BoxWidget(this, qApp->applicationDirPath());
        bottom_grid_layout->addWidget(box_widget,0,0);
        this->content_widget->setLayout(bottom_grid_layout);
        bottom_grid_layout->setSpacing(0);
        bottom_grid_layout->setContentsMargins(0, 0, 0, 0);
    }
    else
    {
        box_widget->show();
    }
    action_widget->setFixedSize(900, 150);
    content_widget->setFixedSize(900, 403);
    if (home_page != NULL)
    {
        home_page->hide();
    }
    if (info_widget != NULL)
    {
        info_widget->hide();
    }
    if (cleaner_widget != NULL)
    {
        cleaner_widget->hide();
    }
    if (setting_widget != NULL)
    {
        setting_widget->hide();
    }
}

void MainWindow::openSkinCenter() {
    int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (500  / 2);
    int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (271  / 2);
    skin_center.move(w_x, w_y);
    skin_center.show();
    skin_center.raise();
}

void MainWindow::newFeatures()
{

}

void MainWindow::setupConfigure()
{

}

void MainWindow::aboutUs()
{
    int w_x = this->frameGeometry().topLeft().x() + (900 / 2) - (560  / 2);
    int w_y = this->frameGeometry().topLeft().y() + (600 /2) - (398  / 2);
    if(aboutDlg == NULL)
    {
        aboutDlg = new AboutDialog(0, version);
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
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
        drag_pos = event->globalPos() - this->frameGeometry().topLeft();
        event->accept();
    }
//    drag_pos = event->globalPos() - pos();
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
        event->accept();
    }
}
