#ifndef CLEANERITEMS_H
#define CLEANERITEMS_H

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
#include "../component/kylincheckbox.h"
#include "../component/kylintitlebar.h"

#include <QCheckBox>
#include <QGroupBox>

class MainWindow;
class CleanerItems : public QWidget
{
    Q_OBJECT
public:
    explicit CleanerItems(QStringList &arglist, int height = 0, const QString title_text = "UbuntuKylin", QWidget *parent = 0);
    ~CleanerItems();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}
    void setLanguage();
    void initConnect();
    int getItemCount();
    QStringList getSelectedItems();

public slots:
    void resetSubCheckbox(int status);
    void scanAllSubCheckbox();
    void onCloseButtonClicked();

private:
    void initTitleBar();

signals:
    void notifyMainCheckBox(int status);

private:
    QList<QCheckBox *> checkbox_list;
    MainWindow *p_mainwindow;
    KylinTitleBar *title_bar;
    QString titleName;
    QPushButton *okBtn;
    QGroupBox *group_box;
//    QCheckBox *checkbox1;
//    QCheckBox *checkbox2;
//    QCheckBox *checkbox3;
//    int widgetHeight;
};

#endif // CLEANERITEMS_H




