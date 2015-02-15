/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "kylincheckbox.h"
//#include "../component/kylintoolbutton.h"
//#include "mainwindow.h"
#include <QVBoxLayout>
#include <QDebug>
#include <QFontMetrics>

KylinCheckBox::KylinCheckBox(QWidget *parent, const QString &picture)
	: QWidget(parent)
{
//    qDebug() << "init main.....";
//    this->setFixedSize(260, 90);
    //set white background color
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    this->setPalette(palette);

    img_btn = new QPushButton();
    img_btn->setFocusPolicy(Qt::NoFocus);
    checkbox = new QCheckBox(this);
    checkbox->setObjectName("mainCheckBox");
    checkbox->setTristate(true);
    checkbox->setEnabled(true);
    checkbox->setCheckState(Qt::Checked);

    name_label = new QLabel();
    name_label->setObjectName("middleblackLabel");
    name_label->setAlignment(Qt::AlignCenter);
    description_label = new QLabel();
    description_label->setAlignment(Qt::AlignCenter);
    description_label->setObjectName("smallgrayLabel");




//    custom_btn = new QPushButton();
//    custom_btn->setFocusPolicy(Qt::NoFocus);
//    custom_btn->setObjectName("checkButton");
//    custom_btn->setCursor(Qt::PointingHandCursor);

//    img_btn->setScaledContents(true);//自动缩放,显示图像大小自动调整为Qlabel大小
//    QPixmap label_pixmap("://res/camera-uk.png");
//    img_btn->setPixmap(label_pixmap);
//    img_btn->setFixedSize(label_pixmap.size());
    img_btn->setFocusPolicy(Qt::NoFocus);
//    QPixmap pixmap("://res/camera-uk.png");
    QPixmap pixmap(picture);
    img_btn->setIcon(pixmap);
    img_btn->setIconSize(pixmap.size());
//    img_btn->setIconSize(QSize(72, 72));
    img_btn->setObjectName("transparentButton");

//    checkbox->setAutoFillBackground(true);
    checkbox->show();
//    checkbox->move(151-checkbox->width(), 0);
    checkbox->move(152, 60);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(img_btn);
    main_layout->addWidget(name_label);
    main_layout->addWidget(description_label);
//    main_layout->addWidget(custom_btn);
    main_layout->setSpacing(5);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    setLayout(main_layout);
    this->initConnect();


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
}

KylinCheckBox::~KylinCheckBox()
{

}

void KylinCheckBox::onZoneClicked()
{
    if(checkbox->checkState() == 0) {
        checkbox->setCheckState(Qt::Checked);
        emit this->spreadStatus(2);
    }
    else if(checkbox->checkState() == 1) {
        checkbox->setCheckState(Qt::Checked);
        emit this->spreadStatus(2);
    }
    else if(checkbox->checkState() == 2) {
        checkbox->setCheckState(Qt::Unchecked);
        emit this->spreadStatus(0);
    }
}

//sub item's change to make it work
void KylinCheckBox::resetMainStatus(int status)
{
    if(status == 0) {
        checkbox->setCheckState(Qt::Unchecked);
    }
    else if(status == 1) {
        checkbox->setCheckState(Qt::PartiallyChecked);
    }
    else if(status == 2) {
        checkbox->setCheckState(Qt::Checked);
    }
}

void KylinCheckBox::initConnect()
{
//    connect(img_btn, SIGNAL(clicked()), this, SLOT(onZoneClicked()));
//    connect(custom_btn, SIGNAL(clicked()), this, SIGNAL(customButtonClicked()));
    connect(img_btn, SIGNAL(clicked()), this, SIGNAL(customButtonClicked()));
}

void KylinCheckBox::setLabelText(const QString &name, const QString &tip)
{
//    QFont font(name_label->font());
//    QFontMetrics fm(font);
//    name_label->setText(fm.elidedText(name), Qt::ElideRight, name_label->width());
//    description_label->setText(fm.elidedText(tip), Qt::ElideRight, description_label->width());


    QFont ft;
    QFontMetrics fm(ft);
    QString elided_text = fm.elidedText(name, Qt::ElideRight, 260);
    name_label->setText(elided_text);
    elided_text = fm.elidedText(tip, Qt::ElideRight, 260);
    description_label->setText(elided_text);
}
