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

//AutoStartWidget::AutoStartWidget(QWidget *parent, SessionDispatcher *proxy) :
//    QWidget(parent),sessionproxy(proxy),
AutoStartWidget::AutoStartWidget(QDialog *parent, SessionDispatcher *proxy, QString skin) :
    QDialog(parent),sessionproxy(proxy),
    ui(new Ui::AutoStartWidget)
{
    ui->setupUi(this);
    this->setFixedSize(560, 398);
    setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("QDialog{border: 1px solid white;border-radius:1px;background-color: #ffffff;}");
    this->setWindowIcon(QIcon(":/res/kylin-assistant.png"));
    this->setWindowTitle(tr("Boot Manager"));
    tip_label = new QLabel();
    num_label = new QLabel();
    on_label = new QLabel();
    on_num_label = new QLabel();
    off_label = new QLabel();
    off_num_label = new QLabel();
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
    tip_layout->setContentsMargins(10, 0, 10, 1);
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
    status_layout->setContentsMargins(10, 0, 10, 0);
    ui->widget_2->setLayout(status_layout);

    title_bar = new KylinTitleBar(this);
    title_bar->move(0,0);
    title_bar->show();
    initTitleBar(skin);
    ui->scrollArea->setStyleSheet("QScrollArea{border: none}");
    ui->scrollArea->setFixedSize(556,300);
    ui->scrollArea->setAutoFillBackground(true);
    ui->scrollArea->setBackgroundRole(QPalette::Light);
    this->initConnect();
}

AutoStartWidget::~AutoStartWidget()
{
//    KylinTitleBar *title_bar;
    if(tip_label != NULL) {
        delete tip_label;
        tip_label = NULL;
    }
    if(num_label != NULL) {
        delete num_label;
        num_label = NULL;
    }
    if(on_label != NULL) {
        delete on_label;
        on_label = NULL;
    }
    if(on_num_label != NULL) {
        delete on_num_label;
        on_num_label = NULL;
    }
    if(off_label != NULL) {
        delete off_label;
        off_label = NULL;
    }
    if(off_num_label != NULL) {
        delete off_num_label;
        off_num_label = NULL;
    }
    if(name_label != NULL) {
        delete name_label;
        name_label = NULL;
    }
    if(status_label != NULL) {
        delete status_label;
        status_label = NULL;
    }
    for(int i=0; i<switcher_list.count(); i++)
    {
        AutoGroup *autoitem = switcher_list.at(i);
        delete autoitem;
        autoitem = NULL;
    }
    switcher_list.clear();
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
    int rowIndex = 0;
    QVBoxLayout *v_layout = new QVBoxLayout();
//    QGridLayout *v_layout = new QGridLayout();
    QSignalMapper *signal_mapper = new QSignalMapper(this);
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
        AutoGroup *auto_group = new AutoGroup();
        auto_group->setFixedHeight(50);
        auto_group->initData(tmpMap);
        if(tmpMap.value("Status") == "true")
            onNum += 1;
        else if(tmpMap.value("Status") == "false")
            offNum += 1;
        connect(auto_group, SIGNAL(autoStatusChange()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(auto_group, tmpMap.value("Path"));
        v_layout->addWidget(auto_group, 0, Qt::AlignBottom);
//        v_layout->addWidget(auto_group, rowIndex, 0);
        rowIndex += 1;
        switcher_list.append(auto_group);
    }
    v_layout->addStretch();
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(setCurrentItemAutoStatus(QString)));
    on_num_label->setText(QString::number(onNum));
    off_num_label->setText(QString::number(offNum));

//    QVBoxLayout *layout  = new QVBoxLayout();
//    layout->addLayout(v_layout);
//    layout->setSpacing(0);
//    layout->setMargin(0);
//    layout->setContentsMargins(10, 0, 10, 10);
    ui->scrollAreaWidgetContents->setLayout(v_layout);
}

void AutoStartWidget::scanAllSwitcher() {
    int count = switcher_list.count();
    onNum = offNum = 0;
    for(int i=0; i<count; i++)
    {
        AutoGroup *checkbox = switcher_list.at(i);
        if(checkbox->getSwitcherStatus())
        {
            onNum +=1;
        }
        else {
            offNum += 1;
        }
    }
    on_num_label->setText(QString::number(onNum));
    off_num_label->setText(QString::number(offNum));
}

void AutoStartWidget::setCurrentItemAutoStatus(QString dekstopName)
{
    int  start_pos = dekstopName.lastIndexOf("/") + 1;
    int end_pos = dekstopName.length();
    QString name = dekstopName.mid(start_pos, end_pos-start_pos);
    sessionproxy->changeAutoStartAppStatus(name);
    this->scanAllSwitcher();
}

void AutoStartWidget::initConnect()
{
    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCloseButtonClicked()));
}

void AutoStartWidget::initTitleBar(QString skin)
{
    title_bar->setTitleWidth(560);
    title_bar->setTitleName(tr("Boot Manager"));
//    title_bar->setTitleBackgound(":/background/res/skin/1.png");
    title_bar->setTitleBackgound(skin);
}

void AutoStartWidget::resetTitleSkin(QString skin)
{
    title_bar->resetBackground(skin);
}

void AutoStartWidget::onCloseButtonClicked()
{
    this->close();
}
