#ifndef WINDOWWIDGET_H
#define WINDOWWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>
#include "../component/kylinswitcher.h"
#include <QSplitter>
class SessionDispatcher;

class WindowWidget : public QWidget
{
    Q_OBJECT
public:
    explicit WindowWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    ~WindowWidget();
    void setLanguage();
    void initConnect();
    void initData();

//signals:
//    void showSettingMainWidget();

public slots:
    void setMenuIcon();
    void setMouseWheel(QString selected);
    void setMouseDoubleClick(QString selected);
    void setMouseMiddleClick(QString selected);
    void setMouseRightClick(QString selected);

private:
    SessionDispatcher *sessionproxy;
//    QSplitter *splitter;
//    QWidget * top_widget;
//    QWidget * bottom_widget;

//    QPushButton *back_btn;
//    QLabel *title_label;
//    QLabel *description_label;

    QLabel *icon_label;
    QLabel *wheel_label;
    QLabel *double_click_label;
    QLabel *middle_click_label;
    QLabel *right_click_label;
    KylinSwitcher *icon_switcher;
    QComboBox *wheel_combo;
    QComboBox *double_click_combo;
    QComboBox *middle_click_combo;
    QComboBox *right_click_combo;

};

#endif // WINDOWWIDGET_H
