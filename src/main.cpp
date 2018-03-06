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
#include "kpplication.h"
#include <QApplication>
#include <QTextCodec>
#include <QTranslator>
#include <QScreen>
#include <QDebug>
#include <QPixmap>
#include <QSplashScreen>
#include <QElapsedTimer>
#include <QDesktopWidget>

#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include <pwd.h>
#include <signal.h>

#define BUFF_SIZE (512)
char filePath[BUFF_SIZE] = {0};

#define LOCKFILE "/tmp/kylin-assistant-%d.pid"
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



bool registerSingleInstance(const QString &path)
{
    QString dbusName = QString("com.kylin.assistant-single-instance.%1").arg(path);
    auto sessionBus = QDBusConnection::sessionBus();
    if (!sessionBus.registerService(dbusName)) {
        qDebug() << "Register single dbus service failed:" << sessionBus.lastError();
        return false;
    }
    return true;
}

//void sig_int(int signal)
//{
//    QApplication::quit();
//}

int main(int argc, char *argv[])
{
    //find . | xargs -x touch
    //linguist: sudo apt-get install qt4-dev-tools

//    QApplication app(argc, argv);
    Kpplication app("kylin-assistant", argc, argv);
    app.setQuitOnLastWindowClosed(false);

    app.setOrganizationName("kylin");
    app.setApplicationName("kylin-assistant");
    app.setApplicationVersion("3.0.0");

    Kpplication *app_ins = Kpplication::instance();
    if (app_ins->isRunning()) {
        app_ins->sendMessage("Hello");
        return 1;
    }

//#ifdef QT_NO_DEBUG
//    qDebug() << "release mode";
//#else
//    qDebug() << "debug mode";
//#endif

//#ifdef QT_NO_INOTIFY
//    qDebug() << "QT_NO_INOTIFY mode";
//#else
//    qDebug() << "NO QT_NO_INOTIFY";
//#endif


    //单程序运行处理
//    QSharedMemory mem("KA");
//    if (!mem.create(1)) {
//        qDebug() << QObject::tr("kylin-assistant had already running!");
//        return 1;
//    }
    /*const QString socketPath(QString("kylin-assistant_%1").arg(getuid()));
    if (registerSingleInstance(socketPath)) {*/
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
        QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
        QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif

//        signal(SIGINT, sig_int);

    //    if (make_pid_file()) {
    //        exit(1);
    //    }

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
            if(!translator.load("kylin-assistant_" + locale + ".qm",
                                ":/qmfile/translation/"))
                qDebug() << "Load translation file："<< "kylin-assistant_" + locale + ".qm" << " failed!";
            else
                app.installTranslator(&translator);
        }

        //加载Qt对话框默认的国际化
        QTranslator qtTranslator;
        qtTranslator.load("qt_" + locale,
                          QLibraryInfo::location(QLibraryInfo::TranslationsPath));
        app.installTranslator(&qtTranslator);

        QFile qss(":/qssfile/res/qss/kylin-assistant.qss");
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

        //启动图片
        /*QPixmap pixmap("://res/skin/x.png");
        QSplashScreen screen(pixmap);
        screen.show();
        screen.showMessage("START...", Qt::AlignCenter, Qt::white);*/

        MainWindow w(arch, sCount);

    /*#if 0
        //延时
        int delayTime = 3;
        QElapsedTimer timer;
        timer.start();
        while (timer.elapsed() < (delayTime * 1000)) {
            app.processEvents();
        }
        screen.finish(&w);
    #endif*/

        w.setTranslator(&translator);
//        w.show();

    //    if (sCount > 1) {
    //        w.setGeometry(desktop->screenGeometry(1));
    //    }
    //    w.display(sCount);

        return app.exec();
    //}

    //return 0;
}
