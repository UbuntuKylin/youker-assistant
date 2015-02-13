#ifndef ANIMATIONWIDGET_H
#define ANIMATIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QHBoxLayout>
#include <QSplitter>
#include <QListWidget>
class SystemDispatcher;

class AnimationWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AnimationWidget(QWidget *parent = 0, SystemDispatcher *proxy = 0);
    ~AnimationWidget();
    void setLanguage();
    void initConnect();
    void initData();
//    QString showSelectFileDialog();

//signals:
//    void showSettingMainWidget();

public slots:
    void selectCustomAnimation();
    void setCustomAnimation();
    void deleteSelectedAnimation(QString name);
    void displayCurrentItemInfo(QString info);

private:
    SystemDispatcher *systemproxy;
//    QSplitter *splitter;
//    QWidget * top_widget;
//    QWidget * bottom_widget;
    QWidget * left_widget;
    QWidget * right_widget;

//    QPushButton *back_btn;
//    QLabel *title_label;
//    QLabel *description_label;
    QLabel *title_label;
    QPushButton *custom_btn;
    QPushButton *ok_btn;
    QWidget *view_widget;
    QWidget *show_widget;
    QLabel *tip_label;

    QListWidget *list_widget;
    QString selected_animation;
};

#endif // ANIMATIONWIDGET_H
