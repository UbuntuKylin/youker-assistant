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

#include "homepage.h"
#include <QSignalMapper>
#include <QDebug>
#include "mainwindow.h"
#include "../component/toolbutton.h"
#include "../component/utils.h"

HomePage::HomePage(QWidget *parent, QString arch, QString os/*, const QString &version*/) :
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
    box_title->setStyleSheet("QPushButton{background:#ffffff;border:none;text-align:left;font-family: 方正黑体_GBK;font-size:24px;color:#000000;}QPushButton:hover{color:#3f96e4;}");//background:transparent;
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



    this->setLanguage();
}

HomePage::~HomePage()
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

void HomePage::initUI()
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




    /*QStringList icon_list;
//    icon_list<<"://res/ubuntukylin-software-center"<<"://res/boot"<<"://res/camera";
    icon_list<<"://res/boot" << "://res/more.png";
    QStringList text_list;
//    text_list<< tr("Youker Softeware Center") << tr("Boot Manager") << tr("Camera");
    text_list << tr("Boot Manager") << tr("More");
    QHBoxLayout *button_layout = new QHBoxLayout();
    QSignalMapper *signal_mapper = new QSignalMapper(this);
    for(int i=0; i<icon_list.size(); i++)
    {
        ToolButton *tool_button = new ToolButton;
        tool_button->setFocusPolicy(Qt::NoFocus);
        tool_button->setIcon(icon_list.at(i));
        tool_button->setText(text_list.at(i));
        connect(tool_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(tool_button, QString::number(i, 10));
        button_layout->addWidget(tool_button);
        item_list.append(tool_button);
    }
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(switchPageIndex(QString)));
*/

//    more_btn->setFocusPolicy(Qt::NoFocus);
//    QPixmap pixmap("://res/more.png");
//    more_btn->setIcon(pixmap);
//    more_btn->setIconSize(pixmap.size());

//    QVBoxLayout *more_layout = new QVBoxLayout();
////    more_layout->addStretch();
//    more_layout->addWidget(more_btn);
//    more_layout->addWidget(more_text_btn);
////    more_layout->addStretch();
//    more_layout->setSpacing(0);
//    more_layout->setMargin(0);
//    more_layout->setContentsMargins(0, 8, 0, 0);

//    button_layout->addStretch();
//    button_layout->addLayout(more_layout);
////    button_layout->addWidget(more_btn, 0, Qt::AlignTop);
//    button_layout->setSpacing(20);
//    button_layout->setMargin(0);
//    button_layout->setContentsMargins(0, 0, 0, 0);

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

void HomePage::initConnect()
{
    connect(this, SIGNAL(moreSignal()), p_mainwindow, SIGNAL(chanegBoxToolStatus()));
//    connect(more_btn, SIGNAL(clicked()), p_mainwindow, SLOT(showBoxWidget()));
//    connect(more_btn, SIGNAL(clicked()), p_mainwindow, SIGNAL(chanegBoxToolStatus()));
//    connect(more_text_btn, SIGNAL(clicked()), p_mainwindow, SLOT(showBoxWidget()));
//    connect(more_text_btn, SIGNAL(clicked()), p_mainwindow, SIGNAL(chanegBoxToolStatus()));
//    connect(check_btn, SIGNAL(clicked()), this, SLOT(checkLastestVersion()));
    connect(check_btn, SIGNAL(clicked()), this, SLOT(onCheckBtnClicked()));
    connect(this, SIGNAL(sendSignal()), p_mainwindow, SIGNAL(chanegBoxToolStatus()));
    connect(box_title, SIGNAL(clicked()), this, SIGNAL(sendSignal()));
}

void HomePage::setLanguage()
{
    version_title->setText(tr("Current Version Number") + "    " + current_version);
    version_tip->setText(tr("Update to the lastest version, make it work better"));
    check_btn->setText(tr("updating on the backend"));
    box_title->setText(tr("Common toolbox"));
    box_tip->setText(tr("Fast and practical, making the system more personalized"));
//    more_text_btn->setText(tr("More"));
//    more_btn->setToolTip(tr("More"));
}

void HomePage::initBoxTool()
{

}

void HomePage::onCheckBtnClicked()
{
    emit this->sendOpenUpgrade();
    check_btn->hide();
}

void HomePage::displayBackedBtn(bool flag)
{
    if(flag)
        check_btn->setText(tr("Upgrade is complete"));
    else
        check_btn->setText(tr("Updating on the backend"));
    check_btn->show();
}

void HomePage::hideBackedBtn()
{
    check_btn->hide();
}

//void HomePage::checkLastestVersion()
//{
//    QStringList version_list = sessionProxy->checkNewVersion();
//    if(version_list.length() == 1) {
//        version_label->setText(version_list.at(0));
//    }
//    if(version_list.length() == 4) {
//         version_label->setText(version_list.at(2));
//        if(version_list.at(3) == "1") {
//            qDebug() << "Neet to UPdate......";
//            p_mainwindow->openUpgradePage(version_list);
////            systemProxy->update_myself();
//        }
//        else {
//            qDebug() << "Unneccesary to UPdate......";
//            p_mainwindow->openUpgradePage(version_list);
//        }
//    }
//    else {
//        version_label->setText("");
//    }
//}

void HomePage::switchPageIndex(QString index)
{
//    bool ok;
//    int current_index = index.toInt(&ok, 10);

    if(index == "0")
        emit this->sendSubIndex(0);
//    else if(index == "-1")
//        if(this->osarch == "aarch64" || this->osname == "Kylin" || this->osname == "YHKylin")
//            sessionProxy->runApp("cheese");
//        else
//            emit this->sendSubIndex(1);
//    else if(index == "1") {
////        p_mainwindow->showBoxWidget();
//        emit this->moreSignal();
//    }

//    if(index == "0")
//    {
//        if(auto_start == NULL) {
//            auto_start = new AutoStartWidget(0, sessionProxy);
//            connect(sessionProxy, SIGNAL(tellAutoModel(QStringList)), auto_start, SLOT(readyReciveData(QStringList)));
//            connect(sessionProxy, SIGNAL(showAutoModel()), auto_start, SLOT(readyShowUI()));
//            auto_start->initData();
//            int w_x = p_mainwindow->frameGeometry().topLeft().x() + (900 / 2) - (560  / 2);
//            int w_y = p_mainwindow->frameGeometry().topLeft().y() + (600 /2) - (398  / 2);
//            auto_start->move(w_x, w_y);
//            auto_start->show();
//            auto_start->raise();
//        }
//        else {
//            int w_x = p_mainwindow->frameGeometry().topLeft().x() + (900 / 2) - (560  / 2);
//            int w_y = p_mainwindow->frameGeometry().topLeft().y() + (600 /2) - (398  / 2);
//            auto_start->move(w_x, w_y);
//            auto_start->show();
//            auto_start->raise();
//        }
//    }

//    else if(index == "1")
//    {
//        if(camera_manager == NULL) {
//            camera_manager = new CameraManager(0, sessionProxy);
//            if(sessionProxy->judge_camera_qt())
//            {
//                camera_manager->setOKButtonEnable(true);
//            }
//            else{
//                camera_manager->setOKButtonEnable(false);
//            }
//            int w_x = p_mainwindow->frameGeometry().topLeft().x() + (900 / 2) - (524  / 2);
//            int w_y = p_mainwindow->frameGeometry().topLeft().y() + (600 /2) - (277  / 2);
//            camera_manager->move(w_x, w_y);
//            camera_manager->exec();
////            camera_manager->show();
////            camera_manager->raise();
//        }
//        else {
//            int w_x = p_mainwindow->frameGeometry().topLeft().x() + (900 / 2) - (524  / 2);
//            int w_y = p_mainwindow->frameGeometry().topLeft().y() + (600 /2) - (277  / 2);
//            camera_manager->move(w_x, w_y);
//            camera_manager->show();
//            camera_manager->raise();
//        }
//    }
}

//bool HomePage::eventFilter(QObject *obj, QEvent *event)
//{
//    if(obj == box_title){
//        if(event->type() == QEvent::MouseButtonRelease){
//            emit this->sendSignal();
////            p_mainwindow->showBoxWidget();
//        }
////        if(event->type() == QEvent::Enter){
////            ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn_hover.png"));
////        }else if(event->type() == QEvent::Leave){
////            ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
////        }else if(event->type() == QEvent::MouseButtonPress){
////            ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn_hover.png"));
////        }else if(event->type() == QEvent::MouseButtonRelease){
////            QMouseEvent *me = (QMouseEvent *)event;
////            QLabel *lb = (QLabel *)obj;
////            if(me->x() > 0 && me->x() < lb->width() && me->y() > 0 && me->y() < lb->height()){
////                this->close();
////                this->destroy();
////            }else{
////                ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
////            }
////        } else {
////            return QObject::eventFilter(obj, event);
////        }
//    }
//    return QObject::eventFilter(obj, event);
//}
