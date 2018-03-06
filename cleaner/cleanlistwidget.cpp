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

#include "cleanlistwidget.h"
#include "ui_cleanlistwidget.h"
#include <QVBoxLayout>
#include <QCheckBox>
#include "../component/utils.h"
#include <QDebug>

//CleanListWidget::CleanListWidget(QStringList &arglist, const QString title_text, QWidget *parent) :
//    QWidget(parent),titleName(title_text),
CleanListWidget::CleanListWidget(QStringList &arglist, QString skin, const QString title_text, QDialog *parent) :
    QDialog(parent),titleName(title_text),
    ui(new Ui::CleanListWidget)
{
    ui->setupUi(this);
    this->setFixedSize(560, 398);
    setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("QDialog{border: 1px solid white;border-radius:1px;background-color: #ffffff;}");
    this->setWindowIcon(QIcon(":/res/kylin-assistant.png"));
    tip_label = new QLabel();
    num_label = new QLabel();

    ui->widget_1->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(233,238,241));//#e9eef1
    ui->widget_1->setPalette(palette);

    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setStyleSheet("QScrollArea{border: none}");
    ui->scrollArea->setAutoFillBackground(true);
    ui->scrollArea->setBackgroundRole(QPalette::Light);//QPalette::Dark
//    palette.setBrush(QPalette::Window, QBrush(Qt::white));
//    ui->scrollArea->setPalette(palette);

    tip_label->setText(tr("Clean Items:"));

    QHBoxLayout *tip_layout = new QHBoxLayout();
    tip_layout->addWidget(tip_label);
    tip_layout->addWidget(num_label);
    tip_layout->addStretch();
    tip_layout->setSpacing(0);
    tip_layout->setMargin(0);
    tip_layout->setContentsMargins(10, 0, 0, 0);
    ui->widget_1->setLayout(tip_layout);

    title_bar = new KylinTitleBar(this);
    title_bar->move(0,0);
    title_bar->show();
    initTitleBar(skin);
    ui->scrollArea->setFixedSize(556,331);


    QVBoxLayout *button_layout = new QVBoxLayout;
    int count = arglist.count();
    num_label->setText(QString::number(count));
    for(int i=0; i<count; i++)
    {
        QCheckBox *checkbox = new QCheckBox(arglist.at(i));
        checkbox->setFocusPolicy(Qt::NoFocus);
        checkbox->setCheckState(Qt::Checked);
        checkbox_list.append(checkbox);
        connect(checkbox, SIGNAL(clicked()), this, SLOT(scanAllSubCheckbox()));
        button_layout->addWidget(checkbox);
    }
    button_layout->setSpacing(5);
    button_layout->setMargin(0);
    button_layout->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *layout  = new QVBoxLayout();
    layout->addLayout(button_layout);
    layout->addStretch();
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setContentsMargins(10, 0, 10, 10);
    ui->scrollAreaWidgetContents->setLayout(layout);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

    this->setLanguage();
    this->initConnect();
}

CleanListWidget::~CleanListWidget()
{
    if(tip_label != NULL) {
        delete tip_label;
        tip_label = NULL;
    }
    if(num_label != NULL) {
        delete num_label;
        num_label = NULL;
    }
    if(title_bar != NULL) {
        delete title_bar;
        title_bar = NULL;
    }
    for(int i=0; i<checkbox_list.count(); i++)
    {
        QCheckBox *box = checkbox_list.at(i);
        delete box;
        box = NULL;
    }
    checkbox_list.clear();
    delete ui;
}

QStringList CleanListWidget::getSelectedItems()
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

void CleanListWidget::scanAllSubCheckbox() {
    int count = checkbox_list.count();
    int m = 0;
    for(int i=0; i<count; i++)
    {
        QCheckBox *checkbox = checkbox_list.at(i);
        if (checkbox->isChecked()) {
            m +=1;
        }
    }
    num_label->setText(QString::number(m));
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

void CleanListWidget::resetSubCheckbox(int status) {
    if(status == 0) {
        for(int i=0; i<checkbox_list.count(); i++)
        {
            QCheckBox *checkbox = checkbox_list.at(i);
            checkbox->setChecked(false);
        }
        num_label->setText("0");
    }
    else if(status == 2) {
        for(int i=0; i<checkbox_list.count(); i++)
        {
            QCheckBox *checkbox = checkbox_list.at(i);
            checkbox->setChecked(true);
        }
        int count = checkbox_list.count();
        num_label->setText(QString::number(count));
    }
}

void CleanListWidget::setLanguage()
{

}

void CleanListWidget::initConnect()
{
    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCloseButtonClicked()));
}

void CleanListWidget::initTitleBar(QString skin)
{
    title_bar->setTitleWidth(560);
    title_bar->setTitleName(titleName);
//    title_bar->setTitleBackgound(":/background/res/skin/1.png");
    title_bar->setTitleBackgound(skin);
}

void CleanListWidget::resetTitleSkin(QString skin)
{
    title_bar->resetBackground(skin);
}


void CleanListWidget::onCloseButtonClicked()
{
    this->close();
}
