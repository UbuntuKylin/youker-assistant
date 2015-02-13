#ifndef NAUTILUSWIDGET_H
#define NAUTILUSWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include "../component/kylinswitcher.h"
#include <QSplitter>
#include <QSlider>
class SessionDispatcher;

class NautilusWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NautilusWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    ~NautilusWidget();
    void setLanguage();
    void initConnect();
    void initData();

//signals:
//    void showSettingMainWidget();

public slots:
    void setLocation();
    void setMountMedia();
    void setOpenFolder();
    void setAutorunProgram();
    void setIconSizeValue(int value);
    void setCacheTimeValue(int value);
    void setCacheSizeValue(int value);

private:
    SessionDispatcher *sessionproxy;
//    QSplitter *splitter;
//    QWidget * top_widget;
//    QWidget * bottom_widget;

//    QPushButton *back_btn;
//    QLabel *title_label;
//    QLabel *description_label;

    QLabel *location_label;
    QLabel *mount_media_label;
    QLabel *open_folder_label;
    QLabel *autorun_program_label;
    QLabel *icon_size_label;
    QLabel *size_value_label;
    QLabel *cache_time_label;
    QLabel *time_value_label;
    QLabel *cache_size_label;
    QLabel *cache_value_label;
    KylinSwitcher *location_switcher;
    KylinSwitcher *mount_media_switcher;
    KylinSwitcher *open_folder_switcher;
    KylinSwitcher *autorun_program_switcher;
    QSlider *icon_size_slider;
    QSlider *cache_time_slider;
    QSlider *cache_size_slider;

};

#endif // NAUTILUSWIDGET_H
