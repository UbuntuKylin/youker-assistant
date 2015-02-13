#ifndef KYLINMENU_H
#define KYLINMENU_H

#include <QMenu>
#include <QDesktopServices>
#include <QUrl>

class MainWindow;

class KylinMenu : public QMenu
{
    Q_OBJECT

public:
    explicit KylinMenu(QWidget *parent = 0);
    void setLanguage();
    void initConnect();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}

private:
    void createActions();

public slots:
    void forumHelp();
    void questionFeedback();

private:
    QAction *help_action;
//    QAction *features_action;
    QAction *feedback_action;
//    QAction *setting_action;
    QAction *about_action;
    MainWindow *p_mainwindow;
};

#endif // KYLINMENU_H
