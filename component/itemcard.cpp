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

ItemCard::ItemCard(QString title, QWidget *parent) :
    QWidget(parent),
    ui(new Ui::ItemCard)
{
    ui->setupUi(this);
    switchTimer = new QTimer();
    connect(switchTimer, SIGNAL(timeout()), this, SLOT(slotSwitchAnimationStep()));

    //delay show animation
    showDelay = false;

    py = 100;
    iconDir = "/var/lib/youker-assistant-daemon/background/";

    delayTimer = new QTimer(this);
    connect(delayTimer, SIGNAL(timeout()), this, SLOT(slotShowDelayAnimation()));

//    ui->deleteWidget->setWindowOpacity(0.5);
    ui->deleteWidget->setStyleSheet("QWidget{background: transparent;}");
//    ui->deleteWidget->setAttribute(Qt::WA_TranslucentBackground, true);
    ui->deleteWidget->setAutoFillBackground(true);
    QPalette palette = ui->deleteWidget->palette();
    palette.setColor(QPalette::Background, QColor(100,100,100,50));
//    palette.setBrush(QPalette::Window, QBrush(Qt::lightGray));
//    palette.setBrush(QPalette::Base, QBrush(QColor(255,0,0,0)));
    ui->deleteWidget->setPalette(palette);


    ui->deleteBtn->setFocusPolicy(Qt::NoFocus);
    ui->deleteBtn->setCursor(Qt::PointingHandCursor);
    ui->deleteBtn->setStyleSheet("QPushButton{background-image:url('://res/cache_logo_gray.png');border:0px;}QPushButton:hover{background:url('://res/cache_logo.png');}QPushButton:pressed{background:url('://res/cache_logo.png');}");
    connect(ui->deleteBtn, SIGNAL(clicked()), this, SLOT(onDeleteBtnClicked()));

    iconpath = iconDir.append(title);
//    ui->icon->setStyleSheet("QLabel{background-image:url('" + iconpath + "')}");
    ui->icon->installEventFilter(this);
//    QPixmap pixmap;
//    pixmap.copy(QRect(0,0,212,100)).save(iconpath);
//    ui->icon->setPixmap(pixmap);
    QPixmap pixmap(iconpath);
    pixmap.copy(QRect(0,0,212,100));
    ui->icon->setPixmap(pixmap);

    ui->name->setStyleSheet("QLabel{background: transparent; font-size:13px;font-weight:bold;color:#666666;}");
    ui->name->setText(title.replace(".png", "").replace(".jpg", ""));

//    ui->using_label->setStyleSheet("QLabel{background: transparent;}");
    ui->using_label->setStyleSheet("QLabel{background-image:url('://res/clothes.png')}");
//    ui->using_label->setAutoFillBackground(true);
//    palette.setBrush(QPalette::Background, QBrush(QPixmap("://res/clothes.png")));
//    ui->using_label->setPalette(palette);
    ui->using_label->hide();
}

ItemCard::~ItemCard() {
    if (switchTimer != NULL) {
        disconnect(switchTimer,SIGNAL(timeout()),this,SLOT(slotSwitchAnimationStep()));
        if(switchTimer->isActive()) {
            switchTimer->stop();
        }
        delete switchTimer;
        switchTimer = NULL;
    }
    if (delayTimer != NULL) {
        disconnect(delayTimer,SIGNAL(timeout()),this,SLOT(slotShowDelayAnimation()));
        if(delayTimer->isActive()) {
            delayTimer->stop();
        }
        delete delayTimer;
        delayTimer = NULL;
    }
    delete ui;
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

void ItemCard::enterEvent(QEvent *)
{
    emit this->sendEnterBackground(iconpath);
    this->delayTimer->start(300);
}

void ItemCard::leaveEvent(QEvent *)
{
    emit this->sendLeaveBackground();
    if (this->delayTimer->isActive())
        this->delayTimer->stop();
    if (this->showDelay) {
        this->showDelay = false;
        this->switchDirection = "down";
        this->switchAnimation();
    }
}

void ItemCard::slotShowDelayAnimation()
{
    if(this->delayTimer->isActive())
        this->delayTimer->stop();
    this->switchDirection = "up";
    this->switchAnimation();
    this->showDelay = true;
}

void ItemCard::switchAnimation()
{
    if(this->switchDirection == "up")
    {
        this->py = 100;
        if(this->switchTimer->isActive())
            this->switchTimer->stop();
        this->switchTimer->start(30);
    }
    else
    {
        this->py = 68;
        if(this->switchTimer->isActive())
            this->switchTimer->stop();
        this->switchTimer->start(30);
    }
}

void ItemCard::slotSwitchAnimationStep()
{
    if(this->switchDirection == "up")
    {
        if(this->py > 68)
        {
            this->py -= 4;
            ui->deleteWidget->move(0, this->py);
        }
        else
        {
            if(this->switchTimer->isActive())
                this->switchTimer->stop();
            ui->deleteWidget->move(0, 68);
        }
    }
    else
    {
        if(this->py >= 68 && this->py < 100)
        {
            this->py += 4;
            ui->deleteWidget->move(0, this->py);
        }
        else
        {
            this->switchTimer->stop();
            ui->deleteWidget->move(0, 100);
        }
    }
}

bool ItemCard::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->icon){
        if(event->type() == QEvent::MouseButtonRelease){
            emit this->sendBackgroundName(iconpath);
        }
    }
    return QObject::eventFilter(obj, event);
}
