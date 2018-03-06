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

#include "filesystemdialog.h"
#include <QApplication>
#include <QVBoxLayout>
#include <QEvent>
#include <QDebug>
#include <QFileInfo>

#include "filesystemdata.h"
#include "filesystemworker.h"

#include "filesystemwatcher.h"

FileSystemDialog::FileSystemDialog(QList<bool> toBeDisplayedColumns, QSettings *settings, QWidget *parent)
    :QWidget(parent)
    ,proSettings(settings)
//    ,m_monitorFile("/home/lixiang/testwatcher/1.c")
//    ,m_monitorFile("/etc/mtab")
{
    setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
    setAcceptDrops(true);
    setAttribute(Qt::WA_NoMousePropagation);
//    setAttribute(Qt::WA_TranslucentBackground);

    this->setObjectName("FileSystemDialog");

    m_layout = new QVBoxLayout(this);
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    m_fileSysListWidget = new FileSystemListWidget(toBeDisplayedColumns);
    connect(m_fileSysListWidget, &FileSystemListWidget::rightMouseClickedItem, this, &FileSystemDialog::popupMenu, Qt::QueuedConnection);
    connect(m_fileSysListWidget, SIGNAL(changeColumnVisible(int,bool,QList<bool>)), this, SIGNAL(changeColumnVisible(int,bool,QList<bool>)));
    m_layout->addWidget(m_fileSysListWidget);

    m_fileSystemWorker = new FileSystemWorker;
    m_fileSystemWorker->moveToThread(qApp->thread());

//    this->initFileSystemMonitor();

    m_menu = new QMenu();
    m_refreshAction = new QAction(tr("Refresh"), this);
    connect(m_refreshAction, &QAction::triggered, this, &FileSystemDialog::refreshFileSysList);
    m_menu->addAction(m_refreshAction);

    this->refreshFileSysList();

    m_fileSystemWatcher = FileSystemWatcher::instance();
    connect(m_fileSystemWatcher, &FileSystemWatcher::deviceAdded, this, [=] (const QString &dev) {
        this->refreshFileSysList();
    });
    connect(m_fileSystemWatcher, &FileSystemWatcher::deviceRemoved, this, [=] (const QString &dev) {
        this->refreshFileSysList();
    });

    //refresh file system info every 10 minutes
    m_timer = new QTimer(this);
    connect(m_timer,SIGNAL(timeout()),this,SLOT(refreshFileSysList()));
    m_timer->start(10000);
}

FileSystemDialog::~FileSystemDialog()
{
//    m_fileSystemMonitor->removePath(m_monitorFile);
//    delete m_fileSystemMonitor;
    if (m_timer != NULL) {
        disconnect(m_timer,SIGNAL(timeout()),this,SLOT(refreshProcproperties()));
        if(m_timer->isActive()) {
            m_timer->stop();
        }
        delete m_timer;
        m_timer = NULL;
    }

    m_fileSystemWorker->deleteLater();
    delete m_fileSysListWidget;
    delete m_refreshAction;
    delete m_menu;
    delete m_layout;
}

void FileSystemDialog::refreshFileSysList()
{
    m_fileSystemWorker->onFileSystemListChanged();

    QList<FileSystemListItem*> items;
    for (FileSystemData *info : m_fileSystemWorker->diskInfoList()) {
        FileSystemListItem *item = new FileSystemListItem(info);
        items << item;
    }
    m_fileSysListWidget->refreshFileSystemItems(items);
}

void FileSystemDialog::popupMenu(QPoint pos)
{
    m_menu->exec(pos);
}

FileSystemListWidget* FileSystemDialog::getFileSysView()
{
    return m_fileSysListWidget;
}

void FileSystemDialog::initFileSystemMonitor() {
    /*int fd = inotify_init();
    int wd = inotify_add_watch (fd, path, mask);
//    int ret = inotify_rm_watch (fd, wd);*/


    /*m_fileSystemMonitor = new QFileSystemWatcher(this);
//    m_fileSystemMonitor->addPath(m_monitorFile);
    QFileInfo info(m_monitorFile);
    m_fileSystemMonitor->addPath(info.absoluteFilePath());

    connect(m_fileSystemMonitor, SIGNAL(directoryChanged(QString)), this, SLOT(onDirectoryChanged(QString)));
    connect(m_fileSystemMonitor, &QFileSystemWatcher::fileChanged, [=] (const QString &path) {
        qDebug()<< "file path===================="<<path;
    });*/
}

void FileSystemDialog::onDirectoryChanged(QString path)
{
    qDebug()<< "dir path===================="<<path;
}

//bool FileSystemDialog::event(QEvent *event)
//{
//    if (event->type() == QEvent::LayoutRequest)
//        setFixedHeight(m_centralLayout->sizeHint().height());

//    return QWidget::event(event);
//}
