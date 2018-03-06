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
#include <QPropertyAnimation>
#include <QParallelAnimationGroup>

//20161228
SkinCenter::SkinCenter(QWidget *parent, QString skin, QString arch, QString os)
    :QDialog(parent)
{
    this->setFixedSize(442, 340);
    this->setStyleSheet("QDialog{border: 1px solid white;border-radius:1px;background-color: #ffffff;}");
//    this->setStyleSheet("QDialog{border: 1px solid gray;border-radius:2px}");
//    this->setStyleSheet("QDialog{border: none;background-color: #ffffff;}");
    setWindowFlags(Qt::FramelessWindowHint);
//    title_bar = new KylinTitleBar(this);
    this->setWindowTitle(tr("Skin Setting"));

    last_skin_path = skin;
    aboutGroup = NULL;
    contributorGroup = NULL;
//    mouse_enter = false;

    baseWidget = new QWidget(this);
    baseWidget->setGeometry(QRect(0, 0, 442, 82));
    baseWidget->setAutoFillBackground(true);

    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(skin)));
    baseWidget->setPalette(palette);

    close_btn = new SystemButton(baseWidget);
    close_btn->setFocusPolicy(Qt::NoFocus);
    close_btn->loadPixmap(":/sys/res/sysBtn/close_button.png");
    if (arch == "aarch64" || os == "Kylin" || os == "YHKylin") {//20161228
        close_btn->move(442-36, 0);
    }
    else {
        close_btn->move(0, 0);
    }

    label = new QLabel(baseWidget);
    label->setGeometry(QRect(71, 0, 300, 30));
    label->setStyleSheet("QLabel{color:#ffffff;font-family: 方正黑体_GBK;font-size: 12px;text-align: center;font-weight:bold;}");
    label->setAlignment(Qt::AlignCenter);
    label->setText(tr("Skin Setting"));

    skin_widget = new QWidget(this);
//    skin_widget->setGeometry(QRect(6, 92, 430, 230));
    skin_widget->setGeometry(QRect(15, 93, 420, 240));
    list_widget = NULL;

    custom_list_widget = NULL;


    sysBtn = new QPushButton(baseWidget);
    sysBtn->setText(tr("Default"));
    sysBtn->setGeometry(QRect(10, 50, 60, 24));
    customBtn = new QPushButton(baseWidget);
    customBtn->setText(tr("Custom"));
    customBtn->setGeometry(QRect(75, 50, 60, 24));
    indicator = new QLabel(baseWidget);
    indicator->setStyleSheet("QLabel{background-image:url('://res/underline.png');background-position:center;}");
    indicator->setGeometry(QRect(10, 75, 60, 2));
    sysBtn->setFocusPolicy(Qt::NoFocus);
    sysBtn->setObjectName("transparentButton");
    customBtn->setFocusPolicy(Qt::NoFocus);
    customBtn->setObjectName("transparentButton");
    sysBtn->setStyleSheet("QPushButton{border:none;text-align:center;font-family: 方正黑体_GBK;font-size:14px;color:#ffffff;}");//QPushButton:hover{color:#666666;} background:transparent
    customBtn->setStyleSheet("QPushButton{border:none;text-align:center;font-family: 方正黑体_GBK;font-size:14px;color:#ffffff;}");//QPushButton:hover{color:#666666;} background:transparent

//    QVBoxLayout *layout  = new QVBoxLayout();
//    layout->addWidget(title_bar);
//    layout->addWidget(skin_widget);
//    layout->setSpacing(10);
//    layout->setMargin(0);
//    layout->setContentsMargins(0, 0, 0, 0);
//    setLayout(layout);

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
    this->initAnimation();
    this->initConnect();
}

SkinCenter::~SkinCenter()
{
    if(aboutGroup != NULL)
    {
        delete aboutGroup;
        aboutGroup = NULL;
    }
    if(contributorGroup != NULL)
    {
        delete contributorGroup;
        contributorGroup = NULL;
    }
    for(int i=0; i<card_list.count(); i++)
    {
        ItemCard *card = card_list.at(i);
        delete card;
        card = NULL;
    }
    card_list.clear();
    for(int i=0; i<custom_card_list.count(); i++)
    {
        ItemCard *card = custom_card_list.at(i);
        delete card;
        card = NULL;
    }
    custom_card_list.clear();

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

void SkinCenter::initAnimation()
{
    QRect mainAcitonRect(10, 75, 60, 2);
    QRect origAcitonRect(75, 75, 60, 2);

    QPropertyAnimation *aboutAnimation = new QPropertyAnimation(indicator, "geometry");
    aboutAnimation->setDuration(300);
    aboutAnimation->setStartValue(origAcitonRect);
    aboutAnimation->setEndValue(mainAcitonRect);

    aboutGroup = new QParallelAnimationGroup(this);
    aboutGroup->addAnimation(aboutAnimation);

    QPropertyAnimation *contributorAnimation = new QPropertyAnimation(indicator, "geometry");
    contributorAnimation->setDuration(300);
    contributorAnimation->setStartValue(mainAcitonRect);
    contributorAnimation->setEndValue(origAcitonRect);

    contributorGroup = new QParallelAnimationGroup(this);
    contributorGroup->addAnimation(contributorAnimation);
}

void SkinCenter::initConnect()
{
//    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCloseButtonClicked()));
    connect(close_btn, SIGNAL(clicked()), this, SLOT(onCloseButtonClicked()));
    connect(sysBtn,SIGNAL(clicked()), this, SLOT(showSystem()));
    connect(customBtn,SIGNAL(clicked()), this, SLOT(showCustom()));
//    connect(delayTimer, SIGNAL(timeout()), this, SLOT(changeAnimationStep()));
}

void SkinCenter::showSystem()
{
    aboutGroup->start();
    if(list_widget != NULL)
        list_widget->show();
    if(custom_list_widget != NULL)
        custom_list_widget->hide();
}

void SkinCenter::showCustom()
{
    contributorGroup->start();
    if(custom_list_widget != NULL)
        custom_list_widget->show();
    if(list_widget != NULL)
        list_widget->hide();
}

void SkinCenter::onCloseButtonClicked()
{
    this->close();
}

void SkinCenter::changeSkinCenterBackground(QString pciture)
{
//    int index = 1;
    last_skin_path = pciture;
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(last_skin_path)));
    baseWidget->setPalette(palette);

//    title_bar->resetBackground(last_skin_path);
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
//    title_bar->resetBackground(pciture);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(pciture)));
    baseWidget->setPalette(palette);
}

void SkinCenter::changeLeaveBackground()
{
    mainwindow->reViewTheOrgSkin();
//    title_bar->resetBackground(last_skin_path);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(last_skin_path)));
    baseWidget->setPalette(palette);
}

void SkinCenter::deleteBackground(QString picture)
{
    bool result = mainwindow->deleteFile(picture);
    if (result)
    {
//        list_widget->clear_card();
        custom_list_widget->clear_card();
        this->reloadBackgroundList();
        QString conf_skin = mainwindow->getCurrentBackgroundAbsName();
        if (conf_skin == picture)
            this->changeSkinCenterBackground(":/background/res/skin/1.png");
    }
}

void SkinCenter::initSysBackgroundList()
{
//    self.winListWidget = CardWidget(427, 88, 6, self.ui.winpageWidget)
//    self.winListWidget.setGeometry(0, 50, 860 + 6 + (20 - 6) / 2, 516)
//    self.winListWidget.calculate_data()
//    list_widget = new CardWidget(200, 88, 6, this->skin_widget);
    list_widget = new CardWidget(130, 87, 10, this->skin_widget);
    list_widget->setGeometry(QRect(0, 0, 420, 240));
    list_widget->calculate_data();
    QDir picdir("/var/lib/kylin-assistant-daemon/default");
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
         ItemCard *card = new ItemCard(fileInfo.fileName(), false, list_widget->cardPanel);
//         card->resetdislayDelBtnValue(true);//test
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
//         connect(card, SIGNAL(sendDelteSignal(QString)), this, SLOT(deleteBackground(QString)));
    }




//    custom_list_widget = new CardWidget(212, 100, 20, this->skin_widget);
    custom_list_widget = new CardWidget(130, 87, 10, this->skin_widget);
    custom_list_widget->hide();
//    custom_list_widget->setGeometry(QRect(30, 0, 500, 239));
    custom_list_widget->setGeometry(QRect(0, 0, 420, 240));
    custom_list_widget->calculate_data();
    QDir customdir("/var/lib/kylin-assistant-daemon/custom");
    customdir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    customdir.setSorting(QDir::Size | QDir::Reversed);
    customdir.setNameFilters(filters);
    QFileInfoList custom_list = customdir.entryInfoList();
    QString cur_custom_skin = mainwindow->getCurrentBackgroundName();
    custom_card_list.clear();
//    qDebug() << "getCurrentBackgroundName->" << mainwindow->getCurrentBackgroundName();
    QSignalMapper *custom_mapper = new QSignalMapper(this);
    for (int j = 0; j < custom_list.size(); ++j) {
        QFileInfo fileInfo = custom_list.at(j);
        ItemCard *card = new ItemCard(fileInfo.fileName(), true, custom_list_widget->cardPanel);
        card->resetdislayDelBtnValue(true);
        custom_card_list.append(card);
        if(cur_custom_skin == fileInfo.fileName())
            card->showUsingLogo(true);
        custom_list_widget->add_card(card);
        connect(card, SIGNAL(sendBackgroundName(QString)), custom_mapper, SLOT(map()));
        custom_mapper->setMapping(card, QString::number(j, 10));
        connect(custom_mapper, SIGNAL(mapped(QString)), this, SLOT(switchCusteomUsingLogo(QString)));
        connect(card, SIGNAL(sendBackgroundName(QString)), this, SLOT(changeSkinCenterBackground(QString)));
        connect(card, SIGNAL(sendEnterBackground(QString)), this, SLOT(changeEnterBackground(QString)));
        connect(card, SIGNAL(sendLeaveBackground()), this, SLOT(changeLeaveBackground()));
        connect(card, SIGNAL(sendDelteSignal(QString)), this, SLOT(deleteBackground(QString)));
    }
    ItemCard *card = new ItemCard("://res/create.png", true, custom_list_widget->cardPanel);
    custom_card_list.append(card);
    custom_list_widget->add_card(card);
    connect(card, SIGNAL(sendAddSignal()), this, SLOT(addCustomBackground()));
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
//    list_widget->setGeometry(QRect(0,2, 500, 230));
//    list_widget->calculate_data();
    custom_list_widget->setGeometry(QRect(0,2, 500, 230));
    custom_list_widget->calculate_data();

//    QDir picdir("/var/lib/kylin-assistant-daemon/default");
    QDir picdir("/var/lib/kylin-assistant-daemon/custom");
    picdir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
    picdir.setSorting(QDir::Size | QDir::Reversed);
    QStringList filters;
    filters << "*.jpg" << "*.png";
    picdir.setNameFilters(filters);
    QFileInfoList list = picdir.entryInfoList();
    QString cur_skin = mainwindow->getCurrentBackgroundName();
//    card_list.clear();
    //no need to call this code, because it have called custom_list_widget->clear_card();
//    for(int i=0; i<custom_card_list.count(); i++)
//    {
//        ItemCard *card = custom_card_list.at(i);
//        delete card;
//        card = NULL;
//    }
    custom_card_list.clear();
    QSignalMapper *signal_mapper = new QSignalMapper(this);
    for (int j = 0; j < list.size(); ++j) {
        QFileInfo fileInfo = list.at(j);
//        ItemCard *card = new ItemCard(fileInfo.fileName(), list_widget->cardPanel);
        ItemCard *card = new ItemCard(fileInfo.fileName(), true, custom_list_widget->cardPanel);
        card->resetdislayDelBtnValue(true);
        card->show();
//        card_list.append(card);
        custom_card_list.append(card);
        if(cur_skin == fileInfo.fileName())
            card->showUsingLogo(true);
//        list_widget->add_card(card);
        custom_list_widget->add_card(card);
        connect(card, SIGNAL(sendBackgroundName(QString)), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(card, QString::number(j, 10));
//        connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(switchUsingLogo(QString)));
        connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(switchCusteomUsingLogo(QString)));
        connect(card, SIGNAL(sendBackgroundName(QString)), this, SLOT(changeSkinCenterBackground(QString)));
        connect(card, SIGNAL(sendEnterBackground(QString)), this, SLOT(changeEnterBackground(QString)));
        connect(card, SIGNAL(sendLeaveBackground()), this, SLOT(changeLeaveBackground()));
        connect(card, SIGNAL(sendDelteSignal(QString)), this, SLOT(deleteBackground(QString)));
    }
    ItemCard *card = new ItemCard("://res/create.png", true, custom_list_widget->cardPanel);
    card->show();
    custom_card_list.append(card);
    custom_list_widget->add_card(card);
    connect(card, SIGNAL(sendAddSignal()), this, SLOT(addCustomBackground()));
}

void SkinCenter::addCustomBackground()
{
    //QStringList fileNameList;
    //QString fileName;
    //QFileDialog* fd = new QFileDialog(this);
    //fd->resize(500, 471);
//  //  fd->setFilter("Allfile(*.*);;png(*.png);;jpg(*.jpg)");
    //fd->setNameFilter(tr("Image Files(*.jpg *.png)"));
    //fd->setViewMode(QFileDialog::List);
    //if (fd->exec() == QDialog::Accepted)
    //{
    //    fileNameList = fd->selectedFiles();
    //    fileName = fileNameList[0];
//  //      qDebug() << "select pic name ->" << fileName;
    //    bool result = mainwindow->CopyFile(fileName);
    //    if(result == true) {
    //        custom_list_widget->clear_card();
    //        this->reloadBackgroundList();
    //        int  start_pos = fileName.lastIndexOf("/") + 1;
    //        int end_pos = fileName.length();
    //        QString icon_name = "/var/lib/kylin-assistant-daemon/custom/";
    //        QString abs_name = icon_name.append(fileName.mid(start_pos, end_pos-start_pos));
//  //          qDebug() << "abs_name->" << abs_name;
    //        this->changeSkinCenterBackground(abs_name);

    //        //change custom using logo
    //        for(int i=0; i<custom_card_list.count() - 1; i++)
    //        {
    //            ItemCard *card = custom_card_list.at(i);
    //            qDebug() << card->getCardName();
    //            if(card->getCardName() == abs_name)
    //            {
    //                card->showUsingLogo(true);
    //            }
    //            else
    //            {
    //                card->showUsingLogo(false);
    //            }
    //        }

    //        //change system using logo
    //        for(int i=0; i<card_list.count(); i++)
    //        {
    //            ItemCard *card = card_list.at(i);
    //            card->showUsingLogo(false);
    //        }
    //    }
    //}
    //else
    //    fd->close();
    
    QStringList fileNameList;
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), ".",
                                                    tr("Files(*.png *.jpg)"));
    if (fileName.length() == 0)
    {
//        QMessageBox::information(NULL, tr("Path"), tr("You didn't select any files."));
    }
    else
    {
        bool result = mainwindow->CopyFile(fileName);
        if(result == true)
        {
            custom_list_widget->clear_card();
            this->reloadBackgroundList();
            int  start_pos = fileName.lastIndexOf("/") + 1;
            int end_pos = fileName.length();
            QString icon_name = "/var/lib/kylin-assistant-daemon/custom/";
            QString abs_name = icon_name.append(fileName.mid(start_pos, end_pos-start_pos));
            this->changeSkinCenterBackground(abs_name);

            for(int i=0; i<custom_card_list.count() - 1; i++)
            {
                ItemCard *card = custom_card_list.at(i);
                qDebug() << card->getCardName();
                if(card->getCardName() == abs_name)
                {
                    card->showUsingLogo(true);
                }
                else
                {
                    card->showUsingLogo(false);
                }
            }

            //change system using logo
            for(int i=0; i<card_list.count(); i++)
            {
                ItemCard *card = card_list.at(i);
                card->showUsingLogo(false);
            }
        }
//        QMessageBox::information(NULL, tr("Path"), tr("You select ") + fileName);
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
    //change custom using logo
    for(int i=0; i<custom_card_list.count()-1; i++)
    {
        ItemCard *card = custom_card_list.at(i);
        card->showUsingLogo(false);
    }
}

void SkinCenter::switchCusteomUsingLogo(QString index)
{
    bool ok;
    int current_index = index.toInt(&ok, 10);
    for(int i=0; i<custom_card_list.count(); i++)
    {
        ItemCard *card = custom_card_list.at(i);
        if(current_index == i)
        {
            card->showUsingLogo(true);
        }
        else
        {
            card->showUsingLogo(false);
        }
    }
    //change ystem using logo
    for(int i=0; i<card_list.count(); i++)
    {
        ItemCard *card = card_list.at(i);
        card->showUsingLogo(false);
    }
}

//void SkinCenter::initTitleBar(const QString &path)
//{
//    title_bar->setTitleWidth(500);
//    title_bar->setTitleName(tr("Skin Center"));
//    last_skin_path = path;
//    title_bar->setTitleBackgound(last_skin_path);
//}

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

//void SkinCenter::paintEvent(QPaintEvent *)
//{
//    if(mouse_enter)
//    {
//        //绘制边框
//        QPainter painter(this);
//        QPen pen(QColor("red"));
//        painter.setPen(pen);
//        painter.drawRoundRect(0,0,this->width()-1, this->height()-1, 5, 5);
//    }
//}

//void SkinCenter::enterEvent(QEvent *)
//{
//    mouse_enter = true;
//    update();
//}

//void SkinCenter::leaveEvent(QEvent *)
//{
//    mouse_enter = false;
//    update();
//}

void SkinCenter::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton)
    {
        m_mousePressed = true;
        m_dragPosition = event->globalPos() - this->frameGeometry().topLeft();
        event->accept();
    }
}

void SkinCenter::mouseReleaseEvent(QMouseEvent *)
{
    m_mousePressed = false;
}

void SkinCenter::mouseMoveEvent(QMouseEvent *event)
{
    if(m_mousePressed)
    {
        QPoint move_pos = event->globalPos();
        move(move_pos - m_dragPosition);
        event->accept();
    }
}

void SkinCenter::closeEvent(QCloseEvent *event)
{
//    title_bar->setTitleBackgound(last_skin_path);
    QPalette palette;
    palette.setBrush(QPalette::Background, QBrush(QPixmap(last_skin_path)));
    baseWidget->setPalette(palette);
    mainwindow->restoreSkin();
}
