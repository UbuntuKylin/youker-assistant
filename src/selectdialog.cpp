/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
 * Author: Kobe Lee
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

#include "selectdialog.h"
#include "ui_selectdialog.h"
#include <QDebug>
#include <QFile>
#include <QMessageBox>
#include <QMouseEvent>

//extern QPoint widgetPosition;

SelectDialog::SelectDialog(QSettings *mSettings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SelectDialog)
{
    ui->setupUi(this);
    weatherdispather = new WeatherDB;
    this->setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
    this->setWindowFlags(Qt::FramelessWindowHint);

    pSettings = mSettings;
    ui->province_combo->setFocus();

    ui->widget->setAutoFillBackground(true);
    QPalette palette;
    QPixmap img(":/pixmap/image/titlebg.png");
    palette.setBrush(QPalette::Window, img);//标题栏背景颜色
    ui->widget->setPalette(palette);
    ui->titleLabel->setStyleSheet("color: white");//设置字颜色

    ui->btn_close->installEventFilter(this);
    ui->province_combo->installEventFilter(this);
    ui->city_combo->installEventFilter(this);
    ui->county_combo->installEventFilter(this);
    ui->okBtn->installEventFilter(this);
    ui->quitBtn->installEventFilter(this);
    ui->btn_close->setStyleSheet("border-image:url(:/pixmap/image/closeBtn.png)");
    ui->okBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/button12-gray.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/button12-gray-hover.png);}");
    ui->quitBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/button12-gray.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/button12-gray-hover.png);}");
    connect(ui->quitBtn, SIGNAL(clicked()), this, SLOT(hide_select_dialog()));
    connect(ui->okBtn, SIGNAL(clicked()), this, SLOT(save_city_conf()));
    connect(ui->province_combo, SIGNAL(currentIndexChanged(int)),  this, SLOT(slotProvince()));
    connect(ui->city_combo, SIGNAL(currentIndexChanged(int)), this, SLOT(slotCity()));
    this->init_combobox_items();
    flag = false;
    selectCity = "";
    ui->tabWidget->setCurrentIndex(0);
//    ui->comboBox->setFocus();
    ui->comboBox->showPopup();
    ui->okButton->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/button12-gray.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/button12-gray-hover.png);}");
    ui->quitButton->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/button12-gray.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/button12-gray-hover.png);}");
    ui->searchBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/button12-gray.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/button12-gray-hover.png);}");
    connect(ui->comboBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(changeSelectCity(QString)));
}

SelectDialog::~SelectDialog()
{
    if (weatherdispather != NULL) {
        delete weatherdispather;
    }
    delete ui;
}

void SelectDialog::init_combobox_items() {
    ui->province_combo->addItems(weatherdispather->get_province_list_qt());
}

void SelectDialog::update_city_list() {
    QStringList db_list = weatherdispather->search_city_table_qt(ui->province_combo->currentText().replace(" ", ""));
    ui->city_combo->clear();
    ui->city_combo->clearEditText();
    ui->city_combo->addItems(db_list);
}

void SelectDialog::update_county_list() {
    QStringList db_list = weatherdispather->search_counties_qt(ui->province_combo->currentText().replace(" ", "") ,ui->city_combo->currentText().replace(" ", ""));
    ui->county_combo->clear();
    ui->county_combo->clearEditText();
    ui->county_combo->addItems(db_list);
}

void SelectDialog::slotProvince() {
    update_city_list();
}

void SelectDialog::slotCity() {
    update_county_list();
}

void SelectDialog::hide_select_dialog()
{
    this->hide();
}

void SelectDialog::showCityDialog() {
    ui->comboBox->clear();
    ui->comboBox->clearEditText();
    flag = false;
    selectCity = "";
    this->show();
}

void SelectDialog::save_city_conf()
{
    QString province = ui->province_combo->currentText().replace(" ", "");
    QString city = ui->city_combo->currentText().replace(" ", "");
    QString county = ui->county_combo->currentText().replace(" ", "");
    QString cur_id = weatherdispather->search_id_qt(province, city, county);
    QString cur_city = QString("%1,%2,%3").arg(province).arg(city).arg(county);
    QStringList lat_lon;
    lat_lon.append("NA");
    lat_lon.append("NA");
    pSettings->beginGroup("weather");
    pSettings->setValue("cityId", cur_id);
    pSettings->setValue("cityName", cur_city);
    pSettings->setValue("latLon", lat_lon);
    pSettings->endGroup();
    pSettings->sync();

    emit readyToUpdateWeatherForWizard();
    this->hide();
}

void SelectDialog::changeSelectCity(QString currentName) {
    selectCity = currentName;
}

void SelectDialog::on_searchBtn_clicked()
{
    QString yahoo_str = ui->comboBox->currentText();
    if(!yahoo_str.isEmpty()) {
        QStringList listname = weatherdispather->search_city_names_qt(yahoo_str);
        QStringList geonameidList = weatherdispather->get_geonameid_list_qt();
        QStringList latitudeList = weatherdispather->get_latitude_list_qt();
        QStringList longitudeList = weatherdispather->get_longitude_list_qt();
//        ("纽约, 纽约州, 美国", "Brooklyn, 纽约州, 美国", "Borough of Queens, 纽约州, 美国", "Manhattan, 纽约州, 美国", "奥尔巴尼, 纽约州, 美国", "Jamaica, 纽约州, 美国", "The Bronx, 纽约州, 美国", "锡拉丘兹, 纽约州, 美国", "水牛城, 纽约州, 美国", "羅徹斯特, 纽约州, 美国")
//        ("5128581", "5110302", "5133273", "5125771", "5106834", "5122520", "5110266", "5140405", "5110629", "5134086")
//        ("40.71427", "40.6501", "40.68149", "40.78343", "42.65258", "40.69149", "40.84985", "43.04812", "42.88645", "43.15478")
//        ("-74.00597", "-73.94958", "-73.83652", "-73.96625", "-73.75623", "-73.80569", "-73.86641", "-76.14742", "-78.87837", "-77.61556")
        if(!listname.isEmpty()) {
            flag = true;
            ui->comboBox->clear();
            ui->comboBox->clearEditText();
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
        else {
            //"警告:               没有找到该城市，请重新输入城市名字！
            ui->comboBox->clear();
            ui->comboBox->clearEditText();
            QMessageBox::warning(NULL,
                                 tr("Warning:"),
                                 tr("The city was not be found, please input the city name again!"),
                                 QMessageBox::Ok);
        }
    }
}

void SelectDialog::on_quitButton_clicked()
{
    this->hide();
}

void SelectDialog::on_okButton_clicked()
{
    if(flag) {
        flag = false;
        QString currentCity = ui->comboBox->currentText();
        if(!currentCity.isEmpty()) {
            if(selectCity != currentCity) {
                //警告：        请输入城市名字，点击＇查找＇按钮进行查找！
                QMessageBox::warning(NULL,
                                     tr("Warning:"),
                                     tr("Please input city name and click 'search' button to find!"),
                                     QMessageBox::Ok);
            }
            else {
                QString cityId;
                QString lat = "NA";
                QString lon = "NA";
                QString tmpId = yahooInfo[currentCity].toString();
                lat = latInfo[currentCity].toString();
                lon = lonInfo[currentCity].toString();
                QString lat_lon;
                lat_lon.append(lat);
                lat_lon.append(lon);
                cityId = weatherdispather->get_yahoo_city_id_qt(tmpId);
                if(!cityId.isEmpty()) {
                    pSettings->beginGroup("weather");
                    pSettings->setValue("cityId", cityId);
                    pSettings->setValue("cityName", currentCity);
                    pSettings->setValue("latLon", lat_lon);
                    pSettings->endGroup();
                    pSettings->sync();
                    emit readyToUpdateWeatherForWizard();
                }
            }
        }
        this->hide();
    }
    else {
        //"警告:               请输入城市名字,点击'查找'按钮进行查找！
        QMessageBox::warning(NULL,
                             tr("Warning:"),
                             tr("Please input city name and click 'search' button to find!"),
                             QMessageBox::Ok);
    }
}

bool SelectDialog::eventFilter(QObject *obj, QEvent *event) {
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
                    this->hide();
                }else{
                    ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
                }
            } else {
                return QObject::eventFilter(obj, event);
            }
    }
    if(obj==ui->province_combo ||obj==ui->city_combo || obj==ui->county_combo ||obj==ui->okBtn ||obj==ui->quitBtn || obj== ui->comboBox || obj==ui->okButton || obj==ui->quitButton || obj==ui->searchBtn)
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

void SelectDialog::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void SelectDialog::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton ) {
        move(event->globalPos() - dragPos);
        setWindowOpacity(1); //0.5
    }
    event->accept();
}

void SelectDialog::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setWindowOpacity(1);
    }
    event->accept();
}
