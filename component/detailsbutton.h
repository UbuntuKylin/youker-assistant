#ifndef DETAILSBUTTON_H
#define DETAILSBUTTON_H

#include <QPushButton>
#include <QString>
#include <QPainter>
#include <QPixmap>
#include <QString>
#include <QStyleOption>
#include <QColor>

class DetailsButton : public QPushButton
{
    Q_OBJECT

public:
    explicit DetailsButton(QString text,QWidget *parent = 0);
    ~DetailsButton();
    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);

signals:
    void clicked();

private:
    QString buttonText;

    bool hover=false;
//    bool pressed=false;
};

#endif // DETAILSBUTTON_H
