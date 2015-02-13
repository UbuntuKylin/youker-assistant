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
