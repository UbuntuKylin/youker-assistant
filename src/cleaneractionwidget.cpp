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

#include "cleaneractionwidget.h"
#include <QDebug>
#include "../dbusproxy/youkersessiondbus.h"
#include "../dbusproxy/youkersystemdbus.h"

CleanerActionWidget::CleanerActionWidget(QWidget *parent)
	: QWidget(parent)
{
    this->setFixedSize(900, 150);

    this->setAutoFillBackground(true);
//    this->setObjectName("transparentWidget");
//    cache_page = new CacheActionWidget(this);
//    statked_widget = new QStackedWidget(this);
////    QPalette palette;
////    palette.setBrush(QPalette::Window, QBrush(Qt::white));
////    statked_widget->setPalette(palette);
////    statked_widget->setAutoFillBackground(true);
//    statked_widget->addWidget(cache_page);
//    QVBoxLayout *layout1 = new QVBoxLayout();
//    layout1->addWidget(statked_widget);
//    layout1->setMargin(0);
//    layout1->setContentsMargins(0, 0, 0, 0);
//    setLayout(layout1);

    suggest_label = new QLabel();
//    result_label = new QLabel();
    doing_label = new QLabel();
    scan_button = new QPushButton(this);
    clean_button = new QPushButton(this);
    back_button = new QPushButton(this);
    back_button->setObjectName("backButton");
    back_button->hide();

    loading_label = new LoadingLabel(this, "clean");
    loading_label->show();

    suggest_label->setObjectName("whiteLabel");
    suggest_label->setWordWrap(true);//QLabel自动换行
    suggest_label->setFixedWidth(550);
//    result_label->setWordWrap(true);//QLabel自动换行
//    result_label->setObjectName("tipLabel");
    doing_label->setFixedWidth(550);
    doing_label->setWordWrap(true);//QLabel自动换行
    doing_label->setObjectName("whiteLabel");
    doing_label->hide();

//    scan_button->setFixedSize(182, 58);
    scan_button->setGeometry(QRect(680, 50, 182, 58));
    scan_button->setFocusPolicy(Qt::NoFocus);
    scan_button->setObjectName("greenButton");
    scan_button->show();
//    clean_button->setFixedSize(182, 58);
    clean_button->setGeometry(QRect(680, 50, 182, 58));
    clean_button->setFocusPolicy(Qt::NoFocus);
    clean_button->setObjectName("greenButton");
    clean_button->hide();

    back_button->setFocusPolicy(Qt::NoFocus);
//    back_button->setFixedSize(50, 30);
    back_button->setGeometry(QRect(820, 110, 50, 30));
    back_button->setObjectName("underlineButton");
    back_button->hide();

    //set underline
    //    QFont font = back_button->font();
    //    font.setUnderline(true);
    //    back_button->setFont(font);

    //set scan button text color
//    QPalette palette;
//    palette.setColor(QPalette::ButtonText, QColor(255,17,135));
//    scan_button->setPalette(palette);

    QVBoxLayout *layout1 = new QVBoxLayout();
    layout1->addStretch();
    layout1->addWidget(suggest_label, 0 , Qt::AlignVCenter);
//    layout1->addWidget(result_label);
    layout1->addWidget(doing_label, 0 , Qt::AlignVCenter);
    layout1->addStretch();
    layout1->setSpacing(0);
    layout1->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addWidget(loading_label, 0, Qt::AlignVCenter);
    layout2->addLayout(layout1);
    layout2->setSpacing(20);
    layout2->setMargin(0);
    layout2->setContentsMargins(0, 0, 0, 0);

//    QVBoxLayout *layout3 = new QVBoxLayout();
//    layout3->addStretch();
//    layout3->addWidget(scan_button, 0, Qt::AlignRight);
//    layout3->addWidget(clean_button, 0, Qt::AlignRight);
//    layout3->addWidget(back_button, 0, Qt::AlignRight);
//    layout3->addStretch();
//    layout3->setSpacing(10);
//    layout3->setContentsMargins(0, 20, 0, 0);



    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addLayout(layout2);
    main_layout->addStretch();
//    main_layout->addLayout(layout3);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(13, 20, 44, 0);

    setLayout(main_layout);

    this->initConnect();
    this->setLanguage();
}

CleanerActionWidget::~CleanerActionWidget()
{
    if(suggest_label != NULL) {
        delete suggest_label;
        suggest_label = NULL;
    }
    if(doing_label != NULL) {
        delete doing_label;
        doing_label = NULL;
    }
}

void CleanerActionWidget::initConnect()
{
    connect(scan_button, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
    connect(clean_button, SIGNAL(clicked()), this, SLOT(onCleanButtonClicked()));
    connect(back_button, SIGNAL(clicked()), this, SLOT(onBackButtonClicked()));
}

void CleanerActionWidget::setLanguage()
{
    suggest_label->setText(tr("Regular cleaning, let your computer remains the relaxed state"));//经常清理，让电脑保持最轻松的状态
//    result_label->setText(tr("上次检测时间为2014-07-07 16:40:35 星期一，清理了4.84KB垃圾。"));
    scan_button->setText(tr("Start Scan"));//开始扫描
    clean_button->setText(tr("Start Cleanup"));//开始清理
    back_button->setText(tr("Back"));
    doing_label->setText(tr("Scaning......"));//正在扫描......
}

void CleanerActionWidget::showCleanOverStatus()
{
    loading_label->stopLoading();
    scan_button->show();
    scan_button->setEnabled(true);
    clean_button->hide();
    clean_button->setEnabled(true);
    back_button->hide();
    doing_label->setText(tr("Clean OK"));
}

void CleanerActionWidget::showCleanerData(const QStringList &data)
{
    if(data.length() == 2)
    {
        doing_label->setText(tr("Cleaning: ") + data.at(0).split(":").at(1));
    }
    else if(data.length() == 3)
    {
        doing_label->setText(data.at(0).split(":").at(1) + tr(", Percent is: ") + data.at(1).split(":").at(1) + tr("%, Status is: ") + data.at(2).split(":").at(1));
    }
}

void CleanerActionWidget::showCleanerStatus(const QString &status, const QString &domain)
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

void CleanerActionWidget::showCleanerError(const QString &status)
{
    if(status.contains("Non-existent:"))
    {
        if(status.split(":").at(1).length() > 0)
            doing_label->setText(status.split(":").at(1) + tr(" does not exist"));
    }
    else if(status.contains("Working:Chromium"))
    {
        doing_label->setText(tr("Chromium Browser is running......"));
    }
}

void CleanerActionWidget::showCleanReciveStatus(const QString &status)
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

void CleanerActionWidget::accordScanOverStatusToChange(bool status)
{
    if (status) {
        doing_label->setText(tr("Scaning......"));
        doing_label->hide();
        loading_label->stopLoading();
        scan_button->hide();
        scan_button->setEnabled(true);
        clean_button->show();
        clean_button->setEnabled(true);
        suggest_label->show();
        back_button->show();
    }
    else {
        doing_label->setText(tr("Scaning......"));
        doing_label->hide();
        loading_label->stopLoading();
        scan_button->hide();
        scan_button->setEnabled(true);
        clean_button->hide();
        clean_button->setEnabled(true);
        suggest_label->show();
        back_button->show();
    }
}

void CleanerActionWidget::showCleanReciveError(const QString &status)
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
        if(status.contains("Non-existent:"))
            doing_label->setText(status.split(":").at(1) + tr(" does not exist"));
    }
}

void CleanerActionWidget::displayAnimation()
{
    scan_button->setEnabled(false);
    loading_label->startLoading();
    suggest_label->hide();
    doing_label->show();
    emit this->showDetailData();
}

//void CleanerActionWidget::displayCleanAnimation()
//{
//    clean_button->show();
//    clean_button->setEnabled(false);
//    loading_label->startLoading();
//    suggest_label->hide();
//    doing_label->setText(tr("Ready to Cleanup......"));//准备清理......
//    doing_label->show();
//}

void CleanerActionWidget::receivePolicyKitSignal(bool status)
{
    /*display Clean Animation
        status = true:ok
        status = false:cacel
    */
    if(status)//ok
    {
        clean_button->show();
        clean_button->setEnabled(false);
        back_button->hide();//0713
        scan_button->hide();
        loading_label->startLoading();
        suggest_label->hide();
        doing_label->setText(tr("Ready to Cleanup......"));//准备清理......
        doing_label->show();
    }
    else {
        clean_button->show();
        back_button->show();
    }
}


void CleanerActionWidget::onStartButtonClicked()
{
    doing_label->setText(tr("Scaning......"));
    emit this->sendScanSignal();
}

void CleanerActionWidget::onCleanButtonClicked()
{
    clean_button->hide();
    back_button->hide();
    emit this->sendCleanSignal();
}

void CleanerActionWidget::displayOrgPage()
{
    doing_label->hide();
    back_button->hide();
//    loading_label->stopLoading();
    scan_button->show();
    scan_button->setEnabled(true);
    clean_button->hide();
    suggest_label->show();
}

void CleanerActionWidget::onBackButtonClicked()
{
    doing_label->hide();
    back_button->hide();
    loading_label->stopLoading();
    scan_button->show();
    scan_button->setEnabled(true);
    clean_button->hide();
//    back_button->hide();
    suggest_label->show();
//    result_label->show();
    emit this->showMainData();
}
