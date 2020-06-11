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
//    QPalette palette;
//    palette.setColor(QPalette::Background, QColor(34,103,242));//#e9eef1
//    this->setPalette(palette);
    this->setStyleSheet("MiddleWidget{background-color:#2267F2; border: none;border-top-left-radius:10px;border-top-right-radius:10px}");

    InitMiddlewidget();
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

    QWidget *topWidget = new QWidget;
    top_layout = new QHBoxLayout(topWidget);
    top_layout->setContentsMargins(0, 0, 0, 0);
    top_layout->setSpacing(0);
    main_layout->addWidget(topWidget, 0, Qt::AlignTop);

    QWidget *bottomWidget = new QWidget;
    botton_layout = new QHBoxLayout(bottomWidget);
    botton_layout->setContentsMargins(105, 0, 0, 0);
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
    qDebug()<< Q_FUNC_INFO;
    QWidget *w = new QWidget;
    m_titleLeftLayout = new QHBoxLayout(w);
    m_titleLeftLayout->setContentsMargins(6, 0, 0, 0);
    m_titleLeftLayout->setSpacing(5);

    QLabel *iconlable = new QLabel(w);
    QPixmap icon(":/res/kylin-assistant.png");
    QPixmap iconNew = icon.scaled(QSize(20,20),Qt::KeepAspectRatio);
    iconlable->setPixmap(iconNew);
    iconlable->setFixedSize(20,20);
    m_titleLeftLayout->addWidget(iconlable);

    QLabel *appLabel = new QLabel(w);
    appLabel->setStyleSheet("QLabel{background-color:transparent;color:#ffffff; font-size:12px;}");
    appLabel->setText(tr("Kylin Assistant"));
    m_titleLeftLayout->addWidget(appLabel);

    top_layout->addWidget(w, 1, Qt::AlignLeft);
}

void MiddleWidget::initTitlebarRightContent()
{
     qDebug()<< Q_FUNC_INFO;
    QWidget *w = new QWidget;
    m_titleRightLayout = new QHBoxLayout(w);
    m_titleRightLayout->setContentsMargins(0, 0, 1, 0);
    m_titleRightLayout->setSpacing(0);

    top_layout->addWidget(w, 1, Qt::AlignRight);

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

    QWidget *w = new QWidget;
//    w->setStyleSheet("background-color:gay;");
    QHBoxLayout *content_layout = new QHBoxLayout(w);
//    if(this->cur_arch == "aarch64" || this->osname == "Kylin" || this->osname == "YHKylin")
//    {
//        icon_list<<":/tool/res/menu/home"<<":/tool/res/menu/cleanup"<<":/tool/res/menu/sysinfo"<<":/tool/res/menu/toolkits";
//        text_list<< tr("KylinHome") << tr("Cleanup") << tr("Sysinfo") << tr("Toolkits");
//    }
//    else {
//        icon_list<<":/tool/res/menu/home"<<":/tool/res/menu/cleanup"<<":/tool/res/menu/sysinfo"<<":/tool/res/menu/feature"<<":/tool/res/menu/toolkits";
//        text_list<< tr("Home") << tr("Cleanup") << tr("Sysinfo") << tr("Feature") << tr("Toolkits");
//    }

    icon_list<<":/tool/res/menu/system-clean.png"/*<<":/tool/res/menu/optimize"*/<< ":/tool/res/menu/monitor.png" << ":/tool/res/menu/drive-manager.png" <<":/tool/res/menu/sysinfo"<<":/tool/res/menu/toolkits" ;
    text_list<< tr("Cleanup") /*<< tr("Optimize")*/ << tr("Monitoring") << tr("Drive")<< tr("Sysinfo") << tr("Toolkits") ;

    QSignalMapper *signal_mapper = new QSignalMapper(this);
    for(int i=0; i<icon_list.size(); i++)
    {
        KylinToolButton *tool_button = new KylinToolButton(icon_list.at(i), text_list.at(i));
        tool_button->setFixedSize(92, 93);
        button_list.append(tool_button);
        connect(tool_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(tool_button, QString::number(i, 10));
        content_layout->addWidget(tool_button, 0, Qt::AlignBottom);
    }
    this->switchSelectedPageIndex("0");
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(switchSelectedPageIndex(QString)));

    content_layout->addStretch();
    content_layout->setSpacing(50);
    content_layout->setMargin(0);
    content_layout->setContentsMargins(0, 0, 0, 0);

//    setLayout(button_layout);
    is_move = false;

    botton_layout->addWidget(w);
}

void MiddleWidget::switchSelectedPageIndex(QString index)
{
    bool ok;
    int current_index = index.toInt(&ok, 10);
//    qDebug() << index;
    for(int i=0; i<button_list.count(); i++)
    {
        KylinToolButton *tool_button = button_list.at(i);
        if(current_index == i)
        {
            tool_button->setMousePress(true);
        }
        else
        {
            tool_button->setMousePress(false);
        }
    }
    emit turnCurrentPage(current_index);
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
