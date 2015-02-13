#ifndef CAMERAMANAGER_H
#define CAMERAMANAGER_H

#include <QDialog>

#include "../component/kylinlistwidget.h"
#include "../component/kylintitlebar.h"
#include "../component/kylinlistwidgetitem.h"

class SessionDispatcher;
class MainWindow;
class CameraManager :public QDialog
{
  Q_OBJECT
public:
    CameraManager(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    ~CameraManager();
    void setParentWindow(MainWindow *From) { mainwindow = From;}
    void initBackgroundList();
    void setLanguage();
    void initConnect();
    void setOKButtonEnable(bool enable);

public slots:
    void onCloseButtonClicked();
    void onOKButtonClicked();
    void onViewButtonClicked();

private:
    void initTitleBar();

private:
    MainWindow *mainwindow;
    SessionDispatcher *sessionproxy;
    KylinTitleBar *title_bar;
    QLabel *msg_label;
    QLabel *tip_label;
    QLabel *description_label;
    QPushButton *okBtn;
    QPushButton *viewBtn;
};

#endif // CAMERAMANAGER_H
