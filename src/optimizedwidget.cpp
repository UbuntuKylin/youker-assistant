#include "optimizedwidget.h"

OptimizedWidget::OptimizedWidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(860,460);
    this->setAutoFillBackground(true);

    this->setStyleSheet("QWidget{background:#ffffff;border: none;\
                        border-bottom-right-radius:10px;\
                        border-bottom-left-radius:10px}");

    main_layout = new QVBoxLayout(this);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0,0,0,0);

    InitUI();

    this->setLayout(main_layout);
}

OptimizedWidget::~OptimizedWidget()
{

}

void OptimizedWidget::InitUI()
{
    InitTopUI();
    InitMiddleUI();
    InitBottomUI();
}

void OptimizedWidget::InitTopUI()
{
    QFrame *top_frame = new QFrame(this);
    top_frame->setFixedSize(860,100);
    top_frame->setStyleSheet("border-bottom-right-radius:0px;\
                             border-bottom-left-radius:0px");
//background:lightgray;

    top_tip = new QLabel(top_frame);
    QFont font;
    font.setPixelSize(36);
    font.setBold(QFont::Bold);
    top_tip->setFont(font);
    top_tip->setText(tr("Optimization makes computers faster."));
    top_tip->setGeometry(QRect(100,56,860,44));
    top_tip->setVisible(true);

    cancel_btn = new QPushButton(top_frame);
    cancel_btn->setText(tr("Cancel"));
    cancel_btn->setGeometry(QRect(620,27,120,36));
    cancel_btn->setStyleSheet("QPushButton{width:120px;height:36px;\
                              border:2px solid rgba(153,153,153,1);\
                              border-radius:18px;font-size:18px;}\
                              QPushButton:hover{width:120px;height:36px;\
                              border:2px solid rgba(34,103,242,1);\
                              border-radius:18px;font-size:18px;}\
                              QPushButton:pressed{width:120px;height:36px;\
                              background:rgba(34,103,242,1);color:white;\
                              border-radius:18px;font-size:18px;}");
    cancel_btn->setVisible(false);

    scan_btn = new QPushButton(top_frame);
    scan_btn->setText(tr("Optimization"));
    scan_btn->setGeometry(QRect(600,25,160,48));
    scan_btn->setStyleSheet("QPushButton{width:160px;height:48px;\
                            background:rgba(34,103,242,1);\
                            border-radius:24px;font-size:20px;color:white;}\
                            QPushButton:hover{width:160px;height:48px;\
                            background:rgba(67,127,240,1);\
                            border-radius:24px;font-size:20px;color:white;}");
    scan_btn->setVisible(false);

    spilterLine = new QFrame(top_frame);
    spilterLine->setFixedSize(860, 2);
    spilterLine->setStyleSheet("QFrame{background:rgba(238,238,238,1);}");
    spilterLine->setFrameShape(QFrame::HLine);
    spilterLine->setFrameShadow(QFrame::Plain);
    spilterLine->setGeometry(QRect(0,87,860,2));
    spilterLine->setVisible(false);

    main_layout->addWidget(top_frame);
}

void OptimizedWidget::InitMiddleUI()
{
    QFrame *middle_frame = new QFrame(this);
    middle_frame->setStyleSheet("border-bottom-right-radius:0px;\
                                border-bottom-left-radius:0px");
    middle_layout = new QHBoxLayout(middle_frame);
    middle_layout->setSpacing(0);
    middle_layout->setMargin(0);
    middle_layout->setContentsMargins(100,40,100,20);
    middle_frame->setFixedSize(860,190);

    QFrame *boot_frame = new QFrame(middle_frame);
    boot_frame->setFixedSize(215,140);
    QVBoxLayout *boot_layout = new QVBoxLayout(boot_frame);

    boot_icon = new QLabel(boot_frame);
    QPixmap icon1(":/res/boot_up.png");
    boot_icon->setPixmap(icon1);
    boot_icon->setFixedSize(icon1.size());
    boot_layout->addWidget(boot_icon);

    boot_label = new QLabel(boot_frame);
    QFont font;
    font.setPixelSize(18);
    font.setBold(QFont::Bold);
    boot_label->setFont(font);
    boot_label->setText(tr("Boot up"));
    boot_layout->addWidget(boot_label);

    QLabel *label1 = new QLabel(boot_frame);
    label1->setText(tr("Optimize boot-up software"));
    label1->setWordWrap(true);
    boot_layout->addWidget(label1);
    middle_layout->addWidget(boot_frame);

    QFrame *system_frame = new QFrame(middle_frame);
    system_frame->setFixedSize(215,140);
    QVBoxLayout *system_layout = new QVBoxLayout(system_frame);

    system_icon = new QLabel(system_frame);
    QPixmap icon2(":/res/system_speed.png");
    system_icon->setPixmap(icon2);
    system_icon->setFixedSize(icon2.size());
    system_layout->addWidget(system_icon);

    system_label = new QLabel(system_frame);
    system_label->setFont(font);
    system_label->setText(tr("System acceleration"));
    system_layout->addWidget(system_label);

    QLabel *label2 = new QLabel(system_frame);
    label2->setText(tr("Optimize system and memory settings"));
    label2->setWordWrap(true);
    system_layout->addWidget(label2);
    middle_layout->addWidget(system_frame);

    QFrame *app_frame = new QFrame(middle_frame);
    app_frame->setFixedSize(215,140);
    QVBoxLayout *app_layout = new QVBoxLayout(app_frame);

    app_icon = new QLabel(app_frame);
    QPixmap icon3(":/res/app_speed.png");
    app_icon->setPixmap(icon3);
    app_icon->setFixedSize(icon3.size());
    app_layout->addWidget(app_icon);

    app_label = new QLabel(app_frame);
    app_label->setFont(font);
    app_label->setText(tr("Software acceleration"));
    app_layout->addWidget(app_label);

    QLabel *label3 = new QLabel(app_frame);
    label3->setText(tr("Log out of software not in use"));
    label3->setWordWrap(true);
    app_layout->addWidget(label3);
    middle_layout->addWidget(app_frame);

    main_layout->addWidget(middle_frame);
}

void OptimizedWidget::InitBottomUI()
{
    QFrame *bottom_frame = new QFrame(this);
    bottom_frame->setFixedSize(860,170);
//    bottom_frame->setStyleSheet("background:lightgray");

    start_btn = new QPushButton(bottom_frame);
    start_btn->setText(tr("Accelerate now"));
    start_btn->setGeometry(QRect(100,10,220,60));
    start_btn->setStyleSheet("QPushButton{width:220px;height:60px;\
                             background:rgba(34,103,242,1);\
                             border-radius:30px;font-size:24px;color:white;}\
                             QPushButton:hover{width:220px;height:60px;\
                             background:rgba(67,127,240,1);\
                             border-radius:30px;font-size:24px;color:white;}");

    main_layout->addWidget(bottom_frame);
}
