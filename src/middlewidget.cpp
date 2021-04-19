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

#include "middlewidget.h"
#include "../component/kylintoolbutton.h"
#include "mainwindow.h"
#include <QDebug>

MiddleWidget::MiddleWidget(QWidget *parent, QString arch, QString os)
    : QWidget(parent), cur_arch(arch), osname(os)
{
    this->setFixedSize(860, 140);
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(34,103,242));//#e9eef1
    this->setPalette(palette);
//    this->setStyleSheet("MiddleWidget{background-color:#2267F2; border: none;/*border-top-left-radius:6px;border-top-right-radius:6px*/}");

//    InitMiddlewidget();
}

void MiddleWidget::paintEvent(QPaintEvent *event)
{
    QStyleOption opt;
    opt.init(this);
    QPainter p(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &p, this);
}


MiddleWidget::~MiddleWidget()
{
    for(int i=0; i<button_list.count(); i++)
    {
        KylinToolButton *btn = button_list.at(i);
        delete btn;
        btn = NULL;
    }
    button_list.clear();
}

void MiddleWidget::InitMiddlewidget()
{
    main_layout = new QVBoxLayout(this);
    main_layout->setContentsMargins(0, 0, 0, 0);
    main_layout->setSpacing(0);

    QWidget *topWidget = new QWidget(this);
    top_layout = new QHBoxLayout(topWidget);
    top_layout->setContentsMargins(0, 0, 0, 0);
    top_layout->setSpacing(0);
    main_layout->addWidget(topWidget, 0, Qt::AlignTop);

    QWidget *bottomWidget = new QWidget(this);
    botton_layout = new QHBoxLayout(bottomWidget);
    botton_layout->setContentsMargins(0, 0, 0, 0);
    botton_layout->setSpacing(0);
    main_layout->addStretch();
    main_layout->addWidget(bottomWidget, 0, Qt::AlignBottom);

    initTitlebarLeftContent();
    initTitlebarRightContent();
    initBottomContent();

    this->setLayout(main_layout);
}

void MiddleWidget::initTitlebarLeftContent()
{
    QWidget *w = new QWidget(this);
//    w->setFixedHeight(38);
//    w->setStyleSheet("QWidget{background-color:red;}");
    m_titleLeftLayout = new QHBoxLayout(w);
    m_titleLeftLayout->setContentsMargins(8, 8, 0, 0);
    m_titleLeftLayout->setSpacing(8);

    iconlable = new QLabel(w);
    qDebug() << Q_FUNC_INFO << QIcon::hasThemeIcon("kylin-assistant");
    iconlable->setPixmap(QIcon::fromTheme("kylin-assistant").pixmap(24,24));
    const QByteArray id("org.ukui.style");
    if (QGSettings::isSchemaInstalled(id)){
        QGSettings *Setting = new QGSettings(id);
        connect(Setting,&QGSettings::changed,[=](QString key){
            if("iconThemeName" == key){
                iconlable->setPixmap(QIcon::fromTheme("kylin-assistant").pixmap(24,24));
            }
        });
    }
//    iconlable->setFixedSize(24,24);
    m_titleLeftLayout->addWidget(iconlable);

    QLabel *appLabel = new QLabel(w);
    appLabel->setStyleSheet("QLabel{background-color:transparent;color:#ffffff; font-size:14px;}");
    appLabel->setText(tr("ToolKit"));
    m_titleLeftLayout->addWidget(appLabel);

    top_layout->addWidget(w, 1, Qt::AlignLeft|Qt::AlignTop);
}

void MiddleWidget::initTitlebarRightContent()
{
     qDebug()<< Q_FUNC_INFO;
    QWidget *w = new QWidget(this);
    m_titleRightLayout = new QHBoxLayout(w);
    m_titleRightLayout->setContentsMargins(0, 4, 4, 0);
    m_titleRightLayout->setSpacing(4);

    top_layout->addWidget(w, 1, Qt::AlignRight|Qt::AlignTop);

    QPushButton *min_button = new QPushButton(w);
    min_button->setFixedSize(30,30);
    min_button->setProperty("isWindowButton", 0x1);
    min_button->setProperty("useIconHighlightEffect", 0x2);
    min_button->setProperty("setIconHighlightEffectDefaultColor", QColor(Qt::white));
    min_button->setFlat(true);
    QPushButton *close_button = new QPushButton(w);
    close_button->setFixedSize(30,30);
    close_button->setProperty("isWindowButton", 0x2);
    close_button->setProperty("useIconHighlightEffect", 0x8);
    close_button->setProperty("setIconHighlightEffectDefaultColor", QColor(Qt::white));
    close_button->setFlat(true);
//    SystemButton *skin_button = new SystemButton();
    QPushButton *main_menu_button = new QPushButton(w);
    main_menu_button->setFixedSize(30,30);
    main_menu_button->setProperty("isWindowButton", 0x1);
    main_menu_button->setProperty("useIconHighlightEffect", 0x2);
    main_menu_button->setProperty("setIconHighlightEffectDefaultColor", QColor(Qt::white));
    main_menu_button->setFlat(true);

    min_button->setIcon(QIcon::fromTheme("window-minimize-symbolic"));
    close_button->setIcon(QIcon::fromTheme("window-close-symbolic"));
//    skin_button->loadPixmap(":/sys/res/sysBtn/skin_button.png");
    main_menu_button->setIcon(QIcon::fromTheme("open-menu-symbolic"));
    min_button->setFocusPolicy(Qt::NoFocus);
    close_button->setFocusPolicy(Qt::NoFocus);
//    skin_button->setFocusPolicy(Qt::NoFocus);
    main_menu_button->setFocusPolicy(Qt::NoFocus);

    m_titleRightLayout->addWidget(main_menu_button);
//    m_titleRightLayout->addWidget(skin_button);
    m_titleRightLayout->addWidget(min_button);
    m_titleRightLayout->addWidget(close_button);

    connect(main_menu_button, &SystemButton::clicked, this, [=] {
        emit this->middle_showMenu();
        /*if (parentWidget()) {
            parentWidget()->showMainMenu();
        }*/
    });
//    connect(skin_button, &SystemButton::clicked, this, [=] {
//        if (parentWidget() && parentWidget()->parentWidget()) {
//            //openSkinCenter()
//        }
//    });
    connect(min_button, &SystemButton::clicked, [=] (const bool b) {
        emit this->middle_showMin();
//        if (p_mainwindow)
//            p_mainwindow->showMinimized();
//        if (parentWidget()) {
//            parentWidget()->showMinimized();
//        }
    });
    connect(close_button, &SystemButton::clicked, this, [=] {
        emit this->middle_closeApp();
//        window()->close();
    });
}

void MiddleWidget::initBottomContent()
{
    QStringList icon_list;
    QStringList text_list;
    QStringList text;

    QWidget *w = new QWidget;
//    w->setStyleSheet("background-color:gay;");
    QHBoxLayout *content_layout = new QHBoxLayout(w);
    content_layout->addStretch();
    content_layout->setSpacing(50);
    content_layout->setMargin(0);
    content_layout->setContentsMargins(0, 0, 0, 0);
//    if(this->cur_arch == "aarch64" || this->osname == "Kylin" || this->osname == "YHKylin")
//    {
//        icon_list<<":/tool/res/menu/home"<<":/tool/res/menu/cleanup"<<":/tool/res/menu/sysinfo"<<":/tool/res/menu/toolkits";
//        text_list<< tr("KylinHome") << tr("Cleanup") << tr("Sysinfo") << tr("Toolkits");
//    }
//    else {
//        icon_list<<":/tool/res/menu/home"<<":/tool/res/menu/cleanup"<<":/tool/res/menu/sysinfo"<<":/tool/res/menu/feature"<<":/tool/res/menu/toolkits";
//        text_list<< tr("Home") << tr("Cleanup") << tr("Sysinfo") << tr("Feature") << tr("Toolkits");
//    }

//    icon_list<<":/tool/res/menu/system-clean.png"/*<<":/tool/res/menu/optimize"*/<< ":/tool/res/menu/monitor.png" << ":/tool/res/menu/drive-manager.png" <<":/tool/res/menu/sysinfo"<<":/tool/res/menu/toolkits" ;
    icon_list<<":/svg/res/svg/top.svg" /*<< ":/svg/res/svg/top2.svg"*/;
    text_list<< tr("Cleanup") /*<< tr("Optimize") */;
    text << "Cleanup" /*<< "Optimize"*/ ;

    if(!hide)
    {
        icon_list <<":/svg/res/svg/top3.svg";
        text_list << tr("Monitor") ;
        text << "Monitor";
    }

    icon_list <<":/svg/res/svg/top4.svg"<<":/svg/res/svg/top5.svg"<<":/svg/res/svg/top7.svg";
    text_list << tr("Drive")<< tr("Sysinfo") << tr("Toolkits") ;
    text << "Drive" << "Sysinfo" << "Toolkits";

    content_layout->addStretch(1);
    QSignalMapper *signal_mapper = new QSignalMapper(this);
    for(int i=0; i<icon_list.size(); i++)
    {
        KylinToolButton *tool_button = new KylinToolButton(icon_list.at(i), text_list.at(i));
        tool_button->setFixedSize(92, 93);
        tool_button->setStatusTip(text.at(i));
        button_list.append(tool_button);
        connect(tool_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(tool_button, QString::number(i, 10));
        content_layout->addWidget(tool_button, 0, Qt::AlignHCenter);
    }
    this->switchSelectedPageIndex("0");
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(switchSelectedPageIndex(QString)));
    content_layout->addStretch(1);

//    setLayout(button_layout);
    is_move = false;

    botton_layout->addWidget(w);
}

void MiddleWidget::switchSelectedPageIndex(QString index)
{
    bool ok;
    int current_index = index.toInt(&ok, 10);
//    qDebug() << index;
    KylinToolButton *index_button;
    for(int i=0; i<button_list.count(); i++)
    {
        KylinToolButton *tool_button = button_list.at(i);
        if(current_index == i)
        {
            index_button = button_list.at(i);
            tool_button->setMousePress(true);
        }
        else
        {
            tool_button->setMousePress(false);
        }
    }
//    qDebug() << index_button->statusTip();
    emit turnCurrentPage(index_button->statusTip());
}

void MiddleWidget::showBoxTool()
{
//    if(this->cur_arch == "aarch64" || this->osname == "Kylin" || this->osname == "YHKylin") {
//        this->switchSelectedPageIndex("3");
//    }
//    else {
    this->switchSelectedPageIndex("3");
//    }
}
