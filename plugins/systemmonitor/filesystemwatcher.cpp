#include "filesystemwatcher.h"
#include "util.h"

#include <QDebug>

FileSystemWatcher *FileSystemWatcher::m_watcher = NULL;

FileSystemWatcher *FileSystemWatcher::instance()
{
    if (!m_watcher) {
        m_watcher = new FileSystemWatcher;
        m_watcher->initWatcher();
    }
    return m_watcher;
}

FileSystemWatcher::FileSystemWatcher(QObject *parent)
    : QObject(parent)
    ,m_fd(-1)
{

}

FileSystemWatcher::~FileSystemWatcher()
{
    this->clearWatcher();
}

bool FileSystemWatcher::initWatcher()
{
    m_origFileSet = getFileContentsLineByLine(DEVICE_MOUNT_PONINT_RECORD_FILE);
    m_fd = open(DEVICE_MOUNT_PONINT_RECORD_FILE, O_RDONLY);
    if (m_fd == -1) {
        qDebug() << QString("open %1 failed!").arg(DEVICE_MOUNT_PONINT_RECORD_FILE);
        return false;
    }

    m_socketNotifier = new QSocketNotifier(m_fd, QSocketNotifier::Write, this);
    m_socketNotifier->setEnabled(true);
    connect(m_socketNotifier, &QSocketNotifier::activated, this, &FileSystemWatcher::onMountDeviceFileContentsChanged);
    return true;
}

bool FileSystemWatcher::watcherInitSuccess()
{
    if (m_fd != -1 && m_socketNotifier) {
        return true;
    }
    else {
        return false;
    }
}

bool FileSystemWatcher::clearWatcher()
{
    if (this->watcherInitSuccess()) {
        close(m_fd);
        m_fd = -1;

        delete m_socketNotifier;
        m_socketNotifier = nullptr;

        return true;
    }
    else {
        return false;
    }
}

void FileSystemWatcher::onMountDeviceFileContentsChanged()
{
    QSet<QString> nowFileSet = getFileContentsLineByLine(DEVICE_MOUNT_PONINT_RECORD_FILE);
    for(const QString &mountPath: nowFileSet - m_origFileSet) {
        emit this->deviceAdded(getDeviceMountedPointPath(mountPath));
    }
    for(const QString &mountPath: m_origFileSet - nowFileSet) {
        emit this->deviceRemoved(getDeviceMountedPointPath(mountPath));
    }
    m_origFileSet = nowFileSet;
}
