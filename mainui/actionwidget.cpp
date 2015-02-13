#include "actionwidget.h"
//#include "../component/kylintoolbutton.h"
//#include "mainwindow.h"

ActionWidget::ActionWidget(QWidget *parent)
	: QWidget(parent)
{
    this->setFixedSize(900, 227);
    this->setAutoFillBackground(true);

//    is_move = false;
//    this->setAutoFillBackground(true);
////    QPalette palette_back;
////    palette_back.setBrush(QPalette::Background, QBrush(QPixmap(":/background/res/bg/1.png")));
////    this->setPalette(palette_back);

//    suggest_label = new QLabel();
//    result_label = new QLabel();
//    scan_button = new QPushButton();
//    back_button = new QPushButton();

//    loading_label = new LoadingLabel();
//    loading_label->show();
////    movie_label->setScaledContents(true);//设置movie_label自动缩放,显示图像大小自动调整为Qlabel大小
////    QPixmap label_pixmap("");
////    movie_label->setPixmap(label_pixmap);
////    movie_label->setFixedSize(label_pixmap.size());

//    suggest_label->setObjectName("whiteLabel");
//    result_label->setWordWrap(true);//QLabel自动换行
//    result_label->setObjectName("tipLabel");

//    scan_button->setFixedSize(204, 65);
//    scan_button->setFocusPolicy(Qt::NoFocus);
//    QPixmap pixmap("://res/scan.png");
//    scan_button->setIcon(pixmap);
//    scan_button->setIconSize(pixmap.size());
//    scan_button->setObjectName("greenButton");
////    QFont scan_font = scan_button->font();
////    scan_font.setPointSize(16);
////    scan_button->setFont(scan_font);
//    back_button->setFocusPolicy(Qt::NoFocus);
//    back_button->setFixedSize(50, 30);
//    back_button->setObjectName("underlineButton");

//    //set underline
//    //    QFont font = back_button->font();
//    //    font.setUnderline(true);
//    //    back_button->setFont(font);

//    //set scan button text color
////    QPalette palette;
////    palette.setColor(QPalette::ButtonText, QColor(255,17,135));
////    scan_button->setPalette(palette);

//    QVBoxLayout *layout1 = new QVBoxLayout();
//    layout1->addStretch();
//    layout1->addWidget(suggest_label);
//    layout1->addWidget(result_label);
//    layout1->addStretch();
//    layout1->setSpacing(15);
//    layout1->setContentsMargins(0, 20, 0, 0);

//    QHBoxLayout *layout2 = new QHBoxLayout();
//    layout2->addWidget(loading_label, 0, Qt::AlignHCenter);
//    layout2->addLayout(layout1);
//    layout2->setSpacing(20);
//    layout2->setContentsMargins(0, 0, 0, 0);

//    QVBoxLayout *layout3 = new QVBoxLayout();
//    layout3->addStretch();
//    layout3->addWidget(scan_button, 0, Qt::AlignRight);
//    layout3->addWidget(back_button, 0, Qt::AlignRight);
//    layout3->addStretch();
//    layout3->setSpacing(10);
//    layout3->setContentsMargins(0, 20, 0, 0);

//    QHBoxLayout *main_layout = new QHBoxLayout();
//    main_layout->addLayout(layout2);
//    main_layout->addStretch();
//    main_layout->addLayout(layout3);
//    main_layout->setSpacing(0);
//    main_layout->setMargin(0);
//    main_layout->setContentsMargins(10, 30, 44, 0);

//    setLayout(main_layout);

//    this->initConnect();
//    this->setLanguage();
}

ActionWidget::~ActionWidget()
{

}

//void ActionWidget::initConnect()
//{
//    connect(scan_button, SIGNAL(clicked()), this, SLOT(onStartButtonClicked()));
//    connect(back_button, SIGNAL(clicked()), this, SLOT(onEndButtonClicked()));
//}

//void ActionWidget::setLanguage()
//{
//    suggest_label->setText(tr("全面检测系统，使系统更加安全，运行更流畅！"));
//    result_label->setText(tr("上次检测时间为2014-07-07 16:40:35 星期一，清理了4.84KB垃圾。"));
//    scan_button->setText(tr("开始扫描"));
//    back_button->setText(tr("Back"));
//}

//void ActionWidget::onStartButtonClicked()
//{
//    loading_label->startLoading();
//}

//void ActionWidget::onEndButtonClicked()
//{
//    loading_label->stopLoading();
//}
