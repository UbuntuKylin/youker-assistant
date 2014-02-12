/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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
    this->setWindowOpacity(1.0);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);

//    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Dialog);
//    this->setAttribute(Qt::WA_TranslucentBackground);

    pSettings = mSettings;
    skinName = QString("");

    mouse_press = false;
    is_change = false;
    current_page = 1;
    //皮肤 1   皮肤 2
    tip_list<<tr("skin 1")<<tr("skin 2")<<tr("skin 3")<<tr("skin 4")<<tr("skin 5")<<
           tr("skin 6")<<tr("skin 7")<<tr("skin 8")<<tr("skin 9")<<tr("skin 10")<<
           tr("skin 11")<<tr("skin 12")<<tr("skin 13")<<tr("skin 14")<<tr("skin 15")<<
           tr("skin 16")<<tr("skin 17")<<tr("skin 18")<<tr("skin 19")<<tr("skin 20") <<
           tr("skin 21")<<tr("skin 22")<<tr("skin 23")<<tr("skin 24");
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

    this->resize(620, 445);
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
    title_label->setText(tr("Youker Skin Center"));//优客皮肤中心
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
        ":/skin/image/5"<<":/skin/image/6"<<":/skin/image/7"<<":/skin/image/8"<<":/skin/img/skin/9"<<
        ":/skin/image/10"<<":/skin/image/11"<<":/skin/image/12"<<":/skin/image/13"<<":/skin/image/14"<<
        ":/skin/image/15"<<":/skin/image/16"<<":/skin/image/17"<<":/skin/image/18"<<":/skin/image/19"<<
        ":/skin/image/20"<<":/skin/image/21"<<":/skin/image/22"<<":/skin/image/23";
    centerLayout = new QGridLayout();
    centerLayout->setSpacing(5);
    centerLayout->setContentsMargins(5, 35, 5, 0);
    for(int i=0; i<8; i++)
    {
        SkinGrid *change_skin_widget = new SkinGrid();
        change_skin_list.append(change_skin_widget);
        connect(change_skin_widget, SIGNAL(skinSignal(QString)), this, SLOT(verifyToUseSkin(QString)));
        centerLayout->addWidget(change_skin_widget, i/4, i%4);
    }
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
    first_page_button->setFixedWidth(60);
    previous_page_button->setFixedWidth(60);
    next_page_button->setFixedWidth(60);
    last_page_button->setFixedWidth(60);
    first_page_button->setCursor(Qt::PointingHandCursor);
    previous_page_button->setCursor(Qt::PointingHandCursor);
    next_page_button->setCursor(Qt::PointingHandCursor);
    last_page_button->setCursor(Qt::PointingHandCursor);
    first_page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");
    previous_page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");
    next_page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");
    last_page_button->setStyleSheet("color:rgb(0, 120, 230); background:transparent;");

    first_page_button->setText(tr("Home"));//首页
    previous_page_button->setText(tr("Previous"));//上一页
    next_page_button->setText(tr("Next"));//下一页
    last_page_button->setText(tr("Last"));//末页

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
    for(int i=0; i<change_skin_list.count(); i++)
    {
        change_skin_list.at(i)->showSkinGrid(":/skin/image/"+ QString::number(previous_total_page++, 10), tip_list.at(tip_index++));
    }
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

//void SkinsWidget::resizeEvent(QResizeEvent *event) {
//    wheel=QImage(event->size(),QImage::Format_ARGB32_Premultiplied);
//    wheel.fill(palette().background().color());
//    update();
//}

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
                    this->hide();
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
