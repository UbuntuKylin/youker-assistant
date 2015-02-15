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

#include <QStringList>
#include <QCloseEvent>
#include <QBitmap>
#include <QPainter>
#include "shredmanager.h"
#include <QFileDialog>
#include <QDir>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QDebug>
#include "filewipe.h"

QPoint widgetPosition;//界面中心位置的全局变量

ShredDialog::ShredDialog(ShredManager *plugin, QDialog *parent)
    :QDialog(parent)
{
    setWindowFlags(Qt::FramelessWindowHint);
    this->setStyleSheet("QDialog{border: 1px solid gray;border-radius:2px}");//设定边框宽度以及颜色

    this->setFixedSize(500, 471);
    process_plugin = plugin;

    title_bar = new KylinTitleBar();
    initTitleBar();

    toolkits = new Toolkits(0, this->width(), this->height());

    select_edit = new QLineEdit();
    select_edit->setFixedWidth(400);
    select_edit->setReadOnly(true);
    select_btn = new KylinEditButton(select_edit);
    shred_btn = new QPushButton();
    cacel_btn = new QPushButton();
    shred_btn->setFixedSize(91, 25);
    shred_btn->setObjectName("blackButton");
    shred_btn->setFocusPolicy(Qt::NoFocus);
    cacel_btn->setFixedSize(91, 25);
    cacel_btn->setObjectName("blackButton");
    cacel_btn->setFocusPolicy(Qt::NoFocus);

    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addStretch();
    layout1->addWidget(select_edit);
    layout1->addStretch();

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addStretch();
    layout2->addWidget(shred_btn);
    layout2->addWidget(cacel_btn);
    layout2->addStretch();
    layout2->setMargin(0);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addStretch();
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addStretch();
    layout->setSpacing(10);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(title_bar);
    main_layout->addLayout(layout);
    main_layout->setSpacing(20);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(main_layout);

    this->setLanguage();
    this->initConnect();
}

ShredDialog::~ShredDialog()
{

}

void ShredDialog::setLanguage()
{
    this->setWindowTitle(tr("Shred Manager"));
    select_edit->setText(tr("No select any file which need to be shredded"));
    shred_btn->setText(tr("Shred File"));
    cacel_btn->setText(tr("Deselect"));
}

void ShredDialog::initConnect()
{
    connect(select_btn, SIGNAL(clicked()), this, SLOT(onSelectButtonClicked()));
    connect(shred_btn, SIGNAL(clicked()), this, SLOT(onShredButtonClicked()));
    connect(cacel_btn, SIGNAL(clicked()), this, SLOT(onCacelButtonClicked()));
//    connect(title_bar, SIGNAL(showMinDialog()), this, SLOT(onMinButtonClicked()));
    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCloseButtonClicked()));
}

void ShredDialog::onCloseButtonClicked()
{
    this->close();
}

//void ShredDialog::onMinButtonClicked()
//{
//    this->showMinimized();
////    this->hide();
//}

void ShredDialog::initTitleBar()
{
    title_bar->setTitleWidth(500);
    title_bar->setTitleName(tr("Shred Manager"));
    title_bar->setTitleBackgound(":/background/res/skin/1.png");
}

void ShredDialog::onSelecteComboActivated(int index)
{
//    qDebug() << index;
}

void ShredDialog::onSelectButtonClicked()
{
    QString fileName=QFileDialog::getOpenFileName(0, tr("Select file"), QDir::homePath(), tr("All Files(*)"));
    select_edit->setText(fileName);
}

void ShredDialog::onShredButtonClicked()
{
    char* ch;
    QByteArray ba = select_edit->text().toUtf8();
    ch=ba.data();
    int result = do_file(ch);
//    qDebug() << "shred file result -> " << result;
    if (result == 0)
    {
        //success
        toolkits->alertMSG(tr("Shred successfully!"));
    }
    else
    {
        //failed
        toolkits->alertMSG(tr("Shred failed!"));
    }
}

void ShredDialog::onCacelButtonClicked()
{
    select_edit->setText(tr("No select any file which need to be shredded"));
}

void ShredDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
//  emit SignalClose();
}

void ShredDialog::paintEvent(QPaintEvent *event)
{
    widgetPosition = this->pos();
//    QBitmap objBitmap(size());
//    //QPainter用于在位图上绘画
//    QPainter painter(&objBitmap);
//    //填充位图矩形框(用白色填充)
//    painter.fillRect(rect(),Qt::white);
//    painter.setBrush(QColor(0,0,0));
//    //在位图上画圆角矩形(用黑色填充)
//    painter.drawRoundedRect(this->rect(),5,5);
//    ////使用setmask过滤即可
//    setMask(objBitmap);
}
