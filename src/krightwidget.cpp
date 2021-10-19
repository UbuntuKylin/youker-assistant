/*
 * Copyright (C) 2021 KylinSoft Co., Ltd.
 *
 * Authors:
 *  Yang Min yangmin@kylinos.cn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "krightwidget.h"
#include "commondef.h"

#include <QProcess>
#include <QApplication>
#include <QPainter>
#include <QPainterPath>
#include <QStyleOption>
#include <QDebug>

KRightWidget::KRightWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(RIGHT_WIDGET_WIDTH, RIGHT_WIDGET_HEIGHT);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->installEventFilter(this);
    initUI();
    initConnections();
}

void KRightWidget::initUI()
{
    // 初始化布局
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(0);
    m_titleLayout = new QHBoxLayout();
    m_titleLayout->setContentsMargins(0,0,0,0);
    m_titleLayout->setSpacing(0);

    // 初始化控件
    m_btnOption  = new QToolButton(this);
    m_btnOption->setToolTip(tr("menu"));
    m_btnOption->setProperty("isWindowButton", 0x01);
    m_btnOption->setProperty("useIconHighlightEffect", 0x2);
    m_btnOption->setIcon(QIcon::fromTheme("open-menu-symbolic"));
    m_btnOption->setAutoRaise(true);
    m_btnMin      = new QToolButton(this);
    m_btnMin->setToolTip(tr("minimize"));
    m_btnMin->setProperty("isWindowButton", 0x01);
    m_btnMin->setProperty("useIconHighlightEffect", 0x2);
    m_btnMin->setAutoRaise(true);
    m_btnMin->setIcon(QIcon::fromTheme("window-minimize-symbolic"));
    m_btnClose    = new QToolButton(this);
    m_btnClose->setToolTip(tr("close"));
    m_btnClose->setProperty("isWindowButton", 0x02);
    m_btnClose->setProperty("useIconHighlightEffect", 0x08);
    m_btnClose->setAutoRaise(true);
    m_btnClose->setIcon(QIcon::fromTheme("window-close-symbolic"));
    m_btnOption->setFixedSize(30, 30);
    m_btnMin->setFixedSize(30, 30);
    m_btnClose->setFixedSize(30, 30);

    m_mainMenu = new QMenu(this);
    m_mainMenu->setMinimumWidth(160);
    m_mainMenu->addAction(tr("Help"));
    m_mainMenu->addAction(tr("About"));
    m_mainMenu->addAction(tr("Exit"));
    m_btnOption->setMenu(m_mainMenu);
    m_btnOption->setPopupMode(QToolButton::InstantPopup);

    connect(m_mainMenu,&QMenu::triggered,this,[=](QAction *action){
        qDebug() << Q_FUNC_INFO << action->text();
        if(action->text() == tr("About")){
            if(!m_aboutDlg){
               createAboutDialog();
            }
            m_aboutDlg->setModal(true);
            m_aboutDlg->show();
        }else if(action->text() == tr("Help")){
            QProcess *process = new QProcess(this);
            QString cmd = "kylin-user-guide";
            QStringList arg;
            qDebug() << Q_FUNC_INFO;
            arg << "-A" << "toolkit";
            process->start(cmd,arg);
        }else if(action->text() == tr("Exit")){
            this->onCloseBtnClicked();
        }
    });

    m_titleLayout->setContentsMargins(0,4,4,0);
    m_titleLayout->setSpacing(4);
    m_titleLayout->addStretch(1);
    m_titleLayout->addWidget(m_btnOption);
    m_titleLayout->addWidget(m_btnMin);
    m_titleLayout->addWidget(m_btnClose);

    QWidget* titleWidget = new QWidget();
    QVBoxLayout *titleVLayout = new QVBoxLayout();
    titleVLayout->setContentsMargins(0,0,0,0);
    titleVLayout->setSpacing(0);
    titleVLayout->addLayout(m_titleLayout);
    titleVLayout->addSpacing(6);
    titleWidget->setLayout(titleVLayout);

    m_mainLayout->addWidget(titleWidget);
    m_stackedWidget = new QStackedWidget();
    m_mainLayout->addWidget(m_stackedWidget);

    this->setLayout(m_mainLayout);
}

void KRightWidget::addPanel(QWidget* pWidget, QString strName, QString strIcon)
{
    Q_UNUSED(strName);
    Q_UNUSED(strIcon);
    if (!pWidget)
        return;
    int nIndex = m_stackedWidget->indexOf(pWidget);
    if (nIndex == -1) { // statckedwidget not contains pWidget
        m_stackedWidget->addWidget(pWidget);
    }
}

void KRightWidget::initConnections()
{
    connect(m_btnClose, SIGNAL(clicked()), this, SLOT(onCloseBtnClicked()));
    connect(m_btnMin, SIGNAL(clicked()), this, SLOT(onMinBtnClicked()));
}

void KRightWidget::createAboutDialog()
{
    QApplication::setOverrideCursor(Qt::WaitCursor);

    m_aboutDlg = new KAAboutDialog(this);

    QApplication::restoreOverrideCursor();
}

void KRightWidget::onMinBtnClicked()
{
    emit minimizeWindow();
}

void KRightWidget::onMaxBtnClicked()
{
    emit maximizeWindow();
}

void KRightWidget::onCloseBtnClicked()
{
    window()->close();
}

void KRightWidget::paintEvent(QPaintEvent *)
{
    QPainterPath path;

    QPainter painter(this);
    painter.setOpacity(1);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    painter.setClipping(true);
    painter.setPen(Qt::transparent);

    path.addRect(this->rect());
    path.setFillRule(Qt::WindingFill);
    painter.setBrush(this->palette().base());
    painter.setPen(Qt::transparent);

    painter.drawPath(path);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void KRightWidget::onSwichPanel(int nIndex)
{
    if (nIndex >= m_stackedWidget->count())
        return;
    m_stackedWidget->setCurrentIndex(nIndex);
}

int KRightWidget::currentIndex()
{
    return m_stackedWidget->currentIndex();
}
