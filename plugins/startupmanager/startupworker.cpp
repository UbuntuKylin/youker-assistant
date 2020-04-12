/*
 *
 * Copyright (C) 2008, 2009 Novell, Inc.
 * Copyright (C) 1999 Free Software Foundation, Inc.
 * Copyright (C) 2007, 2009 Vincent Untz.
 * Copyright (C) 2008 Lucas Rocha.
 * Copyright (C) 2008 William Jon McCann <jmccann@redhat.com>
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of the
 * License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA
 * 02111-1307, USA.
 *
 * Authors:
 *  Vincent Untz <vuntz@gnome.org>
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
 */

#include "startupworker.h"

#include <QSettings>
#include <QDebug>
#include <QFileInfo>
#include <QDirIterator>
#include <QSet>
//#include <QPollingFileSystemWatcherEngine>

#include <glib.h>
#include <sys/stat.h>
#include <string.h>
#include "util.h"

void ensureCKeyInDesktopFil (GKeyFile   *keyfile, const char *key)
{
        char *C_value;
        char *buffer;

        /* Make sure we set the "C" locale strings to the terms we set here.
         * This is so that if the user logs into another locale they get their
         * own description there rather then empty. It is not the C locale
         * however, but the user created this entry herself so it's OK */
        C_value = kylin_start_manager_key_file_get_string(keyfile, key);
        if (C_value == NULL || C_value [0] == '\0') {
            buffer = kylin_start_manager_key_file_get_locale_string(keyfile, key);
            if (buffer) {
                kylin_start_manager_key_file_set_string(keyfile, key, buffer);
                g_free(buffer);
            }
        }
        g_free(C_value);
}

inline QString getCurrentDesktopEnvironment()
{
    QString current_desktop;

    current_desktop = qgetenv("XDG_CURRENT_DESKTOP");//g_getenv
    if(current_desktop.isEmpty()) {
        current_desktop = qgetenv("XDG_SESSION_DESKTOP");
        if(current_desktop.isEmpty())
            current_desktop = "GNOME";
    }

    return current_desktop;
}

bool getShownFromDesktopFile(const QString &desktopFile, const QString &desktopEnvironment)
{
    if (desktopEnvironment.isNull() || desktopEnvironment.isEmpty())
        return true;

    bool found;
    QSettings setting(desktopFile, QSettings::IniFormat);
    setting.setIniCodec("UTF-8");
    setting.beginGroup(KEY_FILE_DESKTOP_GROUP);
    QStringList onlyShowIn = setting.value(KEY_FILE_DESKTOP_KEY_ONLY_SHOW_IN).toStringList();
    QStringList notShowIn = setting.value(KEY_FILE_DESKTOP_KEY_NOT_SHOW_IN).toStringList();
    setting.endGroup();

    if (!onlyShowIn.isEmpty()) {
        found = false;
        foreach (auto dekstopEnv, onlyShowIn) {
            if (dekstopEnv == desktopEnvironment) {
                found = true;
                break;
            }
        }
        if (!found)
            return false;
    }

    if (!notShowIn.isEmpty()) {
        found = false;
        foreach (auto dekstopEnv, notShowIn) {
            if (dekstopEnv == desktopEnvironment) {
                found = true;
                break;
            }
        }
        if (found)
            return false;
    }

    return true;
}

StartupWorker::StartupWorker(QObject *parent)
    : QObject(parent)
{

}

StartupWorker::~StartupWorker()
{
    m_startupInfoList.clear();

//    foreach (MonitorData item, this->m_monitorList) {
//        QFileSystemWatcher *watcher = item.watcher;
//        watcher->removePath(item.dir);
//        delete watcher;
//        watcher = NULL;
//    }
//    this->m_monitorList.clear();
    foreach (MonitorData item, this->m_xdgMap.values()) {
        QFileSystemWatcher *watcher = item.watcher;
        watcher->removePath(item.dir);
        delete watcher;
        watcher = NULL;
    }
    this->m_xdgMap.clear();
}

QFileSystemWatcher *StartupWorker::createFileSystemMonitor(const QString &path)
{
    /*int fd = inotify_init();
    int wd = inotify_add_watch (fd, path, mask);
//    int ret = inotify_rm_watch (fd, wd);*/

//    qDebug() << "watcher path="<<path;
    QFileSystemWatcher *m_fileSystemMonitor = new QFileSystemWatcher(this);
    m_fileSystemMonitor->addPath(path);
//    QFileInfo info(m_monitorFile);
//    m_fileSystemMonitor->addPath(info.absoluteFilePath());

    connect(m_fileSystemMonitor, &QFileSystemWatcher::directoryChanged, [=] (const QString &path) {
        //qDebug()<< "directoryChanged path===================="<<path;
        QStringList fileList;
        QDir dir(path);
        foreach(QFileInfo info, dir.entryInfoList()) {
            if (info.isFile() && info.suffix() == "desktop") {
                fileList.append(info.absoluteFilePath());
            }
        }

        /*QDirIterator dir(path, QDirIterator::Subdirectories);
        while(dir.hasNext()) {
            if (file.exists()) {
            }
            QFileInfo info = dir.fileInfo();
            if (info.isFile()) {
                if (info.suffix() == "desktop") {
//                if (dir.fileInfo().suffix() == "desktop") {
                    QString desktopFile = dir.filePath();
                    fileList.append(desktopFile);
                }
            }
            dir.next();
        }*/

        this->updateGspXdgDir(path, fileList);
    });
//    m_watcherList.append(m_fileSystemMonitor);
//    if (m_watcherMap.contains(path))
//        m_watcherMap.insert(path, m_fileSystemMonitor);

    return m_fileSystemMonitor;

//    connect(m_fileSystemMonitor, &QFileSystemWatcher::fileChanged, [=] (const QString &path) {
//        qDebug()<< "fileChanged path===================="<<path;
//    });
}

void StartupWorker::appendMonitorXdgDirData(MonitorData monitorData)
{
//    this->m_monitorList.append(monitorData);
    m_xdgMap.insert(monitorData.dir, monitorData);
}

int StartupWorker::getDirIndex(QString dir)
{
//    foreach (MonitorData item, this->m_monitorList) {
//        if (item.dir == dir) {
//            return item.index;
//        }
//    }
    foreach (MonitorData item, this->m_xdgMap.values()) {
        if (item.dir == dir) {
            return item.index;
        }
    }
    return -1;
}

QString StartupWorker::getMonitorDirectoryAccordXdgSystemPosition(unsigned int index)
{
//    foreach (MonitorData item, this->m_monitorList) {
//        if (item.index == index) {
//            return item.dir;
//        }
//    }
    foreach (MonitorData item, this->m_xdgMap.values()) {
        if (item.index == index) {
            return item.dir;
        }
    }

    return QString();
}


StartupData StartupWorker::getAppStartupDataAccrodDesktopFileName(QString &basename)
{
    for (StartupData info : this->getStartupInfoList()) {
        if (info.basename == basename) {
            return info;
        }
    }

    return StartupData();
}

/*
 * dir:被监控的目录      fileList:被监控目录下的文件列表
*/
void StartupWorker::updateGspXdgDir(const QString &dir, QStringList fileList)
{
    if (this->m_xdgMap.keys().contains(dir)) {
        QSet<QString> nowAutoStartSet = QSet<QString>::fromList(fileList);
        //canel auto start, add the desktop file to user config dir
        for(const QString &startupItem: nowAutoStartSet - QSet<QString>::fromList(this->m_xdgMap.value(dir).fileList)) {
            //qDebug() << "Add startupItem===="<<startupItem;
            this->newStartupInfo(startupItem, this->m_xdgMap.value(dir).index);
        }

        //start auto start, remove the desktop file which in user config dir
        for(const QString &startupItem: QSet<QString>::fromList(this->m_xdgMap.value(dir).fileList) - nowAutoStartSet) {
            //qDebug() << "Removed startupItem===="<<startupItem;
            StartupData info = getStartupInfoAccordDestkopFile(startupItem);
            if (info.exec.isEmpty() && info.name.isEmpty())
                continue;
            info.enabled = true;
            info.save_mask |= SAVE_MASK_ENABLED;
            this->updateEnable(info.exec, info.enabled);
            this->updateSaveMask(info.exec, info.save_mask);
            this->readySaveDesktopInfo(info);
        }

        /*
        //start auto start, remove the desktop file which in user config dir
        foreach (QString orgFileAbsPath, this->m_xdgMap.value(dir).fileList) {
            if (!fileList.contains(orgFileAbsPath)) {
                qDebug() << "had removed orgFileAbsPath="<<orgFileAbsPath;
                //had removed
                StartupData info = getStartupInfoAccordDestkopFile(orgFileAbsPath);
                if (info.exec.isEmpty() && info.name.isEmpty())
                    continue;
                info.enabled = true;
                info.save_mask |= SAVE_MASK_ENABLED;
                this->updateEnable(info.exec, info.enabled);
                this->updateSaveMask(info.exec, info.save_mask);
                this->readySaveDesktopInfo(info);
            }
        }

        //canel auto start, add the desktop file to user config dir
        foreach (QString nowFileAbsPath, fileList) {
            if (!this->m_xdgMap[dir].fileList.contains(nowFileAbsPath)) {
                //new added
                qDebug() << "add new nowFileAbsPath="<<nowFileAbsPath;
                this->newStartupInfo(nowFileAbsPath, this->m_xdgMap.value(dir).index);
            }
        }
        */

        this->m_xdgMap[dir].fileList.clear();
        this->m_xdgMap[dir].fileList = fileList;

        emit this->refreshUI();
    }
    else
        qDebug() << "WTF........";
}

QString StartupWorker::getStringValueAccordKeyFromDesktopFile(const gchar *key, const QString &desktopFile, bool isLocale)
{
    GKeyFile *keyfile;
    keyfile = g_key_file_new ();
    if (!g_key_file_load_from_file (keyfile, desktopFile.toStdString().c_str(), G_KEY_FILE_NONE, NULL)) {
        g_key_file_free (keyfile);
        return QString();
    }

    if (isLocale) {
        std::string formatted_result(make_string(kylin_start_manager_key_file_get_locale_string (keyfile, key)));
        QString result = QString::fromStdString(formatted_result);
        g_key_file_free (keyfile);
        return result;
    }
    else {
        std::string formatted_result = make_string(kylin_start_manager_key_file_get_string (keyfile, key));
        QString result = QString::fromStdString(formatted_result);
        g_key_file_free (keyfile);
        return result;
    }
}

void StartupWorker::newStartupInfo(const QString &desktopFile, unsigned int xdg_position)
{
    bool isNew;
    QString basename = QFileInfo(desktopFile).fileName();

    StartupData info = getAppStartupDataAccrodDesktopFileName(basename);
    if (info.basename.isEmpty() && info.name.isEmpty() && info.exec.isEmpty())
        isNew = true;
    else
        isNew = false;

    if (!isNew) {
        //qDebug() << "is not new!!!!";
        if (info.xdg_position < xdg_position) {
            /* we don't really care about this file, since we
             * already have something with a higher priority, or
             * we're going to write something in the user config
             * anyway.
             * Note: xdg_position >= 1 so it's a system dir */
            info.xdg_system_position = MIN (xdg_position, info.xdg_system_position);
            return;
        }
    }

    GKeyFile *keyfile;
    keyfile = g_key_file_new ();
    if (!g_key_file_load_from_file (keyfile, desktopFile.toStdString().c_str(), G_KEY_FILE_NONE, NULL)) {
        g_key_file_free(keyfile);
        return;
    }

    bool hidden = get_boolean_from_desktop_file (keyfile, G_KEY_FILE_DESKTOP_KEY_HIDDEN, FALSE);
    bool no_display = get_boolean_from_desktop_file (keyfile,G_KEY_FILE_DESKTOP_KEY_NO_DISPLAY,FALSE);
    bool enabled = get_boolean_from_desktop_file (keyfile, KEY_FILE_DESKTOP_KEY_AUTOSTART_ENABLED,TRUE);
    bool shown = get_shown_from_desktop_file (keyfile,get_current_desktop_env ());

    std::string formatted_result(make_string(kylin_start_manager_key_file_get_locale_string (keyfile, G_KEY_FILE_DESKTOP_KEY_NAME)));
    QString name = QString::fromStdString(formatted_result);
    formatted_result = make_string(kylin_start_manager_key_file_get_string (keyfile, G_KEY_FILE_DESKTOP_KEY_EXEC));
    QString exec = QString::fromStdString(formatted_result);
    formatted_result = make_string(kylin_start_manager_key_file_get_locale_string (keyfile, G_KEY_FILE_DESKTOP_KEY_COMMENT));
    QString comment = QString::fromStdString(formatted_result);
    formatted_result = make_string(kylin_start_manager_key_file_get_locale_string (keyfile, G_KEY_FILE_DESKTOP_KEY_ICON));
    QString icon = QString::fromStdString(formatted_result);
    if (name.isEmpty() || name.isNull())
        name = exec;
    if (comment.isEmpty() || comment.isNull())
        comment = tr("No description");

    /*QSettings setting(desktopFile, QSettings::IniFormat);
    setting.setIniCodec("UTF-8");
    setting.beginGroup(KEY_FILE_DESKTOP_GROUP);

    bool hidden = setting.value(KEY_FILE_DESKTOP_KEY_HIDDEN, false).toBool();
    bool no_display = setting.value(KEY_FILE_DESKTOP_KEY_NO_DISPLAY, false).toBool();
    bool enabled = setting.value(KEY_FILE_DESKTOP_KEY_AUTOSTART_ENABLED, true).toBool();
    bool shown = getShownFromDesktopFile(desktopFile, getCurrentDesktopEnvironment());

    QString name = setting.value(KEY_FILE_DESKTOP_KEY_NAME).toString();
    QString exec = setting.value(KEY_FILE_DESKTOP_KEY_EXEC).toString();
    QString comment = setting.value(KEY_FILE_DESKTOP_KEY_COMMENT).toString();
    QString icon = setting.value(KEY_FILE_DESKTOP_KEY_ICON).toString();
    if (name.isEmpty() || name.isNull())
        name = exec;
    setting.endGroup();*/

    //get description
    QString primary;
    QString secondary;
    if (!name.isEmpty()) {
        primary = name;
    } else if (!exec.isEmpty()) {
        primary = exec;
    } else {
        primary = tr("No name");
    }
    if (!comment.isEmpty()) {
        secondary = comment;
    } else {
        secondary = tr("No description");
    }
    QString description = QString("<b>%1</b>\n%2").arg(primary).arg(secondary);

    info.basename = basename;
    info.path = desktopFile;
    info.hidden = hidden;
    info.no_display = no_display;
    info.enabled = enabled;
    info.shown = shown;
    info.name = name;
    info.exec = exec;
    info.comment = comment;
    info.icon = icon;
    info.description = description;

    if (xdg_position > 0) {
        info.xdg_system_position = xdg_position;
    }
    /* else we keep the old value (which is G_MAXUINT if it wasn't set) */
    info.xdg_position = xdg_position;
//    printf("info.xdg_position===%d\n", info.xdg_position);
    info.old_system_path.clear();

    //printf("hidden=%s\n", hidden ? "Yes" : "No");

    m_startupInfoList[exec] = info;//append item

/*
    //show or hide
    if (!hidden && shown && !no_display) {
        //show
//        if (isExecContains(exec)) {

//        }
        m_startupInfoList[exec] = info;

    }
    else {
        //hide
        if (isExecContains(exec))
            m_startupInfoList.remove(exec);
    }
    */
}

bool StartupWorker::isExecContains(const QString &exec)
{
    return m_startupInfoList.keys().contains(exec);
}

QList<StartupData> StartupWorker::getStartupInfoList() const
{
    return m_startupInfoList.values();
}

StartupData StartupWorker::getStartupInfo(const QString &exec)
{
    return m_startupInfoList.value(exec, StartupData());//nullptr
}

StartupData StartupWorker::getStartupInfoAccordDestkopFile(const QString &desktopFile)
{
    foreach (StartupData data, m_startupInfoList.values()) {
        if (data.path == desktopFile)
            return data;
    }
    return StartupData();
}

void StartupWorker::updateEnable(const QString &exec, bool enabled)
{
    if (m_startupInfoList.contains(exec)) {
        m_startupInfoList[exec].enabled = enabled;//m_startupInfoList[exec].setEnabled(enabled);
    }
}

void StartupWorker::updateSaveMask(const QString &exec, unsigned int save_mask)
{
    if (m_startupInfoList.contains(exec)) {
        m_startupInfoList[exec].save_mask = save_mask;
    }
}

void StartupWorker::updateXdgPosition(const QString &exec, unsigned int xdg_position)
{
    if (m_startupInfoList.contains(exec)) {
        m_startupInfoList[exec].xdg_position = xdg_position;
    }
}

void StartupWorker::updateXdgSystemPosition(const QString &exec, unsigned int xdg_system_position)
{
    if (m_startupInfoList.contains(exec)) {
        m_startupInfoList[exec].xdg_system_position = xdg_system_position;
    }
}

void StartupWorker::updateOldSystemPath(const QString &exec, QString old_system_path)
{
    if (m_startupInfoList.contains(exec)) {
        m_startupInfoList[exec].old_system_path = old_system_path;
    }
}

void StartupWorker::updatePath(const QString &exec, QString path)
{
    if (m_startupInfoList.contains(exec)) {
        m_startupInfoList[exec].path = path;
    }
}

void StartupWorker::ensureUserAutostartupDirExists(void)
{
    char *dir;
    dir = g_build_filename(g_get_user_config_dir(), "autostart", NULL);
    g_mkdir_with_parents(dir, S_IRWXU);//S_IRWXU 00700 权限，代表该文件所有者具有可读、可写及可执行的权限
    g_free(dir);

//    QDir dir;
//    if(!dir.exists("aa")){
//        dir.mkdir("aa");
//    }
    /*const gchar *config_dir = g_get_user_config_dir();
    std::string formatted_result(make_string(g_strdup(config_dir)));//std::string formatted_result = make_string(g_strdup(config_dir));
    QString dir = QString::fromStdString(formatted_result);
    if (dir.endsWith(QLatin1String("/")))
        g_mkdir_with_parents (dir + "autostart", S_IRWXU);//if (g_mkdir_with_parents (dir, 0755) == 0)
    else
        g_mkdir_with_parents (dir + "/autostart", S_IRWXU);*/
}

void StartupWorker::changeSaveFlagsWhenDoneSuccess(StartupData info)
{
    info.save_mask = 0;
    this->updateSaveMask(info.exec, info.save_mask);
    if (!info.old_system_path.isEmpty()) {
        info.old_system_path.clear();
        this->updateOldSystemPath(info.exec, info.old_system_path);
    }
}

/*
 *判断desktop文件是否同时存在于用户的启动配置目录下和系统的启动配置目录下，
 *如果同时存在，说明已经禁止了自启动，否则该应用程序是开机自启动的
*/
bool StartupWorker::isDesktopFileInUserAndSystemConfiguDir(StartupData info, char **system_path)
{
    QString system_dir;
    char          *path;
    char          *str;
    GKeyFile      *keyfile;

    system_dir = getMonitorDirectoryAccordXdgSystemPosition(info.xdg_system_position);
    if (system_dir.isEmpty()) {
        return false;
    }

    path = g_build_filename(system_dir.toStdString().c_str(), info.basename.toStdString().c_str(), NULL);
    keyfile = g_key_file_new();
    if (!g_key_file_load_from_file(keyfile, path, G_KEY_FILE_NONE, NULL)) {
        g_free(path);
        g_key_file_free(keyfile);
        return false;
    }

    if (get_boolean_from_desktop_file(keyfile, G_KEY_FILE_DESKTOP_KEY_HIDDEN, FALSE) != info.hidden ||
        get_boolean_from_desktop_file(keyfile, KEY_FILE_DESKTOP_KEY_AUTOSTART_ENABLED, TRUE) != info.enabled ||
        get_shown_from_desktop_file (keyfile, get_current_desktop_env()) != info.shown) {
        g_free(path);
        g_key_file_free(keyfile);
        return false;
    }
    if (get_boolean_from_desktop_file(keyfile, G_KEY_FILE_DESKTOP_KEY_NO_DISPLAY, FALSE) != info.no_display) {
        g_free(path);
        g_key_file_free(keyfile);
        return false;
    }

    str = kylin_start_manager_key_file_get_locale_string(keyfile, G_KEY_FILE_DESKTOP_KEY_NAME);
    if (!is_str_equal (str, info.name.toStdString().c_str())) {
            g_free(str);
            g_free(path);
            g_key_file_free(keyfile);
            return false;
    }
    g_free(str);

    str = kylin_start_manager_key_file_get_locale_string(keyfile, G_KEY_FILE_DESKTOP_KEY_COMMENT);
    if (!is_str_equal(str, info.comment.toStdString().c_str())) {
            g_free(str);
            g_free(path);
            g_key_file_free(keyfile);
            return false;
    }
    g_free(str);

    str = kylin_start_manager_key_file_get_string(keyfile, G_KEY_FILE_DESKTOP_KEY_EXEC);
    if (!is_str_equal(str, info.exec.toStdString().c_str())) {
        g_free(str);
        g_free(path);
        g_key_file_free(keyfile);
        return false;
    }
    g_free(str);

    str = kylin_start_manager_key_file_get_locale_string(keyfile, G_KEY_FILE_DESKTOP_KEY_ICON);
    if (!is_str_equal(str, info.icon.toStdString().c_str())) {//info.icon.toStdString().data()
        g_free(str);
        g_free(path);
        g_key_file_free(keyfile);
        return false;
    }
    g_free(str);

    g_key_file_free(keyfile);
    *system_path = path;

    return true;
}

/*bool StartupWorker::isDesktopFileInUserAndSystemConfiguDir (StartupData info, QString &system_path, QString locale)
{
    QString system_dir;
    QString path;
    QString str;

    system_dir = getMonitorDirectoryAccordXdgSystemPosition(info.xdg_system_position);
    if (system_dir.isEmpty()) {
        return false;
    }

    path = QString("%1/%2").arg(system_dir).arg(info.basename);

    QSettings setting(path, QSettings::IniFormat);
    setting.setIniCodec("UTF-8");
    setting.beginGroup(KEY_FILE_DESKTOP_GROUP);

    if (setting.value(KEY_FILE_DESKTOP_KEY_HIDDEN, false).toBool() != info.hidden
            || setting.value(KEY_FILE_DESKTOP_KEY_AUTOSTART_ENABLED, true).toBool() != info.enabled
            || getShownFromDesktopFile(path, getCurrentDesktopEnvironment()) != info.shown) {
        setting.endGroup();
        return false;
    }

    if (setting.value(KEY_FILE_DESKTOP_KEY_NO_DISPLAY, false).toBool() != info.no_display) {
        setting.endGroup();
        return false;
    }

    str = setting.value(QString("%1\[%2\]").arg(KEY_FILE_DESKTOP_KEY_NAME).arg(locale)).toString();
    if (QString::compare(str, info.name) != 0) {
        setting.endGroup();
        return false;
    }
    str = setting.value(QString("%1\[%2\]").arg(KEY_FILE_DESKTOP_KEY_COMMENT).arg(locale)).toString();
    if (QString::compare(str, info.comment) != 0) {
        setting.endGroup();
        return false;
    }

    str = setting.value(KEY_FILE_DESKTOP_KEY_EXEC).toString();
    if (QString::compare(str, info.exec) != 0) {
        setting.endGroup();
        return false;
    }

    str = setting.value(QString("%1\[%2\]").arg(KEY_FILE_DESKTOP_KEY_ICON).arg(locale)).toString();
    if (QString::compare(str, info.icon) != 0) {
        setting.endGroup();
        return false;
    }
    system_path = path;

    setting.endGroup();

    return true;
}*/

//void StartupWorker::ensureCKeyInDesktopFil(QString filename, QString key, QString locale)
//{
//    QSettings setting(filename, QSettings::IniFormat);
//    setting.setIniCodec("UTF-8");
//    setting.beginGroup(KEY_FILE_DESKTOP_GROUP);
//    QString C_value;
//    /* Make sure we set the "C" locale strings to the terms we set here.
//     * This is so that if the user logs into another locale they get their
//     * own description there rather then empty. It is not the C locale
//     * however, but the user created this entry herself so it's OK */
//    C_value = setting.value(key).toString();
//    if (C_value.isEmpty() || C_value.isNull()) {
//        QString buffer = setting.value(QString("%1\[%2\]").arg(key).arg(locale)).toString();//g_key_file_get_locale_string
//        if (!buffer.isEmpty()) {
//            setting.setValue(key, buffer);
//        }
//    }
//    setting.endGroup();
//    setting.sync();
//}

bool StartupWorker::saveAppDesktopInfo(StartupData info)
{
    char     *desktop_path;
    GKeyFile *keyfile;
    GError   *error;

    /* first check if removing the data from the user dir and using the
     * data from the system dir is enough -- this helps us keep clean the
     * user config dir by removing unneeded files */
    if (isDesktopFileInUserAndSystemConfiguDir(info, &desktop_path)) {//由关闭到开启的转换过程
        QFile file(info.path);
        if (file.exists()) {
            file.remove();
        }
        std::string formatted_result(make_string(g_strdup(desktop_path)));
        info.path = QString::fromStdString(formatted_result);
        this->updatePath(info.exec, info.path);
        info.xdg_position = info.xdg_system_position;
        this->updateXdgPosition(info.exec, info.xdg_position);
        changeSaveFlagsWhenDoneSuccess(info);
        return false;
    }

    //由开启到关闭的转换过程
    if (!info.old_system_path.isEmpty()) {
        desktop_path = g_strdup(info.old_system_path.toStdString().c_str());
    }
    else {
        desktop_path = g_strdup(info.path.toStdString().c_str());
    }

    keyfile = g_key_file_new();
    error = NULL;
    GKeyFileFlags flags;
    flags = G_KEY_FILE_KEEP_COMMENTS | G_KEY_FILE_KEEP_TRANSLATIONS;
    g_key_file_load_from_file(keyfile, desktop_path, flags, &error);
    g_free(desktop_path);

    if (error) {
        qDebug() << "=======save app desktop error=======";
        g_error_free(error);
        write_default_error_info_to_desktop_file(keyfile);
    }

    //以下操作对文件desktop_path的内容只做缓存修改处理，修改后的数据不写入文件desktop_path，而是将改动后的desktop_path的所有文件内容写入info.path文件中
    if (info.save_mask & SAVE_MASK_HIDDEN) {
        kylin_start_manager_key_file_set_boolean(keyfile, G_KEY_FILE_DESKTOP_KEY_HIDDEN, info.hidden);
    }

    if (info.save_mask & SAVE_MASK_NO_DISPLAY) {
        kylin_start_manager_key_file_set_boolean(keyfile, G_KEY_FILE_DESKTOP_KEY_NO_DISPLAY, info.no_display);
    }

    if (info.save_mask & SAVE_MASK_ENABLED) {
        kylin_start_manager_key_file_set_boolean(keyfile, KEY_FILE_DESKTOP_KEY_AUTOSTART_ENABLED, info.enabled);
    }

    if (info.save_mask & SAVE_MASK_NAME) {
        set_locale_string_into_desktop_file(keyfile, G_KEY_FILE_DESKTOP_KEY_NAME, info.name.toStdString().c_str());
        ensureCKeyInDesktopFil(keyfile, G_KEY_FILE_DESKTOP_KEY_NAME);
    }
    if (info.save_mask & SAVE_MASK_COMMENT) {
        set_locale_string_into_desktop_file(keyfile, G_KEY_FILE_DESKTOP_KEY_COMMENT, info.comment.toStdString().c_str());
        ensureCKeyInDesktopFil(keyfile, G_KEY_FILE_DESKTOP_KEY_COMMENT);
    }

    if (info.save_mask & SAVE_MASK_EXEC) {
        kylin_start_manager_key_file_set_string(keyfile, G_KEY_FILE_DESKTOP_KEY_EXEC, info.exec.toStdString().c_str());
    }

    ensureUserAutostartupDirExists();
    if (write_contents_into_desktop_file(keyfile, info.path.toStdString().c_str(), NULL)) {//将改动后的use_path的所有文件内容写入info.path文件中
        changeSaveFlagsWhenDoneSuccess(info);
    }
    else {
        qDebug() << QString("Could not save %1 file").arg(info.path);
    }
    g_key_file_free(keyfile);

    return false;



/*
    QString use_path;

    QString locale = QLocale::system().name();
//    qDebug() << "locale="<<locale;

    //first check if removing the data from the user dir and using the
    //data from the system dir is enough -- this helps us keep clean the
    //user config dir by removing unneeded files
    if (isDesktopFileInUserAndSystemConfiguDir(info, use_path, locale)) {
        qDebug() << "system use_path="<<use_path;
        QFile file(info.path);
        if (file.exists()) {
            file.remove();
        }
        info.path = use_path;
        this->updatePath(info.exec, info.path);
        info.xdg_position = info.xdg_system_position;
        this->updateXdgPosition(info.exec, info.xdg_position);
        changeSaveFlagsWhenDoneSuccess(info);
        return false;
    }

    if (!info.old_system_path.isEmpty())
        use_path = info.old_system_path;
    else
        use_path = info.path;

    qDebug() << "normal use_path="<<use_path;

//    const char         *locale;
//    const char * const *langs_pointer;
//    int                 i;
//    locale = NULL;
//    langs_pointer = g_get_language_names ();
//    for (i = 0; langs_pointer[i] != NULL; i++) {
//        printf("langs_pointer[i]=%s\n", langs_pointer[i]);
//            //find first without encoding
//            if (strchr (langs_pointer[i], '.') == NULL) {
//                    locale = langs_pointer[i];
//                    break;
//            }
//    }
//    if (locale != NULL) {
//        printf("locale=%s\n", locale);//locale=zh_CN
//    }

    //if read error:set KEY_FILE_DESKTOP_KEY_TYPE "Application" and set KEY_FILE_DESKTOP_KEY_EXEC "/bin/false"
    QSettings setting(use_path, QSettings::IniFormat);
    setting.setIniCodec("UTF-8");
    setting.beginGroup(KEY_FILE_DESKTOP_GROUP);
    if (info.save_mask & SAVE_MASK_HIDDEN) {
        setting.setValue(KEY_FILE_DESKTOP_KEY_HIDDEN, info.hidden);
    }
    if (info.save_mask & SAVE_MASK_NO_DISPLAY) {
        setting.setValue(KEY_FILE_DESKTOP_KEY_NO_DISPLAY, info.no_display);
    }
    if (info.save_mask & SAVE_MASK_ENABLED) {
        setting.setValue(KEY_FILE_DESKTOP_KEY_AUTOSTART_ENABLED, info.enabled);
    }
    if (info.save_mask & SAVE_MASK_NAME) {
        setting.setValue(QString("%1\[%2\]").arg(KEY_FILE_DESKTOP_KEY_NAME).arg(locale), info.name);
//        ensureCKeyInDesktopFil(use_path, KEY_FILE_DESKTOP_KEY_NAME, locale);
    }
    if (info.save_mask & SAVE_MASK_COMMENT) {
        setting.setValue(QString("%1\[%2\]").arg(KEY_FILE_DESKTOP_KEY_COMMENT).arg(locale), info.comment);
//        ensureCKeyInDesktopFil(use_path, KEY_FILE_DESKTOP_KEY_NAME, locale);
    }
    if (info.save_mask & SAVE_MASK_EXEC) {
        setting.setValue(KEY_FILE_DESKTOP_KEY_EXEC, info.exec);
    }
    ensureUserAutostartupDirExists();

    setting.endGroup();
    setting.sync();
    changeSaveFlagsWhenDoneSuccess(info);

    return false;*/
}


void StartupWorker::readySaveDesktopInfo(StartupData info)
{
    /* if the file was not in the user directory, then we'll create a copy
     * there */
    if (info.xdg_position != 0) {//当desktop文件不存在于用户配置目录下时
        info.xdg_position = 0;
        this->updateXdgPosition(info.exec, info.xdg_position);
        if (info.old_system_path.isEmpty()) {
                info.old_system_path = info.path;//将desktop文件当前路径记录到old_system_path中
                this->updateOldSystemPath(info.exec, info.old_system_path);
                /* if old_system_path was not NULL, then it means we
                 * tried to save and we failed; in that case, we want
                 * to try again and use the old file as a basis again */
        }

        //生成一个用户配置目录的desktop文件路径
        const gchar *config_dir = g_get_user_config_dir();
        std::string formatted_result(make_string(g_strdup(config_dir)));
        QString tmpPath = QString::fromStdString(formatted_result);
        if (tmpPath.endsWith(QLatin1String("/")))
            info.path = QString("%1/autostart/%2").arg(tmpPath).arg(info.basename);
        else
            info.path = QString("%1/autostart/%2").arg(tmpPath).arg(info.basename);

        this->updatePath(info.exec, info.path);
    }
    saveAppDesktopInfo(info);
}
