#include "toolkits.h"

Toolkits::Toolkits(QObject *parent) :
    QObject(parent)
{
    this->mainwindow_width = 850;
    this->mainwindow_height = 600;
    this->alert_width = 200;
    this->alert_height = 75;

    alertBG = new AlertDialog();
    this->alertTimer = new QTimer(this);
    connect(alertTimer, SIGNAL(timeout()), this, SLOT(updateAlert()));
    this->alertDelayTimer = new QTimer(this);
    connect(alertDelayTimer, SIGNAL(timeout()), this, SLOT(hideAlert()));
    this->alertGOE = new QGraphicsOpacityEffect();
    this->alertBG->setGraphicsEffect(alertGOE);
    this->ao = 0.0;
//    this->alertBG->show();
    this->alertBG->hide();
}

//启动alert提示
void Toolkits::alertMSG(const QString &alertText, int parent_x, int parent_y){
    this->alert_x = parent_x + (mainwindow_width / 2) - (alert_width  / 2);
    this->alert_y = parent_y + mainwindow_height - 200;

    this->ay = this->alert_y;
    this->ao = 0.0;
    this->alertBG->move(this->alert_x, this->alert_y);
    this->alertGOE->setOpacity(this->ao);
    this->alertBG->setMSG(alertText);
    this->alertBG->show();
    this->alertTimer->start(15);
}
//alert提示框的步处理
void Toolkits::updateAlert(){
    if(this->ao < 0.90){
        this->ao += 0.02;
        this->alertGOE->setOpacity(this->ao);
    }
    if(this->ay <= (this->alert_y - 150)){
        this->alertTimer->stop();
        //5秒后自动关闭alert提示框
        this->alertDelayTimer->start(3000);
    }else{
        this->ay -= 3;
        this->alertBG->move(this->alert_x,this->ay);
    }
}
//隐藏alert提示框
void Toolkits::hideAlert(){
    this->alertBG->hide();
    this->alertDelayTimer->stop();
}
