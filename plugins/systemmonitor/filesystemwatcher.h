#ifndef FILESYSTEMWATCHER_H
#define FILESYSTEMWATCHER_H

#include <QObject>
#include <QSet>
#include <QSocketNotifier>

class FileSystemWatcher : public QObject
{
    Q_OBJECT
public:
    static FileSystemWatcher *instance();

    FileSystemWatcher(QObject *parent = 0);
    ~FileSystemWatcher();

    bool watcherInitSuccess();

signals:
    void deviceAdded(const QString &addDevice);
    void deviceRemoved(const QString &removeDevice);

public slots:
    bool initWatcher();
    bool clearWatcher();

private slots:
    void onMountDeviceFileContentsChanged();

private:
    int m_fd;
    QSocketNotifier *m_socketNotifier = nullptr;
    QSet<QString> m_origFileSet;
    static FileSystemWatcher *m_watcher;
};

#endif // FILESYSTEMWATCHER_H
