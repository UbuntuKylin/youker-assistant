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

#include "themewidget.h"
#include <QStandardItemModel>
#include <QListWidgetItem>
#include <QDebug>

//#include "../component/kylinmenu.h"
#include "../dbusproxy/youkersessiondbus.h"

ThemeWidget::ThemeWidget(QWidget *parent, SessionDispatcher *proxy) :
    QWidget(parent),
    sessionproxy(proxy)
{
//    splitter = new QSplitter();
//    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    splitter->setOrientation(Qt::Vertical);
//    splitter->setHandleWidth(1);

//    top_widget = new QWidget();
//    bottom_widget = new QWidget();

//    title_label = new QLabel();
//    title_label->setFixedHeight(20);
//    description_label = new QLabel();
//    description_label->setFixedHeight(20);
//    back_btn = new QPushButton();

//    QVBoxLayout *v_layout = new QVBoxLayout();
//    v_layout->addWidget(title_label);
//    v_layout->addWidget(description_label);
//    v_layout->setMargin(0);
//    v_layout->setSpacing(1);

//    QHBoxLayout *h_layout = new QHBoxLayout();
//    h_layout->addWidget(back_btn);
//    h_layout->addLayout(v_layout);
//    h_layout->addStretch();
//    top_widget->setLayout(h_layout);
//    top_widget->setFixedSize(900,60);
//    h_layout->setSpacing(20);
//    h_layout->setContentsMargins(20, 0, 0, 0);


//    list_view = new QListView();
//    model = new QStringListModel();
//    QPixmap pix("://res/ubuntukylin.png");
//    QBrush brush(pix);
//    /*QStandardItemModel **/cokMusicListModel=new QStandardItemModel(0,1);
//    for(int i=0;i<6;i++) {
//        QStandardItem * item =new QStandardItem();
//        item->setText(tr("kobe%1").arg(i));
//        item->setSizeHint(QSize(106,106));
//        item->setFont(QFont("微软雅黑",10,1));
//        item->setBackground(brush);
//        cokMusicListModel->appendRow(item);
//    }
////    QStringListModel *model = new QStringListModel(user);
////    userList->setModel(model);        //useList是个QListView
//    list_view->setModel(cokMusicListModel);
//    list_view->setSpacing(5);
//    main_layout->addWidget(list_view);




    //创建QListWidget部件
    list_widget = new QListWidget(this);
    list_widget->setFocusPolicy(Qt::NoFocus);
    //设置QListWidget中的单元项的图片大小
    list_widget->setIconSize(QSize(106, 106));
    list_widget->setResizeMode(QListView::Adjust);
    //设置QListWidget的显示模式
    list_widget->setViewMode(QListView::IconMode);
    //设置QListWidget中的单元项不可被拖动
    list_widget->setMovement(QListView::Static);
    //设置QListWidget中的单元项的间距
    list_widget->setSpacing(26);


    current_index = 0;
    QString current_theme = sessionproxy->get_theme_qt();

    QStringList syslist = sessionproxy->get_themes_qt();
    QList<QString>::Iterator it = syslist.begin(), itend = syslist.end();
    int initIndex = 0;
    for(;it != itend; it++,initIndex++)
    {
        if(*it == current_theme)
            break;
    }

    for(int i = 0; i<syslist.length(); ++i)
    {
        QString strPath=QString(":/gtk/res/theme/" + syslist[i] + ".png");
        QPixmap pixmap(strPath);
        if(pixmap.isNull())
        {
            pixmap = QPixmap(":/gtk/res/theme/disappear.png");
        }
        //伸缩106*106
        QListWidgetItem *pItem = new QListWidgetItem(QIcon(pixmap.scaled(QSize(106,106))), tr("%1").arg(syslist[i]));
        pItem->setSizeHint(QSize(130,130));
//        pItem->setFlags(Qt::ItemIsSelectable);
//        pItem->setBackgroundColor(QColor(0, 0, 255, 127));
        pItem->setTextColor(QColor(0, 0, 255, 127));
        list_widget->insertItem(i, pItem);
//        QPushButton *btn = new QPushButton("aa");
//        list_widget->setItemWidget(pItem, btn);
    }


    using_label = new QLabel(list_widget);
    using_label->setFixedSize(20, 20);
    using_label->setAutoFillBackground(true);
    QPalette palette;
//    palette.setBrush(using_label->backgroundRole(), QBrush(QPixmap("://res/using.png")));
    palette.setBrush(QPalette::Background, QBrush(QPixmap("://res/checkbox-press.png")));
    using_label->setPalette(palette);
    using_label->show();
//    using_label->move(26, 26);

    //set using logo
    QListWidgetItem *cur_item = list_widget->item(initIndex);
    this->initCurrentTheme(cur_item);

//    QHBoxLayout *layout = new QHBoxLayout();
//    layout->addWidget(list_widget);
//    setLayout(layout);
    QGridLayout *layout = new QGridLayout();
    layout->addWidget(list_widget);
    setLayout(layout);

    this->setLanguage();
    this->initConnect();
}

ThemeWidget::~ThemeWidget()
{
}

void ThemeWidget::setLanguage() {
//    title_label->setText(tr("Theme settings"));
//    description_label->setText(tr("Choose the theme what you want."));
//    back_btn->setText(tr("Back"));
}

void ThemeWidget::initConnect() {
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
    connect(list_widget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onItemClicked(QListWidgetItem*)));
}

void ThemeWidget::initCurrentTheme(QListWidgetItem *init_item)
{
    int nRowIndex = list_widget->row(init_item);
    QRect rect = list_widget->visualItemRect(init_item);
//    qDebug() << rect;
//    QPoint p = rect.topLeft();
//    using_label->move(p.x(), p.y());
    QPoint p = rect.bottomRight();
    using_label->move(p.x()-20, p.y()-40);
//    using_label->move(p.x(), p.y());
    //reset current item status
    QListWidgetItem *pre_item = list_widget->item(current_index);
    pre_item->setTextColor(QColor(0, 0, 255, 127));
    current_index = nRowIndex;
    init_item->setTextColor(QColor("4f4f4f"));
}


void ThemeWidget::onItemClicked(QListWidgetItem *selected_item)
{
    if(!selected_item)
    {
        return;
    }
    sessionproxy->set_theme_qt(selected_item->text());

    int nRowIndex = list_widget->row(selected_item);
    //kobe test current pos
//    KylinMenu *main_menu = new KylinMenu(this);
//    if(list_widget->itemAt(mapFromGlobal(QCursor::pos())) != NULL)
//    {
//        main_menu->exec(QCursor::pos()); // 菜单出现的位置为当前鼠标的位置
//    }
    QRect rect = list_widget->visualItemRect(selected_item);
//    qDebug() << rect;
//    QPoint p = rect.topLeft();
    QPoint p = rect.bottomRight();
    using_label->move(p.x()-20, p.y()-40);
//    p.setX(p.x() + 58);
//    p.setY(p.y() + 29);
//    using_label->move(p.x(), p.y());
//    main_menu->exec(this->mapToGlobal(p));

    //reset current item status
    QListWidgetItem *pre_item = list_widget->item(current_index);
    pre_item->setTextColor(QColor(0, 0, 255, 127));

    current_index = nRowIndex;
//    qDebug() << nRowIndex;
//    qDebug() << selected_item->text();
//    item->setBackgroundColor(QColor(0, 0, 255, 127));
    selected_item->setTextColor(QColor("4f4f4f"));
//    selected_item->setSizeHint(QSize(130,130));

//    for(int i=0; i < list_widget->count(); i++)
//    {
//        if (i != nRowIndex)
//        {
//            QListWidgetItem *unselected_item = list_widget->item(i);
//            unselected_item->setTextColor(QColor(0, 0, 255, 127));
//            unselected_item->setSizeHint(QSize(100,100));
//        }
//    }
}

void ThemeWidget::paintEvent(QPaintEvent *)
{
    //kobe: if the scrollbar move, the using_label should move the the select item
    QListWidgetItem *select_item = list_widget->item(current_index);
    QRect rect = list_widget->visualItemRect(select_item);
//    QPoint p = rect.topLeft();
//    using_label->move(p.x(), p.y());
    QPoint p = rect.bottomRight();
    using_label->move(p.x()-20, p.y()-40);
}
