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

#ifndef VOICEWIDGET_H
#define VOICEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>
#include "../component/kylinswitcher.h"
#include <QSplitter>
class SessionDispatcher;
class SystemDispatcher;

class VoiceWidget : public QWidget
{
    Q_OBJECT
public:
    explicit VoiceWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0, SystemDispatcher *sproxy = 0);
    ~VoiceWidget();
    void setLanguage();
    void initConnect();
    void initData();

//signals:
//    void showSettingMainWidget();

public slots:
    void setVoiceTheme(QString selectTheme);
    void setLoginTipVoice();
    void setEventVoice();
    void setInputFeedbackVoice();

private:
    SessionDispatcher *sessionproxy;
    SystemDispatcher *systemproxy;
//    QSplitter *splitter;
//    QWidget * top_widget;
//    QWidget * bottom_widget;

//    QPushButton *back_btn;
//    QLabel *title_label;
//    QLabel *description_label;

    QLabel *theme_label;
    QLabel *tip_label;
    QLabel *event_label;
    QLabel *feedback_label;
    QComboBox *theme_combo;
    KylinSwitcher *tip_switcher;
    KylinSwitcher *event_switcher;
    KylinSwitcher *feedback_switcher;
};

#endif // VOICEWIDGET_H
