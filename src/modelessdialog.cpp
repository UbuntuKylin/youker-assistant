#include "modelessdialog.h"

#include <QDeclarativeContext>
#include <QApplication>

ModelessDialog::ModelessDialog(QWidget *parent)
    :QDialog(parent)
//    :QStackedWidget(parent)
{
    this->setStyleSheet("background:transparent;");
    this->setWindowTitle("youker-dialog");
    this->setAutoFillBackground(false);
    this->setWindowOpacity(1);
    this->setAttribute(Qt::WA_TranslucentBackground);
//    this->setWindowFlags(Qt::FramelessWindowHint);
    this->view = new QDeclarativeView(this);
    this->view->setSource(QUrl("../qml/func/common/ModelessDialog.qml"));
//    this->view->rootContext()->setContextProperty("modelessdialog", this->view);
//    this->addWidget(this->view);
    this->setMouseTracking(true);
}

ModelessDialog::~ModelessDialog()
{
    delete this->view;
}

//void ModelessDialog::mousePressEvent(QMouseEvent *event)
//{
//    if (event->button() == Qt::LeftButton) {
//        dragPosition = event->globalPos() - frameGeometry().topLeft();
//        event->accept();
//    }
//    qDebug() << "mouse press event";
//}

//void ModelessDialog::mouseMoveEvent(QMouseEvent *event)
//{
//    if (event->buttons() & Qt::LeftButton) {
//        move(event->globalPos()-dragPosition);
//        event->accept();
//        qDebug() << "mouse moving";
//    }
//    qDebug() << "mouse move event";
//}
