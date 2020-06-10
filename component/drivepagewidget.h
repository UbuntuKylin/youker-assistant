#ifndef DRIVEPAGEWIDGET_H
#define DRIVEPAGEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QString>
#include <QScrollArea>
#include <QFrame>
#include <QPixmap>

class DrivePageWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrivePageWidget(QWidget *parent = nullptr);
    ~DrivePageWidget();

    void InitPageUI(QMap<QString, QVariant>);

    QString getWhichDrive(QString);
signals:

private:
    QLabel *lable;
    QFrame *main_frame;
    QVBoxLayout *v_layout;
    QVBoxLayout *main_layout;
    QScrollArea *scrollarea;
};

#endif // DRIVEPAGEWIDGET_H
