#include "authdialog.h"
//#include "ui_authdialog.h"
#include <QDebug>
#include <QMouseEvent>
#include <QDeclarativeView>
#include <QApplication>
#include <QDir>
#include <QtGui/QApplication>
#include <QtDeclarative/QDeclarativeView>
#include <QtDeclarative/QDeclarativeEngine>
#include <QtDeclarative/QDeclarativeComponent>
#include <QtDeclarative/QDeclarativeContext>
#include <QtDeclarative/QDeclarativeItem>
#include <QMetaObject>
#include <QDeclarativeContext>
#include <QDesktopWidget>
#include <QGraphicsObject>
#include <QDialog>
#include <QProcess>

//AuthDialog::AuthDialog(QWidget *parent) :
//    QStackedWidget(parent)
//{
//    this->view = new QDeclarativeView(this);
//    this->view->setSource(QUrl("../qml/MyDialog.qml"));

//    this->addWidget(this->view);
//    this->layout = new QBoxLayout(QBoxLayout::TopToBottom, this->view);


//    this->view->rootContext()->setContextProperty("dialogwindow", this->view);
//    this->view->setStyleSheet("background:transparent");
//    this->setAttribute(Qt::WA_TranslucentBackground);
//    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->view->rootContext()->setContextProperty("dialogwindow", this->view);
//    QObject::connect(this->view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));

//    passwd = "";
//}

AuthDialog::AuthDialog(QWidget *parent) :
    QDialog(parent)
{
//    Qt::WindowFlags flags = Qt::Dialog;
//    flags |= Qt::WindowMinimizeButtonHint;
//    this->setWindowFlags(flags);
//    this->setAttribute(Qt::WA_TranslucentBackground);
//    this->setWindowFlags(Qt::FramelessWindowHint);
    this->view = new QDeclarativeView(this);
    this->view->setSource(QUrl("../qml/MyDialog.qml"));


    this->view->rootContext()->setContextProperty("dialogwindow", this->view);
    this->view->setStyleSheet("background:transparent");
    this->setAttribute(Qt::WA_TranslucentBackground);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->view->rootContext()->setContextProperty("dialogwindow", this->view);
    QObject::connect(this->view->engine(), SIGNAL(quit()), qApp, SLOT(quit()));

//    passwd = "";
}

AuthDialog::~AuthDialog()
{
//    delete ui;
}



void AuthDialog::on_quitBtn_clicked()
{
//    QDialog::reject();
}

void AuthDialog::on_okBtn_clicked()
{
//    QDialog::accept();
}
//void AuthDialog::mousePressEvent(QMouseEvent *event)
//{
//    if(event->button() == Qt::LeftButton) {
//        qDebug() << "mouse press event";
//    }
////    if (event->button() == Qt::LeftButton) {
////        dragPosition = event->globalPos() - frameGeometry().topLeft();
////        event->accept();
////    }
////    qDebug() << "mouse press event";
//}

//void AuthDialog::mouseMoveEvent(QMouseEvent *event)
//{
//    if (event->buttons() & Qt::LeftButton) {
////        move(event->globalPos()-dragPosition);
//        event->accept();
//        qDebug() << "mouse moving";
//    }
//    qDebug() << "mouse move event";
//}
