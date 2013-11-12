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

#include <QSettings>
#include <QDebug>
#include <QDir>
#include <QFileDialog>
#include <QMessageBox>
#include <QMouseEvent>
#include <QDir>
#include "wizardcontroller.h"
#include "ui_wizardcontroller.h"
#include <QPixmap>
#include <QBitmap>
#include <QPainter>

#include <QSettings>

#include "locationdialog.h"
WizardController::WizardController(QSettings *mSettings, QWidget *parent) :
    QWizard(parent),
    ui(new Ui::WizardController)
{
    ui->setupUi(this);

    pSettings = mSettings;

    this->setOption(QWizard::NoCancelButton);
    this->setButtonText(QWizard::BackButton,"&返回");
    this->setButtonText(QWizard::NextButton,"&继续");
    this->setButtonText(QWizard::FinishButton,"&完成");
    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
    setWizardStyle(NStyles);//此风格没有分割线

    ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
    ui->btn_close_2->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
    ui->wizardLabel->setStyleSheet("QLabel {border:1px;color:#1790c9;font-size: 14px}");
    ui->wizardLabel_2->setStyleSheet("QLabel {border:1px;color:#1790c9;font-size: 14px}");

    ui->labelCompleteSet->setStyleSheet("QLabel {border:0px;color:#2784bc;font-size: 24px}");
    ui->addBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/user-defined.png);color: #43a2db; font-size: 14px}"
                                        "QPushButton:hover{border-image:url(:/pixmap/image/user-defined-hover.png);color: #43a2db; font-size: 14px}");

    backButton = button(QWizard::BackButton);
    backButton->setStyleSheet("QPushButton {font-size: 12px}");
    nextButton = button(QWizard::NextButton);
    nextButton->setStyleSheet("QPushButton {color: #000000; font-size: 12px}");
    finishButton = button(QWizard::FinishButton);
    finishButton->setStyleSheet("QPushButton {color: #000000; font-size: 12px}");

    spinValue = 0;
    newCityName = "";
    newCityId = "";

    ui->btn_close->installEventFilter(this);
    ui->btn_close_2->installEventFilter(this);
    ui->spinBox->setRange(0, 60);
    ui->spinBox->setSingleStep(5);

    loadConf();

    connect(this,SIGNAL(currentIdChanged(int)),this,SLOT(ChangedBackGround()));
    connect(finishButton, SIGNAL(clicked()),this, SLOT(writeWeatherConf()));
    connect(ui->spinBox,SIGNAL(valueChanged(int)),this,SLOT(setSpinValue(int)));
    connect(ui->addBtn,SIGNAL(clicked()),this,SLOT(addLocation()));
    connect(ui->delBtn,SIGNAL(clicked()),this,SLOT(delLocation()));
}

WizardController::~WizardController()
{
    delete ui;
}

void WizardController::loadConf() {
    pSettings->beginGroup("weather");
    spinValue = pSettings->value("rate").toInt();
    cityList = pSettings->value("places").toStringList();
    newCityId = pSettings->value("cityId").toString();
    pSettings->endGroup();
    pSettings->sync();
    ui->spinBox->setValue(spinValue);
    ui->listWidget->clear();
    int len = cityList.size();
    if (len == 0) {
        ui->delBtn->setEnabled(false);
    }
    else {
        for(int i=0; i<len; i++) {
            ui->listWidget->insertItem(i, cityList.at(i));
        }
        QListWidgetItem *currentitem;
        currentitem = ui->listWidget->item(0);
        ui->listWidget->setCurrentItem(currentitem);
    }
}

void WizardController::setLocation(QString cityName, QString cityId) {
    ui->listWidget->insertItem(0, cityName);
    ui->delBtn->setEnabled(true);

    QListWidgetItem *currentitem;
    currentitem = ui->listWidget->item(0);
    ui->listWidget->setCurrentItem(currentitem);

    newCityName = cityName;
    newCityId = cityId;
}

void WizardController::setSpinValue(int value) {
    spinValue = value;
}

void WizardController::writeWeatherConf() {
    QString strValue = QString::number(spinValue, 10);
    pSettings->setValue("weather/rate", strValue);
    QStringList listName = pSettings->value("weather/places").toStringList();
    listName.append(newCityName);



    pSettings->setValue("weather/places", listName);
    pSettings->setValue("weather/cityId", newCityId);
    pSettings->sync();
//    emit transConfValue("refresh_rate", strValue);
}

QString WizardController::get_id_from_cityname(QString cityName) {
    QFile locationFile("/usr/lib/python2.7/dist-packages/youker-assistant-daemon/src/weather/location.txt");
    if(locationFile.exists() && locationFile.open(QFile::ReadOnly)) {
        QTextStream in(&locationFile);
        QString line;
        QString location;
        QString cityId;
        while(!in.atEnd())
        {
           line = in.readLine();
           location = line.split(':')[0];
           if (cityName == location) {
               cityId = line.split(':')[1];
               break;
           }
        }
        locationFile.close();
        return cityId;
    }
    else {
        QMessageBox::warning(NULL,
                             tr("Warning"),
                             tr("\"%1\" has been deleted or removed!").arg("location.txt"),
                             QMessageBox::Ok);
    }
}

void WizardController::addLocation() {
    LocationDialog *locationDialog = new LocationDialog();
    connect(locationDialog, SIGNAL(sendCityInfo(QString, QString)), this, SLOT(setLocation(QString, QString)));
    locationDialog->exec();
}

void WizardController::delLocation() {
    QString currentStr = ui->listWidget->currentItem()->text();
    QStringList listName = pSettings->value("weather/places").toStringList();
//    QStringList newList;
    int size;
    size = listName.size();
    for(int i =0; i<size; ++i) {
        if(listName.at(i) != currentStr) {
            newList.append(listName.at(i));
        }
    }
    if(newList.size()==0)
    {
      ui->delBtn->setEnabled(false);
    }
    ui->listWidget->clear();
    qDebug() << "aaaaaaaaa";
    qDebug() << newList;
//    pSettings->setValue("weather/places", newList);
    for(int j=0; j<newList.size(); ++j)
    {
        qDebug() << newList.at(j);
        ui->listWidget->insertItem(j, newList.at(j));
    }
    QListWidgetItem *currentitem;
    currentitem = ui->listWidget->item(0);
    ui->listWidget->setCurrentItem(currentitem);
    QString cur_text = ui->listWidget->currentItem()->text();
//    qDebug() << "111111";
//    qDebug() << cur_text;
    QString myid = get_id_from_cityname(cur_text);
//    qDebug() << "222222222";
//    qDebug() << myid;
    pSettings->setValue("weather/cityId", myid);
    pSettings->sync();
}


bool WizardController::eventFilter(QObject *obj, QEvent *event) {
    if(obj == ui->btn_close){
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
    if(obj == ui->btn_close_2){
        if(event->type() == QEvent::Enter){
            ui->btn_close_2->setPixmap(QPixmap(":/pixmap/image/closeBtn-hover.png"));
        }else if(event->type() == QEvent::Leave){
            ui->btn_close_2->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
        }else if(event->type() == QEvent::MouseButtonPress){
            ui->btn_close_2->setPixmap(QPixmap(":/pixmap/image/closeBtn-hover.png"));
        }else if(event->type() == QEvent::MouseButtonRelease){
            QMouseEvent *me = (QMouseEvent *)event;
            QLabel *lb = (QLabel *)obj;
            if(me->x() > 0 && me->x() < lb->width() && me->y() > 0 && me->y() < lb->height()){
                this->close();
            }else{
                ui->btn_close_2->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
            }
        } else {
            return QObject::eventFilter(obj, event);
        }
    }
        return QObject::eventFilter(obj, event);
}

void WizardController::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void WizardController::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton )
    {
        move(event->globalPos() - dragPos);
        setWindowOpacity(0.9);
    }
    event->accept();

}

void WizardController::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        setWindowOpacity(1);
    }
    event->accept();
}

void WizardController::ChangedBackGround() {
    if(currentId()==0) {
        this->setStyleSheet("#WizardController{border-image:url(:/pixmap/image/bg-setting01.png)}"
                            "#*WizardController{border-image:url()}");
    }
    else if(currentId()==1) {
        this->setStyleSheet("#WizardController{border-image:url(:/pixmap/image/bg-setting01.png)}"
                            "#*WizardController{border-image:url()}");
    }
    else if(currentId()==2) {
        this->setStyleSheet("#WizardController{border-image:url(:/pixmap/image/bg-setting02.png)}"
                            "#*WizardController{border-image:url()}");
    }
}
