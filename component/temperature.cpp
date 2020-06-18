#include "temperature.h"
#include <QLabel>
#include <QDebug>

#include "../component/chartwidget.h"

Temperature::Temperature(QWidget *parent) : QWidget(parent)
{
    this->setFixedSize(700,460);
    this->setAutoFillBackground(true);

    this->setStyleSheet("QWidget{background:#ffffff;border: none;\
                        border-bottom-right-radius:0px;\
                        border-bottom-left-radius:10px}");

//    QLabel *label = new QLabel(this);
//    label->setText("temperature-------widget");
    main_layout = new QVBoxLayout(this);
    main_layout->setSpacing(20);
    main_layout->setMargin(0);
    main_layout->setContentsMargins(64,39,64,20);
//    main_layout->addWidget(label);
    InitUI();
}

Temperature::~Temperature()
{

}

void Temperature::InitUI()
{
    QWidget *top_widget = new QWidget(this);
    top_widget->setFixedSize(572,48);
    top_layout = new QHBoxLayout(top_widget);
    top_layout->setSpacing(0);
    top_layout->setMargin(0);
    top_layout->setContentsMargins(0,0,0,0);
    main_layout->addWidget(top_widget);

//    QFrame *spilterLine = new QFrame(this);
//    spilterLine->setFixedSize(572, 2);
//    spilterLine->setStyleSheet("QFrame{background:rgba(238,238,238,1);}");
//    spilterLine->setFrameShape(QFrame::HLine);
//    spilterLine->setFrameShadow(QFrame::Plain);
//    main_layout->addWidget(spilterLine);

    QWidget *bottom_widget = new QWidget(this);
//    bottom_widget->setStyleSheet("background:green;");
//    bottom_widget->setFixedSize(450,300);
    bottom_layout = new QVBoxLayout(bottom_widget);
    bottom_layout->setSpacing(0);
    bottom_layout->setMargin(0);
    bottom_layout->setContentsMargins(0,0,0,0);
    main_layout->addWidget(bottom_widget);

    InitTopUI();
    InitBottomUI();

    this->setLayout(main_layout);
}

void Temperature::InitTopUI()
{
    QFrame *frame = new QFrame();
    QHBoxLayout *h_layout = new QHBoxLayout(frame);
    h_layout->setSpacing(14);
    h_layout->setMargin(0);
    h_layout->setContentsMargins(0,0,0,0);

    QVBoxLayout *v_layout = new QVBoxLayout();
    v_layout->setSpacing(0);
    v_layout->setMargin(0);
    v_layout->setContentsMargins(0,0,0,0);

    temperature_icon = new QLabel();
    top_tip = new QLabel();
    temperature_lable = new QLabel();

    QPixmap pixmap(":/res/temperature_normal.png");
    temperature_icon->setPixmap(pixmap);
    temperature_icon->setFixedSize(pixmap.size());
    h_layout->addWidget(temperature_icon);

    QFont font;
    font.setBold(QFont::Bold);
    font.setPixelSize(18);
//    top_tip->setFont(QFont("",18,QFont::Bold));
    top_tip->setFont(font);
    top_tip->setText(tr("Normal temperature, good heat dissipation."));
    v_layout->addWidget(top_tip);

    QFont font1;
    font.setPixelSize(14);
    temperature_lable->setFont(font1);
    temperature_lable->setText("CPU: 56℃");
    v_layout->addWidget(temperature_lable);

    h_layout->addLayout(v_layout);

    top_layout->addWidget(frame,1,Qt::AlignLeft);
}

void Temperature::InitBottomUI()
{
    QHBoxLayout *layout = new QHBoxLayout();

    QFrame *spilterLine = new QFrame(this);
    spilterLine->setFixedSize(572, 2);
    spilterLine->setStyleSheet("QFrame{background:rgba(238,238,238,1);}");
    spilterLine->setFrameShape(QFrame::HLine);
    spilterLine->setFrameShadow(QFrame::Plain);
    bottom_layout->addWidget(spilterLine);


    chart = new Chart();
//    chart->setPlotArea(QRectF(0,0,300.0,200.0));
    chart->legend()->hide();
    chart->setTheme(QChart::ChartThemeBlueNcs);
    chart->setAnimationOptions(QChart::AllAnimations);
    chartview = new QChartView(chart);
    chartview->setFixedSize(460,350);
//    chartview->setStyleSheet("background:red;");
    chartview->setRenderHint(QPainter::Antialiasing);
    layout->addWidget(chartview);
    layout->addStretch(1);
    bottom_layout->addLayout(layout);


    connect(chart,SIGNAL(requestCpuTemperature()),this,SLOT(sendrequest()));
    connect(this,SIGNAL(sendTemperature(QMap<QString,QVariant>)),chart,SLOT(receiverCpuTemperature(QMap<QString,QVariant>)));
    connect(chart,SIGNAL(refreshlablesignals(qreal)),this,SLOT(refreshlable(qreal)));

}

void Temperature::onsendTemperature(QMap<QString, QVariant> tmpMap)
{
    emit this->sendTemperature(tmpMap);
}

void Temperature::sendrequest()
{
    emit this->requestTemperature();
}

void Temperature::refreshlable(qreal q)
{
    //保留小数点的后一位
    temperature_lable->setText("CPU: "+ QString::number(q,'f',1)+"℃");
    if(q >= 60)
    {
        QPixmap pixmap(":/res/temperature_anomaly.png");
        temperature_icon->setPixmap(pixmap);
        temperature_icon->setFixedSize(pixmap.size());
        temperature_icon->update();
    }
    else
    {
        QPixmap pixmap(":/res/temperature_normal.png");
        temperature_icon->setPixmap(pixmap);
        temperature_icon->setFixedSize(pixmap.size());
        temperature_icon->update();
    }
}
