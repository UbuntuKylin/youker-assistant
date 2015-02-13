#ifndef MOUSEWIDGET_H
#define MOUSEWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSplitter>
#include <QComboBox>
#include <QRadioButton>
class SessionDispatcher;
class SystemDispatcher;

class MouseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit MouseWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0, SystemDispatcher *sproxy = 0);
    ~MouseWidget();
    void setLanguage();
    void initConnect();
    void initData();

//signals:
//    void showSettingMainWidget();

public slots:
    void setMouseCursorTheme(QString selectTheme);
    void setRadioButtonRowStatus(/*bool status*/);

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
    QLabel *size_label;
    QComboBox *theme_combo;
    QRadioButton *small_size;
    QRadioButton *big_size;
};

#endif // MOUSEWIDGET_H
