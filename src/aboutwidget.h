#ifndef ABOUTWIDGET_H
#define ABOUTWIDGET_H

#include <QDialog>
#include <QWidget>
#include <QPushButton>
#include <QLabel>
#include <QIcon>
#include <QFont>
#include <QPalette>
#include <QScrollArea>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextBrowser>
#include <QDebug>

class AboutWidget : public QDialog
{
    Q_OBJECT
public:
    explicit AboutWidget(QWidget *parent = nullptr);
    ~AboutWidget();

    void initUI();
    void setAppIcon(const QString &text);
    void setAppName(const QString &text);
    void setAppVersion(const QString &text);
    void setAppDescription(const QString &text);
protected:
//    void closeEvent(QCloseEvent *event);

private:
    QVBoxLayout *main_layout = nullptr;

    QLabel *title_icon = nullptr;
    QLabel *title_name = nullptr;
    QPushButton *close_btn = nullptr;

    QLabel *app_icon = nullptr;
    QLabel *app_name = nullptr;
    QLabel *app_version = nullptr;
    QTextBrowser *app_description = nullptr;

};

#endif // ABOUTWIDGET_H
