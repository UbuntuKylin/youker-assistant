#include "quibo.h"
#include "ui_quibo.h"

QUIBO::QUIBO(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::QUIBO)
{
    ui->setupUi(this);

    this->colors = new QStringList();
    this->colors->append("blue");
    this->colors->append("purple");
    this->colors->append("green");
    this->colors->append("orange");
    this->colors->append("red");
    this->colors->append("black");
    this->colors->append("white");
    ui->bg->setStyleSheet("QLabel{background-color:" + this->colors->at(0)  + ";}");
    this->cindex = 1;

    this->show();
    this->setWindowState(Qt::WindowActive);
    this->setWindowState(Qt::WindowFullScreen);
}

QUIBO::~QUIBO()
{
    delete ui;
}

void QUIBO::mouseReleaseEvent(QMouseEvent *me){
    if(me->button() == Qt::LeftButton){
        this->changeColor();
    }else if(me->button() == Qt::RightButton){
        exit(0);
    }else{
    }
}

void QUIBO::changeColor(){
    if(this->cindex >= 7){
        exit(0);
    }else{
        ui->bg->setStyleSheet("QLabel{background-color:" + this->colors->at(this->cindex)  + ";}");
        this->cindex ++;
    }
}
