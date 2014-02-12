#ifndef CHANGECITYDIALOG_H
#define CHANGECITYDIALOG_H

#include <QDialog>
//#include "sessiondispatcher.h"
class QSettings;
namespace Ui {
class ChangeCityDialog;
}

class ChangeCityDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit ChangeCityDialog(QSettings *mSettings = 0, QWidget *parent = 0);
    ~ChangeCityDialog();
    void init();
    
private:
    Ui::ChangeCityDialog *ui;

    QSettings *pSettings;
    QPoint dragPos;
//    SessionDispatcher *sedispather;

protected slots:
    void writeWeatherConf();

protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
signals:
    void readyToUpdateWeather();
};

#endif // CHANGECITYDIALOG_H
