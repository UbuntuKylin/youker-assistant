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
#include "kfontdialog.h"
#include "ui_kfontdialog.h"
#include <QMouseEvent>
#include <QListView>
#include <QStringListModel>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>

extern QString selectedFont;
extern QString selectedFcitxFont;
KFontDialog::KFontDialog(QSettings *mSettings, QString flag, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::KFontDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->btn_close->installEventFilter(this);
    ui->okBtn->installEventFilter(this);
    ui->quitBtn->installEventFilter(this);
    ui->btn_close->setStyleSheet("border-image:url(:/pixmap/image/closeBtn.png)");
    ui->okBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/ok.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/ok-hover.png);}");
    ui->quitBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/quit.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/quit-hover.png);}");
    ui->curFontText->setStyleSheet("color: green");

    ui->familyEdit->setReadOnly(true);
    ui->familyEdit->setFocusProxy(ui->familyList);
    ui->fontLabel->setBuddy(ui->familyList);
    ui->styleEdit->setReadOnly(true);
    ui->styleEdit->setFocusProxy(ui->styleList);
    ui->styleLabel->setBuddy(ui->styleList);
    ui->sizeEdit->setReadOnly(true);
    ui->sizeEdit->setFocusProxy(ui->sizeList);
    ui->sizeLabel->setBuddy(ui->sizeList);
    ui->sampleEdit->setSizePolicy(QSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored));
    ui->sampleEdit->setAlignment(Qt::AlignCenter);
    pSettings = mSettings;
    fontFlag = flag;
    getInitFont();//得到初始字体
    familymodel = new QStringListModel;
    stylemodel = new QStringListModel;
    sizemodel = new QStringListModel;
    initDialog();//初始化字体对话框
    connect(ui->familyList, SIGNAL(clicked(QModelIndex)), this, SLOT(updateAll(QModelIndex)));
    connect(ui->styleList, SIGNAL(clicked(QModelIndex)), this, SLOT(updateStyleandSize(QModelIndex)));
    connect(ui->sizeList, SIGNAL(clicked(QModelIndex)), this, SLOT(updateSize(QModelIndex)));
}

KFontDialog::~KFontDialog()
{
    delete ui;
}

void KFontDialog::getInitFont() {
    pSettings->beginGroup("font");
    QString fontStr;
    if(fontFlag == "font") {
        //font
        fontStr = pSettings->value("currentfont").toString();
    }
    else if(fontFlag == "desktopfont") {
        //desktopfont
        fontStr = pSettings->value("desktopfont").toString();
    }
    else if(fontFlag == "monospacefont") {
        //monospacefont
        fontStr = pSettings->value("monospacefont").toString();
    }
    else if(fontFlag == "documentfont") {
        //documentfont
        fontStr = pSettings->value("documentfont").toString();
    }
    else if(fontFlag == "titlebarfont") {
        //titlebarfont
        fontStr = pSettings->value("titlebarfont").toString();
    }
    else if(fontFlag == "fcitxfont")
    {
        fontStr = pSettings->value("fcitxfont").toString();
    }
    pSettings->endGroup();
    pSettings->sync();
    ui->curFontText->setText(fontStr);
}

void KFontDialog::initDialog() {
    //列出所有字体的名字
    QStringList familyNames = fdb.families();
    familymodel->setStringList(familyNames);
    ui->familyList->setModel(familymodel);
    QModelIndex index;
    index = familymodel->index(0);
    ui->familyList->setCurrentIndex(index);

    //列出系统对应的所有风格
    QStringList familystyles = fdb.styles(ui->familyList->currentIndex().data().toString());
    stylemodel->setStringList(familystyles);
    ui->styleList->setModel(stylemodel);
    index = stylemodel->index(0);
    ui->styleList->setCurrentIndex(index);

    //列出所有字体及其风格对应的所有大小
    QList<int> sizes = fdb.pointSizes(ui->familyList->currentIndex().data().toString(), ui->styleList->currentIndex().data().toString());
    QStringList str_sizes;
    for(QList<int>::const_iterator it = sizes.constBegin(); it != sizes.constEnd(); ++it) {
        str_sizes.append(QString::number(*it));
    }
    sizemodel->setStringList(str_sizes);
    ui->sizeList->setModel(sizemodel);
    //默认的字体大小显示为11
    bool flag = false;
    int row = -1;
    for(QStringList::Iterator m = str_sizes.begin(); m != str_sizes.end(); ++m) {
        row++;
        QString size = *m;
        if("11" == size) {//默认字体大小存在列表中
            index = sizemodel->index(row);
            ui->sizeList->setCurrentIndex(index);
            flag = true;
            break;
        }
    }
    if(flag == false) {//11不存在列表中，此时让光标定位在第一个大小上面
        index = sizemodel->index(0);
        ui->sizeList->setCurrentIndex(index);
    }
}

void KFontDialog::updateSampleFont() {
    QFont font(fdb.font(ui->familyEdit->text(), ui->styleEdit->text(), ui->sizeEdit->text().toInt()));
    if (font != ui->sampleEdit->font()) {
        ui->sampleEdit->setFont(font);
    }
}

void KFontDialog::updateAll(QModelIndex index) {
    ui->familyEdit->setText(index.data().toString());
    QModelIndex styleindex = stylemodel->index(0);

    //更新stylemodel
    QStringList familystyles = fdb.styles(ui->familyEdit->text());
    stylemodel->setStringList(familystyles);
    ui->styleList->setModel(stylemodel);
    //设置光标默认值
    ui->styleList->setCurrentIndex(styleindex);
    ui->styleEdit->setText(ui->styleList->currentIndex().data().toString());

    //列出所有字体及其风格对应的所有大小
    //更新sizemodel
    bool sizeFlag = false;
    int num = 0;
    QList<int> sizes = fdb.pointSizes(ui->familyEdit->text(), ui->styleEdit->text());
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
    ui->sizeList->setModel(sizemodel);
    QModelIndex sizeindex;
    //更新时如果大小列表中存在11,则大小的默认值设为11
    if(sizeFlag == false) {
        sizeindex = sizemodel->index(0);
        ui->sizeList->setCurrentIndex(sizeindex);
        ui->sizeEdit->setText(ui->sizeList->currentIndex().data().toString());
    }
    else {
        sizeFlag = false;
        sizeindex = sizemodel->index(num);
        ui->sizeList->setCurrentIndex(sizeindex);
        ui->sizeEdit->setText(ui->sizeList->currentIndex().data().toString());
    }
    QString curStr = ui->familyEdit->text().append(" ").append(ui->styleEdit->text().append(" ").append(ui->sizeEdit->text()));
    ui->curFontText->setText(curStr);
    ui->sampleEdit->setText("Ubuntu Kylin:做最有中国味的操作系统！");
    updateSampleFont();
}

void KFontDialog::updateStyleandSize(QModelIndex index) {
    ui->styleEdit->setText(index.data().toString());

    //列出所有字体及其风格对应的所有大小
    //更新sizemodel
    bool sizeFlag = false;
    int num = 0;
    QList<int> sizes = fdb.pointSizes(ui->familyEdit->text(), ui->styleEdit->text());
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
    ui->sizeList->setModel(sizemodel);
    //更新时如果大小列表中存在11,则大小的默认值设为11
    QModelIndex sizeindex;
    if(sizeFlag == false) {
        sizeindex = sizemodel->index(0);
        ui->sizeList->setCurrentIndex(sizeindex);
        ui->sizeEdit->setText(ui->sizeList->currentIndex().data().toString());
    }
    else {
        sizeFlag = false;
        sizeindex = sizemodel->index(num);
        ui->sizeList->setCurrentIndex(sizeindex);
        ui->sizeEdit->setText(ui->sizeList->currentIndex().data().toString());
    }

    QString curfont = ui->familyEdit->text();
    if(!curfont.isEmpty()) {
        QString curStr = ui->familyEdit->text().append(" ").append(ui->styleEdit->text().append(" ").append(ui->sizeEdit->text()));
        ui->curFontText->setText(curStr);
        updateSampleFont();
    }
}

void KFontDialog::updateSize(QModelIndex index) {
    ui->sizeEdit->setText(index.data().toString());
    QString curfont = ui->familyEdit->text();
    if(!curfont.isEmpty()) {
        QString curStr = ui->familyEdit->text().append(" ").append(ui->styleEdit->text().append(" ").append(ui->sizeEdit->text()));
        ui->curFontText->setText(curStr);
        updateSampleFont();
    }
}

void KFontDialog::on_quitBtn_clicked() {
    this->close();
}

void KFontDialog::on_okBtn_clicked() {
    if(ui->familyEdit->text().isEmpty()) {
        //提示      你还没有更换字体，请选择字体进行更换！
        QMessageBox::warning(NULL,
                             tr("Tips"),
                             tr("You haven't change the font, please choose the font!"),
                             QMessageBox::Ok);
    }
    else {
        selectedFont = ui->familyEdit->text().append(" ").append(ui->styleEdit->text().append(" ").append(ui->sizeEdit->text()));
        selectedFcitxFont = ui->familyEdit->text();
        qDebug()<<selectedFcitxFont;
        this->accept();
    }
}


bool KFontDialog::eventFilter(QObject *obj, QEvent *event) {
    if(obj == ui->btn_close) {
            if(event->type() == QEvent::Enter){
                ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn-hover.png"));
            }else if(event->type() == QEvent::Leave){
                ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
            }else if(event->type() == QEvent::MouseButtonPress){
                ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn-hover.png"));
            }else if(event->type() == QEvent::MouseButtonRelease){
                QMouseEvent *me = (QMouseEvent *)event;
                QLabel *lb = (QLabel *)obj;
                if(me->x() > 0 && me->x() < lb->width() && me->y() > 0 && me->y() < lb->height()){
                    this->close();
                }else{
                    ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
                }
            } else {
                return QObject::eventFilter(obj, event);
            }
    }
    if(obj == ui->okBtn ||obj == ui->quitBtn)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *me = (QMouseEvent *)event;
            dragPos = me->globalPos() - frameGeometry().topLeft();
        }else if(event->type() == QEvent::MouseButtonRelease)
        {
            setWindowOpacity(1);
        }
    }
    return QObject::eventFilter(obj, event);
}

void KFontDialog::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void KFontDialog::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton ) {
        move(event->globalPos() - dragPos);
        setWindowOpacity(1);//0.5
    }
    event->accept();
}

void KFontDialog::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setWindowOpacity(1);
    }
    event->accept();
}
