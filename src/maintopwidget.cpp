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

#include "maintopwidget.h"
#include "mainwindow.h"
#include <QDebug>
#include <QDateTime>


#include "../plugins/widgets/mytristatebutton.h"


#include <QApplication>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QResizeEvent>
#include <QStyleFactory>


MainTopWidget::MainTopWidget(bool isMain, QSettings *mSettings, QWidget *parent)
    : QWidget(parent)
    , pSettings(mSettings)
    , m_isMain(isMain)
//    , p_mainwindow(parent)
{
//    p_mainwindow = static_cast<MainWindow *>(parent);

    if (m_isMain)
        this->setFixedSize(900, 227);
    else
        this->setFixedSize(900, 150);

    this->setAutoFillBackground(true);
//    this->setObjectName("transparentWidget");
    scanFinishTime = "";

    this->initWidgets();


    this->initConnect();
    this->setLanguage();


    if (m_isMain) {
        workFlag = this->getOneKeyFlag();
        if(workFlag.length() > 0)
        {
            if(workFlag == "1")
            {
                //clean
                dateStr = this->getFixCleanDate();
                result_label->setText(tr("The lastest cleanup time is ") + dateStr);
            }
            else if(workFlag == "0")
            {
                //scan
                dateStr = this->getSafeScanDate();
                result_label->setText(tr("The lastest scan time is ") + dateStr);
            }
        }
        else {
            result_label->setText(tr("You have not implemented the one key scan and clean-up operation."));
        }
    }
}

MainTopWidget::~MainTopWidget()
{
    if(loading_label) {
        delete loading_label;
        loading_label = nullptr;
    }
    if(suggest_label) {
        delete suggest_label;
        suggest_label = nullptr;
    }
    if(scan_result_label) {
        delete scan_result_label;
        scan_result_label = nullptr;
    }
    if(result_label) {
        delete result_label;
        result_label = nullptr;
    }
    if(doing_label) {
        delete doing_label;
        doing_label = nullptr;
    }

    delete scan_button;
    delete clean_button;
    delete back_button;

    //Segmentation fault
    QLayoutItem *child;
    while ((child = m_titleLeftLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_titleRightLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_toolLeftLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_toolRightLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_topLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_bottomLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    delete m_layout;
}

void MainTopWidget::initTitlebarLeftContent()
{
    QWidget *w = new QWidget;
    m_titleLeftLayout = new QHBoxLayout(w);
    m_titleLeftLayout->setContentsMargins(6, 0, 0, 0);
    m_titleLeftLayout->setSpacing(0);

    QLabel *appLabel = new QLabel;
    appLabel->setStyleSheet("QLabel{background-color:transparent;color:#ffffff; font-size:12px;}");
    appLabel->setText(tr("Kylin Assistant"));
    m_titleLeftLayout->addWidget(appLabel);

    m_topLayout->addWidget(w, 1, Qt::AlignLeft);
}

void MainTopWidget::initTitlebarRightContent()
{
    QWidget *w = new QWidget;
    m_titleRightLayout = new QHBoxLayout(w);
    m_titleRightLayout->setContentsMargins(0, 0, 1, 0);
    m_titleRightLayout->setSpacing(0);

    m_topLayout->addWidget(w, 1, Qt::AlignRight);

    SystemButton *min_button = new SystemButton();
    SystemButton *close_button = new SystemButton();
//    SystemButton *skin_button = new SystemButton();
    SystemButton *main_menu_button = new SystemButton();
    min_button->loadPixmap(":/sys/res/sysBtn/min_button.png");
    close_button->loadPixmap(":/sys/res/sysBtn/close_button.png");
//    skin_button->loadPixmap(":/sys/res/sysBtn/skin_button.png");
    main_menu_button->loadPixmap(":/sys/res/sysBtn/main_menu.png");
    min_button->setFocusPolicy(Qt::NoFocus);
    close_button->setFocusPolicy(Qt::NoFocus);
//    skin_button->setFocusPolicy(Qt::NoFocus);
    main_menu_button->setFocusPolicy(Qt::NoFocus);

    m_titleRightLayout->addWidget(main_menu_button);
//    m_titleRightLayout->addWidget(skin_button);
    m_titleRightLayout->addWidget(min_button);
    m_titleRightLayout->addWidget(close_button);

    connect(main_menu_button, &SystemButton::clicked, this, [=] {
        emit this->showMenu();
        /*if (parentWidget()) {
            parentWidget()->showMainMenu();
        }*/
    });
//    connect(skin_button, &SystemButton::clicked, this, [=] {
//        if (parentWidget() && parentWidget()->parentWidget()) {
//            //openSkinCenter()
//        }
//    });
    connect(min_button, &SystemButton::clicked, [=] (const bool b) {
        emit this->showMin();
//        if (p_mainwindow)
//            p_mainwindow->showMinimized();
//        if (parentWidget()) {
//            parentWidget()->showMinimized();
//        }
    });
    connect(close_button, &SystemButton::clicked, this, [=] {
        emit this->closeApp();
//        window()->close();
    });
}

void MainTopWidget::initContentLeftContent()
{
    QWidget *w = new QWidget;
    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_toolLeftLayout = new QHBoxLayout(w);
    m_toolLeftLayout->setContentsMargins(0, 0, 0, 0);
    m_toolLeftLayout->setSpacing(10);

    suggest_label = new QLabel();
    doing_label = new QLabel();
    if (m_isMain) {
        scan_result_label = new QLabel();
        result_label = new QLabel();
        loading_label = new LoadingLabel(this, "firstkey");
        scan_result_label->setObjectName("whiteLabel");
        scan_result_label->setWordWrap(true);//QLabel自动换行
        scan_result_label->setFixedWidth(460);
        scan_result_label->hide();
        result_label->setWordWrap(true);//QLabel自动换行
        result_label->setObjectName("smallWhiteLabel");
        result_label->setFixedWidth(460);
        suggest_label->setFixedWidth(460);
        doing_label->setFixedWidth(700);//460
    }
    else {
        loading_label = new LoadingLabel(this, "clean");
        suggest_label->setFixedWidth(550);
        doing_label->setFixedWidth(700);//550
    }
    loading_label->show();

    suggest_label->setObjectName("whiteLabel");
    suggest_label->setWordWrap(true);//QLabel自动换行
//    doing_label->setWordWrap(true);//QLabel自动换行
    doing_label->setObjectName("whiteLabel");
    doing_label->hide();

    QVBoxLayout *layout1 = new QVBoxLayout();
    layout1->addStretch();
    if (m_isMain) {
        layout1->addWidget(suggest_label, 0, Qt::AlignVCenter);
        layout1->addWidget(scan_result_label, 0, Qt::AlignVCenter);
        layout1->addWidget(doing_label, 0, Qt::AlignVCenter);
        layout1->addWidget(result_label, 0, Qt::AlignVCenter);
    }
    else {
        layout1->addWidget(suggest_label, 0, Qt::AlignVCenter);
        layout1->addWidget(doing_label, 0, Qt::AlignVCenter);
    }
    layout1->addStretch();
    layout1->setSpacing(15);
    layout1->setContentsMargins(0, 0, 0, 0);

    m_toolLeftLayout->addStretch();
    m_toolLeftLayout->addWidget(loading_label, 0, Qt::AlignHCenter);
    m_toolLeftLayout->addLayout(layout1);
    m_toolLeftLayout->addStretch();

//    m_bottomLayout->addWidget(w);
    m_bottomLayout->addWidget(w, 1, Qt::AlignLeft);
}

void MainTopWidget::initActionRightContent()
{
    QWidget *w = new QWidget;
    m_toolRightLayout = new QHBoxLayout(w);
    m_toolRightLayout->setContentsMargins(0, 3, 30, 10);
    m_toolRightLayout->setSpacing(5);

    scan_button = new QPushButton(this);
    clean_button = new QPushButton(this);
    back_button = new QPushButton(this);

    scan_button->setObjectName("greenButton");
    scan_button->setFocusPolicy(Qt::NoFocus);
    if (m_isMain) {
        scan_button->setFixedSize(204, 65);
        clean_button->setFixedSize(204, 65);
        QPixmap pixmap("://res/scan.png");
        scan_button->setIcon(pixmap);
        scan_button->setIconSize(pixmap.size());
    }
    else {
        scan_button->setFixedSize(182, 58);
        clean_button->setFixedSize(182, 58);
    }
    scan_button->setVisible(true);
    clean_button->setFocusPolicy(Qt::NoFocus);
    clean_button->setObjectName("greenButton");
    clean_button->setVisible(false);

    back_button->setFocusPolicy(Qt::NoFocus);
    back_button->setFixedSize(50, 30);
//    back_button->setObjectName("backButton");
    back_button->setObjectName("underlineButton");
    back_button->setVisible(false);

    m_toolRightLayout->addWidget(scan_button);
    m_toolRightLayout->addWidget(clean_button);
    m_toolRightLayout->addWidget(back_button);
    m_bottomLayout->addWidget(w, 1, Qt::AlignRight);
}

void MainTopWidget::initWidgets()
{
    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    QWidget *topWidget = new QWidget;
    m_topLayout = new QHBoxLayout(topWidget);
    m_topLayout->setContentsMargins(0, 0, 0, 0);
    m_topLayout->setSpacing(0);
    m_layout->addWidget(topWidget, 0, Qt::AlignTop);

    QWidget *bottomWidget = new QWidget;
    m_bottomLayout = new QHBoxLayout(bottomWidget);
    m_bottomLayout->setContentsMargins(13, 0, 0, 20);
    m_bottomLayout->setSpacing(0);
    m_layout->addWidget(bottomWidget, 0, Qt::AlignBottom);

    this->setLayout(m_layout);

    initTitlebarLeftContent();
    initTitlebarRightContent();
    initContentLeftContent();
    initActionRightContent();
}

void MainTopWidget::initConnect()
{
    connect(scan_button, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
    connect(clean_button, SIGNAL(clicked()), this, SLOT(onCleanButtonClicked()));
    connect(back_button, SIGNAL(clicked()), this, SLOT(onEndButtonClicked()));
}

void MainTopWidget::setLanguage()
{
    scan_button->setText(tr("Start Scan"));//开始扫描
    clean_button->setText(tr("Start Cleanup"));//开始清理
    back_button->setText(tr("Back"));
    doing_label->setText(tr("Scanning......"));//正在扫描......

    if (m_isMain) {
        suggest_label->setText(tr("Quick clean up system trash, saving disk space and improving the system efficiency!"));//一键清理系统垃圾，帮您节省磁盘空间，让系统运行更加有效率！
        scan_result_label->setText(tr("Scan Over"));
    }
    else {
        suggest_label->setText(tr("Regular cleaning, let your computer remains the relaxed state"));//经常清理，让电脑保持最轻松的状态
    }
}

//void MainTopWidget::enableSanButton()
//{
//    scan_button->setEnabled(true);
//}

void MainTopWidget::showCleanOverStatus()
{
    loading_label->stopLoading();
    scan_button->setVisible(true);
    scan_button->setEnabled(true);
    clean_button->setVisible(false);
    clean_button->setEnabled(true);
    back_button->setVisible(false);
    doing_label->setText(tr("Clean OK"));
}

void MainTopWidget::showCleanerData(const QStringList &data)
{
    if(data.length() == 2) {
        this->setDoingLabelText(tr("Cleaning: ") + data.at(0).split(":").at(1));
//        doing_label->setText(tr("Cleaning: ") + data.at(0).split(":").at(1));
    }
    else if(data.length() == 3) {
        this->setDoingLabelText(data.at(0).split(":").at(1) + tr(", Percent is: ") + data.at(1).split(":").at(1) + tr("%, Status is: ") + data.at(2).split(":").at(1));
//        doing_label->setText(data.at(0).split(":").at(1) + tr(", Percent is: ") + data.at(1).split(":").at(1) + tr("%, Status is: ") + data.at(2).split(":").at(1));
    }
}

void MainTopWidget::showCleanerStatus(const QString &status, const QString &domain)
{
    if(status == "Complete:History.firefox" && domain == "history")
    {
        doing_label->setText(tr("Clean Firefox history......"));
    }
    else if(status == "Complete:History.chromium" && domain == "history")
    {
        doing_label->setText(tr("Clean Chromium history......"));
    }
    else if(status == "Complete:History.system" && domain == "history")
    {
        doing_label->setText(tr("Clean system history......"));
    }

    else if(status == "Complete:" && domain == "apt")
    {
        doing_label->setText(tr("Clean apt......"));
    }
    else if(status == "Start:" && domain == "apt")
    {
        doing_label->setText(tr("Start clean apt......"));
    }

    else if(status == "Complete:Cookies.firefox")
    {
        doing_label->setText(tr("Clean Firefox Cookie:") + domain);
    }
    else if(status == "Complete:Cookies.chromium")
    {
        doing_label->setText(tr("Clean Chromium Cookie:") + domain);
    }
}

void MainTopWidget::showCleanerError(const QString &status)
{
    if(status.contains("Non-existent:")) {
        if(status.split(":").at(1).length() > 0) {
            this->setDoingLabelText(status.split(":").at(1) + tr(" does not exist"));
//            doing_label->setText(status.split(":").at(1) + tr(" does not exist"));
        }
    }
    else if(status.contains("Working:Chromium")) {
        doing_label->setText(tr("Chromium Browser is running......"));
    }
}

void MainTopWidget::showCleanReciveStatus(const QString &status)
{
    if(status == "Complete:Cache")
    {
        doing_label->setText(tr("Cache Scan OK"));
    }
    else if(status == "Complete:Cookies")
    {
        doing_label->setText(tr("Cookies Scan OK"));
    }
    else if(status == "Complete:")
    {
        doing_label->setText(tr("History Scan OK"));
    }
    else if(status == "Complete:Packages")
    {
        doing_label->setText(tr("Packages Scan OK"));
    }
    else if(status == "Complete:All")
    {
//        doing_label->setText(tr("Scaning......"));
//        doing_label->hide();
//        loading_label->stopLoading();
//        scan_button->hide();
//        scan_button->setEnabled(true);
//        clean_button->show();
//        clean_button->setEnabled(true);
//        suggest_label->show();
//        back_button->show();
    }
}

void MainTopWidget::accordScanOverStatusToChange(bool status)
{
    if (status) {
        doing_label->setText(tr("Scaning......"));
        doing_label->setVisible(false);
        loading_label->stopLoading();
        scan_button->setVisible(false);
        scan_button->setEnabled(true);
        clean_button->setVisible(true);
        clean_button->setEnabled(true);
        suggest_label->setVisible(true);
        back_button->setVisible(true);
    }
    else {
        doing_label->setText(tr("Scaning......"));
        doing_label->setVisible(false);
        loading_label->stopLoading();
        scan_button->setVisible(false);
        scan_button->setEnabled(true);
        clean_button->setVisible(false);
        clean_button->setEnabled(true);
        suggest_label->setVisible(true);
        back_button->setVisible(true);
    }
}

void MainTopWidget::showCleanReciveError(const QString &status)
{
    doing_label->setText(tr("Error: ") + status);
    if(status == "Uninstalled:Firefox")
    {
        doing_label->setText(tr("Firefox Browser does not be installed"));
    }
    else if(status == "Uninstalled:Chromium")
    {
        doing_label->setText(tr("Chromium Browser does not be installed"));
    }
    else if(status == "Working:Chromium")
    {
        doing_label->setText(tr("Chromium Browser is running"));
    }
    else
    {
        if(status.contains("Non-existent:")) {
            this->setDoingLabelText(status.split(":").at(1) + tr(" does not exist"));
//            doing_label->setText(status.split(":").at(1) + tr(" does not exist"));
        }
    }
}

void MainTopWidget::displayAnimation()
{
//    scan_button->setEnabled(false);
    loading_label->startLoading();
    suggest_label->setVisible(false);
    doing_label->setVisible(true);
    emit this->showDetailData();
}

void MainTopWidget::getScanResult(QString msg)
{
    this->setDoingLabelText(tr("Scanning:") + msg);
//    doing_label->setText(tr("Scanning:") + msg);//正在扫描:
}

void MainTopWidget::finishScanResult(QString msg)
{
    if(msg == "onekey") {
//        doing_label->setText(tr("Scan Over"));//扫描完成
        doing_label->hide();
        scan_result_label->show();
        result_label->show();
        QString msg;
        if (trace.toInt() > 0)
        {
            if (cookies.toInt() > 0) {
                if (garbage == "0.00 B")
                {
                    msg = trace + tr(" history trace; ") + cookies + tr(" browser cookies.") ;
                }
                else
                {
                     msg = trace + tr(" history trace; ") + cookies + tr(" browser cookies; ") + garbage + tr(" garbage.") ;
                }
            }
            else
            {
                if (garbage == "0.00 B")
                {
                    msg = trace + tr(" history trace.") ;
                }
                else
                {
                     msg = trace + tr(" history trace; ") + garbage + tr(" garbage.") ;
                }
            }
        }
        else
        {
            if (cookies.toInt() > 0)
            {
                if (garbage == "0.00 B")
                {
                    msg = cookies + tr(" browser cookies.") ;
                }
                else
                {
                     msg = cookies + tr(" browser cookies; ") + garbage + tr(" garbage.") ;
                }
            }
            else
            {
                if (garbage == "0.00 B")
                {
                    msg = "";
                }
                else
                {
                     msg = garbage + tr(" garbage.") ;
                }
            }
        }
        if (msg.isEmpty()) {
            result_label->setText(tr("No garbage."));
            scan_button->setEnabled(true);
            clean_button->setVisible(false);
        }
        else
        {
            result_label->setText(msg);
            clean_button->setVisible(true);
            clean_button->setEnabled(true);
        }
        scanFinishTime = this->getCurrentDateTime();
//        result_label->setText(tr("The lastest scan time is ") + this->getCurrentDateTime());
        this->writeSafeScanDate();
        scan_button->setVisible(false);
        back_button->setVisible(true);
        loading_label->stopLoading();
    }
}

void MainTopWidget::getScanAllResult(QString flag, QString msg){
    if(flag == "h") {
        trace = msg;
    }
    else if(flag == "k") {
        cookies = msg;
    }
    else if(flag == "c") {
        garbage = msg;
    }
}

void MainTopWidget::getCleanResult(QString msg/*, QString flag*/)
{
//    if(flag == "onekey") {
    if (msg == "yes") {//在弹出输入密码验证时，点击了取消按钮
        loading_label->stopLoading();
        clean_button->setVisible(true);
        clean_button->setEnabled(true);
        back_button->setVisible(true);
    }
    else if (msg == "no") {//在弹出输入密码验证时，输入密码，验证通过，此时让动态图片开始显示
        //show dynamic image
        clean_button->setVisible(true);
        clean_button->setEnabled(false);
        back_button->setVisible(false);
        doing_label->setText(tr("Cleaning......"));//正在清理......
        loading_label->startLoading();
    }
    else if (msg == "c") {
        doing_label->setText(tr("Garbage Cleanup OK......"));
    }
    else if (msg == "h") {
        doing_label->setText(tr("History Cleanup OK......"));
    }
    else if (msg == "k") {
        doing_label->setText(tr("Cookies Cleanup OK......"));
    }
    else if (msg == "o") {
        this->writeFixCleanDate();
        //清理完毕后显示清理总数
        result_label->setText(tr("The lastest cleanup time is ") + this->getCurrentDateTime());
        this->setDoingLabelText(tr("Cleanup Cookies:") +cookies + tr("; Garbage:") + garbage + tr("; Historical records:")+trace, 460);
//        doing_label->setText(tr("Cleanup Cookies:") +cookies + tr("; Garbage:") + garbage + tr("; Historical records:") +trace);
        trace.clear();
        cookies.clear();
        garbage.clear();
        loading_label->stopLoading();
        scan_button->setVisible(true);
        scan_button->setEnabled(true);
        clean_button->setVisible(false);
        clean_button->setEnabled(true);
        back_button->setVisible(false);
    }
//    }
}

void MainTopWidget::finishCleanError(QString msg)
{
    if (msg == "ce") {
        qDebug() << "GarbageException---------";
    }
    else if (msg == "he") {
        qDebug() << "HistoryException---------";
    }
    else if (msg == "ke") {
        qDebug() << "CookiesException---------";
    }
}

void MainTopWidget::getCleaningMessage(QString type, QString status)
{
    if(type == "firefoxhistory") {
        if(status == "start") {
            doing_label->setText(tr("Cleaning up history trace of Firefox..."));//正在清理Firefox的历史痕迹...
        }
        else if(status == "end") {
            doing_label->setText(tr("Firefox history trace had been cleared!"));//Firefox的历史痕迹已清理完毕！
        }
    }
    else if(type == "chromiumhistory") {
        if(status == "start") {
           doing_label->setText(tr("Cleaning up history trace of Chromium..."));//正在清理Chromium的历史痕迹...
        }
        else if(status == "end") {
            doing_label->setText(tr("Chromium history trace had been cleared!"));//Chromium的历史痕迹已清理完毕！
        }
    }
    else if(type == "firefoxcookies") {
        if(status == "start") {
            doing_label->setText(tr("Cleaning up Cookies of Firefox..."));//正在清理Firefox的Cookies...
        }
        else if(status == "end") {
            doing_label->setText(tr("Firefox Cookies had been cleared!"));//Firefox的Cookies已清理完毕！
        }
    }
    else if(type == "chromiumcookies") {
        if(status == "start") {
            doing_label->setText(tr("Cleaning up Cookies of Chromium..."));//正在清理Chromium的Cookies...
        }
        else if(status == "end") {
            doing_label->setText(tr("Chromium Cookies had been cleared!"));//Chromium的Cookies已清理完毕！
        }
    }
    else if(type == "apt") {
        if(status == "end") {
            doing_label->setText(tr("Apt cache had been cleared!"));//Apt缓存已清理完毕！
        }
        else {
            doing_label->setText(tr("Cleaning up Apt cache: ") + status);//正在清理Apt缓存：
        }
    }
    else if(type == "software_center") {
        if(status == "end") {
            doing_label->setText(tr("Software Center cache had been cleared!"));//软件中心缓存已清理完毕！
        }
        else {
            doing_label->setText(tr("Cleaning up Software Center cache: ") + status);//正在清理软件中心缓存：
        }
    }
}

void MainTopWidget::displayOrgPage()
{
    doing_label->setVisible(false);
    back_button->setVisible(false);
//    loading_label->stopLoading();
    scan_button->setVisible(true);
    scan_button->setEnabled(true);
    clean_button->setVisible(false);
    suggest_label->setVisible(true);
}

void MainTopWidget::onStartButtonClicked()
{
    doing_label->setText(tr("Scanning......"));//正在扫描......
    if (m_isMain) {
        scan_button->setVisible(false);
//        scan_button->setEnabled(false);
        loading_label->startLoading();
        suggest_label->setVisible(false);
        scan_result_label->setVisible(false);
        result_label->setVisible(false);
        doing_label->setVisible(true);
        QStringList args;
        args << "cache" << "history" << "cookies";

        emit this->startOneKeyScan(args);
    }
    else {
        scan_button->setVisible(false);
        emit this->sendScanSignal();
    }
}

void MainTopWidget::onCleanButtonClicked()
{
    if (m_isMain) {
        clean_button->setVisible(false);
        back_button->setVisible(false);
        loading_label->startLoading();
        suggest_label->setVisible(false);
        scan_result_label->setVisible(false);
        result_label->setVisible(false);
        doing_label->setText(tr("Ready to Cleanup......"));//准备清理......
        doing_label->setVisible(true);

        emit this->startOneKeyClean();
    }
    else {
        clean_button->setVisible(false);
        back_button->setVisible(false);
        emit this->sendCleanSignal();
    }
}

void MainTopWidget::onEndButtonClicked()
{
    if (m_isMain) {
        result_label->setText(tr("The lastest scan time is ") + scanFinishTime);
        loading_label->stopLoading();
        scan_button->setVisible(true);
        scan_button->setEnabled(true);
        clean_button->setVisible(false);
        back_button->setVisible(false);
        suggest_label->setVisible(true);
        scan_result_label->setVisible(false);
        result_label->setVisible(true);
        doing_label->setVisible(false);
    }
    else {
        doing_label->setVisible(false);
        back_button->setVisible(false);
        loading_label->stopLoading();
        scan_button->setVisible(true);
        scan_button->setEnabled(true);
        clean_button->setVisible(false);
    //    back_button->hide();
        suggest_label->setVisible(true);
    //    result_label->show();
        emit this->showMainData();
    }
}

void MainTopWidget::receivePolicyKitSignal(bool status)
{
    /*display Clean Animation
        status = true:ok
        status = false:cacel
    */
    if(status)//ok
    {
        clean_button->setVisible(true);
        clean_button->setEnabled(false);
        back_button->setVisible(false);
        scan_button->setVisible(false);
        loading_label->startLoading();
        suggest_label->setVisible(false);
        doing_label->setText(tr("Ready to Cleanup......"));//准备清理......
        doing_label->setVisible(true);
    }
    else {
        clean_button->setVisible(true);
        back_button->setVisible(true);
    }
}


void MainTopWidget::writeFixCleanDate() {
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd"); //设置显示格式
    pSettings->beginGroup("OneKeyClean");
    pSettings->setValue("CleanDate", str);
    pSettings->setValue("Flag", "1");
    pSettings->endGroup();
    pSettings->sync();
}

QString MainTopWidget::getFixCleanDate() {
    pSettings->beginGroup("OneKeyClean");
    QString value = pSettings->value("CleanDate").toString();
    pSettings->endGroup();
    pSettings->sync();
    return value;
}

QString MainTopWidget::getCurrentDateTime() {
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd"); //设置显示格式
    return str;
}

void MainTopWidget::writeSafeScanDate() {
    QDateTime time = QDateTime::currentDateTime();//获取系统现在的时间
    QString str = time.toString("yyyy-MM-dd hh:mm:ss dddd"); //设置显示格式
    pSettings->beginGroup("OneKeyClean");
    pSettings->setValue("ScanDate", str);
    pSettings->setValue("Flag", "0");
    pSettings->endGroup();
    pSettings->sync();
}

QString MainTopWidget::getSafeScanDate() {
    pSettings->beginGroup("OneKeyClean");
    QString value = pSettings->value("ScanDate").toString();
    pSettings->endGroup();
    pSettings->sync();
    return value;
}

QString MainTopWidget::getOneKeyFlag() {
    pSettings->beginGroup("OneKeyClean");
    QString value = pSettings->value("Flag").toString();
    pSettings->endGroup();
    pSettings->sync();
    return value;
}

void MainTopWidget::setDoingLabelText(const QString &description, int defaultWidth)
{
    QFont font;
    font.setPixelSize(20);
    const QFontMetrics fm(font);
    QString elided_text = fm.elidedText(description, Qt::ElideRight, defaultWidth);
    doing_label->setText(elided_text);
}
