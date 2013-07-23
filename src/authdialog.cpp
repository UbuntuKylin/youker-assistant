#include "authdialog.h"
#include "ui_authdialog.h"
#include <QDebug>
AuthDialog::AuthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
    passwd = "";
    ui->lineEdit->setFocus();
}

AuthDialog::~AuthDialog()
{
    delete ui;
}



void AuthDialog::on_quitBtn_clicked()
{
    QDialog::reject();
}

void AuthDialog::on_okBtn_clicked()
{
    qDebug() << ui->lineEdit->text();
    passwd = ui->lineEdit->text();
    QDialog::accept();
}
