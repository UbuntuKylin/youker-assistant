#include "autostartwidget.h"
#include "ui_autostartwidget.h"
#include <QDebug>
#include <QVBoxLayout>
#include <QSignalMapper>
#include "../dbusproxy/youkersessiondbus.h"
#include "../component/utils.h"

AutoStartWidget::AutoStartWidget(QWidget *parent, SessionDispatcher *proxy) :
    QWidget(parent),sessionproxy(proxy),
    ui(new Ui::AutoStartWidget)
{
    ui->setupUi(this);
    this->setFixedSize(560, 398);
    setWindowFlags(Qt::FramelessWindowHint);
    tip_label = new QLabel();
    num_label = new QLabel();
    name_label = new QLabel();
    status_label = new QLabel();

    ui->widget_1->setAutoFillBackground(true);
    ui->widget_2->setAutoFillBackground(true);
    QPalette palette;
    palette.setColor(QPalette::Background, QColor(233,238,241));//#e9eef1
    ui->widget_1->setPalette(palette);
    palette.setColor(QPalette::Background, QColor(255,255,255));//#ffffff
    ui->widget_2->setPalette(palette);

    tip_label->setText(tr("AutoStart Items:"));
    num_label->setText(tr("5"));
    name_label->setText(tr("App"));
    status_label->setText(tr("Status"));

    QHBoxLayout *tip_layout = new QHBoxLayout();
    tip_layout->addWidget(tip_label);
    tip_layout->addWidget(num_label);
    tip_layout->addStretch();
    tip_layout->setSpacing(0);
    tip_layout->setMargin(0);
    tip_layout->setContentsMargins(20, 0, 0, 0);
    ui->widget_1->setLayout(tip_layout);

    QHBoxLayout *status_layout = new QHBoxLayout();
    status_layout->addWidget(name_label);
    status_layout->addStretch();
    status_layout->addWidget(status_label);
    status_layout->setSpacing(0);
    status_layout->setMargin(0);
    status_layout->setContentsMargins(20, 0, 20, 0);
    ui->widget_2->setLayout(status_layout);

    title_bar = new KylinTitleBar(this);
    title_bar->move(0,0);
    title_bar->show();
    initTitleBar();
    ui->scrollArea->setFixedSize(560,302);
    this->setLanguage();
    this->initConnect();
}

AutoStartWidget::~AutoStartWidget()
{
    delete ui;
}

void AutoStartWidget::initData()
{
    sessionproxy->getAutoStartAppStatus();
}


void AutoStartWidget::readyReciveData(const QStringList &data)
{
    data_list.append(data);
}

void AutoStartWidget::readyShowUI()
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
        AutoGroup *auto_group = new AutoGroup(ui->scrollAreaWidgetContents);
        auto_group->initData(tmpMap);
        connect(auto_group, SIGNAL(autoStatusChange()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(auto_group, tmpMap.value("Path"));
        v_layout->addWidget(auto_group, 0, Qt::AlignBottom);
    }
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(setCurrentItemAutoStatus(QString)));

    QVBoxLayout *layout  = new QVBoxLayout();
//    layout->addWidget(title_bar);
    layout->addLayout(v_layout);
//    layout->addWidget(scroll_widget);
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->setContentsMargins(10, 0, 10, 10);
    ui->scrollAreaWidgetContents->setLayout(layout);
}

void AutoStartWidget::setCurrentItemAutoStatus(QString dekstopName)
{
    int  start_pos = dekstopName.lastIndexOf("/") + 1;
    int end_pos = dekstopName.length();
    QString name = dekstopName.mid(start_pos, end_pos-start_pos);
    qDebug() << "change status->" << name;
//    sessionproxy->changeAutoStartAppStatus(name);
}

void AutoStartWidget::setLanguage()
{

}

void AutoStartWidget::initConnect()
{
//    connect(title_bar, SIGNAL(showMinDialog()), this, SLOT(onMinButtonClicked()));
    connect(title_bar,SIGNAL(closeDialog()), this, SLOT(onCloseButtonClicked()));
}

void AutoStartWidget::initTitleBar()
{
    title_bar->setTitleWidth(560);
    title_bar->setTitleName(tr("Auto Start"));
    title_bar->setTitleBackgound(":/background/res/skin/1.png");
}

void AutoStartWidget::onCloseButtonClicked()
{
    this->close();
}

//void AutoStartWidget::onMinButtonClicked()
//{
//    this->hide();
//}
