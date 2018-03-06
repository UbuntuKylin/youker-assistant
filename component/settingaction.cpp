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

#include "settingaction.h"

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

SettingAction::SettingAction(QString cur_desktop, QWidget *parent)
    : QWidget(parent), desktop(cur_desktop)
{
    this->setFixedSize(900, 150);
    this->setAutoFillBackground(true);
    this->setObjectName("transparentWidget");

    m_moduleName = "";

    back_btn = new QPushButton();
    back_btn->setCursor(Qt::PointingHandCursor);
    back_btn->setFixedSize(91,39);
    back_btn->setFocusPolicy(Qt::NoFocus);
    QPixmap pixmap("://res/back-arrow.png");
    back_btn->setIcon(pixmap);
    back_btn->setIconSize(pixmap.size());
    back_btn->setObjectName("backgroundButton");
    back_btn->setText(tr("Back"));
    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
    img_label = new QLabel();
    title_label = new QLabel();
//    description_label = new QLabel();

    img_label->setScaledContents(true);//自动缩放,显示图像大小自动调整为Qlabel大小
    QPixmap label_pixmap("://res/systemset.png");
    img_label->setPixmap(label_pixmap);
    img_label->setFixedSize(label_pixmap.size());

    title_label->setObjectName("whiteLabel");
    title_label->setFixedWidth(650);
    title_label->setWordWrap(true);//QLabel自动换行
//    description_label->setWordWrap(true);//QLabel自动换行
//    description_label->setObjectName("tipLabel");


    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addWidget(img_label, 0, Qt::AlignVCenter);
    layout1->addWidget(title_label, 0, Qt::AlignVCenter);
    layout1->setSpacing(20);
    layout1->setMargin(0);
//    layout1->setContentsMargins(20, 20, 0, 0);
    layout1->setContentsMargins(0, 0, 0, 0);


//    QVBoxLayout *layout1 = new QVBoxLayout();
//    layout1->addStretch();
//    layout1->addWidget(title_label);
////    layout1->addWidget(description_label);
//    layout1->addStretch();
//    layout1->setSpacing(15);
//    layout1->setMargin(0);
//    layout1->setContentsMargins(0, 0, 0, 0);

    QVBoxLayout *layout2 = new QVBoxLayout();
    layout2->addWidget(back_btn);
    layout2->addStretch();
    layout2->setMargin(0);
    layout2->setContentsMargins(0, 20, 0, 0);

    QHBoxLayout *main_layout = new QHBoxLayout();
//    main_layout->addWidget(img_label, 0, Qt::AlignVCenter);
    main_layout->addLayout(layout1);
    main_layout->addStretch();
    main_layout->addLayout(layout2);
//    main_layout->addWidget(back_btn, 0, Qt::AlignVCenter);
    main_layout->setSpacing(20);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(20, 20, 0, 0);

    setLayout(main_layout);

}

SettingAction::~SettingAction()
{
    if(back_btn != NULL) {
        delete back_btn;
        back_btn = NULL;
    }
    if(img_label != NULL) {
        delete img_label;
        img_label = NULL;
    }
    if(title_label != NULL) {
        delete title_label;
        title_label = NULL;
    }
}

QString SettingAction::getModuleName() /*const*/
{
    return this->m_moduleName;
}

//void SettingAction::setModuleName(const QString &name)
void SettingAction::setModuleName(QString name)
{
    this->m_moduleName = name;

    const QString title = filterTitleAccordModuleName(name);
    if (title.isEmpty() || title.isNull()) {
        title_label->setText(tr("There may be a mistake."));
    }
    else {
        title_label->setText(title);
    }
}

void SettingAction::setLanguage(int index)
{
    /*back_btn->setText(tr("Back"));
    switch (index) {
    case 1:
        title_label->setText(tr("Choose the theme what you want"));
//        description_label->setText(tr("Choose the theme what you want."));
        break;
    case 2:
        title_label->setText(tr("Set the desktop icon theme and the visibility of desktop icons"));
//        description_label->setText(tr("Set the desktop icon theme and the visibility of desktop icons."));
        break;
    case 3:
        title_label->setText(tr("Replace the theme and size of the mouse pointer, and theme change need to restart system"));
//        description_label->setText(tr("Replace the theme and size of the mouse pointer,  then click the 'OK' button to confirm. Also, theme change need to restart system."));
        break;
    case 4:
        title_label->setText(tr("Set the sound theme you want"));
//        description_label->setText(tr("Set the sound theme you want."));
        break;
//    case 5:
//        title_label->setText(tr("Click the \"Custom Picture\" button to select the picture you want to add, click the picture you want to set and push the \"OK\" button to complete"));
////        description_label->setText(tr("Click the \"Custom Picture\" button to select the picture you want to add, click the picture you want to set and push the \"OK\" button to complete."));
//        break;
    case 5:
        if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "ukui" || this->desktop == "UKUI")
            title_label->setText(tr("Setting the panel mode of auto hide and icon size"));
        else
            title_label->setText(tr("Setting the Launcher display mode, Icon size"));
//        description_label->setText(tr("Setting the Launcher display mode, Icon size."));
        break;
    case 6:
        if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "ukui" || this->desktop == "UKUI")
            title_label->setText(tr("Manage display of the start menu"));
        else
            title_label->setText(tr("Manage Dash and Panel menu settings"));
//        description_label->setText(tr("Manage Dash and Panel menu settings."));
        break;
    case 7:
        title_label->setText(tr("Window Manager settings"));
//        description_label->setText(tr("Window Manager settings."));
        break;
    case 8:
        title_label->setText(tr("According to personal preferences to set the system default font, click the  'Restore' button, can be restored to the state before the font settings"));
//        description_label->setText(tr("According to personal preferences to set the system default font, click the  'Restore' button, can be restored to the state before the font settings."));
        break;
    case 9:
        title_label->setText(tr("Setting the relevant properties of your touchpad,make the operation more convenient"));
//        description_label->setText(tr("Setting the relevant properties of your touchpad,make the operation more convenient."));
        break;
    case 10:
        title_label->setText(tr("Monitor Check"));
//        description_label->setText(tr("Monitor Check."));
        break;
    case 11:
        title_label->setText(tr("Save energy to let the computer longer standby time"));
        break;
    case 12:
        if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "ukui" || this->desktop == "UKUI")
            title_label->setText(tr("Manage the Caja file manager. Tips: if the thumbnail's cache time or size is set to -1, it will not be checked"));
        else
            title_label->setText(tr("Manage the Nautilus file manager. Tips: if the thumbnail's cache time or size is set to -1, it will not be checked"));
//        description_label->setText(tr("Manage the Nautilus file manager. Tips: if the thumbnail's cache time or size is set to -1, it will not be checked."));
        break;
    default:
        break;
    }*/
}
