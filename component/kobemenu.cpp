#include "kobemenu.h"
#include "../mainui/mainwindow.h"
#include <QVBoxLayout>

KobeMenu::KobeMenu(QWidget *parent) :
    QWidget(parent)
{
    this->createActions();
    this->setLanguage();
}

void KobeMenu::createActions()
{
    help_action = new QToolButton(this);
    features_action = new QToolButton(this);
    feedback_action = new QToolButton(this);
    setting_action = new QToolButton(this);
    about_action = new QToolButton(this);
    help_action->setIcon(QIcon(":/tool/res/menu/help.png"));
    help_action->setIconSize(QPixmap(":/tool/res/menu/help.png").size());
    features_action->setIcon(QIcon(":/tool/res/menu/features.png"));
    features_action->setIconSize(QPixmap(":/tool/res/menu/features.png").size());
    feedback_action->setIcon(QIcon(":/tool/res/menu/feedback.png"));
    feedback_action->setIconSize( QPixmap(":/tool/res/menu/feedback.png").size());
    setting_action->setIcon(QIcon(":/tool/res/menu/setup.png"));
    setting_action->setIconSize( QPixmap(":/tool/res/menu/setup.png").size());
    about_action->setIcon(QIcon(":/tool/res/menu/about.png"));
    about_action->setIconSize( QPixmap(":/tool/res/menu/about.png").size());

    QVBoxLayout *layout = new QVBoxLayout();
    layout->addWidget(help_action/*, 0, Qt::AlignTop*/);
    layout->addWidget(features_action);
    layout->addWidget(feedback_action);
    layout->addWidget(setting_action);
    layout->addWidget(about_action/*, 0, Qt::AlignBottom*/);

    layout->setMargin(0);
    layout->setSpacing(5);
    layout->setContentsMargins(5, 5, 5, 5);

    this->setLayout(layout);
}

void KobeMenu::setLanguage() {
    help_action->setText(tr("Forum Help"));
    features_action->setText(tr("Features"));
    feedback_action->setText(tr("Feedback"));
    setting_action->setText(tr("Set up"));
    about_action->setText(tr("About us"));
}

void KobeMenu::initConnect()
{
    connect(help_action, SIGNAL(clicked()), this, SLOT(forumHelp()));
    connect(help_action, SIGNAL(clicked()), p_mainwindow, SLOT(newFeatures()));
    connect(help_action, SIGNAL(clicked()), p_mainwindow, SLOT(questionFeedback()));
    connect(help_action, SIGNAL(clicked()), p_mainwindow, SLOT(setupConfigure()));
    connect(help_action, SIGNAL(clicked()), p_mainwindow, SLOT(aboutUs()));
}

void KobeMenu::forumHelp()
{
    QUrl url(QString("http://www.ubuntukylin.com/ukylin/forum.php"));
    QDesktopServices::openUrl(url);
}
