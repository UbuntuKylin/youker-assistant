/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
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

#include "mainwindow.h"
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QtSingleApplication>
#include <QScreen>
#include <QDebug>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pwd.h>

#define BUFF_SIZE (512)
char filePath[BUFF_SIZE] = {0};

#define LOCKFILE "/tmp/youker-assistant-%d.pid"
#define LOCKMODE (S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH)

int make_pid_file() {
    char buf[16];
    struct flock fl;
    snprintf(filePath, BUFF_SIZE, LOCKFILE, getuid());

    int fd = open(filePath, O_RDWR|O_CREAT, LOCKMODE);
    if (fd < 0) {
        printf("Can not open %s: %s.\n", filePath, strerror(errno));
        return -1;
    }

    fl.l_type = F_WRLCK;
    fl.l_start = 0;
    fl.l_whence = SEEK_SET;
    fl.l_len = 0;

    if (fcntl(fd, F_SETLK, &fl) < 0) {
        printf("Can not lock %s: %s.\n", filePath, strerror(errno));
        close(fd);
        return -1;
    }

    ftruncate(fd, 0);
    sprintf(buf, "%d\n", getpid());
    write(fd, buf, strlen(buf));
    close(fd);
    return 0;
}

// Helper function to return display orientation as a string.
/*QString Orientation(Qt::ScreenOrientation orientation)
{
    switch (orientation) {
        case Qt::PrimaryOrientation           : return "Primary";
        case Qt::LandscapeOrientation         : return "Landscape";
        case Qt::PortraitOrientation          : return "Portrait";
        case Qt::InvertedLandscapeOrientation : return "Inverted landscape";
        case Qt::InvertedPortraitOrientation  : return "Inverted portrait";
        default                               : return "Unknown";
    }
}*/

/*int main(int argc, char *argv)
{
    QGuiApplication a(argc, &argv);

    qDebug() << "Number of screens:" << QGuiApplication::screens().size();

    qDebug() << "Primary screen:" << QGuiApplication::primaryScreen()->name();

    foreach (QScreen *screen, QGuiApplication::screens()) {
        qDebug() << "Information for screen:" << screen->name();
        qDebug() << "  Available geometry:" << screen->availableGeometry().x() << screen->availableGeometry().y() << screen->availableGeometry().width() << "x" << screen->availableGeometry().height();
        qDebug() << "  Available size:" << screen->availableSize().width() << "x" << screen->availableSize().height();
        qDebug() << "  Available virtual geometry:" << screen->availableVirtualGeometry().x() << screen->availableVirtualGeometry().y() << screen->availableVirtualGeometry().width() << "x" << screen->availableVirtualGeometry().height();
        qDebug() << "  Available virtual size:" << screen->availableVirtualSize().width() << "x" << screen->availableVirtualSize().height();
        qDebug() << "  Depth:" << screen->depth() << "bits";
        qDebug() << "  Geometry:" << screen->geometry().x() << screen->geometry().y() << screen->geometry().width() << "x" << screen->geometry().height();
        qDebug() << "  Logical DPI:" << screen->logicalDotsPerInch();
        qDebug() << "  Logical DPI X:" << screen->logicalDotsPerInchX();
        qDebug() << "  Logical DPI Y:" << screen->logicalDotsPerInchY();
        qDebug() << "  Orientation:" << Orientation(screen->orientation());
        qDebug() << "  Physical DPI:" << screen->physicalDotsPerInch();
        qDebug() << "  Physical DPI X:" << screen->physicalDotsPerInchX();
        qDebug() << "  Physical DPI Y:" << screen->physicalDotsPerInchY();
        qDebug() << "  Physical size:" << screen->physicalSize().width() << "x" << screen->physicalSize().height() << "mm";
        qDebug() << "  Primary orientation:" << Orientation(screen->primaryOrientation());
        qDebug() << "  Refresh rate:" << screen->refreshRate() << "Hz";
        qDebug() << "  Size:" << screen->size().width() << "x" << screen->size().height();
        qDebug() << "  Virtual geometry:" << screen->virtualGeometry().x() << screen->virtualGeometry().y() << screen->virtualGeometry().width() << "x" << screen->virtualGeometry().height();
        qDebug() << "  Virtual size:" << screen->virtualSize().width() << "x" << screen->virtualSize().height();
    }
}*/





int main(int argc, char *argv[])
{
//    QApplication app(argc, argv);
    //单程序运行处理
    QtSingleApplication app(argc, argv);
    if (app.isRunning())
        return 0;

    QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
    QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
    QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
    QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));

    if (make_pid_file()) {
        exit(1);
    }

    QString arch = "";

#ifdef __x86_64__
        arch = "x86_64";
#elif __i386__
        arch = "i386";
#elif __aarch64__
        arch = "aarch64";
#endif

    QString locale = QLocale::system().name();
    QTranslator translator;
    if(locale == "zh_CN" || locale == "es" || locale == "fr" || locale == "de" || locale == "ru") {//中文 西班牙语 法语 德语 俄语
        if(!translator.load("youker-assistant_" + locale + ".qm",
                            ":/qmfile/translation/"))
            qDebug() << "Load translation file："<< "youker-assistant_" + locale + ".qm" << " failed!";
        else
            app.installTranslator(&translator);
    }

    //加载Qt对话框默认的国际化
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + locale,
                      QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    app.installTranslator(&qtTranslator);

    QFile qss(":/qssfile/res/qss/youker-assistant.qss");
    qss.open(QFile::ReadOnly);
    qApp->setStyleSheet(qss.readAll());
    qss.close();

    QDesktopWidget *desktop = QApplication::desktop();
//    qDebug() << desktop->primaryScreen();//获取主屏幕的索引序号
    int sCount = desktop->screenCount();//获取当前显示器的个数
//    qDebug() << sCount;
    //如果有两个显示，则N=2，qt默认的计算机主机的index = 0，外接显示器的index = 1；
//    mdlg.setGeometry(desktop->screenGeometry(1));//QDialog 有个成员函数叫setGeometry，只需要将dialog对象的Geometry设置为index为1的显示器即可，默认为0.如果要显示的dialog的对象为mdlg，则
//    mdlg.show();

    MainWindow w(arch);
    w.setTranslator(&translator);
//    if (sCount > 1) {
//        w.setGeometry(desktop->screenGeometry(1));
//    }
    w.display(sCount);

    return app.exec();
}


/*
测试多屏（只测了横屏，没测试纵屏）： 根据当前屏幕数量n，生成n个窗口，每个窗口都占据了一个屏幕
#include "mainwindow.h"

#include <QApplication>

#include <QDesktopWidget>

#include <cstdio>

#include <QMessageBox>



typedef struct{

int screen_no;

QRect rect;

}SCREEN;

SCREEN g_screens[10];



int main(int argc, char *argv[])

{

QApplication app(argc, argv);

QDesktopWidget *desktop = QApplication::desktop();


int screen_count = desktop->screenCount();


int prim_screen = desktop->primaryScreen();

char warning[100], *idx=warning;

for(int i=0; i<screen_count ;i++ ){

g_screens[i].screen_no = prim_screen + i;

g_screens[i].rect = desktop->screenGeometry(prim_screen + i);

sprintf(idx, "screen%d w[%d], h[%d] ",i, g_screens[i].rect.width(),g_screens[i].rect.height() );

idx += strlen(idx);

}

sprintf(idx, "total width[%d] , total height[%d] \n", desktop->width(), desktop->height() );

QMessageBox::warning(NULL, "screen", warning, QMessageBox::Ok);


MainWindow wnd[5];

for(int i=0; i < screen_count; i++){

wnd[i].resize(g_screens[i].rect.width(),g_screens[i].rect.height());

if(i == 0)

wnd[i].move(0,0);

else

wnd[i].move(i* g_screens[i-1].rect.width(),0);

char str[50];

sprintf(str,"this is screen %d",i);

wnd[i].show();

}

return app.exec();

}
 * */
