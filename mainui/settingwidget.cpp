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

#include "settingwidget.h"
#include <QDebug>
//#include "../component/deadpixeldialog.h"
//#include "../dbusproxy/youkersessiondbus.h"
//#include "mainwindow.h"

SettingWidget::SettingWidget(QString cur_desktop, bool has_battery, QWidget *parent) :
    QWidget(parent), desktop(cur_desktop), battery(has_battery)
{
    this->setFixedSize(900, 403);
    //set white background color
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    this->setPalette(palette);

//    this->mainwindow_width = 850;
//    this->mainwindow_height = 600;

    stacked_widget = new QStackedWidget(this);//stacked_widget will delete when SettingWidget delete
    theme_widget = NULL;
    icon_widget = NULL;
    mouse_widget = NULL;
    voice_widget = NULL;
//    animation_widget = NULL;
    launcher_widget = NULL;
    panel_widget = NULL;
    window_widget = NULL;
    font_widget = NULL;
    touchpad_widget = NULL;
    deadpixel_widget = NULL;
    conserve_widget = NULL;
    nautilus_widget = NULL;

    h_splitter = new QSplitter();
    h_splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    h_splitter->setOrientation(Qt::Horizontal);
    h_splitter->setHandleWidth(1);

    this->initIndividuationWidget();
    this->initDesktopWidget();
    this->initFontWidget();
    this->initOptionWidget();
    this->initOtherWidget();

    individuation_widget->setFixedSize(170, 426);
    dekstop_widget->setFixedSize(170, 426);
    fonts_widget->setFixedSize(170, 426);
    option_widget->setFixedSize(170, 426);
    h_splitter->addWidget(individuation_widget);
    h_splitter->addWidget(dekstop_widget);
    h_splitter->addWidget(fonts_widget);
    h_splitter->addWidget(option_widget);
    h_splitter->addWidget(other_widget);

    for(int i = 0; i<h_splitter->count();i++)
    {
        QSplitterHandle *handle = h_splitter->handle(i);
        handle->setEnabled(false);
    }

//    for(int i = 0; i<v_splitter->count();i++)
//    {
//        QSplitterHandle *handle = v_splitter->handle(i);
//        handle->setEnabled(false);
//    }

//    QHBoxLayout *main_layout = new QHBoxLayout();
//    main_layout->addWidget(v_splitter);
//    main_layout->setSpacing(0);
//    main_layout->setContentsMargins(0, 0, 0, 0);


//    connect(theme_widget, SIGNAL(showSettingMainWidget()), this, SLOT(displaySettingHomePage()));
//    connect(icon_widget, SIGNAL(showSettingMainWidget()), this, SLOT(displaySettingHomePage()));
//    connect(mouse_widget, SIGNAL(showSettingMainWidget()), this, SLOT(displaySettingHomePage()));
//    connect(voice_widget, SIGNAL(showSettingMainWidget()), this, SLOT(displaySettingHomePage()));
//    connect(animation_widget, SIGNAL(showSettingMainWidget()), this, SLOT(displaySettingHomePage()));
//    connect(launcher_widget, SIGNAL(showSettingMainWidget()), this, SLOT(displaySettingHomePage()));
//    connect(panel_widget, SIGNAL(showSettingMainWidget()), this, SLOT(displaySettingHomePage()));
//    connect(window_widget, SIGNAL(showSettingMainWidget()), this, SLOT(displaySettingHomePage()));
//    connect(font_widget, SIGNAL(showSettingMainWidget()), this, SLOT(displaySettingHomePage()));
//    connect(touchpad_widget, SIGNAL(showSettingMainWidget()), this, SLOT(displaySettingHomePage()));
//    connect(deadpixel_widget, SIGNAL(showSettingMainWidget()), this, SLOT(displaySettingHomePage()));
//    connect(nautilus_widget, SIGNAL(showSettingMainWidget()), this, SLOT(displaySettingHomePage()));
}

SettingWidget::~SettingWidget()
{
    if(stacked_widget != NULL)
    {
        delete stacked_widget;
        stacked_widget = NULL;
    }
}

void SettingWidget::initUI(QString skin)
{
    theme_widget = new ThemeWidget(this, sessionProxy);
    icon_widget = new IconWidget(this, sessionProxy, desktop);
    mouse_widget = new MouseWidget(this, sessionProxy, systemProxy, desktop);
    voice_widget = new VoiceWidget(this, sessionProxy, systemProxy, desktop);
//    animation_widget = new AnimationWidget(this, systemProxy, p_mainwindow);
    launcher_widget = new LauncherWidget(this, sessionProxy, desktop);
    panel_widget = new PanelWidget(this, sessionProxy, desktop, battery);
    window_widget = new WindowWidget(this, sessionProxy, desktop);
    font_widget = new FontWidget(this, sessionProxy, p_mainwindow, desktop, skin);
    touchpad_widget = new TouchpadWidget(this, sessionProxy, desktop);
    deadpixel_widget = new DeadpixelWidget(this);
    conserve_widget = new ConserveWidget(this, sessionProxy, desktop, battery);
    nautilus_widget = new NautilusWidget(this, sessionProxy);
    stacked_widget->addWidget(h_splitter);
    stacked_widget->addWidget(theme_widget);
    stacked_widget->addWidget(icon_widget);
    stacked_widget->addWidget(mouse_widget);
    stacked_widget->addWidget(voice_widget);
//    stacked_widget->addWidget(animation_widget);
    stacked_widget->addWidget(launcher_widget);
    stacked_widget->addWidget(panel_widget);
    stacked_widget->addWidget(window_widget);
    stacked_widget->addWidget(font_widget);
    stacked_widget->addWidget(touchpad_widget);
    stacked_widget->addWidget(deadpixel_widget);
    stacked_widget->addWidget(conserve_widget);
    stacked_widget->addWidget(nautilus_widget);

    QHBoxLayout *main_layout = new QHBoxLayout();
    main_layout->addWidget(stacked_widget);
    main_layout->setSpacing(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    this->setLayout(main_layout);

//    connect(sessionProxy, SIGNAL(bool_value_notify(QString, bool)), this, SLOT(slot_notify_boolean(QString, bool)));
}

//void SettingWidget::slot_notify_boolean(QString key, bool value)
//{
//}
void SettingWidget::resetSkin(QString skin)
{
    if(font_widget != NULL)
        font_widget->resetCurrentSkin(skin);
}

void SettingWidget::initIndividuationWidget() {
    individuation_widget = new QWidget(this);
    individuation_icon = new QLabel();
    individuation_title = new QLabel();
    dot1 = new QLabel();
    theme_button = new QPushButton();
    dot2 = new QLabel();
    icon_button = new QPushButton();
    dot3 = new QLabel();
    mouse_button = new QPushButton();
    dot4 = new QLabel();
    voice_button = new QPushButton();
//    dot5 = new QLabel();
//    animation_button = new QPushButton();

    theme_button->setFocusPolicy(Qt::NoFocus);
    theme_button->setObjectName("settingButton");
    icon_button->setFocusPolicy(Qt::NoFocus);
    icon_button->setObjectName("settingButton");
    mouse_button->setFocusPolicy(Qt::NoFocus);
    mouse_button->setObjectName("settingButton");
    voice_button->setFocusPolicy(Qt::NoFocus);
    voice_button->setObjectName("settingButton");
//    animation_button->setFocusPolicy(Qt::NoFocus);
//    animation_button->setObjectName("settingButton");

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(individuation_icon);
    title_layout->addWidget(individuation_title);
    title_layout->addStretch();
    title_layout->setSpacing(10);
    title_layout->setContentsMargins(20, 20, 0, 0);
    title_layout->setAlignment(individuation_icon, Qt::AlignVCenter);
    title_layout->setAlignment(individuation_title, Qt::AlignVCenter);

    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addWidget(dot1);
    layout1->addWidget(theme_button);
    layout1->addStretch();
    layout1->setSpacing(5);
    layout1->setContentsMargins(29, 10, 0, 0);
    layout1->setAlignment(dot1, Qt::AlignVCenter);
    layout1->setAlignment(theme_button, Qt::AlignVCenter);

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addWidget(dot2);
    layout2->addWidget(icon_button);
    layout2->addStretch();
    layout2->setSpacing(5);
    layout2->setContentsMargins(29, 0, 0, 0);
    layout2->setAlignment(dot2, Qt::AlignVCenter);
    layout2->setAlignment(icon_button, Qt::AlignVCenter);

    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addWidget(dot3);
    layout3->addWidget(mouse_button);
    layout3->addStretch();
    layout3->setSpacing(5);
    layout3->setContentsMargins(29, 0, 0, 0);
    layout3->setAlignment(dot3, Qt::AlignVCenter);
    layout3->setAlignment(mouse_button, Qt::AlignVCenter);

    QHBoxLayout *layout4 = new QHBoxLayout();
    layout4->addWidget(dot4);
    layout4->addWidget(voice_button);
    layout4->addStretch();
    layout4->setSpacing(5);
    layout4->setContentsMargins(29, 0, 0, 0);
    layout4->setAlignment(dot4, Qt::AlignVCenter);
    layout4->setAlignment(voice_button, Qt::AlignVCenter);

//    QHBoxLayout *layout5 = new QHBoxLayout();
//    layout5->addWidget(dot5);
//    layout5->addWidget(animation_button);
//    layout5->addStretch();
//    layout5->setSpacing(5);
//    layout5->setContentsMargins(29, 0, 0, 0);
//    layout5->setAlignment(dot5, Qt::AlignVCenter);
//    layout5->setAlignment(animation_button, Qt::AlignVCenter);

    QVBoxLayout *v_layout = new QVBoxLayout();
    v_layout->addLayout(title_layout);
    v_layout->addLayout(layout1);
    v_layout->addLayout(layout2);
    v_layout->addLayout(layout3);
    v_layout->addLayout(layout4);
//    v_layout->addLayout(layout5);
    v_layout->addStretch();
    v_layout->setSpacing(10);
    v_layout->setContentsMargins(0, 0, 0, 0);

    individuation_widget->setLayout(v_layout);


    individuation_icon->setPixmap(QPixmap("://res/custom.png"));
    individuation_title->setText(tr("Personalize"));//个性化
    dot1->setPixmap(QPixmap("://res/dot.png"));
    dot2->setPixmap(QPixmap("://res/dot.png"));
    dot3->setPixmap(QPixmap("://res/dot.png"));
    dot4->setPixmap(QPixmap("://res/dot.png"));
//    dot5->setPixmap(QPixmap(":/res//dot.png"));
    theme_button->setStatusTip("theme");
    icon_button->setStatusTip("icon");
    mouse_button->setStatusTip("mouse");
    voice_button->setStatusTip("voice");
//    animation_button->setStatusTip("animation");
    theme_button->setText(tr("ThemeSetting"));//主题设置
    icon_button->setText(tr("IconSetting"));//图标配置
    mouse_button->setText(tr("MousePointer"));//鼠标指针
    voice_button->setText(tr("SoundEffect"));//声音效果
//    animation_button->setText(tr("BootAnimation"));//开机动画

    connect(theme_button, SIGNAL(clicked()), this, SLOT(displaySettingSubPage()));
    connect(icon_button, SIGNAL(clicked()), this, SLOT(displaySettingSubPage()));
    connect(mouse_button, SIGNAL(clicked()), this, SLOT(displaySettingSubPage()));
    connect(voice_button, SIGNAL(clicked()), this, SLOT(displaySettingSubPage()));
//    connect(animation_button, SIGNAL(clicked()), this, SLOT(displaySettingSubPage()));
}

void SettingWidget::initDesktopWidget() {
    dekstop_widget = new QWidget();
    dekstop_icon = new QLabel();
    dekstop_title = new QLabel();
    dot6 = new QLabel();
    launcher_button = new QPushButton();
    dot7 = new QLabel();
    panel_button = new QPushButton();
    dot8 = new QLabel();
    window_button = new QPushButton();

    launcher_button->setFocusPolicy(Qt::NoFocus);
    launcher_button->setObjectName("settingButton");
    panel_button->setFocusPolicy(Qt::NoFocus);
    panel_button->setObjectName("settingButton");
    window_button->setFocusPolicy(Qt::NoFocus);
    window_button->setObjectName("settingButton");

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(dekstop_icon);
    title_layout->addWidget(dekstop_title);
    title_layout->addStretch();
    title_layout->setSpacing(10);
    title_layout->setContentsMargins(20, 20, 0, 0);
    title_layout->setAlignment(dekstop_icon, Qt::AlignVCenter);
    title_layout->setAlignment(dekstop_title, Qt::AlignVCenter);

    QHBoxLayout *layout6 = new QHBoxLayout();
    layout6->addWidget(dot6);
    layout6->addWidget(launcher_button);
    layout6->addStretch();
    layout6->setSpacing(5);
    layout6->setContentsMargins(29, 10, 0, 0);
    layout6->setAlignment(dot6, Qt::AlignVCenter);
    layout6->setAlignment(launcher_button, Qt::AlignVCenter);

    QHBoxLayout *layout7 = new QHBoxLayout();
    layout7->addWidget(dot7);
    layout7->addWidget(panel_button);
    layout7->addStretch();
    layout7->setSpacing(5);
    layout7->setContentsMargins(29, 0, 0, 0);
    layout7->setAlignment(dot7, Qt::AlignVCenter);
    layout7->setAlignment(panel_button, Qt::AlignVCenter);

    QHBoxLayout *layout8 = new QHBoxLayout();
    layout8->addWidget(dot8);
    layout8->addWidget(window_button);
    layout8->addStretch();
    layout8->setMargin(0);
    layout8->setSpacing(5);
    layout8->setContentsMargins(29, 0, 0, 0);
    layout8->setAlignment(dot8, Qt::AlignVCenter);
    layout8->setAlignment(window_button, Qt::AlignVCenter);

    QVBoxLayout *v_layout = new QVBoxLayout();
    v_layout->addLayout(title_layout);
    v_layout->addLayout(layout6);
    v_layout->addLayout(layout7);
    v_layout->addLayout(layout8);
    v_layout->addStretch();
    v_layout->setSpacing(10);
    v_layout->setContentsMargins(0, 0, 0, 0);

    dekstop_widget->setLayout(v_layout);

    dekstop_icon->setPixmap(QPixmap("://res/desktop.png"));
    dekstop_title->setText(tr("Desktop"));//桌面
    dot6->setPixmap(QPixmap("://res/dot.png"));
    dot7->setPixmap(QPixmap("://res/dot.png"));
    dot8->setPixmap(QPixmap("://res/dot.png"));
    if (this->desktop == "mate") {
        launcher_button->setText(tr("Panel"));//面板
        panel_button->setText(tr("StartMenu"));//启动菜单
    }
    else {
        launcher_button->setText(tr("Custom Launcher"));//自定义启动器
        panel_button->setText(tr("Dash & Panel"));//搜索和面板
    }
    window_button->setText(tr("Window"));//窗口
    launcher_button->setStatusTip("launcher");
    panel_button->setStatusTip("panel");
    window_button->setStatusTip("window");

    connect(launcher_button, SIGNAL(clicked()), this, SLOT(displaySettingSubPage()));
    connect(panel_button, SIGNAL(clicked()), this, SLOT(displaySettingSubPage()));
    connect(window_button, SIGNAL(clicked()), this, SLOT(displaySettingSubPage()));
}

void SettingWidget::initFontWidget() {
    fonts_widget = new QWidget();
    font_icon = new QLabel();
    font_title = new QLabel();
    dot9 = new QLabel();
    font_button = new QPushButton();

    font_button->setFocusPolicy(Qt::NoFocus);
    font_button->setObjectName("settingButton");

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(font_icon);
    title_layout->addWidget(font_title);
    title_layout->addStretch();
    title_layout->setSpacing(10);
    title_layout->setContentsMargins(20, 20, 0, 0);
    title_layout->setAlignment(font_icon, Qt::AlignVCenter);
    title_layout->setAlignment(font_title, Qt::AlignVCenter);

    QHBoxLayout *layout9 = new QHBoxLayout();
    layout9->addWidget(dot9);
    layout9->addWidget(font_button);
    layout9->addStretch();
    layout9->setSpacing(5);
    layout9->setContentsMargins(29, 10, 0, 0);
    layout9->setAlignment(dot9, Qt::AlignVCenter);
    layout9->setAlignment(font_button, Qt::AlignVCenter);

    QVBoxLayout *v_layout = new QVBoxLayout();
    v_layout->addLayout(title_layout);
    v_layout->addLayout(layout9);
    v_layout->addStretch();
    v_layout->setSpacing(10);
    v_layout->setContentsMargins(0, 0, 0, 0);

    fonts_widget->setLayout(v_layout);

    font_icon->setPixmap(QPixmap("://res/font.png"));
    font_title->setText(tr("Font"));
    dot9->setPixmap(QPixmap("://res/dot.png"));
    font_button->setText(tr("FontSetting"));//字体设置
    font_button->setStatusTip("font");

    connect(font_button, SIGNAL(clicked()), this, SLOT(displaySettingSubPage()));
}

void SettingWidget::initOptionWidget() {
    option_widget = new QWidget();
    option_icon = new QLabel();
    option_title = new QLabel();
    dot10 = new QLabel();
    touch_button = new QPushButton();
    dot11 = new QLabel();
    pixel_button = new QPushButton();
    dot12 = new QLabel();
    conserve_button = new QPushButton();

    touch_button->setFocusPolicy(Qt::NoFocus);
    touch_button->setObjectName("settingButton");
    pixel_button->setFocusPolicy(Qt::NoFocus);
    pixel_button->setObjectName("settingButton");
    conserve_button->setFocusPolicy(Qt::NoFocus);
    conserve_button->setObjectName("settingButton");

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(option_icon);
    title_layout->addWidget(option_title);
    title_layout->addStretch();
    title_layout->setSpacing(10);
    title_layout->setContentsMargins(20, 20, 0, 0);
    title_layout->setAlignment(option_icon, Qt::AlignVCenter);
    title_layout->setAlignment(option_title, Qt::AlignVCenter);

    QHBoxLayout *layout10 = new QHBoxLayout();
    layout10->addWidget(dot10);
    layout10->addWidget(touch_button);
    layout10->addStretch();
    layout10->setSpacing(5);
    layout10->setContentsMargins(29, 10, 0, 0);
    layout10->setAlignment(dot10, Qt::AlignVCenter);
    layout10->setAlignment(touch_button, Qt::AlignVCenter);

    QHBoxLayout *layout11 = new QHBoxLayout();
    layout11->addWidget(dot11);
    layout11->addWidget(pixel_button);
    layout11->addStretch();
    layout11->setSpacing(5);
    layout11->setContentsMargins(29, 0, 0, 0);
    layout11->setAlignment(dot11, Qt::AlignVCenter);
    layout11->setAlignment(pixel_button, Qt::AlignVCenter);

    QHBoxLayout *layout12 = new QHBoxLayout();
    layout12->addWidget(dot12);
    layout12->addWidget(conserve_button);
    layout12->addStretch();
    layout12->setSpacing(5);
    layout12->setContentsMargins(29, 0, 0, 0);
    layout12->setAlignment(dot12, Qt::AlignVCenter);
    layout12->setAlignment(conserve_button, Qt::AlignVCenter);

    QVBoxLayout *v_layout = new QVBoxLayout();
    v_layout->addLayout(title_layout);
    v_layout->addLayout(layout10);
    v_layout->addLayout(layout11);
    v_layout->addLayout(layout12);
    v_layout->addStretch();
    v_layout->setSpacing(10);
    v_layout->setContentsMargins(0, 0, 0, 0);

    option_widget->setLayout(v_layout);

    option_icon->setPixmap(QPixmap("://res/system.png"));
    option_title->setText(tr("Sys options"));//系统选项
    dot10->setPixmap(QPixmap("://res/dot.png"));
    dot11->setPixmap(QPixmap("://res/dot.png"));
    dot12->setPixmap(QPixmap("://res/dot.png"));
    touch_button->setText(tr("Touchpad"));//触摸板设置
    pixel_button->setText(tr("Dead pixel check"));//坏点检测
    conserve_button->setText(tr("Energy saving"));
    touch_button->setStatusTip("touchpad");
    pixel_button->setStatusTip("deadpixel");
    conserve_button->setStatusTip("conserve");

    connect(touch_button, SIGNAL(clicked()), this, SLOT(displaySettingSubPage()));
    connect(pixel_button, SIGNAL(clicked()), this, SLOT(displaySettingSubPage()));
    connect(conserve_button, SIGNAL(clicked()), this, SLOT(displaySettingSubPage()));
//    connect(pixel_button, SIGNAL(clicked()), this, SLOT(showCheckscreenDialog()));
}

void SettingWidget::initOtherWidget() {
    other_widget = new QWidget();
    other_icon = new QLabel();
    other_title = new QLabel();
    dot13 = new QLabel();
    nautilus_button = new QPushButton();

    nautilus_button->setFocusPolicy(Qt::NoFocus);
    nautilus_button->setObjectName("settingButton");
//    nautilus_button->setStyleSheet("QPushButton{color:rgb(0, 120, 230);background:transparent;}QPushButton:hover{color:rgb(50, 150, 255);}QPushButton:pressed{color:rgb(50, 150, 255);}");

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(other_icon);
    title_layout->addWidget(other_title);
    title_layout->addStretch();
    title_layout->setSpacing(10);
    title_layout->setContentsMargins(20, 20, 0, 0);
    title_layout->setAlignment(other_icon, Qt::AlignVCenter);
    title_layout->setAlignment(other_title, Qt::AlignVCenter);

    QHBoxLayout *layout13 = new QHBoxLayout();
    layout13->addWidget(dot13);
    layout13->addWidget(nautilus_button);
    layout13->addStretch();
    layout13->setSpacing(5);
    layout13->setContentsMargins(29, 0, 0, 0);
    layout13->setAlignment(dot13, Qt::AlignVCenter);
    layout13->setAlignment(nautilus_button, Qt::AlignVCenter);

    QVBoxLayout *v_layout = new QVBoxLayout();
    v_layout->addLayout(title_layout);
    v_layout->addLayout(layout13);
    v_layout->addStretch();
    v_layout->setSpacing(10);
    v_layout->setContentsMargins(0, 0, 0, 0);

    other_widget->setLayout(v_layout);

    other_icon->setPixmap(QPixmap("://res/other.png"));
    other_title->setText(tr("Others"));//杂项
    dot13->setPixmap(QPixmap("://res/dot.png"));
    nautilus_button->setText(tr("File manager"));//文件管理器
    nautilus_button->setStatusTip("nautilus");

    connect(nautilus_button, SIGNAL(clicked()), this, SLOT(displaySettingSubPage()));
}

void SettingWidget::displaySettingHomePage() {
    stacked_widget->setCurrentIndex(0);
}

void SettingWidget::displaySettingSubPage() {
//    QObject *object = QObject::sender();
//	QAction *action = qobject_cast<QAction *>(object);
//	QString object_name = action->objectName();
//	int index = object_name.toInt();
    QObject *object = QObject::sender();
    QPushButton *btn = qobject_cast<QPushButton *>(object);
    QString object_name = btn->statusTip();
    if (object_name == "theme") {
        emit changeActionPage(1);
        if(!theme_widget->getStatus())
            theme_widget->initData();
        stacked_widget->setCurrentIndex(1);
//        stacked_widget->setCurrentWidget(theme_widget);
    }
    else if (object_name == "icon") {
        emit changeActionPage(2);
        if(!icon_widget->getStatus())
            icon_widget->initData();
        stacked_widget->setCurrentIndex(2);
    }
    else if (object_name == "mouse") {
        emit changeActionPage(3);
        if(!mouse_widget->getStatus())
            mouse_widget->initData();
        stacked_widget->setCurrentIndex(3);
    }
    else if (object_name == "voice") {
        emit changeActionPage(4);
        if(!voice_widget->getStatus())
            voice_widget->initData();
        stacked_widget->setCurrentIndex(4);
    }
//    else if (object_name == "animation") {
//        emit changeActionPage(5);
//        if(!animation_widget->getStatus())
//            animation_widget->initData();
//        stacked_widget->setCurrentIndex(5);
//    }

    else if (object_name == "launcher") {
        emit changeActionPage(5);
        if(!launcher_widget->getStatus())
            launcher_widget->initData();
        stacked_widget->setCurrentIndex(5);
    }
    else if (object_name == "panel") {
        emit changeActionPage(6);
        if(!panel_widget->getStatus())
            panel_widget->initData();
        stacked_widget->setCurrentIndex(6);
    }
    else if (object_name == "window") {
        emit changeActionPage(7);
        if(!window_widget->getStatus())
            window_widget->initData();
        stacked_widget->setCurrentIndex(7);
    }
    else if (object_name == "font") {
        emit changeActionPage(8);
        if(!font_widget->getStatus())
            font_widget->initData();
        stacked_widget->setCurrentIndex(8);
    }
    else if (object_name == "touchpad") {
        emit changeActionPage(9);
        if(!touchpad_widget->getStatus())
            touchpad_widget->initData();
        stacked_widget->setCurrentIndex(9);
    }
    else if (object_name == "deadpixel") {
        emit changeActionPage(10);
        stacked_widget->setCurrentIndex(10);
    }
    else if (object_name == "conserve") {
        emit changeActionPage(11);
        if(!conserve_widget->getStatus())
            conserve_widget->initData();
        stacked_widget->setCurrentIndex(11);
    }
    else if (object_name == "nautilus") {
        emit changeActionPage(12);
        if(!nautilus_widget->getStatus())
            nautilus_widget->initData();
        stacked_widget->setCurrentIndex(12);
    }
}
