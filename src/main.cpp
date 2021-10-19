/*
 * Copyright (C) 2021 KylinSoft Co., Ltd.
 *
 * Authors:
 *  Yang Min yangmin@kylinos.cn
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
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
#include <QProcess>
#include <QTranslator>
#include <ukui-log4qt.h>
#include <KWindowEffects>

#include "qtsingleapplication/qtsingleapplication.h"
#include "xatom-helper.h"
#include "utils.h"

#define CHANGELOG_PATH "/usr/share/doc/youker-assistant/changelog.Debian.gz"

static QString getAppVersion(){
    QProcess process;
    process.start(QString("dpkg-parsechangelog -l %1 --show-field Version").arg(CHANGELOG_PATH));
    process.waitForFinished();
    QByteArray result = process.readAllStandardOutput();
    result = result.left(result.length()-1);
    return result;
}

int main(int argc, char *argv[])
{
    initUkuiLog4qt("youker-assistant");

    QApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
    QApplication::setHighDpiScaleFactorRoundingPolicy(Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif
    QString id = QString("ukui-assistant" + QLatin1String(getenv("DISPLAY")));
    qDebug() << "ID:" << id;
    QtSingleApplication app(id, argc, argv);
    QCoreApplication::setOrganizationName("kylin");
    QCoreApplication::setApplicationName("kylin-assistant");
    QCoreApplication::setApplicationVersion(getAppVersion());

    if (app.isRunning()) {
        app.sendMessage(QApplication::arguments().length() > 1 ? QApplication::arguments().at(1) : app.applicationFilePath());
        qDebug() << QObject::tr("app is already running!");
        return EXIT_SUCCESS;
    } else {
#if (QT_VERSION <= QT_VERSION_CHECK(5,0,0))
        QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
        QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
        QTextCodec::setCodecForTr(QTextCodec::codecForName("UTF-8"));
        QTextCodec::setCodecForCStrings(QTextCodec::codecForName("UTF-8"));
#endif
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
        if(locale == "zh_CN" || locale == "es" || locale == "fr" || locale == "de" || locale == "ru" || locale == "bo_CN") {//中文 西班牙语 法语 德语 俄语
        #if 0
            if(!translator.load("kylin-assistant_" + locale + ".qm",
                                ":/qmfile/translation/"))
        #else
            if(!translator.load("kylin-assistant_" + locale + ".qm",
                               "/usr/share/youker-assistant/translations/")) 
        #endif
                qWarning() << "Load translation file："<< "kylin-assistant_" + locale + ".qm" << " failed!";
            else
                app.installTranslator(&translator);
        }
        MainWindow w;

        MotifWmHints hints;
        hints.flags = MWM_HINTS_FUNCTIONS | MWM_HINTS_DECORATIONS;
        hints.functions = MWM_FUNC_ALL;
        hints.decorations = MWM_DECOR_BORDER;
        XAtomHelper::getInstance()->setWindowMotifHint(w.winId(), hints);
        app.setActivationWindow(&w);
        app.setWindowIcon(QIcon::fromTheme("kylin-assistant"));
        KWindowEffects::enableBlurBehind(w.winId(), true);
        QObject::connect(&app,SIGNAL(messageReceived(const QString&)), &w, SLOT(handleMessage(const QString&)));
        centerToScreen(&w);
        w.show();
        return app.exec();
    }
}
