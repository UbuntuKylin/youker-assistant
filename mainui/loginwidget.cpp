#include "loginwidget.h"
#include "../component/kylintoolbutton.h"
#include "mainwindow.h"
#include <QDebug>

LoginWidget::LoginWidget(QWidget *parent)
	: QWidget(parent)
{
    this->setFixedSize(220, 72);
    logo_label = new QPushButton();
    logo_label->setObjectName("whiteButton");
    logo_label->setCursor(Qt::PointingHandCursor);
//    logo_label->setCursor(Qt::ArrowCursor);
//    logo_label->setCursor(Qt::SizeHorCursor);
    logo_label->setFocusPolicy(Qt::NoFocus);
    login_button = new QPushButton();
    login_button->setObjectName("loginButton");
    login_button->setCursor(Qt::PointingHandCursor);
    login_button->setFocusPolicy(Qt::NoFocus);
    login_button->setFixedSize(44, 44);
//    login_button->setIcon(QIcon("://res/logo.png"));
    login_button->setIconSize(QSize(44, 44));
    login_button->setFlat(true);
//    login_button->setStyleSheet("QPushButton{background-image: url(://res/logo.png); border: none;}"
//        "QPushButton:hover{background-image: url(://res/logo-hover.png);}"
//        "QPushButton:pressed{background-image: url(://res/logo-hover.png);}");

    QHBoxLayout *layout = new QHBoxLayout();
    layout->addWidget(logo_label, 0, Qt::AlignVCenter);
    layout->addWidget(login_button, 0, Qt::AlignVCenter);
    layout->addStretch();
    layout->setSpacing(11);
    layout->setMargin(0);
    layout->setContentsMargins(0, 0, 0, 0);

    setLayout(layout);

    is_move = false;
    this->initConnect();
    this->setLauguage();
}

LoginWidget::~LoginWidget()
{
}

void LoginWidget::initConnect()
{
    connect(logo_label, SIGNAL(clicked()), this, SLOT(onLoginButtonClicked()));
    connect(login_button, SIGNAL(clicked()), this, SLOT(onLoginButtonClicked()));
}

void LoginWidget::setLauguage()
{
    logo_label->setText(tr("Login Youker Account"));
}

void LoginWidget::onLoginButtonClicked()
{
    sessionProxy->popup_login_dialog();
}
