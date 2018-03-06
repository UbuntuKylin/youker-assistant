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

#include "topbasewidget.h"
#include "mainwindow.h"

#include <QApplication>
#include <QDebug>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QPushButton>
#include <QCursor>


//    enum SettingModuleID{
//        ThemePage = 0,
//        IconPage,
//        MousePage,
//        SoundPage,
//        PanelPage,
//        MenuPage,
//        WindowPage,
//        FontPage,
//        TouchPadPage,
//        EnergyPage,
//        FMPage
//    };

namespace {
//const QMap<SettingModuleID::SettingModuleID, QString> titleMap()
//{
//    QMap<SettingAction::SettingModuleID, QString> m;
//    m.insert(SettingAction::ThemePage, "a");
//    m.insert(SettingAction::IconPage, "b");
//    m.insert(SettingAction::MousePage, "c");
//    m.insert(SettingAction::SoundPage, "d");
//    return m;
//}

//int filterTitleAccordModuleName(SettingAction::SettingModuleID id)
//{
//    return titleMap().value(id);
//}

const QMap<QString, QString> titleMap()
{
    QMap<QString, QString> tMap;
    tMap.insert("ThemePage", QObject::tr("Choose the theme what you want"));
    tMap.insert("IconPage", QObject::tr("Set the desktop icon theme and the visibility of desktop icons"));
    tMap.insert("MousePage", QObject::tr("Replace the theme and size of the mouse pointer, and theme change need to restart system"));
    tMap.insert("SoundPage", QObject::tr("Set the sound theme you want"));
    tMap.insert("PanelPage", QObject::tr("Setting the panel mode of auto hide and icon size"));
    tMap.insert("MenuPage", QObject::tr("Manage display of the start menu"));
    tMap.insert("WindowPage", QObject::tr("Window Manager settings"));
    tMap.insert("FontPage", QObject::tr("According to personal preferences to set the system default font, click the  'Restore' button, can be restored to the state before the font settings"));
    tMap.insert("TouchPadPage", QObject::tr("Setting the relevant properties of your touchpad,make the operation more convenient"));
    tMap.insert("EnergyPage", QObject::tr("Save energy to let the computer longer standby time"));
    tMap.insert("FMPage", QObject::tr("Manage the file manager. Tips: if the thumbnail's cache time or size is set to -1, it will not be checked"));

    return tMap;
}

QString filterTitleAccordModuleName(QString moduleName)
{
    return titleMap().value(moduleName);
}

}

TopBaseWidget::TopBaseWidget(QWidget *parent)
	: QWidget(parent)
{
    m_titileMessage = "";

    this->setFixedSize(900, 150);
    this->setAutoFillBackground(true);
//    this->setObjectName("transparentWidget");

    this->initWidgets();
}

TopBaseWidget::~TopBaseWidget()
{
    if(img_label != NULL) {
        delete img_label;
        img_label = NULL;
    }
    if(suggest_label != NULL) {
        delete suggest_label;
        suggest_label = NULL;
    }

    delete back_button;

    //Segmentation fault
    QLayoutItem *child;
    while ((child = m_titleLeftLayout->takeAt(0)) != 0) {
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

void TopBaseWidget::setTipMessage(const QString &message)
{
    this->m_titileMessage = message;

    suggest_label->setText(message);
}

void TopBaseWidget::setImage(const QString &pic)
{
    QPixmap label_pixmap(pic);
    img_label->setPixmap(label_pixmap);
    img_label->setFixedSize(label_pixmap.size());
}

//QString TopBaseWidget::getModuleName() /*const*/
//{
//    return this->m_moduleName;
//}

//void SettingAction::setModuleName(const QString &name)
//void TopBaseWidget::setModuleName(QString name)
//{
////    this->m_moduleName = name;
////    back_button->setVisible(true);
////    const QString title = filterTitleAccordModuleName(name);
////    if (title.isEmpty() || title.isNull()) {
////        suggest_label->setText(tr("There may be a mistake."));
////    }
////    else {
////        suggest_label->setText(title);
////    }
//}

//void TopBaseWidget::displayActionSubPage(SettingAction::SettingModuleID moduleId)
void TopBaseWidget::displayActionSubPage(QString moduleName)
{
//    this->m_moduleName = moduleName;
    back_button->setVisible(true);

    const QString title = filterTitleAccordModuleName(moduleName);
    if (title.isEmpty() || title.isNull()) {
        suggest_label->setText(tr("There may be a mistake."));
    }
    else {
        suggest_label->setText(title);
    }
}

void TopBaseWidget::initTitlebarLeftContent()
{
    QWidget *w = new QWidget;
    m_titleLeftLayout = new QHBoxLayout(w);
    m_titleLeftLayout->setContentsMargins(6, 0, 0, 0);
    m_titleLeftLayout->setSpacing(0);

    QLabel *appLabel = new QLabel;
    appLabel->setStyleSheet("QLabel{background-color:transparent;color:#ffffff; font-size:12px;}");
    appLabel->setText(tr("Kylin Assistant"));
    m_titleLeftLayout->addWidget(appLabel);

    m_topLayout->addWidget(w, 1, Qt::AlignLeft);
}

void TopBaseWidget::initTitlebarRightContent()
{
    QWidget *w = new QWidget;
    m_titleRightLayout = new QHBoxLayout(w);
    m_titleRightLayout->setContentsMargins(0, 0, 1, 0);
    m_titleRightLayout->setSpacing(0);

    m_topLayout->addWidget(w, 1, Qt::AlignRight);

    SystemButton *min_button = new SystemButton();
    SystemButton *close_button = new SystemButton();
//    SystemButton *skin_button = new SystemButton();
    SystemButton *main_menu_button = new SystemButton();
    min_button->loadPixmap(":/sys/res/sysBtn/min_button.png");
    close_button->loadPixmap(":/sys/res/sysBtn/close_button.png");
//    skin_button->loadPixmap(":/sys/res/sysBtn/skin_button.png");
    main_menu_button->loadPixmap(":/sys/res/sysBtn/main_menu.png");
    min_button->setFocusPolicy(Qt::NoFocus);
    close_button->setFocusPolicy(Qt::NoFocus);
//    skin_button->setFocusPolicy(Qt::NoFocus);
    main_menu_button->setFocusPolicy(Qt::NoFocus);

    m_titleRightLayout->addWidget(main_menu_button);
//    m_titleRightLayout->addWidget(skin_button);
    m_titleRightLayout->addWidget(min_button);
    m_titleRightLayout->addWidget(close_button);

    connect(main_menu_button, &SystemButton::clicked, this, [=] {
        emit this->showMenu();
    });
//    connect(skin_button, &SystemButton::clicked, this, [=] {
//        emit this->showSkinCenter();
//    });
    connect(min_button, &SystemButton::clicked, this, [=] {
        emit this->showMin();
    });
    connect(close_button, &SystemButton::clicked, this, [=] {
        emit this->closeApp();//window()->close();
    });
}

void TopBaseWidget::initContentLeftContent()
{
    QWidget *w = new QWidget;
    w->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Preferred);
    m_toolLeftLayout = new QHBoxLayout(w);
    m_toolLeftLayout->setContentsMargins(0, 0, 0, 0);

    img_label = new QLabel();
    suggest_label = new QLabel();

    img_label->setScaledContents(true);//自动缩放,显示图像大小自动调整为Qlabel大小

    suggest_label->setObjectName("whiteLabel");
    suggest_label->setWordWrap(true);//QLabel自动换行
    suggest_label->setFixedWidth(650);

    m_toolLeftLayout->setSpacing(10);
    m_toolLeftLayout->addStretch();
    m_toolLeftLayout->addWidget(img_label, 0, Qt::AlignHCenter);
    m_toolLeftLayout->addWidget(suggest_label, 0, Qt::AlignHCenter);
    m_toolLeftLayout->addStretch();

//    m_bottomLayout->addWidget(w);
    m_bottomLayout->addWidget(w, 1, Qt::AlignLeft);
}

void TopBaseWidget::initActionRightContent()
{
    QWidget *w = new QWidget;
    m_toolRightLayout = new QHBoxLayout(w);
    m_toolRightLayout->setContentsMargins(0, 3, 0, 10);
    m_toolRightLayout->setSpacing(0);

    back_button = new QPushButton();
    back_button->setCursor(Qt::PointingHandCursor);
    back_button->setFixedSize(91,39);
    back_button->setFocusPolicy(Qt::NoFocus);
    QPixmap pixmap("://res/back-arrow.png");
    back_button->setIcon(pixmap);
    back_button->setIconSize(pixmap.size());
    back_button->setObjectName("backgroundButton");
    back_button->setText(tr("Back"));
    back_button->setVisible(false);
    connect(back_button, &QPushButton::clicked, this, [=] {
        suggest_label->setText(this->m_titileMessage);
        back_button->setVisible(false);
        emit this->notifyContentPageToMain();
    });

    m_toolRightLayout->addWidget(back_button);
    m_bottomLayout->addWidget(w, 1, Qt::AlignRight);
}

void TopBaseWidget::initWidgets()
{
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
    m_bottomLayout->setContentsMargins(19, 0, 0, 26);
    m_bottomLayout->setSpacing(0);
    m_layout->addWidget(bottomWidget, 0, Qt::AlignBottom);

    this->setLayout(m_layout);

    initTitlebarLeftContent();
    initTitlebarRightContent();
    initContentLeftContent();
    initActionRightContent();
}
