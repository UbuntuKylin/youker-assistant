#include "labelgroup.h"
#include "utils.h"
#include <QPalette>

LabelGroup::LabelGroup(QWidget *parent) :
    QWidget(parent)
{
    this->resize(ITEMWIDTH, ITEMHEIGHT);
    //边框
//    this->setStyleSheet("border:1px solid black;");

    //背景
//    this->setAutoFillBackground(true);
//    QPalette palette;
////    palette.setColor(QPalette::Background, QColor(192,253,123));
//    palette.setBrush(QPalette::Background, QBrush(QPixmap(":/background/res/bg/6.png")));
//    this->setPalette(palette);


    h_layout = new QHBoxLayout();
    key_info = new QLabel();
    value_info = new QLabel();
    key_info->setFixedSize(180, ITEMHEIGHT);
    value_info->setFixedHeight(ITEMHEIGHT);

    QFont font = key_info->font();
    font.setPointSize(14);
    key_info->setFont(font);
    key_info->setObjectName("titleLabel");
    value_info->setFont(font);
    value_info->setObjectName("grayLabel");

    h_layout->addWidget(key_info);
    h_layout->addWidget(value_info);

    h_layout->setMargin(0);//设置总的外围边框
    setLayout(h_layout);
}

//void LabelGroup::pushMap(QString key, QString value)
//{
//    this->name[key] = value;
//}

void LabelGroup::setLanguage(QString key, QString value)
{
    key_info->setText(tr("%1:").arg(key));
    value_info->setText(tr("%1").arg(value));
}
