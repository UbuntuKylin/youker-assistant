#ifndef PANELWIDGET_H
#define PANELWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>
#include "../component/kylinswitcher.h"
#include <QSplitter>
#include <QSlider>
#include <QDoubleSpinBox>
#include <QRadioButton>
class SessionDispatcher;

class PanelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit PanelWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    ~PanelWidget();
    void setLanguage();
    void initConnect();
    void initData();

//signals:
//    void showSettingMainWidget();

public slots:
    void setDateFormat(QString selected);
    void setShowBatteryIcon(QString selected);
    void setTransparencyValue(double value);
    void setRadioButtonRowStatus(/*bool status*/);
    void setDisplaySeconds();
    void setDisplayWeek();
    void setDisplayDate();
    void setDisplayBatteryPercentage();
    void setDisplayBatteryTime();

private:
    SessionDispatcher *sessionproxy;
//    QSplitter *splitter;
//    QWidget * top_widget;
//    QWidget * bottom_widget;

//    QPushButton *back_btn;
//    QLabel *title_label;
//    QLabel *description_label;

    QLabel *blur_label;
    QLabel *transparency_label;
    QLabel *date_format_label;
    QLabel *second_label;
    QLabel *week_label;
    QLabel *date_label;
    QLabel *battery_icon_label;
    QLabel *battery_percentage_label;
    QLabel *battery_time_label;
    QRadioButton *smart_radio;
    QRadioButton *static_radio;
    QRadioButton *clear_radio;
    QDoubleSpinBox *transparency_slider;
    QComboBox *date_combo;
    KylinSwitcher *second_switcher;
    KylinSwitcher *week_switcher;
    KylinSwitcher *date_switcher;
    QComboBox *battery_combo;
    KylinSwitcher *battery_percentage_switcher;
    KylinSwitcher *battery_time_switcher;
};

#endif // PANELWIDGET_H
