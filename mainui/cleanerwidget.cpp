#include "cleanerwidget.h"
#include <QVBoxLayout>
#include <QDebug>
#include "../component/utils.h"
//#include "mainwindow.h"
#include "../dbusproxy/youkersessiondbus.h"
//#include "../dbusproxy/youkersystemdbus.h"

CleanerWidget::CleanerWidget(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(900, 403);
    this->setWindowFlags(Qt::FramelessWindowHint | Qt::Widget);
    //set white background color
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    this->setPalette(palette);

    statked_widget = new QStackedWidget(this);
    p_mainwindow = NULL;
    systemProxy = NULL;
    sessionProxy = NULL;
    main_widget = NULL;
    detail_widget = NULL;


    kthread.setCleanerWidget(this);
}

CleanerWidget::~CleanerWidget()
{

}

void CleanerWidget::initUI()
{
    main_widget = new CleanerMainWidget(this, p_mainwindow);
    detail_widget = new CleanerDetailWidget();
    connect(sessionProxy, SIGNAL(tellCleanerDetailData(QStringList)), detail_widget, SLOT(showReciveData(QStringList)));
    statked_widget->addWidget(main_widget);
    statked_widget->addWidget(detail_widget);
    QVBoxLayout *layout1 = new QVBoxLayout();
    layout1->addWidget(statked_widget);
    layout1->setSpacing(0);
    layout1->setMargin(0);
    layout1->setContentsMargins(0, 0, 0, 0);

    setLayout(layout1);
}

void CleanerWidget::displayDetailPage()
{
    statked_widget->setCurrentIndex(1);
}

void CleanerWidget::displayMainPage()
{
    statked_widget->setCurrentIndex(0);
}
