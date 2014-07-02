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
//    this->setAttribute(Qt::WA_TranslucentBackground);


    ui->widget->setAutoFillBackground(true);
    QPalette palette;
    QPixmap img(":/pixmap/image/titlebg.png");
    palette.setBrush(QPalette::Window, img);//标题栏背景颜色
    ui->widget->setPalette(palette);
    //http://www.atool.org/colorpicker.php
    ui->widget_2->setAutoFillBackground(true);
    palette.setColor(QPalette::Background, QColor(228,242,252));//#e4f2fc
    ui->widget_2->setPalette(palette);

    ui->btn_close->installEventFilter(this);
    ui->comboBox->installEventFilter(this);
    ui->searchBtn->installEventFilter(this);
    ui->okBtn->installEventFilter(this);
    ui->quitBtn->installEventFilter(this);
    ui->btn_close->setStyleSheet("border-image:url(:/pixmap/image/closeBtn.png)");
    ui->okBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/button12-gray.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/button12-gray-hover.png);}");
    ui->quitBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/button12-gray.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/button12-gray-hover.png);}");
    ui->searchBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/button12-gray.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/button12-gray-hover.png);}");


    //------------------
//    this->loadgif = new QMovie("/home/saucy/work/youker-assistant/src/image/loading.gif");
//    ui->loadingDiv->setPixmap(QPixmap("/home/saucy/work/youker-assistant/src/image/div.png"));
//    ui->loadingText->setStyleSheet("QLabel{background-color:white;}");
    ui->loadingDiv->hide();
    ui->loadingText->hide();
//    ui->loading->setMovie(this->loadgif);
    ui->loading->hide();
    //--------------------


    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeSelectCity(QString)));
}

LocationDialog::~LocationDialog()
{
    if (sedispather != NULL) {
        delete sedispather;
    }
    delete ui;
}

//void LocationDialog::startLoading(const QString &loadingText){
//    ui->loadingDiv->setGeometry(0,0,this->width() - 2,this->height() - 30);
//    ui->loadingDiv->show();
//    ui->loading->setGeometry(this->width() / 2 - 25, 0, this->width(), this->height() - 60);
//    this->loadgif->start();
//    ui->loading->show();
//    ui->loadingText->setGeometry(ui->loading->x() + 25 - 150,ui->loading->y() + 120, 300, 20);
//    ui->loadingText->setText(loadingText);
//    ui->loadingText->show();
//}

//void LocationDialog::stopLoading(){
//    ui->loading->setGeometry(0,0,1,1);
//    ui->loadingDiv->setGeometry(0,0,1,1);
//    ui->loadingText->setGeometry(0,0,1,1);
//    ui->loadingText->setText("");
//    this->loadgif->stop();
//    ui->loading->hide();
//    ui->loadingDiv->hide();
//    ui->loadingText->hide();
//}

void LocationDialog::changeSelectCity(QString currentName) {
    selectCity = currentName;
}

QStringList LocationDialog::list_city_names(QString inputText) {
    QFile locationFile("/usr/lib/python2.7/dist-packages/youker-assistant-daemon/src/weather/locations.txt");
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
//            this->startLoading("正在获取城市列表....");
            listname = sedispather->search_city_names_qt(yahoo_str);
            QStringList geonameidList = sedispather->get_geonameid_list_qt();
            QStringList latitudeList = sedispather->get_latitude_list_qt();
            QStringList longitudeList = sedispather->get_longitude_list_qt();
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
                        yahooInfo[listname[i]] = geonameidList[i];
                        latInfo[listname[i]] = latitudeList[i];
                        lonInfo[listname[i]] = longitudeList[i];
                    }
                 }
            }
//            this->stopLoading();
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
                QString lat = "NA";
                QString lon = "NA";
                if(yahoo) {
                    yahoo = false;
                    QString tmpId = yahooInfo[currentCity].toString();
                    lat = latInfo[currentCity].toString();
                    lon = lonInfo[currentCity].toString();
                    cityId = sedispather->get_yahoo_city_id_qt(tmpId);
                }
                else {
                    cityId = cityInfo[currentCity].toString();
                }
                if(!cityId.isEmpty()) {
                    emit sendCityInfo(currentCity, cityId, lat, lon);
                }
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
                ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn_hover.png"));
            }else if(event->type() == QEvent::Leave){
                ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
            }else if(event->type() == QEvent::MouseButtonPress){
                ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn_hover.png"));
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
