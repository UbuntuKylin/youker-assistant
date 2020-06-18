#include "fanwidget.h"
#include <QLabel>

Fanwidget::Fanwidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(700,460);
    this->setAutoFillBackground(true);

    this->setStyleSheet("QWidget{background:#ffffff;border: none;\
                        border-bottom-right-radius:0px;\
                        border-bottom-left-radius:10px}");

    main_layout = new QVBoxLayout(this);
    main_layout->setSpacing(20);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(64,32,64,65);

    InitUI();

}

Fanwidget::~Fanwidget()
{

}

void Fanwidget::InitUI()
{
    QWidget *top_widget = new QWidget(this);
    top_widget->setFixedSize(572,48);
    top_layout = new QHBoxLayout(top_widget);
    top_layout->setSpacing(0);
    top_layout->setMargin(0);
    top_layout->setContentsMargins(0,0,0,0);
    main_layout->addWidget(top_widget);

    QFrame *spilterLine = new QFrame(this);
    spilterLine->setFixedSize(572, 2);
    spilterLine->setStyleSheet("QFrame{background:rgba(238,238,238,1);}");
    spilterLine->setFrameShape(QFrame::HLine);
    spilterLine->setFrameShadow(QFrame::Plain);
    main_layout->addWidget(spilterLine);

    QWidget *bottom_widget = new QWidget(this);
    bottom_widget->setFixedSize(572,320);
    bottom_layout = new QHBoxLayout(bottom_widget);
    bottom_layout->setSpacing(0);
    bottom_layout->setMargin(0);
    bottom_layout->setContentsMargins(0,0,0,0);
    main_layout->addWidget(bottom_widget);
    main_layout->addStretch();

    Initwidgettop();
    Initwidgetbottom();

    this->setLayout(main_layout);
}

void Fanwidget::Initwidgettop()
{
    QFrame *top_frame = new QFrame();
    QFrame *frame = new QFrame();
    QHBoxLayout *this_top_layout = new QHBoxLayout(top_frame);
    this_top_layout->setSpacing(12);
    this_top_layout->setMargin(0);
    this_top_layout->setContentsMargins(0,0,0,0);
    QVBoxLayout *this_layout = new QVBoxLayout(frame);
    this_layout->setSpacing(0);
    this_layout->setMargin(0);
    this_layout->setContentsMargins(0,0,0,0);

    QLabel *fan_icon = new QLabel();
    QLabel *top_fan_speed = new QLabel();
    QLabel *tip_speed = new QLabel();

    QPixmap check_pixmap(":/res/fan.png");
    fan_icon->setPixmap(check_pixmap);
    fan_icon->setFixedSize(check_pixmap.size());

    QFont font;
    font.setBold(QFont::Bold);
    font.setPixelSize(18);
    top_fan_speed->setFont(font);
    top_fan_speed->setText(tr("The fan is working fine, averaging ")+this->Speed+tr(" rpm/s"));
    this_layout->addWidget(top_fan_speed);

    QFont font1;
//    font1.setBold(QFont::Bold);
    font1.setPixelSize(14);
    tip_speed->setFixedHeight(15);
    tip_speed->setFont(font1);
    tip_speed->setText(tr("Maximum 7600 rpm/s, minimum 2546 rpm/s."));
    this_layout->addWidget(tip_speed);

    this_top_layout->addWidget(fan_icon);
    this_top_layout->addWidget(frame);

    top_layout->addWidget(top_frame,1,Qt::AlignLeft);
}

void Fanwidget::Initwidgetbottom()
{
    QFrame *this_frame = new QFrame();
    QFrame *frame = new QFrame();
    QVBoxLayout *h_layout = new QVBoxLayout(this_frame);
    h_layout->setSpacing(0);
    h_layout->setMargin(0);
    h_layout->setContentsMargins(0,0,0,0);
    QVBoxLayout *v_layout = new QVBoxLayout(frame);
    v_layout->setSpacing(0);
    v_layout->setMargin(0);
    v_layout->setContentsMargins(0,54,0,0);

    QLabel *icon_lable = new QLabel();
    QLabel *speed_lable = new QLabel();
    QLabel *tip_text = new QLabel();

    QMovie *movie = new QMovie(":/res/fan-1.gif");
    movie->setSpeed(300);
    icon_lable->setMovie(movie);
    icon_lable->setFixedSize(158,158);
    movie->start();
    v_layout->addWidget(icon_lable);

    speed_lable->setFont(QFont("",24,QFont::Bold));
    speed_lable->setText(this->Speed+tr(" rpm/s"));
    h_layout->addStretch(1);
    h_layout->addWidget(speed_lable,1,Qt::AlignHCenter);

    tip_text->setFont(QFont("",14,QFont::Normal));
    tip_text->setText(tr("current speed"));
    h_layout->addWidget(tip_text,1,Qt::AlignHCenter);
    h_layout->addStretch(1);

    v_layout->addWidget(this_frame);

    bottom_layout->addWidget(frame,0,Qt::AlignHCenter);
}
