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
#include <QPainter>
#include <QDesktopWidget>
#include <QDebug>
#include <QBitmap>

//#include "../dbusproxy/youkersessiondbus.h"
//#include "../dbusproxy/youkersystemdbus.h"
#include "../component/utils.h"

QPoint widgetPosition;//界面中心位置的全局变量

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), skin_center(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->resize(900, 600);
//    this->setMouseTracking(true);
//    ui->centralWidget->setMouseTracking(true);
    this->setWindowOpacity(1);
//    setMouseTracking(true);
    this->setAutoFillBackground(true);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);

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
//    QPalette palette_back;
//    last_skin_path = ":/background/res/skin/1.png";
//    palette_back.setBrush(QPalette::Background, QBrush(QPixmap(last_skin_path)));
//    main_skin_pixmap.load(":/background/res/skin/1.png");
//    setPalette(palette_back);

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

    system_tray = new SystemTray(this);
    connect(system_tray, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconIsActived(QSystemTrayIcon::ActivationReason)));
    connect(system_tray, SIGNAL(showWidget()), this, SLOT(showMainWindow()));
    system_tray->show();

    title_widget = new TitleWidget(this);
    connect(title_widget, SIGNAL(closeApp()), this, SLOT(closeYoukerAssistant()));
    title_widget->setParentWindow(this);
    title_widget->initConnect();

    action_widget = new ActionWidget(this);
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
    mSettings->sync();
    if (mSettings != NULL)
    {
        delete mSettings;
        mSettings = NULL;
    }
    delete ui;
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

//void MainWindow::paintEvent(QPaintEvent *)
//{
//    widgetPosition = this->pos();
//    qDebug() << "--------"<<widgetPosition;
//    //画圆角矩形
////    QBitmap objBitmap(size());
////    QPainter painter(&objBitmap);
////    painter.fillRect(rect(),Qt::white);
////    painter.setBrush(QColor(0,0,0));
////    painter.drawRoundedRect(this->rect(),5,5);
////    setMask(objBitmap);
//}

void MainWindow::setMainWindowLayout() {
    main_layout = new QBoxLayout(QBoxLayout::TopToBottom);
    main_layout->addWidget(action_widget/*, 0, Qt::AlignTop*/);
    main_layout->addWidget(tool_widget);
    main_layout->addWidget(content_widget/*, 0, Qt::AlignBottom*/);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    title_widget->move(0, 0);
    login_widget->move(665, 0);//900 - login_widget(220) - right_align(15) = 665
    this->centralWidget()->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    this->centralWidget()->setLayout(main_layout);
}

void MainWindow::display() {
    this->setMainWindowLayout();

    if (this->isHidden()) {
        int windowWidth = QApplication::desktop()->width();
        int windowHeight = QApplication::desktop()->height();
        this->move((windowWidth - this->width()) / 2,(windowHeight - this->height()) / 2);
        this->show();
        this->raise();
        QTimer::singleShot(500, this, SLOT(startDbusDaemon()));
    }
    else {
        this->hide();
    }
}

void MainWindow::startDbusDaemon()
{
//    systemproxy(this),
    sessioninterface = new SessionDispatcher(this);
    systeminterface = new SystemDispatcher(this);



    login_widget->setSessionDbusProxy(sessioninterface);
    sessioninterface->check_user_qt();
    connect(sessioninterface, SIGNAL(ssoSuccessSignal(QString, QString)), login_widget, SLOT(showLoginInfo(QString,QString)));
    connect(sessioninterface, SIGNAL(ssoLoginLogoutSignal(bool)), login_widget, SLOT(showLoginAndLogoutStatus(bool)));

    //    home_action_widget->setParentWindow(this);
    home_action_widget->setSessionDbusProxy(sessioninterface);
    home_action_widget->setSystemDbusProxy(systeminterface);
    home_action_widget->enableSanButton();
    connect(sessioninterface, SIGNAL(isScanning(QString)), home_action_widget, SLOT(getScanResult(QString)));
    connect(sessioninterface, SIGNAL(finishScanWork(QString)), home_action_widget, SLOT(finishScanResult(QString)));
    connect(sessioninterface, SIGNAL(tellScanResultToQML(QString,QString)) ,home_action_widget, SLOT(getScanAllResult(QString,QString)));
    connect(systeminterface, SIGNAL(finishCleanWorkMain(QString/*, QString*/)), home_action_widget, SLOT(getCleanResult(QString/*, QString*/)));
    connect(systeminterface, SIGNAL(finishCleanWorkMainError(QString)), home_action_widget, SLOT(finishCleanError(QString)));
    connect(systeminterface, SIGNAL(quickCleanProcess(QString,QString)), home_action_widget, SLOT(getCleaningMessage(QString,QString)));
    home_page->setSessionDbusProxy(sessioninterface);
}

void MainWindow::initSkinCenter() {
//    skin_center.setBackGround(last_skin_path);
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

void MainWindow::showMainMenu() {
    QPoint p = rect().topLeft();
    p.setX(p.x() + 104);
    p.setY(p.y() + 22);
    main_menu->exec(this->mapToGlobal(p));
}

void MainWindow::closeYoukerAssistant() {
    qApp->exit();
}

void MainWindow::setCurrentPageIndex(int index)
{
    if(index == 0)
    {
        this->showHomePage();
    }
    else if(index == 1)
    {
        this->showClearWidget();
    }
    else if(index == 2)
    {
        this->showInfoWidget();
    }
    else if(index == 3)
    {
        this->showSettingWidget();
    }
    else if(index == 4)
    {
        this->showBoxWidget();
    }
}

void MainWindow::showHomePage()
{
    if(login_widget->isHidden())
        login_widget->show();
    if(home_action_widget == NULL)
    {
//        qDebug() << "new home action.....";
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
//        qDebug() << "show home.....";
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
//        qDebug() << "new home.....";
        if( bottom_grid_layout == NULL )
            bottom_grid_layout = new QGridLayout();
        home_page = new HomePage();
        home_page->setParentWindow(this);
        home_page->initUI();
        home_page->initConnect();

        bottom_grid_layout->addWidget(home_page,0,0);
        content_widget->setLayout(bottom_grid_layout);
//        this->content_widget->setLayout(bottom_grid_layout);
        bottom_grid_layout->setSpacing(0);
        bottom_grid_layout->setContentsMargins(0, 0, 0, 0);
//        connect(m_formFileSec,SIGNAL(push()),this,SLOT(searchlist()));
    }
    else
    {
//        qDebug() << "show home.....";
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
//        qDebug() << "new info action.....";
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
//        qDebug() << "show info action.....";
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
//        qDebug() << "new info.....";
        if( bottom_grid_layout == NULL )
            bottom_grid_layout = new QGridLayout();
        info_widget = new InfoWidget();
        info_widget->setSessionDbusProxy(sessioninterface);
        info_widget->setSystemDbusProxy(systeminterface);
        info_widget->initUI();
        bottom_grid_layout->addWidget(info_widget,0,0);
        content_widget->setLayout(bottom_grid_layout);
//        this->content_widget->setLayout(bottom_grid_layout);
        bottom_grid_layout->setSpacing(0);
        bottom_grid_layout->setContentsMargins(0, 0, 0, 0);

//        connect(m_formFileSec,SIGNAL(push()),this,SLOT(searchlist()));
    }
    else
    {
//        qDebug() << "show info.....";
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
        connect(systeminterface, SIGNAL(sendCleanOverSignal()), cleaner_action_widget, SLOT(showCleanOverStatus()));
        connect(sessioninterface, SIGNAL(tellCleanerDetailStatus(QString)), cleaner_action_widget, SLOT(showReciveStatus(QString)));
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
        cleaner_widget->setParentWindow(this);
        cleaner_widget->initUI();
        connect(cleaner_action_widget, SIGNAL(showDetailData()),cleaner_widget, SLOT(displayDetailPage()));
        connect(cleaner_action_widget, SIGNAL(showMainData()),cleaner_widget, SLOT(displayMainPage()));
        connect(cleaner_action_widget, SIGNAL(sendCleanSignal()),cleaner_widget, SIGNAL(transCleanSignal()));
        connect(systeminterface, SIGNAL(sendCleanOverSignal()), cleaner_widget, SLOT(displayMainPage()));
        bottom_grid_layout->addWidget(cleaner_widget,0,0);
//        this->content_widget->setLayout(bottom_grid_layout);
        content_widget->setLayout(bottom_grid_layout);
        bottom_grid_layout->setSpacing(0);
        bottom_grid_layout->setContentsMargins(0, 0, 0, 0);
//        connect(m_formFileSec,SIGNAL(push()),this,SLOT(searchlist()));
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
        setting_action_widget = new SettingActionWidget();
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
        setting_widget = new SettingWidget();
        setting_widget->setParentWindow(this);
        setting_widget->setSessionDbusProxy(sessioninterface);
        setting_widget->setSystemDbusProxy(systeminterface);
        setting_widget->initUI();
        connect(setting_widget, SIGNAL(changeActionPage(int)), setting_action_widget, SLOT(displayActionSubPage(int)));
        connect(setting_action_widget, SIGNAL(notifyContentPageToMain()), setting_widget, SLOT(displaySettingHomePage()));
        bottom_grid_layout->addWidget(setting_widget,0,0);
//        this->content_widget->setLayout(bottom_grid_layout);
        content_widget->setLayout(bottom_grid_layout);
        bottom_grid_layout->setSpacing(0);
        bottom_grid_layout->setContentsMargins(0, 0, 0, 0);
//        connect(m_formFileSec,SIGNAL(push()),this,SLOT(searchlist()));
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
//        box_widget = new BoxWidget(this, qApp->applicationDirPath());
        bottom_grid_layout->addWidget(box_widget,0,0);
        this->content_widget->setLayout(bottom_grid_layout);
        bottom_grid_layout->setSpacing(0);
        bottom_grid_layout->setContentsMargins(0, 0, 0, 0);
//        connect(m_formFileSec,SIGNAL(push()),this,SLOT(searchlist()));

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
//    qDebug() << this->frameGeometry().topLeft();
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
        aboutDlg = new AboutDialog();
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

void MainWindow::iconIsActived(QSystemTrayIcon::ActivationReason reason)
{
    switch(reason)
    {
        //点击托盘图标之后松开
    case QSystemTrayIcon::Trigger:
        {
            showMainWindow();
            break;
        }
        //双击托盘图标
    case QSystemTrayIcon::DoubleClick:
        {
            showMainWindow();
            break;
        }
    default:
        break;
    }
}

void MainWindow::showMainWindow()
{
    this->showNormal();
    this->raise();
    this->activateWindow();
}
