#include "windowwidget.h"
#include "../dbusproxy/youkersessiondbus.h"

WindowWidget::WindowWidget(QWidget *parent, SessionDispatcher *proxy) :
    QWidget(parent),
    sessionproxy(proxy)
{
//    splitter = new QSplitter();
//    splitter->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
//    splitter->setOrientation(Qt::Vertical);
//    splitter->setHandleWidth(1);

//    top_widget = new QWidget();
//    bottom_widget = new QWidget();

//    title_label = new QLabel();
//    title_label->setFixedHeight(20);
//    description_label = new QLabel();
//    description_label->setFixedHeight(20);
//    back_btn = new QPushButton();

//    QVBoxLayout *v_layout = new QVBoxLayout();
//    v_layout->addWidget(title_label);
//    v_layout->addWidget(description_label);
//    v_layout->setMargin(0);
//    v_layout->setSpacing(1);

//    QHBoxLayout *h_layout = new QHBoxLayout();
//    h_layout->addWidget(back_btn);
//    h_layout->addLayout(v_layout);
//    h_layout->addStretch();
//    top_widget->setLayout(h_layout);
//    top_widget->setFixedSize(900,60);
//    h_layout->setSpacing(20);
//    h_layout->setContentsMargins(20, 0, 0, 0);

    icon_label = new QLabel();
    wheel_label = new QLabel();
    double_click_label = new QLabel();
    middle_click_label = new QLabel();
    right_click_label = new QLabel();
    icon_switcher = new KylinSwitcher();
    wheel_combo = new QComboBox();
    double_click_combo = new QComboBox();
    middle_click_combo = new QComboBox();
    right_click_combo = new QComboBox();

    icon_label->setFixedWidth(200);
    wheel_label->setFixedWidth(200);
    double_click_label->setFixedWidth(200);
    middle_click_label->setFixedWidth(200);
    right_click_label->setFixedWidth(200);

    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->setSpacing(10);
    layout1->addWidget(icon_label);
    layout1->addWidget(icon_switcher);
    layout1->addStretch();
    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->setSpacing(10);
    layout2->addWidget(wheel_label);
    layout2->addWidget(wheel_combo);
    layout2->addStretch();
    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->setSpacing(10);
    layout3->addWidget(double_click_label);
    layout3->addWidget(double_click_combo);
    layout3->addStretch();
    QHBoxLayout *layout4 = new QHBoxLayout();
    layout4->setSpacing(10);
    layout4->addWidget(middle_click_label);
    layout4->addWidget(middle_click_combo);
    layout4->addStretch();
    QHBoxLayout *layout5 = new QHBoxLayout();
    layout5->setSpacing(10);
    layout5->addWidget(right_click_label);
    layout5->addWidget(right_click_combo);
    layout5->addStretch();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
    layout->addLayout(layout5);
    layout->addStretch();
    setLayout(layout);
    layout->setSpacing(10);
    layout->setContentsMargins(20, 20, 0, 0);

//    splitter->addWidget(top_widget);
//    splitter->addWidget(bottom_widget);

//    QHBoxLayout *main_layout = new QHBoxLayout;
//    main_layout->addStretch();
//    main_layout->addWidget(splitter);
//    main_layout->setSpacing(0);
//    main_layout->setContentsMargins(0, 0, 0, 0);
//    setLayout(main_layout);
    this->initData();
    this->setLanguage();
    this->initConnect();
}

WindowWidget::~WindowWidget()
{
//    if(label != NULL)
//    {
//        delete label;
//        label = NULL;
//    }
//    if(back_btn != NULL)
//    {
//        delete back_btn;
//        back_btn = NULL;
//    }
}

void WindowWidget::setLanguage() {
//    title_label->setText(tr("Window"));
//    description_label->setText(tr("Window Manager settings."));
//    back_btn->setText(tr("Back"));
    icon_label->setText(tr("Menu with icons") + ":");
    wheel_label->setText(tr("Titlebar mouse wheel action") + ":");
    double_click_label->setText(tr("Titlebar double-click action") + ":");
    middle_click_label->setText(tr("Titlebar middle-click action") + ":");
    right_click_label->setText(tr("Titlebar right-click action") + ":");

}

void WindowWidget::initData()
{

    icon_switcher->switchedOn = sessionproxy->get_menus_have_icons_qt();

    QString current_wheel_type = sessionproxy->get_current_titlebar_wheel_qt();
    QStringList wheellist  = sessionproxy->get_titlebar_wheel_qt();
    wheel_combo->clear();
    wheel_combo->clearEditText();
    wheel_combo->addItems(wheellist);
    QList<QString>::Iterator it1 = wheellist.begin(), itend1 = wheellist.end();
    int initIndex1 = 0;
    for(;it1 != itend1; it1++,initIndex1++)
    {
        if(*it1 == current_wheel_type)
            break;
    }
    wheel_combo->setCurrentIndex(initIndex1);

    QString current_double_type = sessionproxy->get_current_titlebar_double_qt();
    QStringList doublelist  = sessionproxy->get_titlebar_double_qt();
    double_click_combo->clear();
    double_click_combo->clearEditText();
    double_click_combo->addItems(doublelist);
    QList<QString>::Iterator it2 = doublelist.begin(), itend2 = doublelist.end();
    int initIndex2 = 0;
    for(;it2 != itend2; it2++,initIndex2++)
    {
        if(*it2 == current_double_type)
            break;
    }
    double_click_combo->setCurrentIndex(initIndex2);

    QString current_middle_type = sessionproxy->get_current_titlebar_middle_qt();
    QStringList middlelist  = sessionproxy->get_titlebar_middle_qt();
    middle_click_combo->clear();
    middle_click_combo->clearEditText();
    middle_click_combo->addItems(middlelist);
    QList<QString>::Iterator it3 = middlelist.begin(), itend3 = middlelist.end();
    int initIndex3 = 0;
    for(;it3 != itend3; it3++,initIndex3++)
    {
        if(*it3 == current_middle_type)
            break;
    }
    middle_click_combo->setCurrentIndex(initIndex3);

    QString current_right_type = sessionproxy->get_current_titlebar_right_qt();
    QStringList rightlist  = sessionproxy->get_titlebar_right_qt();
    right_click_combo->clear();
    right_click_combo->clearEditText();
    right_click_combo->addItems(rightlist);
    QList<QString>::Iterator it4 = rightlist.begin(), itend4 = rightlist.end();
    int initIndex4 = 0;
    for(;it4 != itend4; it4++,initIndex4++)
    {
        if(*it4 == current_right_type)
            break;
    }
    right_click_combo->setCurrentIndex(initIndex4);
}

void WindowWidget::initConnect() {
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
    connect(icon_switcher, SIGNAL(clicked()), this, SLOT(setMenuIcon()));
    connect(wheel_combo, SIGNAL(currentIndexChanged(QString)), this, SLOT(setMouseWheel(QString)));
    connect(double_click_combo, SIGNAL(currentIndexChanged(QString)), this, SLOT(setMouseDoubleClick(QString)));
    connect(middle_click_combo, SIGNAL(currentIndexChanged(QString)), this, SLOT(setMouseMiddleClick(QString)));
    connect(right_click_combo, SIGNAL(currentIndexChanged(QString)), this, SLOT(setMouseRightClick(QString)));
}

void WindowWidget::setMenuIcon()
{
    sessionproxy->set_menus_have_icons_qt(icon_switcher->switchedOn);

}

void WindowWidget::setMouseWheel(QString selected)
{
    sessionproxy->set_titlebar_wheel_qt(selected);
}

void WindowWidget::setMouseDoubleClick(QString selected)
{
    sessionproxy->set_titlebar_double_qt(selected);
}

void WindowWidget::setMouseMiddleClick(QString selected)
{
    sessionproxy->set_titlebar_middle_qt(selected);
}

void WindowWidget::setMouseRightClick(QString selected)
{
    sessionproxy->set_titlebar_right_qt(selected);
}
