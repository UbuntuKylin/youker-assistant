#include "alertdialog.h"
#include "ui_alertdialog.h"

AlertDialog::AlertDialog(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AlertDialog)
{
    ui->setupUi(this);
    this->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    this->setAttribute(Qt::WA_TranslucentBackground);
    connect(ui->alertBG,SIGNAL(clicked()),this,SLOT(hide()));
    ui->alertBG->setStyleSheet("QPushButton{background-image:url(':/pixmap/image/alert.png');border:0px;padding-top:-10px;}");
    ui->alertBG->setFocusPolicy(Qt::NoFocus);
//    this->hide();
}

AlertDialog::~AlertDialog()
{
    delete ui;
}

void AlertDialog::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QStyleOption opt;
    opt.init(this);
    style()->drawPrimitive(QStyle::PE_Widget, &opt, &painter, this);
}

void AlertDialog::setMSG(QString msg)
{
    ui->alertBG->setText(msg);
}
