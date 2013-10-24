#include "changecitydialog.h"
#include "ui_changecitydialog.h"
#include <QSettings>
#include <QMouseEvent>
#include "util.h"
ChangeCityDialog::ChangeCityDialog(QSettings *mSettings, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ChangeCityDialog)
{
    ui->setupUi(this);
    pSettings = mSettings;
    init();

    this->setWindowFlags(Qt::FramelessWindowHint);//去掉标题栏
    this->setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
    ui->btn_close->installEventFilter(this);
    ui->btn_close->setStyleSheet("border-image:url(:/pixmap/image/closeBtn.png)");
    ui->okBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/ok.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/ok-hover.png);}");
    ui->quitBtn->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/quit.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/quit-hover.png);}");
    connect(ui->okBtn, SIGNAL(clicked()),this, SLOT(writeWeatherConf()));
    connect(ui->quitBtn, SIGNAL(clicked()), this, SLOT(close()));
}

ChangeCityDialog::~ChangeCityDialog()
{
    delete ui;
}

void ChangeCityDialog::init() {
    pSettings->beginGroup("weather");
    QStringList cityList = pSettings->value("places").toStringList();
    pSettings->endGroup();
    pSettings->sync();
    ui->listWidget->clear();
    int len = cityList.size();
    for(int i=0; i<len; i++) {
        ui->listWidget->insertItem(i, cityList.at(i));
    }
    QListWidgetItem *currentitem;
    currentitem = ui->listWidget->item(0);
    ui->listWidget->setCurrentItem(currentitem);



//    QString currentStr = ui->listWidget->currentItem()->text();
//    QStringList listName = pSettings->value("weather/places").toStringList();
//    QStringList newList;
//    int size;
//    size = listName.size();
//    for(int i =0; i<size; ++i) {
//        if(listName.at(i) != currentStr) {
//            newList.append(listName.at(i));
//        }
//    }
//    if(newList.size()==0)
//    {
//      ui->delBtn->setEnabled(false);
//      ui->listWidget->clear();
//      pSettings->setValue("weather/places", newList);
//      pSettings->setValue("weather/cityId", "");
//      pSettings->sync();
//    }
//    else {
//        ui->listWidget->clear();
//        pSettings->setValue("weather/places", newList);
//        for(int j=0; j<newList.size(); ++j)
//        {
//            qDebug() << newList.at(j);
//            ui->listWidget->insertItem(j, newList.at(j));
//        }
//        QListWidgetItem *currentitem;
//        currentitem = ui->listWidget->item(0);
//        ui->listWidget->setCurrentItem(currentitem);
//        QString cityId = get_id_from_cityname(ui->listWidget->currentItem()->text());
//        pSettings->setValue("weather/cityId", cityId);
//        pSettings->sync();
//    }
}

void ChangeCityDialog::writeWeatherConf() {
    QString cityId = Util::get_id_from_cityname(ui->listWidget->currentItem()->text());
    if(cityId == "") {
        QMessageBox::warning(NULL,
                             tr("警告"),
                             tr("没有找到城市配置文件！"),
                             QMessageBox::Ok);
    }
    else {
        pSettings->setValue("weather/cityId", cityId);
        pSettings->sync();
    //    QString strValue = QString::number(spinValue, 10);
    //    pSettings->setValue("weather/rate", strValue);
    //    pSettings->sync();
        emit readyToUpdateWeather();
        this->accept();
    }
}

bool ChangeCityDialog::eventFilter(QObject *obj, QEvent *event) {
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

void ChangeCityDialog::mousePressEvent(QMouseEvent *event) {

    if (event->button() == Qt::LeftButton) {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void ChangeCityDialog::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton )
    {
        move(event->globalPos() - dragPos);
        setWindowOpacity(0.9);
    }
    event->accept();

}

void ChangeCityDialog::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton)
    {
        setWindowOpacity(1);
    }
    event->accept();
}
