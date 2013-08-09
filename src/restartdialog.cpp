#include "restartdialog.h"
#include "ui_restartdialog.h"
#include <QMouseEvent>
//#include <sys/types.h>
//#include <unistd.h>
//#include <stdlib.h>
//#include <stdio.h>
//#include <string.h>
//#include <stdio.h>

//#include <errno.h>
//#include <sys/wait.h>
RestartDialog::RestartDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::RestartDialog)
{
    ui->setupUi(this);
    this->setAttribute(Qt::WA_DeleteOnClose);//防止内存泄漏
    this->setWindowFlags(Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    ui->btn_close->installEventFilter(this);
    ui->btn_close->setStyleSheet("border-image:url(:/pixmap/image/closeBtn.png)");
    //QLabel自动换行
    ui->displaylabel->setWordWrap(true);
    ui->displaylabel->setText("您系统上的优客助手是第一次启动相关服务，请点击“确认”按钮关闭，然后重启优客助手。");
//    ui->displaylabel->setAlignment(Qt::AlignTop);
    QObject::connect(ui->okButton,SIGNAL(clicked()),this,SLOT(exit_youker()));
}

RestartDialog::~RestartDialog()
{
    delete ui;
}

void RestartDialog::exit_youker() {
    exit(0);
}

bool RestartDialog::eventFilter(QObject *obj, QEvent *event)
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
                    exit(0);
                }else{
                    ui->btn_close->setPixmap(QPixmap(":/pixmap/image/closeBtn.png"));
                }
            } else {
                return QObject::eventFilter(obj, event);
            }
        }
    return QObject::eventFilter(obj, event);


}

void RestartDialog::mousePressEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        dragPos = event->globalPos() - frameGeometry().topLeft();
        event->accept();
    }

}

void RestartDialog::mouseMoveEvent(QMouseEvent *event)
{
    if (event->buttons() & Qt::LeftButton )
    {
        move(event->globalPos() - dragPos);
        setWindowOpacity(0.5);
    }
    event->accept();

}

void RestartDialog::mouseReleaseEvent(QMouseEvent *event)
{
    if (event->button() == Qt::LeftButton)
    {
        setWindowOpacity(1);
    }
    event->accept();
}
