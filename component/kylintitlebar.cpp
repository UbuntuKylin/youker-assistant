#include "kylintitlebar.h"
#include <QDebug>
#include <QHBoxLayout>

KylinTitleBar::KylinTitleBar(QWidget *parent) :
    QWidget(parent)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedHeight(32);
    this->setAutoFillBackground(true);

    title_label = new QLabel();
    title_label->setAlignment(Qt::AlignCenter);
    logo_label = new QLabel();
    logo_label->setFixedSize(22, 22);
    logo_label->setFrameShape(QFrame::NoFrame);
    logo_label->setAutoFillBackground(true);

    logo_label->setScaledContents(true);//自动缩放,显示图像大小自动调整为Qlabel大小
    QPixmap label_pixmap("://res/icon.png");
    logo_label->setPixmap(label_pixmap);
//    logo_label->setFixedSize(label_pixmap.size());
//    QPalette palette;
//    palette.setBrush(QPalette::Background, QBrush(QPixmap("://res/logo.png")));
//    logo_label->setPalette(palette);

//    QHBoxLayout *label_layout = new QHBoxLayout();
//    label_layout->addWidget(logo_label, 0, Qt::AlignVCenter);
//    label_layout->addWidget(title_label, 0, Qt::AlignVCenter);
//    label_layout->setSpacing(5);
//    label_layout->setMargin(0);
//    label_layout->setContentsMargins(2, 2, 0, 0);

//    min_btn = new SystemButton();
    close_btn = new SystemButton();
//    min_btn->loadPixmap(":/sys/res/sysBtn/min_button.png");
    close_btn->loadPixmap(":/sys/res/sysBtn/close_button.png");

//    QHBoxLayout *btn_layout = new QHBoxLayout();
//    btn_layout->addWidget(min_btn, 0, Qt::AlignTop);
//    btn_layout->addWidget(close_btn, 0, Qt::AlignVCenter);
    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(close_btn, 0, Qt::AlignVCenter);
//    main_layout->addLayout(btn_layout);
    main_layout->addStretch();
    main_layout->addWidget(title_label, 0, Qt::AlignVCenter);
    main_layout->addStretch();
    main_layout->addWidget(logo_label, 0, Qt::AlignVCenter);
//    main_layout->addLayout(label_layout);

    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 2, 0);
    setLayout(main_layout);

//    connect(min_btn, SIGNAL(clicked()), this, SIGNAL(showMinDialog()));
    connect(close_btn, SIGNAL(clicked()), this, SIGNAL(closeDialog()));
}

KylinTitleBar::~KylinTitleBar(void)
{
}

void KylinTitleBar::resizeEvent(QResizeEvent *event)
{
    //width
    this->setFixedWidth(title_width);

    //backgrond
    QPalette palette_widget;
    palette_widget.setBrush(QPalette::Background, QBrush(QPixmap(backgroud_image)));
    setPalette(palette_widget);

    //title and font
    title_label->setText(title_content);
    QPalette objPalette = palette();
    objPalette.setColor(QPalette::WindowText, Qt::white);
    title_label->setPalette(objPalette);
    QFont &objFont = const_cast<QFont&>(font());
    objFont.setWeight(QFont::Bold);
    title_label->setFont(objFont);
}

void KylinTitleBar::mousePressEvent ( QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        if(event->y() < 5 || event->x() < 5 || rect().width() - event->x() < 5) {
            event->ignore();
            return;
        }
        press_point = event->globalPos();
        left_btn_pressed = true;
    }
    event->ignore();
}

void KylinTitleBar::mouseMoveEvent ( QMouseEvent *event)
{
    if(left_btn_pressed) {
        move_point = event->globalPos();
        QWidget *pMainWindow = (qobject_cast<QWidget *>(parent()));
        pMainWindow->move(pMainWindow->pos() + move_point - press_point);
        press_point = move_point;
    }
    event->ignore();
}

void KylinTitleBar::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        left_btn_pressed = false;
    }
    event->ignore();
}
