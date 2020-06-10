#ifndef OPTIMIZEDWIDGET_H
#define OPTIMIZEDWIDGET_H

#include <QWidget>
#include <QFrame>
#include <QPushButton>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QString>
#include <QFont>
#include <QPixmap>

class OptimizedWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OptimizedWidget(QWidget *parent = nullptr);
    ~OptimizedWidget();

    void InitUI();
    void InitTopUI();
    void InitMiddleUI();
    void InitBottomUI();

signals:


private:
    QVBoxLayout *main_layout;
    QHBoxLayout *middle_layout;

    QFrame *spilterLine;

    QPushButton *start_btn;

    QLabel *main_label;
    QLabel *top_tip;

    QLabel *boot_label;
    QLabel *boot_icon;

    QLabel *system_label;
    QLabel *system_icon;

    QLabel *app_label;
    QLabel *app_icon;

    QPushButton *cancel_btn;
    QPushButton *scan_btn;
    QPushButton *return_btn;
};

#endif // OPTIMIZEDWIDGET_H
