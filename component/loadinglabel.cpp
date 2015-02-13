#include "loadinglabel.h"
#include <QHBoxLayout>
#include <QBitmap>
#include <QDebug>

LoadingLabel::LoadingLabel(QWidget *parent, bool flag) :
    QLabel(parent), bigFlag(flag)
{
    if(bigFlag) {
        this->setFixedSize(150, 150);
    }
    else {
        this->setFixedSize(96, 96);
    }
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground, true);
    currentpage = 0;
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(changeAnimationStep()));

    this->loadAllPictures();
    this->raise();

    //init animation
    QPixmap cur_pix = png_vector.at(0);
    this->setPixmap(cur_pix);
    setMask(QBitmap(cur_pix.mask()));
}

LoadingLabel::~LoadingLabel()
{
    disconnect(timer,SIGNAL(timeout()),this,SLOT(changeAnimationStep()));
    if(timer->isActive()) {
        timer->stop();
    }
    if (timer != NULL) {
        delete timer;
        timer = NULL;
    }
}

void LoadingLabel::changeAnimationStep()
{
    if(currentpage == 18)
    {
        currentpage = 0;
    }
    QPixmap cur_pix = png_vector.at(currentpage);
    this->setPixmap(cur_pix);
    setMask(QBitmap(cur_pix.mask()));
    currentpage += 1;
}

void LoadingLabel::loadAllPictures()
{
    QString path;
    if(bigFlag)
        path = ":/movie/res/loading/";
    else
        path = ":/movie/res/loading/small/";
    for(int i =1; i< 19; i++)
    {
        QPixmap img = QPixmap(path + QString::number(i, 10) + ".png");
        png_vector.append(img);
    }
}

void LoadingLabel::startLoading()
{
    currentpage = 0;
    timer->start(60);
}

void LoadingLabel::stopLoading()
{
    timer->stop();
}
