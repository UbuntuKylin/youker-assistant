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

#include "QDesktopWidget"

#include "upgradedialog.h"
#include "../component/loadinglabel.h"
#include <QtGui>
#include <QDebug>

UpgradeDialog::UpgradeDialog(QWidget *parent, const QString &version, QString skin) :
    QDialog(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(334, 470);
    this->setStyleSheet("QDialog{border: 1px solid white;border-radius:1px;background-color: #ffffff;}");

    isBusy = false;

    baseWidget = new QWidget(this);
    baseWidget->setGeometry(QRect(0, 0, 334, 191));
    baseWidget->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(skin)));
    baseWidget->setPalette(palette);

    close_btn = new SystemButton(baseWidget);
    close_btn->setFocusPolicy(Qt::NoFocus);
    close_btn->loadPixmap(":/sys/res/sysBtn/close_button.png");

    nameLabel = new QLabel(baseWidget);
    nameLabel->setGeometry(QRect(37, 0, 260, 30));
    nameLabel->setStyleSheet("QLabel{color:#ffffff;font-family: 方正黑体_GBK;font-size: 12px;text-align: center;font-weight:bold;}");
    nameLabel->setAlignment(Qt::AlignCenter);
    nameLabel->setText(tr("check and update"));

    msg_label = new QLabel(baseWidget);
    msg_label->setGeometry(QRect(10, 50, 324, 20));
    msg_label->setStyleSheet("QLabel{color:#FF0000;font-family: 方正黑体_GBK;font-size: 14px;text-align: center;}");
    msg_label->setAlignment(Qt::AlignCenter);
    msg_label->setText(tr("Is working, please wait a moment."));
    msg_label->hide();

    net_icon_label = new QLabel(this);
    net_icon_label->setGeometry(QRect(76, 91, 182, 181));
    net_icon_label->setStyleSheet("QLabel{background-image:url(':/res/no-net.png')}");
    net_icon_label->hide();

    normal_icon_label = new QLabel(this);
    normal_icon_label->setGeometry(QRect(76, 91, 182, 181));
    normal_icon_label->setStyleSheet("QLabel{background-image:url(':/res/upgrade-normal.png');color:#ffffff;font-family: 方正黑体_GBK;font-size: 20px;text-align: center;}");
    normal_icon_label->setAlignment(Qt::AlignCenter);
    normal_icon_label->hide();

    ok_icon_label = new QLabel(this);
    ok_icon_label->setGeometry(QRect(76, 91, 182, 181));
    ok_icon_label->setStyleSheet("QLabel{background-image:url(':/res/upgrade-ok.png')}");
    ok_icon_label->hide();

    work_loading_label = new LoadingLabel(this, "working");
    work_loading_label->setGeometry(QRect(76, 91, 182, 181));
    work_loading_label->show();

    upgrade_loading_label = new LoadingLabel(this, "upgrading");
    upgrade_loading_label->setGeometry(QRect(76, 91, 182, 181));
    upgrade_loading_label->hide();

//    movie_label = new QLabel(this);
//    movie_label->setGeometry(QRect(76, 91, 182, 181));
//    movie = new QMovie("://res/move.gif");
//    movie_label->setMovie(movie);
    timer = new QTimer(this);

    version_label = new QLabel(this);
    version_label->setObjectName("smallgrayLabel");
    version_label->setGeometry(QRect(10, 440, 324, 20));
    version_label->setText(tr("Current verison:") + version);
    doing_label = new QLabel(this);
    doing_label->setWordWrap(true);//QLabel自动换行
    doing_label->setStyleSheet("QLabel{color:#000000;font-family: 方正黑体_GBK;font-size: 13px;text-align: center;}");
    doing_label->setAlignment(Qt::AlignCenter);
    doing_label->setGeometry(QRect(10, 280, 324, 20));

    error_label = new QLabel(this);
    error_label->setGeometry(QRect(10, 280, 324, 30));
    error_label->setWordWrap(true);//QLabel自动换行
    error_label->setStyleSheet("QLabel{color:#000000;font-family: 方正黑体_GBK;font-size: 20px;text-align: center;}");
    error_label->setAlignment(Qt::AlignCenter);
    error_label->hide();
    tip_label = new QLabel(this);
    tip_label->setGeometry(QRect(10, 310, 324, 20));
    tip_label->setWordWrap(true);//QLabel自动换行
    tip_label->setStyleSheet("QLabel{color:#b2b2b2;font-family: 方正黑体_GBK;font-size: 13px;text-align: center;}");
    tip_label->setAlignment(Qt::AlignCenter);
    tip_label->hide();

    visit_label = new QLabel(this);
    visit_label->setGeometry(QRect(10, 310, 324, 20));
    visit_label->setWordWrap(true);//QLabel自动换行
    visit_label->setStyleSheet("QLabel{color:#b2b2b2;font-family: 方正黑体_GBK;font-size: 13px;text-align: center;}");
    visit_label->setAlignment(Qt::AlignCenter);
    visit_label->hide();

    new_label = new QLabel(this);
    new_label->setWordWrap(true);//QLabel自动换行
    new_label->setStyleSheet("QLabel{color:#000000;font-family: 方正黑体_GBK;font-size: 13px;text-align: center;}");
    new_label->setAlignment(Qt::AlignCenter);
    new_label->setGeometry(QRect(10, 280, 324, 20));
    new_label->hide();

    error_label->setText(tr("An error occurred!"));
    tip_label->setText(tr("Network or local sources anomaly"));
    doing_label->setText(tr("Testing network and local sources......"));
//    visit_label->setText(tr("you can visit ") + QString::fromLocal8Bit("<a style='color: green;' href = https://launchpad.net/youker-assistant> UK official website </a>") + tr("to download the lastest deb package"));
//    visit_label->setText(tr("you can visit ") + tr("<a style='color: green;' href = https://launchpad.net/youker-assistant> UK official website </a>") + tr("to download the lastest deb package"));
    visit_label->setText(tr("you can visit the<a style='color: green;' href = https://launchpad.net/youker-assistant> UK official website </a>to download the lastest deb package."));
    retryBtn = new QPushButton(this);
    retryBtn->setFocusPolicy(Qt::NoFocus);
    retryBtn->setStyleSheet("QPushButton{background-image:url('://res/retry.png');border:0px;}QPushButton:hover{background:url('://res/retry-hover.png');}QPushButton:pressed{background:url('://res/retry-press.png');}");
    retryBtn->hide();
    retryBtn->setText(tr("Retry"));
    retryBtn->setGeometry(QRect(74, 350, 186, 56));

    progressbar = new QProgressBar(this);
    progressbar->setValue(0);
    progressbar->setGeometry(QRect(30, 340, 284, 30));
    progressbar->hide();
    progressbar->setStyleSheet("QProgressBar{background-color:#ffffff;border:1px solid #aaaaaa;border-radius:0px;color:#666666;font-family: 方正黑体_GBK;text-align:center;}"
                                              "QProgressBar:chunk{background-color:#b1dcff;}");
    okBtn = new QPushButton(this);
    okBtn->setFocusPolicy(Qt::NoFocus);
    okBtn->setStyleSheet("QPushButton{background-image:url('://res/retry.png');border:0px;}QPushButton:hover{background:url('://res/retry-hover.png');}QPushButton:pressed{background:url('://res/retry-press.png');}");
    okBtn->hide();
    okBtn->setText(tr("Finish"));
    okBtn->setGeometry(QRect(74, 350, 186, 56));

    upgradeBtn = new QPushButton(this);
    upgradeBtn->setFocusPolicy(Qt::NoFocus);
    upgradeBtn->setGeometry(QRect(234, 437, 91, 25));
    upgradeBtn->setObjectName("blackButton");
    upgradeBtn->setText(tr("Upgrade"));
    upgradeBtn->hide();

    splitlabel = new QLabel(this);
    splitlabel->setGeometry(QRect(0, 430, 334, 1));
    splitlabel->setFixedHeight(1);
    splitlabel->setStyleSheet("QLabel{background:#aaaaaa;}");
    this->initConnect();
}

UpgradeDialog::~UpgradeDialog()
{
//    if(movie != NULL) {
//        delete movie;
//        movie = NULL;
//    }
    if (timer != NULL) {
        disconnect(timer,SIGNAL(timeout()),this,SLOT(slotDisappearTip()));
        if(timer->isActive()) {
            timer->stop();
        }
        delete timer;
        timer = NULL;
    }
}

void UpgradeDialog::initConnect()
{
    connect(close_btn, SIGNAL(clicked()), this, SLOT(onCloseBtnClicked()));
    connect(retryBtn, SIGNAL(clicked()), this, SLOT(onRetryBtnClicked()));
    connect(upgradeBtn, SIGNAL(clicked()), this, SLOT(onUpgradeBtnClicked()));
    connect(okBtn, SIGNAL(clicked()), this, SLOT(onOkBtnClicked()));
    connect(timer, SIGNAL(timeout()), this, SLOT(slotDisappearTip()));
    connect(visit_label,SIGNAL(linkActivated(QString)),this,SLOT(openUrl(QString)));
}

void UpgradeDialog::slotDisappearTip()
{
    msg_label->hide();
}

void UpgradeDialog::openUrl(QString url)
{
    QDesktopServices::openUrl(QUrl(url));
}

void UpgradeDialog::startAccessData()
{
    QTimer::singleShot(100, this, SLOT(checkLastestVersion()));
}

void UpgradeDialog::showErrorComponents()
{
    error_label->show();
    tip_label->show();
    retryBtn->show();
    doing_label->hide();
}

void UpgradeDialog::showUpdateSourceComponents()
{
    doing_label->setText(tr("Start to update the local sources"));
    visit_label->show();
    progressbar->setValue(0);
    progressbar->show();
}

void UpgradeDialog::checkLastestVersion()
{
    //check source list valid or not
    this->isBusy = true;
    work_loading_label->startLoading();
//    movie->start();
    sessionProxy->start_check_source_useable_qt();
}

void UpgradeDialog::onRetryBtnClicked()
{
    this->isBusy = true;
    net_icon_label->hide();
    error_label->hide();
    tip_label->hide();
    retryBtn->hide();
    work_loading_label->show();
    work_loading_label->startLoading();
    doing_label->setText(tr("Testing network and local sources......"));
    doing_label->show();
//    movie_label->show();
//    movie->start();
    sessionProxy->start_check_source_useable_qt();
}

void UpgradeDialog::receiveCheckResultSignal(bool result)
{
    if(result == false) {
        this->isBusy = false;
        work_loading_label->stopLoading();
        work_loading_label->hide();
//        movie->stop();
//        movie_label->hide();
        net_icon_label->show();
        this->showErrorComponents();
    }
    else {
        this->isBusy = true;
        this->showUpdateSourceComponents();
        systemProxy->update_source();
    }
}

void UpgradeDialog::receiveFetchSignal(QString msg_type, QStringList msg)
{
    if(msg_type == "down_start")
    {
        if( msg.length() == 3 && msg.at(0) == "youker-assistant" && msg.at(2) == "install") {
            if(msg.at(1) == "0") {
                doing_label->setText(tr("Start to download"));
            }
        }
        else if( msg.length() == 3 && msg.at(0) == "#update" && msg.at(1) == "0" && msg.at(2) == "update") {
            doing_label->setText(tr("Start to update the local sources"));
        }
    }
    else if(msg_type == "down_stop")
    {
        if( msg.length() == 3 && msg.at(0) == "youker-assistant" && msg.at(2) == "install") {
            if(msg.at(1) == "0") {
                doing_label->setText(tr("Download completely"));
            }
        }
        else if( msg.length() == 3 && msg.at(0) == "#update" && msg.at(1) == "200" && msg.at(2) == "update") {
            progressbar->hide();
            visit_label->hide();
//            movie->stop();
//            movie_label->hide();
            work_loading_label->stopLoading();
            work_loading_label->hide();
            normal_icon_label->show();
            doing_label->setText(tr("Local sources updated"));
            QStringList version_list = sessionProxy->checkNewVersion();
            qDebug() << version_list;//("1.2.0-0ubuntu1", "1.2.0-0ubuntu1", "1.3.1-0ubuntu1", "1")
            if(version_list.length() == 1) {
//                version_label->setText(version_list.at(0));
                normal_icon_label->setText(tr("Not found"));
            }
            else if(version_list.length() == 4) {
        //         version_label->setText(version_list.at(2));
                if(version_list.at(3) == "1") {
                    normal_icon_label->setText(tr("Found a new version"));
                    new_label->show();
                    new_label->setText(tr("New version:") + version_list.at(2));
                    upgradeBtn->show();
                    doing_label->hide();
                }
                else {
                    normal_icon_label->setText(tr("Not found"));
                }
            }
            this->isBusy = false;
        }
    }
    else if(msg_type == "down_fetch" || msg_type == "down_done") {
        if(msg.length() == 3 && msg.at(0) == "#update" && msg.at(2) == "update") {
            doing_label->setText(tr("Updating local sources...") + QString::number(int(msg.at(1).toDouble())) + "%");
            progressbar->setValue(msg.at(1).toFloat());
        }
    }
}

void UpgradeDialog::receiveAptSignal(QString msg_type, QStringList msg)
{
    if(msg_type == "apt_finish")
    {
        if( msg.length() == 3 && msg.at(0) == "youker-assistant" && msg.at(1) == "200" && msg.at(2) == "install") {
            this->isBusy = false;
            ok_icon_label->show();
            okBtn->show();
            doing_label->setText("Youker Assistant is the latest version");
            upgrade_loading_label->stopLoading();
            upgrade_loading_label->hide();
            progressbar->setValue(100);
            progressbar->hide();
            visit_label->hide();
        }
    }
    else if(msg_type == "apt_start")
    {
        if( msg.length() == 3 && msg.at(0) == "youker-assistant" && msg.at(1) == "0" && msg.at(2) == "install") {
            doing_label->setText(tr("Start to install"));
            progressbar->setValue(0);
        }
    }
    else if(msg_type == "apt_pulse")
    {
        if( msg.length() == 4){
            //installing
            doing_label->setText(tr("Upgrading the main program...") + QString::number(int(msg.at(1).toDouble())) + "%");
            progressbar->setValue(msg.at(1).toFloat());
        }
    }
    else {
        qDebug() << "apt->" << msg_type;
        qDebug() << msg;
    }
}

void UpgradeDialog::resetTitleSkin(QString skin)
{
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(skin)));
    baseWidget->setPalette(palette);
}

void UpgradeDialog::resetVersionNumber(QStringList version_list)
{
    qDebug() << "new version->" << version_list;
}

void UpgradeDialog::onCloseBtnClicked()
{
    if(this->isBusy) {
        msg_label->show();
        timer->start(3000);
    }
    else {
        if (timer->isActive())
            timer->stop();
        this->close();
    }
}

void UpgradeDialog::onOkBtnClicked()
{

}

void UpgradeDialog::onUpgradeBtnClicked()
{
    this->isBusy = true;
    new_label->hide();
    upgradeBtn->hide();
    normal_icon_label->hide();
    upgrade_loading_label->show();
    upgrade_loading_label->startLoading();
    doing_label->show();
    doing_label->setText(tr("Start to upgrade the main program"));
    visit_label->show();
    progressbar->setValue(0);
    progressbar->show();
//    net_icon_label->hide();
//    movie_label->show();
//    movie->start();
    systemProxy->update_myself();
}

void UpgradeDialog::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        mouse_press = true;
        drag_pos = event->globalPos() - this->frameGeometry().topLeft();
        event->accept();
    }
}

void UpgradeDialog::mouseReleaseEvent(QMouseEvent *)
{
    mouse_press = false;
}

void UpgradeDialog::mouseMoveEvent(QMouseEvent *event)
{
    if(mouse_press)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - drag_pos);
        event->accept();
    }
}
