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

private:
    QVBoxLayout *main_layout;
    QHBoxLayout *top_layout;
    QHBoxLayout *bottom_layout;
    QString Speed = "5600";
};

#endif // FANWIDGET_H
