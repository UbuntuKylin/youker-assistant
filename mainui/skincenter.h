//#pragma once
//#include "ui_ChangeSkin.h"
#ifndef SKINCENTER_H
#define SKINCENTER_H

#include <QDialog>

#include "../component/kylinlistwidget.h"
#include "../component/kylintitlebar.h"
#include "../component/kylinlistwidgetitem.h"

class MainWindow;
//class KylinTitleBar;
class SkinCenter :public QDialog
{
  Q_OBJECT
public:
    SkinCenter(QWidget *parent = 0, Qt::WindowFlags f = 0);
    ~SkinCenter();
    void setParentWindow(MainWindow *From) { mainwindow = From;}
    void initBackgroundList();
    void setLanguage();
    void initConnect();

public slots:
    void onCloseButtonClicked();
//    void onMinButtonClicked();

protected:
    void closeEvent(QCloseEvent *event);

private:
    void initTitleBar();

private:
//    Ui::Dialog  m_Dlg;
    MainWindow *mainwindow;
    KylinTitleBar *title_bar;
    KylinListWidget *list_widget;
};

#endif // SKINCENTER_H
