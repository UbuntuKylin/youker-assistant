#ifndef KYLINCHECKBOX_H
#define KYLINCHECKBOX_H

#include <QWidget>
#include <QLabel>
#include <QCheckBox>
#include <QPushButton>
//#include <QMouseEvent>
//#include <QHBoxLayout>
//#include <QSignalMapper>
//#include <QVBoxLayout>
//#include "../component/kylinbutton.h"
//#include "../component/kylintoolbutton.h"
//#include "../component/systembutton.h"
//#include "../component/loadinglabel.h"

//class MainWindow;

class KylinCheckBox : public QWidget
{
    Q_OBJECT
public:
    explicit KylinCheckBox(QWidget *parent = 0, const QString &picture= "");
    ~KylinCheckBox();
//    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void initConnect();
    void setLabelText(const QString &name, const QString &tip);

public slots:
    void onZoneClicked();
    void resetMainStatus(int status);

signals:
    void customButtonClicked();
    void spreadStatus(int status);

private:
    QPushButton *img_btn;
    QCheckBox *checkbox;
    QLabel *name_label;
    QLabel *description_label;
//    QPushButton *custom_btn;

//    MainWindow *p_mainwindow;
};

#endif // KYLINCHECKBOX_H
