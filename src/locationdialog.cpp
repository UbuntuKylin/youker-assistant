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

    sedispather = new SessionDispatcher;
    flag = false;
    yahoo = false;
    selectCity = "";
    this->setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
    this->setWindowFlags(Qt::FramelessWindowHint);
    //this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->btn_close->installEventFilter(this);
    ui->comboBox->installEventFilter(this);
    ui->searchBtn->installEventFilter(this);
    ui->okBtn->installEventFilter(this);
    ui->quitBtn->installEventFilter(this);
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
    QString yahoo_str = ui->comboBox->currentText();
    QString content = ui->comboBox->currentText().replace(" ", "");
    if(!content.isEmpty()) {
        QStringList listname = list_city_names(content);
        if(!listname.isEmpty()) {
            yahoo = false;
            flag = true;
            ui->comboBox->clear();
            ui->comboBox->addItems(listname);
            selectCity = "";
            selectCity = ui->comboBox->currentText();
        }
        else {
            listname = sedispather->search_city_names_qt(yahoo_str);
            QStringList geonameidList = sedispather->get_geonameid_list_qt();
            QStringList latitudeList = sedispather->get_latitude_list_qt();
            QStringList longitudeList = sedispather->get_longitude_list_qt();
//            @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
//            def get_longitude_list(self):
//                return self.__lonList

//            # 纬度
//            @dbus.service.method(INTERFACE, in_signature='', out_signature='as')
//            def get_latitude_list(self):
//                return self.__latList
//            qDebug() << "-----------";
//            qDebug() << listname;
//            qDebug() << geonameidList;
//            qDebug() << listname.length();
//            qDebug() << geonameidList.length();
            if(!listname.isEmpty()) {
                yahoo = true;
                flag = true;
                ui->comboBox->clear();
                ui->comboBox->addItems(listname);
                selectCity = "";
                selectCity = ui->comboBox->currentText();
                int len = listname.length();
                if(len == geonameidList.length()) {
                    for (int i=0; i < len; i++) {
//                        qDebug() << listname[i];
//                        qDebug() << geonameidList[i];
                        yahooInfo[listname[i]] = geonameidList[i];
                        latInfo[listname[i]] = latitudeList[i];
                        lonInfo[listname[i]] = longitudeList[i];
                    }
                 }
                qDebug() << yahooInfo;
            }
        }
    }

}

void LocationDialog::on_quitBtn_clicked()
{
    yahoo = false;
    this->close();
}

void LocationDialog::on_okBtn_clicked()
{
    if(flag) {
        flag = false;
        QString currentCity = ui->comboBox->currentText();
        if(!currentCity.isEmpty()) {
            if(selectCity != currentCity) {
                //警告：        请输入城市名字，点击＇查找＇按钮进行查找！
                QMessageBox::warning(NULL,
                                     tr("Warning:"),
                                     tr("Please input city name and click 'find' button to find!"),
                                     QMessageBox::Ok);
            }
            else {
                QString cityId;
                QString lat;
                QString lon;
                if(yahoo) {
                    yahoo = false;
                    QString tmpId = yahooInfo[currentCity].toString();
                    lat = latInfo[currentCity].toString();
                    lon = lonInfo[currentCity].toString();
                    cityId = sedispather->prepare_location_for_yahoo_qt(tmpId);
                    qDebug() << "--------";
                    qDebug() << currentCity;//"纽约, 纽约州, 美国"
                    qDebug() << tmpId;//"5128581"
                    qDebug() << cityId;//"USNY0996"

                }
                else {
                    cityId = cityInfo[currentCity].toString();
                }
                emit sendCityInfo(currentCity, cityId, lat, lon);
            }
        }
        this->accept();
    }
    else {
        //"警告:               请输入城市名字,点击'查找'按钮进行查找！
        QMessageBox::warning(NULL,
                             tr("Warning:"),
                             tr("Please input city name and click 'search' button to find!"),
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
    if(obj==ui->comboBox||obj==ui->searchBtn ||obj==ui->okBtn ||obj==ui->quitBtn)
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

void LocationDialog::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }

}

void LocationDialog::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton ) {
        move(event->globalPos() - dragPos);
        setWindowOpacity(1); //0.5
    }
    event->accept();
}

void LocationDialog::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setWindowOpacity(1);
    }
    event->accept();
}
