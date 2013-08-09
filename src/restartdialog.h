#ifndef RESTARTDIALOG_H
#define RESTARTDIALOG_H

#include <QDialog>
//#include <qfiledialog.h>
namespace Ui {
class RestartDialog;
}

class RestartDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit RestartDialog(QWidget *parent = 0);
    ~RestartDialog();
    
private:
    Ui::RestartDialog *ui;
    QPoint dragPos;
protected:
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    bool eventFilter(QObject *obj, QEvent *event);
public slots:
    void exit_youker();
};

#endif // RESTARTDIALOG_H
