#include "infoactionwidget.h"
#include "../component/kylintoolbutton.h"
#include "mainwindow.h"

InfoActionWidget::InfoActionWidget(QWidget *parent)
	: QWidget(parent)
{
    this->setFixedSize(900, 150);
    this->setAutoFillBackground(true);
    this->setObjectName("transparentWidget");

    img_label = new QLabel();
    suggest_label = new QLabel();
//    result_label = new QLabel();

    img_label->setScaledContents(true);//自动缩放,显示图像大小自动调整为Qlabel大小
    QPixmap label_pixmap("://res/systeminfo.png");
    img_label->setPixmap(label_pixmap);
    img_label->setFixedSize(label_pixmap.size());
//    img_label->setFixedSize(80, 80);

    suggest_label->setObjectName("whiteLabel");
    suggest_label->setWordWrap(true);//QLabel自动换行
//    result_label->setWordWrap(true);//QLabel自动换行
//    result_label->setObjectName("tipLabel");

//    QVBoxLayout *layout1 = new QVBoxLayout();
//    layout1->addStretch();
//    layout1->addWidget(suggest_label);
//    layout1->addWidget(result_label);
//    layout1->addStretch();
//    layout1->setSpacing(15);
//    layout1->setMargin(0);
//    layout1->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addWidget(img_label, 0, Qt::AlignVCenter);
//    layout2->addLayout(layout1);
    layout2->addWidget(suggest_label, 0, Qt::AlignVCenter);
    layout2->setSpacing(20);
    layout2->setMargin(0);
    layout2->setContentsMargins(20, 20, 0, 0);

    setLayout(layout2);

    this->setLanguage();
}

InfoActionWidget::~InfoActionWidget()
{

}


void InfoActionWidget::setLanguage()
{
    suggest_label->setText(tr("Understand hardware information, provide more convenient channel to obtain hardware information"));//了解电脑硬件详细信息，为用户提供更加方便的获 取硬件信息渠道
//    result_label->setText(tr("了解电脑硬件详细信息，为用户提供更加方便的获 取硬件信息渠道。"));
}
