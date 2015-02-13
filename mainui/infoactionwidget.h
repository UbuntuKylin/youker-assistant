#ifndef INFOACTIONWIDGET_H
#define INFOACTIONWIDGET_H

#include <QWidget>
#include <QLabel>
#include <QHBoxLayout>
#include <QVBoxLayout>

class InfoActionWidget : public QWidget
{
    Q_OBJECT
public:
    explicit InfoActionWidget(QWidget *parent = 0);
    ~InfoActionWidget();
    void setLanguage();

private:
    QLabel *img_label;
    QLabel *suggest_label;
//    QLabel *result_label;
};

#endif // INFOACTIONWIDGET_H
