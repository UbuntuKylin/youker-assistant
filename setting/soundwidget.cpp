/*
 * Copyright (C) 2013 ~ 2015 National University of Defense Technology(NUDT) & Kylin Ltd.
 *
 * Authors:
 *  Kobe Lee    xiangli@ubuntukylin.com/kobe24_lixiang@126.com
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

#include "soundwidget.h"
#include <QLabel>
#include <QComboBox>
#include <QHBoxLayout>

SoundWidget::SoundWidget(QWidget *parent, QString cur_desktop) :
    SettingModulePage(parent),desktop(cur_desktop)
{
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

    if (this->desktop == "mate" || this->desktop == "MATE" || this->desktop == "UKUI" || this->desktop == "ukui")
    {
        tip_label->hide();
        tip_switcher->hide();
    }

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
//    this->initSettingData();
    this->setLanguage();
}

SoundWidget::~SoundWidget()
{
    if (theme_label != NULL) {
        delete theme_label;
        theme_label = NULL;
    }
    if (tip_label != NULL) {
        delete tip_label;
        tip_label = NULL;
    }
    if (event_label != NULL) {
        delete event_label;
        event_label = NULL;
    }
    if (feedback_label != NULL) {
        delete feedback_label;
        feedback_label = NULL;
    }
    if (theme_combo != NULL) {
        delete theme_combo;
        theme_combo = NULL;
    }
    if (tip_switcher != NULL) {
        delete tip_switcher;
        tip_switcher = NULL;
    }
    if (event_switcher != NULL) {
        delete event_switcher;
        event_switcher = NULL;
    }
    if (feedback_switcher != NULL) {
        delete feedback_switcher;
        feedback_switcher = NULL;
    }
}

QString SoundWidget::settingModuleName()
{
    return "SoundPage";
}

void SoundWidget::setLanguage() {
//    title_label->setText(tr("Sound effect"));
//    description_label->setText(tr("Set the sound theme you want."));
//    back_btn->setText(tr("Back"));
    theme_label->setText(tr("Sound theme") + ":");
    tip_label->setText(tr("Login tone") + ":");
    event_label->setText(tr("Event sounds") + ":");
    feedback_label->setText(tr("Input feedback sounds") + ":");

}

void SoundWidget::initSettingData()
{
    emit this->requestSoundData();

    this->initConnect();
}

void SoundWidget::onSendSoundList(const QString &currentSound, const QStringList &soundList)
{
    if (!soundList.isEmpty()) {
        m_soundlist.clear();
        m_soundlist = soundList;
        theme_combo->clear();
        theme_combo->clearEditText();
        theme_combo->addItems(m_soundlist);

        QList<QString>::Iterator it = m_soundlist.begin(), itend = m_soundlist.end();
        int initIndex = 0;
        for(;it != itend; it++,initIndex++)
        {
            if(*it == currentSound)
                break;
        }
        theme_combo->setCurrentIndex(initIndex);
    }
}

void SoundWidget::onSendEnableSoundValue(bool login_music, bool sound_event, bool input_sound)
{
    if (desktop != "mate" && desktop != "MATE")
    {
        tip_switcher->switchedOn = login_music;
    }

    event_switcher->switchedOn = sound_event;
    feedback_switcher->switchedOn = input_sound;
}

void SoundWidget::initConnect() {
//    connect(back_btn, SIGNAL(clicked()), this, SIGNAL(showSettingMainWidget()));
    connect(theme_combo, SIGNAL(currentIndexChanged(QString)),  this, SLOT(setVoiceTheme(QString)));
    connect(tip_switcher, SIGNAL(clicked()),  this, SLOT(setLoginTipVoice()));
    connect(event_switcher, SIGNAL(clicked()),  this, SLOT(setEventVoice()));
    connect(feedback_switcher, SIGNAL(clicked()),  this, SLOT(setInputFeedbackVoice()));

//    connect(sessionproxy, SIGNAL(string_value_notify(QString, QString)), this, SLOT(voicewidget_notify_string(QString, QString)));
//    connect(sessionproxy, SIGNAL(bool_value_notify(QString, bool)), this, SLOT(voicewidget_notify_bool(QString, bool)));
}

void SoundWidget::voicewidget_notify_string(QString key, QString value)
{
    if (key == "theme-name") {
        QList<QString>::Iterator it = m_soundlist.begin(), itend = m_soundlist.end();
        int index = -1;
        bool exist = false;
        for(;it != itend; it++)
        {
            ++index;
            if(*it == value) {
                exist = true;
                break;
            }
        }
        if (exist) {
            exist = false;
            theme_combo->setCurrentIndex(index);
        }
        else
            theme_combo->setCurrentIndex(-1);
    }
}

void  SoundWidget::voicewidget_notify_bool(QString key, bool value)
{
    if (key == "event-sounds") {
        event_switcher->switchedOn = value;
    }
    else if (key == "input-feedback-sounds") {
        feedback_switcher->switchedOn = value;
    }
}

void SoundWidget::setVoiceTheme(QString selectTheme) {
    emit resetVoiceTheme(selectTheme);
//    sessionproxy->set_sound_theme_qt(selectTheme);
}

void SoundWidget::setLoginTipVoice() {
    emit resetLoginTipVoice(tip_switcher->switchedOn);
//    sessionproxy->set_login_music_enable_qt(tip_switcher->switchedOn);
}

void SoundWidget::setEventVoice() {
    emit resetEventVoice(event_switcher->switchedOn);
//    sessionproxy->set_sound_event_enable_qt(event_switcher->switchedOn);
}

void SoundWidget::setInputFeedbackVoice() {
    emit resetInputFeedbackVoice(feedback_switcher->switchedOn);
//    sessionproxy->set_input_feedback_sounds_enable_qt(feedback_switcher->switchedOn);
}
