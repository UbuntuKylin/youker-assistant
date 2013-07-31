#include "authdialog.h"
#include "ui_authdialog.h"
#include <QDebug>

QString passwd;

AuthDialog::AuthDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->btn_close->installEventFilter(this);
    ui->btn_min->installEventFilter(this);
    ui->btn_close->setStyleSheet("border-image:url(:/pixmap/image/closeBtn.png)");
    ui->btn_min->setStyleSheet("border-image:url(:/pixmap/image/minBtn.png)");

    ui->lineEdit->setEchoMode(QLineEdit::Password);
    ui->lineEdit->setFocus();

    QObject::connect(ui->okButton,SIGNAL(clicked()),this,SLOT(accept()));
    QObject::connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(reject()));
}

AuthDialog::~AuthDialog()
{
    delete ui;
}

void AuthDialog::on_closeButton_clicked()
{
//    QDialog::reject();
    close();
    QDialog::destroy(true);
    exit(0);
}

void AuthDialog::on_okButton_clicked()
{
    passwd = ui->lineEdit->text();
    if (passwd == "")
        exit(0);
}
