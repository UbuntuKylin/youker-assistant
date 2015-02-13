#include "homepage.h"
//#include "../component/commontoolbutton.h"
#include <QSignalMapper>
#include <QDebug>
#include "mainwindow.h"

HomePage::HomePage(QWidget *parent) :
    QWidget(parent)
{
    this->setFixedSize(900, 326);

    //set white background color
    this->setAutoFillBackground(true);
    QPalette palette;
    palette.setBrush(QPalette::Window, QBrush(Qt::white));
    this->setPalette(palette);

////    QPixmap label_pixmap("");
////    movie_label->setPixmap(label_pixmap);
////    movie_label->setFixedSize(label_pixmap.size());

//    scan_button->setFocusPolicy(Qt::NoFocus);
//    QPixmap pixmap("://res/scan.png");
//    scan_button->setIcon(pixmap);
//    scan_button->setIconSize(pixmap.size());

    version_logo = new QLabel();
    version_title = new QLabel();
    version_tip = new QLabel();
    check_btn = new QPushButton();
    box_logo = new QLabel();
    box_title = new QLabel();
    box_tip = new QLabel();
    more_text_btn = new QPushButton();
    more_btn = new QPushButton();

    auto_start = NULL;
    camera_manager = NULL;

//    software_btn = new CommonToolButton();
//    boot_btn = new CommonToolButton();
//    camera_btn = new CommonToolButton();
//    more_text_btn->setAlignment(Qt::AlignCenter);
    more_text_btn->setObjectName("checkButton");
    more_text_btn->setCursor(Qt::PointingHandCursor);
    more_text_btn->setFocusPolicy(Qt::NoFocus);
    check_btn->setObjectName("checkButton");
    check_btn->setCursor(Qt::PointingHandCursor);
    check_btn->setFocusPolicy(Qt::NoFocus);
    version_title->setObjectName("bigblackLabel");
    box_title->setObjectName("bigblackLabel");
    version_tip->setAlignment(Qt::AlignLeft);
    version_tip->setObjectName("smallgrayLabel");
    box_tip->setAlignment(Qt::AlignLeft);
    box_tip->setObjectName("smallgrayLabel");
    version_tip->setWordWrap(true);//QLabel自动换行
    box_tip->setWordWrap(true);//QLabel自动换行
    more_btn->setObjectName("transparentButton");
    more_btn->setCursor(Qt::PointingHandCursor);

    version_logo->setFixedSize(65, 65);
    version_logo->setPixmap(QPixmap("://res/version.png"));
    box_logo->setFixedSize(65, 65);
    box_logo->setPixmap(QPixmap("://res/box.png"));



    this->setLanguage();
}

HomePage::~HomePage()
{
    if(auto_start != NULL)
    {
        delete auto_start;
        auto_start = NULL;
    }
    if(camera_manager != NULL)
    {
        delete camera_manager;
        camera_manager = NULL;
    }
}

void HomePage::initUI()
{
    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->addWidget(version_title);
    layout1->addWidget(check_btn);
    layout1->addStretch();
    layout1->setMargin(0);
    layout1->setSpacing(5);
    layout1->setContentsMargins(0,0,0,0);
    QVBoxLayout *layout2 = new QVBoxLayout();
    layout2->addStretch();
    layout2->addLayout(layout1);
    layout2->addWidget(version_tip);
    layout2->addStretch();
    layout2->setMargin(0);
    layout2->setSpacing(5);
    layout2->setContentsMargins(0,0,0,0);
    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->addWidget(version_logo/* ,0, Qt::AlignVCenter*/);
    layout3->addLayout(layout2);
    layout3->addStretch();
    layout3->setMargin(0);
    layout3->setSpacing(5);
    layout3->setContentsMargins(0,0,0,0);

    QVBoxLayout *layout4 = new QVBoxLayout();
    layout4->addStretch();
    layout4->addWidget(box_title);
    layout4->addWidget(box_tip);
    layout4->addStretch();
    layout4->setMargin(0);
    layout4->setSpacing(5);
    layout4->setContentsMargins(0,0,0,0);




    QStringList icon_list;
//    icon_list<<"://res/ubuntukylin-software-center"<<"://res/boot"<<"://res/camera";
    icon_list<<"://res/boot"<<"://res/camera";
    QStringList text_list;
//    text_list<< tr("Youker Softeware Center") << tr("Boot Manager") << tr("Camera");
    text_list << tr("Boot Manager") << tr("Camera");
    QHBoxLayout *button_layout = new QHBoxLayout();
    QSignalMapper *signal_mapper = new QSignalMapper(this);
    for(int i=0; i<icon_list.size(); i++)
    {
        QToolButton *tool_button = new QToolButton();
        tool_button->setFocusPolicy(Qt::NoFocus);
        tool_button->setText(text_list.at(i));
        tool_button->setIcon(QIcon(icon_list.at(i)));
        tool_button->setIconSize(QPixmap(icon_list.at(i)).size());
        tool_button->setAutoRaise(true);
        tool_button->setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
        tool_button->setObjectName("commonToolButton");
        tool_button->setFixedSize(110, 110);
//        tool_button->setContentsMargins(0, 20, 0, 30);

        button_list.append(tool_button);
        connect(tool_button, SIGNAL(clicked()), signal_mapper, SLOT(map()));
        signal_mapper->setMapping(tool_button, QString::number(i, 10));
        button_layout->addWidget(tool_button, 0, Qt::AlignBottom);
    }
    connect(signal_mapper, SIGNAL(mapped(QString)), this, SLOT(switchPageIndex(QString)));


    more_btn->setFocusPolicy(Qt::NoFocus);
    QPixmap pixmap("://res/more.png");
    more_btn->setIcon(pixmap);
    more_btn->setIconSize(pixmap.size());

    QVBoxLayout *more_layout = new QVBoxLayout();
    more_layout->addStretch();
    more_layout->addWidget(more_btn);
    more_layout->addWidget(more_text_btn);
    more_layout->addStretch();
    more_layout->setSpacing(0);
    more_layout->setMargin(0);
    more_layout->setContentsMargins(0, 0, 0, 0);

    button_layout->addStretch();
    button_layout->addLayout(more_layout);
//    button_layout->addWidget(more_btn, 0, Qt::AlignTop);
    button_layout->setSpacing(20);
    button_layout->setMargin(0);
    button_layout->setContentsMargins(0, 0, 0, 0);

    QHBoxLayout *layout5 = new QHBoxLayout();
    layout5->addWidget(box_logo);
    layout5->addLayout(layout4);
    layout5->addStretch();
    layout5->addLayout(button_layout);
    layout5->setMargin(0);
    layout5->setSpacing(5);
    layout5->setContentsMargins(0,0,0,0);



    QVBoxLayout *main_layout = new QVBoxLayout();
    main_layout->addLayout(layout3);
    main_layout->addLayout(layout5);
    main_layout->setMargin(0);
    main_layout->setSpacing(50);
    main_layout->setContentsMargins(60,50,60,80);

    this->setLayout(main_layout);
}

void HomePage::initConnect()
{
    connect(more_btn, SIGNAL(clicked()), p_mainwindow, SLOT(showBoxWidget()));
    connect(more_btn, SIGNAL(clicked()), p_mainwindow, SIGNAL(chanegBoxToolStatus()));
    connect(more_text_btn, SIGNAL(clicked()), p_mainwindow, SLOT(showBoxWidget()));
    connect(more_text_btn, SIGNAL(clicked()), p_mainwindow, SIGNAL(chanegBoxToolStatus()));
}

void HomePage::setLanguage()
{
    version_title->setText(tr("Current Version Number") + "    " + "V2.0.0");
    version_tip->setText(tr("Update to the lastest version, make it work better"));
    check_btn->setText(tr("Check new version"));
    box_title->setText(tr("Common toolbox"));
    box_tip->setText(tr("Fast and practical, making the system more personalized"));
    more_text_btn->setText(tr("More"));
    more_btn->setToolTip(tr("More"));
}

void HomePage::initBoxTool()
{

}

void HomePage::switchPageIndex(QString index)
{
//    bool ok;
//    int current_index = index.toInt(&ok, 10);
//    qDebug() << index;

    if(index == "0")
    {
        if(auto_start == NULL) {
            auto_start = new AutoStartWidget(0, sessionProxy);
            connect(sessionProxy, SIGNAL(tellAutoModel(QStringList)), auto_start, SLOT(readyReciveData(QStringList)));
            connect(sessionProxy, SIGNAL(showAutoModel()), auto_start, SLOT(readyShowUI()));
            auto_start->initData();
            int w_x = p_mainwindow->frameGeometry().topLeft().x() + (900 / 2) - (560  / 2);
            int w_y = p_mainwindow->frameGeometry().topLeft().y() + (600 /2) - (398  / 2);
            auto_start->move(w_x, w_y);
            auto_start->show();
            auto_start->raise();
        }
        else {
            int w_x = p_mainwindow->frameGeometry().topLeft().x() + (900 / 2) - (560  / 2);
            int w_y = p_mainwindow->frameGeometry().topLeft().y() + (600 /2) - (398  / 2);
            auto_start->move(w_x, w_y);
            auto_start->show();
            auto_start->raise();
        }
    }

    else if(index == "1")
    {
        if(camera_manager == NULL) {
            camera_manager = new CameraManager(0, sessionProxy);
            if(sessionProxy->judge_camera_qt())
            {
                camera_manager->setOKButtonEnable(true);
            }
            else{
                camera_manager->setOKButtonEnable(false);
            }
            int w_x = p_mainwindow->frameGeometry().topLeft().x() + (900 / 2) - (524  / 2);
            int w_y = p_mainwindow->frameGeometry().topLeft().y() + (600 /2) - (277  / 2);
            camera_manager->move(w_x, w_y);
            camera_manager->show();
            camera_manager->raise();
        }
        else {
            int w_x = p_mainwindow->frameGeometry().topLeft().x() + (900 / 2) - (524  / 2);
            int w_y = p_mainwindow->frameGeometry().topLeft().y() + (600 /2) - (277  / 2);
            camera_manager->move(w_x, w_y);
            camera_manager->show();
            camera_manager->raise();
        }
    }
//    for(int i=0; i<button_list.count(); i++)
//    {
////        CommonToolButton *tool_button = button_list.at(i);
//        QToolButton *tool_button = button_list.at(i);
//        if(current_index == i)
//        {
//            tool_button->setMousePress(true);
//        }
//        else
//        {
//            tool_button->setMousePress(false);
//        }
//    }
}
