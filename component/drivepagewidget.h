#ifndef DRIVEPAGEWIDGET_H
#define DRIVEPAGEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QString>
#include <QScrollArea>
#include <QFrame>
#include <QPixmap>
#include <QStringList>
#include <QIcon>

class DrivePageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrivePageWidget(QWidget *parent = nullptr);
    ~DrivePageWidget();

    void InitPageUI(QMap<QString, QVariant>);

    QStringList getWhichDrive(QString);
signals:

private:
    QLabel *lable;
    QFrame *main_frame;
    QVBoxLayout *v_layout;
    QVBoxLayout *main_layout;
    QScrollArea *scrollarea;
    QStringList drive_list;
};

#endif // DRIVEPAGEWIDGET_H
