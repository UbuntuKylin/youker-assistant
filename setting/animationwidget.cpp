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

#include "animationwidget.h"
#include <QDebug>
#include "../component/agentlistitem.h"
#include "../dbusproxy/youkersystemdbus.h"
#include "../mainui/mainwindow.h"
#include <QStringList>
#include <QFileDialog>
#include "../component/tipdialog.h"

AnimationWidget::AnimationWidget(QWidget *parent, SystemDispatcher *proxy, MainWindow *window) :
    QWidget(parent),
    systemproxy(proxy), parentWindow(window)
{
    dataOK = false;
    title_label = new QLabel();
    left_widget = new QWidget();
    left_widget->setFixedWidth(240);
    right_widget = new QWidget();
    right_widget->setFixedWidth(500);

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

    custom_btn = new QPushButton();
    custom_btn->setFixedSize(120, 32);
    custom_btn->setObjectName("blackButton");
    custom_btn->setFocusPolicy(Qt::NoFocus);
    ok_btn = new QPushButton();
    ok_btn->setFixedSize(91, 25);
    ok_btn->setObjectName("blackButton");
    ok_btn->setFocusPolicy(Qt::NoFocus);

    view_widget = new QWidget();
    view_widget->setFixedSize(205, 190);
    view_widget->setWindowFlags(Qt::FramelessWindowHint);
    view_widget->setAutoFillBackground(true);
    QPalette palette;
//    palette.setColor(QPalette::Background, QColor(192,253,123));
    palette.setBrush(QPalette::Background, QBrush(QPixmap("://res/previewzone.png")));
    view_widget->setPalette(palette);

    show_widget = new QWidget();
    show_widget->setFixedSize(172, 115);
//    show_widget->setWindowFlags(Qt::FramelessWindowHint);
//    show_widget->setAutoFillBackground(true);
//    show_widget->setObjectName("transparentWidget");

    QVBoxLayout *layout0 = new QVBoxLayout();
    layout0->addWidget(show_widget);
    layout0->addStretch();
    layout0->setMargin(0);
    layout0->setSpacing(0);
    view_widget->setLayout(layout0);
    view_widget->setContentsMargins(16, 16, 16, 0);

    tip_label = new QLabel();
    list_widget = new QListWidget();
    list_widget->setObjectName("animationListWidget");

//    QStringList names;
//    for (int i = 1; i <= 30; ++i)
//        names.append(tr("app %1").arg(i));
//    list_widget->insertItems(0, names);
    list_widget->setIconSize(QSize(16, 16));
    list_widget->setResizeMode(QListView::Adjust);
//    list_widget->setViewMode(QListView::IconMode);
    list_widget->setMovement(QListView::Static);
    list_widget->setSpacing(5);

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(title_label);
    layout->addStretch();
    layout->setMargin(0);
    layout->setContentsMargins(20, 20, 0, 0);


    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addStretch();
    layout1->addWidget(view_widget, Qt::AlignHCenter);
    layout1->addStretch();

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addStretch();
    layout2->addWidget(custom_btn, Qt::AlignHCenter);
    layout2->addStretch();

    QVBoxLayout *layout3 = new QVBoxLayout();
    layout3->addLayout(layout1);
    layout3->addLayout(layout2);
    layout3->addStretch();
    layout3->setAlignment(Qt::AlignHCenter);
    layout3->setSpacing(20);
    left_widget->setLayout(layout3);

    QHBoxLayout *layout4 = new QHBoxLayout();
    layout4->addStretch();
    layout4->addWidget(ok_btn);

    QVBoxLayout *layout5 = new QVBoxLayout();
    layout5->addWidget(tip_label);
    layout5->addWidget(list_widget);
    layout5->addLayout(layout4);
    right_widget->setLayout(layout5);

//    QHBoxLayout *layout6 = new QHBoxLayout();
//    layout6->addWidget(left_widget);
//    layout6->addWidget(right_widget);
//    bottom_widget->setLayout(layout6);
//    bottom_widget->setFixedWidth(850);


//    splitter->addWidget(top_widget);
//    splitter->addWidget(bottom_widget);

    QHBoxLayout *widget_layout = new QHBoxLayout();
//    main_layout->addWidget(splitter);
    widget_layout->addWidget(left_widget);
    widget_layout->addWidget(right_widget);
    widget_layout->setSpacing(60);
    widget_layout->setMargin(0);
    widget_layout->setContentsMargins(0, 0, 0, 0);


    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(layout);
    main_layout->addLayout(widget_layout);
    main_layout->setSpacing(30);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 0, 0);

    setLayout(main_layout);
//    this->initData();
    this->setLanguage();
}

AnimationWidget::~AnimationWidget()
{
//    if(title_label != NULL)
//    {
//        delete title_label;
//        title_label = NULL;
//    }
//    if(back_btn != NULL)
//    {
//        delete back_btn;
//        back_btn = NULL;
//    }
}

void AnimationWidget::setLanguage() {
//    title_label->setText(tr("Boot animation settings"));
//    description_label->setText(tr("Click the \"Custom Picture\" button to select the picture you want to add, click the picture you want to set and push the \"OK\" button to complete."));
//    back_btn->setText(tr("Back"));
    title_label->setText(tr("Please select a picture as boot animation"));
    custom_btn->setText(tr("Custom Picture"));
    tip_label->setText(tr("Optional BootAnimation"));
    ok_btn->setText(tr("OK"));
}

void AnimationWidget::initConnect() {
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
    connect(custom_btn, SIGNAL(clicked()), this, SLOT(selectCustomAnimation()));
    connect(ok_btn, SIGNAL(clicked()), this, SLOT(setCustomAnimation()));
}

bool AnimationWidget::getStatus()
{
    return this->dataOK;
}

void AnimationWidget::initData()
{


//    bootimagepage.selectedimage = plymouth_list[0];

    systemproxy->plymouth_init_check_qt();
    QStringList valid_list;
    QStringList plymouth_list = systemproxy->get_existing_plymouth_list_qt();
    for(int i=0; i < plymouth_list.length(); i++) {
        if(systemproxy->get_image_path_qt(plymouth_list[i]) != "False"){
//            mainModel.append({"itemTitle": plymouth_list[i]});
            valid_list.append(plymouth_list[i]);
        }
    }

    for(int nIndex = 0;nIndex < valid_list.length();++nIndex)
    {
        QString strPath=QString("://res/picture.png");
        QPixmap objPixmap(strPath);
//        //生成QListWidgetItem对象(注意：其Icon图像进行了伸缩[16*16])---scaled函数
//        QListWidgetItem *pItem = new QListWidgetItem(QIcon(objPixmap.scaled(QSize(16,16))), tr("animal picture %1").arg(nIndex));
//        //设置单元项的宽度和高度
//        pItem->setSizeHint(QSize(130,20));
//        pItem->setBackgroundColor(QColor(0, 0, 255, 127));
//        pItem->setTextColor(QColor(0, 0, 255, 127));
//        list_widget->insertItem(nIndex, pItem);

        AgentListItem *account_item = new AgentListItem();
        account_item->setCurrentItemName(QString(valid_list[nIndex]));
        connect(account_item, SIGNAL(showItemName(QString)), this, SLOT(displayCurrentItemInfo(QString)));
        connect(account_item, SIGNAL(removeItem(QString)), this, SLOT(deleteSelectedAnimation(QString)));
        QListWidgetItem *item = new QListWidgetItem(list_widget);
//        item->setSizeHint(QSize(130,20));
//        item->setBackgroundColor(QColor(0, 0, 255, 127));
        item->setIcon(QIcon(objPixmap.scaled(QSize(16,16))));
        list_widget->setItemWidget(item, account_item);
    }
//    connect(list_widget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(onItemClicked(QListWidgetItem*)));
    dataOK = true;
    this->initConnect();
}

void AnimationWidget::selectCustomAnimation()
{
    show_widget->setWindowFlags(Qt::FramelessWindowHint);
    show_widget->setAutoFillBackground(true);
//    show_widget->setObjectName("transparentWidget");

    QStringList fileNameList;
    QString abs_path;
    QFileDialog* fd = new QFileDialog(this);
    fd->resize(500, 471);
    fd->setFilter(tr("Image Files (*.png *.jpg *.gif)"));
    fd->setViewMode(QFileDialog::List);//设置浏览模式，有 列表（list） 模式和 详细信息（detail）两种方式
    if (fd->exec() == QDialog::Accepted)
    {
        fileNameList = fd->selectedFiles();
        abs_path = fileNameList[0];
        int  start_pos = abs_path.lastIndexOf("/") + 1;
        int end_pos = abs_path.length();
        QString pic_name = abs_path.mid(start_pos, end_pos-start_pos);
        this->selected_animation = pic_name;
        QPalette palette;
    //    palette.setBrush(QPalette::Background, QBrush(QPixmap("://res/ubuntukylin.png").scaled(180, 170, Qt::KeepAspectRatio)));
        palette.setBrush(QPalette::Background, QBrush(QPixmap(abs_path).scaled(172, 115, Qt::KeepAspectRatio)));
        show_widget->setPalette(palette);
        systemproxy->add_new_plymouth_qt(abs_path, pic_name);
        //update date
        list_widget->clear();
        this->initData();
    }
    else
        fd->close();
}

void AnimationWidget::setCustomAnimation()
{
//    QList<QListWidgetItem *>::const_iterator i=list_widget.begin();
//    qDebug() << (*i)->text();
    systemproxy->custom_plymouth_bg_qt(this->selected_animation);
}

void AnimationWidget::deleteSelectedAnimation(QString name)
{
    QString result = systemproxy->delete_plymouth_qt(name);
    if (result == "ok") {
//        toolkits.alertMSG(qsTr("Deleted successfully!"));//删除成功！
//        qDebug() << "Deleted successfully!";

        int list_count = list_widget->count();
        for(int i=0; i < list_count; i++)
        {
            QListWidgetItem *item = list_widget->item(i);
            AgentListItem *account_item = (AgentListItem *)(list_widget->itemWidget(item));
            QString cur_name = account_item->getCurrentItemName();
            if(name == cur_name)
            {
                list_widget->takeItem(i);
                delete item;
                break;
            }
        }
        TipDialog *dialog = new TipDialog(0, tr("Deleted successfully!"));
        int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (180  / 2);
        dialog->move(w_x, w_y);
        dialog->show();
        dialog->raise();
    }
    else if (result == "use") {
//        qDebug() << "This is the using animation!";
        TipDialog *dialog = new TipDialog(0, tr("This is the using animation!"));
        int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (180  / 2);
        dialog->move(w_x, w_y);
        dialog->show();
        dialog->raise();
//        toolkits.alertMSG(qsTr("This is the using animation!"));//该动画为当前使用动画！
    }
    else if (result == "sys") {
        qDebug() << "This is the default animation!";
        TipDialog *dialog = new TipDialog(0, tr("This is the default animation!"));
        int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (180  / 2);
        dialog->move(w_x, w_y);
        dialog->show();
        dialog->raise();
//        toolkits.alertMSG(qsTr("This is the default animation!"));//该动画为系统默认动画！
    }
    else {
//        qDebug() << "An unknown error occurred!";
        TipDialog *dialog = new TipDialog(0, tr("An unknown error occurred!"));
        int w_x = parentWindow->frameGeometry().topLeft().x() + (900 / 2) - (410  / 2);
        int w_y = parentWindow->frameGeometry().topLeft().y() + (600 /2) - (180  / 2);
        dialog->move(w_x, w_y);
        dialog->show();
        dialog->raise();
//        toolkits.alertMSG(qsTr("An unknown error occurred!"));//发生未知错误！
    }
}

void AnimationWidget::displayCurrentItemInfo(QString info)
{
    this->selected_animation = info;
    int list_count = list_widget->count();
    for(int i=0; i < list_count; i++)
    {
        QListWidgetItem *item = list_widget->item(i);
        AgentListItem *account_item = (AgentListItem *)(list_widget->itemWidget(item));
        QString cur_name = account_item->getCurrentItemName();
        if(info == cur_name)
        {
            list_widget->setCurrentItem(item);
            break;
        }
    }
}
