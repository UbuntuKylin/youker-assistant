#pragma once

#include <QListWidgetItem>
#include <QPainter>
class MainWindow;

class KylinListWidgetItem :public QListWidgetItem
{
public:
    KylinListWidgetItem(const QIcon &icon, const QString &text, QListWidget *view = 0, int type = Type);
    ~KylinListWidgetItem();
    void setPress(bool flag);
    void setOver(bool flag);
    void painter();
    void setMainWindow(MainWindow *window) { mainwindow = window; }
    void setSkinName(QString picture) {point_skin = picture;}
    QString getSkinName() {return point_skin;}

private:
    bool is_over;
    bool is_press;
    MainWindow *mainwindow;
    QString point_skin;
};
