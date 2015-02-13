#ifndef CLEANERMAINWIDGET_H
#define CLEANERMAINWIDGET_H

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
#include "../component/kylincheckbox.h"

#include <QCheckBox>
#include "cleaneritems.h"

class MainWindow;
class CleanerMainWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CleanerMainWidget(QWidget *parent = 0, MainWindow *window = 0);
    ~CleanerMainWidget();
    void setLanguage();

public slots:
    void onButtonClicked();

private:
//    QList<QCheckBox *> checkbox_list;
    MainWindow *parentWindow;
    QLabel *tip_label;
//    QCheckBox *main_checkbox;

    KylinCheckBox *cache_btn;
    CleanerItems *cache_items;
    KylinCheckBox *package_btn;
    CleanerItems *package_items;
    KylinCheckBox *cookies_btn;
    CleanerItems *cookies_items;
//    KylinCheckBox *browser_btn;
    CleanerItems *browser_items;
    KylinCheckBox *trace_btn;
    CleanerItems *trace_items;

};

#endif // CLEANERMAINWIDGET_H




