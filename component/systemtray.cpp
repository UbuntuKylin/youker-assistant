#include "systemtray.h"

SystemTray::SystemTray(QWidget *parent)
    : QSystemTrayIcon(parent)
{
    this->initTrayActions();
    this->setLanguage();
}

SystemTray::~SystemTray()
{
}

void SystemTray::setLanguage()
{
    this->setToolTip(tr("Youker Assistant"));
    action_open->setText(tr("open"));
    action_open->setIcon(QIcon("://res/icon.png"));
    action_logout->setText(tr("logout"));
}

void SystemTray::initTrayActions()
{
    this->setIcon(QIcon("://res/icon.png"));
    tray_menu = new QMenu();
//    tray_menu->setObjectName("mainmenu");
    tray_menu->setStyleSheet("QMenu{background-color: red;border: 1px solid gray;color: #4f4f4f;padding: 1px;}");
    action_open = new QAction(this);
    action_logout = new QAction(this);

    tray_menu->setFixedWidth(250);

    connect(action_open, SIGNAL(triggered()), this, SIGNAL(showWidget()));
    connect(action_logout, SIGNAL(triggered()), qApp, SLOT(quit()));

    this->setContextMenu(tray_menu);

    tray_menu->addAction(action_open);
    tray_menu->addSeparator();
    tray_menu->addAction(action_logout);
}
