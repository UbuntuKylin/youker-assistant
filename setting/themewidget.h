#ifndef THEMEWIDGET_H
#define THEMEWIDGET_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QPushButton>
#include <QListView>
#include <QStringListModel>
#include <QStandardItemModel>
#include <QListWidget>
#include <QSplitter>

class SessionDispatcher;

class ThemeWidget : public QWidget
{
    Q_OBJECT
public:
    explicit ThemeWidget(QWidget *parent = 0, SessionDispatcher *proxy = 0);
    ~ThemeWidget();
    void setLanguage();
    void initConnect();
    void initCurrentTheme(QListWidgetItem *init_item);

protected:
    void paintEvent(QPaintEvent *);

//signals:
//    void showSettingMainWidget();

public slots:
    void onItemClicked(QListWidgetItem *selected_item);

private:
//    QSplitter *splitter;
//    QWidget * top_widget;
//    QWidget * bottom_widget;

//    QPushButton *back_btn;
//    QLabel *title_label;
//    QLabel *description_label;

//    QListView *list_view;
//    QStringListModel *model;
//    QStandardItemModel *cokMusicListModel;
    QListWidget *list_widget;
    int current_index;
    QLabel *using_label;
    SessionDispatcher *sessionproxy;
};

#endif // THEMEWIDGET_H
