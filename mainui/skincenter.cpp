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

#include "skincenter.h"
#include "mainwindow.h"
#include <QDebug>
#include <QVBoxLayout>

SkinCenter::SkinCenter(QWidget *parent/*, Qt::WindowFlags f*/)
    :QDialog(parent)
{
    this->setFixedSize(500, 271);
//    this->setStyleSheet("QDialog{border: 1px solid gray;border-radius:2px}");
    this->setStyleSheet("QDialog{border: none;background-color: #ffffff;}");
    setWindowFlags(Qt::FramelessWindowHint);
    title_bar = new KylinTitleBar();

    skin_widget = new QWidget();
    list_widget = NULL;

    QVBoxLayout *layout  = new QVBoxLayout();
    layout->addWidget(title_bar);
    layout->addWidget(skin_widget);
    layout->setSpacing(10);
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);

//    list_widget = new KylinListWidget();
//    connect(list_widget, SIGNAL(sendBackgroundName(QString)), this, SLOT(changeSkinCenterBackground(QString)));
//    list_widget->setMouseTracking(true);//hover need it
//    list_widget->setAutoFillBackground(false);

//    using_label = new QLabel(list_widget);
//    using_label->setFixedSize(17, 26);
//    using_label->setAutoFillBackground(true);
//    QPalette palette;
////    palette.setBrush(using_label->backgroundRole(), QBrush(QPixmap("://res/clothes.png")));
//    palette.setBrush(QPalette::Background, QBrush(QPixmap("://res/clothes.png")));
//    using_label->setPalette(palette);
//    using_label->show();

////    QHBoxLayout *list_layout  = new QHBoxLayout();
////    list_layout->addWidget(list_widget);
////    list_layout->setSpacing(0);
////    list_layout->setMargin(0);
////    list_layout->setContentsMargins(1, 0, 1, 1);

////    QVBoxLayout *layout  = new QVBoxLayout();
////    layout->addWidget(title_bar);
//////    layout->addWidget(list_widget);
////    layout->addLayout(list_layout);
////    layout->setSpacing(0);
////    layout->setMargin(0);
////    layout->setContentsMargins(0, 0, 0, 0);
////    setLayout(layout);


//    QGridLayout *grid_layout = new QGridLayout();
//    grid_layout->addWidget(list_widget);
//    QVBoxLayout *layout  = new QVBoxLayout();
//    layout->addWidget(title_bar);
//    layout->addLayout(grid_layout);
//    layout->setSpacing(0);
//    layout->setMargin(0);
//    layout->setContentsMargins(0, 0, 0, 0);
//    setLayout(layout);


////    delayTimer = QTimer();

//    this->setLanguage();
    this->initConnect();
}

SkinCenter::~SkinCenter()
{
    if(title_bar != NULL) {
        delete title_bar;
        title_bar = NULL;
    }
    if(skin_widget != NULL) {
        delete skin_widget;
        skin_widget = NULL;
    }
//    disconnect(delayTimer,SIGNAL(timeout()),this,SLOT(changeAnimationStep()));
//    if(delayTimer->isActive()) {
//        delayTimer->stop();
//    }
//    if (delayTimer != NULL) {
//        delete delayTimer;
//        delayTimer = NULL;
//    }
}

//void SkinCenter::setLanguage()
//{

//}

void SkinCenter::initConnect()
{
    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCloseButtonClicked()));
//    connect(delayTimer, SIGNAL(timeout()), this, SLOT(changeAnimationStep()));
}

void SkinCenter::onCloseButtonClicked()
{
    this->close();
}

void SkinCenter::changeSkinCenterBackground(QString pciture)
{
//    int index = 1;
    last_skin_path = pciture;
    title_bar->resetBackground(last_skin_path);
//    int  start_pos = pciture.lastIndexOf("/") + 1;
//    int end_pos = pciture.length();
//    index = pciture.mid(start_pos, end_pos-start_pos).replace(".png", "").toInt();
//    qDebug() << index;
//    QListWidgetItem *cur_item = list_widget->item(index - 1);
//    this->initUsingLogo(cur_item);


    mainwindow->changeSkin(pciture);
}

void SkinCenter::changeEnterBackground(QString pciture)
{
    mainwindow->reViewThePointSkin(pciture);
    title_bar->resetBackground(pciture);
}

void SkinCenter::changeLeaveBackground()
{
    mainwindow->reViewTheOrgSkin();
    title_bar->resetBackground(last_skin_path);
}

void SkinCenter::deleteBackground(QString picture)
{
//    qDebug() << picture;
    bool result = mainwindow->deleteFile(picture);
    if (result)
    {
        list_widget->clear_card();
        this->reloadBackgroundList();
        QString conf_skin = mainwindow->getCurrentBackgroundAbsName();
        if (conf_skin == picture)
            this->changeSkinCenterBackground(":/background/res/skin/1.png");
    }
}

void SkinCenter::initBackgroundList()
{
//    self.winListWidget = CardWidget(427, 88, 6, self.ui.winpageWidget)
//    self.winListWidget.setGeometry(0, 50, 860 + 6 + (20 - 6) / 2, 516)
//    self.winListWidget.calculate_data()
//    list_widget = new CardWidget(200, 88, 6, this->skin_widget);
    list_widget = new CardWidget(212, 100, 20, this->skin_widget);
    list_widget->setGeometry(QRect(30, 0, 500, 239));
    list_widget->calculate_data();

    QDir picdir("/var/lib/youker-assistant-daemon/background");
    picdir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    picdir.setSorting(QDir::Size | QDir::Reversed);
    QStringList filters;
    filters << "*.jpg" << "*.png";
    picdir.setNameFilters(filters);
    QFileInfoList list = picdir.entryInfoList();
    QString cur_skin = mainwindow->getCurrentBackgroundName();
    card_list.clear();
//    qDebug() << "getCurrentBackgroundName->" << mainwindow->getCurrentBackgroundName();
    QSignalMapper *signal_mapper = new QSignalMapper(this);
    for (int j = 0; j < list.size(); ++j) {
        QFileInfo fileInfo = list.at(j);
//        qDebug() << fileInfo.fileName();
         ItemCard *card = new ItemCard(fileInfo.fileName(), list_widget->cardPanel);
         card_list.append(card);
         if(cur_skin == fileInfo.fileName())
             card->showUsingLogo(true);
         list_widget->add_card(card);
         connect(card, SIGNAL(sendBackgroundName(QString)), signal_mapper, SLOT(map()));
         signal_mapper->setMapping(card, QString::number(j, 10));
         connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(switchUsingLogo(QString)));
         connect(card, SIGNAL(sendBackgroundName(QString)), this, SLOT(changeSkinCenterBackground(QString)));
         connect(card, SIGNAL(sendEnterBackground(QString)), this, SLOT(changeEnterBackground(QString)));
         connect(card, SIGNAL(sendLeaveBackground()), this, SLOT(changeLeaveBackground()));
         connect(card, SIGNAL(sendDelteSignal(QString)), this, SLOT(deleteBackground(QString)));
    }

//    list_widget->setIconSize(QSize(150, 100));
//    list_widget->setResizeMode(QListView::Adjust);
//    list_widget->setViewMode(QListView::IconMode);
//    list_widget->setMovement(QListView::Static);
//    list_widget->setSpacing(9);
//    list_widget->setMainWindow(mainwindow);

//    list_widget->setFocusPolicy(Qt::NoFocus);

//    for(int index = 0; index < 4; ++index)
//    {
//        QString iconPath = QString(":/background/res/skin/%1.png").arg(index + 1);
//        QPixmap pixMap(iconPath);
//        KylinListWidgetItem *item = new KylinListWidgetItem(QIcon(pixMap.scaled(QSize(150,100))), "");
//        item->setMainWindow(mainwindow);
//        item->setSkinName(iconPath);
//        item->setSizeHint(QSize(150,100));
//        list_widget->insertItem(index, item);
//    }

////    qDebug() << mainwindow->getCurrentBackgroundIndex();
////    QListWidgetItem *cur_item = list_widget->item(mainwindow->getCurrentBackgroundIndex() - 1);
////    this->initUsingLogo(cur_item);
}

void SkinCenter::reloadBackgroundList()
{
    list_widget->setGeometry(QRect(0,2, 500, 230));
    list_widget->calculate_data();

    QDir picdir("/var/lib/youker-assistant-daemon/background");
    picdir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    picdir.setSorting(QDir::Size | QDir::Reversed);
    QStringList filters;
    filters << "*.jpg" << "*.png";
    picdir.setNameFilters(filters);
    QFileInfoList list = picdir.entryInfoList();
    QString cur_skin = mainwindow->getCurrentBackgroundName();
    card_list.clear();
    QSignalMapper *signal_mapper = new QSignalMapper(this);
    for (int j = 0; j < list.size(); ++j) {
        QFileInfo fileInfo = list.at(j);
//        qDebug() << fileInfo.fileName();
        ItemCard *card = new ItemCard(fileInfo.fileName(), list_widget->cardPanel);
        card->show();
        card_list.append(card);
        if(cur_skin == fileInfo.fileName())
            card->showUsingLogo(true);
        list_widget->add_card(card);
        connect(card, SIGNAL(sendBackgroundName(QString)), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(card, QString::number(j, 10));
        connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(switchUsingLogo(QString)));
        connect(card, SIGNAL(sendBackgroundName(QString)), this, SLOT(changeSkinCenterBackground(QString)));
        connect(card, SIGNAL(sendEnterBackground(QString)), this, SLOT(changeEnterBackground(QString)));
        connect(card, SIGNAL(sendLeaveBackground()), this, SLOT(changeLeaveBackground()));
        connect(card, SIGNAL(sendDelteSignal(QString)), this, SLOT(deleteBackground(QString)));
    }
}

void SkinCenter::switchUsingLogo(QString index)
{
    bool ok;
    int current_index = index.toInt(&ok, 10);
//    qDebug () << "current_index->" << current_index;
    for(int i=0; i<card_list.count(); i++)
    {
        ItemCard *card = card_list.at(i);
        if(current_index == i)
        {
            card->showUsingLogo(true);
        }
        else
        {
            card->showUsingLogo(false);
        }
    }
}

void SkinCenter::initTitleBar(const QString &path)
{
    title_bar->setTitleWidth(500);
    title_bar->setTitleName(tr("Skin Center"));
    last_skin_path = path;
    title_bar->setTitleBackgound(last_skin_path);
}

//void SkinCenter::setLogo()
//{
//    qDebug() << mainwindow->getCurrentBackgroundIndex();
//    QListWidgetItem *cur_item = list_widget->item(mainwindow->getCurrentBackgroundIndex() - 1);
//    this->initUsingLogo(cur_item);
//}


//void SkinCenter::initUsingLogo(QListWidgetItem *init_item) {
////    int nRowIndex = list_widget->row(init_item);
//    QRect rect = list_widget->visualItemRect(init_item);
//    QPoint p = rect.topLeft();
//    using_label->move(p.x(), p.y());
//    qDebug() << p.x();
//    qDebug() << p.y();
//    qDebug() <<"----------------";
////    QPoint p = rect.bottomRight();
////    using_label->move(p.x()-20, p.y()-40);
//    //reset current item status
////    QListWidgetItem *pre_item = list_widget->item(current_index);
////    pre_item->setTextColor(QColor(0, 0, 255, 127));
////    current_index = nRowIndex;
////    init_item->setTextColor(QColor("4f4f4f"));
//}

////void MainWindow::reViewThePointSkin(QString pciture)
////{
////  if (review_skin_pixmap.isDetached())
////  {
////    review_skin_pixmap.detach();
////  }

////  review_skin_pixmap.load(pciture);
////  QPalette palette_back;
////  palette_back.setBrush(QPalette::Background, review_skin_pixmap);
////  action_widget->setPalette(palette_back);
////}

////void  SkinCenter::enterEvent (QEvent *)
////{
////    delayTimer->start(300);
////}

////void  SkinCenter::leaveEvent (QEvent *)
////{
////    if(delayTimer->isActive())
////        delayTimer->stop();
////}

void SkinCenter::closeEvent(QCloseEvent *event)
{
    title_bar->setTitleBackgound(last_skin_path);
    mainwindow->restoreSkin();
}
