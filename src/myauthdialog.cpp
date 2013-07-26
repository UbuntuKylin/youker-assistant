#include "myauthdialog.h"
#include "ui_myauthdialog.h"

MyauthDialog::MyauthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MyauthDialog)
{
    ui->setupUi(this);
    setView();
}

MyauthDialog::~MyauthDialog()
{
    delete ui;
}
