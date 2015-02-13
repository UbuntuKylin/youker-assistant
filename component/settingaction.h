#ifndef SETTINGACTION_H
#define SETTINGACTION_H

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

//class MainWindow;

class SettingAction : public QWidget
{
    Q_OBJECT
public:
    explicit SettingAction(QWidget *parent = 0);
    ~SettingAction();
//    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void setLanguage(int index);

signals:
    void showSettingMainWidget();

private:
    QPushButton *back_btn;
    QLabel *img_label;
    QLabel *title_label;
//    QLabel *description_label;
//    MainWindow *p_mainwindow;
};

#endif // SETTINGACTION_H
