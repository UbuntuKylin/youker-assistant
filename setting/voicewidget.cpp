#include "voicewidget.h"
#include "../dbusproxy/youkersessiondbus.h"
#include "../dbusproxy/youkersystemdbus.h"

VoiceWidget::VoiceWidget(QWidget *parent, SessionDispatcher *proxy , SystemDispatcher *sproxy) :
    QWidget(parent),
    sessionproxy(proxy),
    systemproxy(sproxy)
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

    theme_label = new QLabel();
    tip_label = new QLabel();
    event_label = new QLabel();
    feedback_label = new QLabel();
    theme_combo = new QComboBox();
    tip_switcher = new KylinSwitcher();
    event_switcher = new KylinSwitcher();
    feedback_switcher = new KylinSwitcher();

    theme_label->setFixedWidth(180);
    tip_label->setFixedWidth(180);
    event_label->setFixedWidth(180);
    feedback_label->setFixedWidth(180);

    QHBoxLayout *layout1 = new QHBoxLayout();
    layout1->setSpacing(10);
    layout1->addWidget(theme_label);
    layout1->addWidget(theme_combo);
    layout1->addStretch();
    QHBoxLayout *layout2 = new QHBoxLayout();
    layout2->setSpacing(10);
    layout2->addWidget(tip_label);
    layout2->addWidget(tip_switcher);
    layout2->addStretch();
    QHBoxLayout *layout3 = new QHBoxLayout();
    layout3->setSpacing(10);
    layout3->addWidget(event_label);
    layout3->addWidget(event_switcher);
    layout3->addStretch();
    QHBoxLayout *layout4 = new QHBoxLayout();
    layout4->setSpacing(10);
    layout4->addWidget(feedback_label);
    layout4->addWidget(feedback_switcher);
    layout4->addStretch();
    QVBoxLayout *layout = new QVBoxLayout();
    layout->addLayout(layout1);
    layout->addLayout(layout2);
    layout->addLayout(layout3);
    layout->addLayout(layout4);
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

VoiceWidget::~VoiceWidget()
{

}

void VoiceWidget::setLanguage() {
//    title_label->setText(tr("Sound effect"));
//    description_label->setText(tr("Set the sound theme you want."));
//    back_btn->setText(tr("Back"));
    theme_label->setText(tr("Sound theme") + ":");
    tip_label->setText(tr("Login tone") + ":");
    event_label->setText(tr("Event sounds") + ":");
    feedback_label->setText(tr("Input feedback sounds") + ":");

}


void VoiceWidget::initData()
{
    QString current_sound = sessionproxy->get_sound_theme_qt();
    QStringList soundlist  = systemproxy->get_sound_themes_qt();
    theme_combo->clear();
    theme_combo->clearEditText();
    theme_combo->addItems(soundlist);

    QList<QString>::Iterator it = soundlist.begin(), itend = soundlist.end();
    int initIndex = 0;
    for(;it != itend; it++,initIndex++)
    {
        if(*it == current_sound)
            break;
    }
    theme_combo->setCurrentIndex(initIndex);

    tip_switcher->switchedOn = sessionproxy->get_login_music_enable_qt();
    event_switcher->switchedOn = sessionproxy->get_sound_event_enable_qt();
    feedback_switcher->switchedOn = sessionproxy->get_input_feedback_sounds_enable_qt();
}

void VoiceWidget::initConnect() {
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
    connect(theme_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setVoiceTheme(QString)));
    connect(tip_switcher, SIGNAL(clicked()),  this, SLOT(setLoginTipVoice()));
    connect(event_switcher, SIGNAL(clicked()),  this, SLOT(setEventVoice()));
    connect(feedback_switcher, SIGNAL(clicked()),  this, SLOT(setInputFeedbackVoice()));
}

void VoiceWidget::setVoiceTheme(QString selectTheme) {
    sessionproxy->set_sound_theme_qt(selectTheme);
}

void VoiceWidget::setLoginTipVoice() {
    sessionproxy->set_login_music_enable_qt(tip_switcher->switchedOn);
}

void VoiceWidget::setEventVoice() {
    sessionproxy->set_sound_event_enable_qt(event_switcher->switchedOn);
}

void VoiceWidget::setInputFeedbackVoice() {
    sessionproxy->set_input_feedback_sounds_enable_qt(feedback_switcher->switchedOn);
}
