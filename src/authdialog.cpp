/*
 * Copyright (C) 2013 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; version 3.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "authdialog.h"
#include "ui_authdialog.h"
#include <QDebug>
#include <QProcessEnvironment>
//QString passwd;

AuthDialog::AuthDialog(QString msg, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AuthDialog)
{
    ui->setupUi(this);
    passwd = "";
    this->setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->btn_close->installEventFilter(this);
    ui->btn_min->installEventFilter(this);
    ui->btn_close->setStyleSheet("border-image:url(:/pixmap/image/closeBtn.png)");
    ui->btn_min->setStyleSheet("border-image:url(:/pixmap/image/minBtn.png)");
    ui->okButton->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/ok.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/ok-hover.png);}");
    ui->closeButton->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/quit.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/quit-hover.png);}");


    ui->lineEdit->setEchoMode(QLineEdit::Password);
    ui->lineEdit->setFocus();

    //QLabel自动换行
    ui->msg_label->setWordWrap(true);
    ui->msg_label->setText(msg);

//    QObject::connect(ui->okButton,SIGNAL(clicked()),this,SLOT(accept()));
    QObject::connect(ui->closeButton,SIGNAL(clicked()),this,SLOT(reject()));
}

AuthDialog::~AuthDialog()
{
    delete ui;
}


bool AuthDialog::trans_password(QString flagstr, QString pwd) {
    QString cmd1 = "echo " + pwd + " | sudo -S touch /usr/bin/youker.txt";
    QByteArray ba1 = cmd1.toLatin1();
    const char *transpd = ba1.data();
    int bb = system(transpd);
    if (bb == 0) {
        QString cmd2 = "echo " + pwd + " | sudo -S rm /usr/bin/youker.txt";
        QByteArray ba2 = cmd2.toLatin1();
        const char *transpd2 = ba2.data();
        int cc = system(transpd2);
        qDebug() << cc;
        QProcess *process = new QProcess;
        process->start("/usr/bin/" + flagstr + " " + pwd);
        return true;
    }
    return false;
}

void AuthDialog::on_closeButton_clicked()
{
//    QDialog::reject();
    close();
    QDialog::destroy(true);
//    exit(0);
}

void AuthDialog::on_okButton_clicked()
{
    passwd = ui->lineEdit->text();
    if(trans_password("youkersudo", passwd))
        this->accept();
    else {
        ui->lineEdit->clear();
        ui->lineEdit->setFocus();
        ui->msg_label->setText("提示：密码错误，请重新输入当前用户登录密码，保证优客助手的正常使用。");
    }
}
