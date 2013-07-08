/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
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
#include "modaldialog.h"
#include <QtGui>
ModalDialog::ModalDialog(QWidget *parent)
    :QDialog(parent)
{
    gridLayout = new QGridLayout;

    titlelabel = new QLabel(tr("屏幕坏点检测"));
    textlabel = new QLabel(tr("测试过程中点击鼠标左键更换颜色,点击鼠标右键退出."));
    gridLayout->addWidget(titlelabel);
    gridLayout->addWidget(textlabel);

    okButton = new QPushButton(tr("确定"));
    okButton->setDefault(true);
    cancelButton = new QPushButton(tr("取消"));
    spacerItem = new QSpacerItem(20, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);

    hboxLayout = new QHBoxLayout;
    hboxLayout->addWidget(okButton);
    hboxLayout->addWidget(cancelButton);
    hboxLayout->setSpacing(60);

    QVBoxLayout *dlgLayout = new QVBoxLayout;
    dlgLayout->setMargin(40);
    dlgLayout->addLayout(gridLayout);
    dlgLayout->addStretch(40);
    dlgLayout->addLayout(hboxLayout);
    setLayout(dlgLayout);

    resize(300, 200);

    QWidget::setTabOrder(okButton, cancelButton);
    QObject::connect(okButton,SIGNAL(clicked()),this,SLOT(accept()));
    QObject::connect(okButton,SIGNAL(clicked()),this,SLOT(monitor_check()));
    QObject::connect(cancelButton,SIGNAL(clicked()),this,SLOT(reject()));
    QMetaObject::connectSlotsByName(this);
    layout()->setSizeConstraint(QLayout::SetFixedSize);
    setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
    setWindowFlags(Qt::FramelessWindowHint);//因隐藏默认titlebar


    this->qtui = NULL;
}

void ModalDialog::monitor_check() {
    if (this->qtui)
        delete this->qtui;
    this->qtui = new QUIBO();
}
