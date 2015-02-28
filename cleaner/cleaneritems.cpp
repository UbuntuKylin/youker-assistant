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

#include "cleaneritems.h"
#include "../component/kylintoolbutton.h"
#include "mainwindow.h"
#include <QDebug>

CleanerItems::CleanerItems(QStringList &arglist, int height, const QString title_text, QWidget *parent)
    : QWidget(parent),titleName(title_text)/*, widgetHeight(height)*/
{
    this->setFixedSize(410, height);
//    this->setObjectName("transparentWidget");
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    this->setPalette(palette);

    title_bar = new KylinTitleBar();
    initTitleBar();

//    checkbox1 = new QCheckBox("11111");
//    checkbox1->setCheckState(Qt::Checked);
//    checkbox2 = new QCheckBox("2222222");
//    checkbox2->setCheckState(Qt::Checked);
//    checkbox3 = new QCheckBox("3333333");
//    checkbox3->setCheckState(Qt::Checked);
//    QVBoxLayout *layoutbox = new QVBoxLayout;
//    layoutbox->addWidget(checkbox1);
//    layoutbox->addWidget(checkbox2);
//    layoutbox->addWidget(checkbox3);
//    checkbox_list.append(checkbox1);
//    checkbox_list.append(checkbox2);
//    checkbox_list.append(checkbox3);
//    connect(checkbox1, SIGNAL(clicked()), this, SLOT(scanAllSubCheckbox()));
//    connect(checkbox2, SIGNAL(clicked()), this, SLOT(scanAllSubCheckbox()));
//    connect(checkbox3, SIGNAL(clicked()), this, SLOT(scanAllSubCheckbox()));
//    setLayout(layoutbox);


    QVBoxLayout *button_layout = new QVBoxLayout;
    int count = arglist.count();
    //    QSignalMapper *signal_mapper = new QSignalMapper(this);
    for(int i=0; i<count; i++)
    {
        QCheckBox *checkbox = new QCheckBox(arglist.at(i));
        checkbox->setFocusPolicy(Qt::NoFocus);
        checkbox->setCheckState(Qt::Checked);
//        checkbox->setStatusTip("kobe");
        checkbox_list.append(checkbox);
//        connect(checkbox, SIGNAL(clicked()), signal_mapper, SLOT(map()));
        connect(checkbox, SIGNAL(clicked()), this, SLOT(scanAllSubCheckbox()));
//        signal_mapper->setMapping(checkbox, QString::number(i, 10));
        button_layout->addWidget(checkbox);
    }
    button_layout->setSpacing(20);
    button_layout->setMargin(0);
    button_layout->setContentsMargins(0, 0, 0, 0);
//    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(switchPageIndex(QString)));
//    setLayout(button_layout);

    okBtn = new QPushButton();
    okBtn->setFixedSize(91, 25);
    okBtn->setObjectName("blackButton");
    okBtn->setFocusPolicy(Qt::NoFocus);
//    okBtn->setStyleSheet("QPushButton{font-size:14px;background:#0bc406;border:1px solid #03a603;color:white;}QPushButton:hover{background-color:#16d911;border:1px solid #03a603;color:white;}QPushButton:pressed{background-color:#07b302;border:1px solid #037800;color:white;}");

    QHBoxLayout *btn_layout  = new QHBoxLayout();
    btn_layout->addStretch();
    btn_layout->addWidget(okBtn);
    btn_layout->setMargin(0);
    btn_layout->setContentsMargins(0, 0, 18, 10);

    group_box = new QGroupBox();
    group_box->setTitle(titleName);
    QFont group_box_font = group_box->font();
    group_box_font.setBold(true);
    group_box->setFont(group_box_font);
    group_box->setFixedWidth(380);
    group_box->setLayout(button_layout);
    group_box->setContentsMargins(10, 10, 10, 10);

    QHBoxLayout *group_layout = new QHBoxLayout();
    group_layout->addWidget(group_box);
    group_layout->setMargin(0);
    group_layout->setContentsMargins(10, 10, 10, 10);

    QVBoxLayout *main_layout  = new QVBoxLayout();
    main_layout->addWidget(title_bar);
    main_layout->addLayout(group_layout);
//    main_layout->addWidget(group_box);
    main_layout->addStretch();
    main_layout->addLayout(btn_layout);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(main_layout);

    this->initConnect();
    this->setLanguage();
}

CleanerItems::~CleanerItems()
{

}

void CleanerItems::initConnect()
{
    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCloseButtonClicked()));
    connect(okBtn,SIGNAL(clicked()), this, SLOT(onCloseButtonClicked()));
}

void CleanerItems::onCloseButtonClicked()
{
    this->close();
}

void CleanerItems::initTitleBar()
{
    title_bar->setTitleWidth(410);
    title_bar->setTitleName(titleName);
    title_bar->setTitleBackgound(":/background/res/skin/1.png");
}

int CleanerItems::getItemCount()
{
    return checkbox_list.count();
}

QStringList CleanerItems::getSelectedItems()
{
    QStringList text_list;
    int count = checkbox_list.count();
    for(int i=0; i<count; i++)
    {
        QCheckBox *checkbox = checkbox_list.at(i);
        if (checkbox->isChecked()) {
            text_list.append(checkbox->text());
        }
    }
    return text_list;
}

void CleanerItems::setLanguage()
{
    okBtn->setText(tr("OK"));
}

void CleanerItems::scanAllSubCheckbox() {
    int count = checkbox_list.count();
    int m = 0;
    for(int i=0; i<count; i++)
    {
        QCheckBox *checkbox = checkbox_list.at(i);
        if (checkbox->isChecked()) {
            m +=1;
        }
    }
    if (m == 0) {
        emit this->notifyMainCheckBox(0);
    }
    else if (m == count) {
        emit this->notifyMainCheckBox(2);
    }
    else {
        emit this->notifyMainCheckBox(1);
    }
}

void CleanerItems::resetSubCheckbox(int status) {
    if(status == 0) {
        for(int i=0; i<checkbox_list.count(); i++)
        {
            QCheckBox *checkbox = checkbox_list.at(i);
            checkbox->setChecked(false);
        }
    }
    else if(status == 2) {
        for(int i=0; i<checkbox_list.count(); i++)
        {
            QCheckBox *checkbox = checkbox_list.at(i);
            checkbox->setChecked(true);
        }
    }
}
