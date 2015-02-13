#ifndef TOUCHPADWIDGET_H
#define TOUCHPADWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSplitter>
#include <QRadioButton>
#include "../component/kylinswitcher.h"
class SessionDispatcher;

class TouchpadWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TouchpadWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    ~TouchpadWidget();
    void setLanguage();
    void initConnect();
    void initData();

//signals:
//    void showSettingMainWidget();

public slots:
    void setRadioButtonRowStatus(/*bool status*/);
    void setTouchpad();
    void setHorizontalScrolling();

private:
    SessionDispatcher *sessionproxy;
//    QSplitter *splitter;
//    QWidget * top_widget;
//    QWidget * bottom_widget;

//    QPushButton *back_btn;
//    QLabel *title_label;
//    QLabel *description_label;

    QLabel *touchpad_label;
    QLabel *horizontal_scrolling_label;
    QLabel *scrollbar_type_label;
    QLabel *panel_layout_label;
    KylinSwitcher *touchpad_switcher;
    KylinSwitcher *horizontal_scrolling_switcher;
    QRadioButton *features_radio;
    QRadioButton *standard_radio;
    QRadioButton *edge_radio;
    QRadioButton *two_finger_radio;
};

#endif // TOUCHPADWIDGET_H
