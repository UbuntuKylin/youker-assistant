#ifndef DRIVEWIDGET_H
#define DRIVEWIDGET_H

#include <QWidget>
#include <QSplitter>
#include <QStackedWidget>
#include <QListWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QStringList>
#include <QListWidgetItem>
#include <QLabel>
#include <QFrame>

#include "../component/drivepagewidget.h"

class DrivePageWidget;

class Drivewidget : public QWidget
{
    Q_OBJECT
public:
    explicit Drivewidget(QWidget *parent = nullptr);
    ~Drivewidget();

    void InitWidgetUI();
    QMap<QString, QVariant> getDriveInfo();

signals:

private slots:
    void changewidgetpage(QListWidgetItem*);

private:
    QSplitter *splitter;
    QStackedWidget *stackedwidget;
    QListWidget *list_widget;
    QHBoxLayout *main_layout;
    QStringList string_list;

    DrivePageWidget *all_drives;
    DrivePageWidget *drive_backup;
    DrivePageWidget *drive_reduction;
    DrivePageWidget *driver_uninstallation;
};

#endif // DRIVEWIDGET_H
