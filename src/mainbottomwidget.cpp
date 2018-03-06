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

#include "mainbottomwidget.h"
#include "../component/toolbutton.h"
#include "../component/utils.h"

#include <QApplication>
#include <QSignalMapper>
#include <QDebug>

MainBottomWidget::MainBottomWidget(QWidget *parent, QString arch, QString os/*, const QString &version*/) :
    QWidget(parent), osarch(arch), osname(os)
{
    this->setFixedSize(900, 326);

    //set white background color
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    this->setPalette(palette);

////    QPixmap label_pixmap("");
////    movie_label->setPixmap(label_pixmap);
////    movie_label->setFixedSize(label_pixmap.size());

//    scan_button->setFocusPolicy(Qt::NoFocus);
//    QPixmap pixmap("://res/scan.png");
//    scan_button->setIcon(pixmap);
//    scan_button->setIconSize(pixmap.size());
    current_version = qApp->applicationVersion();
    version_logo = new QLabel();
    version_title = new QLabel();
    version_tip = new QLabel();
    check_btn = new QPushButton();
    check_btn->hide();
//    version_label = new QLabel();
    box_logo = new QLabel();
    box_title = new QPushButton();
    box_title->setFixedWidth(240);
    box_title->setCursor(Qt::PointingHandCursor);
    box_title->setFocusPolicy(Qt::NoFocus);
    box_title->setStyleSheet("QPushButton{background-color:transparent;border:none;text-align:left;font-family: 方正黑体_GBK;font-size:24px;color:#000000;}QPushButton:hover{color:#3f96e4;}");//background:transparent;
//    box_title->installEventFilter(this);
    box_tip = new QLabel();
//    more_text_btn = new QPushButton();
//    more_btn = new QPushButton();

//    auto_start = NULL;
//    camera_manager = NULL;

//    more_text_btn->setObjectName("checkButton");
//    more_text_btn->setCursor(Qt::PointingHandCursor);
//    more_text_btn->setCursor(Qt::OpenHandCursor);
//    more_text_btn->setFocusPolicy(Qt::NoFocus);
//    QFont font = more_text_btn->font();
//    font.setUnderline(true);
//    more_text_btn->setFont(font);

    check_btn->setObjectName("checkButton");
    check_btn->setCursor(Qt::PointingHandCursor);
    check_btn->setFocusPolicy(Qt::NoFocus);
//    version_label->setObjectName("smallgrayLabel");
    version_title->setObjectName("bigblackLabel");
//    box_title->setObjectName("bigblackLabel");
    version_tip->setAlignment(Qt::AlignLeft);
    version_tip->setObjectName("smallgrayLabel");
    version_tip->setFixedWidth(380);
    box_tip->setAlignment(Qt::AlignLeft);
    box_tip->setObjectName("smallgrayLabel");
    version_tip->setWordWrap(true);//QLabel自动换行
    box_tip->setWordWrap(true);//QLabel自动换行
    box_tip->setFixedWidth(380);
//    more_btn->setObjectName("transparentButton");
//    more_btn->setCursor(Qt::PointingHandCursor);

    version_logo->setFixedSize(65, 65);
    version_logo->setPixmap(QPixmap("://res/version.png"));
    box_logo->setFixedSize(65, 65);
    box_logo->setPixmap(QPixmap("://res/box.png"));

    this->initUI();
    this->initConnect();
    this->setLanguage();

}

MainBottomWidget::~MainBottomWidget()
{
    if(version_logo != NULL) {
        delete version_logo;
        version_logo = NULL;
    }
    if(version_title != NULL) {
        delete version_title;
        version_title = NULL;
    }
    if(version_tip != NULL) {
        delete version_tip;
        version_tip = NULL;
    }
    if(check_btn != NULL) {
        delete check_btn;
        check_btn = NULL;
    }
    if(box_logo != NULL) {
        delete box_logo;
        box_logo = NULL;
    }
    if(box_title != NULL) {
        delete box_title;
        box_title = NULL;
    }
    if(box_tip != NULL) {
        delete box_tip;
        box_tip = NULL;
    }
//    for(int i=0; i<item_list.count(); i++)
//    {
//        ToolButton *btn = item_list.at(i);
//        delete btn;
//        btn = NULL;
//    }
//    item_list.clear();
}

void MainBottomWidget::initUI()
{
    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addWidget(version_title);
    layout1->addWidget(check_btn);
//    layout1->addWidget(version_label);
    layout1->addStretch();
    layout1->setMargin(0);
    layout1->setSpacing(5);
    layout1->setContentsMargins(0,0,0,0);
    QVBoxLayout *layout2 = new QVBoxLayout();
    layout2->addStretch();
    layout2->addLayout(layout1);
    layout2->addWidget(version_tip);
    layout2->addStretch();
    layout2->setMargin(0);
    layout2->setSpacing(5);
    layout2->setContentsMargins(0,0,0,0);
    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addWidget(version_logo/* ,0, Qt::AlignVCenter*/);
    layout3->addLayout(layout2);
    layout3->addStretch();
    layout3->setMargin(0);
    layout3->setSpacing(5);
    layout3->setContentsMargins(0,0,0,0);

    QVBoxLayout *layout4 = new QVBoxLayout();
    layout4->addStretch();
    layout4->addWidget(box_title);
    layout4->addWidget(box_tip);
    layout4->addStretch();
    layout4->setMargin(0);
    layout4->setSpacing(5);
    layout4->setContentsMargins(0,0,0,0);

    QHBoxLayout *layout5 = new QHBoxLayout();
    layout5->addWidget(box_logo);
    layout5->addLayout(layout4);
    layout5->addStretch();
//    layout5->addLayout(button_layout);
    layout5->setMargin(0);
    layout5->setSpacing(5);
    layout5->setContentsMargins(0,0,0,0);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(layout3);
    main_layout->addLayout(layout5);
    main_layout->setMargin(0);
    main_layout->setSpacing(50);
    main_layout->setContentsMargins(60,50,60,80);

    this->setLayout(main_layout);
}

void MainBottomWidget::initConnect()
{
    connect(check_btn, SIGNAL(clicked()), this, SLOT(onCheckBtnClicked()));
    connect(box_title, SIGNAL(clicked()), this, SIGNAL(sendSignal()));
}

void MainBottomWidget::setLanguage()
{
    version_title->setText(tr("Current Version Number") + "    " + current_version);
    version_tip->setText(tr("Update to the lastest version, make it work better"));
    check_btn->setText(tr("updating on the backend"));
    box_title->setText(tr("Common toolbox"));
    box_tip->setText(tr("Fast and practical, making the system more personalized"));
//    more_text_btn->setText(tr("More"));
//    more_btn->setToolTip(tr("More"));
}

void MainBottomWidget::initBoxTool()
{

}

void MainBottomWidget::onCheckBtnClicked()
{
    emit this->sendOpenUpgrade();
    check_btn->hide();
}

void MainBottomWidget::displayBackedBtn(bool flag)
{
    if(flag)
        check_btn->setText(tr("Upgrade is complete"));
    else
        check_btn->setText(tr("Updating on the backend"));
    check_btn->show();
}

void MainBottomWidget::hideBackedBtn()
{
    check_btn->hide();
}

void MainBottomWidget::switchPageIndex(QString index)
{

}
