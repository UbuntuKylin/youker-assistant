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

#ifndef SOUNDWIDGET_H
#define SOUNDWIDGET_H

#include <QWidget>
#include "../component/kylinswitcher.h"
#include "settingmodulelpage.h"

class QLabel;
class QPushButton;
class QComboBox;

class SoundWidget : public SettingModulePage
{
    Q_OBJECT
public:
    explicit SoundWidget(QWidget *parent = 0, QString cur_desktop = "");
    ~SoundWidget();
    void setLanguage();
    void initConnect();
    void initSettingData() Q_DECL_OVERRIDE;
    QString settingModuleName() Q_DECL_OVERRIDE;

public slots:
    void setVoiceTheme(QString selectTheme);
    void setLoginTipVoice();
    void setEventVoice();
    void setInputFeedbackVoice();
    void voicewidget_notify_string(QString key, QString value);
    void voicewidget_notify_bool(QString key, bool value);


    void onSendSoundList(const QString &currentSound, const QStringList &soundList);
    void onSendEnableSoundValue(bool login_music, bool sound_event, bool input_sound);

signals:
    void requestSoundData();
    void resetVoiceTheme(QString selectTheme);
    void resetLoginTipVoice(bool b);
    void resetEventVoice(bool b);
    void resetInputFeedbackVoice(bool b);

private:
    QString desktop;
    QStringList m_soundlist;
    QLabel *theme_label;
    QLabel *tip_label;
    QLabel *event_label;
    QLabel *feedback_label;
    QComboBox *theme_combo;
    KylinSwitcher *tip_switcher;
    KylinSwitcher *event_switcher;
    KylinSwitcher *feedback_switcher;
};

#endif // SOUNDWIDGET_H
