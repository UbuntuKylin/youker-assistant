#include "drivewidget.h"
#include "../component/drivepagewidget.h"
#include "../info/devicemanager.h"

#include <QDebug>

Drivewidget::Drivewidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(860,460);
    this->setAutoFillBackground(true);

    this->setStyleSheet("QWidget{background:#ffffff;border: none;\
                        border-bottom-right-radius:10px;\
                        border-bottom-left-radius:10px}");

    splitter = new QSplitter(this);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->setOrientation(Qt::Horizontal);
    splitter->setHandleWidth(1);

    list_widget = new QListWidget(this);
    list_widget->setFixedSize(160,this->height());
    list_widget->setFocusPolicy(Qt::NoFocus);
    list_widget->setObjectName("listview");
    list_widget->setStyleSheet("QListWidget{background: rgb(237,237,237);\
                               border-bottom-right-radius:0px}\
                               QListWidget::item:selected{background:white;color:black;}");

    stackedwidget = new QStackedWidget(this);
    stackedwidget->setFocusPolicy(Qt::NoFocus);
    stackedwidget->setAutoFillBackground(true);

    main_layout = new QHBoxLayout(this);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0,0,0,0);
    main_layout->addWidget(splitter);

//    QLabel *lable = new QLabel();
//    lable->setText("---Drive widget---");
//    main_layout->addWidget(lable);
//    main_layout = new QHBoxLayout(this);
//    main_layout->setSpacing(0);
//    main_layout->setMargin(0);
//    main_layout->setContentsMargins(0,0,0,0);

    InitWidgetUI();
    this->setLayout(main_layout);

    connect(list_widget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(changewidgetpage(QListWidgetItem*)));
}

Drivewidget::~Drivewidget()
{

}

void Drivewidget::InitWidgetUI()
{
    string_list.clear();

    string_list << tr("All Drivers");;
    all_drives = new DrivePageWidget();
//    QMap<QString, QVariant> map = this->getDriveInfo()
    all_drives->InitPageUI(this->getDriveInfo());
    stackedwidget->addWidget(all_drives);
    stackedwidget->setCurrentWidget(all_drives);

//    string_list << tr("Drive Backup");
//    drive_backup = new DrivePageWidget();
//    stackedwidget->addWidget(drive_backup);

//    string_list << tr("Drive Reduction");
//    drive_reduction = new DrivePageWidget();
//    stackedwidget->addWidget(drive_reduction);

//    string_list << tr("Driver Uninstallation");
//    driver_uninstallation = new DrivePageWidget();
//    stackedwidget->addWidget(driver_uninstallation);

    for(int i = 0; i < string_list.length(); i++) {
        QListWidgetItem *item = new QListWidgetItem(string_list.at(i),list_widget);
        item->setSizeHint(QSize(160,60));
        item->setStatusTip(QString::number(i,10));
        item->setTextAlignment(Qt::AlignVCenter|Qt::AlignHCenter);
    }

    list_widget->setCurrentRow(0);

    QFrame *frame = new QFrame();
    QVBoxLayout *right_layout = new QVBoxLayout(frame);

    right_layout->addWidget(stackedwidget);
    right_layout->setSpacing(0);
    right_layout->setMargin(0);
    right_layout->setContentsMargins(0,0,0,0);
    frame->setLayout(right_layout);
    splitter->addWidget(list_widget);
    splitter->addWidget(frame);
}

QMap<QString, QVariant> Drivewidget::getDriveInfo()
{
    QMap<QString, QVariant> driver_info_map;
    DeviceManager manager;
    QStringList list = manager.getDeviceMsg();
//    qDebug() << list;
    for (int i=0 ; i < list.length() ; i++) {
        QStringList splitlist = list.at(i).split(";");
        if(splitlist.length() == 1) {
            QStringList name = splitlist.at(0).split(":");
            driver_info_map.insert(name.at(0).trimmed(), name.at(1));
        }
        else if(splitlist.length() == 2) {
            QStringList name1 = splitlist.at(0).split(":");
            QStringList name2 = splitlist.at(1).split(":");
            driver_info_map.insert(name1.at(0).trimmed(), name1.at(1));
            driver_info_map.insert(name2.at(0).trimmed(), name2.at(1));
        }
        else if(splitlist.length() == 3) {
            QStringList name3 = splitlist[0].split(":");
            QStringList name4 = splitlist[1].split(":");
            QStringList name5 = splitlist[2].split(":");
            driver_info_map.insert(name3.at(0).trimmed(), name3.at(1));
            driver_info_map.insert(name4.at(0).trimmed(), name4.at(1));
            driver_info_map.insert(name5.at(0).trimmed(), name5.at(1));
        }
    }
    return driver_info_map;
}

void Drivewidget::changewidgetpage(QListWidgetItem *item)
{
    qDebug() << Q_FUNC_INFO <<__LINE__;
    if(!item)
        return;
    QString page_Name = item->statusTip();
    if (page_Name.isEmpty() || page_Name.isNull())
        return;
    qDebug() << "InfoWidget changeInfoPage" << page_Name;
    if(page_Name =="0")
    {
        stackedwidget->setCurrentWidget(all_drives);
    }
    else if(page_Name =="1")
    {
        stackedwidget->setCurrentWidget(drive_backup);
    }
    else if(page_Name == "2")
    {
        stackedwidget->setCurrentWidget(drive_reduction);
    }
    else if(page_Name == "3")
    {
        stackedwidget->setCurrentWidget(driver_uninstallation);
    }
}
