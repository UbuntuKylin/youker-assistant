#include "monitorwidget.h"
#include <QDebug>

Monitorwidget::Monitorwidget(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(860,460);
    this->setAutoFillBackground(true);

    this->setStyleSheet("QWidget{background:#ffffff;border: none;}");

    splitter = new QSplitter(this);
    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
    splitter->setOrientation(Qt::Horizontal);
    splitter->setChildrenCollapsible(false);
    splitter->setHandleWidth(1);

    list_widget = new QListWidget(this);
    list_widget->setFixedSize(160,this->height());
    list_widget->setFocusPolicy(Qt::NoFocus);
    list_widget->setObjectName("listview");
    list_widget->setStyleSheet("QListWidget{background: rgb(237,237,237);border-bottom-right-radius:0px;color:black;}\
                                QListWidget::item:selected{background:white;color:black;}");

    stackedwidget = new QStackedWidget(this);
    stackedwidget->setFocusPolicy(Qt::NoFocus);
    stackedwidget->setAutoFillBackground(true);

    main_layout = new QHBoxLayout(this);
    main_layout->setSpacing(0);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(0,0,0,0);
    main_layout->addWidget(splitter);

    this->setLayout(main_layout);
//    InitUI();
    connect(list_widget,SIGNAL(itemClicked(QListWidgetItem*)),this,SLOT(changewidgetpage(QListWidgetItem*)));
}

Monitorwidget::~Monitorwidget()
{

}

void Monitorwidget::InitUI()
{
//    qDebug() << Q_FUNC_INFO << __LINE__;
    string_list.clear();
    status_list.clear();

    if(m_temperature){
        string_list << tr("Temperature");
        status_list << "Temperature";
        temperature = new Temperature();
        stackedwidget->addWidget(temperature);
        stackedwidget->setCurrentWidget(temperature);
        connect(temperature,SIGNAL(requestTemperature()),this,SLOT(sendTemperaturesigle()));
        connect(this,SIGNAL(sendTemperaturedata(QMap<QString, QVariant>)),temperature,SLOT(onsendTemperature(QMap<QString, QVariant>)));
    }

    if(m_fan){
        string_list << tr("Fan Speed");
        status_list << "Fan Speed";
        fan_widget = new Fanwidget();
        stackedwidget->addWidget(fan_widget);
        connect(fan_widget,SIGNAL(Requestsignal()),this,SIGNAL(RequestFanInfoData()));
        connect(this,SIGNAL(SendFanInfoData(QMap<QString,QVariant>)),fan_widget,SLOT(RefreshInterface(QMap<QString,QVariant>)));
    }

    if(m_cpufm){
        string_list << tr("CPU FM");
        status_list << "CPU FM";
        cpu_fm = new CpuFmwidget();
        cpu_fm->set_cpu_listAndCur(governer_list,cur_governer);
        cpu_fm->InitUI();
        stackedwidget->addWidget(cpu_fm);
        connect(this,SIGNAL(onsendcpurangedata(QMap<QString,QVariant>)),cpu_fm,SLOT(getCpuRange(QMap<QString,QVariant>)));
        connect(cpu_fm,SIGNAL(setCpuGoverner(QString)),this,SIGNAL(setCpuGoverner(QString)));
        connect(this,SIGNAL(SendCPUFrequencyData(QMap<QString,QVariant>)),cpu_fm,SLOT(ProcessingCPUFrequencyData(QMap<QString,QVariant>)));
        connect(cpu_fm,SIGNAL(RequestCPUFrequencyData()),this,SIGNAL(RequestCPUFrequencyData()));
        cpu_fm->hide();
        emit this->requestcpurange();
    }
        //    qDebug() << Q_FUNC_INFO <<this->governer_list << this->cur_governer;


    for(int i = 0; i < string_list.length(); i++) {
        QListWidgetItem *item = new QListWidgetItem(string_list.at(i),list_widget);
        item->setSizeHint(QSize(160,60));
        item->setStatusTip(status_list.at(i));
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

void Monitorwidget::set_governer_list(QStringList list)
{
    this->governer_list = list;
}

void Monitorwidget::set_cur_governer(QString string)
{
    this->cur_governer = string;
}

void Monitorwidget::set_temperature(bool f)
{
    this->m_temperature = f;
}

void Monitorwidget::set_fan(bool f)
{
    this->m_fan = f;
}

void Monitorwidget::set_cpuFm(bool f)
{
    this->m_cpufm = f;
}

void Monitorwidget::RefreshCPUFMCheckStatus()
{
    cpu_fm->RefreshCheckStatus();
}

void Monitorwidget::sendTemperaturesigle()
{
    emit this->requestcpuTemperature();
}

void Monitorwidget::onsendTemperaturedata(QMap<QString, QVariant> tmpMap)
{
    emit this->sendTemperaturedata(tmpMap);
//    qDebug() << tmpMap;
}

void Monitorwidget::changewidgetpage(QListWidgetItem *item)
{
//    qDebug() << Q_FUNC_INFO << __LINE__;
    if(!item)
        return;
    QString page_Name = item->statusTip();
    if (page_Name.isEmpty() || page_Name.isNull())
        return;
     qDebug() << "Monitorwidget changeInfoPage" << page_Name;
    if(page_Name =="Temperature")
    {
        stackedwidget->setCurrentWidget(temperature);
    }
    else if(page_Name =="Fan Speed")
    {
        stackedwidget->setCurrentWidget(fan_widget);
    }
    else if(page_Name == "CPU FM")
    {
        stackedwidget->setCurrentWidget(cpu_fm);
        cpu_fm->RefreshCheckStatus();
    }
}

void Monitorwidget::sendcpurangedata(QMap<QString, QVariant> tmpMap)
{
//    qDebug() << Q_FUNC_INFO << tmpMap;
    emit this->onsendcpurangedata(tmpMap);
}
