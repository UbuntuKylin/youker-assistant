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

#include "autostartwidget.h"
#include "ui_autostartwidget.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QSignalMapper>
#include "../dbusproxy/youkersessiondbus.h"
#include "../component/utils.h"

AutoStartWidget::AutoStartWidget(QWidget *parent, SessionDispatcher *proxy) :
    QWidget(parent),sessionproxy(proxy),
    ui(new Ui::AutoStartWidget)
{
    ui->setupUi(this);
    this->setFixedSize(560, 398);
    setWindowFlags(Qt::FramelessWindowHint);
    tip_label = new QLabel();
    num_label = new QLabel();
    on_label = new QLabel();
    on_num_label = new QLabel();
    off_label = new QLabel();
    off_num_label = new QLabel();
    on_label->hide();
    on_num_label->hide();
    off_label->hide();
    off_num_label->hide();
    name_label = new QLabel();
    status_label = new QLabel();

    ui->widget_1->setAutoFillBackground(true);
    ui->widget_2->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(233,238,241));//#e9eef1
    ui->widget_1->setPalette(palette);
    palette.setColor(QPalette::Background, QColor(255,255,255));//#ffffff
    ui->widget_2->setPalette(palette);

    tip_label->setText(tr("AutoStart Items:"));
    name_label->setText(tr("App"));
    status_label->setText(tr("Status"));

    on_label->setText(tr("ON Items:"));
    off_label->setText(tr("OFF Items:"));

    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addWidget(tip_label);
    layout1->addWidget(num_label);
    layout1->setSpacing(0);
    layout1->setMargin(0);

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addWidget(on_label);
    layout2->addWidget(on_num_label);
    layout2->setSpacing(0);
    layout2->setMargin(0);

    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addWidget(off_label);
    layout3->addWidget(off_num_label);
    layout3->setSpacing(0);
    layout3->setMargin(0);

    QHBoxLayout *tip_layout = new QHBoxLayout();
    tip_layout->addLayout(layout1);
    tip_layout->addStretch();
    tip_layout->addLayout(layout2);
    tip_layout->addStretch();
    tip_layout->addLayout(layout3);
    tip_layout->setSpacing(0);
    tip_layout->setMargin(0);
    tip_layout->setContentsMargins(20, 0, 20, 0);
    ui->widget_1->setLayout(tip_layout);

//    QHBoxLayout *tip_layout = new QHBoxLayout();
//    tip_layout->addWidget(tip_label);
//    tip_layout->addWidget(num_label);
//    tip_layout->addStretch();
//    tip_layout->setSpacing(0);
//    tip_layout->setMargin(0);
//    tip_layout->setContentsMargins(20, 0, 0, 0);
//    ui->widget_1->setLayout(tip_layout);

    QHBoxLayout *status_layout = new QHBoxLayout();
    status_layout->addWidget(name_label);
    status_layout->addStretch();
    status_layout->addWidget(status_label);
    status_layout->setSpacing(0);
    status_layout->setMargin(0);
    status_layout->setContentsMargins(20, 0, 20, 0);
    ui->widget_2->setLayout(status_layout);

    title_bar = new KylinTitleBar(this);
    title_bar->move(0,0);
    title_bar->show();
    initTitleBar();
    ui->scrollArea->setFixedSize(560,302);
    this->setLanguage();
    this->initConnect();
}

AutoStartWidget::~AutoStartWidget()
{
    delete ui;
}

void AutoStartWidget::initData()
{
    sessionproxy->getAutoStartAppStatus();
}


void AutoStartWidget::readyReciveData(const QStringList &data)
{
    data_list.append(data);
}

void AutoStartWidget::readyShowUI()
{
    QVBoxLayout *v_layout = new QVBoxLayout();
    QSignalMapper *signal_mapper = new QSignalMapper(this);
//    qDebug() << data_list;
    onNum = offNum = 0;
    num_label->setText(QString::number(data_list.length()));
    for(int i =0; i<data_list.length(); i++)
    {
        QMap<QString,QString> tmpMap;
        QStringList tmp_list = data_list.at(i);
        for(int j=0;j<tmp_list.length();j++)
        {
            tmpMap.insert(tmp_list[j].split(":").at(0), tmp_list[j].split(":").at(1));
        }
        AutoGroup *auto_group = new AutoGroup(ui->scrollAreaWidgetContents);
        auto_group->initData(tmpMap);
//        qDebug() << tmpMap;
        if(tmpMap.value("Status") == "true")
            onNum += 1;
        else if(tmpMap.value("Status") == "false")
            offNum += 1;
        connect(auto_group, SIGNAL(autoStatusChange()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(auto_group, tmpMap.value("Path"));
        v_layout->addWidget(auto_group, 0, Qt::AlignBottom);
    }
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(setCurrentItemAutoStatus(QString)));
    on_num_label->setText(QString::number(onNum));
    off_num_label->setText(QString::number(offNum));

    QVBoxLayout *layout  = new QVBoxLayout();
//    layout->addWidget(title_bar);
    layout->addLayout(v_layout);
//    layout->addWidget(scroll_widget);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setContentsMargins(10, 0, 10, 10);
    ui->scrollAreaWidgetContents->setLayout(layout);
}

void AutoStartWidget::setCurrentItemAutoStatus(QString dekstopName)
{
    int  start_pos = dekstopName.lastIndexOf("/") + 1;
    int end_pos = dekstopName.length();
    QString name = dekstopName.mid(start_pos, end_pos-start_pos);
//    qDebug() << "change status->" << name;
    sessionproxy->changeAutoStartAppStatus(name);
    //need to get status to change on_num_label and off_num_label
//    onNum += 1;
//    offNum -= 1;
//    on_num_label->setText(QString::number(onNum));
//    off_num_label->setText(QString::number(offNum));
}

void AutoStartWidget::setLanguage()
{

}

void AutoStartWidget::initConnect()
{
    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCloseButtonClicked()));
}

void AutoStartWidget::initTitleBar()
{
    title_bar->setTitleWidth(560);
    title_bar->setTitleName(tr("Auto Start"));
    title_bar->setTitleBackgound(":/background/res/skin/1.png");
}

void AutoStartWidget::onCloseButtonClicked()
{
    this->close();
}

//void AutoStartWidget::onMinButtonClicked()
//{
//    this->hide();
//}
