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
#include <QCompleter>
#include <QMouseEvent>

LoginDialog::LoginDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::LoginDialog)
{
    ui->setupUi(this);

//    this->setWindowFlags(Qt::FramelessWindowHint);
//    this->setAttribute(Qt::WA_TranslucentBackground);
//    int bgW =397;
//    int bgH =282;
//    this->resize(bgW, bgH);
//    ui->frame->resize(bgW,bgH);
//    this->setWindowTitle(tr("Login"));


    this->setAttribute(Qt::WA_DeleteOnClose);
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->btn_close->installEventFilter(this);
    ui->btn_min->installEventFilter(this);
    ui->okButton->installEventFilter(this);
    ui->closeButton->installEventFilter(this);
    ui->btn_register->installEventFilter(this);
    ui->btn_close->setStyleSheet("border-image:url(:/pixmap/image/closeBtn.png)");
    ui->btn_min->setStyleSheet("border-image:url(:/pixmap/image/minBtn.png)");
    ui->okButton->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/ok.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/ok-hover.png);}");
    ui->closeButton->setStyleSheet("QPushButton {border-image:url(:/pixmap/image/quit.png);}"
                "QPushButton:hover{border-image:url(:/pixmap/image/quit-hover.png);}");
    ui->warnLabel->setStyleSheet("color: #a53205;"
                "background-color: #fcdba7");
    ui->warnLabel->setVisible(false);
    ui->pwdlineEdit->setEchoMode(QLineEdit::Password);
    ui->username->setFocus();

    loadAccountCache();
    connect(ui->username,SIGNAL(editTextChanged(QString)),this,SLOT(setPassWordForAccountCache(QString)));
}

LoginDialog::~LoginDialog()
{
    delete ui;
}

void LoginDialog::loadAccountCache()
{
    accountCache.loadFromFile();
    QStringList accountlist = accountCache.getUserName();
    QCompleter *completer = new QCompleter(accountlist, this);
    completer->setCompletionMode(QCompleter::UnfilteredPopupCompletion);
    completer->setCaseSensitivity(Qt::CaseInsensitive);
    ui->username->setCompleter(completer);
    ui->username->addItems(accountlist);
    if(!accountlist.isEmpty())
    {
        ui->username->setEditText(accountlist.last());
        QString passwd = accountCache.getPassword(accountlist.last());
        ui->pwdlineEdit->setText(passwd);
        if(!passwd.isEmpty()) {
            ui->passwdremember->setChecked(true);
        }
    }
}

void LoginDialog::on_closeButton_clicked()
{
    this->close();
}

void LoginDialog::on_okButton_clicked()
{
    QString user = ui->username->currentText();
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
            if(!ui->passwdremember->isChecked()) {
                pwd = "";
            }
            accountCache.addAccount(user, pwd);
            this->accept();
        }
    }
}

void LoginDialog::action_register()
{
    QDesktopServices::openUrl(QUrl(QLatin1String("http://www.ubuntukylin.com/ukylin/portal.php")));
}

void LoginDialog::setPassWordForAccountCache(const QString& userName)
{
    QString passwd = accountCache.getPassword(userName);
    ui->pwdlineEdit->setText(passwd);
    if(!passwd.isEmpty()) {
        ui->passwdremember->setChecked(true);
    }
}

bool LoginDialog::eventFilter(QObject *obj, QEvent *event)
{
    if(obj == ui->btn_close){
        if(event->type() == QEvent::Enter){
            ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn-hover.png"));
        }else if(event->type() == QEvent::Leave){
            ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
        }else if(event->type() == QEvent::MouseButtonPress){
            ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn-hover.png"));
        }else if(event->type() == QEvent::MouseButtonRelease){
            QMouseEvent *me = (QMouseEvent *)event;
            QLabel *lb = (QLabel *)obj;
            if(me->x() > 0 && me->x() < lb->width() && me->y() > 0 && me->y() < lb->height()){
                this->close();
                this->destroy();
            }else{
                ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
            }
        } else {
            return QObject::eventFilter(obj, event);
        }
    }
    if(obj == ui->btn_min){
        if(event->type() == QEvent::Enter){
            ui->btn_min->setPixmap(QPixmap(":/pixmap/image/minBtn-hover.png"));
        }else if(event->type() == QEvent::Leave){
            ui->btn_min->setPixmap(QPixmap(":/pixmap/image/minBtn.png"));
        }else if(event->type() == QEvent::MouseButtonPress){
            ui->btn_min->setPixmap(QPixmap(":/pixmap/image/minBtn-hover.png"));
        }else if(event->type() == QEvent::MouseButtonRelease){
            QMouseEvent *me = (QMouseEvent *)event;
            QLabel *lb = (QLabel *)obj;
            if(me->x() > 0 && me->x() < lb->width() && me->y() > 0 && me->y() < lb->height()){
                this->showMinimized();
            }else{
                ui->btn_min->setPixmap(QPixmap(":/pixmap/image/minBtn.png"));
            }
        } else {
            return QObject::eventFilter(obj, event);
        }
    }
    if(obj==ui->btn_register){
        if(event->type() == QEvent::MouseButtonRelease){
            action_register();
        }
    }
    if(obj == ui->okButton ||obj == ui->closeButton || ui->username || ui->pwdlineEdit || ui->passwdremember)
    {
        if(event->type() == QEvent::MouseButtonPress)
        {
            QMouseEvent *me = (QMouseEvent *)event;
            dragPos = me->globalPos() - frameGeometry().topLeft();
        }else if(event->type() == QEvent::MouseButtonRelease)
        {
            setWindowOpacity(1);
        }
    }
    return QObject::eventFilter(obj, event);
}

void LoginDialog::mousePressEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }
}

void LoginDialog::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton ) {
        move(event->globalPos() - dragPos);
        setWindowOpacity(1);//0.5
    }
    event->accept();

}

void LoginDialog::mouseReleaseEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        setWindowOpacity(1);
    }
    event->accept();
}
