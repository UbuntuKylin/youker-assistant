#ifndef FCITXWARNDIALOG_H
#define FCITXWARNDIALOG_H

#include <QDialog>
#include <fcitxwarndialog.h>

namespace Ui {
class FcitxWarnDialog;
}

class FcitxWarnDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit FcitxWarnDialog(QWidget *parent = 0);
    ~FcitxWarnDialog();
public:
    bool eventFilter(QObject *obj, QEvent *event);

signals:
    void fcitxWarntest();
public slots:
    void on_okButton_clicked();

private:
    Ui::FcitxWarnDialog *ui;
};

#endif // FCITXWARNDIALOG_H




