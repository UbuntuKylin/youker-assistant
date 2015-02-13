#ifndef ICONWIDGET_H
#define ICONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QComboBox>
#include "../component/kylinswitcher.h"
#include <QSplitter>
class SessionDispatcher;

class IconWidget : public QWidget
{
    Q_OBJECT
public:
    explicit IconWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    ~IconWidget();
    void setLanguage();
    void initConnect();
    void initData();

//signals:
//    void showSettingMainWidget();

public slots:
    void changeSwitcherStatus();
    void setIconTheme(QString selectTheme);
    void setShowDesktopIcons();
    void setFolderIcon();
    void setNetworkIcon();
    void setRecycleBinIcon();
    void setDiskIcon();

private:
//    QSplitter *splitter;
//    QWidget * top_widget;
//    QWidget * bottom_widget;

//    QPushButton *back_btn;
//    QLabel *title_label;
//    QLabel *description_label;
    SessionDispatcher *sessionproxy;

    QLabel *theme_label;
    QLabel *show_label;
    QLabel *folder_label;
    QLabel *network_label;
    QLabel *recycle_label;
    QLabel *disk_label;
    QComboBox *theme_combo;
    KylinSwitcher *show_switcher;
    KylinSwitcher *folder_switcher;
    KylinSwitcher *network_switcher;
    KylinSwitcher *recycle_switcher;
    KylinSwitcher *disk_switcher;
};

#endif // ICONWIDGET_H
