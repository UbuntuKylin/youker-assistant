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

#include "settingactionwidget.h"
#include "mainwindow.h"

SettingActionWidget::SettingActionWidget(QString cur_desktop, QWidget *parent)
    : QWidget(parent), desktop(cur_desktop)
{
    this->setFixedSize(900, 150);
    this->setAutoFillBackground(true);
    this->setObjectName("transparentWidget");

    img_label = new QLabel();
    title_label = new QLabel();
//    description_label = new QLabel();
    main_acion = new QWidget();
    img_label->setScaledContents(true);//自动缩放,显示图像大小自动调整为Qlabel大小
    QPixmap label_pixmap("://res/systemset.png");
    img_label->setPixmap(label_pixmap);
    img_label->setFixedSize(label_pixmap.size());

    title_label->setObjectName("whiteLabel");
//    description_label->setWordWrap(true);//QLabel自动换行
//    description_label->setObjectName("tipLabel");

//    QVBoxLayout *layout1 = new QVBoxLayout();
//    layout1->addStretch();
//    layout1->addWidget(title_label);
//    layout1->addWidget(description_label);
//    layout1->addStretch();
//    layout1->setSpacing(15);
//    layout1->setMargin(0);
//    layout1->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addWidget(img_label, 0, Qt::AlignVCenter);
    layout2->addWidget(title_label, 0, Qt::AlignVCenter);
//    layout2->addLayout(layout1);
    layout2->setSpacing(20);
    layout2->setMargin(0);
    layout2->setContentsMargins(20, 20, 0, 0);

    main_acion->setLayout(layout2);

    stacked_widget = new QStackedWidget(this);//stacked_widget will delete when SettingWidget delete
    theme_action = new SettingAction(desktop);
    theme_action->setLanguage(1);

    icon_action = new SettingAction(desktop);
    icon_action->setLanguage(2);
    mouse_action = new SettingAction(desktop);
    mouse_action->setLanguage(3);
    voice_action = new SettingAction(desktop);
    voice_action->setLanguage(4);
//    animation_action = new SettingAction(desktop);
//    animation_action->setLanguage(5);
    launcher_action = new SettingAction(desktop);
    launcher_action->setLanguage(5);
    panel_action = new SettingAction(desktop);
    panel_action->setLanguage(6);
    window_action = new SettingAction(desktop);
    window_action->setLanguage(7);
    font_action = new SettingAction(desktop);
    font_action->setLanguage(8);
    touchpad_action = new SettingAction(desktop);
    touchpad_action->setLanguage(9);
    deadpixel_action = new SettingAction(desktop);
    deadpixel_action->setLanguage(10);
    conserve_aciton = new SettingAction(desktop);
    conserve_aciton->setLanguage(11);
    nautilus_action = new SettingAction(desktop);
    nautilus_action->setLanguage(12);
    stacked_widget->addWidget(main_acion);
    stacked_widget->addWidget(theme_action);
    stacked_widget->addWidget(icon_action);
    stacked_widget->addWidget(mouse_action);
    stacked_widget->addWidget(voice_action);
//    stacked_widget->addWidget(animation_action);
    stacked_widget->addWidget(launcher_action);
    stacked_widget->addWidget(panel_action);
    stacked_widget->addWidget(window_action);
    stacked_widget->addWidget(font_action);
    stacked_widget->addWidget(touchpad_action);
    stacked_widget->addWidget(deadpixel_action);
    stacked_widget->addWidget(conserve_aciton);
    stacked_widget->addWidget(nautilus_action);



    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(stacked_widget);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(main_layout);
    this->initConnect();
    this->setLanguage();
}

SettingActionWidget::~SettingActionWidget()
{
    if(img_label != NULL)
    {
        delete img_label;
        img_label = NULL;
    }
    if(title_label != NULL)
    {
        delete title_label;
        title_label = NULL;
    }
    if(main_acion != NULL)
    {
        delete main_acion;
        main_acion = NULL;
    }
    if(theme_action != NULL)
    {
        delete theme_action;
        theme_action = NULL;
    }
    if(icon_action != NULL)
    {
        delete icon_action;
        icon_action = NULL;
    }
    if(mouse_action != NULL)
    {
        delete mouse_action;
        mouse_action = NULL;
    }
    if(voice_action != NULL)
    {
        delete voice_action;
        voice_action = NULL;
    }
    if(launcher_action != NULL)
    {
        delete launcher_action;
        launcher_action = NULL;
    }
    if(panel_action != NULL)
    {
        delete panel_action;
        panel_action = NULL;
    }
    if(window_action != NULL)
    {
        delete window_action;
        window_action = NULL;
    }
    if(font_action != NULL)
    {
        delete font_action;
        font_action = NULL;
    }
    if(touchpad_action != NULL)
    {
        delete touchpad_action;
        touchpad_action = NULL;
    }
    if(deadpixel_action != NULL)
    {
        delete deadpixel_action;
        deadpixel_action = NULL;
    }

    if(conserve_aciton != NULL)
    {
        delete conserve_aciton;
        conserve_aciton = NULL;
    }
    if(nautilus_action != NULL)
    {
        delete nautilus_action;
        nautilus_action = NULL;
    }
}

void SettingActionWidget::initConnect()
{
    connect(theme_action, SIGNAL(showSettingMainWidget()), this, SLOT(displayActionMainPage()));
    connect(icon_action, SIGNAL(showSettingMainWidget()), this, SLOT(displayActionMainPage()));
    connect(mouse_action, SIGNAL(showSettingMainWidget()), this, SLOT(displayActionMainPage()));
    connect(voice_action, SIGNAL(showSettingMainWidget()), this, SLOT(displayActionMainPage()));
//    connect(animation_action, SIGNAL(showSettingMainWidget()), this, SLOT(displayActionMainPage()));
    connect(launcher_action, SIGNAL(showSettingMainWidget()), this, SLOT(displayActionMainPage()));
    connect(panel_action, SIGNAL(showSettingMainWidget()), this, SLOT(displayActionMainPage()));
    connect(window_action, SIGNAL(showSettingMainWidget()), this, SLOT(displayActionMainPage()));
    connect(font_action, SIGNAL(showSettingMainWidget()), this, SLOT(displayActionMainPage()));
    connect(touchpad_action, SIGNAL(showSettingMainWidget()), this, SLOT(displayActionMainPage()));
    connect(deadpixel_action, SIGNAL(showSettingMainWidget()), this, SLOT(displayActionMainPage()));
    connect(conserve_aciton, SIGNAL(showSettingMainWidget()), this, SLOT(displayActionMainPage()));
    connect(nautilus_action, SIGNAL(showSettingMainWidget()), this, SLOT(displayActionMainPage()));
}


void SettingActionWidget::setLanguage()
{
    title_label->setText(tr("You can perform a full range of customized systems based on personal preferences"));//您可以根据个人喜好对系统进行全方位的定制
//    description_label->setText(tr("您可以根据个人喜好对系统进行全方位的定制"));
}

void SettingActionWidget::displayActionSubPage(int index)
{
    stacked_widget->setCurrentIndex(index);
}

void SettingActionWidget::displayActionMainPage() {
    stacked_widget->setCurrentIndex(0);
    emit this->notifyContentPageToMain();
//    QObject *object = QObject::sender();
//	QAction *action = qobject_cast<QAction *>(object);
//	QString object_name = action->objectName();
//	int index = object_name.toInt();



//    QObject *object = QObject::sender();
//    QPushButton *btn = qobject_cast<QPushButton *>(object);
//    QString object_name = btn->statusTip();
//    if (object_name == "theme") {
//        stacked_widget->setCurrentIndex(1);
//    }
//    else if (object_name == "icon") {
//        stacked_widget->setCurrentIndex(2);
//    }
//    else if (object_name == "mouse") {
//        stacked_widget->setCurrentIndex(3);
//    }
//    else if (object_name == "voice") {
//        stacked_widget->setCurrentIndex(4);
//    }
//    else if (object_name == "animation") {
//        stacked_widget->setCurrentIndex(5);
//    }
//    else if (object_name == "launcher") {
//        stacked_widget->setCurrentIndex(6);
//    }
//    else if (object_name == "panel") {
//        stacked_widget->setCurrentIndex(7);
//    }
//    else if (object_name == "window") {
//        stacked_widget->setCurrentIndex(8);
//    }
//    else if (object_name == "font") {
//        stacked_widget->setCurrentIndex(9);
//    }
//    else if (object_name == "touchpad") {
//        stacked_widget->setCurrentIndex(10);
//    }
//    else if (object_name == "deadpixel") {
//        stacked_widget->setCurrentIndex(11);
//    }
//    else if (object_name == "nautilus") {
//        stacked_widget->setCurrentIndex(12);
//    }
}
