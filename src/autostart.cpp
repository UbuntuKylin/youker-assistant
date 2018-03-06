#include "autostart.h"
#include "../component/kylinlistwidgetitem.h"
//#include "mainwindow.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QSignalMapper>
#include "../dbusproxy/youkersessiondbus.h"
#include "../component/utils.h"


AutoStart::AutoStart(QWidget *parent, SessionDispatcher *proxy)
    :QDialog(parent),
    sessionproxy(proxy)
{
    this->setFixedSize(750, 300);
    setWindowFlags(Qt::FramelessWindowHint);
    title_bar = NULL;

    scroll_widget = new TestScrollWidget(this);
    scroll_widget->setGeometry(0, 0, 750, 300);

    this->setLanguage();
    this->initConnect();
}

AutoStart::~AutoStart()
{
}

void AutoStart::initData()
{
    sessionproxy->getAutoStartAppStatus();
}


void AutoStart::readyReciveData(const QStringList &data)
{
    data_list.append(data);
}

void AutoStart::readyShowUI()
{
    QVBoxLayout *v_layout = new QVBoxLayout();
    QSignalMapper *signal_mapper = new QSignalMapper(this);
    for(int i =0; i<data_list.length(); i++)
    {
        QMap<QString,QString> tmpMap;
        QStringList tmp_list = data_list.at(i);
        for(int j=0;j<tmp_list.length();j++)
        {
            tmpMap.insert(tmp_list[j].split(":").at(0), tmp_list[j].split(":").at(1));
        }
        AutoGroup *auto_group = new AutoGroup(scroll_widget->zone);
        auto_group->initData(tmpMap);
//        qDebug() << tmpMap;
        scroll_widget->addScrollWidget(auto_group);

//        AutoGroup *auto_group = new AutoGroup();
//        auto_group->initData(tmpMap);
        connect(auto_group, SIGNAL(autoStatusChange()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(auto_group, tmpMap.value("Path"));
        v_layout->addWidget(auto_group, 0, Qt::AlignBottom);
    }
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(setCurrentItemAutoStatus(QString)));

    QVBoxLayout *layout  = new QVBoxLayout();
    layout->addWidget(title_bar);
    layout->addLayout(v_layout);
//    layout->addWidget(scroll_widget);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);
    setLayout(layout);
}

//void AutoStart::readyShowUI()
//{
////    qDebug() << data_list.length();
//    QVBoxLayout *v_layout = new QVBoxLayout();
//    QSignalMapper *signal_mapper = new QSignalMapper(this);
//    for(int i =0; i<data_list.length(); i++)
//    {
//        QMap<QString,QString> tmpMap;
//        QStringList tmp_list = data_list.at(i);
//        for(int j=0;j<tmp_list.length();j++)
//        {
//            tmpMap.insert(tmp_list[j].split(":").at(0), tmp_list[j].split(":").at(1));
//        }
////        AutoData tmp;
////        qDebug() << tmpMap;
//        AutoGroup *auto_group = new AutoGroup();
//        auto_group->initData(tmpMap);
////        auto_list.append(auto_group);
//        connect(auto_group, SIGNAL(autoStatusChange()), signal_mapper, SLOT(map()));
////        signal_mapper->setMapping(auto_group, QString::number(i, 10));
////        signal_mapper->setMapping(auto_group, auto_group->name_label->text());
//        signal_mapper->setMapping(auto_group, tmpMap.value("Path"));
//        v_layout->addWidget(auto_group, 0, Qt::AlignBottom);
//    }
//    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(setCurrentItemAutoStatus(QString)));

//    QVBoxLayout *layout  = new QVBoxLayout();
//    layout->addWidget(title_bar);
//    layout->addLayout(v_layout);
////    layout->addWidget(list_widget);
//    layout->setSpacing(0);
//    layout->setMargin(0);
//    layout->setContentsMargins(0, 0, 0, 0);
//    setLayout(layout);
////    panel->setLayout(layout);
////    scrollArea->show();
////    QHBoxLayout *main_layout = new QHBoxLayout();
////    main_layout->addWidget(scrollArea);
////    setLayout(main_layout);
//}

void AutoStart::setCurrentItemAutoStatus(QString dekstopName)
{
    int  start_pos = dekstopName.lastIndexOf("/") + 1;
    int end_pos = dekstopName.length();
    QString name = dekstopName.mid(start_pos, end_pos-start_pos);
    qDebug() << "change status->" << name;
    sessionproxy->changeAutoStartAppStatus(name);
}

void AutoStart::setLanguage()
{

}

void AutoStart::initConnect()
{
    connect(title_bar, SIGNAL(showMinDialog()), this, SLOT(onMinButtonClicked()));
    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCloseButtonClicked()));
}

void AutoStart::onCloseButtonClicked()
{
    this->close();
}

void AutoStart::onMinButtonClicked()
{
    this->hide();
}

void AutoStart::initTitleBar()
{
    title_bar->setTitleWidth(500);
    title_bar->setTitleName(tr("Boot Manager"));
    title_bar->setTitleBackgound(":/background/res/skin/1.png");
}
