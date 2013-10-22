#include "locationdialog.h"
#include "ui_locationdialog.h"
#include <QDebug>
#include <QFile>
#include <QMessageBox>
LocationDialog::LocationDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LocationDialog)
{
    ui->setupUi(this);
    ui->comboBox->setFocus();
}

LocationDialog::~LocationDialog()
{
    delete ui;
}

QStringList LocationDialog::list_city_names(QString inputText) {
    QFile locationFile("/usr/lib/python2.7/dist-packages/youker-assistant-daemon/src/weather/location.txt");
    if(locationFile.exists() && locationFile.open(QFile::ReadOnly)) {
        QTextStream in(&locationFile);
        QString line;
        QString keys;
        QString values;
        QStringList listCity;
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
        return listCity;
    }
    else {
        QMessageBox::warning(NULL,
                             tr("Warning"),
                             tr("\"%1\" has been deleted or removed!").arg("location.txt"),
                             QMessageBox::Ok);
    }

}

void LocationDialog::on_searchBtn_clicked()
{
    QString content = ui->comboBox->currentText().replace(" ", "");
    if(!content.isEmpty()) {
        QStringList listname = list_city_names(content);
        if(!listname.isEmpty()) {
            ui->comboBox->clear();
            ui->comboBox->addItems(listname);
        }
    }

}

void LocationDialog::on_quitBtn_clicked()
{
    this->close();
}

void LocationDialog::on_okBtn_clicked()
{
    QString currentCity = ui->comboBox->currentText();
    if(!currentCity.isEmpty()) {
        QString cityId = cityInfo[currentCity].toString();
        emit sendCityInfo(currentCity, cityId);
    }
    this->accept();
}
