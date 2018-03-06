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
    main_action = new QWidget();
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

    main_action->setLayout(layout2);

    stacked_widget = new QStackedWidget(this);//stacked_widget will delete when SettingWidget delete

//    main_action = new SettingAction(desktop);
//    main_action->setModuleName("MainPage");

    theme_action = new SettingAction(desktop);
    theme_action->setModuleName("ThemePage");
//    theme_action->setModuleNameID(SettingAction::ThemePage);

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



//    theme_action->setLanguage(1);

    icon_action = new SettingAction(desktop);
    icon_action->setModuleName("IconPage");
//    icon_action->setLanguage(2);
    mouse_action = new SettingAction(desktop);
    mouse_action->setModuleName("MousePage");
//    mouse_action->setLanguage(3);
    voice_action = new SettingAction(desktop);
    voice_action->setModuleName("SoundPage");
//    voice_action->setLanguage(4);
//    animation_action = new SettingAction(desktop);
//    animation_action->setLanguage(5);
    launcher_action = new SettingAction(desktop);
    launcher_action->setModuleName("MenuPage");
//    launcher_action->setLanguage(5);
    panel_action = new SettingAction(desktop);
    panel_action->setModuleName("PanelPage");
//    panel_action->setLanguage(6);
    window_action = new SettingAction(desktop);
    window_action->setModuleName("WindowPage");
//    window_action->setLanguage(7);
    font_action = new SettingAction(desktop);
    font_action->setModuleName("FontPage");
//    font_action->setLanguage(8);
    touchpad_action = new SettingAction(desktop);
    touchpad_action->setModuleName("TouchPadPage");
//    touchpad_action->setLanguage(9);
//    deadpixel_action = new SettingAction(desktop);
//    deadpixel_action->setModuleName("MonitorPage");
//    deadpixel_action->setLanguage(10);
    conserve_aciton = new SettingAction(desktop);
    conserve_aciton->setModuleName("EnergyPage");
//    conserve_aciton->setLanguage(11);
    nautilus_action = new SettingAction(desktop);
    nautilus_action->setModuleName("FMPage");
//    nautilus_action->setLanguage(12);
    stacked_widget->addWidget(main_action);
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
//    stacked_widget->addWidget(deadpixel_action);
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
    if(main_action != NULL)
    {
        delete main_action;
        main_action = NULL;
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
//    if(deadpixel_action != NULL)
//    {
//        delete deadpixel_action;
//        deadpixel_action = NULL;
//    }

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
//    connect(deadpixel_action, SIGNAL(showSettingMainWidget()), this, SLOT(displayActionMainPage()));
    connect(conserve_aciton, SIGNAL(showSettingMainWidget()), this, SLOT(displayActionMainPage()));
    connect(nautilus_action, SIGNAL(showSettingMainWidget()), this, SLOT(displayActionMainPage()));
}


void SettingActionWidget::setLanguage()
{
    title_label->setText(tr("You can perform a full range of customized systems based on personal preferences"));//您可以根据个人喜好对系统进行全方位的定制
//    description_label->setText(tr("您可以根据个人喜好对系统进行全方位的定制"));
}

//void SettingActionWidget::displayActionSubPage(SettingAction::SettingModuleID moduleId)
void SettingActionWidget::displayActionSubPage(QString moduleName)
{
    for (int i = 0; i < stacked_widget->count(); i++) {
        if (QWidget *widget = static_cast<QWidget *>(stacked_widget->widget(i))) {
            if (widget->inherits("SettingAction")) {
                if (SettingAction *action = static_cast<SettingAction *>(stacked_widget->widget(i))) {
                    QPointer<SettingAction> panel(action);
                    if (panel.isNull()) {
                        continue;
                    }
                    if (action->getModuleName() == moduleName) {
                        stacked_widget->setCurrentWidget(action);
                        break;
                    }
//                    if (action->getModuleNameID() == moduleId) {
//                        stacked_widget->setCurrentWidget(action);
//                    }
                }
            }
        }
    }
}

void SettingActionWidget::displayActionMainPage() {
    stacked_widget->setCurrentWidget(main_action);
    emit this->notifyContentPageToMain();

//    QObject *object = QObject::sender();
//	QAction *action = qobject_cast<QAction *>(object);
//	QString object_name = action->objectName();
}
