/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
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

#include "renicedialog.h"
#include "../../component/utils.h"
#include "util.h"

#include <QApplication>
#include <QDesktopWidget>
#include <QGraphicsDropShadowEffect>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QIcon>

ReniceDialog::ReniceDialog(const QString &title, QWidget *parent)
    : QDialog(parent)
    , m_mousePressed(false)
{
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setFixedSize(464, 240);
    this->setFixedSize(464+SHADOW_LEFT_TOP_PADDING+SHADOW_LEFT_TOP_PADDING, 240+SHADOW_RIGHT_BOTTOM_PADDING+SHADOW_RIGHT_BOTTOM_PADDING);
    this->setContentsMargins(SHADOW_LEFT_TOP_PADDING,SHADOW_LEFT_TOP_PADDING,SHADOW_RIGHT_BOTTOM_PADDING,SHADOW_RIGHT_BOTTOM_PADDING);
    this->setStyleSheet("QDialog{border: 1px solid white;border-radius:1px;background-color: #ffffff;}");
    this->setWindowIcon(QIcon(":/res/kylin-assistant.png"));
    this->setAttribute(Qt::WA_DeleteOnClose);

    QWidget *containerWidget = new QWidget(this);
//    containerWidget->setContentsMargins(SHADOW_LEFT_TOP_PADDING,SHADOW_LEFT_TOP_PADDING,SHADOW_RIGHT_BOTTOM_PADDING,SHADOW_RIGHT_BOTTOM_PADDING);
    m_mainLayout = new QVBoxLayout(containerWidget);
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(20);
    m_mainLayout->setMargin(0);
    m_titleBar = new MyTitleBar(title, false, this);
    m_titleBar->setFixedSize(this->width(), TITLE_BAR_HEIGHT);

    m_titleLabel = new QLabel();
    m_titleLabel->setFixedWidth(80);
    m_titleLabel->setText(tr("Nice value:"));
    m_valueLabel = new QLabel();
    m_slider = new QSlider(Qt::Horizontal);
    m_slider->setFocusPolicy(Qt::NoFocus);
    m_slider->setRange(-20, 19);
    m_slider->setSingleStep(1);

    h_layout = new QHBoxLayout();
    h_layout->setSpacing(10);
    h_layout->setMargin(0);
    h_layout->setContentsMargins(20,0,20,0);
    h_layout->addWidget(m_titleLabel);
    h_layout->addWidget(m_slider);
    h_layout->addWidget(m_valueLabel);

    m_valueStrLabel = new QLabel;
    m_valueStrLabel->setStyleSheet("QLabel{background-color:transparent;color:#000000;font-size:13px;font-weight:bold;}");
    m_valueStrLabel->setAlignment(Qt::AlignCenter);
    m_valueStrLabel->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);

    m_tipTitle = new QLabel;
    m_tipTitle->setStyleSheet("QLabel{background-color:transparent;color:#000000;font-size:12px;font-weight:bold;}");
    m_tipTitle->setText(tr("Note:"));
    m_tipLabel = new QLabel;
    m_tipLabel->setWordWrap(true);//QLabel自动换行
    m_tipLabel->setFixedWidth(388);
    m_tipLabel->setText(tr("The priority of a process is given by its nice value. A lower nice value corresponds to a higher priority."));
    tip_layout = new QHBoxLayout();
    tip_layout->setSpacing(5);
    tip_layout->setMargin(0);
    tip_layout->setContentsMargins(20,0,20,0);
    tip_layout->addWidget(m_tipTitle);
    tip_layout->addWidget(m_tipLabel);

    m_cancelbtn = new QPushButton;
    m_cancelbtn->setFixedSize(91, 25);
    m_cancelbtn->setObjectName("blackButton");
    m_cancelbtn->setFocusPolicy(Qt::NoFocus);
    m_cancelbtn->setText(tr("Cancel"));
    m_changeBtn = new QPushButton;
    m_changeBtn->setFixedSize(91, 25);
    m_changeBtn->setObjectName("blackButton");
    m_changeBtn->setFocusPolicy(Qt::NoFocus);
    m_changeBtn->setText(tr("Change Priority"));

    btn_layout = new QHBoxLayout();
    btn_layout->setMargin(0);
    btn_layout->setSpacing(10);
    btn_layout->setContentsMargins(0,0,20,0);
    btn_layout->addStretch();
    btn_layout->addWidget(m_cancelbtn);
    btn_layout->addWidget(m_changeBtn);


    QVBoxLayout *v_layout = new QVBoxLayout();
    v_layout->setMargin(0);
    v_layout->setSpacing(15);
    v_layout->setContentsMargins(0,0,0,0);
    v_layout->addLayout(h_layout);
    v_layout->addWidget(m_valueStrLabel, 0, Qt::AlignHCenter);
    v_layout->addLayout(tip_layout);
    v_layout->addLayout(btn_layout);

    m_mainLayout->addWidget(m_titleBar);
    m_mainLayout->addLayout(v_layout);

    connect(m_slider, &QSlider::valueChanged, [=] (int value) {
        m_valueLabel->setText(QString::number(value));
        QString levelStr = getNiceLevelWithPriority(value);
        m_valueStrLabel->setText(levelStr);
    });

    connect(m_titleBar, SIGNAL(minSignal()), this, SLOT(hide()));
    connect(m_titleBar, SIGNAL(closeSignal()), this, SLOT(onClose()));
    connect(m_cancelbtn, SIGNAL(clicked(bool)), this, SLOT(onClose()));

    connect(m_changeBtn, &QPushButton::clicked, [=] (bool b) {
        emit this->resetReniceValue(m_slider->value());
    });

    //边框阴影效果
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setBlurRadius(5);
    shadow_effect->setColor(QColor(0, 0, 0, 127));
    shadow_effect->setOffset(2, 4);
    this->setGraphicsEffect(shadow_effect);

//    this->moveCenter();

    QDesktopWidget* desktop = QApplication::desktop();
    this->move((desktop->width() - this->width())/2, (desktop->height() - this->height())/3);
}

ReniceDialog::~ReniceDialog()
{
    delete m_titleBar;
    delete m_valueStrLabel;

    QLayoutItem *child;
    while ((child = h_layout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = tip_layout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = btn_layout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }

    delete m_mainLayout;
}

void ReniceDialog::onClose()
{
    this->close();
}

void ReniceDialog::loadData(int nice)
{
    m_slider->setValue(nice);
    m_valueLabel->setText(QString::number(nice));

    QString levelStr = getNiceLevelWithPriority(nice);
    m_valueStrLabel->setText(levelStr);
}

void ReniceDialog::moveCenter()
{
    /*QPoint pos = QCursor::pos();
    QRect primaryGeometry;
    for (QScreen *screen : qApp->screens()) {
        if (screen->geometry().contains(pos)) {
            primaryGeometry = screen->geometry();
        }
    }

    if (primaryGeometry.isEmpty()) {
        primaryGeometry = qApp->primaryScreen()->geometry();
    }

    this->move(primaryGeometry.x() + (primaryGeometry.width() - this->width())/2,
               primaryGeometry.y() + (primaryGeometry.height() - this->height())/2);
    this->show();
    this->raise();*/
}


void ReniceDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->m_dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->m_mousePressed = true;
    }

    QDialog::mousePressEvent(event);
}

void ReniceDialog::mouseReleaseEvent(QMouseEvent *event)
{
    this->m_mousePressed = false;
    setWindowOpacity(1);

    QDialog::mouseReleaseEvent(event);
}

void ReniceDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (this->m_mousePressed) {
        move(event->globalPos() - this->m_dragPosition);
        setWindowOpacity(0.9);
    }

    QDialog::mouseMoveEvent(event);
}
