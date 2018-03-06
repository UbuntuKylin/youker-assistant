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

#include "kylinfontdialog.h"
#include "utils.h"
#include <QApplication>
#include <QScreen>
#include <QMouseEvent>
#include <QListView>
#include <QStringListModel>
#include <QDebug>
#include <QSettings>
#include <QLabel>
#include <QPushButton>
#include <QMessageBox>
#include <QHBoxLayout>
#include <QLineEdit>
#include <QGraphicsDropShadowEffect>

KylinFontDialog::KylinFontDialog(/*QSettings *mSettings, QString flag, */QString cur_font, QString skin, QWidget *parent) :
    QDialog(parent)
{
    this->setFixedSize(600, 500);
    this->setStyleSheet("QDialog{border: 1px solid white;border-radius:1px;background-color: #ffffff;}");
    this->setWindowIcon(QIcon(":/res/kylin-assistant.png"));
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAutoFillBackground(true);

    /*title_bar = new KylinTitleBar();
    initTitleBar(skin);*/
    title_bar = new MyTitleBar(tr("Font Dialog"), false, this);
    title_bar->setFixedSize(this->width(), TITLE_BAR_HEIGHT);

    cur_tip_label = new QLabel();
    cur_font_label = new QLabel();
    font_label = new QLabel();
    style_label = new QLabel();
    size_label = new QLabel();
    font_edit = new QLineEdit();
    style_edit = new QLineEdit();
    size_edit = new QLineEdit();
    font_view = new QListView();
    style_view = new QListView();
    size_view = new QListView();
    sample_label = new QLabel();
    sample_edit = new QLineEdit();
    ok_btn = new QPushButton();
    cacel_btn = new QPushButton();
    ok_btn->setFixedSize(91, 25);
    ok_btn->setObjectName("blackButton");
    ok_btn->setFocusPolicy(Qt::NoFocus);
    cacel_btn->setFixedSize(91, 25);
    cacel_btn->setObjectName("blackButton");
    cacel_btn->setFocusPolicy(Qt::NoFocus);
    font_edit->setStyleSheet("QLineEdit{border:1px solid #bebebe;}");
    style_edit->setStyleSheet("QLineEdit{border:1px solid #bebebe;}");
    size_edit->setStyleSheet("QLineEdit{border:1px solid #bebebe;}");
    sample_edit->setStyleSheet("QLineEdit{border:1px solid #bebebe;}");

    style_label->setFixedWidth(140);
    style_edit->setFixedWidth(140);
    style_view->setFixedWidth(140);
    size_label->setFixedWidth(60);
    size_edit->setFixedWidth(60);
    size_view->setFixedWidth(60);

    font_edit->setReadOnly(true);
    font_edit->setFocusProxy(font_view);
    font_label->setBuddy(font_view);
    style_edit->setReadOnly(true);
    style_edit->setFocusProxy(style_view);
    style_label->setBuddy(style_view);
    size_edit->setReadOnly(true);
    size_edit->setFocusProxy(size_view);
    size_label->setBuddy(size_view);
    sample_edit->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored));
    sample_edit->setAlignment(Qt::AlignCenter);

    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addWidget(cur_tip_label);
    layout1->addWidget(cur_font_label);
    layout1->addStretch();
    layout1->setSpacing(5);
    layout1->setMargin(0);
    layout1->setContentsMargins(10, 0, 0, 0);

    QVBoxLayout *layout2 = new QVBoxLayout();
    layout2->addWidget(font_label);
    layout2->addWidget(font_edit);
    layout2->addWidget(font_view);

    QVBoxLayout *layout3 = new QVBoxLayout();
    layout3->addWidget(style_label);
    layout3->addWidget(style_edit);
    layout3->addWidget(style_view);

    QVBoxLayout *layout4 = new QVBoxLayout();
    layout4->addWidget(size_label);
    layout4->addWidget(size_edit);
    layout4->addWidget(size_view);

    QHBoxLayout *layout5 = new QHBoxLayout();
    layout5->addLayout(layout2);
    layout5->addLayout(layout3);
    layout5->addLayout(layout4);
    layout5->setSpacing(10);
    layout5->setMargin(0);
    layout5->setContentsMargins(10, 0, 10, 0);

    QVBoxLayout *layout6 = new QVBoxLayout();
    layout6->addWidget(cacel_btn);
    layout6->addWidget(ok_btn);

    QHBoxLayout *layout7 = new QHBoxLayout();
    layout7->addWidget(sample_edit);
//    layout7->addStretch();
    layout7->addLayout(layout6);

    QVBoxLayout *layout8 = new QVBoxLayout();
    layout8->addWidget(sample_label);
    layout8->addLayout(layout7);
    layout8->setSpacing(5);
    layout8->setMargin(0);
    layout8->setContentsMargins(10, 0, 10, 10);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(title_bar);
    main_layout->addLayout(layout1);
    main_layout->addLayout(layout5);
    main_layout->addLayout(layout8);
    main_layout->setSpacing(5);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(main_layout);
    cur_font_label->setText(cur_font);

    familymodel = new QStringListModel;
    stylemodel = new QStringListModel;
    sizemodel = new QStringListModel;

    this->initDialog();//初始化字体对话框


    //边框阴影效果
    QGraphicsDropShadowEffect *shadow_effect = new QGraphicsDropShadowEffect(this);
    shadow_effect->setBlurRadius(5);
    shadow_effect->setColor(QColor(0, 0, 0, 127));
    shadow_effect->setOffset(2, 4);
    this->setGraphicsEffect(shadow_effect);


    this->setLanguage();
    this->initConnect();
    this->moveCenter();
}

KylinFontDialog::~KylinFontDialog()
{
    if (familymodel != NULL) {
        delete familymodel;
        familymodel = NULL;
    }
    if (stylemodel != NULL) {
        delete stylemodel;
        stylemodel = NULL;
    }
    if (sizemodel != NULL) {
        delete sizemodel;
        sizemodel = NULL;
    }
    if (title_bar != NULL) {
        delete title_bar;
        title_bar = NULL;
    }
    if (cur_tip_label != NULL) {
        delete cur_tip_label;
        cur_tip_label = NULL;
    }
    if (cur_font_label != NULL) {
        delete cur_font_label;
        cur_font_label = NULL;
    }
    if (font_label != NULL) {
        delete font_label;
        font_label = NULL;
    }
    if (style_label != NULL) {
        delete style_label;
        style_label = NULL;
    }
    if (size_label != NULL) {
        delete size_label;
        size_label = NULL;
    }
    if (font_edit != NULL) {
        delete font_edit;
        font_edit = NULL;
    }
    if (style_edit != NULL) {
        delete style_edit;
        style_edit = NULL;
    }
    if (size_edit != NULL) {
        delete size_edit;
        size_edit = NULL;
    }
    if (font_view != NULL) {
        delete font_view;
        font_view = NULL;
    }
    if (style_view != NULL) {
        delete style_view;
        style_view = NULL;
    }
    if (size_view != NULL) {
        delete size_view;
        size_view = NULL;
    }
    if (sample_label != NULL) {
        delete sample_label;
        sample_label = NULL;
    }
    if (sample_edit != NULL) {
        delete sample_edit;
        sample_edit = NULL;
    }
    if (ok_btn != NULL) {
        delete ok_btn;
        ok_btn = NULL;
    }
    if (cacel_btn != NULL) {
        delete cacel_btn;
        cacel_btn = NULL;
    }
}

void KylinFontDialog::moveCenter()
{
    QPoint pos = QCursor::pos();
    QRect primaryGeometry;
    for (QScreen *screen : qApp->screens()) {
        if (screen->geometry().contains(pos)) {
            primaryGeometry = screen->geometry();
        }
    }

    if (primaryGeometry.isEmpty()) {
        primaryGeometry = qApp->primaryScreen()->geometry();
    }

    this->move(primaryGeometry.x() + (primaryGeometry.width() - this->width())/2,
               primaryGeometry.y() + (primaryGeometry.height() - this->height())/2);
}

void KylinFontDialog::setLanguage()
{
    cur_tip_label->setText(tr("Current Font") + ":");
    font_label->setText(tr("Font"));
    style_label->setText(tr("Style"));
    size_label->setText(tr("Size"));
    sample_label->setText(tr("View"));
    ok_btn->setText(tr("OK"));
    cacel_btn->setText(tr("Cancel"));
}

void KylinFontDialog::initConnect()
{
//    connect(title_bar, SIGNAL(showMinDialog()), this, SLOT(onMinButtonClicked()));
//    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCacelButtonClicked()));

    connect(title_bar, SIGNAL(closeSignal()), this, SLOT(onCacelButtonClicked()));
    connect(font_view, SIGNAL(clicked(QModelIndex)), this, SLOT(updateAll(QModelIndex)));
    connect(style_view, SIGNAL(clicked(QModelIndex)), this, SLOT(updateStyleandSize(QModelIndex)));
    connect(size_view, SIGNAL(clicked(QModelIndex)), this, SLOT(updateSize(QModelIndex)));
    connect(cacel_btn, SIGNAL(clicked()), this, SLOT(onCacelButtonClicked()));
    connect(ok_btn, SIGNAL(clicked()), this, SLOT(onOKButtonClicked()));
}

void KylinFontDialog::onCacelButtonClicked()
{
    this->close();
}

void KylinFontDialog::onOKButtonClicked() {
    if(font_edit->text().isEmpty()) {
        //提示      您还没有更换字体，请选择字体进行更换！
        QMessageBox::warning(NULL,
                             tr("Tips"),
                             tr("You haven't change the font, please choose the font!"),
                             QMessageBox::Ok);
    }
    else {
        selectedFont = font_edit->text().append(" ").append(style_edit->text().append(" ").append(size_edit->text()));
        emit this->rebackCurrentFont(selectedFont);
        this->accept();
    }
}

void KylinFontDialog::initTitleBar(QString skin)
{
//    title_bar->setTitleWidth(600);
//    title_bar->setTitleName(tr("Font Dialog"));
////    title_bar->setTitleBackgound(":/background/res/skin/1.png");
//    title_bar->setTitleBackgound(skin);
}

void KylinFontDialog::initDialog() {
    //列出所有字体的名字
    QStringList familyNames = fdb.families();
    familymodel->setStringList(familyNames);
    font_view->setModel(familymodel);
    QModelIndex index;
    index = familymodel->index(0);
    font_view->setCurrentIndex(index);

    //列出系统对应的所有风格
    QStringList familystyles = fdb.styles(font_view->currentIndex().data().toString());
    stylemodel->setStringList(familystyles);
    style_view->setModel(stylemodel);
    index = stylemodel->index(0);
    style_view->setCurrentIndex(index);

    //列出所有字体及其风格对应的所有大小
    QList<int> sizes = fdb.pointSizes(font_view->currentIndex().data().toString(), style_view->currentIndex().data().toString());
    QStringList str_sizes;
    for(QList<int>::const_iterator it = sizes.constBegin(); it != sizes.constEnd(); ++it) {
        str_sizes.append(QString::number(*it));
    }
    sizemodel->setStringList(str_sizes);
    size_view->setModel(sizemodel);
    //默认的字体大小显示为11
    bool flag = false;
    int row = -1;
    for(QStringList::Iterator m = str_sizes.begin(); m != str_sizes.end(); ++m) {
        row++;
        QString size = *m;
        if("11" == size) {//默认字体大小存在列表中
            index = sizemodel->index(row);
            size_view->setCurrentIndex(index);
            flag = true;
            break;
        }
    }
    if(flag == false) {//11不存在列表中，此时让光标定位在第一个大小上面
        index = sizemodel->index(0);
        size_view->setCurrentIndex(index);
    }
}

void KylinFontDialog::updateSampleFont() {
    QFont font(fdb.font(font_edit->text(), style_edit->text(), size_edit->text().toInt()));
    if (font != sample_edit->font()) {
        sample_edit->setFont(font);
    }
}

void KylinFontDialog::updateAll(QModelIndex index) {
    font_edit->setText(index.data().toString());
    QModelIndex styleindex = stylemodel->index(0);

    //更新stylemodel
    QStringList familystyles = fdb.styles(font_edit->text());
    stylemodel->setStringList(familystyles);
    style_view->setModel(stylemodel);
    //设置光标默认值
    style_view->setCurrentIndex(styleindex);
    style_edit->setText(style_view->currentIndex().data().toString());

    //列出所有字体及其风格对应的所有大小
    //更新sizemodel
    bool sizeFlag = false;
    int num = 0;
    QList<int> sizes = fdb.pointSizes(font_edit->text(), style_edit->text());
    QStringList str_sizes;
    int row = -1;
    for(QList<int>::const_iterator it = sizes.constBegin(); it != sizes.constEnd(); ++it) {
        row++;
        str_sizes.append(QString::number(*it));
        if(*it == 11) {
            sizeFlag = true;
            num = row;
        }
    }
    sizemodel->setStringList(str_sizes);
    size_view->setModel(sizemodel);
    QModelIndex sizeindex;
    //更新时如果大小列表中存在11,则大小的默认值设为11
    if(sizeFlag == false) {
        sizeindex = sizemodel->index(0);
        size_view->setCurrentIndex(sizeindex);
        size_edit->setText(size_view->currentIndex().data().toString());
    }
    else {
        sizeFlag = false;
        sizeindex = sizemodel->index(num);
        size_view->setCurrentIndex(sizeindex);
        size_edit->setText(size_view->currentIndex().data().toString());
    }
    QString curStr = font_edit->text().append(" ").append(style_edit->text().append(" ").append(size_edit->text()));
    cur_font_label->setText(curStr);
    sample_edit->setText("Ubuntu Kylin:做最有中国味的操作系统！");
    updateSampleFont();
}

void KylinFontDialog::updateStyleandSize(QModelIndex index) {
    style_edit->setText(index.data().toString());

    //列出所有字体及其风格对应的所有大小
    //更新sizemodel
    bool sizeFlag = false;
    int num = 0;
    QList<int> sizes = fdb.pointSizes(font_edit->text(), style_edit->text());
    QStringList str_sizes;
    int row = -1;
    for(QList<int>::const_iterator it = sizes.constBegin(); it != sizes.constEnd(); ++it) {
        row++;
        str_sizes.append(QString::number(*it));
        if(*it == 11) {
            sizeFlag = true;
            num = row;
        }
    }
    sizemodel->setStringList(str_sizes);
    size_view->setModel(sizemodel);
    //更新时如果大小列表中存在11,则大小的默认值设为11
    QModelIndex sizeindex;
    if(sizeFlag == false) {
        sizeindex = sizemodel->index(0);
        size_view->setCurrentIndex(sizeindex);
        size_edit->setText(size_view->currentIndex().data().toString());
    }
    else {
        sizeFlag = false;
        sizeindex = sizemodel->index(num);
        size_view->setCurrentIndex(sizeindex);
        size_edit->setText(size_view->currentIndex().data().toString());
    }

    QString curfont = font_edit->text();
    if(!curfont.isEmpty()) {
        QString curStr = font_edit->text().append(" ").append(style_edit->text().append(" ").append(size_edit->text()));
        cur_font_label->setText(curStr);
        updateSampleFont();
    }
}

void KylinFontDialog::updateSize(QModelIndex index) {
    size_edit->setText(index.data().toString());
    QString curfont = font_edit->text();
    if(!curfont.isEmpty()) {
        QString curStr = font_edit->text().append(" ").append(style_edit->text().append(" ").append(size_edit->text()));
        cur_font_label->setText(curStr);
        updateSampleFont();
    }
}

void KylinFontDialog::resetTitleSkin(QString skin)
{
//    title_bar->resetBackground(skin);
}

bool KylinFontDialog::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ok_btn ||obj == cacel_btn)
    {
        if(event->type() == QEvent::MouseButtonPress) {
            QMouseEvent *me = (QMouseEvent *)event;
            dragPos = me->globalPos() - frameGeometry().topLeft();
        }
        else if(event->type() == QEvent::MouseButtonRelease) {
            setWindowOpacity(1);
        }
    }
    return QObject::eventFilter(obj, event);
}

void KylinFontDialog::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void KylinFontDialog::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton ) {
        move(event->globalPos() - dragPos);
        setWindowOpacity(1);//0.5
    }
    event->accept();
}

void KylinFontDialog::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setWindowOpacity(1);
    }
    event->accept();
}
