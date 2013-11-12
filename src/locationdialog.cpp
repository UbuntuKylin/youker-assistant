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

#include "locationdialog.h"
#include "ui_locationdialog.h"
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QMouseEvent>

LocationDialog::LocationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LocationDialog)
{
    ui->setupUi(this);
    ui->comboBox->setFocus();

    flag = false;
    selectCity = "";
    this->setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->btn_close->installEventFilter(this);
    ui->btn_close->setStyleSheet("border-image:url(:/pixmap/image/closeBtn.png)");
    ui->okBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/ok.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/ok-hover.png);}");
    ui->quitBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/quit.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/quit-hover.png);}");
    ui->searchBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/quit.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/quit-hover.png);}");


    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeSelectCity(QString)));
}

LocationDialog::~LocationDialog()
{
    delete ui;
}

void LocationDialog::changeSelectCity(QString currentName) {
    selectCity = currentName;
}

QStringList LocationDialog::list_city_names(QString inputText) {
    QFile locationFile("/usr/lib/python2.7/dist-packages/youker-assistant-daemon/src/weather/location.txt");
    QStringList listCity;
    if(locationFile.exists() && locationFile.open(QFile::ReadOnly)) {
        QTextStream in(&locationFile);
        QString line;
        QString keys;
        QString values;
        while(!in.atEnd())
        {
           line = in.readLine();
           if (line.contains(inputText))
           {
               keys = line.split(':')[0];
               values = line.split(':')[1];
               listCity.append(keys);
               cityInfo[keys] = values;
           }
        }
        locationFile.close();
    }
    return listCity;
}

void LocationDialog::on_searchBtn_clicked()
{
    QString content = ui->comboBox->currentText().replace(" ", "");
    if(!content.isEmpty()) {
        QStringList listname = list_city_names(content);
        if(!listname.isEmpty()) {
            flag = true;
            ui->comboBox->clear();
            ui->comboBox->addItems(listname);
            selectCity = "";
            selectCity = ui->comboBox->currentText();
        }
    }

}

void LocationDialog::on_quitBtn_clicked()
{
    this->close();
}

void LocationDialog::on_okBtn_clicked()
{
    if(flag) {
        flag = false;
        QString currentCity = ui->comboBox->currentText();
        if(!currentCity.isEmpty()) {
            if(selectCity != currentCity) {
                QMessageBox::warning(NULL,
                                     QObject::tr("警告"),
                                     QObject::tr("请输入合适的城市名字后点击查找按钮进行查找！"),
                                     QMessageBox::Ok);
            }
            else {
                QString cityId = cityInfo[currentCity].toString();
                emit sendCityInfo(currentCity, cityId);
            }
        }
        this->accept();
    }
    else {
        QMessageBox::warning(NULL,
                             QObject::tr("警告"),
                             QObject::tr("请输入合适的城市名字后点击查找按钮进行查找！"),
                             QMessageBox::Ok);
    }
}

bool LocationDialog::eventFilter(QObject *obj, QEvent *event) {
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
    return QObject::eventFilter(obj, event);


}

void LocationDialog::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }

}

void LocationDialog::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton ) {
        move(event->globalPos() - dragPos);
        setWindowOpacity(0.5);
    }
    event->accept();
}

void LocationDialog::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setWindowOpacity(1);
    }
    event->accept();
}
