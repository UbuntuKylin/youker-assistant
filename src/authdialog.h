#ifndef AUTHDIALOG_H
#define AUTHDIALOG_H

#include <QDialog>

namespace Ui {
class AuthDialog;
}

class AuthDialog : public QDialog
{
    Q_OBJECT
    
public:
    explicit AuthDialog(QWidget *parent = 0);
    ~AuthDialog();
    QString passwd;
    
private:
    Ui::AuthDialog *ui;

private slots:
    void on_quitBtn_clicked();
    void on_okBtn_clicked();
};

#endif // AUTHDIALOG_H
