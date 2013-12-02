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

#include "youker-application.h"
#include <QDeclarativeView>
#include <QDebug>
#include <QtDeclarative/QDeclarativeEngine>
#include <QMetaObject>
#include <QDeclarativeContext>
#include <QDesktopWidget>
#include <QGraphicsObject>
#include <QtDBus>


//#include <qfontdatabase.h>

IhuApplication::IhuApplication(QWidget *parent)
    : QWidget(parent), viewer(0)
{
    viewer = new QDeclarativeView;
    tray = new Tray();
    connect(tray,SIGNAL(showOrHideQmlSignal()),this,SLOT(showOrHideMainPage()));
}

IhuApplication::~IhuApplication() {
    if (viewer) {
        delete viewer;
    }
    if (tray) {
        delete tray;
    }
}
/*
 *family->
"Abyssinica SIL"
styles->
("Regular", "斜体")
family->
"AR PL UKai CN"
styles->
("Book", "斜体")
family->
"AR PL UKai HK"
styles->
("Book", "斜体")
family->
"AR PL UKai TW"
styles->
("Book", "斜体")
family->
"AR PL UKai TW MBE"
styles->
("Book", "斜体")
family->
"AR PL UMing CN"
styles->
("Light", "轻体 斜体")
family->
"AR PL UMing HK"
styles->
("Light", "轻体 斜体")
family->
"AR PL UMing TW"
styles->
("Light", "轻体 斜体")
family->
"AR PL UMing TW MBE"
styles->
("Light", "轻体 斜体")
family->
"Bitstream Charter"
styles->
("Bold Italic", "Regular", "Bold", "Italic")
family->
"Century Schoolbook L"
styles->
("Italic", "Bold Italic", "Bold", "Roman", "半粗体 斜体")
family->
"Courier 10 Pitch"
styles->
("Italic", "Regular", "Bold", "Bold Italic")
family->
"DejaVu Sans"
styles->
("Bold", "Book", "粗体 斜体", "斜体")
family->
"DejaVu Sans Mono"
styles->
("Book", "Bold", "斜体", "粗体 斜体")
family->
"DejaVu Serif"
styles->
("Bold", "Book", "粗体 斜体", "斜体")
family->
"Dingbats"
styles->
("Regular", "斜体")
family->
"gargi"
styles->
("Medium", "半粗体 斜体")
family->
"Garuda"
styles->
("BoldOblique", "Bold", "Book", "Oblique")
family->
"Kedage"
styles->
("Normal", "Bold", "斜体", "粗体 斜体")
family->
"Khmer OS"
styles->
("Regular", "斜体")
family->
"Khmer OS System"
styles->
("Regular", "斜体")
family->
"Liberation Mono"
styles->
("Bold Italic", "Bold", "Italic", "Regular")
family->
"Liberation Sans"
styles->
("Bold Italic", "Bold", "Regular", "Italic")
family->
"Liberation Sans Narrow"
styles->
("Bold Italic", "Bold", "Regular", "Italic")
family->
"Liberation Serif"
styles->
("Bold Italic", "Regular", "Italic", "Bold")
family->
"LKLUG"
styles->
("Regular", "斜体")
family->
"Lohit Bengali"
styles->
("Regular", "斜体")
family->
"Lohit Gujarati"
styles->
("Regular", "斜体")
family->
"Lohit Hindi"
styles->
("Regular", "斜体")
family->
"Lohit Punjabi"
styles->
("Regular", "斜体")
family->
"Lohit Tamil"
styles->
("Regular", "斜体")
family->
"Mallige"
styles->
("Normal", "Bold", "斜体", "粗体 斜体")
family->
"Meera"
styles->
("Regular", "斜体")
family->
"Monospace"
styles->
("意大利体", "普通", "粗体 意大利体", "粗体")
family->
"Mukti Narrow"
styles->
("Regular", "斜体")
family->
"Nimbus Mono L"
styles->
("Bold", "Bold Oblique", "Regular Oblique", "Regular")
family->
"Nimbus Roman No9 L"
styles->
("Regular", "Medium", "Regular Italic", "Medium Italic")
family->
"Nimbus Sans L"
styles->
("Bold Condensed", "Regular", "Regular Condensed Italic", "Regular Italic", "Bold Condensed Italic", "Regular Condensed", "Bold", "Bold Italic")
family->
"OpenSymbol"
styles->
("Regular", "斜体")
family->
"ori1Uni"
styles->
("Medium", "半粗体 斜体")
family->
"Padauk"
styles->
("Regular", "Bold", "斜体", "粗体 斜体")
family->
"Padauk Book"
styles->
("Bold", "Regular", "粗体 斜体", "斜体")
family->
"Pothana2000"
styles->
("Regular", "斜体")
family->
"Rachana"
styles->
("Regular", "斜体")
family->
"Rekha"
styles->
("Medium", "半粗体 斜体")
family->
"Saab"
styles->
("Regular", "斜体")
family->
"Sans Serif"
styles->
("意大利体", "普通", "粗体 意大利体", "粗体")
family->
"Serif"
styles->
("意大利体", "普通", "粗体 意大利体", "粗体")
family->
"Standard Symbols L"
styles->
("Regular", "斜体")
family->
"Symbol"
styles->
("Regular", "斜体")
family->
"Tibetan Machine Uni"
styles->
("Regular", "斜体")
family->
"Ubuntu"
styles->
("Bold Italic", "Light Italic", "Medium Italic", "Light", "Regular", "Italic", "Medium", "Bold")
family->
"Ubuntu Condensed"
styles->
("Regular", "斜体")
family->
"Ubuntu Mono"
styles->
("Italic", "Bold Italic", "Regular", "Bold")
family->
"URW Bookman L"
styles->
("Light Italic", "Demi Bold", "Light", "Demi Bold Italic")
family->
"URW Chancery L"
styles->
("Medium Italic")
family->
"URW Gothic L"
styles->
("Demi", "Demi Oblique", "Book", "Book Oblique")
family->
"URW Palladio L"
styles->
("Roman", "Bold", "Bold Italic", "Italic", "半粗体 斜体")
family->
"Vemana2000"
styles->
("Regular", "斜体")
family->
"文泉驿微米黑"
styles->
("Regular", "斜体")
family->
"文泉驿正黑"
styles->
("Regular", "半粗体 斜体")
family->
"文泉驿点阵正黑"
styles->
("Regular", "半粗体 斜体")
family->
"文泉驿等宽微米黑"
styles->
("Regular", "斜体")
family->
"文泉驿等宽正黑"
styles->
("Regular", "半粗体 斜体")
*/
void IhuApplication::showFontFamily() {
//    QFontDatabase fdb;
//    QStringList families = fdb.families();
//    for ( QStringList::Iterator f = families.begin(); f != families.end(); ++f ) {
//        //updateFamilies
//        QString family = *f;
////        qDebug() << "family->";
////        qDebug() << family;
//        //updateStyles
//        QStringList styles = fdb.styles( family );
////        qDebug() << "styles->";
////        qDebug() << styles;
//    }



//    //updateSizes
//    QList<int> sizes = fdb.pointSizes("Ubuntu", "Regular");
//    int i = 0;
//    int current = -1;
//    QStringList str_sizes;
//    int size = 11;//line744 in qfontdialog.cpp
//    for(QList<int>::const_iterator it = sizes.constBegin(); it != sizes.constEnd(); ++it) {
//        str_sizes.append(QString::number(*it));
//        if ((current == -1) && (*it >= size)) {
//            current = i;
//        }
//        ++i;
//    }
//    qDebug() << "str_sizes->";
//    qDebug() << str_sizes;//("6", "7", "8", "9", "10", "11", "12", "14", "16", "18", "20", "22", "24", "26", "28", "36", "48", "72")
////    sizeList->model()->setStringList(str_sizes);
////    if (current == -1) {
////        // we request a size bigger than the ones in the list, select the biggest one
////        current = sizeList->count() - 1;
////    }
////    sizeList->setCurrentItem(current);
////    sizeEdit->blockSignals(true);
////    sizeEdit->setText((smoothScalable ? QString::number(size) : sizeList->currentText()));
////    if (q->style()->styleHint(QStyle::SH_FontDialog_SelectAssociatedText, 0, q)
////    && sizeList->hasFocus())
////    sizeEdit->selectAll();
////    sizeEdit->blockSignals(false);
}

inline bool isRunningInstalled() {
    static bool installed = (QCoreApplication::applicationDirPath() ==
                             QDir(("/usr/bin")).canonicalPath());
    return installed;
}

inline QString getAppDirectory() {
    if (isRunningInstalled()) {
        qDebug() << QCoreApplication::applicationDirPath();
        return QString("/usr/share/youker-assistant/qml/");
    } else {
        return QString(QCoreApplication::applicationDirPath() + "/../qml/");
    }
}

void IhuApplication::showOrHideMainPage() {
    if(viewer->isHidden()) {
        viewer->show();
    }
    else {
        viewer->hide();
    }
}

void IhuApplication::setup() {
    showFontFamily();
    viewer->engine()->setBaseUrl(QUrl::fromLocalFile(getAppDirectory()));
    viewer->setSource(QUrl::fromLocalFile("main.qml"));
    viewer->rootContext()->setContextProperty("mainwindow", viewer);
    viewer->setStyleSheet("background:transparent");
    viewer->setAttribute(Qt::WA_TranslucentBackground);
    viewer->setWindowFlags(Qt::FramelessWindowHint);
    QObject::connect(viewer->engine(), SIGNAL(quit()), qApp, SLOT(quit()));
}

void IhuApplication::showQMLWidget() {
    QDesktopWidget* desktop = QApplication::desktop();
    QSize size = viewer->sizeHint();
    int width = desktop->width();
    int height = desktop->height();
    int mw = size.width();
    int mh = size.height();
    int centerW = (width/2) - (mw/2);
    int centerH = (height/2) - (mh/2);
    viewer->move(centerW, centerH);
    viewer->show();
}
