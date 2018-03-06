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

#include "shreddialog.h"
#include "filewipe.h"
//#include "shredmanager.h"
#include <QObject>
#include <QStringList>
#include <QCloseEvent>
#include <QBitmap>
#include <QFileDialog>
#include <QDir>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QComboBox>
#include <QDebug>
#include <QApplication>
#include <QScreen>

//ShredDialog::ShredDialog(ShredManager *plugin, QDialog *parent)
//    :QDialog(parent)
ShredDialog::ShredDialog(QWidget *parent) :
    QWidget(parent)
    , mousePressed(false)
{
    setWindowFlags(Qt::FramelessWindowHint);
//    this->setWindowFlags(Qt::Window | Qt::FramelessWindowHint | Qt::WindowMinimizeButtonHint);//Attention: Qt::WindowCloseButtonHint make showMinimized() valid
    this->setStyleSheet("QDialog{border: 1px solid white;border-radius:1px;background-color: #ffffff;}");

    this->setWindowTitle(tr("Kylin Shred Manager"));
    this->setWindowIcon(QIcon(":/model/res/plugin/shredder.png"));

    this->setFixedSize(500, 471);
//    process_plugin = plugin;

//    shredSettings = new QSettings(KYLIN_COMPANY_SETTING, KYLIN_SETTING_FILE_NAME_SETTING);
//    shredSettings->setIniCodec("UTF-8");

//    title_bar = new KylinTitleBar();
//    initTitleBar();
    title_bar = new MyTitleBar(tr("Shred Manager"), false, this);
    title_bar->setFixedSize(this->width(), TITLE_BAR_HEIGHT);

    toolkits = new Toolkits(0, this->width(), this->height());

    select_edit = new QLineEdit();
    select_edit->setStyleSheet("QLineEdit{border:1px solid #bebebe;}");
    select_edit->setFixedWidth(400);
    select_edit->setReadOnly(true);
    select_btn = new KylinEditButton(select_edit);
    shred_btn = new QPushButton();
    cacel_btn = new QPushButton();
    shred_btn->setFixedSize(91, 25);
    shred_btn->setObjectName("blackButton");
    shred_btn->setFocusPolicy(Qt::NoFocus);
    cacel_btn->setFixedSize(91, 25);
    cacel_btn->setObjectName("blackButton");
    cacel_btn->setFocusPolicy(Qt::NoFocus);

    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addStretch();
    layout1->addWidget(select_edit);
    layout1->addStretch();

    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->addStretch();
    layout2->addWidget(shred_btn);
    layout2->addWidget(cacel_btn);
    layout2->addStretch();
    layout2->setMargin(0);

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addStretch();
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addStretch();
    layout->setSpacing(10);

    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addWidget(title_bar);
    main_layout->addLayout(layout);
    main_layout->setSpacing(20);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0, 0, 0, 0);
    setLayout(main_layout);

    this->setLanguage();
    this->initConnect();

    this->moveCenter();
}

ShredDialog::~ShredDialog()
{
//    if (shredSettings != NULL)
//    {
//        shredSettings->sync();
//        delete shredSettings;
//        shredSettings = NULL;
//    }
}

void ShredDialog::setLanguage()
{
    select_edit->setText(tr("No select any file which need to be shredded"));
    shred_btn->setText(tr("Shred File"));
    cacel_btn->setText(tr("Deselect"));
}

void ShredDialog::initConnect()
{
    connect(select_btn, SIGNAL(clicked()), this, SLOT(onSelectButtonClicked()));
    connect(shred_btn, SIGNAL(clicked()), this, SLOT(onShredButtonClicked()));
    connect(cacel_btn, SIGNAL(clicked()), this, SLOT(onCacelButtonClicked()));
//    connect(title_bar, SIGNAL(showMinDialog()), this, SLOT(onMinButtonClicked()));
    connect(title_bar,SIGNAL(closeSignal()), this, SLOT(onCloseButtonClicked()));
}

void ShredDialog::onCloseButtonClicked()
{
    this->close();
}

//void ShredDialog::onMinButtonClicked()
//{
//    this->showMinimized();
////    this->hide();
//}

//QString ShredDialog::getCurrrentSkinName()
//{
//    shredSettings->beginGroup("Background");
//    QString skin = shredSettings->value("Path").toString();
//    if(skin.isEmpty()) {
//        skin = ":/background/res/skin/1.png";
//    }
//    else {
//        QStringList skinlist;
//        QString path = "/var/lib/kylin-assistant-daemon/default/";
//        QDir picdir(path);
//        picdir.setFilter(QDir::Files | QDir::Hidden | QDir::NoSymLinks);
//        picdir.setSorting(QDir::Size | QDir::Reversed);
//        QStringList filters;
//        filters << "*.jpg" << "*.png";
//        picdir.setNameFilters(filters);
//        QFileInfoList list = picdir.entryInfoList();
//        if(list.size() < 1) {
//            skinlist << ":/background/res/skin/1.png" << ":/background/res/skin/2.png" << ":/background/res/skin/3.png" << ":/background/res/skin/4.png";
//        }
//        else {
//            for (int j = 0; j < list.size(); ++j) {
//                QFileInfo fileInfo = list.at(j);
//                skinlist << path + fileInfo.fileName();
//            }
//            skinlist << ":/background/res/skin/1.png" << ":/background/res/skin/2.png" << ":/background/res/skin/3.png" << ":/background/res/skin/4.png";
//        }

//        QList<QString>::Iterator it = skinlist.begin(), itend = skinlist.end();
//        bool flag = false;
//        for(;it != itend; it++)
//        {
//            if(*it == skin) {
//                flag = true;
//                break;
//            }
//        }
//        if (flag == false) {
//            skin = skinlist.at(0);
//        }
//    }
//    shredSettings->endGroup();
//    shredSettings->sync();
//    return skin;
//}

//void ShredDialog::initTitleBar()
//{
//    QString skin = this->getCurrrentSkinName();
//    title_bar->setTitleWidth(500);
//    title_bar->setTitleName(tr("Shred Manager"));
////    title_bar->setTitleBackgound(":/background/res/skin/1.png");
//    title_bar->setTitleBackgound(skin);
//}

//void ShredDialog::resetSkin()
//{
//    QString skin = this->getCurrrentSkinName();
//    title_bar->resetBackground(skin);
//}

//void ShredDialog::onSelecteComboActivated(int index)
//{
//}

void ShredDialog::onSelectButtonClicked()
{
//    QString fileName=QFileDialog::getOpenFileName(0, tr("Select file"), QDir::homePath(), tr("All Files(*)"));

    QStringList fileNameList;
    QString fileName;
    QFileDialog* fd = new QFileDialog(this);
//    fd->setStyleSheet("QFileDialog{background-color:blue;}");
    fd->resize(500, 471);
//    fd->setFilter(tr("Allfile(*)"));
    fd->setFilter(QDir::Files | QDir::NoSymLinks | QDir::NoDotAndDotDot);
//    fd->setFilter( "Allfile(*.*);;mp3file(*.mp3);;wmafile(*.wma);;wavefile(*.wav)");
    fd->setViewMode(QFileDialog::List);//设置浏览模式，有 列表（list） 模式和 详细信息（detail）两种方式
    if (fd->exec() == QDialog::Accepted)
    {
        fileNameList = fd->selectedFiles();
        fileName = fileNameList[0];
        select_edit->setText(fileName);
    }
    else
        fd->close();
}

void ShredDialog::onShredButtonClicked()
{
    if(select_edit->text().length() == 0 || !select_edit->text().contains("/"))
    {
        toolkits->alertMSG(this->frameGeometry().topLeft().x(), this->frameGeometry().topLeft().y(), tr("Select file!"));
    }
    else
    {
        char* ch;
        QByteArray ba = select_edit->text().toUtf8();
        ch=ba.data();
        int result = do_file(ch);
        if (result == 0)
        {
            //success
            toolkits->alertMSG(this->frameGeometry().topLeft().x(), this->frameGeometry().topLeft().y(), tr("Shred successfully!"));
            select_edit->setText(tr("No select any file which need to be shredded"));
        }
        else
        {
            //failed
            toolkits->alertMSG(this->frameGeometry().topLeft().x(), this->frameGeometry().topLeft().y(), tr("Shred failed!"));
        }
    }
}

void ShredDialog::onCacelButtonClicked()
{
    select_edit->setText(tr("No select any file which need to be shredded"));
}

void ShredDialog::closeEvent(QCloseEvent *event)
{
    event->accept();
//  emit SignalClose();
}

void ShredDialog::moveCenter()
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

void ShredDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->dragPosition = event->globalPos() - frameGeometry().topLeft();
        this->mousePressed = true;
    }
    QWidget::mousePressEvent(event);
}

void ShredDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton) {
        this->mousePressed = false;
    }

    QWidget::mouseReleaseEvent(event);
}

void ShredDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (this->mousePressed) {
        move(event->globalPos() - this->dragPosition);
    }

    QWidget::mouseMoveEvent(event);
}
