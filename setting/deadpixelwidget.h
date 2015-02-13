#ifndef DEADPIXELWIDGET_H
#define DEADPIXELWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "../component/quibo.h"
#include <QSplitter>

class DeadpixelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DeadpixelWidget(QWidget *parent = 0);
    ~DeadpixelWidget();
    void setLanguage();
    void initConnect();

//signals:
//    void showSettingMainWidget();

public slots:
    void startMonitorCheck();

private:
//    QSplitter *splitter;
//    QWidget * top_widget;
//    QWidget * bottom_widget;
//    QWidget * left_widget;
//    QWidget * right_widget;

//    QPushButton *back_btn;
//    QLabel *title_label;
//    QLabel *description_label;

    QUIBO *qtui;
    QLabel *tip_label;
    QPushButton *ok_btn;
};

#endif // DEADPIXELWIDGET_H
