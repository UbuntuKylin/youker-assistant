#ifndef AUTOSTARTWIDGET_H
#define AUTOSTARTWIDGET_H

#include <QWidget>
#include "../component/kylinlistwidget.h"
#include "../component/kylintitlebar.h"
#include "../component/autogroup.h"

class SessionDispatcher;

namespace Ui {
class AutoStartWidget;
}

class AutoStartWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AutoStartWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    ~AutoStartWidget();
    void setLanguage();
    void initConnect();
    void initData();

public slots:
    void onCloseButtonClicked();
//    void onMinButtonClicked();
    void setCurrentItemAutoStatus(QString dekstopName);
    void readyReciveData(const QStringList &data);
    void readyShowUI();

private:
    void initTitleBar();

private:
    Ui::AutoStartWidget *ui;
    SessionDispatcher *sessionproxy;
    QList<QStringList> data_list;
    KylinTitleBar *title_bar;
    QLabel *tip_label;
    QLabel *num_label;
    QLabel *name_label;
    QLabel *status_label;
};

#endif // AUTOSTARTWIDGET_H
