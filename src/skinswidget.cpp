/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
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

#include "skinswidget.h"
#include <QDebug>
#include <QSettings>
SkinsWidget::SkinsWidget(QSettings *mSettings, QWidget *parent)
    :QWidget(parent)
{
    this->resize(620, 445);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);

    pSettings = mSettings;
    skinName = QString("");

    mouse_press = false;
    is_change = false;
    current_page = 1;
    tip_list<<tr("皮肤1")<<tr("皮肤2")<<tr("皮肤3")<<tr("皮肤4")<<tr("皮肤5")<<
        tr("皮肤6")<<tr("皮肤7")<<tr("皮肤8")<<tr("皮肤9")<<tr("皮肤10");
    this->initTitleBar();
    this->initSkinsCenter();
    this->initBottomBar();

    QVBoxLayout *mainLayout = new QVBoxLayout();
    mainLayout->addLayout(titleLayout);
    mainLayout->addLayout(centerLayout);
    mainLayout->addLayout(bottomLayout);
    mainLayout->addStretch();
    mainLayout->setSpacing(0);
    mainLayout->setContentsMargins(0, 0, 0, 0);
    setLayout(mainLayout);
    this->showSkin(QString::number(current_page, 10));


    QDesktopWidget* desktop = QApplication::desktop();
    move((desktop->width() - this->width())/2, (desktop->height() - this->height())/2);
}

void SkinsWidget::initTitleBar() {
    title_label = new QLabel();
    title_icon_label = new QLabel();
    close_button = new QLabel();
    QPixmap title_pixmap(":/pixmap/image/youker-assistant.png");
    title_icon_label->setPixmap(title_pixmap);
    title_icon_label->setFixedSize(16, 16);
    title_icon_label->setScaledContents(true);

    title_label->setFixedHeight(30);
    title_label->setText(tr("优客皮肤中心"));
    close_button->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));

    titleLayout = new QHBoxLayout();
    titleLayout->addWidget(close_button, 0, Qt::AlignVCenter);
    titleLayout->addStretch();
    titleLayout->addWidget(title_icon_label, 0, Qt::AlignVCenter);
    titleLayout->addWidget(title_label, 0, Qt::AlignVCenter);
    titleLayout->setSpacing(5);
    titleLayout->setContentsMargins(10, 0, 5, 0);
    title_label->setStyleSheet("color:white;");
    close_button->installEventFilter(this);
}

void SkinsWidget::initSkinsCenter() {
    //皮肤列表
    skin_list<<":/skin/image/0"<<":/skin/img/skin/1"<<":/skin/image/2"<<":/skin/image/3"<<":/skin/image/4"<<
        ":/skin/image/5"<<":/skin/image/6"<<":/skin/image/7";

    centerLayout = new QGridLayout();
    centerLayout->setSpacing(5);
    centerLayout->setContentsMargins(5, 35, 5, 0);

    //一页显示8个皮肤
    change_skin_widget_0 = new SkinGrid();
    change_skin_widget_1 = new SkinGrid();
    change_skin_widget_2 = new SkinGrid();
    change_skin_widget_3 = new SkinGrid();
    change_skin_widget_4 = new SkinGrid();
    change_skin_widget_5 = new SkinGrid();
    change_skin_widget_6 = new SkinGrid();
    change_skin_widget_7 = new SkinGrid();

    connect(change_skin_widget_0, SIGNAL(skinSignal(QString)), this, SLOT(verifyToUseSkin(QString)));
    connect(change_skin_widget_1, SIGNAL(skinSignal(QString)), this, SLOT(verifyToUseSkin(QString)));
    connect(change_skin_widget_2, SIGNAL(skinSignal(QString)), this, SLOT(verifyToUseSkin(QString)));
    connect(change_skin_widget_3, SIGNAL(skinSignal(QString)), this, SLOT(verifyToUseSkin(QString)));
    connect(change_skin_widget_4, SIGNAL(skinSignal(QString)), this, SLOT(verifyToUseSkin(QString)));
    connect(change_skin_widget_5, SIGNAL(skinSignal(QString)), this, SLOT(verifyToUseSkin(QString)));
    connect(change_skin_widget_6, SIGNAL(skinSignal(QString)), this, SLOT(verifyToUseSkin(QString)));
    connect(change_skin_widget_7, SIGNAL(skinSignal(QString)), this, SLOT(verifyToUseSkin(QString)));

    centerLayout->addWidget(change_skin_widget_0, 0, 0);
    centerLayout->addWidget(change_skin_widget_1, 0, 1);
    centerLayout->addWidget(change_skin_widget_2, 0, 2);
    centerLayout->addWidget(change_skin_widget_3, 0, 3);
    centerLayout->addWidget(change_skin_widget_4, 1, 0);
    centerLayout->addWidget(change_skin_widget_5, 1, 1);
    centerLayout->addWidget(change_skin_widget_6, 1, 2);
    centerLayout->addWidget(change_skin_widget_7, 1, 3);

    int skin_list_count = skin_list.size();
    page_count = skin_list_count / 8;
    page_count_point = skin_list_count % 8;
    if(page_count_point > 0) {
        page_count = page_count + 1;
    }
}

void SkinsWidget::initBottomBar() {
    QSignalMapper *signal_mapper = new QSignalMapper(this);
    QList<QPushButton *> *button_list = new QList<QPushButton *>();
    for(int i=0; i<page_count; i++) {
        QPushButton *page_button = new QPushButton();
        page_button->setFixedWidth(20);
        page_button->setText(QString::number(i+1, 10));
        page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");
        page_button->setCursor(Qt::PointingHandCursor);
        connect(page_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(page_button, page_button->text());
        button_list->push_back(page_button);
    }

    first_page_button = new QPushButton();
    previous_page_button = new QPushButton();
    next_page_button = new QPushButton();
    last_page_button = new QPushButton();
    first_page_button->setFixedWidth(50);
    previous_page_button->setFixedWidth(50);
    next_page_button->setFixedWidth(50);
    last_page_button->setFixedWidth(50);
    first_page_button->setCursor(Qt::PointingHandCursor);
    previous_page_button->setCursor(Qt::PointingHandCursor);
    next_page_button->setCursor(Qt::PointingHandCursor);
    last_page_button->setCursor(Qt::PointingHandCursor);
    first_page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");
    previous_page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");
    next_page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");
    last_page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");

    first_page_button->setText(tr("首页"));
    previous_page_button->setText(tr("上一页"));
    next_page_button->setText(tr("下一页"));
    last_page_button->setText(tr("末页"));

    connect(first_page_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
    connect(previous_page_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
    connect(next_page_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
    connect(last_page_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
    signal_mapper->setMapping(first_page_button, "first");
    signal_mapper->setMapping(previous_page_button, "previous");
    signal_mapper->setMapping(next_page_button, "next");
    signal_mapper->setMapping(last_page_button, "last");
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(showSkin(QString)));

    bottomLayout = new QHBoxLayout();
    bottomLayout->addStretch();
    bottomLayout->addWidget(first_page_button, 0, Qt::AlignVCenter);
    bottomLayout->addWidget(previous_page_button, 0, Qt::AlignVCenter);
    for(int i=0; i<button_list->count(); i++) {
        QPushButton *page_button = button_list->at(i);
        bottomLayout->addWidget(page_button, 0, Qt::AlignVCenter);
    }
    bottomLayout->addWidget(next_page_button, 0, Qt::AlignVCenter);
    bottomLayout->addWidget(last_page_button, 0, Qt::AlignVCenter);
    bottomLayout->addStretch();
    bottomLayout->setSpacing(2);
    bottomLayout->setContentsMargins(0, 10, 0, 0);
}

void SkinsWidget::selectShowNumber(int left_number, int previous_total_page, int tip_index) {
    if(left_number >= 8) {
        change_skin_widget_0->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
        change_skin_widget_1->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
        change_skin_widget_2->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
        change_skin_widget_3->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
        change_skin_widget_4->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
        change_skin_widget_5->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
        change_skin_widget_6->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
        change_skin_widget_7->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
    }
//    else if(left_number == 1) {
//        change_skin_widget_0->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_1->showSkinGrid("", "", false);
//        change_skin_widget_2->showSkinGrid("", "", false);
//        change_skin_widget_3->showSkinGrid("", "", false);
//        change_skin_widget_4->showSkinGrid("", "", false);
//        change_skin_widget_5->showSkinGrid("", "", false);
//        change_skin_widget_6->showSkinGrid("", "", false);
//        change_skin_widget_7->showSkinGrid("", "", false);
//    }
//    else if(left_number == 2) {
//        change_skin_widget_0->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_1->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_2->showSkinGrid("", "", false);
//        change_skin_widget_3->showSkinGrid("", "", false);
//        change_skin_widget_4->showSkinGrid("", "", false);
//        change_skin_widget_5->showSkinGrid("", "", false);
//        change_skin_widget_6->showSkinGrid("", "", false);
//        change_skin_widget_7->showSkinGrid("", "", false);
//    }
//    else if(left_number == 3) {
//        change_skin_widget_0->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_1->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_2->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_3->showSkinGrid("", "", false);
//        change_skin_widget_4->showSkinGrid("", "", false);
//        change_skin_widget_5->showSkinGrid("", "", false);
//        change_skin_widget_6->showSkinGrid("", "", false);
//        change_skin_widget_7->showSkinGrid("", "", false);
//    }
//    else if(left_number == 4) {
//        change_skin_widget_0->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_1->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_2->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_3->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_4->showSkinGrid("", "", false);
//        change_skin_widget_5->showSkinGrid("", "", false);
//        change_skin_widget_6->showSkinGrid("", "", false);
//        change_skin_widget_7->showSkinGrid("", "", false);
//    }
//    else if(left_number == 5) {
//        change_skin_widget_0->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_1->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_2->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_3->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_4->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_5->showSkinGrid("", "", false);
//        change_skin_widget_6->showSkinGrid("", "", false);
//        change_skin_widget_7->showSkinGrid("", "", false);
//    }
//    else if(left_number == 6) {
//        change_skin_widget_0->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_1->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_2->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_3->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_4->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_5->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_6->showSkinGrid("", "", false);
//        change_skin_widget_7->showSkinGrid("", "", false);
//    }
//    else if(left_number == 7) {
//        change_skin_widget_0->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_1->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_2->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_3->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_4->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_5->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_6->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
//        change_skin_widget_7->showSkinGrid("", "", false);
//    }
}

void SkinsWidget::showSkin(QString current_skin) {
    if(current_skin == "first") {
        current_page = 1;
    }
    else if(current_skin == "previous") {
        if(current_page > 2) {
            current_page = current_page - 1;
        }
    }
    else if(current_skin == "next") {
        if(current_page < page_count) {
            current_page = current_page + 1;
        }
    }
    else if(current_skin == "last") {
        current_page = page_count;
    }
    else {
        bool ok;
        current_page = current_skin.toInt(&ok, 10);
    }

    if(current_page == 1) {
        next_page_button->show();
        last_page_button->show();
        first_page_button->hide();
        previous_page_button->hide();
    }
    else if(current_page == page_count) {
        first_page_button->show();
        previous_page_button->show();
        next_page_button->hide();
        last_page_button->hide();
    }
    else {
        first_page_button->hide();
        previous_page_button->show();
        next_page_button->show();
        last_page_button->hide();
    }

    int previous_total_page = (current_page - 1)*8;
    int tip_index = previous_total_page;
    //len=皮肤列表总数
    int len = skin_list.size();
    //left_number=当前页面为止，还剩下的皮肤总数
    int left_number = len - (current_page - 1)*8;
    this->selectShowNumber(left_number, previous_total_page, tip_index);
}

void SkinsWidget::verifyToUseSkin(QString skinName) {
    //开始更换皮肤对话框的皮肤
    this->skinName = skinName;
    is_change = true;
    update();
    //开始触发信号，使得QML开始更新皮肤，截取图片名字
    QStringList splitList = skinName.split("/");
    QString picName = splitList.at(splitList.length() - 1);
    emit skinSignalToQML(picName);
}

void SkinsWidget::paintEvent(QPaintEvent *) {
    if(!is_change) {
        //初始化皮肤对画框的皮肤
        pSettings->beginGroup("skin");
        skinName = pSettings->value("background").toString();
        skinName = QString(":/skin/image/") + skinName;
        pSettings->endGroup();
        pSettings->sync();
    }
    QPainter painter(this);
    painter.drawPixmap(rect(), QPixmap(skinName));

    QPainter painter2(this);
    QLinearGradient linear2(rect().topLeft(), rect().bottomLeft());
    linear2.setColorAt(0, Qt::white);
    linear2.setColorAt(0.5, Qt::white);
    linear2.setColorAt(1, Qt::white);
    painter2.setPen(Qt::white);
    painter2.setBrush(linear2);
    painter2.drawRect(QRect(0, 30, this->width(), this->height()-30));

    QPainter painter3(this);
    painter3.setPen(Qt::gray);
    static const QPointF points[4] = {QPointF(0, 30), QPointF(0, this->height()-1), QPointF(this->width()-1, this->height()-1), QPointF(this->width()-1, 30)};
    painter3.drawPolyline(points, 4);
}

bool SkinsWidget::eventFilter(QObject *obj, QEvent *event) {
    if(obj == close_button) {
            if(event->type() == QEvent::Enter){
                close_button->setPixmap(QPixmap(":/pixmap/image/closeBtn-hover.png"));
            }else if(event->type() == QEvent::Leave){
                close_button->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
            }else if(event->type() == QEvent::MouseButtonPress){
                close_button->setPixmap(QPixmap(":/pixmap/image/closeBtn-hover.png"));
            }else if(event->type() == QEvent::MouseButtonRelease){
                QMouseEvent *me = (QMouseEvent *)event;
                QLabel *lb = (QLabel *)obj;
                if(me->x() > 0 && me->x() < lb->width() && me->y() > 0 && me->y() < lb->height()){
                    this->close();
                }else{
                    close_button->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
                }
            } else {
                return QObject::eventFilter(obj, event);
            }
        }
        return QObject::eventFilter(obj, event);
}

void SkinsWidget::mousePressEvent( QMouseEvent * event ) {
    if(event->button() == Qt::LeftButton) {
        mouse_press = true;
    }
    move_point = event->globalPos() - pos();
}

void SkinsWidget::mouseReleaseEvent(QMouseEvent *) {
    mouse_press = false;
}

void SkinsWidget::mouseMoveEvent(QMouseEvent *event) {
    if(mouse_press) {
        QPoint move_pos = event->globalPos();
        move(move_pos - move_point);
    }
}
