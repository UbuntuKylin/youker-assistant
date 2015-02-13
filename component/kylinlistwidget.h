//#pragma once
#ifndef KYLINLISTWIDGET_H
#define KYLINLISTWIDGET_H

#include <QListWidget>
class MainWindow;

class KylinListWidget : public QListWidget
{
    Q_OBJECT
public:
    KylinListWidget(QWidget *parent = 0);
    ~KylinListWidget();
    void setMainWindow(MainWindow* window) { mainwindow = window;}

public slots:
    void onItemClicked(QListWidgetItem *item);

protected:
    virtual void	enterEvent (QEvent  *event);
    virtual void	leaveEvent (QEvent *event);
    virtual void mouseMoveEvent(QMouseEvent *event);
    virtual void moveEvent(QMoveEvent *event);

private:
    MainWindow *mainwindow;
};

#endif // KYLINLISTWIDGET_H
