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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QPixmap>
#include <QSettings>
#include <QDesktopWidget>

#include "bottomcontentwidget.h"
#include "infowidget.h"
#include "settingwidget.h"
#include "cleanerwidget.h"
#include "boxwidget.h"
#include "../component/kylinmenu.h"
#include "../component/utils.h"
#include "../component/toolkits.h"
#include "aboutdialog.h"

class DataWorker;
class SystemDbusProxy;
class SessionDbusProxy;

class MainTopWidget;
class MiddleWidget;
class MainBottomWidget;
class TopBaseWidget;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QString cur_arch = "", int d_count = 0, QWidget* parent = 0/*, Qt::WindowFlags flags = 0*/);
    ~MainWindow();
    void setTranslator(QTranslator* translator);
    void initConnect();
    void reViewThePointSkin(QString pciture);
    void reViewTheOrgSkin();
    void changeSkin(QString pciture);
    void restoreSkin();
    int getCurrentBackgroundIndex();
    QString getCurrentBackgroundName();
    QString getCurrentBackgroundAbsName();
    QStringList filterSkin();
    bool deleteFile(QString filename);
    bool CopyFile(QString filename);
    QString accessOSName();
    void createAboutDialog();

    void initWidgets();
    void moveCenter();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void closeEvent(QCloseEvent *);
//    virtual void paintEvent(QPaintEvent *event);

public slots:
    void openSkinCenter();
    void openUpgradePage(/*QStringList version_list*/);
//    void openUpgradePageAgain();
    void showMainMenu();
    void closeYoukerAssistant();
    void setCurrentPageIndex(int index);
    void changeLanguage(LANGUAGE language);
    void newFeatures();
    void setupConfigure();
    void aboutUs();
    void startDbusDaemon();
    void onInitDataFinished();
    void onPluginModuleError(const QString &info);

private:
    QStackedWidget *m_topStack = nullptr;
    QStackedWidget *m_bottomStack = nullptr;

    MainTopWidget *m_mainTopWidget = nullptr;
    MiddleWidget *m_middleWidget = nullptr;
    MainBottomWidget *m_mainBottomWidget = nullptr;
    MainTopWidget *cleaner_action_widget;
    TopBaseWidget *info_action_widget = nullptr;
    TopBaseWidget *setting_action_widget = nullptr;
    TopBaseWidget *box_action_widget = nullptr;

    InfoWidget *info_widget = nullptr;
    CleanerWidget *cleaner_widget = nullptr;
    SettingWidget *setting_widget = nullptr;
    BoxWidget *box_widget = nullptr;
    KylinMenu *main_menu = nullptr;
    QPoint m_dragPosition; //移动的距离
    bool m_mousePressed; //按下鼠标左键
    QTranslator* translator = nullptr; //翻译器
    LANGUAGE current_language; //当前语言
    QPixmap main_skin_pixmap;
    QString last_skin_path;
    QPixmap review_skin_pixmap;
    Toolkits *toolKits = nullptr;
    AboutDialog *aboutDlg;
    QSettings *mSettings;
    QString desktop;
    QString osName;
    QString arch;
    bool battery;
    bool sensor;
    int display_count;
    QStringList m_cpulist;
    QString m_currentCpuMode;
    PAGESTATUS status;
    DataWorker *m_dataWorker = nullptr;
    QWidget *centralWidget = nullptr;
};

class GlobalData // define by hebing,just for transmit var
{

public:
    static QString globalarch;
};

#endif // MAINWINDOW_H
