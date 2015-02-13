#ifndef SYSTEMTRAY_H
#define SYSTEMTRAY_H

#include <QSystemTrayIcon>
#include <QMenu>
#include <QAction>
#include <QApplication>
#include <QWidgetAction>
#include <QPushButton>
#include <QLabel>
#include <QHBoxLayout>
#include <QPainter>

class SystemTray : public QSystemTrayIcon
{
    Q_OBJECT

public:
    explicit SystemTray(QWidget *parent = 0);
    ~SystemTray();
    void setLanguage();

signals:
    void showWidget();

private:
    void initTrayActions();

private:
    QMenu *tray_menu;
    QAction *action_open;
    QAction *action_logout;
};

#endif // SYSTEMTRAY_H
