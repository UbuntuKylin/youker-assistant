#include "cacheactionwidget.h"
#include "../component/kylintoolbutton.h"
#include "mainwindow.h"

CacheActionWidget::CacheActionWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(900, 150);
    this->setAutoFillBackground(true);
    this->setObjectName("transparentWidget");

    img_label = new QLabel();
    title_label = new QLabel();
    description_label = new QLabel();

    img_label->setScaledContents(true);//自动缩放,显示图像大小自动调整为Qlabel大小
    QPixmap label_pixmap("://res/cache.png");
    img_label->setPixmap(label_pixmap);
    img_label->setFixedSize(label_pixmap.size());

    title_label->setObjectName("whiteLabel");
    description_label->setWordWrap(true);//QLabel自动换行
    description_label->setObjectName("tipLabel");

    QVBoxLayout *layout1 = new QVBoxLayout();
    layout1->addStretch();
    layout1->addWidget(title_label);
    layout1->addWidget(description_label);
    layout1->addStretch();
    layout1->setSpacing(15);
    layout1->setMargin(0);
    layout1->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addWidget(img_label, 0, Qt::AlignVCenter);
    layout2->addLayout(layout1);
    layout2->setSpacing(20);
    layout2->setMargin(0);
    layout2->setContentsMargins(20, 20, 0, 0);

    setLayout(layout2);

    this->setLanguage();
}

CacheActionWidget::~CacheActionWidget()
{

}

void CacheActionWidget::setLanguage()
{
    title_label->setText(tr("Cleaning up the system cache"));
    description_label->setText(tr("Deep cleaning up the system cache, to save disk space"));
//    action_btn->setText(tr("Start scanning"));
//    clean_btn->setText(tr("Begin cleanup"));
}