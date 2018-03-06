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

#include "monitortitlewidget.h"
#include "../widgets/mytristatebutton.h"
#include "../widgets/myunderlinebutton.h"
#include "../widgets/mysearchedit.h"
#include "util.h"

#include <QApplication>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QPainter>
#include <QResizeEvent>
#include <QStyleFactory>
#include <QObject>

MonitorTitleWidget::MonitorTitleWidget(QSettings *settings, QWidget *parent)
    :QFrame(parent)
    ,proSettings(settings)
{
    this->setWindowFlags(Qt::FramelessWindowHint);//this->setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint  | Qt::WindowCloseButtonHint);
//    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);//Attention: Qt::WindowCloseButtonHint make showMinimized() valid

    installEventFilter(this);
    setMouseTracking(true);
    setFixedHeight(MONITOR_TITLE_WIDGET_HEIGHT);

    this->setAutoFillBackground(true);
//    this->setAttribute(Qt::WA_TranslucentBackground);

    QPalette palette;
    palette.setColor(QPalette::Background, QColor("#0d87ca"));
    this->setPalette(palette);
//    this->setStyleSheet("QFrame{background:transparent;background-color:#0d87ca;border-radius:5px;border:1px solid red;}");
//    this->setStyleSheet("QFrame {padding: 5px 0;} QFrame:hover {background-color: rgba(255, 245, 250, 0.1);border-radius: 5px;}");

    m_searchTimer = new QTimer(this);
    m_searchTimer->setSingleShot(true);
    connect(m_searchTimer, SIGNAL(timeout()), this, SLOT(onRefreshSearchResult()));

    initWidgets();
}

MonitorTitleWidget::~MonitorTitleWidget()
{
    delete emptyLabel;
    delete m_searchEdit;
    delete m_cancelSearchBtn;
    delete maxBtn;

    if (m_searchTimer) {
        disconnect(m_searchTimer, SIGNAL(timeout()), this, SLOT(onRefreshSearchResult()));
        if(m_searchTimer->isActive()) {
            m_searchTimer->stop();
        }
        delete m_searchTimer;
        m_searchTimer = nullptr;
    }

    //Segmentation fault
    QLayoutItem *child;
    while ((child = m_titleLeftLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_titleMiddleLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_titleRightLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_toolLeftLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_toolRightLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_topLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    while ((child = m_bottomLayout->takeAt(0)) != 0) {
        if (child->widget())
            child->widget()->deleteLater();
        delete child;
    }
    delete m_layout;
}

bool MonitorTitleWidget::eventFilter(QObject *obj, QEvent *event)
{
    if (event->type() == QEvent::KeyPress) {
        if (obj == this) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Escape) {
                m_searchEdit->clearEdit();
                emit canelSearchEditFocus();
            }
        }
        else if (obj == m_searchEdit->getLineEdit()) {
            QKeyEvent *keyEvent = static_cast<QKeyEvent *>(event);
            if (keyEvent->key() == Qt::Key_Tab) {
                emit canelSearchEditFocus();
            }
        }
    }

    return QFrame::eventFilter(obj, event);
}

void MonitorTitleWidget::setSearchEditFocus()
{
    if (m_searchEdit->searchedText() != "") {
        m_searchEdit->getLineEdit()->setFocus();
    } else {
        m_searchEdit->setFocus();
    }
}

void MonitorTitleWidget::onRefreshSearchResult()
{
    if (m_searchEdit->searchedText() == searchTextCache) {
        emit this->searchSignal(searchTextCache);
    }
}

void MonitorTitleWidget::handleSearchTextChanged()
{
    searchTextCache = m_searchEdit->searchedText();

    this->m_cancelSearchBtn->setVisible(!searchTextCache.isEmpty());

    if (m_searchTimer->isActive()) {
        m_searchTimer->stop();
    }
    m_searchTimer->start(300);
}

void MonitorTitleWidget::onCancelSearchBtnClicked(bool b)
{
    this->m_cancelSearchBtn->setVisible(false);
    m_searchEdit->clearAndFocusEdit();
    emit canelSearchEditFocus();
}

void MonitorTitleWidget::mouseDoubleClickEvent(QMouseEvent *e)
{
    if (e->button() == Qt::LeftButton) {
        if (window()->isMaximized())
            window()->showNormal();
        else if (! window()->isFullScreen())
            window()->showMaximized();
    }

    QFrame::mouseDoubleClickEvent(e);
}

/*void MonitorTitleWidget::paintEvent(QPaintEvent *event)
{
//    QFrame::paintEvent(event);

    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing, true);

    //draw background
    QPainterPath path;
    path.addRect(QRectF(0, 0, width(), height()));
    painter.setOpacity(1);
    painter.fillPath(path, QColor("#0d87ca"));


    //draw line
//    const QColor color(QColor(255, 255, 255, 127));
//    int borderHeight = 1;
//    QPainterPath path;
//    path.moveTo(QPointF(x(), y() + borderHeight - 0.5));
//    path.lineTo(QPointF(x() + width(), y() + borderHeight - 0.5));
//    painter.setPen(QPen(color));
//    painter.drawPath(path);

    //绘制圆角矩形
//    painter.setPen(QPen(QColor("#e9eef0"), 0));//边框颜色
//    painter.setBrush(QColor("#0d87ca"));//背景色
//    painter.setOpacity(1);
//    QRectF r(1, 1, width() - 2, height() - 2);//左边 上边 右边 下边
//    painter.drawRoundedRect(r, 5, 5);

    QFrame::paintEvent(event);
}*/

void MonitorTitleWidget::initTitlebarLeftContent()
{
    QWidget *w = new QWidget;
    m_titleLeftLayout = new QHBoxLayout(w);
    m_titleLeftLayout->setContentsMargins(6, 0, 0, 0);
    m_titleLeftLayout->setSpacing(0);

    emptyLabel = new QLabel;
    emptyLabel->setStyleSheet("QLabel{background-color:transparent;}");
    m_titleLeftLayout->addWidget(emptyLabel);

    m_topLayout->addWidget(w, 1, Qt::AlignLeft);
}

void MonitorTitleWidget::initTitlebarMiddleContent()
{
    QWidget *w = new QWidget;
    m_titleMiddleLayout = new QHBoxLayout(w);
    m_titleMiddleLayout->setContentsMargins(0, 0, 0, 0);

    QLabel *titleLabel = new QLabel;
    titleLabel->setStyleSheet("QLabel{background-color:transparent;color:#ffffff; font-size:12px;}");
    titleLabel->setText(tr("Kylin System Monitor"));
    m_titleMiddleLayout->addWidget(titleLabel);
    m_topLayout->addWidget(w);
}

void MonitorTitleWidget::initTitlebarRightContent()
{
    QWidget *w = new QWidget;
    m_titleRightLayout = new QHBoxLayout(w);
    m_titleRightLayout->setContentsMargins(0, 0, 1, 0);
    m_titleRightLayout->setSpacing(0);

    m_topLayout->addWidget(w, 1, Qt::AlignRight);

    MyTristateButton *minBtn = new MyTristateButton;
    minBtn->setObjectName("MinButton");
    connect(minBtn, SIGNAL(clicked()), this, SLOT(onMinBtnClicked()));
//    connect(minBtn, &MyTristateButton::clicked, this, [=] {
//        if (parentWidget() && parentWidget()->parentWidget()) {
//            parentWidget()->parentWidget()->showMinimized();
//        }
//    });
    /*MyTristateButton **/maxBtn = new MyTristateButton;
    maxBtn->setObjectName("MaxButton");
    connect(maxBtn, SIGNAL(clicked()), this, SLOT(onMaxBtnClicked()));
//    connect(maxBtn, &MyTristateButton::clicked, this, [=] {
//        if (window()->isMaximized()) {
//            window()->showNormal();
//            maxBtn->setObjectName("MaxButton");
//        }
//        else {
//            window()->showMaximized();
//            maxBtn->setObjectName("UnMaxButton");
//        }
//    });
//    connect(this, &MonitorTitleWidget::updateMaxBtn, this, [=]{
//        if (window()->isMaximized()) {
//            maxBtn->setObjectName("UnMaxButton");
//        } else {
//            maxBtn->setObjectName("MaxButton");
//        }
//    });
    MyTristateButton *closeBtn = new MyTristateButton;
    closeBtn->setObjectName("CloseButton");
    connect(closeBtn, SIGNAL(clicked()), this, SLOT(onCloseBtnClicked()));
//    connect(closeBtn, &MyTristateButton::clicked, this, [=] {
//        window()->close();
//    });

//    connect(this, SIGNAL(updateMaxBtn()), this, SLOT(onUpdateMaxBtnStatusChanged()));

    m_titleRightLayout->addWidget(minBtn);
    m_titleRightLayout->addWidget(maxBtn);
    m_titleRightLayout->addWidget(closeBtn);
}

void MonitorTitleWidget::onMinBtnClicked()
{
    if (parentWidget() && parentWidget()->parentWidget()) {
        parentWidget()->parentWidget()->showMinimized();
    }
}

void MonitorTitleWidget::onMaxBtnClicked()
{
    if (window()->isMaximized()) {
        window()->showNormal();
        maxBtn->setObjectName("MaxButton");
    }
    else {
        window()->showMaximized();
        maxBtn->setObjectName("UnMaxButton");
    }
}

void MonitorTitleWidget::onCloseBtnClicked()
{
    window()->close();
}

void MonitorTitleWidget::onUpdateMaxBtnStatusChanged()
{
    if (window()->isMaximized()) {
        maxBtn->setObjectName("UnMaxButton");
    } else {
        maxBtn->setObjectName("MaxButton");
    }
}

void MonitorTitleWidget::initToolbarLeftContent()
{
    QWidget *w = new QWidget;
    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_toolLeftLayout = new QHBoxLayout(w);
    m_toolLeftLayout->setContentsMargins(0, 0, 0, 0);
    m_toolLeftLayout->setSpacing(10);

    MyUnderLineButton *processButton = new MyUnderLineButton();
    processButton->setName(tr("Processes"));
    processButton->setChecked(true);

    MyUnderLineButton *resourcesButton = new MyUnderLineButton();
    resourcesButton->setName(tr("Resources"));
    resourcesButton->setChecked(false);

    MyUnderLineButton *disksButton = new MyUnderLineButton();
    disksButton->setName(tr("File Systems"));
    disksButton->setChecked(false);

    connect(processButton, &MyUnderLineButton::clicked, this, [=] {
        emit this->changePage(0);
        processButton->setChecked(true);
        resourcesButton->setChecked(false);
        disksButton->setChecked(false);
        if (!m_searchEdit->isVisible())
            m_searchEdit->setVisible(true);
    });
    connect(resourcesButton, &MyUnderLineButton::clicked, this, [=] {
        emit this->changePage(1);
        processButton->setChecked(false);
        resourcesButton->setChecked(true);
        disksButton->setChecked(false);
        if (m_searchEdit->isVisible())
            m_searchEdit->setVisible(false);
        m_searchEdit->clearEdit();
        emit canelSearchEditFocus();
    });
    connect(disksButton, &MyUnderLineButton::clicked, this, [=] {
        emit this->changePage(2);
        processButton->setChecked(false);
        resourcesButton->setChecked(false);
        disksButton->setChecked(true);
        if (m_searchEdit->isVisible())
            m_searchEdit->setVisible(false);
        m_searchEdit->clearEdit();
        emit canelSearchEditFocus();
    });

    m_toolLeftLayout->addStretch();
    m_toolLeftLayout->addWidget(processButton);
    m_toolLeftLayout->addWidget(resourcesButton);
    m_toolLeftLayout->addWidget(disksButton);
    m_toolLeftLayout->addStretch();

//    m_bottomLayout->addWidget(w);
    m_bottomLayout->addWidget(w, 1, Qt::AlignLeft);
}

void MonitorTitleWidget::initToolbarRightContent()
{
    QWidget *w = new QWidget;
    m_toolRightLayout = new QHBoxLayout(w);
    m_toolRightLayout->setContentsMargins(0, 3, 6, 10);
    m_toolRightLayout->setSpacing(5);

    m_cancelSearchBtn = new QPushButton;
    m_cancelSearchBtn->setStyleSheet("QPushButton{background-color:transparent;text-align:center;font-family: 方正黑体_GBK;font-size:11px;color:#ffffff;}QPushButton:hover{color:#000000;}");
    m_cancelSearchBtn->setText(tr("Cancel"));
    m_cancelSearchBtn->setFocusPolicy(Qt::NoFocus);
    m_cancelSearchBtn->setFixedSize(46, 25);
    m_cancelSearchBtn->setVisible(false);
    connect(m_cancelSearchBtn, SIGNAL(clicked(bool)), SLOT(onCancelSearchBtnClicked(bool)));
    connect(m_searchEdit, &MySearchEdit::textChanged, this, &MonitorTitleWidget::handleSearchTextChanged, Qt::QueuedConnection);
    m_toolRightLayout->addWidget(m_searchEdit);
    m_toolRightLayout->addWidget(m_cancelSearchBtn);
    m_bottomLayout->addWidget(w, 1, Qt::AlignRight);
}

void MonitorTitleWidget::initWidgets()
{
    m_searchEdit = new MySearchEdit();
    m_searchEdit->setPlaceHolder(tr("Enter the relevant info of process"));
    m_searchEdit->setFixedSize(222, 30);
    m_searchEdit->getLineEdit()->installEventFilter(this);

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    QWidget *topWidget = new QWidget;
    m_topLayout = new QHBoxLayout(topWidget);
    m_topLayout->setContentsMargins(0, 0, 0, 0);
    m_topLayout->setSpacing(0);
    m_layout->addWidget(topWidget, 0, Qt::AlignTop);

    QWidget *bottomWidget = new QWidget;
    m_bottomLayout = new QHBoxLayout(bottomWidget);
    m_bottomLayout->setContentsMargins(0, 0, 0, 0);
    m_bottomLayout->setSpacing(0);
    m_layout->addWidget(bottomWidget, 0, Qt::AlignBottom);

    this->setLayout(m_layout);

    initTitlebarLeftContent();
    initTitlebarMiddleContent();
    initTitlebarRightContent();
    initToolbarLeftContent();
    initToolbarRightContent();
}
