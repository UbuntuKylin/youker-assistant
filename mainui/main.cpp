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

    MainWindow w(arch);
    w.setTranslator(&translator);
    w.display();

    return app.exec();
}
