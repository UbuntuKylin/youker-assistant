/*
 * Copyright (C) 2013 ~ 2018 National University of Defense Technology(NUDT) & Tianjin Kylin Ltd.
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

#include <QWidget>
#include <QSettings>
#include <QMenu>
#include <QFileSystemWatcher>
#include "filesystemlistwidget.h"

class FileSystemData;
class FileSystemWorker;
class FileSystemWatcher;
class QVBoxLayout;
class QHBoxLayout;

class FileSystemDialog : public QWidget
{
    Q_OBJECT

public:
    explicit FileSystemDialog(QList<bool> toBeDisplayedColumns, QSettings *settings, QWidget* parent = 0);
    ~FileSystemDialog();

    FileSystemListWidget *getFileSysView();
    void initFileSystemMonitor();

public slots:
    void refreshFileSysList();
    void onDirectoryChanged(QString path);
    void popupMenu(QPoint pos);

signals:
    void changeColumnVisible(int index, bool visible, QList<bool> columnVisible);

//private:
//    bool event(QEvent *event);

private:
    FileSystemWorker *m_fileSystemWorker = nullptr;
//    QFileSystemWatcher *m_fileSystemMonitor = nullptr;
//    QString m_monitorFile;
    QSettings *proSettings = nullptr;
    FileSystemListWidget *m_fileSysListWidget = nullptr;
    QAction *m_refreshAction = nullptr;
    QMenu *m_menu = nullptr;
    QVBoxLayout *m_layout = nullptr;
    QTimer *m_timer = nullptr;
    FileSystemWatcher *m_fileSystemWatcher = nullptr;
};
