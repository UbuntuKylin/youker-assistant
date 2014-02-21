/*
 * Copyright (C) 2013 ~ 2014 National University of Defense Technology(NUDT) & Kylin Ltd.
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
#include "logindialog.h"
#include "ui_logindialog.h"
#include <QDebug>
#include <QMessageBox>
#include <QDesktopServices>
#include <QUrl>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->btn_close->installEventFilter(this);
    ui->btn_min->installEventFilter(this);
    ui->okButton->installEventFilter(this);
    ui->closeButton->installEventFilter(this);
    ui->btn_close->setStyleSheet("border-image:url(:/pixmap/image/closeBtn.png)");
    ui->btn_min->setStyleSheet("border-image:url(:/pixmap/image/minBtn.png)");
    ui->registerButton->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/register.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/register-hover.png);}");
    ui->okButton->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/ok.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/ok-hover.png);}");
    ui->closeButton->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/quit.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/quit-hover.png);}");
    ui->warnLabel->setStyleSheet("color: #a53205;"
                "background-color: #fcdba7");
    ui->warnLabel->setVisible(false);
    ui->pwdlineEdit->setEchoMode(QLineEdit::Password);
    ui->userlineEdit->setFocus();
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::on_closeButton_clicked()
{
    this->close();
}

void LoginDialog::on_okButton_clicked()
{
    QString user = ui->userlineEdit->text();
    QString pwd = ui->pwdlineEdit->text();
    if(user.isEmpty()) {
        if(!ui->warnLabel->isVisible()) {
            ui->warnLabel->setVisible(true);
        }
        ui->warnLabel->setText(tr("Please input your username!"));
    }
    else {
        if(pwd.isEmpty()) {
            if(!ui->warnLabel->isVisible()) {
                ui->warnLabel->setVisible(true);
            }
            ui->warnLabel->setText(tr("Please input your password!"));
        }
        else {
            if(ui->warnLabel->isVisible()) {
                ui->warnLabel->setVisible(false);
            }
            ui->warnLabel->setText("");
            emit translate_user_password(user.replace(" ", ""), pwd);
            this->accept();
        }
    }
}

void LoginDialog::on_registerButton_clicked()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://www.ubuntukylin.com/ukylin/portal.php")));
}
