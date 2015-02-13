#ifndef LAUNCHERWIDGET_H
#define LAUNCHERWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>
#include "../component/kylinswitcher.h"
#include <QSplitter>
#include <QSlider>
#include <QDoubleSpinBox>
class SessionDispatcher;

class LauncherWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LauncherWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    ~LauncherWidget();
    void setLanguage();
    void initConnect();
    void initData();

//signals:
//    void showSettingMainWidget();

public slots:
    void setIconColouring(QString selectColour);
    void setAutoHide();
    void setDisplayDesktopIcon();
    void setIconSizeValue(int value);
    void setTransparencyValue(double value);

private:
    SessionDispatcher *sessionproxy;
//    QSplitter *splitter;
//    QWidget * top_widget;
//    QWidget * bottom_widget;

//    QPushButton *back_btn;
//    QLabel *title_label;
//    QLabel *description_label;

    QLabel *size_label;
    QLabel *size_value_label;
    QLabel *hide_label;
    QLabel *icon_label;
    QLabel *transparency_label;
    QLabel *background_label;
    QSlider *size_slider;
    KylinSwitcher *hide_switcher;
    KylinSwitcher *icon_switcher;
    QDoubleSpinBox *transparency_slider;
    QComboBox *backgound_combo;
};

#endif // LAUNCHERWIDGET_H
