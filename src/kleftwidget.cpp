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
#include "kleftwidget.h"
#include "commondef.h"
#include "imageutil.h"

#include <QPainter>
#include <QPainterPath>
#include <QPixmap>
#include <QVariant>
#include <QDebug>

KLeftWidget::KLeftWidget(QWidget *parent)
    : QWidget(parent)
{
    this->setFixedSize(LEFT_WIDGET_WIDTH,LEFT_WIDGET_HEIGHT);
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->installEventFilter(this);
    initUI();
    initConnections();
}

KLeftWidget::~KLeftWidget()
{
    if (qtSettings) {
        delete qtSettings;
        qtSettings = nullptr;
    }
}

void KLeftWidget::initUI()
{
    // 初始化布局
    m_mainLayout = new QVBoxLayout(this);
    m_mainLayout->setContentsMargins(0,0,0,0);
    m_mainLayout->setSpacing(0);
    m_titleLayout = new QHBoxLayout();
    m_titleLayout->setContentsMargins(0,0,0,0);
    m_titleLayout->setSpacing(0);
    m_itemsLayout = new QVBoxLayout();
    m_itemsLayout->setContentsMargins(0,0,0,0);
    m_itemsLayout->setSpacing(0);

    // 初始化控件
    m_titleLayout->setContentsMargins(8,8,0,0);
    m_labelTitleIcon  = new QLabel(this);
    m_labelTitle  = new QLabel(tr("ToolKit"), this);

    m_labelTitleIcon->setFixedSize(24, 24);
    QIcon titleIcon = QIcon::fromTheme("kylin-assistant");
    m_labelTitleIcon->setPixmap(titleIcon.pixmap(titleIcon.actualSize(QSize(24, 24))));
    m_labelTitle->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    m_titleLayout->addWidget(m_labelTitleIcon);
    m_titleLayout->addSpacing(8);
    m_titleLayout->addWidget(m_labelTitle);
    m_titleLayout->addStretch();

    QWidget *titleWidget = new QWidget(this);
    titleWidget->setLayout(m_titleLayout);
    m_mainLayout->addWidget(titleWidget);

    m_itemsLayout->setContentsMargins(10,16,10,16);
    m_itemsLayout->setSpacing(12);
    m_buttonGroup = new QButtonGroup(this);
    m_buttonGroup->setExclusive(true);

    m_verticalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Expanding);
    m_itemsLayout->addItem(m_verticalSpacer);

    m_mainLayout->addLayout(m_itemsLayout);
    this->setLayout(m_mainLayout);
    initThemeMode();
}

int KLeftWidget::addItems(QString strText, QString strTip, QString strIcon)
{
    Q_UNUSED(strTip);
    KLeftSideItem * leftsidebarBtn = new KLeftSideItem();
    leftsidebarBtn->setAttribute(Qt::WA_DeleteOnClose);
    leftsidebarBtn->setCheckable(true);
    leftsidebarBtn->setIcon(strIcon);
    leftsidebarBtn->setFixedSize(LEFT_BUTTON_WIDTH, LEFT_BUTTON_HEITHT);
    leftsidebarBtn->setText(strText);

    int nLength = m_buttonGroup->buttons().length();
    leftsidebarBtn->setChecked(false);
    m_buttonGroup->addButton(leftsidebarBtn, nLength);
    m_itemsLayout->addWidget(leftsidebarBtn);
    m_itemsLayout->removeItem(m_verticalSpacer);
    m_itemsLayout->addItem(m_verticalSpacer);
    return nLength;
}

void KLeftWidget::initConnections()
{
    connect(m_buttonGroup, SIGNAL(buttonClicked(int)), this, SIGNAL(switchPage(int)));
}

void KLeftWidget::onSwichPanel(int nIndex)
{
    QPushButton *sideButton = qobject_cast<QPushButton *>(m_buttonGroup->button(nIndex));
    if (sideButton) {
        sideButton->setChecked(true);
    }
}

int KLeftWidget::currentIndex()
{
    return m_buttonGroup->checkedId();
}

void KLeftWidget::initThemeMode()
{
    const QByteArray idd(THEME_QT_SCHEMA);
    if(QGSettings::isSchemaInstalled(idd)) {
        qtSettings = new QGSettings(idd);
    }
    if (qtSettings) {
        //监听主题改变
        connect(qtSettings, &QGSettings::changed, this, [=](const QString &key)
        {
            if (key == "styleName") {
            } else if ("iconThemeName" == key) {
                if (m_labelTitleIcon) {
                    m_labelTitleIcon->setPixmap(QIcon::fromTheme("kylin-assistant").pixmap(24,24));
                    //this->setWindowIcon(QIcon::fromTheme("kylin-assistant"));
                }
            }
        });
    }
}
