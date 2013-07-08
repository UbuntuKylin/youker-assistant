/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
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
