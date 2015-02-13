#include "titlewidget.h"
#include "../component/kylintoolbutton.h"
#include "mainwindow.h"

TitleWidget::TitleWidget(QWidget *parent)
	: QWidget(parent)
{
    min_button = new SystemButton();
    close_button = new SystemButton();
    skin_button = new SystemButton();
    main_menu_button = new SystemButton();
    min_button->loadPixmap(":/sys/res/sysBtn/min_button.png");
    close_button->loadPixmap(":/sys/res/sysBtn/close_button.png");
    skin_button->loadPixmap(":/sys/res/sysBtn/skin_button.png");
    main_menu_button->loadPixmap(":/sys/res/sysBtn/main_menu.png");

    QHBoxLayout *title_layout = new QHBoxLayout();
    title_layout->addWidget(close_button, 0, Qt::AlignTop);
    title_layout->addWidget(min_button, 0, Qt::AlignTop);
    title_layout->addWidget(skin_button, 0, Qt::AlignTop);
    title_layout->addWidget(main_menu_button, 0, Qt::AlignTop);
    title_layout->addStretch();
	title_layout->setSpacing(0);
    title_layout->setContentsMargins(0, 0, 5, 0);

	QVBoxLayout *main_layout = new QVBoxLayout();
	main_layout->addLayout(title_layout);
	main_layout->setSpacing(0);
	main_layout->setContentsMargins(0, 0, 0, 0);

    setLayout(main_layout);
    this->setFixedSize(900, 36);
    is_move = false;
}

TitleWidget::~TitleWidget()
{
    if(min_button != NULL)
    {
        delete min_button;
        min_button = NULL;
    }
    if(close_button != NULL)
    {
        delete close_button;
        close_button = NULL;
    }
    if(skin_button != NULL)
    {
        delete skin_button;
        skin_button = NULL;
    }
    if(main_menu_button != NULL)
    {
        delete main_menu_button;
        main_menu_button = NULL;
    }
}

void TitleWidget::initConnect() {
    connect(min_button, SIGNAL(clicked()), p_mainwindow, SLOT(showMinimized()));
    connect(close_button, SIGNAL(clicked()), this, SIGNAL(closeApp()));
    connect(skin_button, SIGNAL(clicked()), p_mainwindow, SLOT(openSkinCenter()));
    connect(main_menu_button, SIGNAL(clicked()), p_mainwindow, SLOT(showMainMenu()));
}
