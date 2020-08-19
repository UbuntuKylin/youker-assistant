#ifndef FANWIDGET_H
#define FANWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QString>
#include <QFrame>
#include <QPixmap>
#include <QFont>
#include <QDebug>
#include <QPainter>
#include <QMovie>
#include <QTimer>
#include <QLabel>


class Fanwidget : public QWidget
{
    Q_OBJECT
public:
    explicit Fanwidget(QWidget *parent = nullptr);
    ~Fanwidget();

    void InitUI();
    void Initwidgettop();
    void Initwidgetbottom();

signals:
    void Requestsignal();

private slots:
    void RefreshInterface(QMap<QString,QVariant> tmpMap);

private:
    QVBoxLayout *main_layout;
    QHBoxLayout *top_layout;
    QHBoxLayout *bottom_layout;

    QLabel *top_fan_speed;
    QLabel *tip_speed;
    QLabel *speed_lable;
    QLabel *icon_lable;
    QMovie *movie;

    QString Speed = "5600";
    QTimer m_timer;

    int sumSpeed = 0;
    int maxSpeed = 0;
    int minSpeed = 0;
    int timeNum = 0;
};

#endif // FANWIDGET_H
