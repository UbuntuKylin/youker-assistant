#ifndef KOBEMENU_H
#define KOBEMENU_H

#include <QWidget>
#include <QToolButton>
#include <QDesktopServices>
#include <QUrl>

class MainWindow;

class KobeMenu : public QWidget
{
    Q_OBJECT
public:
    explicit KobeMenu(QWidget *parent = 0);
    void setLanguage();
    void initConnect();
    void setParentWindow(MainWindow* window) { p_mainwindow = window;}

private:
    void createActions();

public slots:
    void forumHelp();

private:
    QToolButton *help_action;
    QToolButton *features_action;
    QToolButton *feedback_action;
    QToolButton *setting_action;
    QToolButton *about_action;
    MainWindow *p_mainwindow;

};

#endif // KOBEMENU_H
