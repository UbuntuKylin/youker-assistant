/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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
#include "itemcard.h"
#include "ui_itemcard.h"
#include <QDebug>
#include <QBitmap>

ItemCard::ItemCard(QString title, bool flag, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemCard)
{
    ui->setupUi(this);
    ui->deleteWidget->hide();
    ui->coverWidget->lower();
    ui->coverWidget->hide();
    dislayDelBtn = false;
//    switchTimer = new QTimer();
//    connect(switchTimer, SIGNAL(timeout()), this, SLOT(slotSwitchAnimationStep()));

    //delay show animation
    showDelay = false;

//    py = 87;//67
    if(flag)
        iconDir = "/var/lib/kylin-assistant-daemon/custom/";
    else
        iconDir = "/var/lib/kylin-assistant-daemon/default/";

//    delayTimer = new QTimer(this);
//    connect(delayTimer, SIGNAL(timeout()), this, SLOT(slotShowDelayAnimation()));

//    ui->deleteWidget->setAutoFillBackground(true);
//    QPalette palette = ui->deleteWidget->palette();
////    palette.setColor(QPalette::Background, QColor(100,100,100,50));
//    palette.setBrush(QPalette::Window, QBrush(Qt::red));
////    palette.setBrush(QPalette::Base, QBrush(QColor(255,0,0,0)));
//    ui->deleteWidget->setPalette(palette);

//    ui->deleteWidget->setStyleSheet("QWidget{background:transparent url(:/background/res/skin/1.png);icon-size:20px 5px}");
    ui->baseWidget->setStyleSheet("QWidget{background:transparent;}");
    ui->deleteWidget->setStyleSheet("QWidget{background:transparent url(://res/conceal.png);}");
    ui->coverWidget->setStyleSheet("QWidget{background:transparent url(://res/skin-cover.png);}");

//    QPixmap pix = QPixmap("://res/menu-big-hover.png","0",Qt::AvoidDither|Qt::ThresholdDither|Qt::ThresholdAlphaDither);
//    ui->baseWidget->setMask(pix.mask());

    ui->deleteBtn->setFocusPolicy(Qt::NoFocus);
    ui->deleteBtn->setCursor(Qt::PointingHandCursor);
    ui->deleteBtn->setStyleSheet("QPushButton{background-image:url('://res/remove.png');border:0px;}");
//    ui->deleteBtn->setStyleSheet("QPushButton{background-image:url('://res/remove.png');border:0px;}QPushButton:hover{background:url('://res/cache_logo.png');}QPushButton:pressed{background:url('://res/cache_logo.png');}");
    connect(ui->deleteBtn, SIGNAL(clicked()), this, SLOT(onDeleteBtnClicked()));
    if(title == "://res/create.png") {
        iconpath = title;
        ui->name->hide();
        this->setCursor(Qt::PointingHandCursor);
    }
    else {
        iconpath = iconDir.append(title);
    }
//    ui->icon->setStyleSheet("QLabel{background-image:url('" + iconpath + "')}");
    ui->icon->installEventFilter(this);
//    QPixmap pixmap;
//    pixmap.copy(QRect(0,0,212,100)).save(iconpath);
//    ui->icon->setPixmap(pixmap);
    QPixmap pixmap(iconpath);
    pixmap.copy(QRect(0,0,130,68));
    ui->icon->setPixmap(pixmap);

    ui->name->setStyleSheet("QLabel{background: transparent; font-size:13px;color:#666666;}");
    ui->name->setText(title.replace(".png", "").replace(".jpg", ""));

//    ui->using_label->setStyleSheet("QLabel{background: transparent;}");
    ui->using_label->setStyleSheet("QLabel{background-image:url('://res/choose.png')}");
//    ui->using_label->setAutoFillBackground(true);
//    palette.setBrush(QPalette::Background, QBrush(QPixmap("://res/clothes.png")));
//    ui->using_label->setPalette(palette);
    ui->using_label->hide();
}

ItemCard::~ItemCard() {
//    if (switchTimer != NULL) {
//        disconnect(switchTimer,SIGNAL(timeout()),this,SLOT(slotSwitchAnimationStep()));
//        if(switchTimer->isActive()) {
//            switchTimer->stop();
//        }
//        delete switchTimer;
//        switchTimer = NULL;
//    }
//    if (delayTimer != NULL) {
//        disconnect(delayTimer,SIGNAL(timeout()),this,SLOT(slotShowDelayAnimation()));
//        if(delayTimer->isActive()) {
//            delayTimer->stop();
//        }
//        delete delayTimer;
//        delayTimer = NULL;
//    }
    delete ui;
}

void ItemCard::resetdislayDelBtnValue(bool flag)
{
    if(flag)
        this->dislayDelBtn = true;
    else
        this->dislayDelBtn = false;
}

void ItemCard::onDeleteBtnClicked()
{
    emit this->sendDelteSignal(iconpath);
}

void ItemCard::showUsingLogo(bool flag)
{
    if(flag)
        ui->using_label->show();
    else
        ui->using_label->hide();
}

QString ItemCard::getCardName()
{
    return this->iconpath;
}

void ItemCard::enterEvent(QEvent *)
{
    emit this->sendEnterBackground(iconpath);
    if(this->iconpath != "://res/create.png")
        ui->coverWidget->show();
    if (this->dislayDelBtn) {
        ui->deleteWidget->show();
//        this->delayTimer->start(300);
    }
}

void ItemCard::leaveEvent(QEvent *)
{
    emit this->sendLeaveBackground();
    if(this->iconpath != "://res/create.png")
        ui->coverWidget->hide();
    if (this->dislayDelBtn)
        ui->deleteWidget->hide();
//    if (this->delayTimer->isActive())
//        this->delayTimer->stop();
//    if (this->showDelay && this->dislayDelBtn) {
//        this->showDelay = false;
//        this->switchDirection = "down";
//        this->switchAnimation();
//    }
}

void ItemCard::slotShowDelayAnimation()
{
//    if(this->delayTimer->isActive())
//        this->delayTimer->stop();
//    this->switchDirection = "up";
//    this->switchAnimation();
//    this->showDelay = true;
}

void ItemCard::switchAnimation()
{
//    if(this->switchDirection == "up")
//    {
//        this->py = 87;//67
//        if(this->switchTimer->isActive())
//            this->switchTimer->stop();
//        this->switchTimer->start(30);
//    }
//    else
//    {
//        this->py = 48;//49
//        if(this->switchTimer->isActive())
//            this->switchTimer->stop();
//        this->switchTimer->start(30);
//    }
}

void ItemCard::slotSwitchAnimationStep()
{
//    if(this->switchDirection == "up")
//    {
////        if(this->py < 0)
////        {
////            this->py += 3;
////            ui->deleteWidget->move(0, this->py);
////        }
////        else
////        {
////            if(this->switchTimer->isActive())
////                this->switchTimer->stop();
////            ui->deleteWidget->move(0, 0);
////        }
//        if(this->py > 48)//49
//        {
//            this->py -= 3;
//            ui->deleteWidget->move(0, this->py);
//        }
//        else
//        {
//            if(this->switchTimer->isActive())
//                this->switchTimer->stop();
//            ui->deleteWidget->move(0, 48);//   49
//        }
//    }
//    else
//    {
////        if(this->py <= 48 && this->py > -18)// if(this->py >= 49 && this->py < 67)
////        {
////            this->py -= 3;
////            ui->deleteWidget->move(0, this->py);
////        }
////        else
////        {
////            this->switchTimer->stop();
////            ui->deleteWidget->move(0, -18);//67
////        }
//        if(this->py >= 48 && this->py < 87)// if(this->py >= 49 && this->py < 67)
//        {
//            this->py += 3;
//            ui->deleteWidget->move(0, this->py);
//        }
//        else
//        {
//            this->switchTimer->stop();
//            ui->deleteWidget->move(0, 87);//67
//        }
//    }
}

bool ItemCard::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->icon){
        if(event->type() == QEvent::MouseButtonRelease){
            if (this->iconpath == "://res/create.png")
                emit this->sendAddSignal();
            else
                emit this->sendBackgroundName(iconpath);
        }
    }
    return QObject::eventFilter(obj, event);
}
