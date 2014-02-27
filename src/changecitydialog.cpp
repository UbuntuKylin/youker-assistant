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
}

void ChangeCityDialog::writeWeatherConf() {
    QString name = ui->listWidget->currentItem()->text();
    QString cityId = Util::get_id_from_cityname(name);
    bool flag = false;
    if(cityId == "") {
        //从Yahoo获取对应城市的id
        pSettings->beginGroup("weather");
        QStringList cityList = pSettings->value("places").toStringList();
        QStringList idList = pSettings->value("idList").toStringList();
//        QStringList latitude = pSettings->value("latitude").toStringList();
//        QStringList longitude = pSettings->value("longitude").toStringList();
        pSettings->endGroup();
        pSettings->sync();

        if(cityList.isEmpty()) {
            //警告:     没有找到该城市！
            QMessageBox::warning(NULL,
                                 tr("Warning:"),
                                 tr("Cannot find the city!"),
                                 QMessageBox::Ok);
        }
        else {
            int j = 0;
            for (int i=0; i< cityList.length(); i++) {
                if(name == cityList[i]) {
                    flag = true;
                    break;
                }
                j += 1;
            }
            if(flag) {
                flag = false;
                pSettings->setValue("weather/cityId", idList[j]);
                pSettings->sync();
                emit readyToUpdateWeather();
                this->accept();
            }
        }
    }
    else {
        pSettings->setValue("weather/cityId", cityId);
        pSettings->sync();
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
        setWindowOpacity(1);//0.9
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
