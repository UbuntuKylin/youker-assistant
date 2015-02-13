#ifndef SETTINGACTIONWIDGET_H
#define SETTINGACTIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QMouseEvent>
#include <QHBoxLayout>
#include <QSignalMapper>
#include <QVBoxLayout>
#include "../component/kylinbutton.h"
#include "../component/kylintoolbutton.h"
#include "../component/systembutton.h"
#include "../component/loadinglabel.h"
#include <QStackedWidget>

#include "../component/settingaction.h"

class MainWindow;

class SettingActionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SettingActionWidget(QWidget *parent = 0);
    ~SettingActionWidget();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void setLanguage();
    void initConnect();

public slots:
    void displayActionMainPage();
    void displayActionSubPage(int index);

signals:
    void notifyContentPageToMain();

private:
    QLabel *img_label;
    QLabel *title_label;
//    QLabel *description_label;
    QStackedWidget *stacked_widget;
    QWidget *main_acion;
    SettingAction *theme_action;
    SettingAction *icon_action;
    SettingAction *mouse_action;
    SettingAction *voice_action;
    SettingAction *animation_action;
    SettingAction *launcher_action;
    SettingAction *panel_action;
    SettingAction *window_action;
    SettingAction *font_action;
    SettingAction *touchpad_action;
    SettingAction *deadpixel_action;
    SettingAction *nautilus_action;

    MainWindow *p_mainwindow;
};

#endif // SETTINGACTIONWIDGET_H
