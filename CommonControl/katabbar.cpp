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

#include "katabbar.h"

#include <QPainterPath>
#include <QPainter>
#include <QScrollBar>
#include <QTimer>
#include <QDebug>

#include "../../src/commondef.h"
#include "kabuttonproxystyle.h"

KATabBar::KATabBar(QWidget *parent)
    : QWidget(parent)
    , m_nCurIndex(-1)
{
    this->setAttribute(Qt::WA_TranslucentBackground);
    initUI();
    initConnections();
    initStyleTheme();
}

KATabBar::~KATabBar()
{
    if (m_styleSettings) {
        delete m_styleSettings;
        m_styleSettings = nullptr;
    }
}

void KATabBar::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainterPath path;

    QPainter painter(this);
    painter.setOpacity(1);
    painter.setRenderHint(QPainter::Antialiasing);  // 反锯齿;
    painter.setClipping(true);
    painter.setPen(Qt::transparent);

    path.addRoundedRect(this->rect(), 6.0, 6.0);
    path.setFillRule(Qt::WindingFill);
    painter.setBrush(this->palette().base());
    painter.setPen(Qt::transparent);

    painter.drawPath(path);
    // 画线
    QPen pen;
    pen.setWidth(1);
    pen.setBrush(this->palette().alternateBase());
    painter.setPen(pen);

    painter.drawLine(this->rect().x(), this->rect().y()+this->rect().height()-2,
                     this->rect().x()+this->rect().width(), this->rect().y()+this->rect().height());
}

void KATabBar::initUI()
{
    m_mainLayout = new QVBoxLayout();
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(0);
    m_topLayout = new QHBoxLayout();
    m_topLayout->setContentsMargins(0,0,0,0);
    m_topLayout->setSpacing(16);
    m_topMidLayout = new QHBoxLayout();
    m_topMidLayout->setContentsMargins(0,0,0,0);
    m_topMidLayout->setSpacing(0);

    m_leftArrowBtn = new QPushButton();
    m_leftArrowBtn->setIcon(QIcon::fromTheme("pan-start-symbolic"));
    m_leftArrowBtn->setFlat(true);
    m_leftArrowBtn->setFixedSize(24, 52);
    m_rightArrowBtn = new QPushButton();
    m_rightArrowBtn->setIcon(QIcon::fromTheme("pan-end-symbolic"));
    m_rightArrowBtn->setFlat(true);
    m_rightArrowBtn->setFixedSize(24, 52);
    m_topLayout->addWidget(m_leftArrowBtn);

    QWidget *middleWidget = new QWidget();
    middleWidget->setLayout(m_topMidLayout);
    m_scrollWidget = new QScrollArea();
    m_scrollWidget->setAlignment(Qt::AlignTop);
    m_scrollWidget->setContentsMargins(0, 0, 0, 0);
    m_scrollWidget->setBackgroundRole(QPalette::Base);
    m_scrollWidget->setAutoFillBackground(true);
    m_scrollWidget->setFrameStyle(0);
    m_scrollWidget->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollWidget->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollWidget->setWidgetResizable(true);
    m_scrollWidget->setWidget(middleWidget);
    m_scrollWidget->setFixedHeight(52);
    m_scrollWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
    m_topLayout->addWidget(m_scrollWidget);

    m_topLayout->addWidget(m_rightArrowBtn);

    m_btnGroup = new QButtonGroup(this);
    m_btnGroup->setExclusive(true);

    m_mainLayout->addLayout(m_topLayout);
    m_mainLayout->addSpacing(2);

    this->setLayout(m_mainLayout);
}

void KATabBar::initConnections()
{
    connect(m_leftArrowBtn, &QPushButton::clicked, this, &KATabBar::onChangeTabPage);
    connect(m_rightArrowBtn, &QPushButton::clicked, this, &KATabBar::onChangeTabPage);
}

int KATabBar::addTabButton(KATabButton *tabBtn)
{
    if (!tabBtn)
        return -1;
    if (m_btnGroup->id(tabBtn) >= 0)
        return m_btnGroup->id(tabBtn);
    tabBtn->setFixedHeight(52);
    tabBtn->setCheckable(true);
    tabBtn->setStyle(new KAButtonProxyStyle(m_strStyleName));
    connect(tabBtn, &QPushButton::clicked, this, &KATabBar::onTabItemClicked);
    m_btnGroup->addButton(tabBtn, m_btnGroup->buttons().size());
    m_topMidLayout->addWidget(tabBtn);
    return m_btnGroup->id(tabBtn);
}

void KATabBar::onChangeTabPage()
{
    QPushButton* btnSender = qobject_cast<QPushButton*>(sender());
    if (btnSender == m_leftArrowBtn) {
        QScrollBar *scrollHBar = m_scrollWidget->horizontalScrollBar();
        scrollHBar->triggerAction(QAbstractSlider::SliderPageStepSub);
    } else if (btnSender == m_rightArrowBtn) {
        QScrollBar *scrollHBar = m_scrollWidget->horizontalScrollBar();
        scrollHBar->triggerAction(QAbstractSlider::SliderPageStepAdd);
    }
    checkArrowNeedShow();
}

void KATabBar::resizeEvent(QResizeEvent *e)
{
    QWidget::resizeEvent(e);
    QTimer::singleShot(0, this, &KATabBar::checkArrowNeedShow);
}

void KATabBar::checkArrowNeedShow()
{
    QScrollBar *scrollHBar = m_scrollWidget->horizontalScrollBar();
    int nCurValue = scrollHBar->value();
    int nMaxValue = scrollHBar->maximum();
    int nMinValue = scrollHBar->minimum();
    if (nCurValue<=nMinValue) {
        m_leftArrowBtn->setEnabled(false);
    } else {
        m_leftArrowBtn->setEnabled(true);
    }
    if (nCurValue>=nMaxValue) {
        m_rightArrowBtn->setEnabled(false);
    } else {
        m_rightArrowBtn->setEnabled(true);
    }
    qDebug()<<"min:max:cur:"<<nMinValue<<nMaxValue<<nCurValue;
}

void KATabBar::initStyleTheme()
{
    const QByteArray idd(THEME_QT_SCHEMA);
    if(QGSettings::isSchemaInstalled(idd)) {
        m_styleSettings = new QGSettings(idd);
    }
    if (m_styleSettings) {
        connect(m_styleSettings, &QGSettings::changed, this, [=](const QString &key) {
            if (key == "styleName") {
                qDebug()<<"style name changed";
                auto styleName = m_styleSettings->get("styleName").toString();

                if (styleName == "ukui-default" || styleName == "ukui-dark" || styleName == "ukui-white"
                        || styleName == "ukui-black" || styleName == "ukui-light" || styleName == "ukui") {
                    if (styleName == "ukui")
                        styleName = "ukui-default";
                    else if (styleName == "ukui-black")
                        styleName = "ukui-dark";
                    else if (styleName == "ukui-white")
                        styleName = "ukui-light";

                    m_strStyleName = styleName;
                    auto listBtn = m_btnGroup->buttons();
                    for (auto btn : listBtn) {
                        btn->setStyle(new KAButtonProxyStyle(m_strStyleName));
                    }
                }
            }
        });
        auto styleName = m_styleSettings->get("styleName").toString();
        if (styleName == "ukui-default" || styleName == "ukui-dark" || styleName == "ukui-white"
                || styleName == "ukui-black" || styleName == "ukui-light" || styleName == "ukui") {
            if (styleName == "ukui")
                styleName = "ukui-default";
            else if (styleName == "ukui-black")
                styleName = "ukui-dark";
            else if (styleName == "ukui-white")
                styleName = "ukui-light";

            m_strStyleName = styleName;
        }
    }
}

void KATabBar::onChangeTabIndex(int nIndex)
{
    if (m_btnGroup->checkedId() == nIndex ||
        nIndex < 0 || nIndex >= m_btnGroup->buttons().size())
        return;
    auto curBtn = m_btnGroup->button(nIndex);
    if (curBtn) {
        curBtn->setChecked(true);
        m_nCurIndex = nIndex;
    }
}

void KATabBar::onTabItemClicked()
{
    KATabButton* clickedBtn = qobject_cast<KATabButton*>(sender());
    int nClickedIndex = m_btnGroup->id(clickedBtn);
    if (nClickedIndex >= 0) {
        Q_EMIT changeTabIndex(nClickedIndex);
    }
}
